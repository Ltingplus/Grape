
#include "Grape.h"
#include "Grape/Renderer/Renderer.h"

using namespace Grape;

class ExampleLayer : public Grape::ILayer
{
public:
    ExampleLayer()
        : ILayer("Example")
        , m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
        , m_cameraPosition(0.0f)
        , m_cameraRotation(0.0f)
        , m_cameraMoveSpeed(2.0f)
        , m_cameraRotationSpeed(90.0f)
    {
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

            uniform mat4 u_viewProjection;

            void main()
            {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_viewProjection * vec4(a_position, 1.0);
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

            uniform mat4 u_viewProjection;

            void main()
            {
                v_position = a_position;
                gl_Position = u_viewProjection * vec4(a_position, 1.0);
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

    void OnUpdate(Timestep ts) override
    {
        if (Grape::IInput::IsKeyPressed(GP_KEY_LEFT))
            m_cameraPosition.x += m_cameraMoveSpeed * ts;
        else if (Grape::IInput::IsKeyPressed(GP_KEY_RIGHT))
            m_cameraPosition.x -= m_cameraMoveSpeed * ts;

        if (Grape::IInput::IsKeyPressed(GP_KEY_UP))
            m_cameraPosition.y -= m_cameraMoveSpeed * ts;
        else if (Grape::IInput::IsKeyPressed(GP_KEY_DOWN))
            m_cameraPosition.y += m_cameraMoveSpeed * ts;

        if (Grape::IInput::IsKeyPressed(GP_KEY_A))
            m_cameraRotation -= m_cameraRotationSpeed * ts;
        if (Grape::IInput::IsKeyPressed(GP_KEY_D))
            m_cameraRotation += m_cameraRotationSpeed * ts;

        RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
        RenderCommand::Clear();

        m_camera.SetPosition(m_cameraPosition);
        m_camera.SetRotation(m_cameraRotation);

        Renderer::BeginScene(m_camera);

        Renderer::Submit(m_blueShader, m_squareVertexArray);

        Renderer::Submit(m_shader, m_vertexArray);
    }

    void OnEvent(Grape::IEvent& event) override
    {
        if (event.GetEventType() == Grape::EventType::KeyPressed)
        {
            Grape::KeyPressedEvent& e = (Grape::KeyPressedEvent&)event;
            if (e.GetKeyCode() == GP_KEY_SPACE)
                GP_TRACE("Space key is pressed (event)!");
            GP_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

private:
    std::shared_ptr<Grape::Shader> m_shader;
    std::shared_ptr<Grape::VertexArray> m_vertexArray;
    std::shared_ptr<Grape::Shader> m_blueShader;
    std::shared_ptr<Grape::VertexArray> m_squareVertexArray;

    Grape::OrthographicCamera m_camera;

    glm::vec3 m_cameraPosition;
    float m_cameraMoveSpeed;

    float m_cameraRotation;
    float m_cameraRotationSpeed;
};
class SandboxApp : public Grape::IApplication
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer());
        PushOverlayer(new Grape::ImGuiLayer());
    }

    ~SandboxApp()
    {

    }

};

Grape::IApplication* Grape::CreateApplication()
{
    return new SandboxApp();
}

