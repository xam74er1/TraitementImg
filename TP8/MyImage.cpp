#include "MyImage.hpp"
#include <math.h>

using namespace std;
using namespace cv;

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

    unsigned long my, mx;

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

	my = whith % 2 == 0 ? (whith / 2) : (whith / 2) - 1;
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

MyImage* MyImage::Rotate90(bool hori)
{
    unsigned char* in_data = this->GetData();

    MyImage* copie = new MyImage(GetWidth(), GetHeight());

    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    unsigned long pos = 0;
    unsigned long npos = 0;

    unsigned char* out_data = copie->GetData();

    for(int y = 0; y < height; y++) {
	for(int x = 0; x < whith; x++) {
	    pos = (((y)*height) + x) * 3;
	    npos = ((x * height) + (y)) * 3;

	    out_data[npos] = in_data[pos];
	    out_data[npos + 1] = in_data[pos + 1];
	    out_data[npos + 2] = in_data[pos + 2];
	}
    }

    copie->Mirror(hori);
    return copie;
}

void MyImage::Posterize()
{
    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i++) {
	if(in_data[i] > 128) {
	    in_data[i] = 255;
	} else {
	    in_data[i] = 0;
	}
    }
}

int MyImage::count_nbColor()
{
    char* tab = (char*)calloc(256 * 256 * 256, 1);
    unsigned long indice = 0;
    unsigned char r, g, b, l;
    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];
	g = in_data[i + 1];
	b = in_data[i + 2];
	indice = (r << 16) + (g << 8) + b;
	tab[indice] = 1;
    }

    int count = 0;

    for(unsigned long i = 0; i < 255 * 255 * 255; i++) {
	if(tab[i]) {
	    count++;
	}
    }
    return count + 1;
    free(tab);
}

void MyImage::EnhenceContrast(int minValue, int maxValue)
{
    if(minValue > 0 || maxValue < 255) {
	int f = 255 / (maxValue - minValue);
	int d = 255 * minValue / (maxValue - minValue);

	unsigned char* in_data = this->GetData();
	unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
	for(int i = 0; i < sizeTab; i++) {
	    in_data[i] = f * in_data[i] + d;
	}
    }
}

void MyImage::Luninosite(int lum)
{

    unsigned char* in_data = this->GetData();
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    int res;
    for(int i = 0; i < sizeTab; i++) {
	res = in_data[i] + lum;
	if(res > 255) {
	    res = 255;
	} else if(res < 0) {
	    res = 0;
	}
	in_data[i] = (char)res;
    }
}

void MyImage::test()
{

    /*
     unsigned char* in_data = this->GetData();
unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
for(int i = 0; i < sizeTab; i += 3) {
            in_data[i] = in_data[i]+128;
            in_data[i+1] = in_data[i+1]+128;
            in_data[i+2] = in_data[i+2]+128;
    }
     * */
}

void MyImage::colorAtPostion(unsigned long x, unsigned long y)
{

    // std::cout<<" x = "<<x<<" y ="<<y<<std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    // vecteur de mes pt de la tete

    std::vector<unsigned long> vectX;
    std::vector<unsigned long> vectY;

    unsigned long m_x;
    unsigned long m_y;

    for(unsigned long i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;

	    m_x = (i / 3) % (whith);
	    m_y = i / (whith * 3); // semble bon
	    vectX.push_back(m_x);
	    vectY.push_back(m_y);

	} else {
	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }

    // unsigned long  midele = CalcMHWScore(vect);

    x = CalcMHWScore(vectX);
    y = CalcMHWScore(vectY);

    cout << " x : " << x << " y: " << y << endl;
    unsigned long pos;
    for(unsigned long ya = 0; ya < 10; ya++) {
	for(unsigned long xa = 0; xa < 10; xa++) {
	    // std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
	    pos = (((y + ya) * whith) + xa + x) * 3;
	    in_data[pos] = 0;
	    in_data[pos + 1] = 254;
	    in_data[pos + 2] = 0;
	}
    }
}

