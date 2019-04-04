// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <iostream>
#include <stdio.h>

#include <wx/wxprec.h>
#include <wx/thread.h>


#ifndef WX_PRECOMP
#include "MyHistogram.hpp"
#include "MyImage.hpp"
#include "MyRotateDialog.hpp"
#include "MyThresholdDialog.hpp"
#include <iostream>
#include <stdio.h>
#include <wx/wx.h>
#include "MyHistogram.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>	// one of the OpenCV libraries
#include "opencv_bridge.h"
#include <opencv/cv.h>
#include <opencv/highgui.h> // one of the OpenCV libraries

#endif
wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);

wxDECLARE_EVENT(MY_THREAD_EVENT, wxCommandEvent) ;
wxDEFINE_EVENT(MY_THREAD_EVENT, wxCommandEvent) ;

using namespace std;

class MyThread;
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow* parent,MyThread * thread = nullptr);
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
	void drawImage(MyImage * data,int id =-1);
	void aplyEffect(int id);
	void test();
	void Face2();
	void Face2BW();
	void Face3BW();
	void addCounter();
	void ConvertiToOpenCV();
	void ouvertureOpenCV();
	void ConvertireToWxWiget();
	void setSeuil();
	void setSize();
	void seuillvl(wxCommandEvent& event);
	void sizelvl(wxCommandEvent& event);
	void fusion();
	void erode();
  bool run = true;

private:
    wxBitmap m_bitmap; // used to display the image
    MyImage* m_image;  // used to load and process the image
	MyImage* img_save;  // used to load and process the image
    int m_whith;
    int m_height;
    MyThread* m_theread;
    int m_seuil = 0;
	int m_size = 0;

    unsigned long xd, yd, xf, yf;
    bool drawRect = false;
    int counter = 0;
};

MyPanel::MyPanel(wxWindow* parent, MyThread* thread)
    : wxPanel(parent, wxID_ANY, wxPoint(200, 0))
    , m_theread(thread)
{

}

void MyPanel::addCounter()
{
    counter++;
}

void MyPanel::OpenImage(wxString fileName)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

    delete m_image;
    m_image = new MyImage(fileName);
    img_save = new MyImage((MyImage)m_image->Copy());

    m_height = m_image->GetHeight();
    m_whith = m_image->GetWidth();
    GetParent()->SetSize(m_whith + 200, m_height + 10);

    this->SetSize(m_whith, m_height);
    Refresh();
}

MyPanel::~MyPanel(){};

void MyPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{

	m_bitmap = wxBitmap(*m_image);
	wxPaintDC dc(this);
	dc.DrawBitmap(m_bitmap, 0, 0);
	/*
	const wxPoint pt = wxGetMousePosition();
	int mouseX = pt.x - this->GetScreenPosition().x;
	nt mouseY = pt.y - this->GetScreenPosition().y;
	dc.DrawCircle(mouseX,mouseY,10);
	*/
	if(drawRect) {

	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 10-pixels-thick pink outline
	dc.DrawRectangle(xd, yd, (xf - xd), (yf - yd));
	drawRect = false;

	}

	if(m_image) {
	delete m_image;
	}
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
	int res = m_rd->ShowModal();

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
	// MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,
	// 140));
	// dlg->ShowModal();
	int m_seil = m_seuil;
	m_image->Threshold(m_seil);
	Refresh();
    }
}

void MyPanel::Seil(int seuil)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    std::cout << m_seuil << std::endl;
    if(m_image) {
	// MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,
	// 140));
	// dlg->ShowModal();
	int m_seil = m_seuil;
	m_image->Threshold(m_seil);
	Refresh();
    }
}

void MyPanel::OnThresholdImage(wxCommandEvent& event)
{

    // delete m_image;

    *m_image = (MyImage)img_save->Copy();

    int m_seil = event.GetInt();
    m_image->Threshold(m_seil);
    Refresh();
}

