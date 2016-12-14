#include <string.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/cv.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <windows.h>
#include <fstream>      // std::ifstream
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	Mat img, templ, img_display, result;

	img = imread( "feed/stop.png", CV_LOAD_IMAGE_GRAYSCALE );
	templ = imread( "semaphores/stop.png", CV_LOAD_IMAGE_GRAYSCALE );
	resize( templ, templ, Size(img.cols/3, img.rows/3) );

	if (img.empty() || templ.empty()) {
		cout << "Invalid images." << endl;
		waitKey(0);
		return 1;
	}

	img.copyTo( img_display );

	int result_cols =  img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create( result_rows, result_cols, CV_32FC1 );
	matchTemplate(img, templ, result, CV_TM_SQDIFF  );

	double minVal; 
	double maxVal; 
	Point minLoc;
	Point maxLoc;

	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

	cout << "Template detected at: " << minLoc << endl;

	rectangle( img_display, minLoc, Point( minLoc.x + templ.cols , minLoc.y + templ.rows ), Scalar(255,0,0),0.3, 8);

	imshow( "Feed", img_display );

	waitKey(0);
	return 0;
}