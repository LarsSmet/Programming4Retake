#pragma once
#include <BaseComponent.h>
#include "MiniginPCH.h"
#include <utils.h>
#include <RectangleColliderComponent.h>

namespace dae
{

	struct LadderInfo
	{
		RectangleColliderComponent* colliderComp;
		Point2f botPoint;
		Point2f topPoint;
		std::vector<Point2f> jumpOffPoints;
		bool hasJumpOffPoint = false;

		~LadderInfo()
		{
			
		}
	};

	class LadderComponent final : public BaseComponent
	{
	public:
		LadderComponent(GameObject* go, std::vector<std::vector<Point2f>> pStartEndVertices, std::vector<std::vector<Point2f>> jumpOffPoints);
		~LadderComponent();

		std::vector<std::shared_ptr<LadderInfo>> GetLaddersInfo();

	private:

		
		std::vector<std::shared_ptr<LadderInfo>> m_LaddersInfo;

	};

}

