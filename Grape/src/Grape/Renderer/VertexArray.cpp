#include "gppch.h"
#include "VertexArray.h"
#include "Grape/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


Grape::VertexArray* Grape::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererApi::None: GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case  RendererApi::OpenGL: return new OpenGLVertexArray();
	default:
		break;
	}
	GP_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
