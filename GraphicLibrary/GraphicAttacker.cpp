#include "stdafx.h"
#include "GraphicAttacker.h"

namespace GraphicLibrary
{

	GraphicAttacker::GraphicAttacker()
	{
	}


	GraphicAttacker::GraphicAttacker(int bmi)
	{
		bitmapIndex = bmi;
	}

	GraphicAttacker::~GraphicAttacker()
	{
	}

	void GraphicAttacker::getState()
		// should probably add parameters so i can actually have triggered or posttrigger states
		// im just dumb cause i used override
	{
		direction = Direction::Left;
		footFirst = FootFirst::Right;
	}

	void GraphicAttacker::editBrush(/*std::shared_ptr<GraphicStorage> gs,*/ int placeAtx, int placeAty, int finalSizex, int finalSizey)
	{
		//gs->getBrush(bitmapIndex)->SetTransform();
	}

}