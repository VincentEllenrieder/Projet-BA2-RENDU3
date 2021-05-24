//projet.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale	

#include <iomanip>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char* argv[]) {
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	
	MyEvent win;
	win.set_title("Planet Donut");
	win.set_default_size(1200,800);
	if (argc == 1) {
		MyArea myArea;
		win.add(myArea);
		myArea.show();
	}
	if (argc == 2) { 
		Simulation goSimulation;
		simulation::setWolrd();
		goSimulation.lecture(argv[1]);
	}
	return app->run(win); 
}
	
	
	
	
	
	
	
	
	



