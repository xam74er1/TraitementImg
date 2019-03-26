#include "MyImage.hpp"
#include <vector> 

MyImage::MyImage(const wxString& fileName)
    : wxImage(fileName)
{
}

MyImage::MyImage(wxImage image)
    : wxImage(image)
{
}

MyImage::MyImage(int largeur, int hauteur)
    : wxImage(largeur, hauteur)
{
}

MyImage::MyImage()
    : wxImage()
{
}

MyImage::~MyImage()
{
}

void MyImage::Negative()
{

    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i++) {
	in_data[i] = 255 - in_data[i];
    }
}

void MyImage::Desature()
{
    unsigned char r, g, b, l;
    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];
	g = in_data[i + 1];
	b = in_data[i + 2];

	l = 0.2126 * r + 0.7152 * g + 0.0722 * b;

	in_data[i] = l;
	in_data[i + 1] = l;
	in_data[i + 2] = l;
    }
}
void MyImage::Threshold(int seuil)
{
    Desature();

    unsigned char r, g, b, l;
    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];

	if(r > seuil) {
	    l = 255;
	} else {
	    l = 0;
	}

	in_data[i] = l;
	in_data[i + 1] = l;
	in_data[i + 2] = l;
    }
}


void MyImage::Mirror(bool horizontally)
{

    unsigned char* in_data = this->GetData();

    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();
	
	unsigned long my,mx ;

    unsigned long pos = 0;
    unsigned long npos = 0;
    if(horizontally) {
		
		
	for(int y = 0; y < height; y++) {
	    for(int x = 0; x < (whith / 2); x++) {
		pos = ((y * height) + x) * 3;
		npos = ((y * height) + (whith - 1 - x)) * 3;
		//
		//		if(x<10&&y<10){
		//			std::cout<<" pos  "<<pos<<" npos "<<npos<<std::endl;
		//			std::cout<<" at pos  "<<int(in_data[pos])<<" at npos
		//"<<int(in_data[npos])<<std::endl;
		//		}

		// r
		permute(in_data[pos], in_data[npos]);
		// g
		permute(in_data[pos + 1], in_data[npos + 1]);
		// b
		permute(in_data[pos + 2], in_data[npos + 2]);
	    }
	}
    } else {
		
		my = whith %2==0 ? (whith / 2) : (whith / 2)-1;
	for(int y = 0; y < my; y++) {
	    for(int x = 0; x < whith; x++) {
		pos = ((y * height) + x) * 3;
		npos = (((height - 1 - y) * height) + (x)) * 3;
		// r
		permute(in_data[pos], in_data[npos]);
		// g
		permute(in_data[pos + 1], in_data[npos + 1]);
		// b
		permute(in_data[pos + 2], in_data[npos + 2]);
	    }
	}
    }
}

void MyImage::permute(unsigned char& a, unsigned char& b)
{
    unsigned char tmp = a;
    a = b;
    b = tmp;
}

MyImage* MyImage::Rotate90(bool hori){
    unsigned char* in_data = this->GetData();
	
	MyImage *copie = new MyImage(GetWidth(),GetHeight());
	
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    unsigned long pos = 0;
    unsigned long npos = 0;
	
	unsigned char* out_data = copie->GetData();
  
	for(int y = 0; y < height; y++) {
	    for(int x = 0; x < whith ; x++) {
		pos = (((y) * height) + x) * 3;
		npos = ((x * height) + (y)) * 3;
		
		out_data[npos] = in_data[pos];
		out_data[npos+1] = in_data[pos+1];
		out_data[npos+2] = in_data[pos+2];
	    }
	}
	
	copie->Mirror(hori);
	return copie;
 
}

void MyImage::Posterize(){
	 unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i ++) {
		if(in_data[i]>128){
			in_data[i] = 255;
		}else{
			in_data[i] = 0;
		}
	}
}

int MyImage::count_nbColor(){
	char* tab = (char *) calloc(256*256*256, 1); 
	unsigned long indice = 0;
	 unsigned char r, g, b, l;
    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];
	g = in_data[i + 1];
	b = in_data[i + 2];
	indice = (r<<16)+(g<<8)+b;
	tab[indice]=1;
	}
	
	int count = 0;
	
	for(unsigned long i=0; i<255*255*255; i++) {
		if(tab[i]){
			count++;
		}
	}
	return count+1;
	free(tab);

}

void MyImage::EnhenceContrast(int minValue, int maxValue){
	if(minValue>0||maxValue<255){
		int f = 255/(maxValue- minValue);
		int d = 255*minValue/(maxValue- minValue);
		
		unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i ++) {
		in_data[i] = f * in_data[i]+d;
	}
}
}



