//simulation.cc RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#include <iostream>
#include <cairomm/context.h>
#include <gtkmm/window.h>
#include "gui.h"
#include "graphic.h"
#include "simulation.h"
#include "base.h"

using namespace std;

namespace {
	constexpr unsigned max_tab(10);
	static std::vector<SimData> report(max_tab); // init with zeros
}

static Simulation sim;
static bool link(true);
static bool range(false);

MyArea::MyArea() :empty(false)
{}

MyArea::~MyArea()
{}

void MyArea::clear(){
	empty= true;
	refresh();
}

void MyArea::draw(){
	empty= false;
	refresh();
}

void MyArea::refresh(){
	auto win = get_window();
	if(win){
		Gdk::Rectangle r(0,0, get_allocation().get_width(), 
										get_allocation().get_height());
		win->invalidate_rect(r,false);
	}
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	double frameWidth = allocation.get_width();
	double frameHeight = allocation.get_height();
	double drawWidth;
	double drawHeight;
	if (frameHeight <= frameWidth) {
		drawWidth = frameHeight;
		drawHeight = frameHeight;
	} else {
		drawWidth = frameWidth;
		drawHeight = frameWidth;
	}
	draw_frame(cr);
	graphic_set_context(cr);
	
	cr -> translate(drawWidth/2, drawHeight/2);
	double xMax = getXMax();
	double xMin = getXMin();
	double yMax = getYMax();
	double yMin = getYMin();
	double scale1 = drawWidth/(xMax-xMin);
	double scale2 = drawHeight/(yMax-yMin);
	cr -> scale(scale1, scale2);
	cr -> set_line_width(3);
	
	sim.drawConnexionRange(range, link);
	graphic::whiteFrame(xMax, 0, xMax*2 + frameWidth, 0, yMax*2);
	graphic::whiteFrame(0, yMax, 0, yMax*2 + frameHeight, xMax*2);
	
	return true;
}

MyEvent::MyEvent()
	:m_Box(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Top(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_Box_Gauche(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Droite(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_Box_Bottom(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_vbox(Gtk::ORIENTATION_VERTICAL, 10),
	m_Label_General("General"), m_Button_Exit("exit"), m_Button_File("open file"), 
	m_Button_Save("save file"),m_Button_Start("start"), m_Button_Step("step"), 
	m_Label_Toggle("toggle display"), m_Button_Link("toggle link"),m_Button_Range("toggle range"), 
	m_Label_Info("Init"), m_Button_Scroll("Add one more"), count(0), start(true), step(false)
{
	set_title("Further");
	set_border_width(5); //distance entre bord intérieur et extérieur de la fenêtre
	
	m_Button_Scroll.signal_clicked().connect(sigc::mem_fun(*this,
												&Scroll::on_button_clicked_scroll));
	
	// Add outer box to the window
	add(m_Box);
	
	m_Vbox.add(m_Button_Scroll);
	m_Vbox.add(scrolled_window);
	
	m_Box.pack_start(m_Box_Top);
	m_Box_Top.pack_start(m_Box_Gauche,false, false);
	m_Box_Top.pack_start(m_Box_Droite);
	m_Box_Bottom.pack_start(m_Vbox);
	m_Box.pack_start(m_Box_Bottom,false,false);
	m_Area.set_size_request(180,180);
	m_Box_Droite.pack_start(m_Area);
	
	m_Box_Gauche.pack_start(m_Label_General,false,false);
	m_Box_Gauche.pack_start(m_Button_Exit,false,false);
	m_Box_Gauche.pack_start(m_Button_File,false,false);
	m_Box_Gauche.pack_start(m_Button_Save,false,false);
	m_Box_Gauche.pack_start(m_Button_Start,false,false);
	m_Box_Gauche.pack_start(m_Button_Step,false,false); 
	
	m_Box_Gauche.pack_start(m_Label_Toggle,false,false);
	m_Box_Gauche.pack_start(m_Button_Link,false,false);
	m_Box_Gauche.pack_start(m_Button_Range,false,false);
	
	m_Box_Bottom.pack_start(m_Label_Info,false,false);
	
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_clicked_exit));	
	m_Button_File.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_file_clicked));
	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_file_clicked2));
	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_clicked_start));
	m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_clicked_step));
	m_Button_Link.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_clicked_link));
	m_Button_Range.signal_clicked().connect(sigc::mem_fun(*this,&MyEvent::on_button_clicked_range));
	
	Glib::signal_idle().connect( sigc::mem_fun(*this, &MyEvent::on_idle) );
	
	add_events(Gdk::KEY_RELEASE_MASK);
	
	scrolled_window.set_size_request(500, 200);  // replace 500 by -1 for the project
	scrolled_window.add(tree_view);

	scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,
							  Gtk::PolicyType::POLICY_AUTOMATIC);
	scrolled_window.set_hexpand();

	tree_view.append_column("nbP", _columns._col_nbP);
	tree_view.append_column("nbF", _columns._col_nbF);
	tree_view.append_column("nbT", _columns._col_nbT);
	tree_view.append_column("nbC", _columns._col_nbC);
	tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

	auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
	int cols_count = tree_view.append_column("Mission completeness", *cell);

	auto progress_col = tree_view.get_column(cols_count - 1);
	if(progress_col) progress_col->add_attribute(cell->property_value(),
													_columns._col_resource_percentage);
													
	show_all_children();	
}

