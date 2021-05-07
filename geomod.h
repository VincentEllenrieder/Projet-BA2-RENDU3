//geomod.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include "constantes.h"

#ifndef GEOMOD_H
#define GEOMOD_H

struct Point {
	double x;
	double y;
};

struct Vecteur {
	double norme;
	double hori;
	double vert;
	
};

namespace geomod {
	double setMax(double m);
	double getMax();
	double getEpsilonZero();
	Point setPoint(double x, double y);
	Point normalise(Point p2D);
	double normalise(double v);
	Vecteur shortestWay(Point a, Point b);
	bool samePoint(Point a, Point b);
	bool belong(Point a, Point b, double rayon);
	bool intersection(Point a, Point b, double r1, double r2);
}

#endif
