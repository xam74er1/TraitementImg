
#include <wx/wxprec.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <wx/wx.h>
wxDECLARE_EVENT(MON_EVENEMENT, wxCommandEvent);
class MyThresholdDialog : public wxDialog
{
private:	
	wxButton* m_okButton;
	wxButton* m_cancelButton;
public:
	wxSlider* m_threshold;
	MyThresholdDialog( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ,int min=0 , int max=255 , int actual = 128);
		~MyThresholdDialog();
		void OnScroll( wxScrollEvent& event );
};


