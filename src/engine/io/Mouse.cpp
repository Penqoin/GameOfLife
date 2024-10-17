#include "engine/io/Mouse.hpp"

double engine::Mouse::x = 0;
double engine::Mouse::y = 0;

double engine::Mouse::lastX = 0;
double engine::Mouse::lastY = 0;

bool engine::Mouse::firstMouse = true; 

double engine::Mouse::dx = 0;
double engine::Mouse::dy = 0;

double engine::Mouse::scrollDx = 0;
double engine::Mouse::scrollDy = 0;

bool engine::Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool engine::Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void engine::Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y)
{
    x = _x;
    y = _y;

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    dx = x - lastX;
    dy = y - lastY;

    lastX = x;
    lastY = y;
}

void engine::Mouse::mouseButtonCallback(GLFWwindow *window, int button, int action, int mode)
{
    if (action != GLFW_RELEASE)
    {
        if (!buttons[button])
            buttons[button] = true;
    }
    else 
    {
        buttons[button] = false;
    }
    buttonsChanged[button] = action != GLFW_RELEASE;
}

void engine::Mouse::mouseWheelCallback(GLFWwindow *window, double dx, double dy)
{
    scrollDx = dx;
    scrollDy = dy;
}

double engine::Mouse::getMouseX() { return x; }
double engine::Mouse::getMouseY() { return y; }

double engine::Mouse::getDx()
{
    double _t = dx;
    dx = 0;
    return _t;
}

double engine::Mouse::getDy()
{
    double _t = dy;
    dy = 0;
    return _t;
}

double engine::Mouse::getScrollDx()
{
    double _t = scrollDx;
    scrollDx = 0;
    return _t;
}

double engine::Mouse::getScrollDy() 
{
    double _t = scrollDy;
    scrollDy = 0;
    return _t;
}

bool engine::Mouse::button(int button)
{
    return buttons[button];
}

bool engine::Mouse::buttonChange(int button)
{
    bool ans = buttonsChanged[button];
    buttonsChanged[button] = false;
    return ans;
}

bool engine::Mouse::buttonWentUp(int button)
{
    return !buttons[button] && buttonChange(button);
}

bool engine::Mouse::buttonWentDown(int button)
{
    return buttons[button] && buttonChange(button);
}
