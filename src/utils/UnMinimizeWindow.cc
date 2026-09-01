#include "UnMinimizeWindow.hh"
#include <cstdlib>
#include <string>

void unMinimizeWindow(const std::string &windowID) {
    std::string unMinimizeWindowCommand = "xdotool windowactivate " + windowID;
    system(unMinimizeWindowCommand.c_str());
}
