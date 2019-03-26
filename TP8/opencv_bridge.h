#ifndef OPENCV_BRIDGE_H

#include <opencv/cv.h>
#define OPENCV_BRIDGE_H



void IplImageToBuffer(IplImage* iImage, unsigned char* buffer) ;
void BufferToIplImage(unsigned char* buffer, IplImage* iImage) ;

#endif // OPENCV_BRIDGE_H
