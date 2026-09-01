#include "GetWindowIDs.hh"
#include "../misc/ExportCommandOutputToArray.hh"
#include <string>
#include <memory>
#include <vector>

// Get IDs of running GUI programs
std::vector<std::string> getWindowIDs() {
    // This command outputs window IDs of GUI programs
    std::string getRunningIDsCommand = R"(
for win_id in $( wmctrl -l | cut -d' ' -f1 ); do
    if xprop -id "$win_id" _NET_WM_WINDOW_TYPE | grep -q _NET_WM_WINDOW_TYPE_NORMAL; then
        echo "$win_id"
    fi
done)";
    std::vector<std::string> windowIDsList = runCommandAndReturnEachLineAsEntryInArray(getRunningIDsCommand.c_str());
    return windowIDsList;
}
