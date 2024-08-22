
#include "gppch.h"
#include "RayTracing.h"

#include "glm/gtc/type_ptr.hpp"

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

void RayTracingRenderer::Render(const Scene& scene, const PerspectiveCamera& camera)
{
    Ray ray;
    ray.Origin = camera.GetPostion();
    for (uint32_t y = 0; y < m_finalImage->GetHeight(); y++)
    {
        for (uint32_t x = 0; x < m_finalImage->GetWidth(); x++)
        {
            if (x > 848 && y > 273)
            {
                ray.Direction = camera.GetRayDirections()[x + y * m_finalImage->GetWidth()];

            }
            else
                ray.Direction = camera.GetRayDirections()[x + y * m_finalImage->GetWidth()];

            auto color = TraceRay(scene, ray);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            m_imageData[x + y * m_finalImage->GetWidth()] = Utils::ConvertToRGBA(color);
        }
    }
    for (uint32_t x = 0; x < m_finalImage->GetWidth(); x++)
        m_imageData[x] = Utils::ConvertToRGBA(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    for (uint32_t y = 0; y < m_finalImage->GetHeight(); y++)
        m_imageData[y * m_finalImage->GetWidth()] = Utils::ConvertToRGBA(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));


    m_finalImage->SetData(m_imageData);
}

glm::vec4 RayTracingRenderer::TraceRay(const Scene& scene, const Ray& ray)
{
    if (scene.Spheres.empty())
        return glm::vec4(0, 0, 0, 1);
    
    // ray: x=ax + bx*t; y=ay+by*t
    // circle: x^2 + y^2 - r^2 = 0
    // (bx^2 + by^2)t^2 + (2(ax*bx + ay*by))t + (ax^2 + ay^2 - r^2) = 0
    // where
    // a = ray origin
    // b = ray direction
    // r = radius
    // t = hit distance
    const Sphere* closestSphere = nullptr;
    float hitDistance = std::numeric_limits<float>::max();
    for (const Sphere& sphere : scene.Spheres)
    {
        glm::vec3 origin = ray.Origin - sphere.Position;
        float a = glm::dot(ray.Direction, ray.Direction);
        float b = 2.0f * glm::dot(origin, ray.Direction);
        float c = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;

        // Quadratic forumula discriminant:
        // b^2 - 4ac
        float discriminant = b * b - 4.0f * a * c;
        if (discriminant < 0.0f)
            continue;
        // Quadratic formula:
        // (-b +- sqrt(discriminant)) / 2a
        // float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
        float closestT = (-b - glm::sqrt(discriminant) / (2.0f * a));// first hit distance
        if (closestT < hitDistance)
        {
            hitDistance = closestT;
            closestSphere = &sphere;
        }
    }
    if (closestSphere == nullptr)
        return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 origin = ray.Origin - closestSphere->Position;
    glm::vec3 hitPoint = origin + ray.Direction * hitDistance;
    glm::vec3 normal = glm::normalize(hitPoint);
    glm::vec3 lightDir = glm::normalize(scene.LightDir);
    float lightIntensity = glm::max(glm::dot(normal, -lightDir), 0.0f);// cos(sita)

    glm::vec3 sphereColor = closestSphere->Albedo;
    sphereColor *= lightIntensity;
    
    return glm::vec4(sphereColor, 1.0f);
}

RayTracingLayer::RayTracingLayer()
    : ILayer("RayTracing")
    , m_camera(45.0f, 0.1f, 100.0f, glm::vec3(0, 0, -10))
{
    {
        Sphere sphere;
        sphere.Position = { 0.0f, 0.0f, 0.0f };
        sphere.Radius = 0.5f;
        sphere.Albedo = { 1.0f, 0.0f, 1.0f };
        m_scene.Spheres.emplace_back(sphere);
    }
    {
        Sphere sphere;
        sphere.Position = { 1.0f, 0.0f, -5.0f };
        sphere.Radius = 1.5f;
        sphere.Albedo = { 0.2f, 0.3f, 1.0f };
        m_scene.Spheres.emplace_back(sphere);
    }
}

void RayTracingLayer::OnUpdate(Timestep ts)
{
    m_camera.OnUpdate(ts);
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

    ImGui::Begin("Scene");

    ImGui::DragFloat3("Light Direction", glm::value_ptr(m_scene.LightDir), 0.1f);
    ImGui::Separator();

    for (size_t i = 0; i < m_scene.Spheres.size(); i++)
    {
        ImGui::PushID(i);

        Sphere& sphere = m_scene.Spheres[i];
        ImGui::DragFloat3("Position", glm::value_ptr(sphere.Position), 0.1f);
        ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
        ImGui::ColorEdit3("Albedo", glm::value_ptr(sphere.Albedo));

        ImGui::Separator();

        ImGui::PopID();
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");
    m_viewportWidth = ImGui::GetContentRegionAvail().x;
    m_viewportHeight = ImGui::GetContentRegionAvail().y;
    auto image = m_renderer.GetFinalImage();
    if (image)
        ImGui::Image((ImTextureID)(intptr_t)image->GetTextureID(), ImVec2(image->GetWidth(), image->GetHeight()), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();

    Render();
}

void RayTracingLayer::Render()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();

    m_renderer.OnResize(m_viewportWidth, m_viewportHeight);
    m_camera.OnResize(m_viewportWidth, m_viewportHeight);
    m_renderer.Render(m_scene, m_camera);

    m_lastRenderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - time).count() * 0.001f * 0.001f;
}
