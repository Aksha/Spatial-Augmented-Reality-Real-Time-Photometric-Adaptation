#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

/*#include "cv.h"
#include <highgui.h>
#include <vector> */



//========================================================================
int main(int argc, char* argv[]){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 2390,768, OF_WINDOW);			// <-------- setup the GL context
    ofSetWindowPosition(0, 0);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

   /* cv::Mat src = cv::imread(argv[1], 1);

    vector<Point> capturedImage;

    //these are points detect that represent the four corners of the captured image
    capturedImage.push_back(Point( 20 + camWidth, 20));
    capturedImage.push_back(Point(20 + camWidth + camWidth, 20));
    capturedImage.push_back(Point(20 + camWidth, 20 + camHeight));
    capturedImage.push_back(Point(20 + camWidth + camWidth, 20 + camHeight));

    //Drawing lines around the captured image to see the degree of rotation and saving it on disk
    const Point* point = &capturedImage[0];
    int n = (int)not_a_rect_shape.size();
    Mat draw = src.clone();
    polylines(draw, &point, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    imwrite("draw.jpg", draw); */
}
