#ifndef CLASS_ENVIRONMENT_HPP
#define CLASS_ENVIRONMENT_HPP

// external
#include <glm/glm.hpp>

/*
    Environment class
    - stores values for environment (constants, etc)

    1 cubic unit in OpenGL space is equivalent to 1 meter cubed
*/

namespace engine 
{
    class Environment {
    public:
        static glm::vec3 worldUp;						// up vector in world
        static glm::vec3 gravitationalAcceleration;		// acceleration due to gravity
    };
};


#endif
