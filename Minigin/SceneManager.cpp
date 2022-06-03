#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	if (m_ActiveScene != nullptr)
		m_ActiveScene->Update(deltaTime);

	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	if (m_ActiveScene != nullptr)
		m_ActiveScene->FixedUpdate(deltaTime);

	//for (auto& scene : m_Scenes)
	//{
	//	scene->FixedUpdate(deltaTime);
	//}
}

void dae::SceneManager::Render()
{
	if (m_ActiveScene != nullptr)
		m_ActiveScene->Render();

	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](std::shared_ptr<Scene> scene)
		{
			return scene->GetSceneName() == name;
		});

	if (it != m_Scenes.end())
	{
		m_ActiveScene = *it;
	}
}

void dae::SceneManager::NextScene()
{
	for (unsigned int i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i] == m_ActiveScene)
		{
			if (++i < m_Scenes.size())
			{
				m_ActiveScene = m_Scenes[i];
				break;
			}
		}
	}
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](std::shared_ptr<Scene> scene)
		{
			return scene->GetSceneName() == name;
		});

	if (it != m_Scenes.end())
	{
		return *(*it);
	}


	return CreateScene(name);
}

dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_ActiveScene;
}