#include "gppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Grape
{
    RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}