MyEvent::~MyEvent()
{}

void MyEvent::on_button_clicked_exit() {
	exit(0);
}

void MyEvent::on_button_clicked_start(){
	start=not(start);
	if (start==true) {
		m_Button_Start.set_label("stop");
		cout << "La simulation est arretée" << endl;
		Glib::signal_idle().connect( sigc::mem_fun(*this, &MyEvent::on_idle) );
	}
	else {
		m_Button_Start.set_label("start");
		cout<<"La simulation reprend" << endl;
	}	
}
void MyEvent::on_button_clicked_step(){
	cout << "Step" << endl;
	if (start==true) {
		on_idle();
		m_Area.draw();
	}
}

void MyEvent::on_button_clicked_open() {
	Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	dialog.set_transient_for(*this);
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	
	m_Label_Info.set_text("choosing a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();
	m_Label_Info.set_text("Done choosing a file");
	//Handle the response:
	switch(result){ 
		case(Gtk::RESPONSE_OK):{
			cout << "Open clicked." << endl;
			string filename = dialog.get_filename();
			cout << "File selected: " <<  filename << endl;
			m_Area.clear();
			sim.lecture(filename);
			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void MyEvent::on_button_clicked_save() {
	Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	dialog.set_transient_for(*this);
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	
	m_Label_Info.set_text("saving a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();
	m_Label_Info.set_text("Done saving a file");
	//Handle the response:
	switch(result){ 
		case(Gtk::RESPONSE_OK):{
			cout << "Save clicked." << endl;
			string filename = dialog.get_filename();
			cout << "File selected: " <<  filename << endl;
			ofstream sortie(dialog.get_filename()); 
			sim.ecriture(sortie); 
			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void MyEvent::on_button_clicked_link() {
	link = !(link);
	//if (link) updateAdjacence(robots, robots);
}

void MyEvent::on_button_clicked_range() {
	range = !(range);
	//updateAdjacence(robots, robots);
}

bool MyEvent::on_key_press_event(GdkEventKey * key_event){
	if(key_event->type == GDK_KEY_PRESS){
		switch(gdk_keyval_to_unicode(key_event->keyval)){
			case 's':
				cout << " S key pressed !" << endl;
				step = true;
				return true;
			case 'q':
				cout << "Quit" << endl;
				exit(0);
				break;
		}
	}
	return Gtk::Window::on_key_press_event(key_event);
}

bool MyEvent::on_idle(){
	static unsigned count(0);
	if(start){
		sim.executeSimulation();
		cout << "Mise à jour de la simulation numéro : " << ++count << endl;
		m_Area.clear();
	}
	else if (step){
		step = false;
		cout << "Mise à jour de la simulation numéro : " << ++count << endl;
	}
	return true;  // return false when done
}
void MyEvent::on_button_clicked_scroll()
{
  tree_view_update(); 
}

void MyEvent::tree_view_update()
{
  Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(_columns);
  tree_view.set_model(ref_tree_model);

  if(true)
  {
	if(count > report.size()) 
		std::cout << max_tab << " lines max are displayed" << std::endl;

	for(size_t i = 0 ; i < count and i <report.size() ; ++i)
	{
	  report[i].nbP = i;
	  report[i].nbF = i;
	  report[i].nbT = i;
	  report[i].nbC = i;
	  report[i].ressource = 1000*i;
	  report[i].ressource_p = 10*i;
		
	  auto row = *(ref_tree_model->append());
	  row[_columns._col_nbP] = report[i].nbP;
	  row[_columns._col_nbF] = report[i].nbF;
	  row[_columns._col_nbT] = report[i].nbT;
      row[_columns._col_nbC] = report[i].nbC;
	  row[_columns._col_resource] = report[i].ressource;
	  row[_columns._col_resource_percentage] = report[i].ressource_p;
	}
  }
}
