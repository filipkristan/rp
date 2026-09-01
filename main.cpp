
#include "src/ui/InternetConnectivityButton.hh"
#include "src/ui/VolumeMixer.hh"
#include "src/ui/StartMenu.hh"
#include "src/ui/TaskList.hh"
#include "src/ui/Button.hh"
#include "src/ui/Fonts.hh"
#include "src/ui/Clock.hh"
#include "src/misc/DecoratePanel.hh"
#include "src/utils/GetWindowIDs.hh"
#include "src/utils/x11.hh"
#include <GLFW/glfw3.h>
#include <iostream>
#include <raylib.h>
#include <chrono>
#include <thread>

GLFWwindow *window = NULL;
extern std::string icontexturepaths[];

// Sets the default icons
void setIconTextures() {
    for (int i = 0; i < 10; i++) {
        icontextures[i] = LoadTexture(icontexturepaths[i].c_str());
        if (icontextures[i].id == 0) {
            TraceLog(LOG_ERROR, "Failed to load texture %s");
        }
    }
}

std::thread updateWindowIDsList() {
    windowIDsList = getWindowIDs(); // NOTE: delete
}

int main() {
    // NOTE: Make window transparent and clickable, look what is set when user hovers a button
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
    InitWindow(800, PANEL_HEIGHT, "x11-panel-0x123456789");
    
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor);
    int monitorHeight = GetMonitorHeight(monitor);

    SetWindowSize(monitorWidth, PANEL_HEIGHT);
    SetWindowPosition(0, monitorHeight);

    window = glfwGetCurrentContext();
    enableX11WindowSettings();
    windowIDsList = getWindowIDs(); // NOTE: delete

    // button & font stuff
    initButtons();
    initFonts();

    // SET BUTTONS (Runs once at startup)
    setStartMenu();
    setTaskList();
    setClock();
    setVolumeMixer();
    setInternetConnectivityButton();
    setIconTextures();

    SetTargetFPS(60);

    // Threads
    std::thread clockWorker(updateClock);
    clockWorker.detach();
    std::thread taskListWorker(updateTaskList);
    taskListWorker.detach();

    while (!WindowShouldClose()) {
        decoratePanel();
        updateIconPaths();
        updateButtons(ClockButton);
        updateButtons(VolumeMixerButton);
        updateButtons(StartMenuButton);
        updateButtons(InternetConnectivityButton);
        updateTaskListButtons(REAL_TaskListButtons);
        resetTaskListButtonIcons();

        BeginDrawing();
        drawTaskList();
        drawStartMenu();
        drawClock();
        drawInternetConnectivityButton();
        EndDrawing();
    }

    UnloadTexture(emptyTexture);
    UnloadTexture(buttonTexture);
    UnloadTexture(placeholderTexture);
    for (int i = 0; i < 10; ++i) {
        // NOTE: change to number of buttons
        UnloadTexture(icontextures[i]);
    }
    CloseWindow();
    return 0;
}
