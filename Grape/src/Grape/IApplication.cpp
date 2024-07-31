

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Log.h"

#include "glad/glad.h"


namespace Grape
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Grape::ShaderDataType::Float:        return GL_FLOAT;
        case Grape::ShaderDataType::Float2:        return GL_FLOAT;
        case Grape::ShaderDataType::Float3:        return GL_FLOAT;
        case Grape::ShaderDataType::Float4:        return GL_FLOAT;
        case Grape::ShaderDataType::Int:        return GL_INT;
        case Grape::ShaderDataType::Int2:        return GL_INT;
        case Grape::ShaderDataType::Int3:        return GL_INT;
        case Grape::ShaderDataType::Int4:        return GL_INT;
        case Grape::ShaderDataType::Mat3:        return GL_FLOAT;
        case Grape::ShaderDataType::Mat4:        return GL_FLOAT;
        default:
            break;
        }
        GP_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

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

        float vertices[3 * 7] = 
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        {
            BufferLayout layout =
            {
                {ShaderDataType::Float3, "a_position"},
                {ShaderDataType::Float4, "a_color"},
            };
            m_vertexBuffer->SetLayout(layout);
        }
        uint32_t index = 0;
        const auto& layout = m_vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type)
                , element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
            ++index;
        }
        unsigned int indices[3] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        // shader
        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;
            out vec3 v_position;
            out vec4 v_color;

            void main()
            {
                v_position = a_position;
                v_color = a_color;
                gl_Position = vec4(a_position, 1.0);
            }
        )";
        std::string fagSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_position;
            in vec4 v_color;

            void main()
            {
                color = vec4(v_position * 0.5 + 0.5, 1.0f);
                color = v_color;
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