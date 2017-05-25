#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;

        int point_x[4];
        int point_y[4];
        ofMesh mesh;
        ofImage img;
        ofImage meshImage;
        ofImage originalImage;
        ofImage img2;
        ofPoint pointClicked[4];
		ofPoint corners[4];
        unsigned char * diffImage;
		ofTexture diffTexture;


        int selectedCorner;
        float width, height;

        void ofxQuadWarp(ofBaseHasTexture &tex, ofPoint lt, ofPoint rt, ofPoint rb, ofPoint lb, int rows, int cols) ;
        ofPoint ofxLerp(ofPoint start, ofPoint end, float amt);
        int ofxIndex(float x, float y, float w);

		ofVideoPlayer 		fingerMovie;
		bool                frameByframe;
};
