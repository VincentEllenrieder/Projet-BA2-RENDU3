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
	bool commAtCenter;
	vector<shared_ptr<Robot>> robots;
	vector<shared_ptr<RobotProspection>> robotsProsp;
	vector<shared_ptr<RobotForage>> robotsForage;
	vector<shared_ptr<RobotTransport>> robotsTransp;
	vector<shared_ptr<RobotCommunication>> robotsComm;
	
public:
	Base(Point c, double ress) 
	: centreBase(c), rayonBase(rayon_base), ressourceBase(ress), commAtCenter(false)
	{}
	~Base() {destroyRobots();}
	
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
	
	bool destroyBase();
	
	//-----------------------------------Tâche de mise à jour-------------------------
	
	void updateRemote();
	
	void updateAutonomous();
	
	void maintenance();
	
	void creation();
	
	//---------------------------------Connexion--------------------------------------
	
	void updateAdjacence(vector<shared_ptr<Robot>> robots1, 
						 vector<shared_ptr<Robot>> robots2);
						 
	void connexion();
	
	vector<shared_ptr<Robot>> parcoursDFS(shared_ptr<Robot> depart);
	
	void recDFS(vector<shared_ptr<Robot>>& result, shared_ptr<Robot> prochain);
	
	//-----------------------------------Robots globaux-------------------------------
	
	int createID() const;
	
	void destroyRobots();
	
	//-------------------------------Robots Prosp-------------------------------------
	
	void creationProsp();
	
	bool findNewGisement(Point g) const;
		
	Point setNewGoal(Point pos);
	
	bool limiteCarburantProsp(Point pos, double distance);
	
	//-------------------------------RobotsForage------------------------------------
	
	void creationForageTransport();
	
	void bestForage(vector<Gisement> foundGisements);
	
	Point meilleurGisement(vector<Gisement> foundGisements);
	
	vector<Gisement> updateInterest(Point centre, 
									vector<Gisement> interestGisements);
	
	//--------------------------------Robots Transport--------------------------------
	
	bool loadingAccepted(double butXT, double butYT);
	
	bool goalIsBase(double bx, double by);
	
	Point newGoal();
	
	//--------------------------------Robots Communication---------------------------
	
	void creationComm();
	
	Point setCommGoal();
	
	bool squareOneCompleted();
	
	bool squareTwoCompleted();
	
	bool squareThreeCompleted();
	
	Point squareOneGoal();
	
	Point squareTwoGoal();
	
	Point squareThreeGoal();
		
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
