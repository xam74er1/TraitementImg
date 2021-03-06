// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <iostream>
#include <stdio.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include "MyImage.hpp"
#include "MyRotateDialog.hpp"
#include "MyThresholdDialog.hpp"
#include <iostream>
#include <wx/wx.h>
#include "MyHistogram.hpp"
#endif
wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow* parent);
    ~MyPanel();
    void OpenImage(wxString fileName);
    void SaveImage(wxString fileName);
    void OnPaint(wxPaintEvent& WXUNUSED(event));
    void Mirror(bool horisontal = false);
    void Blurp(int blur);
    void Rotate(bool rotation);
    void Negative();
    void Desature();
    void Seil(int seuil);
	void OnThresholdImage(wxCommandEvent& event);
	void OnLumina(wxCommandEvent& event);
	void SeilOld(int seuil);
    void posterize();
	void count_histogram();
	void enhenceContrast();
    int getM_Whith();
    int getM_Height();
	void Lunina();
	void Disterbing();
	void justRed();

private:
    wxBitmap m_bitmap; // used to display the image
    MyImage* m_image;  // used to load and process the image
	 MyImage* img_save;  // used to load and process the image
    int m_whith;
    int m_height;
};

MyPanel::MyPanel(wxWindow* parent)
    : wxPanel(parent)
{
	
}

void MyPanel::OpenImage(wxString fileName)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

    delete m_image;
    m_image = new MyImage(fileName);
	img_save = new MyImage((MyImage) m_image->Copy());

    m_height = m_image->GetHeight();
    m_whith = m_image->GetWidth();
    GetParent()->SetSize(m_whith, m_height + 10);

    this->SetSize(m_whith, m_height);
    Refresh();
}

MyPanel::~MyPanel(){};

void MyPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{

    m_bitmap = wxBitmap(*m_image);
    wxPaintDC dc(this);
    dc.DrawBitmap(m_bitmap, 0, 0);
}

int MyPanel::getM_Whith()
{
    return m_whith;
}
int MyPanel::getM_Height()
{
    return m_height;
}

void MyPanel::SaveImage(wxString fileName)
{
    if(m_image) {
	m_image->SaveFile(fileName);
    }
}

void MyPanel::Mirror(bool horisontal)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	//*m_image = m_image->Mirror(horisontal);
	m_image->Mirror(horisontal);
	// delete m_image;
	// m_image = &tmp;
	// delete &tmp;

	Refresh();
    }
}

void MyPanel::Blurp(int blur)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    *m_image = m_image->Blur(blur);
    Refresh();
}

void MyPanel::Rotate(bool rotation)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {
	MyRotateDialog* m_rd = new MyRotateDialog(this);
	int res =m_rd->ShowModal();

	if(res == wxID_OK) {

	    int index = m_rd->RadioBox1->GetSelection();
	    // Si lindex n'est pas 3
	    rotation = (index != 2);
	    MyImage* tmp = m_image;
	    m_image = m_image->Rotate90(rotation);
	    delete tmp;
	    // Si 180
	    if(index == 1) {
		MyImage* tmp = m_image;
		m_image = m_image->Rotate90(rotation);
		delete tmp;
	    }

	    Refresh();
	}
    }
}


void MyPanel::Negative()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	m_image->Negative();
	Refresh();
    }
}

void MyPanel::Desature()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	m_image->Desature();
	Refresh();
    }
}


void MyPanel::SeilOld(int seuil)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {
	MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
	dlg->ShowModal();
	int m_seil = dlg->m_threshold->GetValue();
	m_image->Threshold(m_seil);
	Refresh();
    }
}

void MyPanel::Seil(int seuil)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
	
    if(m_image) {
		
		*img_save = (MyImage) m_image->Copy();
	MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
	int res = dlg->ShowModal();
	
	if(res!=wxID_OK){
		//delete m_image;
		*m_image = (MyImage) img_save->Copy();
		
			Refresh();
	}
	
	Unbind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
	//delete img_save;
    }
}



void MyPanel::OnThresholdImage(wxCommandEvent& event){
	
	
	//delete m_image;
	
	*m_image =(MyImage) img_save->Copy();
	

	int m_seil = event.GetInt();
	m_image->Threshold(m_seil);
	Refresh();
}



void MyPanel::Lunina()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	Bind(MON_EVENEMENT, &MyPanel::OnLumina, this) ;
	
    if(m_image) {
		
		*img_save = (MyImage) m_image->Copy();
	MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Luminosite"), wxDefaultPosition, wxSize(250, 140),wxDEFAULT_DIALOG_STYLE,-255,255,0);
	int res = dlg->ShowModal();
	
	if(res!=wxID_OK){
		//delete m_image;
		*m_image = (MyImage) img_save->Copy();
		std::cout<<" on annule tout "<<std::endl;
			Refresh();
	}
	Unbind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
	//delete img_save;
    }
}

