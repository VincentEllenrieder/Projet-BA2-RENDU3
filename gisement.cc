//geomod.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iomanip>			
#include "gisement.h"

using namespace std;

namespace {
	vector<Gisement> gisements;
}

void Gisement::gisementIntersectGisement(Gisement& g) const {
	for (size_t i(0); i < gisements.size(); ++i) {
		Point c2 = gisements[i].getCentreGisement();
		double r2 = gisements[i].getRayon();
		if (geomod::intersection(centreGisement, c2, rayonGisement, r2) == true) {
			double x1 = centreGisement.x;
			double y1 = centreGisement.y;
			double x2 = c2.x;
			double y2 = c2.y;
			cout << message::field_superposition(x1, y1, x2, y2);
			exit(0);
		}
	}
	gisements.push_back(g);
}

void Gisement::lostRessources() {
	capaciteGisement -= deltaR;
}

vector<Gisement> gisement::getGisements() {
	return gisements;
}

void gisement::destroyGisements() {
	gisements.clear();
}
