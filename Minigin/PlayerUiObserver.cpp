#include "MiniginPCH.h"
#include "PlayerUiObserver.h"
#include "PlayerUiComponent.h"
#include "HealthComponent.h"


dae::PlayerUiObserver::PlayerUiObserver(PlayerUiComponent* playerUi)
	:m_pPlayerUi(playerUi)
{
}
dae::PlayerUiObserver::~PlayerUiObserver()
{

}

void dae::PlayerUiObserver::onNotify(const dae::GameObject& go, Event event)
{
	switch (event)
	{
	case Event::PlayerHit:
	{
		m_pPlayerUi->SetLives(go.GetComponent<HealthComponent>()->GetHealth());
		break;
	}
	}
}