void MyPanel::OnLumina(wxCommandEvent& event){
	//delete m_image;
	
	*m_image =(MyImage) img_save->Copy();

	int m_seil = event.GetInt();
	m_image->Luninosite(m_seil);
	Refresh();
}

void MyPanel::posterize()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	m_image->Posterize();
	Refresh();
    }
}

void MyPanel::count_histogram()
{
	int nbc = m_image->count_nbColor();
	wxLogMessage(wxT("il y a "+std::to_string(nbc)+" couleur dans image"));
}


void MyPanel::enhenceContrast(){
	
	 Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {
	MyHistogram *m_ht = new MyHistogram(m_image);
	
	int min ,max;
	
	m_ht->GetDynamic(&min,&max);

	
	std::cout<<"min "<<min<<" max"<<max<<std::endl;
	
	m_image->EnhenceContrast(min,max);
	Refresh();
	//std::cout<<"end"<<std::endl;
	}
}


void MyPanel::Disterbing()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	m_image->Dither();
	Refresh();
    }
}


void MyPanel::justRed(){
	 Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {

	m_image->justRed();
	Refresh();
    }
}

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnEnCour(wxCommandEvent& event);
    void OnResize(wxCommandEvent& event);
    void OnMouseMove(wxMouseEvent& evt);
    void OnOppen(wxCommandEvent& event);
    void OpenImage(wxString fileName);
    void OnSave(wxCommandEvent& event);
    void OnProcessImage(wxCommandEvent& event);
    MyPanel* m_panel; // the panel inside the main frame
};

