#pragma once

#include "EnemyComponent.h"

namespace dae
{
	class MoveState : public AIState
	{

	public:

		MoveState();

		
		virtual void OnEnter(EnemyComponent* comp);


		virtual AIState* Update(EnemyComponent* comp);
	


	private:

		

	};

}

