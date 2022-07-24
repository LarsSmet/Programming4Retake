#include "pch.h"
#include "ClimbingLadderState.h"
#include "MoveState.h"

namespace dae
{
	//source: https://gameprogrammingpatterns.com/state.html#where-are-the-state-objects

	ClimbingLadderState::ClimbingLadderState() : m_CurrentLadderInfo{ nullptr }
	{

	}


	void ClimbingLadderState::OnEnter(EnemyComponent* comp)
	{
		auto posPlayer = comp->GetPlayer()->GetTransformComp().GetPosition();

		auto col = comp->GetPhysicsComponent()->GetColliderComponent()->GetRectCollider();
		col;

		float speed = 20.0f;

		m_CurrentLadderInfo = comp->GetCurrentLadderInfo();

		std::vector<Point2f> pointsToCheck;
	
		pointsToCheck.emplace_back(m_CurrentLadderInfo->botPoint);
		pointsToCheck.emplace_back(m_CurrentLadderInfo->topPoint);


		for (size_t i = 0; i < m_CurrentLadderInfo->jumpOffPoints.size(); ++i)
		{
			pointsToCheck.emplace_back(m_CurrentLadderInfo->jumpOffPoints[i]);
		}

		size_t indexForCurJumpOff{};
		size_t indexToIgnore{};
		float currentLowestDist{};

		for (size_t j = 0; j < pointsToCheck.size(); ++j)
		{
			if (j == 0)
			{
				currentLowestDist = GetDistance(pointsToCheck[j], Point2f{ col->left, col->bottom });
				indexToIgnore = j;
			}
			else
			{

				if (currentLowestDist >= GetDistance(pointsToCheck[j], Point2f{ col->left, col->bottom }))
				{
					currentLowestDist = GetDistance(pointsToCheck[j], Point2f{ col->left, col->bottom });
					indexToIgnore = j;
				}

			}



		}

		for (size_t k = 0; k < pointsToCheck.size(); ++k)
		{
			if (k != indexToIgnore)
			{

				if (k == 0)
				{
					currentLowestDist = GetDistance(pointsToCheck[k], Point2f{ posPlayer.x, posPlayer.y });
					indexForCurJumpOff = k;
				}
				else
				{

					if (currentLowestDist >= GetDistance(pointsToCheck[k], Point2f{ posPlayer.x, posPlayer.y }))
					{
						currentLowestDist = GetDistance(pointsToCheck[k], Point2f{ posPlayer.x, posPlayer.y });
						indexForCurJumpOff = k;
					}

				}

			}

		}

		m_PointToJumpOff = pointsToCheck[indexForCurJumpOff];

		if (m_PointToJumpOff.y > posPlayer.y)
		{

			comp->SetVelocity(Velocity{ 0, speed });
		}
		else
		{
			comp->SetVelocity(Velocity{ 0, -speed });
		}

		

	}



	AIState* ClimbingLadderState::Update(EnemyComponent* comp)
	{
		//comp->comp
		comp;
		//check first 

		int curClosest = 0; //dont forger also look at velocity
		curClosest;

		auto velocity = comp->GetVelocity();

		if (velocity.y < 1) //going up
		{

			/*for (size_t i = 0; i < m_CurrentLadderInfo->jumpOffPoints.size(); ++i)
			{
				if()
			}*/

		}
		else if (velocity.y > 1)
		{

		}

	


	
			//if ();

			if (comp->GetVelocity().y < 0)
			{
				if (comp->GetPhysicsComponent()->GetColliderComponent()->GetRectCollider()->bottom >= m_PointToJumpOff.y)
				{
					return new MoveState();
				}
			}
			else
			{
				if (comp->GetPhysicsComponent()->GetColliderComponent()->GetRectCollider()->bottom <= m_PointToJumpOff.y)
				{
					return new MoveState();
				}
			}
			
		
		


		return nullptr;
	}

	float ClimbingLadderState::GetDistance(Point2f p1, Point2f p2)
	{
		float x = p1.x - p2.x;
		float y = p1.y - p2.y;

		float sum = (x * x) + (y * y);

		return sqrtf(sum);

	}

	

}