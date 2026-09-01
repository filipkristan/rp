#include "GetFocusedWindowID.hh"
#include "../misc/ExportCommandOutputToArray.hh"
#include <string>
#include <vector>

std::string getFocusedWindowID() {
    std::string getFocusedWindowIDFromWindowIDCommand =
            R"(xprop -root _NET_ACTIVE_WINDOW | awk '{printf "0x%08x\n", strtonum($NF)}')";
    std::vector<std::string> focusedWindowIDArray = runCommandAndReturnEachLineAsEntryInArray(
        getFocusedWindowIDFromWindowIDCommand.c_str());
    std::string focusedWindowID = focusedWindowIDArray[0];
    return focusedWindowID;
}
