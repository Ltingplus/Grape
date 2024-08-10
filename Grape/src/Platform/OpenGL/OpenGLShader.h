#pragma once
#include "Grape/Renderer/IShader.h"

#include <string>
#include "glm/glm.hpp"

namespace Grape
{
    class OpenGLShader : public IShader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc);
        virtual ~OpenGLShader();

        void Bind() const override;
        void unBind() const override;

        void UploadUniformInt(const std::string& name, const int& value);

        void UploadUniformFloat(const std::string& name, const float& value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UpdateUniformMatrix3(const std::string& name, const glm::mat3& mat);
        void UpdateUniformMatrix4(const std::string& name, const glm::mat4& mat);

    private:
        uint32_t m_rendererID;
    };
}

