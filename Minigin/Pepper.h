#pragma once
#include "Component.h"

namespace dae
{

	class CollisionBox;
	class Texture2D;
	class AnimationManager;

	class Pepper final : public Component
	{
		friend class GameObject;
	public:
		~Pepper();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init();

		Pepper(const Pepper& other) = delete;
		Pepper(Pepper&& other) = delete;
		Pepper& operator=(const Pepper& other) = delete;
		Pepper& operator=(Pepper&& other) = delete;

	private:
		Pepper();

		bool m_OnCooldown;

		AnimationManager* m_pAnimationComp;
	};
}
