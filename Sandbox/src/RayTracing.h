#pragma once

#include "Grape.h"
#include "Grape/Renderer/Renderer.h"
#include "Grape/Core/IImage.h"

#include "imgui/imgui.h"


using namespace Grape;

class RayTracingRenderer
{
public:
    RayTracingRenderer() = default;

    void OnResize(uint32_t width, uint32_t height);
    void Render();

    Ref<IImage> GetFinalImage() const { return m_finalImage; }

private:
    glm::vec4 ProcessPixel(glm::vec2 coord);

private:
    Ref<IImage> m_finalImage;
    uint32_t* m_imageData = nullptr;
};

class RayTracingLayer : public ILayer
{
public:
    RayTracingLayer()
        : ILayer("RayTracing")
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
    uint32_t m_viewportWidth = 0, m_viewportHeight = 0;

    float m_lastRenderTime = 0.0f;

};
