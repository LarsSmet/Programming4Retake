#pragma once
#include "Command.h"
#include "CharacterComponent.h"

namespace dae
{

	class MoveCommand : public Command
	{
	public:

		


		MoveCommand(CharacterComponent* characterComp, float xSpeed, float ySpeed) : m_CharacterComp{ characterComp }, m_Velocity { xSpeed, ySpeed }
		{

		};



		~MoveCommand() {};

		void Execute() //in my game you dont have diagonal player movement, so no need to do extra checks for that
		{
		


			LadderInfo ladderInfo;
			ladderInfo;
			bool isCollidingWithLadder = m_CharacterComp->LadderCollision(ladderInfo);

			isCollidingWithLadder;
			auto yPosCharacter = m_CharacterComp->GetPhysicsComp()->GetColliderComponent()->GetRectCollider()->bottom + 17 /*+ 16*/; //plus 16 because bottom is actually left top
			yPosCharacter;
			auto yPosLadderTop = ladderInfo.botPoint.y;
			auto yPosLadderBot =  ladderInfo.topPoint.y;
		
			yPosLadderBot;
			yPosLadderTop;


			auto physComp = m_CharacterComp->GetPhysicsComp();

			

			if (isCollidingWithLadder)
			{
			
				if(yPosCharacter >= yPosLadderBot)
				{
				
					if (m_Velocity.y < 0)
					{
						m_CharacterComp->SetState(State::UsingLadder);
						physComp->SetVelocity(m_Velocity);
					}
					else if (m_Velocity.y > 0)
					{
						m_CharacterComp->SetState(State::CanGrabLadder);
					}
					else if (m_Velocity.y == 0)
					{
						physComp->SetVelocity(m_Velocity);
						m_CharacterComp->SetState(State::CanGrabLadder);
					}


				}
				else if (yPosCharacter-2 <= yPosLadderTop)
				{
					


					if (m_Velocity.y < 0)
					{
						m_CharacterComp->SetState(State::CanGrabLadder);
					}
					else if (m_Velocity.y > 0)
					{
						m_CharacterComp->SetState(State::UsingLadder);
						physComp->SetVelocity(m_Velocity);
					}
					else if (m_Velocity.y == 0)
					{
						physComp->SetVelocity(m_Velocity);
						m_CharacterComp->SetState(State::CanGrabLadder);
					}
				}

				else if (m_Velocity.x == 0 )
				{

					m_CharacterComp->SetState(State::UsingLadder);
					physComp->SetVelocity(m_Velocity);
				}

				else if (ladderInfo.hasJumpOffPoint) 
				{
					if(m_Velocity.y == 0)
					{ 

						for (size_t i = 0; i < ladderInfo.jumpOffPoints.size(); ++i)
						{

							if (yPosCharacter == ladderInfo.jumpOffPoints[i].y)
							{
								m_CharacterComp->SetState(State::CanGrabLadder);
								physComp->SetVelocity(m_Velocity);
							}

						}
					}

				}
			
			}
			else
			{
				m_CharacterComp->SetState(State::Normal);
				if (m_Velocity.y == 0)
				{
					physComp->SetVelocity(m_Velocity);
				}
			}






		}




		

		

	private:


		

		Velocity m_Velocity;
		CharacterComponent* m_CharacterComp;


	};




	class PlayerDeathCommand : public Command
	{
	public:

		PlayerDeathCommand(PlayerComponent& playerComp) : m_PlayerComp{ playerComp } {}
		void Execute()
		{
			m_PlayerComp.KillPlayer();

		}


	private:

		PlayerComponent& m_PlayerComp;


	};

	class EnemyDeathCommand : public Command
	{
	public:

		EnemyDeathCommand(PlayerComponent& playerComp) : m_PlayerComp{ playerComp } {}
		void Execute()
		{
			m_PlayerComp.AddPoints(100, Event::EnemyDied);
			auto& mySoundSystem = ServiceLocator::GetSoundSystem();
			mySoundSystem.PlaySound(SoundRequest{ "../Data/DeathSound.wav", 10 });
			

		}


	private:

		PlayerComponent& m_PlayerComp;


	};


	class BurgerDropCommand : public Command
	{
	public:

		BurgerDropCommand(PlayerComponent& playerComp) : m_PlayerComp{ playerComp } {}
		void Execute()
		{
			m_PlayerComp.AddPoints(50, Event::BurgerDropped);
		}


	private:

		PlayerComponent& m_PlayerComp;


	};



	class JumpCommand : public Command
	{
	public:
		void Execute()
		{
			//std::cout << "Jump";
		}
	};

	class FireCommand : public Command
	{
	public:
		void Execute()
		{
			//std::cout << "Fire";
		}
	};

	class DuckCommand : public Command
	{
	public:
		void Execute()
		{
			//std::cout << "Duck";
		}
	};

	class FartCommand : public Command
	{
	public:
		void Execute()
		{
			//std::cout << "Fart";
		}
	};

}


//m_CharacterComp->SetState(State::Normal);

