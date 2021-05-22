//base.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>	
#include <iostream>
#include "base.h"

using namespace std;

namespace {
	unsigned int amountProduced(0);
}

//---------------------------------Base-------------------------------------------

bool Base::intersectBase(Base otherBase) const {
	Point c2 = otherBase.getCentre();
	bool answer = geomod::intersection(centreBase, c2, rayon_base, rayon_base);
	return answer;
}

void Base::intersectGisement() const {
	vector<Gisement> copieGisements = gisement::getGisements();
	for (size_t i(0); i < copieGisements.size(); ++i) {
		Point c2 = copieGisements[i].getCentreGisement();
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

bool Base::arret() {
	if (finR > ressourceBase) {
		fini = false;
		return fini;
	} else { 
		fini = true;
		return fini;
	}
}

void Base::updateMoney() {
	for(size_t i(0); i < robotsTransp.size(); ++i) {
		Point pos = robotsTransp[i] -> getPosition();
		bool retour = robotsTransp[i] -> getRetour();
		bool inside = geomod::belong(centreBase, pos, rayonBase);
		if ((inside == true) and (retour == true)) {
			ressourceBase += deltaR;
		}
	}
}

//---------------------------Tâche de mise à jour + creation---------------------------

void Base::update() {
	updateMoney();
	updateRobots();
	maintenance();
	
	
}

void Base::creation() {
	if(robotsProsp.size() < 9) creationProsp();
	
	
	

}
	

//-----------------------------------Robots globaux------------------------------------

void Base::updateRobots() {
	for(size_t i(0); i < robotsProsp.size(); ++i) {
		bool findNew = findNewGisement(robotsProsp[i]);
		Point pos = robotsProsp[i] -> getPosition();
		Point newGoal = setNewGoal(pos);
		robotsProsp[i] -> updateProsp(findNew, newGoal);
	}
	for(size_t i(0); i < robotsForage.size(); ++i) { //ajouter updateForage
		robotsForage[i] -> updateForage();
	}
	for(size_t i(0); i < robotsTransp.size(); ++i) {
		double bx = (robotsTransp[i] -> getBut()).x;
		double by = (robotsTransp[i] -> getBut()).y;
		bool proceed = loadingAccepted(bx, by);
		robotsTransp[i] -> updateTransp(proceed);
	}
}

int Base::createID() const {
	bool same = false;
	for (int ID(1); ID < 999999; ++ID) {
		for (size_t j(0); j < robots.size(); ++j) {
			if (ID == (robots[j] -> getId())) {
				same = true;
				break;
			}
		if (same == false) return ID;
		}
	}
}
		

//-----------------------------maintenance----------------------------------------

void Base::limiteCarburantProsp() {
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		Point position = robotsProsp[i] -> getPosition();
		if ((maxD_prosp - (geomod::shortestWay(centreBase, position).norme) 
			- (robotsProsp[i] -> getDp()) - deltaD) <= 0) {
			robotsProsp[i] -> setRetour(true);
		}
	}
}

void Base::maintenance() {
	for (size_t i(0); i < robots.size(); ++i) {
		double dist = robots[i] -> getDp();
		Point pos = robots[i] -> getPosition();
		if ((geomod::belong(centreBase, pos, rayonBase)) == true) {
			double c = cout_reparation * dist;
			ressourceBase -= c;
			robots[i] -> setDp(0);
		}
	}
}		

//-------------------------------Robots Prosp----------------------------------------

void Base::creationProsp() {
	while (amountProduced < max_robot) {
		Point but = setNewGoal(centreBase);
		if (ressourceBase - cout_prosp > 0) {
			addProsp(createID(), 0, centreBase.x, centreBase.y, but.x, but.y, 
					 false, false, false);
			ressourceBase = ressourceBase - cout_prosp;
			++amountProduced;
		}
	}
}

bool Base::findNewGisement(shared_ptr<RobotProspection>& prospecteur) const {
	bool findNew = false;
	Point g = prospecteur -> getCdng();
	int count(0);
	for (size_t i(0); i < robotsForage.size(); ++i) { 
		double bx = (robotsForage[i] -> getBut()).x;
		double by = (robotsForage[i] -> getBut()).y;
		if ((bx == g.x) and (by == g.y)) ++count;
	}
	if (count >= 3) findNew = true;
	return findNew;
}

Point Base::setNewGoal(Point pos) {
	int x = rand() % (300 * 2 + 1) + (-300);
	int plusMinus = rand() % 2 + 1;
	int y = sqrt((pow((rayon_com), 2)) - (pow(x, 2)));
	if (plusMinus == 1) y = -y;
	double newX = pos.x + x;
	double newY = pos.y + y;
	Point newBut = geomod::setPoint(newX, newY);
	return newBut;
}

//-------------------------------RobotsForage----------------------------------------		

void Base::creationForageTransport() { 
	vector<Gisement> foundGisements;
	if (amountProduced < max_robot) {
		for (size_t i(0); i < robotsProsp.size(); ++i) {
			if (robotsProsp[i] -> getFound() == true) {
				Gisement decouvert(robotsProsp[i] -> getCdng(), 
								   robotsProsp[i] -> getRg(),
								   robotsProsp[i] -> getCapg());
				foundGisements.push_back(decouvert);
			}
		}
		bestForage(foundGisements);
	}
}	

void Base::bestForage(vector<Gisement> foundGisements) {
	Point centre = meilleurGisement(foundGisements);
	int count(0);
	for (size_t i(0); i < robotsForage.size(); ++i) {
		double bx = (robotsForage[i] -> getBut()).x;
		double by = (robotsForage[i] -> getBut()).y;
		if ((bx == centre.x) and (by == centre.y)) ++count;
	}
	if (count >= 3) { //déjà 3 robotsForage ayant ce gisement comme but 
		 foundGisements = updateInterest(centre, foundGisements); 
		 bestForage(foundGisements);
		 return;
	} else {
		if (ressourceBase - cout_forage > 0) {
			addForage(createID(), 0, centreBase.x, centreBase.y, centre.x, centre.y, 
					  false);
			ressourceBase = ressourceBase - cout_forage;
			++amountProduced;
		}
		if (ressourceBase - cout_transp > 0) {
			addForage(createID(), 0, centreBase.x, centreBase.y, centre.x, centre.y, 
					  false);
			ressourceBase = ressourceBase - cout_transp;
			++amountProduced;
		}
	}
}

Point Base::meilleurGisement(vector<Gisement> foundGisements) {
	Point centre = foundGisements[0].getCentreGisement();
	double ress = foundGisements[0].getRessource();
	for (size_t i(0); i < foundGisements.size(); ++i) {
		double r = foundGisements[i].getRessource();
		Point c = foundGisements[i].getCentreGisement();
		if (r > ress) {
			ress = r;
			centre = c;
		}
		if (r == ress) {
			Vecteur distance1 = geomod::shortestWay(centreBase, centre);
			Vecteur distance2 = geomod::shortestWay(centreBase, c);
			if (distance2.norme < distance1.norme) {
				ress = r;
				centre = c;
			}
		}
	}
	return centre;
}

vector<Gisement> Base::updateInterest(Point centre, 
									  vector<Gisement> interestGisements) {
	vector<Gisement> interestUpdated;
	for (size_t i(0); i < interestGisements.size(); ++i) {
		double cx = (interestGisements[i].getCentreGisement()).x;
		double cy = (interestGisements[i].getCentreGisement()).y;
		if ((cx == centre.x) and (cy == centre.y)) continue;
		else interestUpdated.push_back(interestGisements[i]);
	}
	return interestUpdated;
}

//--------------------------------Robots Transport-----------------------------------

bool Base::loadingAccepted(double butXT, double butYT) {
	bool proceed = false;
	vector<Gisement> gisements = gisement::getGisements();
	for (size_t i(0); i < robotsForage.size(); ++i) {
		double butXF = (robotsForage[i] -> getBut()).x;
		double butYF = (robotsForage[i] -> getBut()).y;
		if((butXT == butXF) and (butYT == butYF)) {
			for (size_t j(0); j < gisements.size(); ++j) {
				 double gx = gisements[j].getCentreGisement().x;
				 double gy = gisements[j].getCentreGisement().y;
				 if((gx == butXT) and (gy == butYT) 
					 and (gisements[i].getRessource() >= deltaR)) {
						 proceed = true;
						 break;
				}
			}
		}
	}
	return proceed; 
}
				 
				 
				 
//----------------------ajout robots------------------------------------------

void Base::addProsp(int newId, double dist, double x, double y, double xb, 
					double yb, bool att, bool ret, bool fnd) {
							  
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<RobotProspection> newPtr(new RobotProspection(newId, c, dist, b, att,
															 ret, fnd));
	
	for (size_t i(0); i < robots.size(); ++i) {
		int identification = (robots[i] -> getId()); 
		if (newId == identification) {	
			cout << message::identical_robot_uid(identification);
			exit(0);
		}
	}
	
	robotsProsp.push_back(newPtr);
	robots.push_back(newPtr);
}

void Base::addProsp(int newId, double dist, double x, double y, double xb, 
					double yb, bool att, bool ret, bool fnd, double xg, double yg,
					double rayong, double capaciteg) {
						
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<RobotProspection> newPtr(new RobotProspection(newId, c, dist, b, att, 
															 ret, fnd, xg, yg, rayong, 
															 capaciteg));
	for (size_t i(0); i < robots.size(); ++i) {
		int identification = (robots[i] -> getId()); 
		if (newId == identification) {
			cout << message::identical_robot_uid(identification);
			exit(0);
		}
	}
	robots.push_back(newPtr);
	robotsProsp.push_back(newPtr);
}
			
void Base::addForage(int newId, double dist, double x, double y, double xb, double yb, 
					 bool att) {
				   
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<RobotForage> newPtr(new RobotForage(newId, c, dist, b, att));
	
	for (size_t i(0); i < robots.size(); ++i) {
		int identification = (robots[i] -> getId()); 
		if (newId == identification) {
			cout << message::identical_robot_uid(identification);
			exit(0);
		}
	}
	robots.push_back(newPtr);
	robotsForage.push_back(newPtr);
}
				   			  
void Base::addTransp(int newId, double dist, double x, double y, double xb, double yb, 
					 bool att, bool ret) {	
			   			   
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<RobotTransport> newPtr(new RobotTransport(newId, c, dist, b, att, ret));
	
	for (size_t i(0); i < robots.size(); ++i) {
		int identification = (robots[i] -> getId()); 
		if (newId == identification) {
			cout << message::identical_robot_uid(identification);
			exit(0);
		}
	}
	robots.push_back(newPtr);
	robotsTransp.push_back(newPtr);
}
				   			  
void Base::addComm(int newId, double dist, double x, double y, double xb, double yb, 
				   bool att) {
   
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<RobotCommunication> newPtr(new RobotCommunication(newId, c, dist, b, 
																 att));
	for (size_t i(0); i < robots.size(); ++i) {
		int identification = (robots[i] -> getId()); 
		if (newId == identification) {
			cout << message::identical_robot_uid(identification);
			exit(0);
		}
	}
	robots.push_back(newPtr);
	robotsComm.push_back(newPtr);
	if ((x == centreBase.x) and (y == centreBase.y)) Base::setCommAtCenter(true);
}
	



	
	
	
	
	
	
	
	
	
	
	
	
