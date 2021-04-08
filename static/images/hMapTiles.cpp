// g++ Desktop/dump.cpp -o output `pkg-config --cflags --libs opencv4` && ./output 
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <functional>
#include <iostream>
#include <dirent.h>
#include <vector>

//int ckt = 0;

using namespace std;
using namespace cv;
void listFiles(const string &path, function<void(const string &)> cb) {
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR) 
                listFiles(path + f->d_name + "/", cb);

            if (f->d_type == DT_REG)
                cb(path + f->d_name);
        }
        closedir(dir);
    }
}

int main(){

    listFiles("/home/kd/Desktop/GSOC_V3/static/images/mask_hm_files/
    ", [](const string &path) {
        cout << path <<endl;
        Mat mSource_Gray,mBlobHeatMap,mHeatMap;
	    mSource_Gray= imread(path,0);

	    threshold(mSource_Gray,mSource_Gray,254,255,THRESH_BINARY);
	    
	    
	    Mat mDist,mBlobDist;
	    distanceTransform(mSource_Gray, mDist, DIST_L2, 3);
	    normalize(mDist, mDist, 0, 1., cv::NORM_MINMAX);
	    mDist.convertTo(mDist,CV_8UC1,255,0);
	   
	    vector<vector<Point> > contours;
	    vector<Vec4i> hierarchy;
	
	    findContours( mSource_Gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	    Mat mBlobMask = Mat::zeros( mSource_Gray.size(), CV_8UC1 );
	    for( size_t i = 0; i< contours.size(); i++ )
	    {
		    drawContours( mBlobMask, contours, (int)i, Scalar(255), -1);
		    mDist.copyTo(mBlobDist,mBlobMask);
		    applyColorMap(mBlobDist,mBlobHeatMap,COLORMAP_JET);
		    GaussianBlur(mBlobHeatMap,mBlobHeatMap,Size(21,21),0,0);
		    mBlobHeatMap.copyTo(mHeatMap,mBlobMask);
	    }
	    try{
	        imwrite(path, mHeatMap);
	    }
	    catch(...){
	        
	    }
    });
}
	    
		
