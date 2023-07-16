#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Config
int overrideOS = -1; // Keep at -1 to display your OS, otherwise use: 0 - Windows
					 //												  1 - Linux			    (General)
					 //												  2 - MacOS
					 //												  3 - Do not display     (hides your OS and replaces it with: OS-RP)

int currentAppDisplay = 0; // Changes how your current app is shown: -1 - Do not display    (doesn't show your current application)
						   //										 0  - Default		    (Title only)

int displayOSRPTime = 0; // Changes OSRP time display: -1 - Do not display
						 //							   0  - Default (Display)

int supportOSRP = 0; // This option allows you to support OS-RP by adding a link to the repository: -1 - Do not display
					 //																			    0  - Support (Will add a small image with the link in the text)


// Code
// READ FILE LINE-BY-LINE AND SET VARIABLES CORRECTLY
void readCFG() {
	std::ifstream file("osrp.txt");

	int lI = 0;
	for (std::string line; getline(file, line); )
	{
		switch (lI) {
		case 1: {
			overrideOS = std::stoi(line);
			break;
		}
		case 2: {
			currentAppDisplay = std::stoi(line);
			break;
		}
		case 3: {
			displayOSRPTime = std::stoi(line);
		}
		case 4: {
			supportOSRP = std::stoi(line);
		}
		}
		lI++;
	}
}

// CHECK CONFIG FILE, OTHERWISE CREATE
FILE* exists() {
	FILE* cfg;
	if (cfg = fopen("osrp.txt", "r")) {
		std::cout << "Configuration file exists! Reading configuration...\n";
		fclose(cfg);
		readCFG();
		return cfg;
	}
	else {
		std::cout << "Configuration doesn't exist, creating!\n";
		return NULL;
	}
}

// CREATE CONFIG
FILE* createCfg() {
	std::fstream file;
	std::ofstream { "osrp.txt" };
	file.open("osrp.txt");

	if (!file) {
		std::cout << "File error!\n";
	}
	else {
		std::cout << "Configuration created! [osrp.txt]\n";
		file << "*OS-RP CONFIG* -- CHECK GITHUB FOR EXPLANATION -- OR READ THE CODE IN OS-RP.H\n"
			"-1\n"
			"0\n"
			"0\n"
			"0";
		file.close();
	}

	return exists();
}

// SECOND METHOD TO CHECK WHETHER CONFIG EXISTS
FILE* cfgFileExists() {
	FILE* file = exists();
	if (file == NULL) {
		file = createCfg();
	}
	return file;
}
