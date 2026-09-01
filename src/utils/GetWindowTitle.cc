#include "GetWindowTitle.hh"
#include "../misc/ExportCommandOutputToArray.hh"
#include <iostream>

// TODO: Fix title max length
// Get the window title from tile ID
std::string getWindowTitle(const std::string &id, const std::string &titleMaxLength) {
    std::string getTitleFromWindowIDCommand = "xdotool getwindowname " + id + " | awk '{print substr($0, 1, ";
    getTitleFromWindowIDCommand.append(titleMaxLength);
    getTitleFromWindowIDCommand.append(")}'");
    std::vector<std::string> windowTitleArray = runCommandAndReturnEachLineAsEntryInArray(
        getTitleFromWindowIDCommand.c_str());
    std::string windowTitle = windowTitleArray[0];
    return windowTitle;
}
