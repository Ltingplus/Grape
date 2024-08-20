
#include "gppch.h"
#include "RayTracing.h"

namespace Utils 
{

    static uint32_t ConvertToRGBA(const glm::vec4& color)
    {
        uint8_t r = (uint8_t)(color.r * 255.0f);
        uint8_t g = (uint8_t)(color.g * 255.0f);
        uint8_t b = (uint8_t)(color.b * 255.0f);
        uint8_t a = (uint8_t)(color.a * 255.0f);

        uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
        return result;
    }

}

using namespace Grape;

void RayTracingRenderer::OnResize(uint32_t width, uint32_t height)
{
    if (m_finalImage)
    {
        // No resize necessary
        if (m_finalImage->GetWidth() == width && m_finalImage->GetHeight() == height)
            return;

        m_finalImage->Resize(width, height);
    }
    else
    {
        m_finalImage = IImage::Create(width, height, Grape::ImageFormat::RGBA);
    }

    delete[] m_imageData;
    m_imageData = new uint32_t[width * height];
}

void RayTracingRenderer::Render()
{
    for (uint32_t y = 0; y < m_finalImage->GetHeight(); y++)
    {
        for (uint32_t x = 0; x < m_finalImage->GetWidth(); x++)
        {
            glm::vec2 coord = { (float)x / (float)m_finalImage->GetWidth(), (float)y / (float)m_finalImage->GetHeight() };
            coord = coord * 2.0f - 1.0f; // -1 -> 1
            auto color = ProcessPixel(coord);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            m_imageData[x + y * m_finalImage->GetWidth()] = Utils::ConvertToRGBA(color);
        }
    }

    m_finalImage->SetData(m_imageData);
}

glm::vec4 RayTracingRenderer::ProcessPixel(glm::vec2 coord)
{
    glm::vec3 rayOrigin(0.0f, 0.0f, 1.0f);
    glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
    float radius = 0.5f;
    //rayDirection = glm::normalize(rayDirection);

    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
    // where
    // a = ray origin
    // b = ray direction
    // r = radius
    // t = hit distance

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

    // Quadratic forumula discriminant:
    // b^2 - 4ac

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
        return glm::vec4(0, 0, 0, 1);

    float closestT = (-b - glm::sqrt(discriminant) / (2.0f * a));// first hit distance
    glm::vec3 hitPoint = rayOrigin + rayDirection * closestT;
    glm::vec3 normal = glm::normalize(hitPoint);
    glm::vec3 lightDir = glm::normalize((glm::vec3(-1, -1, -1)));
    float linghtIdensity = glm::max(glm::dot(normal, -lightDir), 0.0f);// cos(sita)

    glm::vec3 sphereColor(1, 0, 1);
    sphereColor *= linghtIdensity;

    return glm::vec4(sphereColor, 1.0f);
}

void RayTracingLayer::OnUpdate(Timestep ts)
{
}

void RayTracingLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::Text("Last render: %.3fms", m_lastRenderTime);
    if (ImGui::Button("Render"))
    {
        Render();
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_viewportWidth = ImGui::GetContentRegionAvail().x;
    m_viewportHeight = ImGui::GetContentRegionAvail().y;

    auto image = m_renderer.GetFinalImage();
    if (image)
        ImGui::Image((ImTextureID)(intptr_t)image->GetTextureID(), ImVec2(image->GetWidth(), image->GetHeight()));

    ImGui::End();
    ImGui::PopStyleVar();

    Render();
}

void RayTracingLayer::Render()
{
    //Timer timer;

    m_renderer.OnResize(m_viewportWidth, m_viewportHeight);
    m_renderer.Render();

    //m_LastRenderTime = timer.ElapsedMillis();
}
