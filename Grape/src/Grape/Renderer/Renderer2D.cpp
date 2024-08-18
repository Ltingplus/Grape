#include "gppch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "IShader.h"
#include "RenderCommand.h"

namespace Grape
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<IShader> TextureShader;
        Ref<ITexture2D> WhiteTexture;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::Init()
    {
        s_data = new Renderer2DStorage();
        s_data->QuadVertexArray = VertexArray::Create();

        float squareVertices[5 * 4] = {
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Ref<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
                  { ShaderDataType::Float3, "a_position" },
                  { ShaderDataType::Float2, "a_texCoord" }
            });
        s_data->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB; 
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        s_data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_data->WhiteTexture = ITexture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_data->TextureShader = IShader::Create("assets/shaders/Texture.glsl");
        s_data->TextureShader->Bind();
        s_data->TextureShader->SetInt("u_texture", 0);
    
    }

    void Renderer2D::ShutDown()
    {
        delete s_data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_data->TextureShader->Bind();
        s_data->TextureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_data->TextureShader->SetFloat4("u_color", color);
        s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);
        s_data->WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_data->TextureShader->SetMat4("u_transform", transform);
        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture
        , float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture
        , float tilingFactor, const glm::vec4& tintColor)
    {
        s_data->TextureShader->SetFloat4("u_color", tintColor);
        s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_data->TextureShader->SetMat4("u_transform", transform);

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 1.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        s_data->TextureShader->SetFloat4("u_color", color);
        s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);
        s_data->WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_data->TextureShader->SetMat4("u_transform", transform);
        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<ITexture2D>& texture
        , float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }
    

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<ITexture2D>& texture
        , float tilingFactor, const glm::vec4& tintColor)
    {
        s_data->TextureShader->SetFloat4("u_color", tintColor);
        s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_data->TextureShader->SetMat4("u_transform", transform);

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }

}
