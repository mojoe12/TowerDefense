#include "stdafx.h"
#include "GraphicWeapon.h"


namespace GraphicLibrary
{
	GraphicWeapon::GraphicWeapon()
	{
	}

	GraphicWeapon::GraphicWeapon(int bmi)
	{
		bitmapIndex = bmi;
	}


	GraphicWeapon::~GraphicWeapon()
	{
	}

	void GraphicWeapon::getState()
		// should probably add parameters so i can actually have triggered or posttrigger states
	{
		currentstate = TriggerState::PreTrigger;
	}

}