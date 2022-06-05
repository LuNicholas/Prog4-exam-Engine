#include "BurgerTimePCH.h"
#include "LevelReader.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "Plate.h"

LevelReader::LevelReader()
{

}
LevelReader::~LevelReader()
{

}
std::vector<std::shared_ptr<dae::GameObject>> LevelReader::GetIngredients()
{
	return m_Ingredients;
}
std::vector<std::shared_ptr<dae::GameObject>> LevelReader::GetPlates()
{
	return m_Plates;
}

void LevelReader::AddLevel(const std::string& fileName, std::shared_ptr<dae::GameObject>& go)
{

	std::string line;


	m_Input.open(fileName, std::ios::in | std::ios::binary);

	if (m_Input.is_open())
	{
		while (!m_Input.eof())
		{
			std::getline(m_Input, line, '/');
			if (line.at(0) == 'F')
			{
				ReadFloor(go);
			}
			else if (line.at(0) == 'L')
			{
				ReadLadder(go);
			}
			else if (line.at(0) == 'T')
			{
				ReadIngredient(dae::Ingredient::IngredientType::topBun);
			}
			else if (line.at(0) == 'S')
			{
				ReadIngredient(dae::Ingredient::IngredientType::salad);
			}
			else if (line.at(0) == 'P')
			{
				ReadIngredient(dae::Ingredient::IngredientType::patty);
			}
			else if (line.at(0) == 'B')
			{
				ReadIngredient(dae::Ingredient::IngredientType::botBun);
			}
			else if (line.at(0) == 'X')
			{
				ReadPlate();
			}
			std::getline(m_Input, line, '\n');
		}
	}
	m_Input.close();
}

void LevelReader::ReadFloor(std::shared_ptr<dae::GameObject>& go)
{
	dae::CollisionBox* colBox = go->AddComponent<dae::CollisionBox>();
	std::string numberString;
	glm::vec2 number;

	std::getline(m_Input, numberString, '/');
	number.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	number.y = std::stoi(numberString);

	colBox->SetPosition(number.x, number.y);


	std::getline(m_Input, numberString, '/');
	number.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	number.y = std::stoi(numberString);

	colBox->SetBox(number.x, number.y);

	colBox->SetTag("floor");
}
void LevelReader::ReadLadder(std::shared_ptr<dae::GameObject>& go)
{
	dae::CollisionBox* colBox = go->AddComponent<dae::CollisionBox>();
	std::string numberString;
	glm::vec2 number;

	std::getline(m_Input, numberString, '/');
	number.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	number.y = std::stoi(numberString);

	colBox->SetPosition(number.x, number.y);


	std::getline(m_Input, numberString, '/');
	number.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	number.y = std::stoi(numberString);

	colBox->SetBox(number.x, number.y);

	colBox->SetTag("Ladder");
}

void LevelReader::ReadIngredient(dae::Ingredient::IngredientType type)
{
	auto go = std::make_shared<dae::GameObject>();
	dae::Ingredient* ingredientComp = go->AddComponent<dae::Ingredient>();
	std::string numberString;
	glm::vec2 position;

	std::getline(m_Input, numberString, '/');
	position.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	position.y = std::stoi(numberString);


	ingredientComp->Init(type, position);


	m_Plates.back()->GetComponent<Plate>()->AddIngredient(ingredientComp);

	m_Ingredients.push_back(go);
}
void LevelReader::ReadPlate()
{
	auto go = std::make_shared<dae::GameObject>();
	Plate* plateComp = go->AddComponent<Plate>();
	std::string numberString;
	glm::vec2 position;

	std::getline(m_Input, numberString, '/');
	position.x = std::stoi(numberString);
	std::getline(m_Input, numberString, '/');
	position.y = std::stoi(numberString);

	plateComp->Init(position);
	m_Plates.push_back(go);
}