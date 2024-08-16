#include "gppch.h"
#include "OrthographicCameraController.h"
#include "Grape/IInput.h"
#include "Grape/KeyCodes.h"

namespace Grape
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation /*= false*/)
        : m_aspectRatio(aspectRatio)
        , m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
        , m_rotation(rotation)
    {

    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (IInput::IsKeyPressed(GP_KEY_A))
            m_cameraPosition.x += m_cameraTranslationSpeed * ts;
        else if (Grape::IInput::IsKeyPressed(GP_KEY_D))
            m_cameraPosition.x -= m_cameraTranslationSpeed * ts;

        if (Grape::IInput::IsKeyPressed(GP_KEY_W))
            m_cameraPosition.y -= m_cameraTranslationSpeed * ts;
        else if (Grape::IInput::IsKeyPressed(GP_KEY_S))
            m_cameraPosition.y += m_cameraTranslationSpeed * ts;
        m_camera.SetPosition(m_cameraPosition);

        if(m_rotation)
        {
            if (Grape::IInput::IsKeyPressed(GP_KEY_Q))
                m_cameraRotation -= m_cameraRotationSpeed * ts;
            if (Grape::IInput::IsKeyPressed(GP_KEY_E))
                m_cameraRotation += m_cameraRotationSpeed * ts;
            m_camera.SetRotation(m_cameraRotation);
        }
        m_cameraTranslationSpeed = m_zoomLevel;

    }

    void OrthographicCameraController::OnEvent(IEvent& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(GP_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(GP_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_zoomLevel -= e.GetYOffset() * 0.25f;
        m_zoomLevel = std::max(m_zoomLevel, 0.25f);
        m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_aspectRatio = (float)e.GetHeight() / (float)e.GetWidth();

        m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

}
