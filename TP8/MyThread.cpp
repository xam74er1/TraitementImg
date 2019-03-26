#include "MyThread.hpp"



MyThread::MyThread(MyFrame *frame):m_frame(frame)
//-----------------------------------------------------------------------------
{
}

/-----------------------------------------------------------------------------
void* MyThread::Entry()  
//-----------------------------------------------------------------------------
{
    int i = 0;
    while(!TestDestroy())	// tant que le thread n'est pas détruit
    {

      Sleep(50) ;		// pour ne pas envoyer trop d'événements
      wxCommandEvent* evt = new wxCommandEvent(MY_THREAD_EVENT) ;
      evt->SetInt(i++) ;
      wxQueueEvent(m_frame, evt) ;	// envoie l'événement
    }
    return NULL ;	// the thread is finished in a clean way
}


MyThread::~MyThread()
{
}

