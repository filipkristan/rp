cmake_minimum_required(VERSION 3.28)
project(panel)

set(CMAKE_CXX_STANDARD 20)

add_executable(panel
        main.cpp
        src/ui/Button.cc
        src/utils/x11.cc
        src/utils/GetWindowIDs.cc
        src/utils/GetWindowTitle.cc
        src/utils/MinimizeWindow.cc
        src/utils/UnMinimizeWindow.cc
        src/ui/Clock.cc
        src/misc/ExportCommandOutputToArray.cc
        src/misc/ExportCommandOutputToArray.hh
        src/utils/GetFocusedWindowID.cc
        src/utils/GetFocusedWindowID.hh
        src/ui/StartMenu.cc
        src/ui/StartMenu.hh
        src/ui/TaskList.cc
        src/ui/TaskList.hh
        src/utils/CheckIfWindowIsActive.cc
        src/utils/CheckIfWindowIsActive.hh
        src/utils/CloseWindow.cc
        src/utils/CloseWindow.hh
        src/ui/VolumeMixer.cc
        src/ui/VolumeMixer.hh
        src/ui/InternetConnectivityButton.cc
        src/ui/InternetConnectivityButton.hh
        src/misc/DecoratePanel.cc
        src/misc/DecoratePanel.hh
        src/misc/GetProgramIconPathFromWindowID.cc
        src/misc/GetProgramIconPathFromWindowID.hh
        src/ui/Fonts.cc
        src/ui/Fonts.hh
)

target_include_directories(panel PRIVATE /usr/local/include)
target_link_directories(panel PRIVATE /usr/local/lib)
target_link_libraries(panel PRIVATE raylib -lX11)
