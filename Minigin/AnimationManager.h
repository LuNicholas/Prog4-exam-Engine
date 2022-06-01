#pragma once
#include "Component.h"
#include <map>

namespace dae
{
	class SpriteAnimation;

	class AnimationManager final: public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void AddAnimation(const std::string& spriteSheet, const std::string& id, int width, int height, int col, int row, float frameTime);
		void SetActiveAnimation(const std::string& id);

		void ResetAnimation();

		~AnimationManager();
		AnimationManager(const AnimationManager& other) = delete;
		AnimationManager(AnimationManager&& other) = delete;
		AnimationManager& operator=(const AnimationManager& other) = delete;
		AnimationManager& operator=(AnimationManager&& other) = delete;

	private:
		AnimationManager();

		std::map<std::string, SpriteAnimation*> m_Animations;
		std::string m_ActiveAnim;
		//std::vector<> m_Animations;
	};

}