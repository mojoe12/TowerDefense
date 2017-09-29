#include "stdafx.h"
#include "Engine.h"
//#include "SimpleWave.h"
#include <memory>

std::shared_ptr<GraphicLibrary::GraphicStorage> LogicLibrary::Engine::brushSet = nullptr;

LogicLibrary::Engine::Engine()
{
}

LogicLibrary::Engine::Engine(std::shared_ptr<Machine> machi, std::shared_ptr<Wave> wavei, double tii, double mii)
{
	mach = machi;
	wave = wavei;
	time = 0;
	timeIncrement = tii;
	money = mii;
}


LogicLibrary::Engine::~Engine()
{
	// send information back to the user?
	// maybe with a final reportStatus()
	// communicate with display
}

void LogicLibrary::Engine::Update()
{
	time += timeIncrement;
	wave->Update(time);
	mach->Update(time);
	reportStatus();
}

void LogicLibrary::Engine::loadBrushSet(std::shared_ptr<GraphicLibrary::GraphicStorage> gs)
{
	brushSet = gs;
}

void LogicLibrary::Engine::reportStatus() const
{
// use text file or screen to print out current statuses
// or print out money and have the map print out its status
// probably gonna want wave data there too, maybe call that
}

std::shared_ptr<LogicLibrary::Machine> LogicLibrary::Engine::getMachine()
{
	return mach;
}
