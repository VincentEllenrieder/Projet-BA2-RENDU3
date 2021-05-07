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
	vector<Gisement> gisements;
	
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
	
	bool intersect(Gisement otherGisement) const{
		Point c2 = otherGisement.getCentre();
		double r2 = otherGisement.getRayon();
		bool answer = geomod::intersection(centreGisement, c2, rayonGisement, r2);
		return answer;
	}
};

#endif
