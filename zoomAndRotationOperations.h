#pragma once
#pragma once
#ifndef ZOOMANDROTATIONOPERATIONS_H
#define ZOOMANDROTATIONOPERATIONS_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

// Parte 2
// grayscale_zoom_out: zoom out a grayscale image based on values given
//     Mat1b& src: grayscale image pointer
//     int x_red: width reduction
//     int y_red: height reduction
void grayscale_zoom_out(Mat1b& src, int x_red, int y_red);

// colorful_zoom_out: zoom out a colorful image based on values given
//     Mat3b& src: colorful image pointer
//     int x_red: width reduction
//     int y_red: height reduction
void colorful_zoom_out(Mat3b& src, int x_red, int y_red);

// grayscale_zoom_in: zoom in a grayscale image 2 x 2
//     Mat1b& src: grayscale image pointer
void grayscale_zoom_in(Mat1b& src);

// colorful_zoom_in: zoom in a colorful image 2 x 2
//     Mat3b& src: colorful image pointer
void colorful_zoom_in(Mat3b& src);

// grayscale_rotate_h: clockwise rotation of grayscale image
//     Mat1b& src: grayscale image pointer
void grayscale_rotate_h(Mat1b& src);

// grayscale_rotate_a: anticlockwise rotation of grayscale image
//     Mat1b& src: grayscale image pointer
void grayscale_rotate_a(Mat1b& src);

// colorful_rotate_h: clockwise rotation of colorful image
//     Mat3b& src: colorful image pointer
void colorful_rotate_h(Mat3b& src);

// colorful_rotate_a: anticlockwise rotation of colorful image
//     Mat3b& src: colorful image pointer
void colorful_rotate_a(Mat3b& src);

#endif ZOOMANDROTATIONOPERATIONS_H