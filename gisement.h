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
	
	Point getCentre() const{
		Point c = centreGisement;
		return c;
	}
	
	double getRayon() const{
		double r = rayonGisement;
		return r;
	}
	double getRessource() const{
		double ressource = capaciteGisement;
		return ressource;
	}
	
	void gisementIntersectGisement(Gisement& g) const;
};

namespace gisement {
	vector<Gisement> getGisements();
}
#endif
