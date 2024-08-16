#pragma once

#include "glm/detail/type_mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Grape
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3& position) 
        {
            m_position = position;
            RecalculateViewMatrix();
        }
        const float& GetRotation() const { return m_rotation; }
        void SetRotation(const float& rotation)
        {
            m_rotation = rotation;
            RecalculateViewMatrix();
        }

        void SetProjection(float left, float right, float bottom, float top)
        {
            m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
            m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
        }

        const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();
    private:
        glm::vec3 m_position;
        glm::mat4 m_viewProjectionMatrix;
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;

        float m_rotation;
    };
}
