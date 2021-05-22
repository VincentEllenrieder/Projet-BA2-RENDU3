//robot.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <vector>
#include <memory>
#include <cmath>
#include "gisement.h"
#include "constantes.h"
#include "geomod.h"

#ifndef ROBOT_H
#define ROBOT_H

using namespace std;

class Robot {
protected:
	int uid;
	Point positionR;
	double dp;
	Point but;
	bool atteint;
	double rayonCom;
	bool connecte;
	vector<shared_ptr<Robot>> listeAdjacence;

public:
	Robot(int id, Point p, double dist, Point b, bool att)
	: uid(id), positionR(p), dp(dist), but(b), atteint(att), rayonCom(rayon_com),
	  connecte(false)
	  
	{}
	
	int getId() const {return uid;}
	
	Point getPosition() const {return positionR;}
	
	vector<shared_ptr<Robot>> getAdjacence() const {return listeAdjacence;}
	
	double getDp() {return dp;}
	
	Point getBut() {return but;}
	
	bool getAtteint() {return atteint;}
	
	void setDp(double dist) {dp = dist;}
	
	void setBut(Point b) {but = b;}
	
	void setPosition(Point p) {positionR = p;}
	
	void setAtteint(bool a) {atteint = a;}
	
	void updatePosition();
	
	void reached();
};

class RobotProspection : public Robot {
private:
	double coutProsp;
	double maxDProsp;
	bool retour;
	bool found;
	Point cdng;
	double rayong;
	double ressourceg;
	
	
public:
	RobotProspection(int id, Point p, double dist, Point b, bool att,
					 bool ret, bool fnd) //sans gisement trouvé
	: Robot(id, p, dist, b, att), coutProsp(cout_prosp), maxDProsp(maxD_prosp),
	  retour(ret), found(fnd)
	{}
	
	RobotProspection(int id, Point p, double dist, Point b, bool att,
					 bool ret, bool fnd, double xg, double yg,
					 double rayong, double capaciteg) //gisement trouvé
	: Robot(id, p, dist, b, att), coutProsp(cout_prosp), maxDProsp(maxD_prosp),
	  retour(ret), found(fnd), cdng(geomod::setPoint(xg, yg)), rayong(rayong),
	  ressourceg(capaciteg)
	{}

	bool getFound() {return found;}
	
	Point getCdng() {return cdng;}

	double getRg() {return rayong;}
	
	double getCapg() {return ressourceg;}

	void setRetour(bool r) {retour = r;}
	
	void updateProsp(bool findNew, Point newBut);
	
	void checkIfFound();
	
	void foundGisement(Point cdnG, double rayonG, double ressourceG);
	
	void setNewGoal();
};

class RobotForage : public Robot {
private:
	double coutForage;
	double maxDForage;
	
public:
	RobotForage(int id, Point p, double dist, Point b, bool att)
	: Robot(id, p, dist, b, att), coutForage(cout_forage), maxDForage(maxD_forage)
	{}	
	
	void updateForage();
}; 

class RobotTransport : public Robot {
private:
	double coutTransp;
	int maxDTransp;
	bool retour;
	
public:
	RobotTransport(int id, Point p, double dist, Point b, bool att, bool ret)
	: Robot(id, p, dist, b, att), coutTransp(cout_transp), maxDTransp(maxD_transp),
	  retour(ret)
	{}	
	
	bool getRetour() {return retour;}
	
	void setRetour(bool a) {retour = a;}
	
	void updateTransp(bool proceed);
	
	void updateGisement();
};

class RobotCommunication : public Robot {
private:
	double coutCom;
	int maxDCom;
	
public:
	RobotCommunication(int id, Point p, double dist, Point b, bool att)
	: Robot(id, p, dist, b, att), coutCom(cout_com), maxDCom(maxD_com)
	{}	
};


#endif
