// !g++ heat.cpp -o output `pkg-config --cflags --libs opencv4` && ./output 

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int main(){
	Mat mSource_Gray,mBlobHeatMap,mHeatMap;
	mSource_Gray= imread("/home/kd/env/sample.bmp",0);

	//Just making sure everything is binary
	threshold(mSource_Gray,mSource_Gray,254,255,THRESH_BINARY);
	//imshow("Source Image",mSource_Gray);
	//imwrite("./Source.jpg", mSource_Gray);
	
	Mat mDist,mBlobDist;
	distanceTransform(mSource_Gray, mDist, DIST_L2, 3);
	normalize(mDist, mDist, 0, 1., cv::NORM_MINMAX);
	mDist.convertTo(mDist,CV_8UC1,255,0);
	//imshow("mDist",mDist);
	imwrite("./dist.jpg", mDist);
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	/// Find contours to Mask out the Individual Contours
	findContours( mSource_Gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	/// Draw contours (Mask)
	Mat mBlobMask = Mat::zeros( mSource_Gray.size(), CV_8UC1 );
	for( size_t i = 0; i< contours.size(); i++ )
	{
		drawContours( mBlobMask, contours, (int)i, Scalar(255), -1);
		mDist.copyTo(mBlobDist,mBlobMask);
		applyColorMap(mBlobDist,mBlobHeatMap,COLORMAP_JET);
		GaussianBlur(mBlobHeatMap,mBlobHeatMap,Size(21,21),0,0);
		mBlobHeatMap.copyTo(mHeatMap,mBlobMask);
	}

	//imshow("mHeatMap",mHeatMap);
	imwrite("./map.jpg", mHeatMap);
	if ((char)waitKey(10) > 0){};

}