void MyImage::colorStanfordMetodeBlackAndWhite()
{
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    for(int i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;
	} else {
	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }
}

void MyImage::colorSubriance(unsigned long x, unsigned long y)
{

    std::cout << " x = " << x << " y =" << y << std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();
    unsigned long index = ((y * whith) + x) * 3;

    unsigned char colorR = in_data[index];
    unsigned char colorG = in_data[index + 1];
    unsigned char colorB = in_data[index + 2];

    std::cout << " index : " << index << " , height : " << height << " color : " << (int)colorR << " , " << (int)colorG
              << " , " << (int)colorB << " , " << std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    int seuil = 30;
    int distance = 0;

    std::cout << distanceEuclidienne((int)in_data[0], (int)in_data[1], (int)in_data[2], colorR, colorG, colorB)
              << std::endl;

    for(int i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche
	distance =
	    distanceEuclidienne((int)in_data[i], (int)in_data[i + 1], (int)in_data[i + 2], colorR, colorG, colorB);
	if(distance < seuil) {
	    in_data[i] = 255;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;
	}
    }

    in_data[index + 1] = 254;

    for(int j = 0; j < 100; j += 3) {
	in_data[index + j + 1] = 254;
    }

    unsigned long pos;
    for(unsigned long ya = 0; ya < 10; ya++) {
	for(unsigned long xa = 0; xa < 10; xa++) {
	    // std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
	    pos = (((y + ya) * whith) + xa + x) * 3;
	    in_data[pos + 1] = 254;
	}
    }
}

void MyImage::colorBlackAndWhite(unsigned long x, unsigned long y)
{

    // Source : https://web.stanford.edu/class/ee368/Project_03/Project/reports/ee368group15.pdf
    std::cout << " x = " << x << " y =" << y << std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();
    unsigned long index = ((y * whith) + x) * 3;

    unsigned char colorR = in_data[index];
    unsigned char colorG = in_data[index + 1];
    unsigned char colorB = in_data[index + 2];

    std::cout << " index : " << index << " , height : " << height << " color : " << (int)colorR << " , " << (int)colorG
              << " , " << (int)colorB << " , " << std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    int seuil = 30;
    int distance = 0;

    std::cout << distanceEuclidienne((int)in_data[0], (int)in_data[1], (int)in_data[2], colorR, colorG, colorB)
              << std::endl;

    for(int i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche
	distance =
	    distanceEuclidienne((int)in_data[i], (int)in_data[i + 1], (int)in_data[i + 2], colorR, colorG, colorB);
	if(distance < seuil) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;
	} else {
	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }

    in_data[index + 1] = 254;

    for(int j = 0; j < 100; j += 3) {
	in_data[index + j + 1] = 254;
    }

    unsigned long pos;
    for(unsigned long ya = 0; ya < 10; ya++) {
	for(unsigned long xa = 0; xa < 10; xa++) {
	    // std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
	    pos = (((y + ya) * whith) + xa + x) * 3;
	    in_data[pos + 1] = 254;
	}
    }
}

int MyImage::distanceEuclidienne(int r, int g, int b, int cr, int cg, int cb)
{
    return sqrt((int)((r - cr) * (r - cr) + (g - cg) * (g - cg) + (b - cb) * (b - cb)));
}

unsigned long MyImage::CalcMHWScore(vector<unsigned long> scores, bool isSorted)
{
    size_t size = scores.size();

    if(size == 0) {
	return 0; // Undefined, really.
    } else {
	if(!isSorted) {
	    sort(scores.begin(), scores.end());
	}
	if(size % 2 == 0) {
	    return (scores[size / 2 - 1] + scores[size / 2]) / 2;
	} else {
	    return scores[size / 2];
	}
    }
}

