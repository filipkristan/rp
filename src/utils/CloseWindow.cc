#include "CloseWindow.hh"
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

void closeWindow(const std::string &id) {
    std::string command = "xdotool windowclose " + id;
    system(("xdotool windowclose " + id).c_str());
}
