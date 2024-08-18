#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Grape
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

        static Ref<IShader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        static Ref<IShader> Create(const std::string& filePath);

        virtual const std::string& GetName() const = 0;
        virtual void Bind() const = 0;
        virtual void unBind() const = 0;

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    };


    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<IShader>& shader);
        void Add(const Ref<IShader>& shader);

        Ref<IShader> Load(const std::string& filepath);
        Ref<IShader> Load(const std::string& name, const std::string& filepath);

        Ref<IShader> Get(const std::string& name);

        bool Exists(const std::string& name) const;

    private:
        std::unordered_map<std::string, Ref<IShader>> m_shaders;
    };
}