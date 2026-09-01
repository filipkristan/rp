#ifndef RAYLIB_BUTTON_BUTTON_HH
#define RAYLIB_BUTTON_BUTTON_HH
#include <utility>
#include <vector>
#include <raylib.h>
#include <string>

class Button;
extern std::vector<Button> Buttons;
extern std::vector<Button> StartMenuButton;
extern std::vector<Button> TaskListButtons;
extern std::vector<Button> ClockButton;
extern std::vector<Button> VolumeMixerButton;
extern std::vector<std::string> windowIDsList;

inline Texture placeholderTexture;
inline Texture buttonTexture;
inline Texture emptyTexture;
inline Texture startMenuTexture;
inline Texture faviconIconPlaceholderTexture;
inline Texture clockTexture;
inline Texture inactiveButtonTexture;
inline Texture volumeIconButtonTexture;
inline Texture inuseButtonTexture;
inline Texture tasklisticontexture;

class Button {
public:
    Vector2 pos = {120, 0};
    Rectangle bounds{};
    Rectangle sourceRec{};
    Texture2D texture{};
    int state = 0;
    bool action = false;
    std::string label = "Label";
    float width = 100;
    float height = 40;
    std::string windowID = "0x123456789";
    float labelVerticalPaddingY = 0;
    float labelHorizontalPaddingX = 0;
    float fontSize = 14;
    bool isVisible = false;
    Texture2D tasklisticon = faviconIconPlaceholderTexture;
    std::string currentUrl;

    Button() {
        this->sourceRec = {0, 0, (float) this->width, this->height};
        this->texture = placeholderTexture;
        this->currentUrl = "/tmp/0x05200009_32x32.png";
        this->tasklisticon = faviconIconPlaceholderTexture;
        this->bounds = Rectangle(0, 0, width, height);
        this->labelHorizontalPaddingX = this->width / 2 - MeasureText(this->label.c_str(), this->fontSize) / 2;
        this->labelVerticalPaddingY = 10;
    }

    Button(Vector2 pos) : Button() {
        this->pos = pos;
        this->bounds = Rectangle(pos.x, pos.y, width, height); // set new bounds now that we have set button position
    }

    Button(Vector2 pos, float width, float height, std::string label, std::string windowID) : Button(pos) {
        this->width = width;
        this->height = height;
        this->label = std::move(label);
        this->sourceRec = {0, 0, (float) this->width, this->height};
        this->bounds = Rectangle(pos.x, pos.y, width, height);
        this->windowID = std::move(windowID);
        if (this->windowID != "STARTBUTTON" && this->windowID != "EMPTY" && this->windowID != "CLOCK" && this->windowID
            != "VOLUMEMIXER" && this->windowID != "INTERNETCONNECTIVITY") {
            //this->tasklisticon = tasklisticon = getProgramIconPathFromWindowID(this->windowID);
        } else {
            // this->tasklisticon = tasklisticon = "/tmp/0x0240004c_32x32.png";
        }
    }

    Button(Vector2 pos, float width, float height, std::string label, std::string windowID,
           const Texture &texture) : Button(
        pos, width, height, std::move(label), std::move(windowID)) {
        this->texture = texture;
    }

    Button(Vector2 pos, float width, float height, std::string label, std::string windowID, const Texture &texture,
           float labelHorizontalPaddingX,
           float labelVerticalPaddingY) : Button(
        pos, width, height, std::move(label), std::move(windowID), texture) {
        this->labelHorizontalPaddingX = labelHorizontalPaddingX;
        this->labelVerticalPaddingY = labelVerticalPaddingY;
    }
};

void initButtons();

void updateButtons(std::vector<Button> &btn);

#endif
