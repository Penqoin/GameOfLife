#ifndef CLASS_MESH_HPP
#define CLASS_MESH_HPP

#include "engine/graphics/memory/VAO.hpp"
#include "engine/graphics/rendering/Shader.hpp"
#include "Instance.hpp"

#include "glm/glm.hpp"
#include <vector>

namespace engine 
{
    struct Vertex 
    {
        glm::vec2 pos;
        glm::vec2 texCoord;

        static std::vector<Vertex> genVertices(float* vertices, unsigned int n_vertices, unsigned int stride = 2);
    };

    class Mesh 
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        VAO vao;

        Mesh();
        Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& indices);

        void render(Shader shader, std::vector<Instance>& instances);

        void loadData(std::vector<Vertex>& _verts, std::vector<unsigned int>& _inds);

        void cleanup();

    private:
        void setup();

    };
};


#endif // !CLASS_MESH_HPP
