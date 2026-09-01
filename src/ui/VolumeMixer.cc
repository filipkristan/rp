#include "../ui/VolumeMixer.hh"
#include "Button.hh"

void setVolumeMixer() {
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor);
    float volumeMixerX = monitorWidth - 146;
    VolumeMixerButton.insert(VolumeMixerButton.end(), {
                                 Button({volumeMixerX, 6}, 40, 40, "", "VOLUMEMIXER", volumeIconButtonTexture)
                             });
}

void drawVolumeMixer() {
    for (const auto &btn: StartMenuButton) {
        DrawTextureRec(btn.texture, btn.sourceRec, (Vector2){btn.bounds.x, btn.bounds.y}, WHITE);
        DrawText(btn.label.c_str(), btn.pos.x + btn.labelHorizontalPaddingX - 32, btn.pos.y + btn.labelVerticalPaddingY,
                 btn.fontSize,WHITE);
    }
}
