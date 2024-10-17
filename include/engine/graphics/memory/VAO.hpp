#ifndef CLASS_ARRAY_BUFFER
#define CLASS_ARRAY_BUFFER

#include "glad/glad.h"
#include <map>
#include <string>
#include <vector>
namespace engine
{
    class ArrayBuffer 
    {
    public:
        unsigned int ID;

        /*
         * CONSTRUCTORS
         */
        ArrayBuffer(GLenum targetBuffer = GL_ARRAY_BUFFER): m_targetBuffer(targetBuffer) {}
        ~ArrayBuffer() { cleanup(); }

        /*
         * HELPERS
         */
        void gen()
        {
            glGenBuffers(1, &ID);
        }

        void bind()
        {
            glBindBuffer(m_targetBuffer, ID);
        }

        void unbind()
        {
            glBindBuffer(m_targetBuffer, 0);
        }

        template<typename T>
        void setBufferData(const std::vector<T>& c_data, GLenum usage)
        {
            glBufferData(m_targetBuffer, c_data.size() * sizeof(T), c_data.data(), usage);
        }

        template<typename T> 
        void setAttribPtr(
            unsigned int idx,
            unsigned int size,
            unsigned int stride,
            unsigned int offset,
            GLenum type = GL_FLOAT
        )
        {
            glVertexAttribPointer(idx, size, type, GL_FALSE, stride * sizeof(T), (void*)(offset * sizeof(T)));
            glEnableVertexAttribArray(idx);
        }

        void cleanup()
        {
            glDeleteBuffers(1, &ID);
        } 


    private:
        GLenum m_targetBuffer;
    };

    class VAO 
    {
    public:
        std::map<std::string, ArrayBuffer> buffers;

        ArrayBuffer& operator[](std::string key) { return buffers[key]; }

        VAO() = default;

        void gen()
        {
            glGenVertexArrays(1, &ID);
        }

        void bind()
        {
            glBindVertexArray(ID);
        }

        void unbind()
        {
            glBindVertexArray(0);
        }

        void draw(GLenum mode, unsigned int size, GLenum type, unsigned int offset)
        {
            glDrawElementsInstanced(mode, size, type, (void*)offset, 1);
        }

        void drawArrays(GLenum mode, unsigned int first, unsigned int count)
        {
            glDrawArrays(mode, first, count);
        }

        void cleanup()
        {
            glDeleteVertexArrays(1, &ID);
        }
    private:
        unsigned int ID;
    };
};

#endif // !CLASS_ARRAY_BUFFER