void MyPanel::Lunina()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(MON_EVENEMENT, &MyPanel::OnLumina, this);

    if(m_image) {

	//*img_save = (MyImage) m_image->Copy();
	MyThresholdDialog* dlg = new MyThresholdDialog(
	    this, -1, wxT("Luminosite"), wxDefaultPosition, wxSize(250, 140), wxDEFAULT_DIALOG_STYLE, -255, 255, 0);
	int res = dlg->ShowModal();

	if(res != wxID_OK) {
	    // delete m_image;
	    *m_image = (MyImage)img_save->Copy();
	    // std::cout<<" on annule tout "<<std::endl;
	    Refresh();
	}
	Unbind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this);
	// delete img_save;
    }
}

void MyPanel::OnLumina(wxCommandEvent& event)
{
    // delete m_image;

    *m_image = (MyImage)img_save->Copy();

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
    wxLogMessage(wxT("il y a " + std::to_string(nbc) + " couleur dans image"));
}

void MyPanel::enhenceContrast()
{

    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    if(m_image) {
		MyHistogram* m_ht = new MyHistogram(m_image);

		int min, max;

		m_ht->GetDynamic(&min, &max);

		std::cout << "min " << min << " max" << max << std::endl;

		m_image->EnhenceContrast(min, max);
		Refresh();
		// std::cout<<"end"<<std::endl;
    }
}

void MyPanel::drawImage(MyImage *data,int id ){
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

	//if(!m_image){

	//}

	if(run){
	m_image = data;

	int  m_height = m_image->GetHeight();
   int m_whith = m_image->GetWidth();
    GetParent()->SetSize(m_whith, m_height + 10);

    this->SetSize(m_whith, m_height);

	if(id!=-1){
		aplyEffect(id);
	}else{
		Refresh();
	}
	}
}

void MyPanel::test()
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

    const wxPoint pt = wxGetMousePosition();
    int mouseX = pt.x - this->GetScreenPosition().x;
    int mouseY = pt.y - this->GetScreenPosition().y;

    if(m_image) {


		m_image->testOpenCv2();
		//m_image->contourVisage();


	Refresh();
    }
}

void MyPanel::Face2(){
	  Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);


		drawRect = true;

    if(m_image) {

	m_image->FollowOneFaceV2(xd,yd,xf,yf);

	//cout<<" xd "<<xd<<" yd "<<yd<<endl;

	Refresh();



    }
}

void MyPanel::Face2BW(){
	  Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);


		drawRect = true;
		bool direct = false;
		bool needFind = (counter%10==0)||direct;



    if(m_image) {

	m_image->FollowOneFaceV2BlackAndWhite(xd,yd,xf,yf,needFind);

	//cout<<" xd "<<xd<<" yd "<<yd<<endl;

	Refresh();

    }
}


void MyPanel::seuillvl(wxCommandEvent& event)
{
    m_seuil = event.GetInt();
    // std::cout << m_seil << std::endl;
}

void MyPanel::sizelvl(wxCommandEvent& event)
{
    m_size = event.GetInt();
    // std::cout << m_seil << std::endl;
}

void MyPanel::setSeuil()
{
    Bind(MON_EVENEMENT, &MyPanel::seuillvl, this);

    MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
    int res = dlg->ShowModal();

    if(res != wxID_OK) {
	Unbind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this);
    }
}

void MyPanel::setSize()
{
    Bind(MON_EVENEMENT, &MyPanel::sizelvl, this);

	MyThresholdDialog* dlg = new MyThresholdDialog(this, -1, wxT("Size"), wxDefaultPosition, wxSize(250, 140), wxDEFAULT_DIALOG_STYLE ,0 , 10 , m_size);
    int res = dlg->ShowModal();
}

void MyPanel::fusion() {
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

    if(m_image) {
		int size = m_size;
		m_image->fusionTest(size);
		Refresh();
    }
}

void MyPanel::erode() {
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);

    if(m_image) {
		int size = m_size;
		m_image->erodeTest(size);
		Refresh();
    }
}


