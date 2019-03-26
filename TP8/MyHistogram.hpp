#ifndef MYHISTOGRAM_HPP
#define MYHISTOGRAM_HPP

#include "MyImage.hpp"
class MyHistogram
{
public:
	MyHistogram(MyImage *img_);
	~MyHistogram();
void GetDynamic(int *minValue, int *maxValue);
private :
unsigned long * tab ;
void count_nblv(MyImage *m_img);

};

#endif // MYHISTOGRAM_HPP
