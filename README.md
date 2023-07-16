# OS-RP
OS-RP allows you to show details about your OS and current activity on Discord. Functionality is pretty limited so far.
To build this you need CMake.
Only Windows is supported for the time being (library linking issues, I suck at linking).
PRs are welcome.

# Quick explanation of the config system:
A config file is automatically generated on first run.
The config system isn't very good, but it works. Here is how you can change it (if there are any big errors in it, it will fall back to default values):
The config system is based on line order so these are going to be in the CORRECT line order
- **anything, the first line is ignored, still has to be there though, you can keep it empty**
- OS override **(-1 auto OS, 0 Windows, 1 Linux, 2 MacOS, 3 Hidden [Replaced with OSRP])**
- Current focused application display **(-1 Hidden [Completely hidden, not even replaced], 0 Display)**
- OS-RP usage time **(-1 Hidden, 0 Display)**
- Support OSRP [This option allows you to support OS-RP by adding an image and a link to the repository] **(-1 Do not support, 0 Support)**

![unstable](https://github.com/PetrTech/OS-RP/assets/55279432/203b9eef-02ea-45eb-adeb-27bfdc833dba)
![OSRP](https://github.com/PetrTech/OS-RP/assets/55279432/96a1dc6c-31ed-4ae1-ac11-0e391ddff449)
