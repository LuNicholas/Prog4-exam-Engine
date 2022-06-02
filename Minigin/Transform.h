#pragma once

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetWorldPosition(const glm::vec3& worldPos) { m_WorldPosition = worldPos; }

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_WorldPosition;

	};
}
