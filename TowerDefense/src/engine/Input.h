#pragma once

class Input
{
public:
    Input() = delete;

    //standard callback functions from GLFW. Callbacks set in TowerDefense Init function
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    //Sets the scale and sets HEIGHT to the height of the window
    //Must be called before use to set HEIGHT, even if scale is left at 1.0f
    static void SetScale(float scale, GLFWwindow* window);

    //Returns x and y positions of mouse in window. Values range from 0 to WIDTH and 0 to HEIGHT respectively
    //The bottom left corner is 0,0
    inline static float GetMouseX() { return MOUSEX; }
    inline static float GetMouseY() { return MOUSEY; }

    //Returns 1 for scroll up, -1 for scroll down, 0 otherwise
    inline static int GetMouseSCROLL() { int returner = MOUSESCROLL; MOUSESCROLL = 0; return returner; }

    inline static bool GetMouseClicked() { return MOUSECLICKED; }
    inline static bool GetMouseClickedAndSetFalse() { if (MOUSECLICKED) { MOUSECLICKED = false; return true; } else return false; }

private:
    static float SCALE, MOUSEX, MOUSEY;
    static int HEIGHT, MOUSESCROLL;
    static bool MOUSECLICKED;
};