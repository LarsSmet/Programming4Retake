#pragma once

#include "EnemyComponent.h"

namespace dae
{
	class ClimbingLadderState : public AIState
	{

	public:

		ClimbingLadderState();
	

		virtual void OnEnter(EnemyComponent* comp);

		virtual AIState* Update(EnemyComponent* comp);

		
		
	
		

	private:

		float GetDistance(Point2f p1, Point2f p2);
		LadderInfo* m_CurrentLadderInfo;

		Point2f m_PointToJumpOff;


	};
}

