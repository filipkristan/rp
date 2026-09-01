#include "Fonts.hh"
#include <raylib.h>

void initFonts() {
    //font1 = LoadFont("../res/dejavu.fnt");
    font1 = LoadFontEx("../res/NotoSansTC-Regular.ttf", 26, 0, 250);
    font2 = LoadFontEx("../res/NotoSansTC-Regular.ttf", 28, 0, 250);
}
