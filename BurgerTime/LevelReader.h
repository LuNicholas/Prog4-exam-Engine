#pragma once
#include <iostream>
#include <fstream>
#include <iomanip> 

namespace dae
{
	class GameObject;
}

class LevelReader
{
public:
	LevelReader();
	~LevelReader();

	void AddLevel(const std::string& fileName, std::shared_ptr<dae::GameObject>& go);

private:
	std::ifstream m_Input;
	
	void ReadFloor(const std::string& line, std::shared_ptr<dae::GameObject>& go);
	void ReadLadder(const std::string& line, std::shared_ptr<dae::GameObject>& go);

};

