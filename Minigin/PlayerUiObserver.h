#pragma once
#include "Observer.h"


namespace dae
{
    class GameObject;
    class PlayerUiComponent;

    class PlayerUiObserver final : public Observer
    {
    public:
        PlayerUiObserver(PlayerUiComponent* playerUi);
        ~PlayerUiObserver();

        void onNotify(const dae::GameObject&, Event event);

    private:
        PlayerUiComponent* m_pPlayerUi = nullptr;
    };
}
