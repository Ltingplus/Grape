#include "gppch.h"

#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Grape
{

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::Api::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::Api::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
