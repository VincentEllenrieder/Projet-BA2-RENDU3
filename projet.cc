//projet.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale	

#include <iomanip>
#include "simulation.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc == 1) {
		
	}
	if (argc == 2) { 
		Simulation goSimulation;
		simulation::setWolrd();
		goSimulation.lecture(argv[1]);
		goSimulation.executeSimulation();
	}
}
 
	
	
	
	
	
	
	
	
	



