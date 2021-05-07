//base.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>	
#include <iostream>
#include "base.h"

using namespace std;

void Base::addProsp(int newId, double dist, double x, double y, double xb, 
					double yb, bool att, bool ret, bool fnd) {
							  
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<Robot> newPtr(new RobotProspection(newId, c, dist, b, att, ret, fnd));
		
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

void Base::addProsp(int newId, double dist, double x, double y, double xb, 
					double yb, bool att, bool ret, bool fnd, double xg, double yg,
					double rayong, double capaciteg) {
						
	Point c = geomod::setPoint(x, y);
	Point b = geomod::setPoint(xb, yb);
	shared_ptr<Robot> newPtr(new RobotProspection(newId, c, dist, b, att, ret, fnd, 
												  xg, yg, rayong, capaciteg));
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
	shared_ptr<Robot> newPtr(new RobotForage(newId, c, dist, b, att));
	
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
	shared_ptr<Robot> newPtr(new RobotTransport(newId, c, dist, b, att, ret));
	
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
	shared_ptr<Robot> newPtr(new RobotForage(newId, c, dist, b, att));
	
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




	
	
	
	
	
	
	
	
	
	
	
	