void MyImage::FollowOneFace(unsigned long x, unsigned long y)
{

    // std::cout<<" x = "<<x<<" y ="<<y<<std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    // vecteur de mes pt de la tete

    std::vector<unsigned long> vectX;
    std::vector<unsigned long> vectY;

    unsigned long m_x;
    unsigned long m_y;

    for(unsigned long i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;

	    m_x = (i / 3) % (whith);
	    m_y = i / (whith * 3); // semble bon
	    vectX.push_back(m_x);
	    vectY.push_back(m_y);

	} else {

	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }

    // unsigned long  midele = CalcMHWScore(vect);

    x = CalcMHWScore(vectX);
    y = CalcMHWScore(vectY);

    cout << " x : " << x << " y: " << y << endl;
    unsigned long pos;
    for(unsigned long ya = 0; ya < 10; ya++) {
	for(unsigned long xa = 0; xa < 10; xa++) {
	    // std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
	    pos = (((y + ya) * whith) + xa + x) * 3;
	    in_data[pos] = 0;
	    in_data[pos + 1] = 254;
	    in_data[pos + 2] = 0;
	}
    }
}

void MyImage::FollowOneFaceV2(unsigned long& xd, unsigned long& yd, unsigned long& xf, unsigned long& yf)
{

    // std::cout<<" x = "<<x<<" y ="<<y<<std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    // vecteur de mes pt de la tete

    std::vector<unsigned long> vectX;
    std::vector<unsigned long> vectY;

    unsigned long m_x;
    unsigned long m_y;

    for(unsigned long i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {

	    /*in_data[i] = 0;
	    in_data[i+1] = 0;
	    in_data[i+2] =0;
	     * */

	    m_x = (i / 3) % (whith);
	    m_y = i / (whith * 3); // semble bon
	    vectX.push_back(m_x);
	    vectY.push_back(m_y);

	} else {
	    /*
	    in_data[i] = 255;
	    in_data[i+1] = 255;
	    in_data[i+2] =255;
	     * */
	}
    }

    // unsigned long  midele = CalcMHWScore(vect);

    sort(vectX.begin(), vectX.end());
    sort(vectY.begin(), vectY.end());

    size_t sizeX = vectX.size();
    size_t sizeY = vectY.size();

    int dist = 20;
    // calcule du q1
    xd = vectX[sizeX / dist];
    yd = vectY[sizeY / dist];

    // caclue q3
    xf = vectX[(dist - 1) * sizeX / dist];
    yf = vectY[(dist - 1) * sizeY / dist];

    unsigned long x = CalcMHWScore(vectX);
    unsigned long y = CalcMHWScore(vectY);

    // cout<<" x : "<<x<<" y: "<<y<<endl;
    unsigned long pos;
    for(unsigned long ya = 0; ya < 10; ya++) {
	for(unsigned long xa = 0; xa < 10; xa++) {
	    // std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
	    pos = (((y + ya) * whith) + xa + x) * 3;
	    in_data[pos] = 0;
	    in_data[pos + 1] = 254;
	    in_data[pos + 2] = 0;
	}
    }
}

void MyImage::FollowOneFaceV2BlackAndWhite(unsigned long& xd,
    unsigned long& yd,
    unsigned long& xf,
    unsigned long& yf,
    bool calc)
{

    // std::cout<<" x = "<<x<<" y ="<<y<<std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    // vecteur de mes pt de la tete

    std::vector<unsigned long> vectX;
    std::vector<unsigned long> vectY;

    unsigned long m_x;
    unsigned long m_y;

    for(unsigned long i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;

	    m_x = (i / 3) % (whith);
	    m_y = i / (whith * 3); // semble bon
	    vectX.push_back(m_x);
	    vectY.push_back(m_y);

	} else {
	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }

    // unsigned long  midele = CalcMHWScore(vect);

    if(calc) {
	sort(vectX.begin(), vectX.end());
	sort(vectY.begin(), vectY.end());

	size_t sizeX = vectX.size();
	size_t sizeY = vectY.size();

	int dist = 20;
	// calcule du q1
	xd = vectX[sizeX / dist];
	yd = vectY[sizeY / dist];

	// caclue q3
	xf = vectX[(dist - 1) * sizeX / dist];
	yf = vectY[(dist - 1) * sizeY / dist];

	unsigned long x = CalcMHWScore(vectX);
	unsigned long y = CalcMHWScore(vectY);

	// cout<<" x : "<<x<<" y: "<<y<<endl;
	unsigned long pos;
	for(unsigned long ya = 0; ya < 10; ya++) {
	    for(unsigned long xa = 0; xa < 10; xa++) {
		// std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
		pos = (((y + ya) * whith) + xa + x) * 3;
		in_data[pos] = 0;
		in_data[pos + 1] = 254;
		in_data[pos + 2] = 0;
	    }
	}
    }
}

