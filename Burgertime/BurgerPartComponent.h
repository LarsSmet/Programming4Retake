#pragma once
#include <BaseComponent.h>
#include <vector>
#include <RectangleColliderComponent.h>
#include <PhysicsComponent.h>
#include "CharacterComponent.h"
#include "GameMode.h"
#include "SoundSystem.h"


namespace dae
{
    enum class BurgerState
    {
        normal,
        falling,
       
    };


    struct BurgerPart
    {
        std::shared_ptr<RectangleColliderComponent> pCollider;
        bool hasBeenWalked = false;
        //float lastPosY;

    };


    class BurgerPartComponent : public BaseComponent
    {

    public:
        BurgerPartComponent(GameObject* go, Point2f pos, float width, float height, CharacterComponent* pCharacter, BaseColliderComponent* level, GameMode* gameMode);
        ~BurgerPartComponent();

        virtual void Update(float elapsedSec) override;

        BurgerState GetBurgerState() const;

        int GetAmountOfCol() const;

        std::vector<BurgerPart> GetParts() const;

        void SetState(BurgerState newState);

        RectangleColliderComponent* GetTotalCollider() const;

        void SetHitByOtherPart(bool value);

        void HandleMovement();

        void SavePreviousYPos();

    private:


   

        Rectf* m_pPlayerCollider;

        std::vector<BurgerPart> m_Parts;

        BurgerState m_State;

        BaseColliderComponent* m_pLevel;

        float m_PreviousYPos;



        GameMode* m_pGameMode;

        int m_AmountOfCol;

        RectangleColliderComponent* m_TotalCollider; 


        bool m_GotHitByOtherPart;



    };

}