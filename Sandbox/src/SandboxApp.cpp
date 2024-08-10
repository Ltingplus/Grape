
#include "Grape.h"
#include "Grape/Renderer/Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

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
        Grape::Ref<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_position"},
            {ShaderDataType::Float4, "a_color"},
        };
        vertexBuffer->SetLayout(layout);
        m_vertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        Grape::Ref<IndexBuffer> indexBuffer;
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
            uniform mat4 u_transform;

            void main()
            {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
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
        m_shader.reset(IShader::Create(vertexSrc, fagSrc));

        m_squareVertexArray.reset(VertexArray::Create());
        float squareVertices[5 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        Grape::Ref<VertexBuffer> sqVertexBuffer;
        sqVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        BufferLayout sqLayout =
        {
            {ShaderDataType::Float3, "a_position"},
            {ShaderDataType::Float2, "a_texCoord"}
        };
        sqVertexBuffer->SetLayout(sqLayout);
        m_squareVertexArray->AddVertexBuffer(sqVertexBuffer);

        unsigned int sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Grape::Ref<IndexBuffer> sqIndexBuffer;
        sqIndexBuffer.reset(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
        m_squareVertexArray->SetIndexBuffer(sqIndexBuffer);
        // shader
        std::string flatColorVertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_position;
            out vec3 v_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main()
            {
                v_position = a_position;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";
        std::string flatColorFagSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_position;

            uniform vec3 u_color;

            void main()
            {
                color = vec4(u_color, 1.0f);
            }
        )";
        m_flatColorShader.reset(IShader::Create(flatColorVertexSrc, flatColorFagSrc));
    
        std::string textureShaderVertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec2 a_texCoord;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            out vec2 v_texCoord;

            void main()
            {
                v_texCoord = a_texCoord;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";
        std::string textureShaderFagSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec2 v_texCoord;

            uniform sampler2D u_texture;

            void main()
            {
                color = texture(u_texture, v_texCoord);
            }
        )";

        m_textureShader.reset(Grape::IShader::Create(textureShaderVertexSrc, textureShaderFagSrc));
        m_texture = Grape::ITexture2D::Create("assets/textures/Checkerboard.png");

        std::dynamic_pointer_cast<Grape::OpenGLShader>(m_textureShader)->Bind();
        std::dynamic_pointer_cast<Grape::OpenGLShader>(m_textureShader)->UploadUniformInt("u_texture", 0);

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

        std::dynamic_pointer_cast<OpenGLShader>(m_flatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_color", m_squareColor);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Renderer::Submit(m_flatColorShader, m_squareVertexArray, transform);
            }
        }
        m_texture->Bind();
        Renderer::Submit(m_textureShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        //Renderer::Submit(m_shader, m_vertexArray);
        Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_squareColor));
        ImGui::End();
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
    Grape::Ref<Grape::IShader> m_shader;
    Grape::Ref<Grape::VertexArray> m_vertexArray;
    Grape::Ref<Grape::IShader> m_flatColorShader;
    Grape::Ref<Grape::IShader> m_textureShader;
    Grape::Ref<Grape::VertexArray> m_squareVertexArray;
    Grape::Ref<Grape::ITexture2D> m_texture;

    Grape::OrthographicCamera m_camera;

    glm::vec3 m_cameraPosition;
    float m_cameraMoveSpeed;

    float m_cameraRotation;
    float m_cameraRotationSpeed;
    glm::vec3 m_squareColor = { 0.2f, 0.3f, 0.8f };
};
class SandboxApp : public Grape::IApplication
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer());
    }

    ~SandboxApp()
    {

    }

};

Grape::IApplication* Grape::CreateApplication()
{
    return new SandboxApp();
}

