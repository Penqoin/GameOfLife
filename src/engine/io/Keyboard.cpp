#include "engine/io/Keyboard.hpp"

/*
    define initial static values
*/

// key state array (true for down, false for up)
bool engine::Keyboard::keys[GLFW_KEY_LAST] = { 0 };
// key changed array (true if changed)
bool engine::Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };

/*
    static callback
*/

// key state changed
void engine::Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!keys[key])
            keys[key] = true;
    }
    else
    {
        keys[key] = false;
    }
    keysChanged[key] = action != GLFW_REPEAT;
}

/*
    static accessors
*/

bool engine::Keyboard::key(int key) { return keys[key]; }

// get if key recently changed
bool engine::Keyboard::keyChanged(int key)
{
    bool ret = keysChanged[key];
    // set to false because change no longer new
    keysChanged[key] = false;
    return ret;
}

// get if key recently changed and is up
bool engine::Keyboard::keyWentDown(int key) { return keys[key] && keyChanged(key); }

// get if key recently changed and is down
bool engine::Keyboard::keyWentUp(int key) { return !keys[key] && keyChanged(key); }
