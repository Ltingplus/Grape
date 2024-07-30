

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Log.h"

#include "glad/glad.h"

namespace Grape
{

	IApplication* IApplication::s_instance = nullptr;

	IApplication::IApplication()
		: m_window(IWindow::Create())
	{
		GP_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;
		m_window->SetEventCallback(GP_BIND_EVENT_FN(IApplication::OnEvent));
	
		// »æÖÆÈý½ÇÐÎ²âÊÔ
		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	IApplication::~IApplication()
	{
	}

	void IApplication::Run()
	{
		while (m_running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (auto layer : m_layerStack)
				layer->OnUpdate();

			m_window->OnUpdate();
		}
	}

	void IApplication::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GP_BIND_EVENT_FN(IApplication::OnWindowClose));

		//GP_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.IsHandled())
				break;
		}
	}

	void IApplication::PushLayer(ILayer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void IApplication::PushOverlayer(ILayer* layer)
	{
		m_layerStack.PushOverlayer(layer);
		layer->OnAttach();
	}

	bool IApplication::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

}