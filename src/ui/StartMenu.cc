#include "../ui/StartMenu.hh"
#include "Button.hh"

void setStartMenu() {
    VolumeMixerButton.insert(VolumeMixerButton.end(), {
                                 Button({5, 6}, 40, 40, "", "STARTBUTTON", startMenuTexture)
                             });
}

void drawStartMenu() {
    for (const auto &btn: VolumeMixerButton) {
        DrawTextureRec(btn.texture, btn.sourceRec, (Vector2){btn.bounds.x, btn.bounds.y}, WHITE);
        DrawText(btn.label.c_str(), btn.pos.x + btn.labelHorizontalPaddingX, btn.pos.y + btn.labelVerticalPaddingY,
                 btn.fontSize,WHITE);
    }
}
