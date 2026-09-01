#ifndef PANEL_EXPORT_COMMAND_TO_ARRAY_HH
#define PANEL_EXPORT_COMMAND_TO_ARRAY_HH
#include <string>
#include <vector>

std::vector<std::string> runCommandAndReturnEachLineAsEntryInArray(const char *cmd);

#endif
