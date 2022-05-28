#include "MiniginPCH.h"
#include "AnimationManager.h"
#include "SpriteAnimation.h"

dae::AnimationManager::AnimationManager()
{
}
dae::AnimationManager::~AnimationManager()
{
	for (std::pair<std::string, SpriteAnimation*> anim : m_Animations)
	{
		delete anim.second;
	}
}


void dae::AnimationManager::Update(float deltaTime)
{
	m_Animations[m_ActiveAnim]->Update(deltaTime);
	m_Animations[m_ActiveAnim]->SetTransform(m_Transform);
}
void dae::AnimationManager::FixedUpdate(float deltaTime)
{
	m_Animations[m_ActiveAnim]->FixedUpdate(deltaTime);
}
void dae::AnimationManager::Render() const
{
	m_Animations.at(m_ActiveAnim)->Render();
}


void dae::AnimationManager::AddAnimation(const std::string& spriteSheet ,const std::string& id, int width, int height, int col, int row, float frameTime)
{

	SpriteAnimation* pAnimation = new SpriteAnimation(spriteSheet, width, height, col, row, frameTime);

	m_Animations[id] = pAnimation;
}

void dae::AnimationManager::SetActiveAnimation(const std::string& id)
{
	m_ActiveAnim = id;
}