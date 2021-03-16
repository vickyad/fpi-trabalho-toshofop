#include "zoomAndRotationOperations.h"

// grayscale_zoom_out: zoom out a grayscale image based on values given
//     Mat1b& src: grayscale image pointer
//     int x_red: width reduction
//     int y_red: height reduction
void grayscale_zoom_out(Mat1b& src, int x_red, int y_red) {
    Mat1b dst(floor(src.rows / y_red), floor(src.cols / x_red));
    int sum;

    for (int row = 0; row < src.rows; row += y_red) {
        for (int col = 0; col < src.cols; col += x_red) {
            // get pixel
            // calculate avegare value
            sum = 0;
            for (int c = 0; c < x_red; c++) {
                for (int r = 0; r < y_red; r++) {
                    sum += src.at<uchar>(row + r, col + c);
                }
            }
            sum = sum / (x_red + y_red);
            dst.at<uchar>(row / y_red, col / x_red) = sum;
        }
    }

    src = dst;
}

// colorful_zoom_out: zoom out a colorful image based on values given
//     Mat3b& src: colorful image pointer
//     int x_red: width reduction
//     int y_red: height reduction
void colorful_zoom_out(Mat3b& src, int x_red, int y_red) {
    Mat3b reduced(floor(src.rows / y_red), floor(src.cols / x_red));
    int sum_r, sum_b, sum_g;

    for (int row = 0; row < src.rows; row += y_red) {
        for (int col = 0; col < src.cols; col += x_red) {
            // get pixel
            sum_r = 0;
            sum_b = 0;
            sum_g = 0;

            // calculate avegare value
            for (int c = 0; c < x_red; c++) {
                for (int r = 0; r < y_red; r++) {
                    sum_r += src.at<Vec3b>(row + r, col + c)[0];
                    sum_b += src.at<Vec3b>(row + r, col + c)[1];
                    sum_g += src.at<Vec3b>(row + r, col + c)[2];
                }
            }

            sum_r = sum_r / (x_red + y_red);
            sum_b = sum_b / (x_red + y_red);
            sum_g = sum_g / (x_red + y_red);

            reduced.at<Vec3b>(row / y_red, col / x_red)[0] = sum_r;
            reduced.at<Vec3b>(row / y_red, col / x_red)[1] = sum_b;
            reduced.at<Vec3b>(row / y_red, col / x_red)[2] = sum_g;
        }
    }

    src = reduced;
}


// grayscale_zoom_in: zoom in a grayscale image 2 x 2
//     Mat1b& src: grayscale image pointer
void grayscale_zoom_in(Mat1b& src) {
    Mat1b amplied(src.rows * 2 - 1, src.cols * 2 - 1);

    // calculation for even rows from source image:
    // [A B C] => [A (AB)/2 B (BC)/2 C]
    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            // get pixel
            if (col % 2 != 0) {
                amplied.at<uchar>(2 * row, 2 * col - 1) = (src.at<uchar>(row, col - 1) + src.at<uchar>(row, col)) / 2;

                if (col + 1 < src.cols) {
                    amplied.at<uchar>(2 * row, 2 * col + 1) = (src.at<uchar>(row, col + 1) + src.at<uchar>(row, col)) / 2;
                }
            }
            amplied.at<uchar>(2 * row, 2 * col) = src.at<uchar>(row, col);
        }
    }

    // calculation for odd rows already in the amplied image
    // [A (AB)/2 B (BC)/2 C;          [   A     (AB)/2     B      (BC)/2      C  ;
    // ~ blank ~               =>      (AD)/2  (ADBE)/4  (BE)/2  (BECF)/4  (CF)/2
    //  D (DE)/2 E (EF)/2 F]              D     (DE)/2     E      (EF)/2      F  ]
    for (int row = 1; row < amplied.rows - 1; row += 2) {
        for (int col = 0; col < amplied.cols; col++) {
            // get pixel
            if (col % 2 != 0) {
                amplied.at<uchar>(row, col) = (amplied.at<uchar>(row, col - 1) + amplied.at<uchar>(row, col + 1) + amplied.at<uchar>(row - 1, col) + amplied.at<uchar>(row + 1, col)) / 4;
            }
            else {
                amplied.at<uchar>(row, col) = (amplied.at<uchar>(row - 1, col) + amplied.at<uchar>(row + 1, col)) / 2;
            }
        }
    }

    src = amplied;
}

