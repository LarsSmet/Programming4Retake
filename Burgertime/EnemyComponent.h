#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include "LadderComponent.h"

#include "CharacterComponent.h"


namespace dae
{
	class EnemyComponent;

	class AIState
	{

	public:

		AIState() {};
		virtual ~AIState(){};
		virtual AIState* Update(EnemyComponent* comp) { comp; return nullptr; };
		virtual void OnEnter(EnemyComponent* comp) { comp; };
		virtual void OnExit(EnemyComponent* comp) { comp; };

	private:


	};
	


	class EnemyComponent : public BaseComponent
	{

	public:

		EnemyComponent(GameObject* go, PhysicsComponent* physicsComp, BaseColliderComponent* level, LadderComponent* ladders, CharacterComponent* character);
		~EnemyComponent();
		virtual void Update(float elapsedSec) override;
	
		void SetVelocity(Velocity newVelocity);

		void HandleLevelCollision();

		CharacterComponent* GetPlayer();

		bool LadderCollision();

		PhysicsComponent* GetPhysicsComponent();

		LadderInfo* GetCurrentLadderInfo();

		Velocity GetVelocity();


	private:

		AIState* m_State;
		PhysicsComponent* m_pPhysicsComponent;
		BaseColliderComponent* m_pLevel;
		TransformComponent* m_pTransformComp;

		

		std::vector<std::shared_ptr<LadderInfo>> m_LaddersInfo;

		CharacterComponent* m_CharacterComponent;

		LadderInfo* m_CurrentLadderInfo;



	};



	


}

