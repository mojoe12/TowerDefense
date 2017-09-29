#include "stdafx.h"
#include "SimpleEngine.h"
#include "SimpleWave.h"
#include "LandmineBuilder.h"
#include "Road.h"

static const double ti0 = 1;
static const double mi0 = 100;

//make functions static

// one thing concerns dr. dong
// modify engine constructors to have an initialize functions 
// protected acccessors and setters vs private data


// driver not engine

using cellmap = std::vector<std::vector<std::shared_ptr<Cell>>>;

SimpleEngine::SimpleEngine() :
{
	// why is all this data being made in one place?
	// well im glad you asked, me
	// allocating a ton of data simult.ly will
	// save cache-switching time

	Machine machine = Machine();
	std::shared_ptr<Machine> machptr = std::make_shared<Machine>(machine);

	SimpleWave wave = SimpleWave(machptr);
	std::shared_ptr<Wave> waveptr = std::make_shared<Wave>(wave);

	Coordinate<double> towerpos(1, 2);
	LandmineBuilder tower = LandmineBuilder(towerpos, machptr);
	std::shared_ptr<Tower> towerptr = std::make_shared<Tower>(tower);
	machine.addTower(towerptr);

	int gameheight = 4, gamewidth = 4;
	cellmap cells = cellmap (gameheight);
	for (int i = 0; i < gameheight; i++) {
		for (int j = 0; j < gamewidth; j++) {
			Coordinate<double> position(i, j);
			Road newterr = Road(position, machptr, true, true);
			Cell newcell = Cell(i, j, std::make_shared<Terrain>(newterr));
			cells[i].push_back(std::make_shared<Cell>(newcell));
		}
	}

	Map map = Map(cells);
	std::shared_ptr<Map> mapptr = std::make_shared<Map>(map);
	machine.setMap(mapptr);

	//make mossible paths

	//make it so that the cells get what they need

}



SimpleEngine::~SimpleEngine()
{
}
