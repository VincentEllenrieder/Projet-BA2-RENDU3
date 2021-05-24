
#include <cmath>
#include "graphic.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr); 

void graphic::graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr){
	ptcr = &cr;
}

void graphic::decision(int couleur) {
	switch (couleur) {
		case 1 : 
			(*ptcr)->set_source_rgb(1.,0.,0.);
			break;
		case 2 : 
			(*ptcr)->set_source_rgb(0.,0.,1.);
			break;
		case 3 : 
			(*ptcr)->set_source_rgb(0.,1.,0.);
			break;
		case 4 : 
			(*ptcr)->set_source_rgb(1.,0.88,0.21);
			break;
		case 5 : 
			(*ptcr)->set_source_rgb(0.1,0.,0.5);
			break;
		case 6 : 
			(*ptcr)->set_source_rgb(0.,1.,1.);
			break;
	}
}

void graphic::graphic_draw_circle(const double c1, const double c2, const double rayon) {
	(*ptcr)->save();
	(*ptcr)->arc(c1, c2, rayon, 0., 2*M_PI);
	(*ptcr)->stroke();
	(*ptcr)->restore();
}
	
void graphic::drawGisement(const double c1, const double c2, const double rayon) {
	(*ptcr)->save();
	(*ptcr) -> set_source_rgb(1.,1.,1.);
	graphic_draw_circle(c1, c2, rayon*10);
	(*ptcr)->restore();
}

void graphic::drawBase(const double c1, const double c2, const double rayon, const int couleur) {
	(*ptcr)->save();
	decision(couleur);
	graphic_draw_circle(c1, c2, rayon*10);
	(*ptcr)->restore();
}

void graphic::drawRobot(const double c1, const double c2, const int couleur) {
	(*ptcr)->save();
	decision(couleur);
	graphic_draw_circle(c1, c2, 10.);
	(*ptcr)->restore();
}

void graphic::drawLink(const double c1, const double c2, const double c3, const double c4) {
	(*ptcr)->save();
	(*ptcr)->set_source_rgb(0.5,0.,0.5);
	(*ptcr)->move_to(c1, c2);
	(*ptcr)->line_to(c3, c4);
	(*ptcr)->stroke();
	(*ptcr)->restore();
}

void graphic::drawRange(const double c1, const double c2, const double rayon) {
	(*ptcr)->save();
	(*ptcr)->set_source_rgb(0.5,0.,0.5);
	graphic_draw_circle(c1, c2, rayon);
	(*ptcr)->restore();
}

void whiteFrame(double x1, double y1, double x2, double y2, double e) {
	(*ptcr)->save();
	(*ptcr)->set_source_rgb(240.0/256, 241/256.0, 242.0/256);
	(*ptcr)->set_line_width(e);
	(*ptcr)->move_to(x1, y1);
	(*ptcr)->line_to(x2, y2);
	(*ptcr)->stroke();
	(*ptcr)->restore();
}
