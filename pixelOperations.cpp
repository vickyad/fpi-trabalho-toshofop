#include "pixelOperations.h"

/* PARTE 1 */
// colorful_flip_x: flip image towards x axis
//     Mat3b& src: colorful image pointer to be flipped
void colorful_flip_x(Mat3b& src) {
    Mat3b _dst(src.rows, src.cols);
    for (int r = 0; r < _dst.rows; ++r) {
        for (int c = 0; c < _dst.cols; ++c) {
            // get pixel
            _dst(r, c) = src(r, src.cols - 1 - c);
        }
    }
    src = _dst;
}

// colorful_custom_flip: flip image towards x or y axis
//     Mat3b& src: colorful image pointer to be flipped 
//     int code: code tha defines if the flip is towards x or y axis
//         code > 0 -> x axis
//         code <= 0 -> y axis
void colorful_custom_flip(Mat3b& src, int code) {
    if (code > 0)
    {   // Flip x axis
        colorful_flip_x(src);
    }
    else {
        // Flip y axis
        src = src.t();
        colorful_flip_x(src);
        src = src.t();
    }
}

// grayscale_flip_x: flip image towards x axis
//     Mat1b& src: grayscale image pointer to be flipped
void grayscale_flip_x(Mat1b& src) {
    Mat1b _dst(src.rows, src.cols);
    for (int r = 0; r < _dst.rows; ++r) {
        for (int c = 0; c < _dst.cols; ++c) {
            // get pixel
            _dst(r, c) = src(r, src.cols - 1 - c);
        }
    }
    src = _dst;
}

// grayscale_custom_flip: flip image towards x or y axis
//     Mat1b& src: grayscale image pointer to be flipped 
//     int code: code tha defines if the flip is towards x or y axis
//         code > 0 -> x axis
//         code <= 0 -> y axis
void grayscale_custom_flip(Mat1b& src, int code) {
    if (code > 0)
    {   // Flip x axis
        grayscale_flip_x(src);
    }
    else {
        // Flip y axis
        src = src.t();
        grayscale_flip_x(src);
        src = src.t();
    }
}


// color_to_grayscale: convert a colorful image to grayscale
//     Mat3b& src: colorful image pointer 
//     Mat1b& dst: pointer for the grayscale image
void color_to_grayscale(const Mat3b& src, Mat1b& dst) {
    dst = Mat::zeros(src.rows, src.cols, CV_8UC1);

    for (int i = 0; i < src.cols; i++) {
        for (int j = 0; j < src.rows; j++) {
            // get pixel
            Vec3b color1 = src.at<Vec3b>(Point(i, j));
            Scalar color2 = dst.at<uchar>(Point(i, j));
            color2 = (0.114 * color1.val[0] + 0.587 * color1.val[1] + 0.299 * color1.val[2]);

            dst.at<uchar>(Point(i, j)) = color2.val[0];
        }
    }
}


// colorful_quatization: quatize a colorful image
//     Mat3b& src: colorful image pointer 
//     int q: how many colors will be used
void colorful_quatization(Mat3b& image1, int q) {
    int divisor = 256 / q;
    int max_quantized_value = 255 / divisor;

    for (int r = 0; r < image1.rows; r++) {
        for (int c = 0; c < image1.cols; c++) {
            // get pixel
            image1.at<Vec3b>(r, c)[0] = ((image1.at<Vec3b>(r, c)[0] / divisor) * 255) / max_quantized_value;
            image1.at<Vec3b>(r, c)[1] = ((image1.at<Vec3b>(r, c)[1] / divisor) * 255) / max_quantized_value;
            image1.at<Vec3b>(r, c)[2] = ((image1.at<Vec3b>(r, c)[2] / divisor) * 255) / max_quantized_value;
        }

    }
}

// quatization: quatize a grayscale image
//     Mat1b& src: grayscale image pointer 
//     int q: how many colors will be used
void quatization(Mat1b& src, int q) {
    int divisor = 256 / q;
    int max_quantized_value = 255 / divisor;

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            src.at<uchar>(r, c) = ((src.at<uchar>(r, c) / divisor) * 255) / max_quantized_value;
        }

    }
}



/* PARTE 2 */
// colorful_negative: convert colorful image to negative
//     Mat3b& src: colorful image pointer
void colorful_negative(Mat3b& src) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            src.at<Vec3b>(r, c)[0] = 255 - src.at<Vec3b>(r, c)[0];
            src.at<Vec3b>(r, c)[1] = 255 - src.at<Vec3b>(r, c)[1];
            src.at<Vec3b>(r, c)[2] = 255 - src.at<Vec3b>(r, c)[2];
        }
    }
}

// grayscale_negative: convert grayscale image to negative
//    Mat1b& src: grayscale image pointer
void grayscale_negative(Mat1b& src) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            src.at<uchar>(r, c) = 255 - src.at<uchar>(r, c);
        }
    }
}


// colorful_brightness: brighten colorful image
//    Mat3b& src: colorful image pointer
//    int value: value to be applied
void colorful_brightness(Mat3b& src, int value) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            for (int i = 0; i < 3; i++) {
                if (src.at<Vec3b>(r, c)[i] + value > 255) {
                    src.at<Vec3b>(r, c)[i] = 255;
                }
                else if (src.at<uchar>(r, c) + value < 0) {
                    src.at<Vec3b>(r, c)[i] = 0;
                }
                else {
                    src.at<Vec3b>(r, c)[i] += value;
                }
            }
        }
    }
}

// grayscale_brightness: brighten grayscale image
//    Mat1b& src: grayscale image pointer
//    int value: value to be applied
void grayscale_brightness(Mat1b& src, int value) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            if (src.at<uchar>(r, c) + value > 255) {
                src.at<uchar>(r, c) = 255;
            }
            else if (src.at<uchar>(r, c) + value < 0) {
                src.at<uchar>(r, c) = 0;
            }
            else {
                src.at<uchar>(r, c) += value;
            }
        }
    }
}

// colorful_contrast: apply contrat filter to colorful image
//    Mat3b& src: colorful image pointer
//    int value: value to be applied
void colorful_contrast(Mat3b& src, int value) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            for (int i = 0; i < 3; i++) {
                if (src.at<Vec3b>(r, c)[i] * value > 255) {
                    src.at<Vec3b>(r, c)[i] = 255;
                }
                else {
                    src.at<Vec3b>(r, c)[i] *= value;
                }
            }
        }
    }
}

// grayscale_contrast: apply contrat filter to grayscale image
//    Mat1b& src: grayscale image pointer
//    int value: value to be applied
void grayscale_contrast(Mat1b& src, int value) {
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            if (src.at<uchar>(r, c) * value > 255) {
                src.at<uchar>(r, c) = 255;
            }
            else {
                src.at<uchar>(r, c) *= value;
            }
        }
    }
}