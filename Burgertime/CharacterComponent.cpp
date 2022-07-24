#include "pch.h"
//#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "GameObject.h"
#include <InputManager.h>


namespace dae
{

	CharacterComponent::CharacterComponent(GameObject* go, PhysicsComponent* physicsComp, int ammo, BaseColliderComponent* level, LadderComponent* ladders)
		: BaseComponent{ go }, m_pPhysicsComponent{ physicsComp }, m_Ammo{ ammo }, m_pLevel{ level }, m_LaddersInfo{ ladders->GetLaddersInfo() }
	{
		m_pTransformComp = go->GetTransformComp();
		m_State = State::UsingLadder;
	}



	CharacterComponent::~CharacterComponent()
	{


		delete m_pPhysicsComponent;
		m_pPhysicsComponent = nullptr;


	}

	bool CharacterComponent::LadderCollision(LadderInfo& ladderInfo)
	{
		auto colComp = m_pPhysicsComponent->GetColliderComponent();

		for (size_t i = 0; i < m_LaddersInfo.size(); ++i)
		{
		


			if (colComp->OnTrigger(m_LaddersInfo[i]->colliderComp)) //return bool
			{
				ladderInfo = *m_LaddersInfo[i]; //ladderinfo always stays the same

				return true;
			}


		}

		return false;
	}

	void CharacterComponent::Update(float elapsedSec)
	{


		auto transformComp = m_Owner->GetTransformComp();
		auto colComp = m_pPhysicsComponent->GetColliderComponent();


		InputManager& inputManager = InputManager::GetInstance();

		
		if (!inputManager.IsPressed(int(ControllerButton::ArrowLeft)) && !inputManager.IsPressed(int(ControllerButton::ArrowRight)))
		{

			m_pPhysicsComponent->SetXVelocity(0);
		}

		if (!inputManager.IsPressed(int(ControllerButton::ArrowUp)) && !inputManager.IsPressed(int(ControllerButton::ArrowDown)))
		{

			m_pPhysicsComponent->SetYVelocity(0);
		}

	
			


		if (m_State != State::UsingLadder)
		{
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
				

				}
				else if (colInfo.rightHit)
				{
					transformComp->SetPosition(transformComp->GetPosition().x - 1, transformComp->GetPosition().y);
					colComp->SetPosition(colComp->GetPosition().x - 1, colComp->GetPosition().y);
				
				}

			
			}

		}
		
		m_pPhysicsComponent->Update( elapsedSec);


	}

	void CharacterComponent::SpawnPepperCloud(glm::vec2 pos)
	{
		GameObject* test = new GameObject{100.f,20.f};
		
		test;
		pos;
	}

	PhysicsComponent* CharacterComponent::GetPhysicsComp()
	{
		return m_pPhysicsComponent;
	}

	TransformComponent& CharacterComponent::GetTransformComp()
	{
		// TODO: insert return statement here
		return *m_pTransformComp;
	}

	void CharacterComponent::SetState(State newState)
	{
		m_State = newState;

	}



	State CharacterComponent::GetState()
	{
		return m_State;

	}

}
