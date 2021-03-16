#pragma once
#ifndef CONVOLUTIONOPERATION_H
#define CONVOLUTIONOPERATION_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

/* Parte 2 */
// grayscale_convolution: make an grayscale image convolution with a given kernel
//     Mat1b& src: grayscale image pointer
//     Mat kernel: kernel matrix
void grayscale_convolution(Mat1b& src, Mat kernel);

// colorful_convolution: make an colorful image convolution with a given kernel
//     Mat3b& src: colorful image pointer
//     Mat kernel: kernel matrix
void colorful_convolution(Mat3b& src, Mat kernel);

// grayscale_add_127: add +127 to each pixel on grayscale source image
//     Mat1b& src: grayscale image pointer
void grayscale_add_127(Mat1b& src);

// colorful_add_127: add +127 to each pixel on colorful source image
//     Mat3b& src: colorful image pointer
void colorful_add_127(Mat3b& src);

#endif CONVOLUTIONOPERATION_H