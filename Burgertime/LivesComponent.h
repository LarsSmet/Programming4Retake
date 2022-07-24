#pragma once
#include "BaseComponent.h"

namespace dae
{

	class LivesComponent final : public BaseComponent
	{

	public:

		LivesComponent(GameObject* go, int lives);
		~LivesComponent();

		void AddLife(int amount);
		void RemoveLife(int amount);
		int GetLives();

	private:


		int m_Lives;


	};

}