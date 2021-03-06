//base.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>	
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
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
	bool fini = false;
	if (ressourceBase >= finR) fini = true;
	return fini;
}

void Base::updateMoney() {
	for (size_t i(0); i < robotsTransp.size(); ++i) {
		Point pos = robotsTransp[i] -> getPosition();
		bool retour = robotsTransp[i] -> getRetour();
		bool inside = geomod::belong(centreBase, pos, rayonBase);
		if ((inside == true) and (retour == true)) {
			ressourceBase += deltaR;
			robotsTransp[i] -> setRetour(false);
		}
	}
}

bool Base::destroyBase() {
	bool destroy = false;
	if (ressourceBase <= 0) {
		destroy = true;
	}
	return destroy;
}

//------------------------------------Ecriture----------------------------------------

void Base::ecritureBase(ofstream& sortie) {
	double xB = centreBase.x;
	double yB = centreBase.y;
	double ressB = ressourceBase;
	unsigned P = robotsProsp.size();
	unsigned F = robotsForage.size();
	unsigned T = robotsTransp.size();
	unsigned C = robotsComm.size();
	sortie << "		" << xB << " " << yB << " " << ressB << " " << P << " "
		   << F << " " << T << " " << C << endl;
	for(size_t i(0); i < robotsProsp.size(); ++i) { 
		ecritureProsp(robotsProsp[i], sortie);
		sortie << endl;
	}
	for(size_t i(0); i < robotsForage.size(); ++i) { 
		ecritureForage(robotsForage[i], sortie);
		sortie << endl;
	}
	for(size_t i(0); i < robotsTransp.size(); ++i) { 
		ecritureTransp(robotsTransp[i], sortie);
		sortie << endl;
	}
	for(size_t i(0); i < robotsComm.size(); ++i) { 
		ecritureComm(robotsComm[i], sortie);
		sortie << endl;
	}
}	

void Base::ecritureProsp(shared_ptr<RobotProspection>& prospecteur, ofstream& sortie) {
			
	double id = prospecteur -> getId();
	double distance = prospecteur -> getDp();
	double x = (prospecteur -> getPosition()).x;
	double y = (prospecteur -> getPosition()).y;
	double xBut = (prospecteur -> getBut()).x;
	double yBut = (prospecteur -> getBut()).y;
	bool att = prospecteur -> getAtteint();
	bool ret = prospecteur -> getRetour();
	bool fnd = prospecteur -> getFound();
	if (fnd == true) {
		double xG = (prospecteur -> getCdng()).x;
		double yG = (prospecteur -> getCdng()).y;
		double rayonG = prospecteur -> getRg();
		double ressG = prospecteur -> getCapg();
		sortie << "				" << "# Prospecteurs" << endl;
		sortie << " 			" << id << " " << distance << " " << x << " " 
			   << y << " " << xBut << " " << yBut  << " " << att << " " << ret
			   << " " << fnd << " " << xG << " " << yG << " " << rayonG << " " 
			   << ressG << endl;
	} else {
		sortie << "				" << "# Prospecteurs" << endl;
		sortie << " 			" << id << " " << distance << " " << x << " " 
			   << y << " " << xBut << " " << yBut  << " " << att << " " << ret
			   << " " << fnd << endl;	
	}
}

void Base::ecritureForage(shared_ptr<RobotForage>& foreur, ofstream& sortie) {
	
	double id = foreur -> getId();
	double distance = foreur -> getDp();
	double x = (foreur -> getPosition()).x;
	double y = (foreur -> getPosition()).y;
	double xBut = (foreur -> getBut()).x;
	double yBut = (foreur -> getBut()).y;
	bool att = foreur -> getAtteint();
	sortie << "				" << "# Foreurs" << endl;
	sortie << " 			" << id << " " << distance << " " << x << " " 
		   << y << " " << xBut << " " << yBut  << " " << att << endl;	
}

void Base::ecritureTransp(shared_ptr<RobotTransport>& transporteur, ofstream& sortie) {
	
	double id = transporteur -> getId();
	double distance = transporteur -> getDp();
	double x = (transporteur -> getPosition()).x;
	double y = (transporteur -> getPosition()).y;
	double xBut = (transporteur -> getBut()).x;
	double yBut = (transporteur -> getBut()).y;
	bool att = transporteur -> getAtteint();
	bool ret = transporteur -> getRetour();
	sortie << "				" << "# Transporteurs" << endl;
	sortie << " 			" << id << " " << distance << " " << x << " " 
		   << y << " " << xBut << " " << yBut  << " " << att << " " << ret << endl;	
}