class MyFrame;

class MyThread : public wxThread
//-----------------------------------------------------------------------
{
public:
    MyThread(MyFrame* frame);
	void getCurrentFrame();

private:
    MyFrame* m_frame;
    virtual void* Entry();
    CvCapture* capture = NULL;
    IplImage* frame = NULL;
    int key = 0;
    unsigned char* buffer;
};



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
    void OnSetCounter(wxCommandEvent& event);

    void OnOffCam();

    MyPanel* m_panel; // the panel inside the main frame
	wxPanel * m_sidebar; // sidebar panel
    MyThread* m_thread;
    int id = -1;
    bool onoffStatus = false;
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
    ID_TEST,
    ID_FACE2,
    ID_FACE2BW,
    ID_SETSEUIL,
	ID_SETSIZE,
    ID_ONOFFCAM,
	ID_FUSION,
	ID_ERODE
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

<<<<<<< HEAD
=======


>>>>>>> 28a32409ca16854a43a7eef8ecf24b5fce1e794a
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), _T("Show about dialog"));
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);

    menuFile->Append(wxID_ABOUT, wxT("About"));
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

    menuFile->Append(ID_ONOFFCAM, wxT("Camera: on/off ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ONOFFCAM);

    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;

    menuHelp->Append(ID_ENCOUR, wxT("en cour"));
    Bind(wxEVT_MENU, &MyFrame::OnEnCour, this, ID_ENCOUR);

    wxMenu* menuResize = new wxMenu;

    menuResize->Append(ID_RESIZE_UP, wxT("Agrandir...\tCtrl-+"));
    Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_RESIZE_UP);

    menuResize->Append(ID_RESIZE_DOWN, wxT("Reduire...\tCtrl--"));
    Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_RESIZE_DOWN);

    wxMenu* menuImage = new wxMenu;

    menuImage->Append(ID_OPPEN, wxT("Ouvrir...\tCtrl-O"));
    Bind(wxEVT_MENU, &MyFrame::OnOppen, this, ID_OPPEN);

    menuImage->Append(ID_SAVE, wxT("Save...\tCtrl-S"));
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_SAVE);

    wxMenu* menuProcessImage = new wxMenu;

    menuProcessImage->Append(ID_MIROR_H, wxT("Horizontal Miror...\tCtrl-M-H"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MIROR_H);

    menuProcessImage->Append(ID_MIROR_V, wxT("Vertical Miror...\tCtrl-M-V"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MIROR_V);

    menuProcessImage->AppendSeparator();

    menuProcessImage->Append(ID_BLURP, wxT("Blur...\tCtrl-B"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_BLURP);

    menuProcessImage->AppendSeparator();

    menuProcessImage->Append(ID_ROTATION_P90, wxT("Rotation +90 ...\tCtrl-R"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_P90);

    menuProcessImage->Append(ID_ROTATION_M90, wxT("Rotation -90 ...\tCtrl-R"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_M90);

    menuProcessImage->Append(ID_ROTATION_M180, wxT("Rotation 180 ...\tCtrl-T"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROTATION_M180);

    wxMenu* menuProcesse = new wxMenu;

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

    // menuProcesse->Append(ID_TEST, wxT("TEST..\tCtrl-Y"));
    // Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_TEST);

    menuProcesse->AppendSeparator();

    menuProcesse->Append(ID_FACE2, wxT("Face Detection ..\tCtrl-F"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_FACE2);

    menuProcesse->Append(ID_FACE2BW, wxT("Face Detection black and white ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_FACE2BW);
<<<<<<< HEAD

    menuProcesse->Append(ID_SETSEUIL, wxT("Curseur Threshold ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_SETSEUIL);
	menuProcesse->AppendSeparator();

	    menuProcesse->Append(ID_TEST, wxT("test ..\tCtrl-T"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_TEST);

=======

	menuProcesse->Append(ID_FUSION, wxT("Fusion ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_FUSION);

	menuProcesse->Append(ID_ERODE, wxT("Erode ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ERODE);
>>>>>>> ed30bea80f28f790172f66dcceaccf877bbb6cbc

    wxMenu* menuCalcule = new wxMenu;

    menuCalcule->Append(ID_HISTOGRAMCOUNT, wxT("Historgrame...\tCtrl-H"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_HISTOGRAMCOUNT);

	wxMenu* menuCursors = new wxMenu;

	menuCursors->Append(ID_SETSEUIL, wxT("Curseur Threshold ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_SETSEUIL);

	menuCursors->Append(ID_SETSIZE, wxT("Curseur size ..\tCtrl-FBW"));
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_SETSIZE);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("File"));
    menuBar->Append(menuHelp, wxT("Help"));
    menuBar->Append(menuResize, wxT("Resize"));
    menuBar->Append(menuImage, wxT("Image"));
    menuBar->Append(menuProcesse, wxT("Processe"));
	menuBar->Append(menuCalcule, wxT("Calcule"));
	menuBar->Append(menuCursors, wxT("Cursors"));

    SetMenuBar(menuBar);

    CreateStatusBar(3);
    SetStatusText(wxT("une bare qui marche"), 1);

    Bind(wxEVT_MOTION, &MyFrame::OnMouseMove, this);

    this->CenterOnScreen();

    //-------Theread------
	Bind(MY_THREAD_EVENT, &MyFrame::OnSetCounter, this);
	m_thread = new MyThread(this);
	m_thread->Create();
<<<<<<< HEAD
	CvCapture* capture = cvCreateCameraCapture(-1); //-1 or whatever number works for you
	if (capture) //camera is connected
	{
		m_thread->Run();
	}
	else
	{
		cout << "BIEN" << endl;
	}

	m_sidebar = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(200,100));
	wxStaticText *threshold_text = new wxStaticText(m_sidebar, wxID_ANY, wxString("Threshold cursor"), wxPoint(20,10), wxSize(160,10));
	wxSlider *slider_threshold = new wxSlider(m_sidebar, wxID_ANY, 0, 0, 255, wxPoint(20,20), wxSize(160,50),wxSL_HORIZONTAL);
	wxStaticText *size_text = new wxStaticText(m_sidebar, wxID_ANY, wxString("Size cursor"), wxPoint(20,60), wxSize(160,20));
	wxSlider *slider_size = new wxSlider(m_sidebar, wxID_ANY, 0, 0, 255, wxPoint(20,40), wxSize(160,100),wxSL_HORIZONTAL);
	m_panel = new MyPanel(this, m_thread);
	// slider_threshold->GetValue(); // Mettre la bonne valeur
	// slider_size->GetValue();
=======
	m_thread->Run();

	m_panel = new MyPanel(this,m_thread);
>>>>>>> 28a32409ca16854a43a7eef8ecf24b5fce1e794a
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
    if(event.GetId() == ID_SETSEUIL) {
		m_panel->setSeuil();
    } else if(event.GetId() == ID_ONOFFCAM) {
		OnOffCam();
    } else if (event.GetId() == ID_SETSIZE){
		m_panel->setSize();
	} else {
	id = event.GetId();
    }
    //    switch(event.GetId()) {
    //   case ID_ROTATION_P90:
    //	m_panel->Rotate(true);
    //	break;
    //    case ID_ROTATION_M90:
    //	m_panel->Rotate(false);
    //	break;
    //    case ID_ROTATION_M180:
    //	m_panel->Rotate(false);
    //	// m_panel->Rotate(false);
    //	break;
    //    case ID_MIROR_H:
    //	m_panel->Mirror(true);
    //	break;
    //    case ID_MIROR_V:
    //	m_panel->Mirror(false);
    //	break;
    //    case ID_BLURP:
    //	m_panel->Blurp(1);
    //	break;
    //    case ID_NEGATIVE:
    //	m_panel->Negative();
    //	break;
    //    case ID_DESATURE:
    //	m_panel->Desature();
    //	break;
    //    case ID_SEIL:
    //	m_panel->Seil(100);
    //	break;
    //    case ID_POSTERIZE:
    //	m_panel->posterize();
    //	break;
    //	case ID_HISTOGRAMCOUNT:
    //	m_panel->count_histogram();
    //	break;
    //	case ID_CONTRAST:
    //	m_panel->enhenceContrast();
    //	break;
    //	case ID_LUMINA:
    //	m_panel->Lunina();
    //	break;
    //    }
}

//------------------------------------------------------------------------
void MyFrame::OnSetCounter(wxCommandEvent& event)
//------------------------------------------------------------------------
{
    // std::cout<<"on est ici"<<std::endl;
    MyImage* tmp = (MyImage*)event.GetClientData();

    m_panel->drawImage(tmp, id);

    m_panel->addCounter();
}

// Pause/Resume le thread caméra
void MyFrame::OnOffCam()
{
    if(onoffStatus == true) {
		// Recuperer frame en cours et draw()
		// frame -> image


		m_thread->Pause();
		onoffStatus = false;
    } else if(onoffStatus == false) {
		m_thread->Resume();
		onoffStatus = true;
    }
}

//------------TRHEAD------

MyThread::MyThread(MyFrame* frame)
    : m_frame(frame)
//-----------------------------------------------------------------------------
{
    capture = cvCaptureFromCAM(0); // initialize default camera
    if(!capture) {
		fprintf(stderr, "Cannot initialize webcam!\n");
    }
}

//-----------------------------------------------------------------------------
void* MyThread::Entry()
//-----------------------------------------------------------------------------
{
    MyImage* m_image;
    int i = 0;
    while(!TestDestroy()) // tant que le thread n'est pas détruit
    {

	frame = cvQueryFrame(capture); // capture frame
	buffer = (unsigned char*)malloc(frame->height * frame->width * 3);
	IplImageToBuffer(frame, buffer); // convertion de limge en char *
	Sleep(50);                       // pour ne pas envoyer trop d'événements
	wxCommandEvent* evt = new wxCommandEvent(MY_THREAD_EVENT);

	m_image = new MyImage(frame->width, frame->height);
	m_image->SetData(buffer);

	evt->SetClientData(m_image);
	wxQueueEvent(m_frame, evt); // envoie l'événement
    }
    return NULL; // the thread is finished in a clean way
}

MyImage getCurrentFrame() { // en cours
	// set variable MyImage dans m_panel
	// m_image = new MyImage(fileName);
}

void MyPanel::aplyEffect(int id)
{
    switch(id) {
    case ID_ROTATION_P90:
	Rotate(true);
	break;
    case ID_ROTATION_M90:
	Rotate(false);
	break;
    case ID_ROTATION_M180:
	Rotate(false);
	 Rotate(false);
	break;
    case ID_MIROR_H:
	Mirror(true);
	break;
    case ID_MIROR_V:
	Mirror(false);
	break;
    case ID_BLURP:
	Blurp(1);
	break;
    case ID_NEGATIVE:
	Negative();
	break;
    case ID_DESATURE:
	Desature();
	break;
    case ID_SEIL:
	Seil(100);
	break;
    case ID_POSTERIZE:
	posterize();
	break;
    case ID_HISTOGRAMCOUNT:
	count_histogram();
	break;
    case ID_CONTRAST:
	enhenceContrast();
	break;
    case ID_LUMINA:
	Lunina();
	break;
    case ID_TEST:
	test();
	break;
    case ID_FACE2:
	Face2();
	break;
    case ID_FACE2BW:
	Face2BW();
	break;
<<<<<<< HEAD

=======
	case ID_FUSION:
	fusion();
	break;
	case ID_ERODE:
	erode();
	break;
>>>>>>> ed30bea80f28f790172f66dcceaccf877bbb6cbc
    }
}
