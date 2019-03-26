#include "MyHistogram.hpp"

MyHistogram::MyHistogram(MyImage *img_)
{	//un talbeu vide de 255 
	tab = (unsigned long *) calloc(256, sizeof(unsigned long)); 
	count_nblv(img_);
}

MyHistogram::~MyHistogram()
{
}

void MyHistogram::count_nblv(MyImage *m_img){
	 unsigned char r, g, b;
	 int l;
    unsigned char* in_data = m_img->GetData();
    unsigned long sizeTab = m_img->GetHeight() * m_img->GetWidth() * 3;
    for(int i = 0; i < sizeTab; i += 3) {
	r = in_data[i];
	g = in_data[i + 1];
	b = in_data[i + 2];

	l = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		this->tab[l]++;
    }
	
	

}

void MyHistogram::GetDynamic(int *minValue, int *maxValue){
	*minValue = -1;
	*maxValue = -1;

/*
	int i = 0;
	
	while(i<255&&tab[i]!=0){
		i++;
	}
	
	*minValue=i;
	
	i = 255;
	
	while(i>0&&tab[i]!=0){
		i--;
	}
	
	*maxValue=i;
	* 
	* */
	
	for(int  i=0;  i<255; i++) {
		if(*minValue==-1&&this->tab[i]!=0){
			*minValue = i;
		}
	
		if(this->tab[i]!=0){
			*maxValue =i;
		}
	
	}

}