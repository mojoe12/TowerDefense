#pragma once

#include "MessageQueue.h"
#include "Engine.h"

class EngineRunner
{
public:
	EngineRunner(std::shared_ptr<LogicLibrary::Engine>, std::shared_ptr<GraphicLibrary::GraphicStorage>);
	~EngineRunner();

	void run(MessageQueue);

private:
	std::shared_ptr<LogicLibrary::Engine> eng;
	std::shared_ptr<GraphicLibrary::GraphicStorage> gs;

};

