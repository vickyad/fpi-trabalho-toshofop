#pragma once
#ifndef HISTOGRAMOPERATION_H
#define HISTOGRAMOPERATION_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

/* Parte 2 */
// plotHistogram: show histogram on screen
//     int histogram[256]: histogram vector
//     const char* name: name of window
void plotHistogram(int histogram[256], const char* name);

// grayscale_histogram:
//     Mat1b& src: grayscale image pointer
//     int (&histogram)[256]: histogram pointer
void grayscale_histogram(Mat1b& src, int(&histogram)[256]);

// histogram_equalization: equalize histogram 
//     Mat1b& src: grayscale image pointer
//     int (&histogram)[256]: pointer to histogram
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void histogram_equalization(Mat1b& src, int(&histogram)[256], int(&cumhistogram)[256]);

// grayscale_equalization: equalize grayscale image according to equalized histogram
//     Mat1b& src: pointer to grayscale image
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void grayscale_equalization(Mat1b& src, int(&cumhistogram)[256]);

// colorful_equalization: equalize colorful image according to equalized histogram
//     Mat3b& src: pointer to colorful image
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void colorful_equalization(Mat3b& src, int(&cumhistogram)[256]);

// histogram_matching: match target image histogram with source image
//     Mat1b& src: pointer to grayscale image
//     Mat1b& target: pointer to grayscale target image
void histogram_matching(Mat1b& src, Mat1b& target);

int map_histograms(int shade, int(&target_histogram)[256]);

#endif HISTOGRAMOPERATION_H