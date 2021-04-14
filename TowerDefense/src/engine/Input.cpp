#include "pch.h"
#include "TowerDefense.h"

float Input::SCALE = 1.0f;
int Input::HEIGHT = 0;
float Input::MOUSEX = 0;
float Input::MOUSEY = 0;
int Input::MOUSESCROLL = 0;
bool Input::MOUSECLICKED = false;

//Sets the scale and sets HEIGHT to the height of the window
//Must be called before use to set HEIGHT, even if scale is left at 1.0f
void Input::SetScale(float scale, GLFWwindow* window)
{ 
    glfwGetWindowSize(window, nullptr, &HEIGHT);
    SCALE = scale;
}

//Scales x and y positions of mouse in window. Values range from 0 to the Width of the window and 0 to HEIGHT respectively
//The bottom left corner is 0,0
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    MOUSEX = (float)(xpos/SCALE);
    MOUSEY = (float)((HEIGHT- ypos)/ SCALE);
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        MOUSECLICKED = true;
    else if (action == GLFW_RELEASE)
        MOUSECLICKED = false;
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MOUSESCROLL = (int)yoffset;
}