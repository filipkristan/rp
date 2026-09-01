#include "../ui/TaskList.hh"
#include "../../src/misc/ExportCommandOutputToArray.hh"
#include "../../src/misc/GetProgramIconPathFromWindowID.hh"
#include "../utils/CheckIfWindowIsActive.hh"
#include "../utils/GetFocusedWindowID.hh"
#include "../utils/UnMinimizeWindow.hh"
#include "../utils/MinimizeWindow.hh"
#include "../utils/GetWindowTitle.hh"
#include "../utils/GetWindowIDs.hh"
#include "../utils/CloseWindow.hh"
#include "Button.hh"
#include "Fonts.hh"
#include <chrono>
#include <iostream>

std::string icontexturepaths[10] = {
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png",
    "../res/placeholder.png"
};

void setTaskList() {
    int numberOfButtons = 10; // TODO: Get max number of buttons by calculating width of the screen
    for (int i = 0; i < numberOfButtons; ++i) {
        // Adds some padding before the tasklist for the start button and then and some more padding for each new button to stop them from stacking on each other
        float padding = 0;
        if (padding < numberOfButtons) {
            padding = 48 + 163 * i;
        } else {
            padding = 0;
        }
        REAL_TaskListButtons[i] = (Button({padding, 6}, 160, 40, "", "EMPTY",
                                          emptyTexture, 42,
                                          12));
        REAL_TaskListButtons[i].tasklisticon = LoadTexture(icontexturepaths[i].c_str());
        REAL_TaskListButtons[i].currentUrl = icontexturepaths[i];
        textureimage = LoadImage("../res/ethernet.png");
    }
}

void setTaskListButtonIcon(int index) {
}

void updateIconPaths() {
    // has to be execured on main thread?
    programs = getWindowIDs();
    for (int i = 0; i < programs.size(); ++i) {
        UnloadTexture(icontextures[i]);
        std::string id = programs[i];
        icontexturepaths[i] = getProgramIconPathFromWindowID(id);
        icontextures[i] = LoadTexture(icontexturepaths[i].c_str());
    }
}

// void updateIconPaths() {
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     programs = getWindowIDs();
//     for (int i = 0; i < programs.size(); ++i) {
//         UnloadTexture(icontextures[i]);
//         std::string id = programs[i];
//         icontexturepaths[i] = getProgramIconPathFromWindowID(id);
//         icontextures[i] = LoadTexture(icontexturepaths[i].c_str());
//     }
// }

// NOTE: Calculate the amount of needed filled and empty buttons and then populate their properties
void resetTaskList() {
    programs = getWindowIDs();

    int numberofemptybuttons = REAL_TaskListButtons.size() - programs.size();
    for (int i = 0; i < programs.size(); ++i) {
        REAL_TaskListButtons[i].windowID = programs[i];
    }
    for (int i = 0; i < numberofemptybuttons; ++i) {
        REAL_TaskListButtons[programs.size() + i].windowID = "EMPTY";
    }

    for (int i = 0; i < REAL_TaskListButtons.size(); ++i) {
        if (checkIfWindowIsActive(REAL_TaskListButtons[i].windowID) == true) {
            // Set window title etc...
            REAL_TaskListButtons[i].tasklisticon = icontextures[i];
            std::string windowtitle = getWindowTitle(REAL_TaskListButtons[i].windowID, "20");
            if (windowtitle.length() < 12) {
                REAL_TaskListButtons[i].label = getWindowTitle(REAL_TaskListButtons[i].windowID, "20");
            } else if (windowtitle.length() >= 12) {
                //  doesnt seem to work fully
                std::string modifiedTitle = windowtitle.substr(0, 12);
                REAL_TaskListButtons[i].label = modifiedTitle;
                REAL_TaskListButtons[i].label.append("...");
            }
            REAL_TaskListButtons[i].isVisible = true;
            REAL_TaskListButtons[i].tasklisticon = icontextures[i];
        }
    }
}

int MAXNUMBAH = REAL_TaskListButtons.size();

