//projet.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale	

#include <iomanip>
#include "simulation.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 2) exit(0);
	else { 
		Simulation goSimulation;
		goSimulation.lecture(argv[1]);
		goSimulation.executeSimulation();
	}
	
}
 
	
	
	
	
	
	
	
	
	