void Base::ecritureComm(shared_ptr<RobotCommunication>& communicateur, 
						ofstream& sortie) {
	double id = communicateur -> getId();
	double distance = communicateur -> getDp();
	double x = (communicateur -> getPosition()).x;
	double y = (communicateur -> getPosition()).y;
	double xBut = (communicateur -> getBut()).x;
	double yBut = (communicateur -> getBut()).y;
	bool att = communicateur -> getAtteint();
	sortie << "				" << "# Communicateurs" << endl;
	sortie << " 			" << id << " " << distance << " " << x << " " 
		   << y << " " << xBut << " " << yBut  << " " << att << endl;	
}

//---------------------------Creation + mise ?? jour---------------------------------

void Base::maintenance() {
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		double dist = robotsProsp[i] -> getDp();
		Point pos = robotsProsp[i] -> getPosition();
		bool ret = robotsProsp[i] -> getRetour();
		if ((centreBase.x == pos.x) and (centreBase.y == pos.y) and (ret == true)) {
			double c = cout_reparation * dist;
			ressourceBase -= c;
			robotsProsp[i] -> setDp(0);
		}
	}
	for (size_t i(0); i < robotsTransp.size(); ++i) {
		double dist = robotsTransp[i] -> getDp();
		Point pos = robotsTransp[i] -> getPosition();
		bool ret = robotsTransp[i] -> getRetour();
		if ((centreBase.x == pos.x) and (centreBase.y == pos.y) and (ret == true)) {
			double c = cout_reparation * dist;
			ressourceBase -= c;
			robotsTransp[i] -> setDp(0);
		}
	}
}	

void Base::creation() {
	amountProduced = 0;
	if ((robotsProsp.size() < 9) or (robotsComm.size() < 9)) {
		for (int i(0); i < 6; ++i) {
			if (i % 2 == 0) {
				while ((amountProduced < 3) and (robotsComm.size() < 9)) {
					creationComm();
				}
			} else {
				while ((amountProduced < 3) and (robotsProsp.size() < 9)) {
					creationProsp();
				}
			}
		}
	}
	while (amountProduced < 3) {
		creationForageTransport();
		creationComm();
	}
}	

void Base::updateRemote() {
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		if (robotsProsp[i] -> getRemote() == true) {
			bool findNew;
			if (robotsProsp[i] -> getFound() == true) {
				Point g = robotsProsp[i] -> getCdng();
				findNew = findNewGisement(g);
			}
			Point pos = robotsProsp[i] -> getPosition();
			double dist = robotsProsp[i] -> getDp();
			bool back = limiteCarburantProsp(pos, dist);
			Point newGoal = setNewGoal(pos);
			robotsProsp[i] -> updateProspRemote(findNew, newGoal, back, centreBase);
		}
	}
	for (size_t i(0); i < robotsForage.size(); ++i) {
		robotsForage[i] -> updateForage();
	}
	for (size_t i(0); i < robotsTransp.size(); ++i) {
			double bx = (robotsTransp[i] -> getBut()).x;
			double by = (robotsTransp[i] -> getBut()).y;
			bool proceed = loadingAccepted(bx, by);
			Point newBut = newGoal();//nouveau but donn?? seulement s'il est ?? sa base
			robotsTransp[i] -> updateTransp(proceed,	//et y sera donc de toute 
											centreBase, newBut); //fa??on en remote
	}
	for (size_t i(0); i < robotsComm.size(); ++i) {
		robotsComm[i] -> updateComm();
	}
}

void Base::updateAutonomous() {
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		if (robotsProsp[i] -> getRemote() == false) {
			robotsProsp[i] -> updateProspAuto(centreBase);
		}
	}
}

//-----------------------------------Connexion---------------------------------------


void Base::updateAdjacence(vector<shared_ptr<Robot>> robots1, 
						   vector<shared_ptr<Robot>> robots2) {
	for (size_t i(0); i < robots1.size(); ++i) { 
		vector<shared_ptr<Robot>> adjacence = robots1[i] -> getAdjacence();
		for (size_t j(0); i < adjacence.size(); ++j) {  
			adjacence[i].reset();
		}
		adjacence.clear();
		int id1 = robots1[i] -> getId();
		Point position1 = robots1[i] -> getPosition();
		
		for (size_t j(0); j < robots1.size(); ++j) { 
			int id2 = robots1[j] -> getId();
			if (id1 == id2) continue;
			Point position2 = robots1[j] -> getPosition();
			double distance = (geomod::shortestWay(position1, position2)).norme;
			if(distance <= rayon_com) {
				adjacence.push_back(robots1[j]);
			}
		}
		// si temps : remplacer void par bool pour retourner un booleen disant si
		// ce graphe est reli?? ?? des robots d'autres bases
		//for(size_t j(0); j < robots2.size(); ++j) { 	
			//Point position2 = robots2[j] -> getPosition();
			//double distance = geomod::shortestWay(position1, position2);
			//if(distance <= rayon_com) {
			//	adjacence.push_back(robots1[j]);
			//}
		//}
		robots1[i] -> setAdjacence(adjacence);
	}
}

