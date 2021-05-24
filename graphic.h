
#ifndef GTKMM_EXAMPLE_GRAPHIC_GUI_H
#define GTKMM_EXAMPLE_GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>

namespace graphic {
	void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);
	void graphic_draw_circle(const int c1, const int c2, const int rayon, 
							 const int depart);
	void decision(int couleur);
	void drawGisement(const double c1, const double c2, const double rayon);
	void drawBase(const double c1, const double c2, const double rayon, 
													const int couleur);
	void drawRobot(const double c1, const double c2, const int couleur);
	void drawLink(const double c1, const double c2, const double c3, const double c4);
	void drawRange(const double c1, const double c2);
	void whiteFrame(double x1, double y1, double x2, double y2, double k);
}

#endif // GTKMM_EXAMPLE_GRAPHIC_GUI_H