//if (isCollidingWithLadder)
//{


//	m_CharacterComp->SetState(State::OnLadder);

//	if ((yPosCharacter == yPosLadderBot) && (m_Velocity.y >= 0))//can be made to <= if needed
//	{
//		m_CharacterComp->SetState(State::UsingLadder);
//		
//		//if vertical movement is not downwards(standing on bot of ladder)
//		
//		physComp->SetVelocity(m_Velocity);
//		physComp->GetColliderComponent()->SetPosition(physComp->GetColliderComponent()->GetPosition().x, physComp->GetColliderComponent()->GetPosition().y - 1); //-1 cuz flip
//		m_CharacterComp->GetTransformComp().SetPosition(m_CharacterComp->GetTransformComp().GetPosition().x, m_CharacterComp->GetTransformComp().GetPosition().y -1);


//		//physComp->SetVelocity(m_Velocity);
//		//physComp->GetColliderComponent()->SetPosition(physComp->GetColliderComponent()->GetPosition().x, physComp->GetColliderComponent()->GetPosition().y + 1); //-1 cuz flip
//		//m_CharacterComp->GetTransformComp().SetPosition(m_CharacterComp->GetTransformComp().GetPosition().x, m_CharacterComp->GetTransformComp().GetPosition().y + 1);

//			
//			std::cout << "called inside firs tif" << physComp->GetColliderComponent()->GetPosition().y;
//		
//	}
//	else if ((yPosCharacter == yPosLadderTop) && (m_Velocity.y <= 0))
//	{
//		//if vertical movement is not upwards(standing on top of ladder)
//		if (m_Velocity.x == 0)
//		{
//			m_CharacterComp->SetState(State::UsingLadder);
//		}
//		else
//		{
//			m_CharacterComp->SetState(State::Normal);
//		}

//			m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//		
//	}
//	else if(m_Velocity.x == 0) //on ladder
//	{
//		m_CharacterComp->SetState(State::UsingLadder);
//		m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//	}



//

//}
//else if(m_Velocity.y == 0)
//{
//	m_CharacterComp->SetState(State::Normal);
//	m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//	
//}

//if is on ladder && speedy > 0 
//new with states
/*	if (m_CharacterComp->GetState() != State::UsingLadder)
	{
		if (m_CharacterComp->LadderCollision(ladderInfo))
		{

			m_CharacterComp->SetState(State::CanGrabLadder);



			m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
		}
	}
	else */

//if (m_CharacterComp->GetState() == State::CanGrabLadder || m_CharacterComp->GetState() == State::Normal)
//{
//	if (isCollidingWithLadder == false)
//	{
//		m_CharacterComp->SetState(State::Normal);
//	}
//	else
//	{
//		m_CharacterComp->SetState(State::CanGrabLadder);
//	}
//}
//
//if (m_CharacterComp->GetState() == State::UsingLadder)
//{
//
//
//
//	if ((yPosCharacter == yPosLadderBot) && (m_Velocity.y >= 0))//can be made to <= if needed
//	{
//		m_CharacterComp->SetState(State::CanGrabLadder);
//
//		std::cout << "called";
//
//		//if vertical movement is not downwards(standing on bot of ladder)
//
//		physComp->SetVelocity(m_Velocity);
//		physComp->GetColliderComponent()->SetPosition(physComp->GetColliderComponent()->GetPosition().x, physComp->GetColliderComponent()->GetPosition().y/* - 1*/); //-1 cuz flip
//		m_CharacterComp->GetTransformComp().SetPosition(m_CharacterComp->GetTransformComp().GetPosition().x, m_CharacterComp->GetTransformComp().GetPosition().y /*1*/);
//
//
//	}
//	else if ((yPosCharacter == yPosLadderTop) && (m_Velocity.y <= 0))
//	{
//		m_CharacterComp->SetState(State::CanGrabLadder);
//		physComp->SetVelocity(m_Velocity);
//		physComp->GetColliderComponent()->SetPosition(physComp->GetColliderComponent()->GetPosition().x, physComp->GetColliderComponent()->GetPosition().y /*- 1*/); //-1 cuz flip
//		m_CharacterComp->GetTransformComp().SetPosition(m_CharacterComp->GetTransformComp().GetPosition().x, m_CharacterComp->GetTransformComp().GetPosition().y /*- 1*/);
//	}
//	else if (m_Velocity.x == 0)
//	{
//		m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//	}
//
//}
//else if (m_CharacterComp->GetState() == State::Normal)
//{
//	if (m_Velocity.y == 0)
//	{
//		m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//	}
//}
//else if (m_CharacterComp->GetState() == State::CanGrabLadder)
//{
//	if (m_Velocity.x == 0)
//	{
//		m_CharacterComp->SetState(State::UsingLadder);
//	}
//	else if (m_Velocity.y == 0)
//	{
//		m_CharacterComp->SetState(State::CanGrabLadder);
//	}
//	m_CharacterComp->GetPhysicsComp()->SetVelocity(m_Velocity);
//}