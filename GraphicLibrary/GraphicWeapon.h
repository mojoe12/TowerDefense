#pragma once
#include "AnimatedBitmapObject.h"

namespace GraphicLibrary
{
	enum class TriggerState {
		PreTrigger,
		Triggered,
		PostTrigger
	};

	class GraphicWeapon :
		public AnimatedBitmapObject
	{
	public:
		GraphicWeapon();
		GraphicWeapon(int);
		~GraphicWeapon();
		void getState() override; 
		TriggerState currentstate;

	private:
		int bitmapIndex;

	};


}