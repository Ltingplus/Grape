#pragma once

namespace Grape
{
	enum class RendererApi
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static RendererApi GetAPI()
		{
			return s_rendererAPI;
		}

	private:
		static RendererApi s_rendererAPI;
	};
}