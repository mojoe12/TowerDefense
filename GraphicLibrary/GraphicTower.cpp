#include "stdafx.h"
#include "GraphicTower.h"


namespace GraphicLibrary
{
	GraphicTower::GraphicTower()
	{
	}

	GraphicTower::GraphicTower(int bmi)
	{
		bitmapIndex = bmi;
	}


	GraphicTower::~GraphicTower()
	{
	}

	void GraphicTower::getState()
		// should probably add parameters so i can actually have triggered or posttrigger states
	{
		buildState = BuildState::Built;
		fireState = FireState::Inactive;
	}

}