// ttraitment morpholgique : tuto : https://codes-sources.commentcamarche.net/source/view/40531/1080357#browser
// vers la ligne 329
// dilatation + erotion   = ouverture

// Tuto pour letitage : https://openclassrooms.com/forum/sujet/etiquetage-en-composantes-connexes?page=1

// etiqctage

// idee : passe sur un traitement oppen cv , avec un image

void MyImage::FollowOneFaceV3(unsigned long& xd, unsigned long& yd, unsigned long& xf, unsigned long& yf, bool calc)
{

    // std::cout<<" x = "<<x<<" y ="<<y<<std::endl;
    unsigned char* in_data = this->GetData();
    unsigned long height = this->GetHeight();

    unsigned long whith = this->GetWidth();

    // std::cout<<" index : "<<index<<" , height : "<<height<<" color : "<<(int) colorR<<" , "<<(int) colorG<<" ,
    // "<<(int) colorB<<" , "<<std::endl;

    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;

    unsigned char cb = 0;
    unsigned char cr = 0;

    // vecteur de mes pt de la tete

    std::vector<unsigned long> vectX;
    std::vector<unsigned long> vectY;

    unsigned long m_x;
    unsigned long m_y;

    for(unsigned long i = 0; i < sizeTab; i += 3) {
	// Si la distance est sufisament proche

	cb = 0.257 * in_data[i] - 0.504 * in_data[i + 1] + 0.098 * in_data[i + 2] + 128;
	cr = 0.439 * in_data[i] - 0.368 * in_data[i + 1] - 0.071 * in_data[i + 2] + 128;
	if(140 < cr && cr < 165 && 105 < cb && cb < 135) {
	    in_data[i] = 0;
	    in_data[i + 1] = 0;
	    in_data[i + 2] = 0;

	    m_x = (i / 3) % (whith);
	    m_y = i / (whith * 3); // semble bon
	    vectX.push_back(m_x);
	    vectY.push_back(m_y);

	} else {
	    in_data[i] = 255;
	    in_data[i + 1] = 255;
	    in_data[i + 2] = 255;
	}
    }

    // unsigned long  midele = CalcMHWScore(vect);

    if(calc) {
	sort(vectX.begin(), vectX.end());
	sort(vectY.begin(), vectY.end());

	size_t sizeX = vectX.size();
	size_t sizeY = vectY.size();

	int dist = 20;
	// calcule du q1
	xd = vectX[sizeX / dist];
	yd = vectY[sizeY / dist];

	// caclue q3
	xf = vectX[(dist - 1) * sizeX / dist];
	yf = vectY[(dist - 1) * sizeY / dist];

	unsigned long x = CalcMHWScore(vectX);
	unsigned long y = CalcMHWScore(vectY);

	// cout<<" x : "<<x<<" y: "<<y<<endl;
	unsigned long pos;
	for(unsigned long ya = 0; ya < 10; ya++) {
	    for(unsigned long xa = 0; xa < 10; xa++) {
		// std::cout<<" y :"<<(y+ya)<<" x : "<<(xa+x)<<std::endl;
		pos = (((y + ya) * whith) + xa + x) * 3;
		in_data[pos] = 0;
		in_data[pos + 1] = 254;
		in_data[pos + 2] = 0;
	    }
	}
    }
}
// https://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
// https://docs.opencv.org/2.4.13.7/doc/tutorials/imgproc/opening_closing_hats/opening_closing_hats.html
void MyImage::testOpenCv2()
{
    //---------ZONE OPTION -----
	
	cv::Mat canny_output;
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
	
	int minX,minY,maxX,maxY;

   
    int dilation_type;
    float dilation_size = 17;
    float errode_size = 4;
	float errode_size_b = 6;
    int dilation_elem = 2;

    if(dilation_elem == 0) {
	dilation_type = MORPH_RECT;
    } else if(dilation_elem == 1) {
	dilation_type = MORPH_CROSS;
    } else if(dilation_elem == 2) {
	dilation_type = MORPH_ELLIPSE;
    }

    cv::Mat src_gray;

    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf, false);

    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    unsigned char* tmp = this->GetData();

 MyImage* backup = new MyImage((MyImage) this->Copy());


    cv::Mat m_mat = cv::Mat(cvSize(sx, sy), CV_8UC3, tmp);

    cv::Mat element_dilatation = getStructuringElement(
        dilation_type, cvSize(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));

    cv::Mat element_errode = getStructuringElement(
        dilation_type, cvSize(2 * errode_size + 1, 2 * errode_size + 1), Point(errode_size, errode_size));
		
		 cv::Mat element_errode_b = getStructuringElement(
        dilation_type, cvSize(2 * errode_size_b + 1, 2 * errode_size_b + 1), Point(errode_size_b, errode_size_b));


    /// Apply the dilation operation
    // on invese les couleur on traite , on re invsesse
    bitwise_not(m_mat, m_mat);
    // ouverture
    erode(m_mat, m_mat, element_errode);
    dilate(m_mat, m_mat, element_dilatation);
    erode(m_mat, m_mat, element_errode_b);

    bitwise_not(m_mat, m_mat);

    int thresh = 5;
    int max_thresh = 10;
    RNG rng(12345);

    cvtColor(m_mat, src_gray, CV_BGR2GRAY);
    // blur(src_gray, src_gray, cv::Size(10, 10));

    

    /// Detect edges using canny
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    cv::Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	


    for(int i = 0; i < contours.size(); i++) {
	 //cv::Scalar color = Scalar(0, rng.uniform(0, 255), rng.uniform(0, 255));
	cv::Scalar color = Scalar(255, 0, 0);
	findRectOfVector(contours[i],maxX,maxY,minX,minY);
	
	cv::Point pt1(minX, minY);
	cv::Point pt2(maxX, maxY);
	
	cv::Rect rect(10,10,100,100);
	
	cv::rectangle(drawing, pt1,pt2, color,10,255,0);
	
	//cout<<"min X :"<<minX<<" min Y "<<minY<<" max X "<<maxX<<" max Y"<<maxY<<endl;
	
	drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }

	

    cout << "Il y a " << contours.size() << "diferent " << endl;

    unsigned char* buf = (unsigned char*)malloc(sx * sy * 3);

    matToBuffer(drawing ,buf);

    this->SetData(buf, true);
	
	

    // on repasse sur limage acutel
