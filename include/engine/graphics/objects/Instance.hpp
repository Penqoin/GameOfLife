#ifndef STRUCT_INSTANCES_HPP
#define STRUCT_INSTANCES_HPP

#include "engine/graphics/rendering/Texture.hpp"
#include "glm/glm.hpp"
#include <cstdlib>
#include <ctime>

struct Instance 
    {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec4 color;

        engine::Texture texture;

        Instance(
            const glm::vec2& pos,
            const glm::vec3& rot,
            const glm::vec3& scl,
            engine::Texture text
        ) : scale(scl), rotation(rot), texture(text)
        {
            position.x = pos.x;
            position.y = pos.y;
            position.z = -3.f;
            
            color = glm::vec4(1.f);
            texture.load();
        }
    };

#endif // !STRUCT_INSTANCES_HPP
