#include "../ui/InternetConnectivityButton.hh"
#include "Button.hh"

std::vector<Button> InternetConnectivityButton;

void setInternetConnectivityButton() {
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor);
    float InternetConnectivityButtonX = monitorWidth - 189;
    InternetConnectivityButton.insert(InternetConnectivityButton.end(), {
                                          Button({InternetConnectivityButtonX, 6}, 40, 40, "",
                                                 "INTERNETCONNECTIVITY", ethernetButtonTexture)
                                      });
}

void drawInternetConnectivityButton() {
    for (const auto &btn: InternetConnectivityButton) {
        DrawTextureRec(btn.texture, btn.sourceRec, (Vector2){btn.bounds.x, btn.bounds.y}, WHITE);
        DrawText(btn.label.c_str(), btn.pos.x + btn.labelHorizontalPaddingX, btn.pos.y + btn.labelVerticalPaddingY,
                 btn.fontSize,WHITE);
    }
}
