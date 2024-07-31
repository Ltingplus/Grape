
#include "gppch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLBuffer.h"

namespace Grape
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererApi::None:
        {
            GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }
        case RendererApi::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        default:
            break;
        }
        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Grape::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererApi::None:
        {
            GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }
        case RendererApi::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        default:
            break;
        }
        GP_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}

