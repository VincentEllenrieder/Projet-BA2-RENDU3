//gisement.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <vector>
#include <iostream>
#include "geomod.h"
#include "constantes.h"
#include "message.h"

using namespace std;

#ifndef GISEMENT_H
#define GISEMENT_H

class Gisement {
private:
	Point centreGisement;
	double rayonGisement;
	double capaciteGisement;
	
public:
	Gisement(Point c, double r, double cap) 
	: centreGisement(c), rayonGisement(r), capaciteGisement(cap)
	{}
	
	Point getCentreGisement() const {return centreGisement;}
	
	double getRayon() const {return rayonGisement;}
	
	double getRessource() const {return capaciteGisement;}
	
	void setRessource(double ressource) {capaciteGisement = ressource;}
		
	void gisementIntersectGisement(Gisement& g) const;
	
	void lostRessources();
};

namespace gisement {
	vector<Gisement> getGisements ();
	void destroyGisements();
}

#endif
