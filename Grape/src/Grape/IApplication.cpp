

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

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };
		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// shader
		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_position;
			out vec3 v_position;

			void main()
			{
				v_position = a_position;
				gl_Position = vec4(a_position, 1.0);
			}
		)";
		std::string fagSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_position;

			void main()
			{
				color = vec4(v_position * 0.5 + 0.5, 1.0);
			}
		)";
		m_shader.reset(new Shader(vertexSrc, fagSrc));
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

			m_shader->Bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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