#pragma once

#include <string>

namespace Grape
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragSrc);
        ~Shader();

        void Bind() const;
        void unBind() const;

    private:
        uint32_t m_rendererID;
    };
}