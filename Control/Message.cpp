#include "stdafx.h"
#include "Message.h"
#include <memory>
#include "Tower.h"


Message::Message()
{
	shouldChangeTime = false;
	shouldBuild = false;
}

Message::Message(bool ict)
{
	shouldChangeTime = ict;
	shouldBuild = false;
}

Message::Message(bool ict, bool ib, std::shared_ptr<LogicLibrary::Tower> tower)
{
	shouldChangeTime = ict;
	shouldBuild = ib;
	newTower = tower;
}

void Message::place(LogicLibrary::Coordinate<int> pos)
{
	position = pos;
}

bool Message::ifChangeTime()
{
	return shouldChangeTime;
}

bool Message::ifBuild()
{
	return shouldBuild;
}

std::shared_ptr<LogicLibrary::Tower> Message::getTower()
{
	return newTower;
}

LogicLibrary::Coordinate<int> Message::getPosition()
{
	return position;
}


Message::~Message()
{
}
