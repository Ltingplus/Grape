#pragma once

#include "Grape.h"
#include "Grape/Renderer/Renderer.h"
#include "Grape/Core/IImage.h"

#include "imgui/imgui.h"
#include "Grape/Renderer/PerspectiveCamera.h"


using namespace Grape;

struct Ray
{
    glm::vec3 Origin;
    glm::vec3 Direction;
};

class RayTracingRenderer
{
public:
    RayTracingRenderer() = default;

    void OnResize(uint32_t width, uint32_t height);
    void Render(const PerspectiveCamera& camera);

    Ref<IImage> GetFinalImage() const { return m_finalImage; }

private:
    glm::vec4 TraceRay(const Ray& ray);

private:
    Ref<IImage> m_finalImage;
    uint32_t* m_imageData = nullptr;
};

class RayTracingLayer : public ILayer
{
public:
    RayTracingLayer()
        : ILayer("RayTracing")
        , m_camera(45.0f, 0.1f, 100.0f, glm::vec3(0, 0, -2))
    {

    }

    void OnUpdate(Timestep ts) override;

    virtual void OnImGuiRender() override;

    void OnEvent(Grape::IEvent& e) override
    {

    }

    void Render();

private:
    RayTracingRenderer m_renderer;
    PerspectiveCamera m_camera;
    uint32_t m_viewportWidth = 0, m_viewportHeight = 0;

    float m_lastRenderTime = 0.0f;

};
