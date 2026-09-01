#ifndef PANEL_TASKLIST_HH
#define PANEL_TASKLIST_HH
#include <array>
#include "Button.hh"

inline std::array<Button, 10> REAL_TaskListButtons;
inline Rectangle taskListHoverListCoordinates;
inline Image textureimage;
inline Texture2D icontextures[10] = {0};
inline std::vector<std::string> programs;

void resetTaskListButtonIcons();

void updateIconPaths();

void setTaskList();

void updateTaskListButtons(std::array<Button, 10> &btn);

void updateTaskList();

void drawTaskList();

#endif
