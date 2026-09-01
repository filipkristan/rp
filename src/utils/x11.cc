#include "x11.hh"
#define GLFW_INCLUDE_X11
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <cstdio>

extern GLFWwindow *window;

void enableX11WindowSettings() {
    Display *dpy = glfwGetX11Display();
    Window win = glfwGetX11Window(window);

    if (!dpy || !win) {
        fprintf(stderr, "Failed to retrieve X11 display or window from GLFW\n");
        return;
    }

    int screen = DefaultScreen(dpy);
    int width = DisplayWidth(dpy, screen);

    // Set window properties so it behaves like a dock/panel. It reserves space at the bottom and some other stuff
    Atom wmType = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
    Atom wmTypeDock = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(dpy, win, wmType, XA_ATOM, 32, PropModeReplace,
                    reinterpret_cast<unsigned char *>(&wmTypeDock), 1);

    Atom wmState = XInternAtom(dpy, "_NET_WM_STATE", False);
    Atom wmStateAbove = XInternAtom(dpy, "_NET_WM_STATE_ABOVE", False);
    Atom wmStateSticky = XInternAtom(dpy, "_NET_WM_STATE_STICKY", False);
    Atom states[2] = {wmStateAbove, wmStateSticky};
    XChangeProperty(dpy, win, wmState, XA_ATOM, 32, PropModeReplace,
                    reinterpret_cast<unsigned char *>(states), 2);

    unsigned long strut[12] = {0};
    strut[3] = PANEL_HEIGHT;
    strut[10] = 0;
    strut[11] = width;

    Atom strutPartial = XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False);
    Atom cardinal = XInternAtom(dpy, "CARDINAL", False);
    XChangeProperty(dpy, win, strutPartial, cardinal, 32, PropModeReplace,
                    reinterpret_cast<unsigned char *>(strut), 12);

    Atom strutSimple = XInternAtom(dpy, "_NET_WM_STRUT", False);
    unsigned long strutSimpleData[4] = {0, 0, 0, PANEL_HEIGHT};
    XChangeProperty(dpy, win, strutSimple, cardinal, 32, PropModeReplace,
                    reinterpret_cast<unsigned char *>(strutSimpleData), 4);

    XFlush(dpy);
}
