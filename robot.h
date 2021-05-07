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
	bool connecte;
	vector<shared_ptr<Robot>> listeAdjacence;
	
public:
	Robot(int id, Point p, double dist, Point b, bool att)
	: uid(id), positionR(p), dp(dist), but(b), atteint(att), connecte(false)
	{}
	
	int getId() const {
		int identification = uid;
		return identification;
	}
	Point getPosition() const {
		Point p = positionR;
		return p;
	}
	vector<shared_ptr<Robot>> getAdjacence() const {
		vector<shared_ptr<Robot>> liste = listeAdjacence;
		return liste;
	}
	
	double getDp() {
		double distance(dp);
		return distance;
	}
	
	void setPosition(Point p) {
		positionR = p;
	}
	
	void setAtteint(bool a) {
		atteint = a;
	}
	
	void updatePosition();
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
					 bool ret, bool fnd)
	: Robot(id, p, dist, b, att), coutProsp(cout_prosp), maxDProsp(maxD_prosp),
	  retour(ret), found(fnd)
	{}
	
	RobotProspection(int id, Point p, double dist, Point b, bool att,
					 bool ret, bool fnd, double xg, double yg,
					 double rayong, double capaciteg)
	: Robot(id, p, dist, b, att), coutProsp(cout_prosp), maxDProsp(maxD_prosp),
	  retour(ret), found(fnd), cdng(geomod::setPoint(xg, yg)), rayong(rayong),
	  ressourceg(capaciteg)
	{}
	
	double getMaxDP() {
		double m = maxDProsp;
		return m;
	}
	bool getFound() {
		bool fnd = found;
		return fnd;
	}
	Point getCdng() {
		Point p = cdng;
		return p;
	}
	void setRetour(bool r) {
		retour = r;
	}
	
	void updateProsp(vector<Gisement> gisements) {	//à terminer (VIncent)
		dp += deltaD;
		updatePosition();
		for (size_t i(0); i < gisements.size(); ++i) {
			Point positionG(gisements[i].getCentre());
			double rayonG = gisements[i].getRayon();
			if (geomod::belong(positionR, positionG, rayonG) == true) {
				cdng = positionG;
				rayong = rayonG;
				ressourceg = gisements[i].getRessource();
				found = true;
			}
		}
	}
};

class RobotForage : public Robot {
private:
	double coutForage;
	double maxDForage;
	
public:
	RobotForage(int id, Point p, double dist, Point b, bool att)
	: Robot(id, p, dist, b, att), coutForage(cout_forage), maxDForage(maxD_forage)
	{}	
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
};

class RobotCommunication : public Robot {
private:
	double coutCom;
	int maxDCom;
	double rayonCom;
	
public:
	RobotCommunication(int id, Point p, double dist, Point b, bool att)
	: Robot(id, p, dist, b, att), coutCom(cout_com), maxDCom(maxD_com), 
	  rayonCom(rayon_com)
	{}	
};


#endif