if(true){
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    unsigned char* in_data = this->GetData();
    unsigned char* backup_data = backup->GetData();


    for(unsigned long i = 0; i < sizeTab; i += 3) {

	// si le pixel nest pas rouge
	if(in_data[i] != 255) {
	    in_data[i] = backup_data[i];
	    in_data[i + 1] = backup_data[i + 1];
	    in_data[i + 2] = backup_data[i + 2];
	}
    }

}
}


//source : http://answers.opencv.org/question/31515/sorting-contours-from-left-to-right-and-top-to-bottom/

void MyImage::findRectOfVector(vector<Point>  vec,int &maxX ,int &maxY , int &minX , int &minY){
	
	 maxX = -1;
	 maxY = -1;
	 minY = 10000000;
	 minX = 10000000;
	
	cv::Point pt;
	for(int i =0;i<vec.size();i++){
		pt = vec[i];
		
		if(pt.x<minX){
			minX = pt.x;
		}
		
		if(pt.x>maxX){
			maxX = pt.x;
		}
		
			if(pt.y<minY){
			minY = pt.y;
		}
		
		if(pt.y>maxY){
			maxY = pt.y;
		}
		
	}
}

void MyImage::testOpenCv()
{

    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf);
    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    IplImage* img = cvCreateImage(cvSize(sy, sx), IPL_DEPTH_8U, 3);

    unsigned char* tmp = this->GetData();
    BufferToIplImage(tmp, img);

    // traitement
    CvScalar p;
    int x, y, k;

    assert(img->depth == IPL_DEPTH_8U);

    for(y = 0; y < img->height; ++y) {
	for(x = 0; x < img->width; ++x) {
	    p = cvGet2D(img, y, x);
	    for(k = 0; k < img->nChannels; ++k) {
		p.val[k] = 255 - p.val[k];
	    }
	    cvSet2D(img, y, x, p);
	}
    }

    // fin du traitement
    unsigned char* buf = (unsigned char*)malloc(img->height * img->width * 3);
    IplImageToBuffer(img, buf);
    this->SetData(buf);
}

