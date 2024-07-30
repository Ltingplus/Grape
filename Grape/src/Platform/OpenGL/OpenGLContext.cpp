#include "gppch.h"
#include "OpenGLContext.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Grape
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		GP_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GP_CORE_ASSERT(status, "Failed to initialize Glad!");

	}


	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}