void Base::connexion() {
	shared_ptr<Robot> robotCentral;
	for (size_t i(0); i < robots.size(); ++i) {
		Point position = robots[i] -> getPosition();
		if ((position.x == centreBase.x) and (position.y == centreBase.y)) {
			robotCentral = robots[i];
			break;
		}
	}
	vector<shared_ptr<Robot>> connectedToBase = parcoursDFS(robotCentral);
	
	for (size_t i(0); i < robots.size(); ++i) {
		robots[i] -> setRemote(false);
		int id1 = robots[i] -> getId();
		for (size_t j(0); j < connectedToBase.size(); ++j) {
			int id2 = connectedToBase[j] -> getId();
			if (id1 == id2) robots[i] -> setRemote(true);
		}
	}
}
			
vector<shared_ptr<Robot>> Base::parcoursDFS(shared_ptr<Robot> depart) {
	
	vector<shared_ptr<Robot>> result;
	for (auto p : robots) p -> setVisited(false);
	
	recDFS(result, depart);
	return result;
}

void Base::recDFS(vector<shared_ptr<Robot>>& result, shared_ptr<Robot> prochain) {
	
	prochain -> setVisited(true);
	result.push_back(prochain);
	
	const vector<shared_ptr<Robot>> adjacence = prochain -> getAdjacence();
	for(size_t i(0); i < adjacence.size(); ++i) {
		bool controled = adjacence[i] -> getVisited();
		if (controled == false) recDFS(result, adjacence[i]);
	}
}

//-----------------------------------Robots globaux------------------------------------

int Base::createID() const {
	bool same = false;
	for (int ID(1); ID < 999999; ++ID) {
		for (size_t j(0); j < robots.size(); ++j) {
			if (ID == (robots[j] -> getId())) {
				same = true;
				break;
			}
		if (same == false) return ID;
		break;
		}
	}
	return 0;
}

void Base::destroyRobots() {
	for (size_t i(0); i < robots.size(); ++i) {
		robots[i].reset();
	}
	robots.clear();
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		robotsProsp[i].reset();
	}
	robotsProsp.clear();
	for (size_t i(0); i < robotsForage.size(); ++i) {
		robotsForage[i].reset();
	}
	robotsForage.clear();
	for (size_t i(0); i < robotsTransp.size(); ++i) {
		robotsTransp[i].reset();
	}
	robotsTransp.clear();
	for (size_t i(0); i < robotsComm.size(); ++i) {
		robotsComm[i].reset();
	}
	robotsComm.clear();
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

bool Base::findNewGisement(Point g) const {
	bool findNew = false;
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

bool Base::limiteCarburantProsp(Point position, double distance) {
	bool back = false;
	double calc = maxD_prosp - (geomod::shortestWay(centreBase, position).norme) 
				  - distance - deltaD;
	if (calc <= 0) back = true;
	return back;
}
//-------------------------------RobotsForage----------------------------------------		

void Base::creationForageTransport() { 
	vector<Gisement> foundGisements;
	for (size_t i(0); i < robotsProsp.size(); ++i) {
		if (robotsProsp[i] -> getFound() == true) {
			Gisement decouvert(robotsProsp[i] -> getCdng(), 
							   robotsProsp[i] -> getRg(),
							   robotsProsp[i] -> getCapg());
			foundGisements.push_back(decouvert);
		}
	}
	if (foundGisements.size() == 0) return;
	bestForage(foundGisements);
}	

void Base::bestForage(vector<Gisement> foundGisements) {
	Point centre = meilleurGisement(foundGisements);
	int count(0);
	for (size_t i(0); i < robotsForage.size(); ++i) {
		double bx = (robotsForage[i] -> getBut()).x;
		double by = (robotsForage[i] -> getBut()).y;
		if ((bx == centre.x) and (by == centre.y)) ++count;
	}
	if (count >= 3) { //d??j?? 3 robotsForage ayant ce gisement comme but 
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
		if ((ressourceBase - cout_transp > 0) and (amountProduced < max_robot)) {
			addTransp(createID(), 0, centreBase.x, centreBase.y, centre.x, centre.y, 
					  false, false);
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

Point Base::newGoal() {
	for (size_t i(0); i < robotsForage.size(); ++i) {
		bool incoming = false;
		Point butF = robotsForage[i] -> getBut();
		for (size_t j(0); j < robotsTransp. size(); ++j) {
			Point butT = robotsTransp[j] -> getBut();
			if((butT.x == butF.x) and (butT.y == butF.y)) {
				incoming = true;
				break;
			}
		}
		if (incoming == false) return butF;
		break;
	}
	return centreBase;
}

//------------------------Robot Communication-----------------------------------------
		
void Base::creationComm() {
	if (amountProduced < max_robot) {
		Point b = setCommGoal();
		addComm(createID(), 0, centreBase.x, centreBase.y, b.x, b.y, false);
		ressourceBase = ressourceBase - cout_com;
		++amountProduced;
	}
}

Point Base::setCommGoal() { //les robots de comm forment 3 carr??s pour couvrir toute 
	Point goal;				// la map : 1 de 9 points, 1 de 16, 1 de 24
	bool completedOne = squareOneCompleted();
	bool completedTwo = squareTwoCompleted();
	bool completedThree = squareThreeCompleted();
	if (completedOne == false) goal = squareOneGoal();
	if ((completedTwo == false) and (completedOne == true)) goal = squareTwoGoal();
	if ((completedThree == false) and (completedTwo == true) 
		 and (completedOne == true)) goal = squareThreeGoal();
	return goal;
}


bool Base::squareOneCompleted() {
	double cX, cY;
	double m, n;
	bool completed = false;
	int count(0);
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + rayon_com * m;
			cY = centreBase.y + rayon_com * n;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) ++ count;
			}
		}
	}
	if (count == 9) completed = true;
	return completed;
}

