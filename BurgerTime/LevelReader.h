#pragma once
#include <iostream>
#include <fstream>
#include <iomanip> 

namespace dae
{
	class GameObject;
}
	class Plate;

class LevelReader
{
	enum class IngredientType
	{
		topBun,
		salad,
		patty,
		botBun,
	};

public:
	LevelReader();
	~LevelReader();

	void AddLevel(const std::string& fileName, std::shared_ptr<dae::GameObject>& go);
	std::vector<std::shared_ptr<dae::GameObject>>& GetIngredients();
	std::vector<std::shared_ptr<dae::GameObject>>& GetPlates();

private:
	std::ifstream m_Input;

	std::vector<std::shared_ptr<dae::GameObject>> m_Ingredients;
	std::vector<std::shared_ptr<dae::GameObject>> m_Plates;
	
	void ReadFloor(std::shared_ptr<dae::GameObject>& go);
	void ReadLadder(std::shared_ptr<dae::GameObject>& go);

	void ReadIngredient(IngredientType type);
	void ReadPlate();


};

