#include "gppch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Grape/Core/IInput.h"
#include "Grape/Core/KeyCodes.h"


namespace Grape
{

    PerspectiveCamera::PerspectiveCamera(float verticalFov, float nearClip, float farClip, const glm::vec3& position)
        : m_verticalFov(verticalFov)
        , m_nearClip(nearClip)
        , m_farClip(farClip)
        , m_position(position)
    {
        m_forwardDirection = glm::vec3(0, 0, -1);
    }

    void PerspectiveCamera::OnUpdate(float ts)
    {
        glm::vec2 mousePos{ IInput::GetMousePosition().first, IInput::GetMousePosition().second };
        glm::vec2 delta = (mousePos - m_lastMousePosition) * 0.002f;
        m_lastMousePosition = mousePos;

        if (!IInput::IsMouseButtonPressed((int)MouseButton::Right))
            return;

        bool isMoved = false;

        constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
        glm::vec3 rightDirection = glm::cross(m_forwardDirection, upDirection);

        float speed = 5.0f;

        // Movement
        if (IInput::IsKeyPressed(GP_KEY_W))
        {
            m_position += m_forwardDirection * speed * ts;
            isMoved = true;
        }
        else if (IInput::IsKeyPressed(GP_KEY_S))
        {
            m_position -= m_forwardDirection * speed * ts;
            isMoved = true;
        }
        if (IInput::IsKeyPressed(GP_KEY_A))
        {
            m_position -= rightDirection * speed * ts;
            isMoved = true;
        }
        else if (IInput::IsKeyPressed(GP_KEY_D))
        {
            m_position += rightDirection * speed * ts;
            isMoved = true;
        }
        if (IInput::IsKeyPressed(GP_KEY_Q))
        {
            m_position -= upDirection * speed * ts;
            isMoved = true;
        }
        else if (IInput::IsKeyPressed(GP_KEY_E))
        {
            m_position += upDirection * speed * ts;
            isMoved = true;
        }

        // Rotation
        if (delta.x != 0.0f || delta.y != 0.0f)
        {
            float pitchDelta = delta.y * GetRotationSpeed();
            float yawDelta = delta.x * GetRotationSpeed();

            glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
                glm::angleAxis(-yawDelta, glm::vec3(0.0f, 1.0f, 0.0f))));
            m_forwardDirection = glm::rotate(q, m_forwardDirection);

            isMoved = true;
        }

        if (isMoved)
        {
            RecalculateView();
            RecalculateRayDirections();
        }
    }

    void PerspectiveCamera::OnResize(uint32_t width, uint32_t height)
    {
        if (width == m_viewportWidth && height == m_viewportHeight)
            return;
        m_viewportWidth = width;
        m_viewportHeight = height;
        RecalculateProjection();
        RecalculateRayDirections();
    }

    void PerspectiveCamera::RecalculateProjection()
    {
        m_projection = glm::perspectiveFov(m_verticalFov, (float)m_viewportWidth, (float)m_viewportHeight, m_nearClip, m_farClip);
        m_inverseProjection = glm::inverse(m_projection);
    }

    void PerspectiveCamera::RecalculateView()
    {
        m_view = glm::lookAt(m_position, m_position + m_forwardDirection, glm::vec3(0, 1, 0));
        m_inverseView = glm::inverse(m_view);
    }

    void PerspectiveCamera::RecalculateRayDirections()
    {
        m_rayDirections.resize(m_viewportWidth * m_viewportHeight);

        for (uint32_t y = 0; y < m_viewportHeight; y++)
        {
            for (uint32_t x = 0; x < m_viewportWidth; x++)
            {
                glm::vec2 coord = { (float)x / (float)m_viewportWidth, (float)y / (float)m_viewportHeight };
                coord = coord * 2.0f - 1.0f; // [-1, 1]
                glm::vec4 clipCoord = glm::vec4(coord.x, coord.y, 1, 1);// 屏幕空间坐标转裁剪空间坐标

                glm::vec4 worldCoord = m_inverseView * m_inverseProjection * clipCoord;
                glm::vec3 worldPos = glm::vec3(worldCoord) / worldCoord.w;//归一化齐次坐标
                //glm::vec4 target = m_inverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
                //glm::vec3 rayDirection = glm::vec3(m_inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
                m_rayDirections[x + y * m_viewportWidth] = glm::normalize(worldPos);
            }
        }
    }

}