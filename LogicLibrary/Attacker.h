#pragma once
#include "MapObject.h"
#include "PathObject.h"

namespace LogicLibrary
{
	class Attacker :
		public MapObject
	{
	public:
		Attacker(LogicLibrary::Coordinate<double>, std::shared_ptr<Machine>, double, double);
		virtual void Update(double);
		void loseHealth(double);

	protected:
		double getCurrentSpeed() const;
		void updatePath();
		LogicLibrary::Coordinate<double> getDirection() const;
		void checkDeath();
	private:
		double lastTime;
		LogicLibrary::Coordinate<double> lastPosition;
		std::shared_ptr<PathObject> path;
		double health;
		double normalSpeed;

	};
}