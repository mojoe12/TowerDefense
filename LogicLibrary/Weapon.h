#pragma once
#include "MapObject.h"
#include "Coordinate.h"

namespace LogicLibrary
{

	class Weapon :
		public MapObject
	{
	public:
		Weapon(Coordinate<double>, std::shared_ptr<Machine>, Coordinate<double>);
		~Weapon();
		virtual void Update(double) override;

	protected:
		virtual bool ifTriggered() = 0;
		virtual void Trigger() = 0;
		void updatePosition(double);
	private:
		Coordinate<double> velocity;
		Coordinate<double> lastPosition;
		double lastTime;
	};


}