// colorful_zoom_in: zoom in a colorful image 2 x 2
//     Mat3b& src: colorful image pointer
void colorful_zoom_in(Mat3b& src) {
    Mat3b amplied(src.rows * 2 - 1, src.cols * 2 - 1);

    // calculation for even rows from source image:
    // [A B C] => [A (AB)/2 B (BC)/2 C]
    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            // get pixel
            if (col % 2 != 0) {
                amplied.at<Vec3b>(2 * row, 2 * col - 1)[0] = (src.at<Vec3b>(row, col - 1)[0] + src.at<Vec3b>(row, col)[0]) / 2;
                amplied.at<Vec3b>(2 * row, 2 * col - 1)[1] = (src.at<Vec3b>(row, col - 1)[1] + src.at<Vec3b>(row, col)[1]) / 2;
                amplied.at<Vec3b>(2 * row, 2 * col - 1)[2] = (src.at<Vec3b>(row, col - 1)[2] + src.at<Vec3b>(row, col)[2]) / 2;

                if (col + 1 < src.cols) {
                    amplied.at<Vec3b>(2 * row, 2 * col + 1)[0] = (src.at<Vec3b>(row, col + 1) + src.at<Vec3b>(row, col))[0] / 2;
                    amplied.at<Vec3b>(2 * row, 2 * col + 1)[1] = (src.at<Vec3b>(row, col + 1) + src.at<Vec3b>(row, col))[1] / 2;
                    amplied.at<Vec3b>(2 * row, 2 * col + 1)[2] = (src.at<Vec3b>(row, col + 1) + src.at<Vec3b>(row, col))[2] / 2;
                }
            }
            amplied.at<Vec3b>(2 * row, 2 * col)[0] = src.at<Vec3b>(row, col)[0];
            amplied.at<Vec3b>(2 * row, 2 * col)[1] = src.at<Vec3b>(row, col)[1];
            amplied.at<Vec3b>(2 * row, 2 * col)[2] = src.at<Vec3b>(row, col)[2];
        }
    }

    // calculation for odd rows already in the amplied image
    // [A (AB)/2 B (BC)/2 C;          [   A     (AB)/2     B      (BC)/2      C  ;
    // ~ blank ~               =>      (AD)/2  (ADBE)/4  (BE)/2  (BECF)/4  (CF)/2
    //  D (DE)/2 E (EF)/2 F]              D     (DE)/2     E      (EF)/2      F  ]
    for (int row = 1; row < amplied.rows - 1; row += 2) {
        for (int col = 0; col < amplied.cols - 1; col++) {
            // get pixel
            if (col % 2 != 0) {
                amplied.at<Vec3b>(row, col)[0] = (amplied.at<Vec3b>(row, col - 1)[0] + amplied.at<Vec3b>(row, col + 1)[0] + amplied.at<Vec3b>(row - 1, col)[0] + amplied.at<Vec3b>(row + 1, col)[0]) / 4;
                amplied.at<Vec3b>(row, col)[1] = (amplied.at<Vec3b>(row, col - 1)[1] + amplied.at<Vec3b>(row, col + 1)[1] + amplied.at<Vec3b>(row - 1, col)[1] + amplied.at<Vec3b>(row + 1, col)[1]) / 4;
                amplied.at<Vec3b>(row, col)[2] = (amplied.at<Vec3b>(row, col - 1)[2] + amplied.at<Vec3b>(row, col + 1)[2] + amplied.at<Vec3b>(row - 1, col)[2] + amplied.at<Vec3b>(row + 1, col)[2]) / 4;
            }
            else {
                amplied.at<Vec3b>(row, col)[0] = (amplied.at<Vec3b>(row - 1, col)[0] + amplied.at<Vec3b>(row + 1, col)[0]) / 2;
                amplied.at<Vec3b>(row, col)[1] = (amplied.at<Vec3b>(row - 1, col)[1] + amplied.at<Vec3b>(row + 1, col)[1]) / 2;
                amplied.at<Vec3b>(row, col)[2] = (amplied.at<Vec3b>(row - 1, col)[2] + amplied.at<Vec3b>(row + 1, col)[2]) / 2;
            }
        }
    }

    src = amplied;

}


// grayscale_rotate_h: clockwise rotation of grayscale image
//     Mat1b& src: grayscale image pointer
void grayscale_rotate_h(Mat1b& src) {
    Mat1b rotated(src.cols, src.rows);

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            rotated.at<uchar>(c, src.rows - r - 1) = src.at<uchar>(r, c);
        }
    }

    src = rotated;
}

// grayscale_rotate_a: anticlockwise rotation of grayscale image
//     Mat1b& src: grayscale image pointer
void grayscale_rotate_a(Mat1b& src) {
    Mat1b rotated(src.cols, src.rows);

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            rotated.at<uchar>(src.cols - c - 1, r) = src.at<uchar>(r, c);
        }
    }

    src = rotated;
}

// colorful_rotate_h: clockwise rotation of colorful image
//     Mat3b& src: colorful image pointer
void colorful_rotate_h(Mat3b& src) {
    Mat3b rotated(src.cols, src.rows);

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            rotated.at<Vec3b>(c, src.rows - r - 1)[0] = src.at<Vec3b>(r, c)[0];
            rotated.at<Vec3b>(c, src.rows - r - 1)[1] = src.at<Vec3b>(r, c)[1];
            rotated.at<Vec3b>(c, src.rows - r - 1)[2] = src.at<Vec3b>(r, c)[2];
        }
    }

    src = rotated;
}

// colorful_rotate_a: anticlockwise rotation of colorful image
//     Mat3b& src: colorful image pointer
void colorful_rotate_a(Mat3b& src) {
    Mat3b rotated(src.cols, src.rows);

    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            // get pixel
            rotated.at<Vec3b>(src.cols - c - 1, r)[0] = src.at<Vec3b>(r, c)[0];
            rotated.at<Vec3b>(src.cols - c - 1, r)[1] = src.at<Vec3b>(r, c)[1];
            rotated.at<Vec3b>(src.cols - c - 1, r)[2] = src.at<Vec3b>(r, c)[2];
        }
    }

    src = rotated;
}