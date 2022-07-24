#include "pch.h"
#include "GameMode.h"

namespace dae
{



	GameMode::GameMode(GameObject* go):BaseComponent(go)
	{
	}

	GameMode::~GameMode()
	{
	}

	void GameMode::AddBurgerPart(BurgerPartComponent* newPart)
	{
		m_AllBurgerPartComponents.emplace_back(newPart);
	}

	std::vector<BurgerPartComponent*> GameMode::GetAllBurgerParts()
	{
		return m_AllBurgerPartComponents;
	}

}