bool Base::squareTwoCompleted() {
	double cX, cY;
	double m, n;
	int count(0);
	bool completed = false;
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + 2 * rayon_com * m;
			cY = centreBase.y + 2 * rayon_com * n;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) ++ count;
			}
		}
	}
	if (count == 16) completed = true;
	return completed;
}

bool Base::squareThreeCompleted() {
	double cX, cY;
	double m, n;
	int count(0);
	bool completed = false;
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + 3 * rayon_com * m;
			cY = centreBase.y + 3 * rayon_com * n;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) ++ count;
			}
		}
	}
	if (count == 24) completed = true;
	return completed;
}

Point Base::squareOneGoal() {
	double cX, cY;
	double m, n;
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + rayon_com * m;
			cY = centreBase.y + rayon_com * n;
			bool onPosition = false;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) {
					onPosition = true;
					break;
				}
			}
			if (onPosition == false) {
				Point goal = geomod::setPoint(cX, cY);
				return goal;
			}
		}
	}
}

Point Base::squareTwoGoal() {
	double cX, cY;
	double m, n;
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + 2 * rayon_com * m;
			cY = centreBase.y + 2 * rayon_com * n;
			bool onPosition = false;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) {
					onPosition = true;
					break;
				}
			}
			if (onPosition == false) {
				Point goal = geomod::setPoint(cX, cY);
				return goal;
			}
		}
	}
}


Point Base::squareThreeGoal() {
	double cX, cY;
	double m, n;
	for (int k(0); k < 4; ++k) {
		if (k == 0) m = 1;
		if (k == 1) m = 0;
		if (k == 2) m = -1;
		for (int l(0); l < 4; ++l) {
			if (k == 0) n = 1;
			if (k == 1) n = 0;
			if (k == 2) n = -1;
			cX = centreBase.x + 3 * rayon_com * m;
			cY = centreBase.y + 3 * rayon_com * n;
			bool onPosition = false;
			for (size_t i(0); i < robotsComm.size(); ++i) {
				Point p = geomod::setPoint(cX, cY);
				Point but  = robotsComm[i] -> getBut();
				if ((but.x == p.x) and (but.y == p.y)) {
					onPosition = true;
					break;
				}
			}
			if (onPosition == false) {
				Point goal = geomod::setPoint(cX, cY);
				return goal;
			}
		}
	}
}

//----------------------------ajout robots------------------------------------------

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
	CercleR cercle(x, -y, getCouleur());
	cercle.dessinRobot(getCouleur());
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
	CercleR cercle(x, -y, getCouleur());
	cercle.dessinRobot(getCouleur());
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
	CercleR cercle(x, -y, getCouleur());
	cercle.dessinRobot(getCouleur());
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
	CercleR cercle(x, -y, getCouleur());
	cercle.dessinRobot(getCouleur());
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
	CercleR cercle(x, -y, getCouleur());
	cercle.dessinRobot(getCouleur());
	if ((x == centreBase.x) and (y == centreBase.y)) Base::setCommAtCenter(true);
}
	



	
	
	
	
	
	
	
	
	
	
	
	
