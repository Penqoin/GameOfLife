#ifndef CLASS_MODEL_HPP
#define CLASS_MODEL_HPP

#include "engine/graphics/objects/Mesh.hpp"
#include "Instance.hpp"

#include <memory>
#include <vector>

namespace engine 
{
    class Model 
    {
    public:
        Model();

        virtual void init() {};
        virtual void render(Shader shader);

        void setMesh(std::unique_ptr<Mesh> m);
        void addInstance(Instance info);

        void cleanup();
    protected:
        std::vector<Instance> m_instances;
        std::unique_ptr<Mesh> m_Mesh;
    };
};
#endif // !CLASS_MODEL_HPP
