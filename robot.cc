//geomod.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>
#include <iostream>		
#include <cstdlib>
#include "robot.h"

using namespace std;

//utilisation du théorème de Thalès pour un triangle A (position initale), B (but),
// C (troisième côté du triangle), et les points D et E formant la droite DE, plus 
//courte que et parallèle au segment BC
void Robot::updatePosition() {
	double xa = positionR.x;
	double ya = positionR.y;
	double xb = but.x;
	double yb = but.y;
	double AB = (geomod::shortestWay(positionR, but)).norme;
	double BC = abs(xa-xb);
	double AC = abs(ya-yb);
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
	if ((positionR.x == but.x) and (positionR.y == but.y)) setAtteint(true);
	return;
	}
