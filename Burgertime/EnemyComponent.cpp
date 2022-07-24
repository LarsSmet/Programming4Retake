#include "pch.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "MoveState.h"

namespace dae
{
	EnemyComponent::EnemyComponent(GameObject* go, PhysicsComponent* physicsComp, BaseColliderComponent* level, LadderComponent* ladders, CharacterComponent* character): BaseComponent(go),
		m_pPhysicsComponent{physicsComp}, m_pLevel{level}, m_LaddersInfo{ladders->GetLaddersInfo()}, m_CharacterComponent{ character }
	{
		m_pTransformComp = go->GetTransformComp();
		m_State = new MoveState();
		m_State->OnEnter(this);

	}

	EnemyComponent::~EnemyComponent()
	{
		delete m_State;
		m_State = nullptr;
	}

	void EnemyComponent::Update(float elapsedSec)
	{
		
		auto transformComp = m_Owner->GetTransformComp();
		auto colComp = m_pPhysicsComponent->GetColliderComponent();
		//handle state
		colComp;

		//m_pPhysicsComponent->SetVelocity(Velocity{1.f,0.f});
		transformComp;
		
		//save old state
		AIState* state = m_State->Update(this);
		
		

		//m_State->Update(this);
		if (state != nullptr)
		{
			delete m_State;
			m_State = state;
			state->OnEnter(this);
		}



		

		m_pPhysicsComponent->Update(elapsedSec);

	}

	void EnemyComponent::SetVelocity(Velocity newVelocity)
	{

		m_pPhysicsComponent->SetVelocity(newVelocity);
	}

	void EnemyComponent::HandleLevelCollision()
	{

		auto transformComp = m_Owner->GetTransformComp();
		auto colComp = m_pPhysicsComponent->GetColliderComponent();

		auto colInfo = colComp->OnCollision(m_pLevel);

		if (colInfo.verticalHit)
		{


			m_pPhysicsComponent->SetYVelocity(0);

			if (colInfo.botHit == true)
			{
				/*	transformComp->SetPosition(transformComp->GetPosition().x , transformComp->GetPosition().y +1);
					colComp->SetPosition(colComp->GetPosition().x, colComp->GetPosition().y +1);*/
			}


		}
		if (colInfo.horizontalHit)
		{
			m_pPhysicsComponent->SetXVelocity(0);

			//check left or right bool

			if (colInfo.leftHit)
			{
				transformComp->SetPosition(transformComp->GetPosition().x + 1, transformComp->GetPosition().y);
				colComp->SetPosition(colComp->GetPosition().x + 1, colComp->GetPosition().y);
				//std::cout << "lefthit";

			}
			else if (colInfo.rightHit)
			{
				transformComp->SetPosition(transformComp->GetPosition().x - 1, transformComp->GetPosition().y);
				colComp->SetPosition(colComp->GetPosition().x - 1, colComp->GetPosition().y);
				//std::cout << "righthit";
			}


		}

	}

	CharacterComponent* EnemyComponent::GetPlayer()
	{
		return m_CharacterComponent;
	}

	bool EnemyComponent::LadderCollision()
	{
		auto colComp = m_pPhysicsComponent->GetColliderComponent();

		for (size_t i = 0; i < m_LaddersInfo.size(); ++i)
		{



			if (colComp->OnTrigger(m_LaddersInfo[i]->colliderComp)) //return bool
			{
				m_CurrentLadderInfo = m_LaddersInfo[i].get(); //ladderinfo always stays the same

				return true;
			}


		}

		return false;
	}

	PhysicsComponent* EnemyComponent::GetPhysicsComponent()
	{
		return m_pPhysicsComponent;
	}

	LadderInfo* EnemyComponent::GetCurrentLadderInfo()
	{
		return m_CurrentLadderInfo;
	}

	Velocity EnemyComponent::GetVelocity()
	{
		return m_pPhysicsComponent->GetVelocity();
	}




}