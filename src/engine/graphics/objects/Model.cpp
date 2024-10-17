#include "engine/graphics/rendering/Shader.hpp"
#include <engine/graphics/objects/Model.hpp>

engine::Model::Model() {}

void engine::Model::render(engine::Shader shader)
{
    m_Mesh->render(shader, m_instances);
}

void engine::Model::addInstance(Instance info)
{
    m_instances.push_back(info);
}

void engine::Model::setMesh(std::unique_ptr<Mesh> m)
{
    m_Mesh = std::move(m);
}

void engine::Model::cleanup()
{
    m_Mesh->cleanup();
}
