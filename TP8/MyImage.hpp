
#include <wx/wxprec.h>
#include <iostream>
#include <stdio.h>
#ifndef MYIMAGE_HPP
#define MYIMAGE_HPP
#include <iostream>
#include <wx/wx.h>
#include <time.h>
#include <vector> 
#include <algorithm>
using namespace std;
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

void test();

void colorAtPostion(unsigned long x, unsigned long y );

void colorSubriance(unsigned long x, unsigned long y );

void colorBlackAndWhite(unsigned long x, unsigned long y );

void colorStanfordMetodeBlackAndWhite();

void FollowOneFaceV2(unsigned long &xd, unsigned long &yd,unsigned long &xf, unsigned long &yf );

void FollowOneFaceV2BlackAndWhite(unsigned long &xd, unsigned long &yd,unsigned long &xf, unsigned long &yf ,bool calc = true);

void FollowOneFaceV3(unsigned long &xd, unsigned long &yd,unsigned long &xf, unsigned long &yf ,bool calc = true);

	~MyImage();
private :
void permute(unsigned char &a,unsigned char &b);

unsigned long CalcMHWScore(vector<unsigned long > scores,bool isSorted=false);

int distanceEuclidienne(int r , int g ,int b , int cr , int cg , int cb);

void FollowOneFace(unsigned long x, unsigned long y );



};

#endif // MYIMAGE_HPP
