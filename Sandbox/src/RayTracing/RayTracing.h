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
    struct HitPayload
    {
        float HitDistance;
        glm::vec3 WorldPosition;
        glm::vec3 WorldNormal;

        int ObjectIndex;
    };

    glm::vec4 PerPixel(uint32_t x, uint32_t y);
    HitPayload TraceRay(const Ray& ray);
    HitPayload ClosetHit(const Ray& ray, float hitDistance, int objectIndex);
    HitPayload Miss(const Ray& ray);

private:
    Ref<IImage> m_finalImage;
    uint32_t* m_imageData = nullptr;

    const PerspectiveCamera* m_activeCamera = nullptr;
    const Scene* m_activeScene = nullptr;
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
