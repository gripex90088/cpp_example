#include <stdlib.h>

#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <bits/stl_vector.h>

#include "opencv2/imgproc/types_c.h"

using namespace cv;
std::vector<cv::Mat> planes;
cv::Mat complexImage;

void shiftDFT(cv::Mat image)
{
	image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
	int cx = image.cols / 2;
	int cy = image.rows / 2;

	Mat q0 = Mat(image, Rect(0, 0, cx, cy));
	Mat q1 = Mat(image, Rect(cx, 0, cx, cy));
	Mat q2 = Mat(image, Rect(0, cy, cx, cy));
	Mat q3 = Mat(image, Rect(cx, cy, cx, cy));

	cv::Mat tmp = cv::Mat();
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

cv::Mat optimizeImageDim(cv::Mat image)
{
	// init
	cv::Mat padded;
	// get the optimal rows size for dft
	int addPixelRows = cv::getOptimalDFTSize(image.rows);
	// get the optimal cols size for dft
	int addPixelCols = cv::getOptimalDFTSize(image.cols);
	// apply the optimal cols and rows size to the image
	cv::copyMakeBorder(image, padded, 0, addPixelRows - image.rows, 0, addPixelCols - image.cols,
			cv::BORDER_CONSTANT, Scalar::all(0));

	return padded;
}


cv::Mat createOptimizedMagnitude(cv::Mat complexImage)
{
	// init
	std::vector<cv::Mat> newPlanes;
	cv::Mat mag = cv::Mat();
	// split the comples image in two planes
	cv::split(complexImage, newPlanes);
	// compute the magnitude
	cv::magnitude(newPlanes[0], newPlanes[1], mag);

	// move to a logarithmic scale
	cv::add(cv::Mat::ones(mag.size(), CV_32F), mag, mag);
	cv::log(mag, mag);
	// optionally reorder the 4 quadrants of the magnitude image
	shiftDFT(mag);
	// normalize the magnitude image for the visualization since both JavaFX
	// and OpenCV need images with value between 0 and 255
	// convert back to CV_8UC1
	mag.convertTo(mag, CV_8UC1);
	cv::normalize(mag, mag, 0, 255, cv::NORM_MINMAX, CV_8UC1);

	return mag;
}

cv::Mat transformImage(cv::Mat image)
{
	// planes??????????????,???.
	if (!planes.empty()) {
		planes.clear();
	}
	// optimize the dimension of the loaded image
	cv::Mat padded = optimizeImageDim(image);
	padded.convertTo(padded, CV_32F);
	// prepare the image planes to obtain the complex image
	planes.push_back(padded);
	planes.push_back(cv::Mat::zeros(padded.size(), CV_32F));
	// prepare a complex image for performing the dft
	cv::merge(planes, complexImage);
	// dft
	printf("complexImage types %d\n", complexImage.type());
	cv::dft(complexImage, complexImage);

    // optimize the image resulting from the dft operation
    cv::Mat magnitude = createOptimizedMagnitude(complexImage);
    planes.clear();
    return magnitude;
}


void transformImageWithText(cv::Mat image, String watermarkText,
    cv::Point point, double fontSize, Scalar scalar)
{
	// planes??????????????,???.
	if (!planes.empty()) {
		planes.clear();
	}
	// optimize the dimension of the loaded image
	cv::Mat padded = optimizeImageDim(image);
	padded.convertTo(padded, CV_32F);
	printf("padded types %d CV_32FC1 %d\n", padded.type(), CV_32F);
	// prepare the image planes to obtain the complex image
	planes.push_back(padded);
	planes.push_back(cv::Mat::zeros(padded.size(), CV_32F));
	// prepare a complex image for performing the dft
	cv::merge(planes, complexImage);
	printf("complexImage types %d\n", complexImage.type());
	// dft
	cv::dft(complexImage, complexImage);
	// ????????
	cv::putText(complexImage, watermarkText, point, cv::FONT_HERSHEY_DUPLEX, fontSize, scalar,2);
	cv::flip(complexImage, complexImage, -1);
	cv::putText(complexImage, watermarkText, point, cv::FONT_HERSHEY_DUPLEX, fontSize, scalar,2);
	cv::flip(complexImage, complexImage, -1);

	planes.clear();
}

cv::Mat antitransformImage()
{
	cv::Mat invDFT = cv::Mat();
	cv::idft(complexImage, invDFT, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT, 0);
	cv::Mat restoredImage = cv::Mat();
	invDFT.convertTo(restoredImage, CV_8U);
	planes.clear();
	return restoredImage;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("watermark enc/dec file_name\n");
    }
    else
    {
        if (strcmp(argv[1], "enc") == 0)
        {
            //load image
            Point point(50, 100);
            Scalar scalar(0, 0, 0, 0);
            printf("read file %s\n", argv[2]);

    		cv::Mat img1 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
            transformImageWithText(img1, "shennug", point, 2.0, scalar);
            cv::Mat img2 = createOptimizedMagnitude(complexImage);

            cv::Mat img3 = antitransformImage();

            cv::namedWindow("Matrix1", cv::WINDOW_AUTOSIZE);
            cv::imshow("Matrix1", img1);

            cv::namedWindow("Matrix2", cv::WINDOW_AUTOSIZE);
            cv::imshow("Matrix2", img2);

            cv::namedWindow("Matrix3", cv::WINDOW_AUTOSIZE);
            cv::imshow("Matrix3", img3);

            cv::imwrite("1_orig.jpg", img1);
            cv::imwrite("1_watermark.jpg", img2);


            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        if (strcmp(argv[1], "dec") == 0)
        {
            //load image
            Point point(50, 100);
            Scalar scalar(0, 0, 0, 0);
            printf("read file %s\n", argv[2]);

    		cv::Mat img1 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
            transformImage(img1);
            cv::Mat img2 = createOptimizedMagnitude(complexImage);

            cv::Mat img3 = antitransformImage();

            cv::namedWindow("Matrix1", cv::WINDOW_AUTOSIZE);
            cv::imshow("Matrix1", img1);

            cv::namedWindow("Matrix2", cv::WINDOW_AUTOSIZE);
            cv::imshow("Matrix2", img2);
            cv::imwrite("1_decode.jpg", img2);


            cv::waitKey(0);
            cv::destroyAllWindows();
        }

    }

    return 1;

}
