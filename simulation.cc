//simulation.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "simulation.h"

using namespace std;

namespace {
	int etat;
	int i(0), total(0), i_r(0), total_r(0), nbP(0), nbF(0), nbT(0), nbC(0);
	
	enum EtatLecture {NBG, GISEMENTS, NBB, BASES, R_PROSP, R_FORAGE,
					  R_TRANSP, R_COMM};
}

void Simulation::executeSimulation() {
	for (int i(0); i >= 0; ++i) {
		
		for (size_t k(0); k < bases.size(); ++k) {
			bool autonome = bases[k].arret();
			if (autonome == false) {
				for (size_t l(0); l < bases.size(); ++l) {
					bases[k].updateAdjacence(bases[k].getRobots(),
											 bases[l].getRobots());
				}
				bases[k].connexion();
				bases[k].maintenance();
				bases[k].creation();
				bases[k].updateRemote();
				bases[k].updateAutonomous();
				bases[k].updateMoney();
				if (bases[k].destroyBase() == true) bases[k].~Base();
			}
		}
	}
}

void Simulation::lecture(char* nomFichier){
    string line;
    ifstream fichier(nomFichier);
    geomod::setMax(dim_max);
    if(!fichier.fail()) {
        while(getline(fichier >> ws,line)) {
			if(line[0]=='#') continue;  
			Simulation::decodageLigne(line, fichier);
        }
		Simulation::commAtCenterBase();
		simulation::successfullRead(fichier);
	}
	else end(fichier);
}

void Simulation::decodageLigne(string line, ifstream& fichier) {
	istringstream data(line);		
	double x, y, r, cap, ressource, dp, xb, yb, xg, yg, rayong, capaciteg;
	int uid;
	string sAtteint, sRetour, sFound;
	switch(etat) {
		case NBG:
			if(!(data >> total)) end(fichier);
			simulation::etatApresNBG(fichier);
			break;
		
		case GISEMENTS:
			if(!(data >> x >> y >> r >> cap)) end(fichier);
			else ++i;
			Simulation::addGisement(x, y, r, cap);
			simulation::etatApresGisement(fichier);
			break;

		case NBB:
			if(!(data >> total)) end(fichier);
			else i = 0;
			simulation::etatApresNBB(fichier);
			break;

		case BASES:
			if(!(data >> x >> y >> ressource >> nbP >> nbF >> nbT >> nbC)) {
				end(fichier);
			} else ++i;
			Simulation::addBase(x, y, ressource);
			simulation::etatApresBase(fichier);
			break;
			
		case R_PROSP: {
			if(!(data >> uid >> dp >> x >> y >> xb >> yb >> sAtteint >> sRetour >> 
				 sFound)) end(fichier);
			else ++i_r;
			bool atteint = simulation::convertStringToBool(sAtteint);
			bool retour = simulation::convertStringToBool(sRetour);
			bool found = simulation::convertStringToBool(sFound);
			if (found == true){
				if(!(data >> xg >> yg >> rayong >> capaciteg)) end(fichier);
				else bases[i-1].addProsp(uid, dp, x, y, xb, yb, atteint, retour,
										 found, xg, yg, rayong, capaciteg);
			} else bases[i-1].addProsp(uid, dp, x, y, xb, yb, atteint, retour, found);
			simulation::etatApresProsp(fichier);
		}
		break;
		
		case R_FORAGE: {
			if(!(data >> uid >> dp >> x >> y >> xb >> yb >> sAtteint)) {
				end(fichier);
			} else ++i_r;
			bool atteint = simulation::convertStringToBool(sAtteint);
			bases[i-1].addForage(uid, dp, x, y, xb, yb, atteint);
			simulation::etatApresForage(fichier);
		}
		break;
		
		case R_TRANSP: {
			if(!(data >> uid >> dp >> x >> y >> xb >> yb >> sAtteint >> sRetour)) {
				end(fichier);
			} else ++i_r;
			bool atteint = simulation::convertStringToBool(sAtteint);
			bool retour = simulation::convertStringToBool(sRetour);
			bases[i-1].addTransp(uid, dp, x, y, xb, yb, atteint, retour);
			simulation::etatApresTransp(fichier);
		}
		break;
		
		case R_COMM: {
			if(!(data >> uid >> dp >> x >> y >> xb >> yb >> sAtteint)) {
				end(fichier);
			} else ++i_r;
			bool atteint = simulation::convertStringToBool(sAtteint);
			bases[i-1].addComm(uid, dp, x, y, xb, yb, atteint);
			simulation::etatApresComm(fichier);
		}
		break;	
	}
}


