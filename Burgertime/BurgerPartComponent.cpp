#include "pch.h"
#include "BurgerPartComponent.h"
#include "GameObject.h"


namespace dae
{
	BurgerPartComponent::BurgerPartComponent(GameObject* go, Point2f pos, float width, float height, CharacterComponent* pCharacter, BaseColliderComponent* level,
		GameMode* gameMode) : BaseComponent(go), m_pPlayerCollider{ pCharacter->GetPhysicsComp()->GetColliderComponent()->GetRectCollider() },
		m_State{BurgerState::normal}, m_pLevel{ level }, m_PreviousYPos{pos.y}, m_pGameMode{gameMode}, m_AmountOfCol{3},
		m_TotalCollider{ new RectangleColliderComponent{ go, false, new Rectf{pos.x, pos.y, width, height} } }, m_GotHitByOtherPart{false}
	{
	
		//m_TotalCollider = new RectangleColliderComponent{ go, false, new Rectf{pos.x, pos.y, width, height} };
		

		for (int i = 0; i < m_AmountOfCol; ++i)
		{
			BurgerPart part;
			Rectf* rectCol = new Rectf{ pos.x + i * (width/ m_AmountOfCol), pos.y, width/ m_AmountOfCol, height };
			auto rectColComp = std::make_shared<RectangleColliderComponent>(go, false, rectCol);
			part.pCollider = rectColComp;
			m_Parts.emplace_back(part);
		
		}
		
	}

	BurgerPartComponent::~BurgerPartComponent()
	{
		delete m_TotalCollider;
		m_TotalCollider = nullptr;
	}


	void BurgerPartComponent::Update(float elapsedSec)
	{
		elapsedSec;
		auto transformComp = m_Owner->GetTransformComp();
		
		transformComp;
	

		if (m_State == BurgerState::falling)
		{
		
			HandleMovement();

			
			for (size_t otherPart = 0; otherPart < m_pGameMode->GetAllBurgerParts().size(); ++otherPart) //can be remnoved, mistake with size
			{
		
				if (m_pGameMode->GetAllBurgerParts()[otherPart] != this)
				{
					if (m_TotalCollider->OnTrigger(m_pGameMode->GetAllBurgerParts()[otherPart]->GetTotalCollider()))
					{
						

						if (m_pGameMode->GetAllBurgerParts()[otherPart]->GetBurgerState() != BurgerState::falling)
						{

							for (int i = 0; i < m_pGameMode->GetAllBurgerParts()[otherPart]->GetAmountOfCol(); ++i)
							{
								
								if (m_TotalCollider->GetRectCollider()->bottom < m_pGameMode->GetAllBurgerParts()[otherPart]->GetTotalCollider()->GetRectCollider()->bottom)
								{
									m_pGameMode->GetAllBurgerParts()[otherPart]->SetHitByOtherPart(true);
								}
							


							}
						}

					}
				}
			}
	
	

		}
		else if (m_State == BurgerState::normal)
		{


			if (m_GotHitByOtherPart == true)
			{
				for (size_t i = 0; i < m_Parts.size(); ++i)
				{

						m_Parts[i].hasBeenWalked = true;
			

				}
			}




	
			for (size_t i = 0; i < m_Parts.size(); ++i)
			{

		

				if (utils::IsOverlapping(*m_Parts[i].pCollider->GetRectCollider(), *m_pPlayerCollider))
				{
					m_Parts[i].hasBeenWalked = true;


				}




			}


			for (size_t i = 0; i < m_Parts.size(); ++i)
			{
				if (m_Parts[i].hasBeenWalked == false)
				{
					break;
				}

				if (i == m_Parts.size() - 1)
				{
					


					SavePreviousYPos();
					//set to burger fall and play sound
					m_State = BurgerState::falling;

		
					auto& mySoundSystem = ServiceLocator::GetSoundSystem();
					mySoundSystem.PlaySound(SoundRequest{ "../Data/DeathSound.wav", 10 });
					

					for (size_t j = 0; j < m_Parts.size(); ++j)
					{
						m_Parts[j].hasBeenWalked = false;
					}

	
				}


			}

		}

	}
	int BurgerPartComponent::GetAmountOfCol() const
	{
		return m_AmountOfCol;
	}
	std::vector<BurgerPart> BurgerPartComponent::GetParts() const
	{
		return m_Parts;
	}
	void BurgerPartComponent::SetState(BurgerState newState)
	{
		m_State = newState;
	}
	RectangleColliderComponent* BurgerPartComponent::GetTotalCollider() const
	{
		return m_TotalCollider;
	}
	void BurgerPartComponent::SetHitByOtherPart(bool value)
	{
		m_GotHitByOtherPart = value;

	}
	void BurgerPartComponent::HandleMovement() //falling movement and check if hit other part
	{
		float speed = 0.3f;

		auto transformComp = m_Owner->GetTransformComp();
	
		transformComp;


		transformComp->Move(0, speed);
		m_TotalCollider->Move(0, speed);


		for (size_t i = 0; i < m_Parts.size(); ++i)
		{
			m_Parts[i].pCollider->Move(0, speed);

			auto colInfo = m_Parts[i].pCollider->OnCollision(m_pLevel);



			if (colInfo.verticalHit)
			{
				
				if (colInfo.hitInfoVertical.intersectPoint.y > m_PreviousYPos)
				{
					m_State = BurgerState::normal;
					m_GotHitByOtherPart = false;
				
				}
			}



		}
	}
	void BurgerPartComponent::SavePreviousYPos()
	{
		auto colInfo = m_Parts[m_Parts.size() -1].pCollider->OnCollision(m_pLevel);


		if (colInfo.verticalHit)
		{

			m_PreviousYPos = colInfo.hitInfoVertical.intersectPoint.y + m_Parts[m_Parts.size() - 1].pCollider->GetRectCollider()->height;

		}

		
	}
	BurgerState BurgerPartComponent::GetBurgerState() const
	{
		return m_State;
	}
}