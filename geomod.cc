//geomod.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>
#include <iostream>
#include <cmath>				
#include "geomod.h"

using namespace std;

namespace {
	double epsilon_zero;
	double maxi;
}

double geomod::setMax(double maxValue) {
	maxi = maxValue;
	epsilon_zero = pow(10, -10)*maxi;
	return maxi;
}

double geomod::getMax() {
	return maxi;
}

double geomod::getEpsilonZero() {
	return epsilon_zero;
}

Point geomod::setPoint(double abscisse, double ordonnee) {	
	Point p;
	p.x = abscisse;
	p.y = ordonnee;
	p = geomod::normalise(p);
	return p;
}

Point geomod::normalise(Point p) {	//normalise un point 2D
	if ((p.x > maxi) or (p.x < -maxi)) {
		if (p.x < 0) {
			p.x = p.x + 2*maxi;	
		} else { 
			p.x = p.x - 2*maxi;
		} 
	}
	if  ((p.y > maxi) or (p.y < -maxi)) {
		if (p.y < 0) {
			p.y = p.y + 2*maxi;
		} else { 
			p.y = p.y - 2*maxi;	
		}
	}
	return p;
}
	
double geomod::normalise(double v) { //normalise une coordonnée		
	if (v < 0) {
		v = v + 2*maxi;
	} else { 
		v = v - 2*maxi;
	}
	return v;
}
	
Vecteur geomod::shortestWay(Point a, Point b){
	Vecteur v;
	double shortest(3*maxi+1);
	double xInt;						
	double yInt;				
	for (int kx(-1); kx < 2; ++kx) {
		xInt = b.x + 2*kx*maxi;
		for (int ky(-1); ky < 2; ++ky) {		
			yInt = b.y + 2*ky*maxi;
			double norme;
			norme=sqrt(pow(xInt-a.x,2)+pow(yInt-a.y,2));
			if (norme < shortest){
				shortest = norme;
				v.hori = xInt-a.x;
				v.vert = yInt-a.y;
				v.norme = shortest;
			}
		}
	}
	return v;
}

bool geomod::samePoint(Point a, Point b){
	Vecteur v = geomod::shortestWay(a,b);
	if (v.norme<epsilon_zero) {
		return true;
	}
	else {
		return false;
	}
}

bool geomod::belong(Point a, Point b, double rayon)	{												
	Vecteur v = geomod::shortestWay(a,b);
	if (v.norme < rayon - epsilon_zero) {
		return true;
	}
	else {
		return false;
	}
}

bool geomod::intersection(Point a, Point b, double r1, double r2){															
	Vecteur v = geomod::shortestWay(a,b);
	if (v.norme<r1+r2-epsilon_zero) {
		return true;
	}
	else {
		return false;
	}
}