void Simulation::addBase(double x, double y, double ressource) {				 
	Point c = geomod::setPoint(x, y);
	Base newBase(c, ressource);
	
	for(size_t i(0); i < bases.size(); ++i) {
		if (bases[i].intersectBase(newBase) == true) {
			double x1 = (newBase.getCentre()).x;
			double y1 = (newBase.getCentre()).y;
			double x2 = (bases[i].getCentre()).x;
			double y2 = (bases[i].getCentre()).y;
			cout << message::base_superposition(x1, y1, x2, y2);
		}
	newBase.intersectGisement();
	}
	bases.push_back(newBase);
}

void Simulation::addGisement(double x, double y, double r, double cap) {
	Point c = geomod::setPoint(x, y);
	Gisement newGisement(c, r, cap);
	newGisement.gisementIntersectGisement(newGisement);
}


void Simulation::commAtCenterBase() {
	for(size_t i(0); i < bases.size(); ++i) {
		if ((bases[i].getCommAtCenter()) == false) {
			double x1 = (bases[i].getCentre()).x;
			double y1 = (bases[i].getCentre()).y;
			cout << message::missing_robot_communication(x1, y1);
		}
	}
}

void Simulation::end(ifstream& fichier) {
	fichier.close();
	destroyData();
}

void Simulation::destroyData() {
	gisement::destroyGisements();
	for(size_t i(0); i < bases.size(); ++i) { 
		bases[i].destroyRobots();
	}
	bases.clear();
}

void simulation::setWolrd() {
	geomod::setMax(dim_max);
}

void simulation::etatApresNBG(ifstream& fichier) {
	if(total == 0) etat = NBB;
	else etat = GISEMENTS;
}

void simulation::etatApresGisement(ifstream& fichier) {
	if(i == total) etat = NBB;
}

void simulation::etatApresNBB(ifstream& fichier) {
	etat = BASES;
}

void simulation::etatApresBase(ifstream& fichier) {
	if(nbP != 0) {
		etat = R_PROSP;
		total_r = nbP;
		i_r = 0;
	} else {
		if (nbF != 0) {
			etat = R_FORAGE;
			total_r = nbF;
			i_r = 0;
		} else {
			if (nbT != 0) {
				etat = R_TRANSP;
				total_r = nbT;
				i_r = 0;
			} else {
				if (nbC != 0) {
					etat = R_COMM;
					total_r = nbC;
					i_r = 0;
				}
			}
		}
	}
}

void simulation::etatApresProsp(ifstream& fichier) {
	if (i_r == total_r) {
		if (nbF != 0) {
			etat = R_FORAGE;
			total_r = nbF;
			i_r = 0;
		} else {
			if (nbT != 0) {
				etat = R_TRANSP;
				total_r = nbT;
				i_r = 0;
			} else {
				if (nbC != 0) {
					etat = R_COMM;
					total_r = nbC;
					i_r = 0;
				} else {
					if (i != total) etat = BASES;
				}
			}
		}
	}
}

void simulation::etatApresForage(ifstream& fichier) {
	if (i_r == total_r) {
		if (nbT != 0) {
			etat = R_TRANSP;
			total_r = nbT;
			i_r = 0;
		} else {
			if (nbC != 0) {
				etat = R_COMM;
				total_r = nbC;
				i_r = 0;
			} else {
				if (i != total) etat = BASES;
			}
		}
	}
}

void simulation::etatApresTransp(ifstream& fichier) {
	if (i_r == total_r) {	
		if (nbC != 0) {
			etat = R_COMM;
			total_r = nbC;
			i_r = 0;
		} else {
			if (i != total) etat = BASES;
		}
	}
}

void simulation::etatApresComm(ifstream& fichier) {
	if (i_r == total_r) {	 
		if (i != total) etat = BASES;
	}
}

void simulation::successfullRead(ifstream& fichier) {
	fichier.close();
	cout << message::success();
}

bool simulation::convertStringToBool(string& str) {
	if (str == "true") return true;
	else return false;
}


