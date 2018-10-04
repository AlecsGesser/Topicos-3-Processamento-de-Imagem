#ifndef FUNCTION_H
#define FUNCTION_H


void mahalanobisv2(Image &src, unsigned int W, unsigned int H);
void threshold(Image& src, Image& out);
void window_show(char* namewindow, Image& src, bool st);
void kneighboor(Image& src, Image& dst, int r);
void cubo(Image& src, Image& dst, int thr);
void convolution(Image& src,Image& dst, int iterations);




#ifndef 