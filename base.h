//base.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <vector>
#include <memory>
#include <cmath>
#include "geomod.h"
#include "constantes.h"
#include "message.h"
#include "gisement.h"
#include "robot.h"

#ifndef BASE_H
#define BASE_H

using namespace std;

class Base {
private:
	Point centreBase;
	double rayonBase;
	double ressourceBase;
	bool fini;
	bool commAtCenter;
	vector<shared_ptr<Robot>> robots;
	vector<shared_ptr<RobotProspection>> robotsProsp;
	vector<shared_ptr<RobotForage>> robotsForage;
	vector<shared_ptr<RobotTransport>> robotsTransp;
	vector<shared_ptr<RobotCommunication>> robotsComm;
	
public:
	Base(Point c, double ress) 
	: centreBase(c), rayonBase(rayon_base), ressourceBase(ress), fini(arret()), 
	  commAtCenter(false)
	{}
	
	void setRessources(double ressources) {
		ressourceBase = ressources;
	}
	
	void setCommAtCenter(bool update) {
		commAtCenter = update;
	}
	
	bool getCommAtCenter() const{
		bool thereIs = commAtCenter;
		return thereIs;
	}
	
	Point getCentre() const {
		Point c = centreBase;
		return c;
	}
	
	vector<shared_ptr<Robot>> getRobots() const {
		vector<shared_ptr<Robot>> liste = robots;
		return liste;
	}
	
	bool intersectBase(Base otherBase) const {
		Point c2 = otherBase.getCentre();
		bool answer = geomod::intersection(centreBase, c2, rayon_base, rayon_base);
		return answer;
	}
	
	void intersectGisement() const {
		vector<Gisement> copieGisements = gisement::getGisements();
		for (size_t i(0); i < copieGisements.size(); ++i) {
			Point c2 = copieGisements[i].getCentre();
			double r2 = copieGisements[i].getRayon();
			if (geomod::intersection(centreBase, c2, rayon_base, r2) == true) {
				double x1 = centreBase.x;
				double y1 = centreBase.y;
				double x2 = c2.x;
				double y2 = c2.y;
				cout << message::base_field_superposition(x1, y1, x2, y2);
				exit(0);
			}
		}
	}
	
	bool arret() {
		if (finR > ressourceBase) {
			fini = false;
			return fini;
		} else { 
			fini = true;
			return fini;
		}
	}
	
	void limiteCarburant() {
		for (size_t i(0); i < robotsProsp.size(); ++i) {
			double positionx = robotsProsp[i] -> getPosition().x;
			double positiony = robotsProsp[i] -> getPosition().y;
			double distanceMax = robotsProsp[i] -> getMaxDP();
			if ((distanceMax - sqrt(pow(centreBase.x - positionx, 2)
			+ pow(centreBase.y-positiony, 2))
			- (robotsProsp[i] -> getDp()) - deltaD) <= 0) {
				robotsProsp[i] -> setRetour(true);
			}
		}
	}
	
	void reparation() {
		for (size_t i(0); i < robots.size(); ++i) {
			double c = cout_reparation * (robots[i] -> getDp());
			ressourceBase = ressourceBase - c;
		}
	}
	
	void creationForage() {
		vector<Point> buts;
		for (size_t i(0); i < robotsProsp.size(); ++i) {
			Point but;
			if (robotsProsp[i] -> getFound() == true) {
				but = robotsProsp[i]-> getCdng();
				for (size_t j(0); j < buts.size(); ++j) {
					if (geomod::samePoint(but,buts[j]) == false) {
						buts.push_back(but);
					}
				}
			}
		}
		double cheminCourt = 3*dim_max;
		for (size_t k(0); k<buts.size(); ++k) {
			if (cheminCourt>(geomod::shortestWay(centreBase,buts[k])).norme) {
				cheminCourt=(geomod::shortestWay(centreBase,buts[k])).norme;
			}
		}
		//addForage();
	}
	
	//void creationProsp(vector<Gisement> gisements) {
		//for (size_t i(0); i < robotsProsp().size(); ++i) {
			//robotsProsp[i] -> majProsp;
		//if (ressourceBase - cout_prosp - cout_forage - cout_transp - cout_com > 500) {
//	}
			
		
	
	void addProsp(int id, double dist, double x, double y, double xb, double yb, 
				  bool att, bool ret, bool fnd);
	
	void addProsp(int newId, double dist, double x, double y, double xb, 
				  double yb, bool att, bool ret, bool fnd, double xg, double yg,
				  double rayong, double capaciteg);
				  
	void addForage(int id, double dist, double x, double y, double xb, double yb, 
				   bool att);	
				   			  
	void addTransp(int id, double dist, double x, double y, double xb, double yb, 
				   bool att, bool ret);	
				   			  
	void addComm(int id, double dist, double x, double y, double xb, double yb, 
				 bool att);
	void creation();
};


#endif
