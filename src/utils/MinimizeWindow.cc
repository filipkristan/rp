#include "MinimizeWindow.hh"
#include <string>

void minimizeWindow(const std::string &windowID) {
    std::string minimizeWindowCommand = "xdotool windowminimize " + windowID;
    system(minimizeWindowCommand.c_str());
}
