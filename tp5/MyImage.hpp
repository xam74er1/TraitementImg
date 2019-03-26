
#include <wx/wxprec.h>
#include <iostream>
#include <stdio.h>
#ifndef MYIMAGE_HPP
#define MYIMAGE_HPP
#include <iostream>
#include <wx/wx.h>
#include <time.h>
class MyImage : public wxImage
{
public:
	

MyImage(const wxString& fileName) ;
MyImage(wxImage image) ;

MyImage(int largeur, int hauteur) ;
MyImage() ;

void Negative();

void Desature();

void Threshold(int seuil);
void Mirror(bool horizontally);
void Posterize();
MyImage* Rotate90(bool hori);

int count_nbColor();

void EnhenceContrast(int minValue, int maxValue);

void Luninosite(int lum);

void Dither();
void justRed();

	~MyImage();
private :
void permute(unsigned char &a,unsigned char &b);

};

#endif // MYIMAGE_HPP
