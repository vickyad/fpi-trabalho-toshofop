#include "convolutionOperations.h"

// grayscale_convolution: make an grayscale image convolution with a given kernel
//     Mat1b& src: grayscale image pointer
//     Mat kernel: kernel matrix
void grayscale_convolution(Mat1b& src, Mat kernel) {
    Mat1b dst(src.rows, src.cols);

    for (int r = 1; r < src.rows - 1; r++) {
        for (int c = 1; c < src.cols - 1; c++) {
            // get pixel
            // calculate new pixel value
            double value = (kernel.at<double>(0, 0) * src.at<uchar>(r - 1, c - 1)) + (kernel.at<double>(0, 1) * src.at<uchar>(r - 1, c)) + kernel.at<double>(0, 2) * src.at<uchar>(r - 1, c + 1)
                + (kernel.at<double>(1, 0) * src.at<uchar>(r, c - 1)) + (kernel.at<double>(1, 1) * src.at<uchar>(r, c)) + kernel.at<double>(1, 2) * src.at<uchar>(r, c + 1)
                + (kernel.at<double>(2, 0) * src.at<uchar>(r + 1, c - 1)) + (kernel.at<double>(2, 1) * src.at<uchar>(r + 1, c)) + kernel.at<double>(2, 2) * src.at<uchar>(r + 1, c + 1);

            if (value > 255) {
                dst.at<uchar>(r, c) = 255;
            }
            else if (value < 0) {
                dst.at<uchar>(r, c) = 0;
            }
            else {
                dst.at<uchar>(r, c) = value;
            }
        }
    }

    src = dst;
}

// colorful_convolution: make an colorful image convolution with a given kernel
//     Mat3b& src: colorful image pointer
//     Mat kernel: kernel matrix
void colorful_convolution(Mat3b& src, Mat kernel) {
    Mat3b dst(src.rows, src.cols);

    for (int r = 1; r < src.rows - 1; r++) {
        for (int c = 1; c < src.cols - 1; c++) {
            // get pixel
            // calculate new pixel value
            double value_r = (kernel.at<double>(0, 0) * src.at<Vec3b>(r - 1, c - 1)[0]) + (kernel.at<double>(0, 1) * src.at<Vec3b>(r - 1, c)[0]) + (kernel.at<double>(0, 2) * src.at<Vec3b>(r - 1, c + 1)[0])
                + (kernel.at<double>(1, 0) * src.at<Vec3b>(r, c - 1)[0]) + (kernel.at<double>(1, 1) * src.at<Vec3b>(r, c)[0]) + (kernel.at<double>(1, 2) * src.at<Vec3b>(r, c + 1)[0])
                + (kernel.at<double>(2, 0) * src.at<Vec3b>(r + 1, c - 1)[0]) + (kernel.at<double>(2, 1) * src.at<Vec3b>(r + 1, c)[0]) + (kernel.at<double>(2, 2) * src.at<Vec3b>(r + 1, c + 1)[0]);

            double value_g = (kernel.at<double>(0, 0) * src.at<Vec3b>(r - 1, c - 1)[1]) + (kernel.at<double>(0, 1) * src.at<Vec3b>(r - 1, c)[1]) + (kernel.at<double>(0, 2) * src.at<Vec3b>(r - 1, c + 1)[1])
                + (kernel.at<double>(1, 0) * src.at<Vec3b>(r, c - 1)[1]) + (kernel.at<double>(1, 1) * src.at<Vec3b>(r, c)[1]) + (kernel.at<double>(1, 2) * src.at<Vec3b>(r, c + 1)[1])
                + (kernel.at<double>(2, 0) * src.at<Vec3b>(r + 1, c - 1)[1]) + (kernel.at<double>(2, 1) * src.at<Vec3b>(r + 1, c)[1]) + (kernel.at<double>(2, 2) * src.at<Vec3b>(r + 1, c + 1)[1]);

            double value_b = (kernel.at<double>(0, 0) * src.at<Vec3b>(r - 1, c - 1)[2]) + (kernel.at<double>(0, 1) * src.at<Vec3b>(r - 1, c)[2]) + (kernel.at<double>(0, 2) * src.at<Vec3b>(r - 1, c + 1)[2])
                + (kernel.at<double>(1, 0) * src.at<Vec3b>(r, c - 1)[2]) + (kernel.at<double>(1, 1) * src.at<Vec3b>(r, c)[2]) + (kernel.at<double>(1, 2) * src.at<Vec3b>(r, c + 1)[2])
                + (kernel.at<double>(2, 0) * src.at<Vec3b>(r + 1, c - 1)[2]) + (kernel.at<double>(2, 1) * src.at<Vec3b>(r + 1, c)[2]) + (kernel.at<double>(2, 2) * src.at<Vec3b>(r + 1, c + 1)[2]);

            if (value_r > 255) {
                dst.at<Vec3b>(r, c)[0] = 255;
            }
            else if (value_r < 0) {
                dst.at<Vec3b>(r, c)[0] = 0;
            }
            else {
                dst.at<Vec3b>(r, c)[0] = value_r;
            }

            if (value_g > 255) {
                dst.at<Vec3b>(r, c)[1] = 255;
            }
            else if (value_g < 0) {
                dst.at<Vec3b>(r, c)[1] = 0;
            }
            else {
                dst.at<Vec3b>(r, c)[1] = value_g;
            }

            if (value_b > 255) {
                dst.at<Vec3b>(r, c)[2] = 255;
            }
            else if (value_b < 0) {
                dst.at<Vec3b>(r, c)[2] = 0;
            }
            else {
                dst.at<Vec3b>(r, c)[2] = value_b;
            }

        }
    }

    src = dst;
}

// grayscale_add_127: add +127 to each pixel on grayscale source image
//     Mat1b& src: grayscale image pointer
void grayscale_add_127(Mat1b& src) {
    for (int r = 1; r < src.rows - 1; r++) {
        for (int c = 1; c < src.cols - 1; c++) {
            // get pixel
            // verify if the pixel will not overflow
            if (src.at<uchar>(r, c) < 128) {
                src.at<uchar>(r, c) += 127;
            }
        }
    }
}

// colorful_add_127: add +127 to each pixel on colorful source image
//     Mat3b& src: colorful image pointer
void colorful_add_127(Mat3b& src) {
    for (int r = 1; r < src.rows - 1; r++) {
        for (int c = 1; c < src.cols - 1; c++) {
            // get pixel
            // verify if the pixel will not overflow
            if (src.at<Vec3b>(r, c)[0] < 128) {
                src.at<Vec3b>(r, c)[0] += 127;
            }

            if (src.at<Vec3b>(r, c)[1] < 128) {
                src.at<Vec3b>(r, c)[1] += 127;
            }

            if (src.at<Vec3b>(r, c)[2] < 128) {
                src.at<Vec3b>(r, c)[2] += 127;
            }
        }
    }
}