void MyImage::BlackAndWhiteResumer()
{
    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf, false);
    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    unsigned char* tmp = this->GetData();

    cv::Mat m_mat = cv::Mat(cvSize(sx, sy), CV_8UC3, tmp);

    int dilation_type;
    float dilation_size = 5;
    int dilation_elem = 2;

    if(dilation_elem == 0) {
	dilation_type = MORPH_RECT;
    } else if(dilation_elem == 1) {
	dilation_type = MORPH_CROSS;
    } else if(dilation_elem == 2) {
	dilation_type = MORPH_ELLIPSE;
    }

    cv::Mat element = getStructuringElement(
        dilation_type, cvSize(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
    /// Apply the dilation operation
    // on invese les couleur on traite , on re invsesse
    bitwise_not(m_mat, m_mat);
    dilate(m_mat, m_mat, element);
    bitwise_not(m_mat, m_mat);

    // fin du traitement

    this->SetData(m_mat.data, true);
}

void MyImage::BlackAndWhiteResumerBig()
{

    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf, false);
    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    unsigned char* tmp = this->GetData();

    cv::Mat m_mat = cv::Mat(cvSize(sx, sy), CV_8UC3, tmp);

    int dilation_type;
    float dilation_size = 15;
    float errode_size = 10;
    int dilation_elem = 2;

    if(dilation_elem == 0) {
	dilation_type = MORPH_RECT;
    } else if(dilation_elem == 1) {
	dilation_type = MORPH_CROSS;
    } else if(dilation_elem == 2) {
	dilation_type = MORPH_ELLIPSE;
    }

    cv::Mat element_dilatation = getStructuringElement(
        dilation_type, cvSize(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));

    cv::Mat element_errode = getStructuringElement(
        dilation_type, cvSize(2 * errode_size + 1, 2 * errode_size + 1), Point(errode_size, errode_size));

    /// Apply the dilation operation
    // on invese les couleur on traite , on re invsesse
    bitwise_not(m_mat, m_mat);
    // ouverture
    dilate(m_mat, m_mat, element_dilatation);
    erode(m_mat, m_mat, element_errode);
    bitwise_not(m_mat, m_mat);

    // fin du traitement

    this->SetData(m_mat.data, true);
}

void MyImage::contourVisage()
{
    cv::Mat src_gray;
    cv::Mat canny_output;
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;

    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf, false);
    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    unsigned char* tmp = this->GetData();

    cv::Mat m_mat = cv::Mat(cvSize(sx, sy), CV_8UC3, tmp);

    int thresh = 5;
    int max_thresh = 10;
    int morph_elem = 2;
    int morph_size = 12;
    int errode_size = 1;
    int operation = MORPH_CLOSE;
    int dilation_type = MORPH_ELLIPSE;
    RNG rng(12345);

    // blur(src_gray, src_gray, cv::Size(3, 3));

    Mat element = getStructuringElement(
        morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    cv::Mat element_errode = getStructuringElement(
        dilation_type, cvSize(2 * errode_size + 1, 2 * errode_size + 1), Point(errode_size, errode_size));

    /*
    bitwise_not(m_mat, m_mat);
    morphologyEx( m_mat, m_mat, operation, element );
     erode(m_mat, m_mat, element_errode);
    bitwise_not(m_mat, m_mat);

     * */
    bitwise_not(m_mat, m_mat);
    dilate(m_mat, m_mat, element_errode);
    bitwise_not(m_mat, m_mat);
    cvtColor(m_mat, src_gray, CV_BGR2GRAY);

    /// Detect edges using canny
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    cv::Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for(int i = 0; i < contours.size(); i++) {
	cv::Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }

    unsigned char* buf = (unsigned char*)malloc(sx * sy * 3);

    matToBuffer(drawing, buf);

    this->SetData(buf, true);
}

