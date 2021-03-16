#define CVUI_IMPLEMENTATION

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>
#include "cvui.h"
#include "pixelOperations.h"
#include "histogramOperations.h"
#include "zoomAndRotationOperations.h"
#include "convolutionOperations.h"

using namespace cv;
using namespace std;


int main(int argc, char** argv) {
    // Variables
    Mat3b src;
    Mat3b dst;
    Mat1b dst_1;
    const char* imageName = argc >= 2 ? argv[1] : "lena.jpg";
    int histogram[256];
    int cumhistogram[256];
    int count = 1;
    int value = 100;
    int flag = 0;
    int height_reduce = 2;
    int width_reduce = 2;
    int close = 0;
    double k_00 = 0, k_01 = 0, k_02 = 0, k_10 = 0, k_11 = 0, k_12 = 0, k_20 = 0, k_21 = 0, k_22 = 0;


    // Menu frame
    cv::Mat frame = cv::Mat(850, 520, CV_8UC3);

    // Window inicialization
    cvui::init("Menu");

    // Loads an image
    src = imread(samples::findFile(imageName), IMREAD_COLOR);

    // Verify if the image is empty -> if it is empty, return with failure
    if (src.empty()) {
        std::cout << "Error opening image" << endl;
        return EXIT_FAILURE;
    }

    // Make a copy of the image for manipulation
    dst = src.clone();

    // Create a grayscale copy
    color_to_grayscale(dst, dst_1);

    // Show image loaded
    cv:: imshow("Original image", src);

    while (true) {
        // Fill the frame with some color
        frame = cv::Scalar(128, 128, 128);

        // EXPORT IMAGE BUTTON
        if (cvui::button(frame, 10, 10, 160, 20, "Export Image")) {
            string output_file;
            std::cout << "Insira o nome do arquivo: " << endl;
            std::cin >> output_file;
            bool isSuccess;

            // Verify if the last image manipulated is grayscale or colorful
            if (flag) {
                isSuccess = imwrite(output_file, dst_1);
            }
            else {
                isSuccess = imwrite(output_file, dst); //write the image to a file
            }
            if (isSuccess == false) {
                std::printf(" Failed to save the image\n");
                return EXIT_FAILURE;
            }

            std::printf("Image is succusfully saved to a file");

            if (flag) {
                cv::imshow("Saved Image", dst_1);
            }
            else {
                cv::imshow("Saved Image", dst);
            }

            cv::waitKey(0); // Wait for any keystroke in the window

            cv::destroyWindow("Saved Image"); //destroy the created window
        }

        // RESET BUTTON
        if (cvui::button(frame, 10, 30, 160, 20, "Reset")) {
            flag = 0;
            dst = src.clone();
            color_to_grayscale(dst, dst_1);

            cv::imshow("Result Image", dst);
        }

        // FLIP X AXIS BUTTON
        if (cvui::button(frame, 10, 60, 160, 20, "Flip X Axis")) {
            if (flag) {
                grayscale_custom_flip(dst_1, 1);
                cv::imshow("Result Image", dst_1);
            }
            else {
                colorful_custom_flip(dst, 1);
                cv:: imshow("Result Image", dst);
            }
        }

        // FLIP Y AXIS BUTTON
        if (cvui::button(frame, 10, 80, 160, 20, "Flip Y Axis")) {
            if (flag) {
                grayscale_custom_flip(dst_1, 0);
                cv::imshow("Result Image", dst_1);
            }
            else {
                colorful_custom_flip(dst, 0);
                cv::imshow("Result Image", dst);
            }
        }

        // GRAYSCALE BUTTON
        if (cvui::button(frame, 10, 110, 160, 20, "Grayscale")) {
            color_to_grayscale(dst, dst_1);
            cv::imshow("Result Image", dst_1);
            flag = 1;
        }

        // QUANTIZE COLORFUL BUTTON
        if (cvui::button(frame, 10, 140, 160, 20, "Quantize colorful")) {
            if (count > 0) {
                colorful_quatization(dst, count);
                cv::imshow("Result Image", dst);
                flag = 0;
            }
            else {
                std::cout << "You need to choose a number greater than zero" << endl;
            }
        }

        // QUANTIZE GRAYSCALE BUTTON
        if (cvui::button(frame, 10, 160, 160, 20, "Quantize grayscale")) {
            if (count > 0) {
                quatization(dst_1, count);
                cv::imshow("Result Image", dst_1);
                flag = 1;
            } else {
                std::cout << "You need to choose a number greater than zero" << endl;
            }
        }

        // NEGATIVE COLORFUL BUTTON
        if (cvui::button(frame, 10, 190, 160, 20, "Colorful Negative")) {
            colorful_negative(dst);
            cv::imshow("Result Image", dst);
            flag = 0;
        }

        // NEGATIVE GRAYSCALE BUTTON
        if (cvui::button(frame, 10, 220, 160, 20, "Grayscale Negative")) {
            grayscale_negative(dst_1);
            cv::imshow("Result Image", dst_1);
            flag = 1;
        }

        // COLORFUL BRIGHTNESS BUTTON
        if (cvui::button(frame, 10, 250, 160, 20, "Colorful Brightness")) {
            colorful_brightness(dst, value);
            cv::imshow("Result Image", dst);
            flag = 0;
        }

        // GRAYSCALE BRIGHTNESS BUTTON
        if (cvui::button(frame, 10, 270, 160, 20, "Grayscale Brightness")) {
            grayscale_brightness(dst_1, value);
            cv::imshow("Result Image", dst_1);
            flag = 1;
        }

        // COLORFUL CONTRAST BUTTON
        if (cvui::button(frame, 10, 300, 160, 20, "Colorful Contrast")) {
            colorful_contrast(dst, value);
            cv::imshow("Result Image", dst);
            flag = 0;
        }

        // GRAYSCALE CONTRAST BUTTON
        if (cvui::button(frame, 10, 320, 160, 20, "Grayscale Contrast")) {
            grayscale_contrast(dst_1, value);
            cv::imshow("Result Image", dst_1);
            flag = 1;
        }

        // GRAYSCALE HISTOGRAM BUTTON
        if (cvui::button(frame, 10,350, 160, 20, "Histogram")) {
            grayscale_histogram(dst_1, histogram);
        }

        // HISTOGRAM EQUALIZATION BUTTON
        if (cvui::button(frame, 10, 370, 160, 20, "Histogram Equalization")) {
            histogram_equalization(dst_1, histogram, cumhistogram);
            if (flag) {
                grayscale_equalization(dst_1, cumhistogram);
                cv::imshow("Result Image", dst_1);
                flag = 1;
            }
            else {
                colorful_equalization(dst, cumhistogram);
                cv::imshow("Result Image", dst);
                flag = 0;
            }
        }

        // HISTOGRAM MATCHING BUTTON
        if (cvui::button(frame, 10, 390, 160, 20, "Histogram Matching")) {
            string output_file;
            std::cout << "Insira o nome do arquivo: " << endl;
            std::cin >> output_file;
            std::cout << output_file << endl;
            
            Mat1b target = imread(samples::findFile(output_file), IMREAD_GRAYSCALE);
            cv::imshow("Target Image", target);

            histogram_matching(dst_1, target);
            cv::imshow("Result Image", dst_1);
            flag = 1;
        }

        // ZOOM IN BUTTON
        if (cvui::button(frame, 10, 420, 160, 20, "Zoom in")) {
            if (flag) {
                grayscale_zoom_in(dst_1);
                cv::imshow("Result Image", dst_1);
            }
            else {
                colorful_zoom_in(dst);
                cv::imshow("Result Image", dst);
            }
        }

        // ZOOM OUT BUTTON
        if (cvui::button(frame, 10, 440, 160, 20, "Zoom out")) {
            if (flag) {
                grayscale_zoom_out(dst_1, width_reduce, height_reduce);
                cv::imshow("Result Image", dst_1);
            } else {
                colorful_zoom_out(dst, width_reduce, height_reduce);
                cv::imshow("Result Image", dst);
            }
        }

        //ROTATE +90º BUTTON
        if (cvui::button(frame, 10, 520, 160, 20, "Rotate +90")) {
            if (flag) {
                grayscale_rotate_h(dst_1);
                cv::imshow("Result Image", dst_1);
            } else {
                colorful_rotate_h(dst);
                cv::imshow("Result Image", dst);
            }
        }

        //ROTATE -90º BUTTON
        if (cvui::button(frame, 10, 540, 160, 20, "Rotate -90")) {
            if (flag) {
                grayscale_rotate_a(dst_1);
                cv::imshow("Result Image", dst_1);
            } else {
                colorful_rotate_a(dst);
                cv::imshow("Result Image", dst);
            }
        }

        // CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 570, 160, 20, "Convolution")) {
            Mat rotated_kernel = (Mat_<double>(3, 3) << k_22, k_21, k_20, k_12, k_11, k_10, k_02, k_01, k_00);

            if (flag) {
                grayscale_convolution(dst_1, rotated_kernel);
                cv::imshow("Result Image", dst_1);
            } else {
                colorful_convolution(dst, rotated_kernel);
                cv::imshow("Result Image", dst);
            }
        }

        // GAUSSIAN CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 590, 160, 20, "Gaussian Convolution")) {
            Mat kernel = (Mat_<double>(3, 3) << 0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625);
            
            if (flag) {
                grayscale_convolution(dst_1, kernel);
                cv::imshow("Result Image", dst_1);
            } else {
                colorful_convolution(dst, kernel);
                cv::imshow("Result Image", dst);
            }
        }

        // LAPLACIAN CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 610, 160, 20, "Laplacian Convolution")) {
            Mat kernel = (Mat_<double>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);

            grayscale_convolution(dst_1, kernel);
            cv::imshow("Result Image", dst_1);

            grayscale_add_127(dst_1);
            cv::imshow("Result Image +127", dst_1);
        }

        // HIGH-PASS CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 630, 160, 20, "High-pass Convolution")) {
            Mat kernel = (Mat_<double>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);

            grayscale_convolution(dst_1, kernel);
            cv::imshow("Result Image", dst_1);

            grayscale_add_127(dst_1);
            cv::imshow("Result Image +127", dst_1);
        }

        // PREWITT Hx CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 650, 160, 20, "Prewitt Hx Convolution")) {
            Mat rotated_kernel = (Mat_<double>(3, 3) << 1, 0, -1, 1, 0, -1, 1, 0, -1);

            if (flag) {
                grayscale_convolution(dst_1, rotated_kernel);
                cv::imshow("Result Image", dst_1);

                grayscale_add_127(dst_1);
                cv::imshow("Result Image +127", dst_1);
            } else {
                colorful_convolution(dst, rotated_kernel);
                cv::imshow("Result Image", dst);

                colorful_add_127(dst);
                cv::imshow("Result Image +127", dst);
            }
        }
        
        // PREWITT Hy CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 670, 160, 20, "Prewitt Hy Convolution")) {
            Mat rotated_kernel = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);

            if (flag) {
                grayscale_convolution(dst_1, rotated_kernel);
                cv::imshow("Result Image", dst_1);

                grayscale_add_127(dst_1);
                cv::imshow("Result Image +127", dst_1);
            } else {
                colorful_convolution(dst, rotated_kernel);
                cv::imshow("Result Image", dst);

                colorful_add_127(dst);
                cv::imshow("Result Image +127", dst);
            }
        }

        // SOBEL Hx CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 690, 160, 20, "Sobel Hx Convolution")) {
            Mat rotated_kernel = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);

            if (flag) {
                grayscale_convolution(dst_1, rotated_kernel);
                cv::imshow("Result Image", dst_1);

                grayscale_add_127(dst_1);
                cv::imshow("Result Image +127", dst_1);
            } else {
                colorful_convolution(dst, rotated_kernel);
                cv::imshow("Result Image", dst);

                colorful_add_127(dst);
                cv::imshow("Result Image +127", dst);
            }
        }

        // SOBEL Hy CONVOLUTION BUTTON
        if (cvui::button(frame, 10, 710, 160, 20, "Sobel Hy Convolution")) {
            Mat rotated_kernel = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, 2, -1);

            if (flag) {
                grayscale_convolution(dst_1, rotated_kernel);
                cv::imshow("Result Image", dst_1);

                grayscale_add_127(dst_1);
                cv::imshow("Result Image +127", dst_1);
            } else {
                colorful_convolution(dst, rotated_kernel);
                cv::imshow("Result Image", dst);

                colorful_add_127(dst);
                cv::imshow("Result Image +127", dst);
            }
        }

        // Counter for quantize colors
        cvui::counter(frame, 200, 140, &count);

        // Counter for brightness
        cvui::counter(frame, 200, 250, &value);

        // Counter for zoom out
        cvui::text(frame, 10, 465, "Width");
        cvui::counter(frame, 10, 480, &width_reduce);

        cvui::text(frame, 110, 465, "Height");
        cvui::counter(frame, 110, 480, &height_reduce);

        // Counters for convolution
        cvui::counter(frame, 10, 740, &k_22, 0.05);
        cvui::counter(frame, 105, 740, &k_21, 0.05);
        cvui::counter(frame, 200, 740, &k_20, 0.05);

        cvui::counter(frame, 10, 760, &k_12, 0.05);
        cvui::counter(frame, 105, 760, &k_11, 0.05);
        cvui::counter(frame, 200, 760, &k_10, 0.05);

        cvui::counter(frame, 10, 780, &k_02, 0.05);
        cvui::counter(frame, 105, 780, &k_01, 0.05);
        cvui::counter(frame, 200, 780, &k_00, 0.05);

        // Update cvui internal stuff
        cvui::update();

        // Show everything on the screen
        cv::imshow("Menu", frame);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    // Destroy all windows
    destroyAllWindows();

    return EXIT_SUCCESS;
}