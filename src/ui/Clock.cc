#include "../ui/Clock.hh"
#include "../../src/misc/ExportCommandOutputToArray.hh"
#include "Button.hh"
#include "Fonts.hh"
#include <iostream>
#include <string>
#include <thread>

// Get the current time
std::string getClockTime() {
    std::string getClockTimeCommand = "date '+ %H:%M %p'";
    std::vector<std::string> clockArray = runCommandAndReturnEachLineAsEntryInArray(
        getClockTimeCommand.c_str());
    std::string time = clockArray[0];
    return time;
}

// Set the initial clock value
void setClock() {
    // Get all necessary info and calculate the desired X position for the clock
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor);
    float clockX = monitorWidth - 103;
    ClockButton.clear();
    ClockButton.insert(ClockButton.end(), {
                           Button({clockX, 6}, 100, 40, getClockTime(), "CLOCK", clockTexture, 22,
                                  14)
                       });
}

// Update the clock label every 10 seconds to properly reflect the current time
void updateClock() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        ClockButton[0].label = getClockTime();
        // std::cout << "Time: " << ClockButton[0].label << std::endl; // DEBUG
    }
}

void drawClock() {
    for (const auto &btn: ClockButton) {
        DrawTextureRec(btn.texture, btn.sourceRec, (Vector2){btn.bounds.x, btn.bounds.y}, WHITE);
        //DrawText(btn.label.c_str(), btn.pos.x + btn.labelHorizontalPaddingX, btn.pos.y + btn.labelVerticalPaddingY, btn.fontSize,WHITE);
        DrawTextEx(font2, btn.label.c_str(), {
                       btn.pos.x + btn.labelHorizontalPaddingX - 14, btn.pos.y + btn.labelVerticalPaddingY - 9
                   }, 28, 0, WHITE);
    }
}
