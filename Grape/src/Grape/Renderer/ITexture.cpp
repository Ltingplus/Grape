#include "gppch.h"
#include "ITexture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"

namespace Grape
{

    Ref<ITexture2D> ITexture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::Api::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::Api::OpenGL:  return std::make_shared<OpenGLTexture>(path);
        }

        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}