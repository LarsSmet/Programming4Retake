#include "pch.h"
#include "MoveState.h"
#include "ClimbingLadderState.h"

namespace dae
{



	MoveState::MoveState() /*m_Speed{1.0f}*/
	{
	}
	void MoveState::OnEnter(EnemyComponent* comp)
	{
		auto posPlayer = comp->GetPlayer()->GetTransformComp().GetPosition();

		auto col = comp->GetPhysicsComponent()->GetColliderComponent()->GetRectCollider();
		
		float speed = 20.0f;

		if (col->left < posPlayer.x)
		{
			comp->SetVelocity(Velocity{ speed, 0.0f });
	
		}
		else if (col->left > posPlayer.x)
		{
			comp->SetVelocity(Velocity{ -speed, 0.0f });
		}

	
	}
	AIState* MoveState::Update(EnemyComponent* comp)
	{

		//handle level col and check if hit ladder -> then switch to state
		comp->HandleLevelCollision();
		
		

		if (comp->LadderCollision())
		{
			//ClimbingLadderState* test =  new ClimbingLadderState();
			
			return new ClimbingLadderState{};
		}
		else
		{
			return nullptr;
		}



		//if no ladder overlap
		//return comp->getstate()
	}




}