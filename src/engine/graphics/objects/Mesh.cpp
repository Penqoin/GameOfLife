#include "engine/graphics/objects/Mesh.hpp"
#include "glm/ext/matrix_transform.hpp"

std::vector<engine::Vertex> engine::Vertex::genVertices(float* vertices, unsigned int n_vertices, unsigned int stride)
{
    std::vector<engine::Vertex> verts(n_vertices);

    for (int i = 0; i < n_vertices; i++)
    {
        verts[i].pos = glm::vec2(vertices[i * stride], vertices[i * stride + 1]);
        verts[i].texCoord = glm::vec2(vertices[i * stride + 2], vertices[i * stride + 3]);
    }

    return verts;
}

engine::Mesh::Mesh() {}

engine::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    loadData(vertices, indices);
}

void engine::Mesh::render(Shader shader, std::vector<Instance>& instances)
{
    
    shader.activate();
    for (Instance& inst : instances)
    {
        glm::mat4 model(1.f);
        model = glm::translate(model, inst.position);
        model = glm::scale(model, inst.scale);

        glActiveTexture(GL_TEXTURE0);
        inst.texture.bind();

        shader.setMat4("model", model);
        shader.setFloat4("color", inst.color);

        

        vao.bind();
        vao.draw(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        vao.unbind();
    }
}


void engine::Mesh::loadData(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
{
    this->vertices = _vertices;
    this->indices = _indices;

    vao.gen();
    vao.bind();

    vao["EBO"] = ArrayBuffer(GL_ELEMENT_ARRAY_BUFFER);
    vao["EBO"].gen();
    vao["EBO"].bind();
    vao["EBO"].setBufferData(indices, GL_STATIC_DRAW);

    vao["VBO"] = ArrayBuffer();
    vao["VBO"].gen();
    vao["VBO"].bind();
    vao["VBO"].setBufferData(vertices, GL_STATIC_DRAW);
    vao["VBO"].setAttribPtr<float>(0, 2, 4, 0);

    // texture ptr
    vao["VBO"].setAttribPtr<float>(1, 2, 4, 2);

    vao["VBO"].unbind();
    vao.unbind();
}

void engine::Mesh::cleanup()
{
    vao.cleanup();
}
