//simulation.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <vector>
#include "gisement.h"
#include "base.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {
private:
	vector<Base> bases;
	
public:

//--------------------------------------boucle---------------------------------------

	void executeSimulation();
	
//--------------------------------------------lecture----------------------------------
	
	void lecture(char* nomFichier);
	
	void decodageLigne(string line, ifstream& fichier);
		
	void addGisement(double x, double y, double r, double cap);
	
	void addBase(double x, double y, double ressource);
	
	void commAtCenterBase();
	
//----------------------------------------ecriture---------------------------------

	void ecriture(ofstream& sortie);

//--------------------------------------------autres-----------------------------------
	
	void end(ifstream& fichier);
	
	void destroyData();
	
	void drawConnexionRange(bool affiche, bool link);
};

namespace simulation{
	void setWolrd();
	void etatApresNBG(ifstream& fichier);
	void etatApresGisement(ifstream& fichier);
	void etatApresNBB(ifstream& fichier);
	void etatApresBase(ifstream& fichier);
	void etatApresProsp(ifstream& fichier);
	void etatApresForage(ifstream& fichier);
	void etatApresTransp(ifstream& fichier);
	void etatApresComm(ifstream& fichier);
	void successfullRead(ifstream& fichier);
	bool convertStringToBool(string& str);
}

#endif
