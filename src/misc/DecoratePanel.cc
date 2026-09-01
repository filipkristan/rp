#include "DecoratePanel.hh"
#include <raylib.h>

Color mainColor = {42, 46, 50, 255};
// Color secondaryColor = {1, 1, 1,1};
Color secondaryColor = CLITERAL(Color){71, 77, 84, 255};

int monitor = GetCurrentMonitor();

void decoratePanel() {
    ClearBackground(mainColor);
    DrawRectangle(0, 2, GetMonitorWidth(monitor), 2, secondaryColor);
}
