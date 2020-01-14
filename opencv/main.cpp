/*
 * main.cpp
 *
 *  Created on: Oct 31, 2019
 *      Author: xuxing
 */
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

void paintCircle(char **argv)
{
	Mat image = imread(argv[1]);
	Point center = Point(500, 500);
	Scalar color = Scalar(0, 255, 0);
	circle(image, center, 100, color, 8);
	imwrite("out.jpg", image);
}

void paintLine(char **argv)
{
	Mat image = imread(argv[1]);

	Point start = Point(0, 0);
	Point end = Point(500, 500);
	Scalar color = Scalar(0, 255, 0);
	line(image, start, end, color);
	imwrite("out_line.jpg", image);
}

void paintImg(char **argv)
{
	Mat srcImage = imread(argv[1]);
	Mat signal = imread(argv[2]);

	Mat imageROI = srcImage(Rect(300, 500, signal.cols, signal.rows));
	Mat mask = imread(argv[2], 0);
	signal.copyTo(imageROI, mask);
//	namedWindow("ROI图像叠加");
	imshow("ROI图像叠加demo", srcImage);
	waitKey();
}

int main(int argc, char **argv)
{
	paintCircle(argv);
	paintLine(argv);
	paintImg(argv);
	return EXIT_SUCCESS;
}
