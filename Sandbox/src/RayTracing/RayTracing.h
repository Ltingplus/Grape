#pragma once

#include "Grape.h"
#include "Grape/Renderer/Renderer.h"
#include "Grape/Core/IImage.h"
#include "Grape/Renderer/PerspectiveCamera.h"
#include "Scene.h"

#include "imgui/imgui.h"


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
    void Render(const Scene& scene, const PerspectiveCamera& camera);

    Ref<IImage> GetFinalImage() const { return m_finalImage; }

private:
    glm::vec4 TraceRay(const Scene& scene, const Ray& ray);

private:
    Ref<IImage> m_finalImage;
    uint32_t* m_imageData = nullptr;
};

class RayTracingLayer : public ILayer
{
public:
    RayTracingLayer();

    void OnUpdate(Timestep ts) override;

    virtual void OnImGuiRender() override;

    void Render();

private:
    RayTracingRenderer m_renderer;
    PerspectiveCamera m_camera;
    Scene m_scene;
    uint32_t m_viewportWidth = 0, m_viewportHeight = 0;

    float m_lastRenderTime = 0.0f;

};
