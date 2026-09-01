#include "CheckIfWindowIsActive.hh"
#include "../misc/ExportCommandOutputToArray.hh"
#include <cstring>
#include <ostream>
#include <string>

bool checkIfWindowIsActive(const std::string &id) {
    bool res = false;
    std::string firstHalf = R"(if xprop -id )";
    std::string lastHalf = R"( _NET_WM_PID > /dev/null 2>&1; then
        echo "Window exists"
        else
        echo "Window does not exist"
        fi
    )";
    std::string command;
    command.append(firstHalf);
    command.append(id);
    command.append(lastHalf);

    std::vector<std::string> checkResArray = runCommandAndReturnEachLineAsEntryInArray(command.c_str());

    // Check if a window is active and return the proper result
    if (strcmp(checkResArray[0].c_str(), "Window exists") == 0) {
        res = true; // window exists
        // std::cout << "! - CHAD - " << checkResArray[0].c_str() << std::endl; // NOTE: debug
    } else {
        res = false; // window doesn't exist
        // std::cout << "? - CHUD - " << checkResArray[0].c_str() << std::endl; // NOTE: debug
    }
    return res;
}
