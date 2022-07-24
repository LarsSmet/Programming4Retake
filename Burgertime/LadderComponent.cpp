#include "pch.h"
#include "LadderComponent.h"

namespace dae
{



	LadderComponent::LadderComponent(GameObject* go, std::vector<std::vector<Point2f>> pStartEndVertices, std::vector<std::vector<Point2f>> jumpOffPoints): BaseComponent(go)
	{
		
		for (size_t i = 0; i < pStartEndVertices.size(); ++i)
		{
			//handle height
			Point2f p1 = pStartEndVertices.at(i).at(0);
			Point2f p2 = pStartEndVertices.at(i).at(1);

			float width = 1;
			float height = 1;

			

			auto ladderInfo = std::make_shared<LadderInfo>();

			if (p1.y > p2.y) 
			{
				height = p1.y - p2.y;
				ladderInfo->botPoint = p2;
				ladderInfo->topPoint = p1;
			}
			else if (p2.y > p1.y)
			{
				height = p2.y - p1.y;
				ladderInfo->botPoint = p1;
				ladderInfo->topPoint = p2;
			}
		



			//x doesn't matter because size is 1 anyways
			Rectf* collider = new Rectf{ ladderInfo->botPoint.x, ladderInfo->botPoint.y,width,height };
			ladderInfo->colliderComp = new RectangleColliderComponent{ go, false, collider };

			for (size_t point = 0; point < jumpOffPoints.size(); ++point)
			{
				if (utils::IsPointInRect(jumpOffPoints.at(point).at(0), *collider))
				{
					ladderInfo->jumpOffPoints.emplace_back(jumpOffPoints.at(point).at(0));
					ladderInfo->hasJumpOffPoint = true;
				}

			}


			m_LaddersInfo.emplace_back(ladderInfo);
		}
	}

	LadderComponent::~LadderComponent()
	{

		for (size_t i = 0; i < m_LaddersInfo.size(); ++i)
		{
			delete m_LaddersInfo[i]->colliderComp;
			m_LaddersInfo[i]->colliderComp = nullptr;
		}

	}

	std::vector<std::shared_ptr<LadderInfo>> LadderComponent::GetLaddersInfo()
	{
		return m_LaddersInfo;
	}


}