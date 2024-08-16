#include "gppch.h"

#include "IShader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Grape
{

    Ref<IShader> IShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::Api::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::Api::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IShader> IShader::Create(const std::string& filePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::Api::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::Api::OpenGL:  return std::make_shared<OpenGLShader>(filePath);
        }

        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<IShader>& shader)
    {
        GP_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<IShader>& shader)
    {
        Add(shader->GetName(), shader);
    }

    Ref<IShader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<IShader> ShaderLibrary::Load(const std::string&  name, const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Grape::Ref<Grape::IShader> ShaderLibrary::Get(const std::string& name)
    {
        GP_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_shaders.find(name) != m_shaders.end();
    }
}
