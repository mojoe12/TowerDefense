#pragma once
#include "Coordinate.h"
#include <memory>
#include "Tower.h"

class Message
{
public:
	Message();
	Message(bool);
	Message(bool, bool, std::shared_ptr<LogicLibrary::Tower>);

	void place(LogicLibrary::Coordinate<int> pos);

	bool ifChangeTime();
	bool ifBuild();
	std::shared_ptr<LogicLibrary::Tower> getTower();
	LogicLibrary::Coordinate<int> getPosition();

	~Message();

private:
	bool shouldChangeTime;
	bool shouldBuild;
	LogicLibrary::Coordinate<int> position;
	std::shared_ptr<LogicLibrary::Tower> newTower;
};

