#include "stdafx.h"
#include "Attacker.h"
#include "Machine.h"
#include "Terrain.h"
#include "Map.h"

namespace LogicLibrary
{

	Attacker::Attacker(Coordinate<double> positioni, std::shared_ptr<Machine> machptri, double speedi, double healthi)
		: MapObject(positioni, machptri),
		lastTime(0),
		lastPosition(positioni),
		path(nullptr),
		health(healthi),
		normalSpeed(speedi)
	{
	}

	void Attacker::Update(double time)
	{
		updatePath();
		double speed = getCurrentSpeed();
		Coordinate<double> direc = getDirection();
		Coordinate<double> velo = Coordinate<double>(direc.X() * speed, direc.Y() * speed);

		double timedelta = time - lastTime;
		Coordinate<double> positiondelta = Coordinate<double>(velo.X() * timedelta, velo.Y() * timedelta);
		position = Coordinate<double>(position.X() + positiondelta.X(), position.Y() + positiondelta.Y());

		lastTime = time;
		lastPosition = position;



	}

	double Attacker::getCurrentSpeed() const
	{
		int terrainSpeed = 0;
		Coordinate<int> indices = Coordinate<int>(position);

		double terrMult = (machptr->getTerrainAt(indices.X(), indices.Y())).getSpeed();
		return terrMult * normalSpeed;
	}

	void Attacker::updatePath()
	{
		path = machptr->getPath(std::make_shared<Attacker>(*this));
	}

	Coordinate<double> Attacker::getDirection() const
	{
		Coordinate<int> nextsquare = path->getNext();
		Coordinate<double> nextspot(nextsquare.X() + .5, nextsquare.Y() + .5);

		double x = nextspot.X() - getPosition().X();
		double y = nextspot.Y() - getPosition().Y();
		double angle = atan2(y, x);
		Coordinate<double> direc(cos(angle), sin(angle));
		return direc;
	}

	void Attacker::loseHealth(double lostHealth)
	{
		health -= lostHealth;
		checkDeath();
	}

	void Attacker::checkDeath()
	{
		if (health < 0) {
			machptr->dltAttacker(std::shared_ptr<Attacker>(this));
			this->~Attacker();
		}
	}

}