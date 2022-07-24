#pragma once
#include <BaseComponent.h>
#include <vector>


namespace dae
{

    class BurgerPartComponent;

    class GameMode : public BaseComponent
    {

    public:

        GameMode(GameObject* go);
        ~GameMode();

        void AddBurgerPart(BurgerPartComponent* newPart);
        std::vector<BurgerPartComponent*> GetAllBurgerParts();

    private:

        std::vector<BurgerPartComponent*> m_AllBurgerPartComponents;

    };

}
