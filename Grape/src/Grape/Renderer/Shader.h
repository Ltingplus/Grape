#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Grape
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragSrc);
        ~Shader();

        void Bind() const;
        void unBind() const;

        void UpdateUniformMatrix(const std::string& name, const glm::mat4& mat);

    private:
        uint32_t m_rendererID;
    };
}