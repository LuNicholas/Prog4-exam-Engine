#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Texture2DComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetTexture(std::string filename);

		virtual ~Texture2DComponent() = default;
		Texture2DComponent(const Texture2DComponent& other) = delete;
		Texture2DComponent(Texture2DComponent&& other) = delete;
		Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
		Texture2DComponent& operator=(Texture2DComponent&& other) = delete;
	private:
		Texture2DComponent();

		std::shared_ptr<Texture2D> m_Texture{};	
	};
}
