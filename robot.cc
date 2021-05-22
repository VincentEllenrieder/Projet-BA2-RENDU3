//geomod.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>
#include <iostream>		
#include <cstdlib>
#include "robot.h"

using namespace std;

//----------------------------------Robots globaux------------------------------------

//utilisation du théorème de Thalès pour un triangle A (position initale), B (but),
// C (troisième côté du triangle), et les points D et E formant la droite DE, plus 
//courte que et parallèle au segment BC
void Robot::updatePosition() {
	double xa = positionR.x;
	double ya = positionR.y;
	double xb = but.x;
	double yb = but.y;
	double AB = (geomod::shortestWay(positionR, but)).norme;
	double BC = (geomod::shortestWay(positionR, but)).hori;
	double AC = (geomod::shortestWay(positionR, but)).vert;
	double deltaX = deltaD * (BC/AB);
	double deltaY = deltaD * (AC/AB);
	double xd, yd;
	if ((xa <= xb) and (ya <= yb)) {
		xd = xa + deltaX;
		yd = ya + deltaY;
	}
	if ((xa <= xb) and (ya > yb)) {
		xd = xa + deltaX;
		yd = ya - deltaY;
	}
	if ((xa > xb) and (ya <= yb)) {
		xd = xa - deltaX;
		yd = ya + deltaY;
	}
	if ((xa > xb) and (ya > yb)) {
		xd = xa - deltaX;
		yd = ya - deltaY;
	}
	Point p = geomod::setPoint(xd, yd);
	setPosition(p);
}

void Robot::reached() {
	vector<Gisement> gisements = gisement::getGisements();
	bool goalIsGisement = false;
	Point g;
	double rayon;
	for (size_t i(0); i < gisements.size(); ++i) {	//determine si son but est dans un
		g = gisements[i].getCentreGisement();	//gisement et s'il est atteint
		rayon = gisements[i].getRayon();
		goalIsGisement = geomod::belong(but, g, rayon);
		if (goalIsGisement == true) break;
	}
	if (goalIsGisement == true) {
		bool circleReached = geomod::belong(positionR, g, rayon);
		if (circleReached == true) atteint = true;
	}
	bool pointReached = geomod::samePoint(positionR, but);
	if (pointReached == true) atteint = true;
}

//---------------------------Robots Prospection---------------------------------------

void RobotProspection::updateProsp(bool findNew, Point newBut) {
	if ((atteint == false) and (dp != maxDProsp)) {
		dp += deltaD;
		updatePosition();
		reached();
	}
	checkIfFound();
	if ((found == false) and (atteint == true)) {
		setBut(newBut);
		atteint = false;
	}
	if ((found == true) and (findNew == true)) {
		found = false;
		atteint = false;
		setBut(newBut);
	}
}

void RobotProspection::checkIfFound() {
	vector<Gisement> gisements = gisement::getGisements();
	if ((found == false) and (atteint == true)) {
		for (size_t i(0); i < gisements.size(); ++i) {
			Point positionG = gisements[i].getCentreGisement();
			double rayonG = gisements[i].getRayon();
			double ressourceG = gisements[i].getRessource();
			if ((geomod::belong(positionR, positionG, rayonG) == true) 
				 and (ressourceG > 0)) {
				foundGisement(positionG, rayonG, ressourceG); 
				found = true;
			}
		}
	}
}

void RobotProspection::foundGisement(Point cdng, double rayonG, double ressourceG) {
	cdng = cdng;
	rayong = rayonG;
	ressourceg = ressourceG;
	found = true;
	atteint = true;
}

	
//---------------------------Robots Forage---------------------------------------

void RobotForage::updateForage() {
	if ((atteint == false) and (dp != maxDForage)) {
		dp += deltaD;
		updatePosition();
		reached();
	}
	if (atteint == true) atteint = true;
}
		

//---------------------------Robots Transport----------------------------------------

void RobotTransport::updateTransp(bool proceed) {
	if ((atteint == false) and (dp != maxDTransp)) {
		dp += deltaD;
		updatePosition();
		reached();
	}
	if ((atteint == true) and (proceed == true)) {
		updateGisement();
		retour = true;
		

void RobotTransport::updateGisement() {
	
	



















