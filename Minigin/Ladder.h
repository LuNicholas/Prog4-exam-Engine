#pragma once
#include "Component.h"

namespace dae
{
	class Ladder : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		~Ladder();
		Ladder(const Ladder& other) = delete;
		Ladder(Ladder&& other) = delete;
		Ladder& operator=(const Ladder& other) = delete;
		Ladder& operator=(Ladder&& other) = delete;

	private:
		Ladder();
	};
}