void MyImage::matToBuffer(cv::Mat mat, unsigned char* buffer)
{
    int rowSize = mat.step;
    unsigned char* rowAddress = mat.data;
    for(int y = 0; y < mat.rows; y++) {
	memcpy(buffer + y * rowSize, rowAddress, rowSize);
	rowAddress += mat.step;
    }
}

///-------------------


void MyImage::testOpenCv3()
{
    //---------ZONE OPTION -----
	
	cv::Mat canny_output;
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
	
	int minX,minY,maxX,maxY;

   
    int thresh = 5;
    int max_thresh = 10;
    int morph_elem = 2;
    int morph_size = 11;
    int errode_size = 4;
    int operation = MORPH_CLOSE;
    int dilation_type = MORPH_ELLIPSE;
    RNG rng(12345);

    
    cv::Mat src_gray;

    unsigned long xd, yd, xf, yf;

    FollowOneFaceV3(xd, yd, xf, yf, false);

    unsigned long sx = this->GetWidth();
    unsigned long sy = this->GetHeight();
    unsigned char* tmp = this->GetData();




    cv::Mat m_mat = cv::Mat(cvSize(sx, sy), CV_8UC3, tmp);

    Mat element = getStructuringElement(
        morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

    cv::Mat element_errode = getStructuringElement(
        dilation_type, cvSize(2 * errode_size + 1, 2 * errode_size + 1), Point(errode_size, errode_size));
		
		


    /// Apply the dilation operation
    // on invese les couleur on traite , on re invsesse
    bitwise_not(m_mat, m_mat);
    morphologyEx( m_mat, m_mat, operation, element );
     erode(m_mat, m_mat, element_errode);
    bitwise_not(m_mat, m_mat);


 MyImage* backup = new MyImage((MyImage) this->Copy());

    cvtColor(m_mat, src_gray, CV_BGR2GRAY);
    // blur(src_gray, src_gray, cv::Size(10, 10));

    

    /// Detect edges using canny
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    cv::Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	


    for(int i = 0; i < contours.size(); i++) {
	 //cv::Scalar color = Scalar(0, rng.uniform(0, 255), rng.uniform(0, 255));
	cv::Scalar color = Scalar(255, 0, 0);
	findRectOfVector(contours[i],maxX,maxY,minX,minY);
	
	cv::Point pt1(minX, minY);
	cv::Point pt2(maxX, maxY);
	
	cv::Rect rect(10,10,100,100);
	
	cv::rectangle(drawing, pt1,pt2, color,10,255,0);
	
	//cout<<"min X :"<<minX<<" min Y "<<minY<<" max X "<<maxX<<" max Y"<<maxY<<endl;
	
	drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }

	

    cout << "Il y a " << contours.size() << "diferent " << endl;

    unsigned char* buf = (unsigned char*)malloc(sx * sy * 3);

    matToBuffer(drawing ,buf);

    this->SetData(buf, true);
	
	

    // on repasse sur limage acutel
if(true){
    unsigned long sizeTab = this->GetHeight() * this->GetWidth() * 3;
    unsigned char* in_data = this->GetData();
    unsigned char* backup_data = backup->GetData();


    for(unsigned long i = 0; i < sizeTab; i += 3) {

	// si le pixel nest pas rouge
	if(in_data[i] != 255) {
	    in_data[i] = backup_data[i];
	    in_data[i + 1] = backup_data[i + 1];
	    in_data[i + 2] = backup_data[i + 2];
	}
    }

}
}