void MyImage::Luninosite(int lum){

		
		unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
	int res;
    for(int i = 0; i < sizeTab; i ++) {
		res = in_data[i]+lum;
		if(res>255){
			res= 255;
		}else if(res<0){
			res = 0;
		}
		in_data[i] = (char) res;
	}
}

void MyImage::Dither(){
	std::cout<<"distubing"<<std::endl;
	//Peutre inutille , si plus grand que 128 jaroundi au sup si non au dessou 
	
	/*unsigned char * tabColor[8][3] = {
		{0,0,0},{0,255,0},{0,0,255},{0,255,255},
		{255,0,0},{255,255,0},{255,255,255},{255,0,255}
		};
		 * */
	char  tabErreur[3] = {0,0,0};
	//i = ylenght*y+x 
	//y = i/largeur 
	//x = i%longeur
	
	unsigned char* in_data = this->GetData();
	unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
	unsigned long longeur = this->GetHeight();
	unsigned long largeur = this->GetWidth();
	
	unsigned long x =0;
	unsigned long y=0;
	unsigned long index = 0;
	
	int erreur = 0;
	int erreur_tmp=0;
	
	unsigned char r,g,b,nr,ng,nb;
	
	for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];
	g = in_data[i + 1];
	b = in_data[i + 2];
	
	//for(int j =0;j<8;j++){
		//distance eucldientde 
		//erreur_tmp = (r-tab[j][0])*(r-tab[j][0])+;
		
		//Aroundi des couleur 
		 nr = r>128 ? 255 : 0;
		 ng = g>128 ? 255 : 0;
		 nb = b>128 ? 255 : 0;
		
		tabErreur[0] = (char ) -(r - nr);
		tabErreur[1] = (char ) -(g - ng);
		tabErreur[2] = (char ) -(b - nb);
	
		
		//aplication des nouvelle couleur 
		in_data[i]=nr ;
		in_data[i+1]=ng ;
		in_data[i+2]=nb;
		
		//aplication ds nvll couleur 
		 x = i%longeur;
		 y = i/largeur;
		
		//x+1
		index = i+3;
		
		in_data[index] =(tabErreur[0]*7)/16+in_data[index] > 255 ? 255 :(tabErreur[0]*7)/16+in_data[index]; 
		in_data[index+1] =(tabErreur[1]*7)/16+in_data[index] > 255 ? 255 :(tabErreur[1]*7)/16+in_data[index+1]; 
		in_data[index+2] =(tabErreur[2]*7)/16+in_data[index] > 255 ? 255 :(tabErreur[2]*7)/16+in_data[index+2]; 
		
		//y +1 
		
		index = i +largeur;
		
		
		in_data[index] =(tabErreur[0]*5)/16+in_data[index] > 255 ? 255 :(tabErreur[0]*5)/16+in_data[index]; 
		in_data[index+1] =(tabErreur[1]*5)/16+in_data[index] > 255 ? 255 :(tabErreur[1]*5)/16+in_data[index+1]; 
		in_data[index+2] =(tabErreur[2]*5)/16+in_data[index] > 255 ? 255 :(tabErreur[2]*5)/16+in_data[index+2]; 
		
		//x+1 y +1 
		
		index +=3;
		
		in_data[index] =(tabErreur[0]*3)/16+in_data[index] > 255 ? 255 :(tabErreur[0]*3)/16+in_data[index]; 
		in_data[index+1] =(tabErreur[1]*3)/16+in_data[index] > 255 ? 255 :(tabErreur[1]*3)/16+in_data[index+1]; 
		in_data[index+2] =(tabErreur[2]*3)/16+in_data[index] > 255 ? 255 :(tabErreur[2]*3)/16+in_data[index+2]; 
		
		//x-1 y+1
		
		//index -3 -3 
		index -=6;
		
		in_data[index] =(tabErreur[0]*1)/16+in_data[index] > 255 ? 255 : (tabErreur[0]*1)/16+in_data[index]; 
		in_data[index+1] =(tabErreur[1]*1)/16;+in_data[index] > 255 ? 255 :(tabErreur[1]*1)/16+in_data[index+1]; 
		in_data[index+2] =(tabErreur[2]*1)/16+in_data[index] > 255 ? 255 :(tabErreur[2]*1)/16+in_data[index+2]; 
	//}
	
	}
}

void MyImage::justRed(){
	
	 unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
		in_data[i] = 0;
		//in_data[i+1] = 0;
		in_data[i+2] = 0;
	}
}