void resetTaskListButtonIcons() {
    programs = getWindowIDs();
    for (int i = 0; i < programs.size(); i++) {
        std::string targetUrl = icontexturepaths[i];
        REAL_TaskListButtons[i].isVisible = true;
        if (targetUrl != REAL_TaskListButtons[i].currentUrl) {
            std::cout << "index: " << i << std::endl;
            if (REAL_TaskListButtons[i].tasklisticon.id != 0) {
                UnloadTexture(REAL_TaskListButtons[i].tasklisticon);
            }
            REAL_TaskListButtons[i].tasklisticon = LoadTexture(icontexturepaths[i].c_str());
            REAL_TaskListButtons[i].currentUrl = targetUrl;

            if (REAL_TaskListButtons[i].texture.id == 0) {
                TraceLog(LOG_WARNING, "Failed to load texture: %s", targetUrl.c_str());
            } else {
                TraceLog(LOG_INFO, "Updated button %d texture to: %s", i, targetUrl.c_str());
            }
        }
    }
}

void updateTaskList() {
    while (true) {
        resetTaskList();
    }
}

void drawTaskList() {
    for (const auto &btn: REAL_TaskListButtons) {
        if (btn.isVisible == true) {
            DrawTextureRec(btn.texture, btn.sourceRec, (Vector2){btn.bounds.x, btn.bounds.y}, WHITE);
            //  DrawText(btn.label.c_str(), btn.pos.x + btn.labelHorizontalPaddingX, btn.pos.y + btn.labelVerticalPaddingY, btn.fontSize,WHITE);
            DrawTextEx(font1, btn.label.c_str(), {
                           btn.pos.x + btn.labelHorizontalPaddingX, btn.pos.y + btn.labelVerticalPaddingY - 6
                       }, 26, 0, WHITE);
            DrawTexture(btn.tasklisticon, btn.pos.x + 4, btn.pos.y + 4,WHITE);
        }
    }
}

void updateTaskListButtons(std::array<Button, 10> &btn) {
    Vector2 mousePoint = GetMousePosition();
    // loop trough buttons to check for mouse interactions
    for (int i = 0; i < btn.size(); i++) {
        btn[i].action = false;
        if (btn[i].windowID == getFocusedWindowID()) {
            btn[i].texture = inuseButtonTexture;
        } else {
            btn[i].texture = buttonTexture;
        }
        // Check button state for each button
        if (CheckCollisionPointRec(mousePoint, btn[i].bounds)) {
            taskListHoverListCoordinates = {btn[i].pos.x, btn[i].pos.y - 10, 160, 80};
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btn[i].state = 2;
            } else {
                btn[i].state = 1;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btn[i].action = true;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                std::cout << "Opening taskbar menu!" << std::endl;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
                std::cout << "Closing window!" << std::endl;
                closeWindow(btn[i].windowID);
            }
        } else {
            btn[i].state = 0;
        }

        // Handle button actions
        if (btn[i].action) {
            if (btn[i].windowID == "EMPTY") {
                // NOTE: These buttons are invisible to the user and exist solely to be replaced with real tasklist information
                std::cout << "You clicked a empty taskbar button!" << std::endl;
                std::cout << "Window ID: " << btn[i].windowID << std::endl;
            } else {
                // Check if the button ID is the same ID as the focused window ID and minimize window if it is and do the reverse if the IDs are different
                if (btn[i].windowID == getFocusedWindowID()) {
                    std::cout << "Minimizing the window with ID: " << btn[i].label << " (" << btn[i].windowID << ")" <<
                            std::endl;
                    minimizeWindow(btn[i].windowID);
                } else {
                    std::cout << "Unminimizing window: " << btn[i].label << " (" << btn[i].windowID << ")" << std::endl;
                    unMinimizeWindow(btn[i].windowID);
                }
            }
        }

        // Update the source rectangle Y position based on state (this is related to changing button texture depending if a mouse is hovering over it or if a mouse button click was detected)
        float frameHeight = static_cast<float>(buttonTexture.height) / 3.0f;
        btn[i].sourceRec.y = btn[i].state * frameHeight;
    }
}
