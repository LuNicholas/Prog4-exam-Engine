#include "BurgerTimePCH.h"
#include "LevelReader.h"
#include "GameObject.h"
#include "CollisionBox.h"

LevelReader::LevelReader()
{

}
LevelReader::~LevelReader()
{

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
				ReadFloor(line, go);
			}
			else if (line.at(0) == 'L')
			{
				ReadLadder(line, go);
			}
			std::getline(m_Input, line, '\n');
		}
	}
	m_Input.close();
}

void LevelReader::ReadFloor(const std::string& line, std::shared_ptr<dae::GameObject>& go)
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
void LevelReader::ReadLadder(const std::string& line, std::shared_ptr<dae::GameObject>& go)
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