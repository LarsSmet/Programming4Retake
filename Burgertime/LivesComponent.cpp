#include "pch.h"
#include "LivesComponent.h"

namespace dae
{

	LivesComponent::LivesComponent(GameObject* go, int lives) : BaseComponent{go}, m_Lives { lives }
	{

	}

	LivesComponent::~LivesComponent()
	{

	}

	void LivesComponent::AddLife(int amount)
	{
		m_Lives += amount;
	}
	void LivesComponent::RemoveLife(int amount)
	{
		m_Lives -= amount;
	}
	int LivesComponent::GetLives()
	{
		return m_Lives;
	}



}