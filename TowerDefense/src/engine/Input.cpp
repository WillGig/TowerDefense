#include "pch.h"
#include "TowerDefense.h"

float Input::SCALE = 1.0f;
float Input::XOFF = 0.0f;
float Input::YOFF = 0.0f;
int Input::HEIGHT = 0;
int Input::WIDTH = 0;
int Input::MAXHEIGHT = 0;
float Input::MOUSEX = 0.0f;
float Input::MOUSEY = 0.0f;
int Input::MOUSESCROLL = 0;
bool Input::LEFTMOUSECLICKED = false;
bool Input::RIGHTMOUSECLICKED = false;
bool Input::KEYS[65536];

//Sets the scale and sets HEIGHT to the height of the window
//Must be called before use to set HEIGHT, even if scale is left at 1.0f
//XOffset and YOffset represent the blank side bars on either side of the screen if the aspect ratio is not 4:3
void Input::SetScale(float scale, float hOffSet, float vOffSet, int maxHeight, GLFWwindow* window)
{ 
    glfwGetWindowSize(window, &WIDTH, &HEIGHT);
    XOFF = hOffSet;
    YOFF = vOffSet;
    SCALE = scale;
    MAXHEIGHT = maxHeight;
}

//Scales x and y positions of mouse in window. Values range from 0 to 800 and 0 to 600 respectively if the 
// mouse is in the game portion of the window. The bottom left corner of the game (not the window) is 0,0
//XOffset and YOffset represent the blank side bars on either side of the screen if the aspect ratio is not 4:3
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
        MOUSEX = (float)(xpos / SCALE - XOFF);
        MOUSEY = (float)(MAXHEIGHT - (ypos/SCALE - YOFF));
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            LEFTMOUSECLICKED = true;
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
            RIGHTMOUSECLICKED = true;
    } 
    else if (action == GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            LEFTMOUSECLICKED = false;
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            RIGHTMOUSECLICKED = false;
    }
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MOUSESCROLL = (int)yoffset;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key > 0 && key < 65536)
        KEYS[key] = action != GLFW_RELEASE;
}

void Input::window_size_callback(GLFWwindow* window, int width, int height)
{
     //Setting Renderer Projection Matrix to game dimensions
    float scale;
    float hOffSet = 0.0f;
    float vOffSet = 0.0f;

    if ((float)height / 600.0f > (float)width / 800.0f)
    {
        scale = ((float)width / 800.0f);
        vOffSet = (height - 600.0f * scale) / (2 * scale);
    }
    else
    {
        scale = ((float)height / 600.0f);
        hOffSet = (width - 800.0f * scale) / (2 * scale);
    }

    glViewport(0, 0, width, height);
    Renderer::Get().SetProjectionMatrix(-hOffSet, 800.0f + hOffSet, -vOffSet, 600.0f + vOffSet, -1.0f, 1.0f);

    //Set Mouse Input dimensions
    Input::SetScale(scale, hOffSet, vOffSet, 600, window);
}