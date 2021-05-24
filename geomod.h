//geomod.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include "constantes.h"
#include "graphic.h"

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
	void rebouclementBase(double x, double y, double rayon, int couleur);
	void rebouclementGisement(double x, double y, double rayon);
	void range(double c1, double c2, double rayon, bool range);
	void link(double c1, double c2, double c3, double c4, bool link);
}

class Cercle {
	private:
		double CentreX;
		double CentreY;
	public:
		Cercle(double cx, double cy)
		:CentreX(cx), CentreY(cy)
		{}
		double getCentreX() {return CentreX;}
		double getCentreY() {return CentreY;}
};

class CercleG : public Cercle {
	private:
		double rayon;
	public:
		CercleG(double cx, double cy, double r)
		:Cercle(cx, cy), rayon(r)
		{}
		void dessinGisement();
};

class CercleB : public Cercle {
	private:
		double rayon;
		int couleur;
	public:
		CercleB(double cx, double cy, double r, int cl)
		:Cercle(cx, cy), rayon(r), couleur(cl)
		{}
		void dessinBase(int couleur);
};

class CercleR : public Cercle {
	private:
		int couleur;
	public:
		CercleR(double cx, double cy, int cl)
		:Cercle(cx, cy), couleur(cl)
		{}
		void dessinRobot(int couleur);
};


#endif
