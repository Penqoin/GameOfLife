#ifndef CLASS_MOUSE_HPP
#define CLASS_MOUSE_HPP

#include "GLFW/glfw3.h"

namespace engine 
{
    class Mouse 
    {
    public:
        /*
         * CALLBACKS
         */
        static void cursorPosCallback(GLFWwindow* window, double dx, double dy);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
        static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);

        /*
         * accessors
         */

        static double getMouseX();
        static double getMouseY();

        static double getDx();
        static double getDy();

        static double getScrollDx();
        static double getScrollDy();

        static bool button(int button);
        static bool buttonChange(int button);
        static bool buttonWentUp(int button);
        static bool buttonWentDown(int button);

    private:
        static double x;
        static double y;

        static double lastX;
        static double lastY;

        static bool firstMouse;

        static double dx;
        static double dy;

        static double scrollDx;
        static double scrollDy;

        static bool buttons[];
        static bool buttonsChanged[];
    };   
};

#endif // !CLASS_MOUSE_HPP
