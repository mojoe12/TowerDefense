#include "stdafx.h"
#include "EngineRunner.h"
#include <mutex>

EngineRunner::EngineRunner(std::shared_ptr<LogicLibrary::Engine> engi, std::shared_ptr<GraphicLibrary::GraphicStorage> gsi) :
	eng(engi),
	gs(gsi)
{
}

EngineRunner::~EngineRunner()
{
}

void EngineRunner::run(MessageQueue mq)
{
	while (true) {
		eng->Update();

		//process message queue
		// trigger gs.draw()
	}
}
