#pragma once
#include <Component.h>

namespace dae
{
	class CollisionBox;
	class Ingredient;
}

class Plate final : public dae::Component
{

public:

	friend class dae::GameObject;

	void Init();
	void AddIngredient(dae::Ingredient* ingredient);
	bool IsPlateDone()const;

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	~Plate();
	Plate(const Plate& other) = delete;
	Plate(Plate&& other) = delete;
	Plate& operator=(const Plate& other) = delete;
	Plate& operator=(Plate&& other) = delete;

private:
	Plate();

	dae::CollisionBox* m_pCollider;
	std::vector<dae::Ingredient*> m_Ingredients;

	bool m_PlateDone;

};

