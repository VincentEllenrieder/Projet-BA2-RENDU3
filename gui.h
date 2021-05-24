//simulation.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include "graphic.h"
#include "simulation.h"
#include <gtkmm/drawingarea.h>
#include <gtkmm.h>

#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

struct SimData
{
  unsigned nbP;
  unsigned nbF;
  unsigned nbT;
  unsigned nbC;
  double ressource;
  double ressource_p;
};

namespace gtk
{
  template<class T, class... T_Args>
  auto make_managed(T_Args&&... args) -> T*
  {
    return manage(new T(std::forward<T_Args>(args)...));
  }
}

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
		void tree_view_update();
	
	protected:
		MyArea m_Area;
		bool on_idle();
		//Button Signal handlers:
		void on_button_clicked_exit();
		void on_button_file_clicked();
		void on_button_file_clicked2();
		void on_button_clicked_start();
		void on_button_clicked_step();
		
		void on_button_clicked_link();
		void on_button_clicked_range();
		
		void on_button_clicked_scroll();
		
		bool on_key_press_event(GdkEventKey * key_event);
		
		
		Gtk::Box m_Box, m_Box_Top, m_Box_Gauche, m_Box_Droite, m_Box_Bottom, m_Vbox;
		Gtk::Button m_Button_Exit,m_Button_File,m_Button_Save,m_Button_Start,m_Button_Step,m_Button_Link,m_Button_Range, m_Button_Scroll;
		Gtk::Label  m_Label_General, m_Label_Toggle, m_Label_Info; //m_, m_Label_nbP, m_Label_nbF, m_Label_nbT, m_Label_nbC, m_Label_ressource, m_Label_mission;
		//Gtk::Frame 
	private:
		void draw();
		bool start;
		bool step;
		bool link;
		bool range;
		class Model_columns : public Gtk::TreeModel::ColumnRecord
		{
	    public:
			Model_columns()
			{
				add(_col_id);
				add(_col_nbP);
				add(_col_nbF);
				add(_col_nbT);
				add(_col_nbC);
				add(_col_resource);
				add(_col_resource_percentage);
			}
			Gtk::TreeModelColumn<int> _col_id;
			Gtk::TreeModelColumn<int> _col_nbP;
			Gtk::TreeModelColumn<int> _col_nbF;
			Gtk::TreeModelColumn<int> _col_nbT;
			Gtk::TreeModelColumn<int> _col_nbC;
			Gtk::TreeModelColumn<double> _col_resource;
			Gtk::TreeModelColumn<int> _col_resource_percentage;
		};

		Model_columns _columns;

		Gtk::ScrolledWindow scrolled_window;
		Gtk::TreeView tree_view;
		unsigned count;
};

};
#endif // GTKMM_MYAREA_H
