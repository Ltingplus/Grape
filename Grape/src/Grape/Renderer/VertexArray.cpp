#include "gppch.h"
#include "VertexArray.h"
#include "Grape/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


Grape::Ref<Grape::VertexArray> Grape::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::Api::None: GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case  RendererAPI::Api::OpenGL: return std::make_shared<OpenGLVertexArray>();
	default:
		break;
	}
	GP_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
