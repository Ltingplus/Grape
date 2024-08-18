#pragma once
#include "Grape/Renderer/IShader.h"

#include <string>
#include "glm/glm.hpp"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Grape
{
    class OpenGLShader : public IShader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc);
        OpenGLShader(const std::string& filePath);
        virtual ~OpenGLShader();

        const std::string& GetName() const override { return m_name; }
        void Bind() const override;
        void unBind() const override;

        void SetInt(const std::string& name, int value) override;
        void SetFloat(const std::string& name, float value) override;
        void SetFloat3(const std::string& name, const glm::vec3& value) override;
        void SetFloat4(const std::string& name, const glm::vec4& value) override;
        void SetMat4(const std::string& name, const glm::mat4& value) override;

        void UploadUniformInt(const std::string& name, const int& value);

        void UploadUniformFloat(const std::string& name, const float& value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMatrix3(const std::string& name, const glm::mat3& mat);
        void UploadUniformMatrix4(const std::string& name, const glm::mat4& mat);

    private:
        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

    private:
        uint32_t m_rendererID;
        std::string m_name;
    };
}