enum { // énumération. Elle gère la numérotation automatiquement
    ID_Hello = 1,
    ID_ENCOUR,
    ID_RESIZE_UP,
    ID_RESIZE_DOWN,
    ID_OPPEN,
    ID_SAVE,
    ID_MIROR_H,
    ID_MIROR_V,
    ID_BLURP,
    ID_ROTATION_P90,
    ID_ROTATION_M90,
    ID_ROTATION_M180,
    ID_PROCESSE_IMAGE,
    ID_NEGATIVE,
    ID_DESATURE,
    ID_SEIL,
    ID_POSTERIZE,
	ID_HISTOGRAMCOUNT,
	ID_CONTRAST,
	ID_LUMINA,
	ID_DISTURB,
	ID_TEST

};
IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(wxT("Hello World"), wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    wxInitAllImageHandlers();
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    m_panel = new MyPanel(this);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), _T("Show about dialog"));
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);

    menuFile->Append(wxID_ABOUT, wxT("About"));
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;

    menuHelp->Append(ID_ENCOUR, wxT("en cour"));
    Bind(wxEVT_MENU, &MyFrame::OnEnCour, this, ID_ENCOUR);

    wxMenu* menuResize = new wxMenu;

    menuResize->Append(ID_RESIZE_UP, wxT("Agrandire...\tCtrl-+"));
    Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_RESIZE_UP);

    menuResize->Append(ID_RESIZE_DOWN, wxT("Reduire...\tCtrl--"));
    Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_RESIZE_DOWN);

    wxMenu* menuImage = new wxMenu;

    menuImage->Append(ID_OPPEN, wxT("Ouvrir...\tCtrl-O"));
    Bind(wxEVT_MENU, &MyFrame::OnOppen, this, ID_OPPEN);

    menuImage->Append(ID_SAVE, wxT("Save...\tCtrl-S"));
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_SAVE);

    wxMenu* menuProcesse = new wxMenu;

    menuProcesse->Append(ID_MIROR_H, wxT("Horisontal Miror...\tCtrl-M-H"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MIROR_H);

    menuProcesse->Append(ID_MIROR_V, wxT("Vertical Miror...\tCtrl-M-V"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MIROR_V);

    menuProcesse->AppendSeparator();

    menuProcesse->Append(ID_BLURP, wxT("Blur...\tCtrl-B"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_BLURP);

    menuProcesse->AppendSeparator();

    menuProcesse->Append(ID_ROTATION_P90, wxT("Rotation +90 ...\tCtrl-R"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_P90);

    menuProcesse->Append(ID_ROTATION_M90, wxT("Rotation -90 ...\tCtrl-Y"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_M90);

    menuProcesse->Append(ID_ROTATION_M180, wxT("Rotation 180 ...\tCtrl-T"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_M180);

    menuProcesse->AppendSeparator();

    menuProcesse->Append(ID_NEGATIVE, wxT("Negative...\tCtrl-N"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_NEGATIVE);

    menuProcesse->Append(ID_DESATURE, wxT("Desature...\tCtrl-D"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_DESATURE);

    menuProcesse->Append(ID_SEIL, wxT("thresholding...\tCtrl-SE"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_SEIL);

    menuProcesse->Append(ID_POSTERIZE, wxT("Posterize...\tCtrl-PO"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_POSTERIZE);
	
	
    menuProcesse->Append(ID_CONTRAST, wxT("Contraste...\tCtrl-PE"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_CONTRAST);
	
	menuProcesse->Append(ID_LUMINA, wxT("Luminosite..\tCtrl-PE"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_LUMINA);
	
	menuProcesse->Append(ID_DISTURB, wxT("Distubing..\tCtrl-PE"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_DISTURB);
	
	menuProcesse->Append(ID_TEST, wxT("Distubing..\tCtrl-PE"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_TEST);
	
	
	
	wxMenu* menuCalcule= new wxMenu;
	
	menuCalcule->Append(ID_HISTOGRAMCOUNT, wxT("Historgrame...\tCtrl-H"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_HISTOGRAMCOUNT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("File"));
    menuBar->Append(menuHelp, wxT("Help"));
    menuBar->Append(menuResize, wxT("Resize"));
    menuBar->Append(menuImage, wxT("Image"));
    menuBar->Append(menuProcesse, wxT("Processe"));
	menuBar->Append(menuCalcule, wxT("Calcule"));

    SetMenuBar(menuBar);

    CreateStatusBar(3);
    SetStatusText(wxT("une bare qui marche"), 1);

    Bind(wxEVT_MOTION, &MyFrame::OnMouseMove, this);

    this->CenterOnScreen();

    //-------Pannel ------
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage(wxT("Hello world from wxWidgets!"));
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxLogMessage(wxT("Create by Max CLERC"));
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnEnCour(wxCommandEvent& event)
{
    wxLogMessage(wxT("En cour de creation "));
}
void MyFrame::OnResize(wxCommandEvent& event)
{
    int height;
    int whith;

    GetSize(&height, &whith);

    int size = 100;

    if(event.GetId() == ID_RESIZE_UP) {
	if(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) > height + size &&
	    wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) > whith + size)
	    SetSize(height + size, whith + size);
    } else {
	if(GetMinHeight() < height - size && GetMinWidth() < whith - size)
	    SetSize(height - size, whith - size);
    }
}

void MyFrame::OnMouseMove(wxMouseEvent& evt)
{
    SetStatusText(wxT("une bare qui marche"), 1);
    int x = 0;
    int y = 0;
    evt.GetPosition(&x, &y);
    wxString str;
    str.sprintf("x = %d and y = %d", x, y);

    SetStatusText(str);
}

void MyFrame::OnOppen(wxCommandEvent& event)
{
    wxString filename = wxFileSelector("Choose a file to open");
    if(!filename.empty()) {
	m_panel->OpenImage(filename);

    } else {
	std::cout << "nope" << std::endl;
    }
}

//------------------PANEL -----

void MyFrame::OnSave(wxCommandEvent& event)
{
    wxString filename = wxSaveFileSelector("Save your image", "jpeg");
    if(!filename.empty()) {
	m_panel->SaveImage(filename);
    }
}

void MyFrame::OnProcessImage(wxCommandEvent& event)
{
    switch(event.GetId()) {
    case ID_ROTATION_P90:
	m_panel->Rotate(true);
	break;
    case ID_ROTATION_M90:
	m_panel->Rotate(false);
	break;
    case ID_ROTATION_M180:
	m_panel->Rotate(false);
	// m_panel->Rotate(false);
	break;
    case ID_MIROR_H:
	m_panel->Mirror(true);
	break;
    case ID_MIROR_V:
	m_panel->Mirror(false);
	break;
    case ID_BLURP:
	m_panel->Blurp(1);
	break;
    case ID_NEGATIVE:
	m_panel->Negative();
	break;
    case ID_DESATURE:
	m_panel->Desature();
	break;
    case ID_SEIL:
	m_panel->Seil(100);
	break;
    case ID_POSTERIZE:
	m_panel->posterize();
	break;
	case ID_HISTOGRAMCOUNT:
	m_panel->count_histogram();
	break;
	case ID_CONTRAST:
	m_panel->enhenceContrast();
	break;
	case ID_LUMINA:
	m_panel->Lunina();
	break;
	case ID_DISTURB:
	m_panel->Disterbing();
	break;
	case ID_TEST:
	m_panel->justRed();
	break;
    }
}