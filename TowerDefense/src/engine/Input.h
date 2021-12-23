#pragma once

class Input
{
public:
    Input() = delete;

    //standard callback functions from GLFW. Callbacks set in TowerDefense Init function
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_size_callback(GLFWwindow* window, int width, int height);

    //Sets the scale and sets the dimesions of the window
    //Also sets the offsets horizontal or vertical offsets if the aspect ratio is not 4:3
    //Must be called before use to set HEIGHT and WIDTH
    //maxHeight is the maximum height of the orthographic projection and is used for inverting the y coordinate of the mouse
    static void SetScale(float scale, float hOffSet, float vOffSet, int maxHeight, GLFWwindow* window);

    //Returns x and y positions of mouse in window. Values range from 0 to WIDTH and 0 to HEIGHT respectively
    //The bottom left corner is 0,0
    inline static float GetMouseX() { return MOUSEX; }
    inline static float GetMouseY() { return MOUSEY; }

    //Returns 1 for scroll up, -1 for scroll down, 0 otherwise
    inline static int GetMouseSCROLL() { int returner = MOUSESCROLL; MOUSESCROLL = 0; return returner; }

    inline static bool GetLeftMouseClicked() { return LEFTMOUSECLICKED; }
    inline static bool GetLeftMouseClickedAndSetFalse() { if (LEFTMOUSECLICKED) { LEFTMOUSECLICKED = false; return true; } return false; }
    inline static bool GetRightMouseClicked() { return RIGHTMOUSECLICKED; }
    inline static bool GetRightMouseClickedAndSetFalse() { if (RIGHTMOUSECLICKED) { RIGHTMOUSECLICKED = false; return true; } return false; }

    inline static bool GetKeyPressed(int key) { return KEYS[key]; }
    inline static bool GetKeyPressedAndSetFalse(int key) { if (KEYS[key]) { KEYS[key] = false; return true; } return false; }

private:
    static float SCALE, MOUSEX, MOUSEY, XOFF, YOFF;
    static int HEIGHT, WIDTH, MOUSESCROLL, MAXHEIGHT;
    static bool LEFTMOUSECLICKED, RIGHTMOUSECLICKED;
    static bool KEYS[];
};