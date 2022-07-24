#pragma once
#include "BaseComponent.h"
#include "MiniginPCH.h"
#include <PhysicsComponent.h>
#include "LadderComponent.h"


namespace dae
{
	
	enum class State
	{
		//OnLadder,
		Normal,
		UsingLadder,
		CanGrabLadder,
		temp
	};


	class CharacterComponent final: public BaseComponent
	{
	public:

		CharacterComponent(GameObject* go, PhysicsComponent* physicsComp, int ammo, BaseColliderComponent* level, LadderComponent* ladders);
		~CharacterComponent();

		bool LadderCollision(LadderInfo& ladderInfo);

		virtual void Update(float elapsedSec);

		void SpawnPepperCloud(glm::vec2 pos);

		PhysicsComponent* GetPhysicsComp();
		TransformComponent& GetTransformComp();

		void SetState(State newState);

		State GetState();


	private:

		int m_Ammo;
		PhysicsComponent* m_pPhysicsComponent;
		BaseColliderComponent* m_pLevel;
		TransformComponent* m_pTransformComp;

	

		std::vector<std::shared_ptr<LadderInfo>> m_LaddersInfo;

		State m_State;

	};

}
