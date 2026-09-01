#ifndef PANEL_INTERNET_CONNECTIVITY_BUTTON_HH
#define PANEL_INTERNET_CONNECTIVITY_BUTTON_HH
#include "Button.hh"

extern std::vector<Button> InternetConnectivityButton;

void setInternetConnectivityButton();

void drawInternetConnectivityButton();

inline Texture ethernetButtonTexture;

#endif
