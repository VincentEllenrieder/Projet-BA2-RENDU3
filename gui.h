//simulation.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include "graphic.h"
#include "simulation.h"
#include <gtkmm/drawingarea.h>
#include <gtkmm.h>

#ifndef GTKMM_MYAREA_H
#define GTKMM_MYAREA_H

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		~MyArea();
		void clear();
		void draw();
		double getXMax() {return xMax;}
		double getXMin() {return xMin;}
		double getYMax() {return yMax;}
		double getYMin() {return yMin;}
	protected:
		//Override default signal handler:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
		bool draw_rame(const Cairo::RefPtr<Cairo::Context>& cr);
	private:
		bool empty;
		void refresh();
		double xMin;
		double xMax;
		double yMin;
		double yMax;
};

class MyEvent : public Gtk::Window
{
	public:
		MyEvent();
		~MyEvent();
	
	protected:
		MyArea m_Area;
		bool on_idle(Simulation goSimulation);
		//Button Signal handlers:
		void on_button_clicked_exit();
		void on_button_clicked_open();
		void on_button_clicked_save();
		void on_button_clicked_start(Simulation goSimulation);
		void on_button_clicked_step();
		
		void on_button_clicked_link();
		void on_button_clicked_range();
		
		bool on_key_press_event(GdkEventKey * key_event);
		
		void
		
		Gtk::Box m_Box, m_Box_Top, m_Box_Gauche, m_Box_Droite, m_Box_Bottom;
		Gtk::Button m_Button_Exit,m_Button_File,m_Button_Save,m_Button_Start,m_Button_Step,m_Button_Link,m_Button_Range;
		Gtk::Label  m_Label_General, m_Label_Toggle, m_Label_Info;
	private:
		void draw();
		bool start;
		bool step;
		bool link;
		bool range;
};
#endif // GTKMM_MYAREA_H
