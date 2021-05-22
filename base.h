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
	
	bool getCommAtCenter() const {return commAtCenter;}
	
	Point getCentre() const {return centreBase;}
	
	vector<shared_ptr<Robot>> getRobots() const {return robots;}
	
	void setRessources(double ressources) {ressourceBase = ressources;}
	
	void setCommAtCenter(bool update) {commAtCenter = update;}
	
	//---------------------------------Base-------------------------------------------
	
	bool intersectBase(Base otherBase) const;
	
	void intersectGisement() const;
	
	bool arret();
	
	void updateMoney();
	
	//-----------------------------------Tâche de mise à jour-------------------------
	
	void update();
	
	void creation();
	
	//-----------------------------------Robots globaux-------------------------------
	
	void updateRobots();
	
	int createID() const;
	
	//-----------------------------maintenance----------------------------------------
	
	void limiteCarburantProsp();
	
	void maintenance();
	
	//-------------------------------Robots Prosp-------------------------------------
	
	void creationProsp();
	
	bool findNewGisement(shared_ptr<RobotProspection>& prosp) const;
		
	Point setNewGoal(Point pos);
	
	//-------------------------------RobotsForage------------------------------------
	
	void creationForageTransport();
	
	void bestForage(vector<Gisement> foundGisements);
	
	Point meilleurGisement(vector<Gisement> foundGisements);
	
	vector<Gisement> updateInterest(Point centre, 
									vector<Gisement> interestGisements);
	
	void creationForage(Gisement nouveau);
	
	//--------------------------------Robots Transport--------------------------------
	
	bool loadingAccepted(double butXT, double butYT);
	
	//----------------------ajout robots------------------------------------------
	
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
	
};


#endif
