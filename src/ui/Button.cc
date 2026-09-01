#include "Button.hh"
#include "InternetConnectivityButton.hh"
#include <raylib.h>
#include <iostream>
#include <vector>

std::vector<Button> Buttons;
std::vector<Button> StartMenuButton;
std::vector<Button> TaskListButtons;
std::vector<Button> ClockButton;
std::vector<Button> VolumeMixerButton;
std::vector<std::string> windowIDsList;

void initButtons() {
    buttonTexture = LoadTexture("../res/button.png");
    emptyTexture = LoadTexture("../res/emptyButton.png");
    placeholderTexture = LoadTexture("../res/placeholder.png");
    startMenuTexture = LoadTexture("../res/startbutton.png");
    faviconIconPlaceholderTexture = LoadTexture("../res/favicon.png");
    clockTexture = LoadTexture("../res/clock.png");
    inactiveButtonTexture = LoadTexture("../res/inactivebutton.png");
    volumeIconButtonTexture = LoadTexture("../res/volumeicon.png");
    ethernetButtonTexture = LoadTexture("../res/ethernet.png");
    inuseButtonTexture = LoadTexture("../res/buttoninuse.png");
    tasklisticontexture = LoadTexture("../res/ethernet.png");
}

void updateButtons(std::vector<Button> &btn) {
    Vector2 mousePoint = GetMousePosition();
    // loop trough buttons to check for mouse interactions
    for (int i = 0; i < btn.size(); i++) {
        btn[i].action = false;
        if (CheckCollisionPointRec(mousePoint, btn[i].bounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btn[i].state = 2;
            } else {
                btn[i].state = 1;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btn[i].action = true;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                std::cout << "right clicked on button!" << std::endl;
                std::cout << "maybe a menu should appear?" << std::endl;
            }
        } else {
            btn[i].state = 0;
        }

        // Handle button actions
        if (btn[i].action) {
            if (btn[i].windowID == "STARTBUTTON") {
                std::cout << "You clicked the start button!" << std::endl;
                system("rofi -show run"); // runs rofi's program runner
            } else if (btn[i].windowID == "CLOCK") {
                std::cout << "You clicked the clock!" << std::endl;
                // updateClock(); NOTE: old function used to directly update the clock label to set updated clock, now a thread takes care of the clock and updates it automatically every 10 seconds
            } else if (btn[i].windowID == "VOLUMEMIXER") {
                std::cout << "You clicked the volume icon!" << std::endl;
            } else if (btn[i].windowID == "INTERNETCONNECTIVITY") {
                std::cout << "You clicked the connectivity button!" << std::endl;
            }
        }

        // Update the source rectangle Y position based on state (this is related to changing button texture depending if a mouse is hovering over it or if a mouse button click was detected)
        float frameHeight = static_cast<float>(buttonTexture.height) / 3.0f;
        btn[i].sourceRec.y = btn[i].state * frameHeight;
    }
}
