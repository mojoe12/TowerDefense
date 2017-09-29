#include "stdafx.h"
#include "Werewolf.h"


// need to connect, see header file

namespace LogicLibrary
{
	const double Werewolf::normalSpeed = 1;
	const double Werewolf::initialHealth = 100;
	const int Werewolf::bitmapIndex = 0;

	Werewolf::Werewolf(Coordinate<double> posi, std::shared_ptr<Machine> machptri) :
		Attacker(posi, machptri, normalSpeed, initialHealth),
		GraphicAttacker(bitmapIndex)
	{
	}

	Werewolf::~Werewolf()
	{
	}

	void Werewolf::Update(double time)
	{
		Attacker::Update(time);
		GraphicAttacker::getState();
		
		const int sizeXinPixels = 10;
		const int sizeYinPixels = 10;
		GraphicAttacker::editBrush(position.X(), position.Y(), sizeXinPixels, sizeYinPixels);

	}
}
