#include "OS-RP.h"
#include <iostream>
#include <fstream>
#include <discord.h>
#include <chrono>
#include <thread>
#include <csignal>

using namespace std;

discord::Core* core{};

volatile sig_atomic_t g_shouldExit = 0;
int usageTime = 0; // in seconds

// APPLE AND LINUX NOT TESTED!!!!! IF THERE ARE ANY ISSUES, YOU CAN CREATE A PR
#ifdef _WIN32
#include <Windows.h>
const char* platform = "windows";

// Possibly incorrect.
std::string getWindowsVersion() {
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (GetVersionEx(&osvi)) {
		if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0)
			return "Windows 10";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
			return "Windows 8.1";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
			return "Windows 8";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
			return "Windows 7";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			return "Windows Vista";
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
			return "Windows XP 64-bit Edition";
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			return "Windows XP";
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			return "Windows 2000";
	}

	return "Unknown";
}
#elif __linux__
#include <sys/utsname.h>

const char* platform = "linux";

std::string getLinuxDistroVersion() {
	struct utsname systemInfo;
	if (uname(&systemInfo) == 0) {
		std::string version(systemInfo.release);
		return "Linux " + version;
	}
	return "Unknown";
}

#elif __APPLE__
#include <sys/utsname.h>

const char* platform = "macos";

std::string getMacOSVersion() {
	struct utsname systemInfo;
	if (uname(&systemInfo) == 0) {
		std::string version(systemInfo.release);
		return "macOS " + version;
	}
	return "Unknown";
}
#else
const char* platform = "osrp";
#endif

// Signal handler for SIGINT
void handleSignal(int signal) {
	if (signal == SIGINT) {
		g_shouldExit = 1;
		std::cout << "Caught SIGINT, cleaning up and exiting." << std::endl;
	}
}

void clear() {
	core->ActivityManager().ClearActivity([](discord::Result result) {
		if (result == discord::Result::Ok) {
			std::cout << "Cleared" << std::endl;
		}
		else {
			std::cout << "Failed to clear" << std::endl;
		}
	});
}

std::string formatTime(int seconds) {
	int days = seconds / (60 * 60 * 24);
	seconds %= (60 * 60 * 24);

	int hours = seconds / (60 * 60);
	seconds %= (60 * 60);

	int minutes = seconds / 60;
	seconds %= 60;

	std::ostringstream oss;
	oss << days << "d" << hours << "h" << minutes << "min" << seconds << "s";

	return oss.str();
}

void setActivity() {
	discord::Activity activity{};

	std::string osVer = "No Details";

#ifdef _WIN32
	osVer = getWindowsVersion();
	HWND focusedWindow = GetForegroundWindow();
	char windowTitle[256];

	GetWindowTextA(focusedWindow, windowTitle, sizeof(windowTitle));

	if (currentAppDisplay != -1) {
		activity.SetDetails(windowTitle);
	}
#elif __linux__
	osVer = getLinuxDistroVersion();
#elif __APPLE__
	osVer = getMacOSVersion();
#endif

	if (displayOSRPTime != -1) {
		activity.SetState(("OSRP time: " + formatTime(usageTime)).c_str());
	}

	if (overrideOS == -1) {
		activity.GetAssets().SetLargeText(osVer.c_str());
	}
	else if (overrideOS == 0) {
		platform = "windows";
	}
	else if (overrideOS == 1) {
		platform = "linux";
	}
	else if (overrideOS == 2) {
		platform = "macos";
	}
	else {
		platform = "osrp";
	}
	
	activity.GetAssets().SetLargeImage(platform);

	if (supportOSRP != -1) {
		activity.GetAssets().SetSmallImage("osrp");
		activity.GetAssets().SetSmallText("https://github.com/PetrTech/OS-RP");
	}

	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

int main()
{
	try {
		using namespace std::this_thread;
		using namespace std::chrono;

#ifdef _WIN32
		std::signal(SIGINT, handleSignal);
#endif

		FILE* cfg = cfgFileExists();

		auto result = discord::Core::Create(1130163445740863508, DiscordCreateFlags_Default, &core);
		discord::Activity activity{};

		setActivity();

		cout << "Running, keep alive.";

		int loop = 0;
		while (!g_shouldExit) {
			try {
				// Your main loop logic here
				if (loop == 30) {
					loop = 0;
					usageTime++;
				}

				sleep_for(milliseconds(33));
				setActivity();
				loop++;
				::core->RunCallbacks();
			}
			catch (const std::exception& e) {
				std::cerr << "Exception caught: " << e.what() << std::endl;
				clear();
				g_shouldExit = 1;
			}
		}
	}
	catch (const std::exception& e) {
		clear();
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	clear();

	return 0;
}
