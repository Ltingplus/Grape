#pragma once
#include "Grape/Core/Timestep.h"

#include "Grape/Renderer/OrthographicCamera.h"
#include "Grape/Events/MouseEvent.h"
#include "Grape/Events/ApplicationEvent.h"

namespace Grape
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(IEvent& e);

        OrthographicCamera& GetCamera() { return m_camera; }

        float GetZoomLevel() const { return m_zoomLevel; }
        void SetZoomLevel(float level) { m_zoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_aspectRatio;//×Ýºá±È
        float m_zoomLevel = 1.0f;
        OrthographicCamera m_camera;

        bool m_rotation;
        glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_cameraRotation = 0.0f;
        float m_cameraTranslationSpeed = 5.0f;
        float m_cameraRotationSpeed = 180.0f;
    };
}

