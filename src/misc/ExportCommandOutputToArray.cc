#include "ExportCommandOutputToArray.hh"
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdio>
#include <vector>
#include <sstream>
#include <string>

// NOTE: this runs a command and returns a array with the results,
// each line that would ordinarily get output in to the console
// gets saved as a entry in the array.
std::vector<std::string> runCommandAndReturnEachLineAsEntryInArray(const char *cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return {"ERROR"};
    char buffer[128];
    std::string accumulatedOutput;
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            accumulatedOutput += buffer;
    }
    std::vector<std::string> lines;
    std::stringstream ss(accumulatedOutput);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}
