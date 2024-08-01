

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
    
        // ªÊ÷∆»˝Ω«–Œ≤‚ ‘
        m_vertexArray.reset(VertexArray::Create());
        float vertices[3 * 7] = 
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_position"},
            {ShaderDataType::Float4, "a_color"},
        };
        vertexBuffer->SetLayout(layout);
        m_vertexArray->AddVertexBuffer(vertexBuffer);
        
        unsigned int indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_vertexArray->SetIndexBuffer(indexBuffer);
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

        m_squareVertexArray.reset(VertexArray::Create());
        float squareVertices[3 * 4] =
        {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f, 
             0.75f,  0.75f, 0.0f,
             -0.75f,  0.75f, 0.0f
        };
        std::shared_ptr<VertexBuffer> sqVertexBuffer;
        sqVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        BufferLayout sqLayout =
        {
            {ShaderDataType::Float3, "a_position"}
        };
        sqVertexBuffer->SetLayout(sqLayout);
        m_squareVertexArray->AddVertexBuffer(sqVertexBuffer);

        unsigned int sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> sqIndexBuffer;
        sqIndexBuffer.reset(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
        m_squareVertexArray->SetIndexBuffer(sqIndexBuffer);
        // shader
        std::string blueSqVertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_position;
            out vec3 v_position;

            void main()
            {
                v_position = a_position;
                gl_Position = vec4(a_position, 1.0);
            }
        )";
        std::string blueSqFagSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_position;

            void main()
            {
                color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
            }
        )";
        m_blueShader.reset(new Shader(blueSqVertexSrc, blueSqFagSrc));
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

            m_blueShader->Bind();
            m_squareVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            m_shader->Bind();
            m_vertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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