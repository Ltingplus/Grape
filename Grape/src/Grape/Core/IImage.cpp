
#include "gppch.h"
#include "IImage.h"
#include "Grape/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLImage.h"

namespace Grape
{

    Ref<IImage> IImage::Create(uint32_t width, uint32_t height, ImageFormat format, const void* data /*= nullptr*/)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::Api::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::Api::OpenGL:  return std::make_shared<OpenGLImage>(width, height, format, data);
        }

        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}