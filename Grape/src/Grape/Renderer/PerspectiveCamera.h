#pragma once

#include "glm/glm.hpp"

namespace Grape
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(float verticalFov, float nearClip, float farClip, const glm::vec3& position);

        bool OnUpdate(float ts);
        void OnResize(uint32_t width, uint32_t height);

        const glm::mat4& GetProjection() const { return m_projection; }
        const glm::mat4& GetInverseProjection() const { return m_inverseProjection; }
        const glm::mat4& GetView() const { return m_view; }
        const glm::mat4& GetInverseView() const { return m_inverseView; }

        const glm::vec3& GetPostion() const { return m_position; }
        const glm::vec3& GetDirection() const { return m_forwardDirection; }

        const std::vector<glm::vec3>& GetRayDirections() const { return m_rayDirections; }

        float GetRotationSpeed() { return 0.3f; }

    private:
        void RecalculateProjection();
        void RecalculateView();
        void RecalculateRayDirections();

    private:
        glm::mat4 m_projection{ 1.0f };
        glm::mat4 m_inverseProjection{ 1.0f };
        glm::mat4 m_view{ 1.0f };
        glm::mat4 m_inverseView{ 1.0f };

        float m_verticalFov = 45.0f;
        float m_nearClip = 0.1f;
        float m_farClip = 100.0f;

        glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 m_forwardDirection{ 0.0f, 0.0f, 0.0f };

        std::vector<glm::vec3> m_rayDirections;

        glm::vec2 m_lastMousePosition{ 0.0f, 0.0f };

        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;

    };
}
