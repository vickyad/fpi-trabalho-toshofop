#pragma once
#ifndef PIXELOPERATION_H
#define PIXELOPERATION_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

/* Parte 1 */
// colorful_flip_x: flip colorful image towards x axis
//  Mat3b& src: image pointer to be flipped
void colorful_flip_x(Mat3b& src);

// colorful_custom_flip: flip colorful image towards x or y axis
//  Mat3b& src: image pointer to be flipped 
//  int code: code tha defines if the flip is towards x or y axis
//      code > 0 -> x axis
//      code <= 0 -> y axis
void colorful_custom_flip(Mat3b& src, int code);

// grayscale_flip_x: flip grayscale image towards x axis
//  Mat3b& src: image pointer to be flipped
void grayscale_flip_x(Mat1b& src);

// grayscale_custom_flip: flip grayscale image towards x or y axis
//  Mat3b& src: image pointer to be flipped 
//  int code: code tha defines if the flip is towards x or y axis
//      code > 0 -> x axis
//      code <= 0 -> y axis
void grayscale_custom_flip(Mat1b& src, int code);

// color_to_grayscale: convert a colorful image to grayscale
//  Mat3b& src: colorful image pointer 
//  Mat3b& dst: pointer for the grayscale image
void color_to_grayscale(const Mat3b& src, Mat1b& dst);

// colorful_quatization: quatize a colorful image
//  Mat3b& src: colorful image pointer 
//  int q: how many colors will be used
void colorful_quatization(Mat3b& image1, int q);

// quatization: quatize a grayscale image
//  Mat3b& src: grayscale image pointer 
//  int q: how many colors will be used
void quatization(Mat1b& src, int q);


/* Parte 2 */
// colorful_negative: convert colorful image to negative
//     Mat3b& src: colorful image pointer
void colorful_negative(Mat3b& src);

// grayscale_negative: convert grayscale image to negative
//    Mat1b& src: grayscale image pointer
void grayscale_negative(Mat1b& src);

// colorful_brightness: brighten colorful image
//    Mat3b& src: colorful image pointer
//    int value: value to be applied
void colorful_brightness(Mat3b& src, int value);

// grayscale_brightness: brighten grayscale image
//    Mat1b& src: grayscale image pointer
//    int value: value to be applied
void grayscale_brightness(Mat1b& src, int value);

// colorful_contrast: apply contrat filter to colorful image
//    Mat3b& src: colorful image pointer
//    int value: value to be applied
void colorful_contrast(Mat3b& src, int value);

// grayscale_contrast: apply contrat filter to grayscale image
//    Mat1b& src: grayscale image pointer
//    int value: value to be applied
void grayscale_contrast(Mat1b& src, int value);

#endif PIXELOPERATION_H