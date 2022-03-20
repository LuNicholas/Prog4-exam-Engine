#include "MiniginPCH.h"
#include "PlayerUiObserver.h"
//#include "PlayerUiComponent.h"
//#include "HealthComponent.h"
//
//
//dae::PlayerUiObserver::PlayerUiObserver()
//{
//}
//dae::PlayerUiObserver::~PlayerUiObserver()
//{
//
//}
//
//void dae::PlayerUiObserver::onNotify(const dae::GameObject& go, Event event)
//{
//	switch (event)
//	{
//	case Event::PlayerDied:
//	{
//		go.GetComponent<PlayerUiComponent>()->SetLives(go.GetComponent<HealthComponent>()->GetHealth());
//		break;
//	}
//	case Event::ScoreIncrease:
//	{
//		go.GetComponent<PlayerUiComponent>()->AddScore(100);
//		break;
//	}
//	}
//}