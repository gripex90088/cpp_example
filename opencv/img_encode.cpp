/*
 ============================================================================
 Name        : img_encode.cpp
 Author      : JianRong
 Version     :
 Copyright   : Your copyright notice
 Description : <opencv> image encode, Ansi-style,
 	 	 	   image coding for network transmission
 ============================================================================
 */

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::stringstream;

int main()
{
	cv::Mat img = cv::imread("./emoji/happy.png", CV_LOAD_IMAGE_COLOR);
	vector<uchar> data_encode;
	cv::imencode(".jpg", img, data_encode);

	string str_encode(data_encode.begin(), data_encode.end());
	ofstream ofs("out.txt");
	assert(ofs.is_open());
	ofs << str_encode;
	ofs.flush();
	ofs.close();

	ifstream ifs("out.txt");
	assert(ifs.is_open());
	stringstream sstr;
	while (ifs >> sstr.rdbuf());
	ifs.close();
	cv::Mat img_decode;
	string str_tmp = sstr.str();
	vector<uchar> data(str_tmp.begin(), str_tmp.end());
	img_decode = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);
	cv::imshow("pic", img_decode);
	cvWaitKey(10000);

	return 0;
}
