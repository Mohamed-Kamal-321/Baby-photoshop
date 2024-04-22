#include<iostream>
using namespace std;
#ifndef FILTERS_H
#define FILTERS_H
#include <QImage>
#include<string>

using namespace std;
class filters
{
private:
     bool flag;
public:
    filters();
    void greyscale(QImage& image);
    void Black_and_White(QImage& image);
    void invert(QImage& image);
    void lighten(QImage& image);
    void darken(QImage& image);
    void Detect_Image_Edges(QImage& image);
    void blur(QImage& image);
    void wano(QImage& s);
    void old_tv(QImage& image);
    void purple(QImage& s);
    void infrared(QImage& s);
    void oil_paint(QImage& img);
    void flip_horizontal(QImage& img);
    void flip_vertical(QImage& img);
    void rotate(QImage& img);
    void blur_edges(QImage&s);
    void fancy1_frame(QImage& img);
    void resizeImage(QImage& image, int newWidth, int newHeight);
    void merge(QImage& image,QImage &image2);
    void Contrast_minus(QImage& image);
    void Contrast_plus(QImage& image);
    void applySepiaTone(QImage& image);
    void crop(QImage& image, int x, int y, int w, int h);
    void skew(QImage& s, double skewAngle);
    void no_aspect(QImage& image, int newWidth, int newHeight);
    void aspect_height(QImage& image, int newHeight);
    void aspect_width(QImage& image, int newWidth);
    void simple(QImage& s, int thickness, QString color);
    void fancy1(QImage& img);
    void white(QImage& img);
    void black(QImage& img);
    void frame(QImage& img, int choice);

};

#endif // FILTERS_H
