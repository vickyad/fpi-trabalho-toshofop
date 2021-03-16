#include "histogramOperations.h"

// plotHistogram: show histogram on screen
//     int histogram[256]: histogram vector
//     const char* name: name of window
void plotHistogram(int histogram[256], const char* name) {
    int hist_w = 256, hist_h = 256;
    int bin_w = 1;
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    // find the maximum intensity element from histogram
    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    int norm_hist[256];

    // normalize the histogram between 0 and histImage.rows
    for (int i = 0; i < 256; i++) {
        norm_hist[i] = ((double)histogram[i] / max) * histImage.rows;
    }

    // plot histogram
    for (int i = 1; i < 256; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - norm_hist[i - 1]),
            Point(bin_w * (i), hist_h - norm_hist[i]),
            Scalar(255, 255, 255), 1, 8, 0);
    }

    imshow(name, histImage);
}

// grayscale_histogram:
//     Mat1b& src: grayscale image pointer
//     int (&histogram)[256]: histogram pointer
void grayscale_histogram(Mat1b& src, int(&histogram)[256]) {
    int position;

    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for (int row = 0; row < src.rows; ++row) {
        for (int col = 0; col < src.cols; ++col) {
            // get pixel
            position = (int)src(row, col);

            // add to position
            histogram[position] += 1;
        }
    }

    plotHistogram(histogram, "Histogram");
}

// histogram_equalization: equalize histogram 
//     Mat1b& src: grayscale image pointer
//     int (&histogram)[256]: pointer to histogram
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void histogram_equalization(Mat1b& src, int(&histogram)[256], int(&cumhistogram)[256]) {
    // Calculate the size of image
    int size = src.rows * src.cols;
    float alpha = 255.0 / size;

    // Calculate cummulative histogram
    cumhistogram[0] = alpha * histogram[0];

    for (int i = 1; i < 256; i++) {
        cumhistogram[i] = alpha * histogram[i] + cumhistogram[i - 1];
    }
}

// grayscale_equalization: equalize grayscale image according to equalized histogram
//     Mat1b& src: pointer to grayscale image
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void grayscale_equalization(Mat1b& src, int(&cumhistogram)[256]) {
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            // get pixel
            src.at<uchar>(y, x) = (cumhistogram[src.at<uchar>(y, x)]);
        }
    }

    plotHistogram(cumhistogram, "Equalized Histogram");
}

// colorful_equalization: equalize colorful image according to equalized histogram
//     Mat3b& src: pointer to colorful image
//     int (&cumhistogram)[256]: pointer to cummulative histogram
void colorful_equalization(Mat3b& src, int(&cumhistogram)[256]) {
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            // get pixel
            src.at<Vec3b>(y, x)[0] = (cumhistogram[src.at<Vec3b>(y, x)[0]]);
            src.at<Vec3b>(y, x)[1] = (cumhistogram[src.at<Vec3b>(y, x)[1]]);
            src.at<Vec3b>(y, x)[2] = (cumhistogram[src.at<Vec3b>(y, x)[2]]);
        }
    }

    plotHistogram(cumhistogram, "Equalized Histogram");
}

int map_histograms(int shade, int(&target_histogram)[256]) {
    int position = 0;

    while (target_histogram[position] != shade && position < 256) {
        position++;
    }

    return position;
}

// histogram_matching: match target image histogram with source image
//     Mat1b& src: pointer to grayscale image
//     Mat1b& target: pointer to grayscale target image
void histogram_matching(Mat1b& src, Mat1b& target) {
    int src_histogram[256], cum_src_hist[256];
    int target_histogram[256], cum_target_hist[256];
    int HM_hist[256];

    int src_size = src.cols * src.rows;
    int target_size = target.cols * target.rows;

    // calculate target histogram
    grayscale_histogram(target, target_histogram);
    histogram_equalization(target, target_histogram, cum_target_hist);

    grayscale_histogram(src, src_histogram);
    histogram_equalization(src, src_histogram, cum_src_hist);

    // find the maximum intensity element from histogram
    int max_target = cum_target_hist[0];
    int max_src = cum_src_hist[0];
    for (int i = 1; i < 256; i++) {
        if (max_target < cum_target_hist[i]) {
            max_target = cum_target_hist[i];
        }

        if (max_src < cum_src_hist[i]) {
            max_src = cum_src_hist[i];
        }
    }

    int target_norm_hist[256];
    int src_norm_hist[256];

    // normalize the histogram between 0 and histImage.rows
    for (int i = 0; i < 256; i++) {
        target_norm_hist[i] = ((double)cum_target_hist[i] / max_target * target_size);
        src_norm_hist[i] = ((double)cum_src_hist[i] / max_src * src_size);
    }

    for (int i = 0; i < 256; i++) {
        HM_hist[i] = src_norm_hist[map_histograms(src_norm_hist[i], target_norm_hist)];
    }

    // apply target histogram to image source
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            // get pixel
            src.at<uchar>(y, x) = (HM_hist[src.at<uchar>(y, x)]);
        }
    }
}

