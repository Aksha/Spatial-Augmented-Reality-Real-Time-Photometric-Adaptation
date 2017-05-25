#include "testApp.h"

int which_point = 0;

//--------------------------------------------------------------
void testApp::setup(){

	camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 480;
    img.loadImage("rocks.jpg"); // this is the original image
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);  //To use the external camera
	vidGrabber.initGrabber(camWidth,camHeight);
    vidGrabber.setDesiredFrameRate(84);
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);


    diffImage = new unsigned char[320*240*3];
   // diffTexture.allocate(320, 240, GL_RGB);

    //To be able to select the points
    pointClicked[0].set(0,0);
    pointClicked[1].set(320,0);
    pointClicked[2].set(320,240);
    pointClicked[3].set(0,240);


     for(int i=0;i<4;i++){
            point_x[i] = 5;
            point_y[i] = 5;
    }

}


//--------------------------------------------------------------
void testApp::update(){

	//ofBackground(100,100,100);

	vidGrabber.update();
    // Edge detection program
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();


        for (int i = camWidth*3+3; i < totalPixels-camWidth*3-3; i+=3){
                 videoInverted[i] = pixels[i]*(0.2126) + pixels[i+1]*(0.7152) + pixels[i+2]*(0.0722);
                 videoInverted[i] = 127+( pixels[i-(3*camWidth) - 3] * -1 + pixels[ i-(3*camWidth)] * 0 + pixels[i-(3*camWidth) + 3] * 1
                                    +pixels[i-3]* -2 + pixels[i]* 0 + pixels[i+3] * 2
                                    + pixels[i + (3*camWidth) - 3] * -1 + pixels[ i+(3*camWidth)] * 0 + pixels[i+(3*camWidth) + 3] * 1)/8;
                 videoInverted[i+1] = videoInverted[i];
                 videoInverted[i+2] = videoInverted[i];

            int threshold = 20;
            if(videoInverted[i] > 127+threshold || videoInverted[i] < 127 - threshold){
                     videoInverted[i] = 255;
                     videoInverted[i+1] = videoInverted[i];
                     videoInverted[i+2] = videoInverted[i];
                 }
                 else {
                      videoInverted[i] = 0;
                     videoInverted[i+1] = videoInverted[i];
                     videoInverted[i+2] = videoInverted[i];
                 }
            }

                videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
    }


}
//--------------------------------------------------------------
void testApp::draw() {

	ofBackground(127);
    ofSetColor(255);

    img.draw(640,0,320,240);
    img.draw(1366,0,1024,768);
	vidGrabber.draw(0,0, 320, 240);
	videoTexture.draw(0, 240, 320, 240);
	ofxQuadWarp(vidGrabber, ofPoint(0,0),ofPoint(320,0),ofPoint(320,240),ofPoint(0,240), 20, 20);

    meshImage.grabScreen(320,0,320,240); // To get the image from the output screen at position (320,0) size (320,240)
    originalImage.grabScreen(640,0,320,240);

    unsigned char * originalImagePixels = originalImage.getPixels();
    unsigned char * meshImagePixels = meshImage.getPixels();

    //Drawing a grayscale image by calculating the difference in rgb values for each pixel between the original image and the projected image
    int totalimgPixels = 320*240*3;
    for (int i = 0; i < totalimgPixels; i = i + 3) {
    diffImage[i] = 127 + (meshImagePixels[i] - originalImagePixels[i])/2; //Red
    diffImage[i+1] = 127 + (meshImagePixels[i+1] - originalImagePixels[i+1])/2; //Green
    diffImage[i+2] = 127 + (meshImagePixels[i+2] - originalImagePixels[i+2])/2; //Blue
    }


    img2.setFromPixels(diffImage,320,240,OF_IMAGE_COLOR);
    img2.draw(320*3,0,320,240);
     //diffTexture.loadData(diffImage, 320, 240, GL_RGB);

	 for(int i=0;i<4;i++){
        ofSetColor(0);
        ofFill();
        ofCircle(pointClicked[i],10);
    }


}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	// in fullscreen mode, on a pc at least, the
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...

	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}

    if(key == 'r') {
    ofPushMatrix();
    ofTranslate(10, 10, 0);
    ofRotate(20);
    //vidGrabber.setAnchorPercent(0.5, 0.5);
    vidGrabber.draw(20, 20, camWidth, camHeight);
    ofPopMatrix();
    }


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    if(which_point < 4){
        point_x[which_point] = x;
        point_y[which_point] = y;
    }

    for(int i = 0; i < 4; i++){
        pointClicked[i].set(point_x[i], point_y[i]);
    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    which_point += 1;
    if(which_point >= 4) which_point = 0;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

ofPoint testApp::ofxLerp(ofPoint start, ofPoint end, float amt) {
    return start + amt * (end - start);
}

int testApp::ofxIndex(float x, float y, float w) {
    return y*w+x;
}

//Warping and de-skewing
void testApp::ofxQuadWarp(ofBaseHasTexture &tex, ofPoint lt, ofPoint rt, ofPoint rb, ofPoint lb, int rows, int cols) {
    float tw = tex.getTextureReference().getWidth();
    float th = tex.getTextureReference().getHeight();

    tex.getTextureReference().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
    ofMesh mesh;

    for (int x=0; x<=cols; x++) {
        float f = float(x)/cols;

        ofPoint vTop(ofxLerp(lt,rt,f));
        ofPoint vBottom(ofxLerp(lb,rb,f));

        ofPoint pc0(pointClicked[0].x*camWidth/320,pointClicked[0].y*camHeight/240);
        ofPoint pc1(pointClicked[1].x*camWidth/320,pointClicked[1].y*camHeight/240);
        ofPoint pc2(pointClicked[2].x*camWidth/320,pointClicked[2].y*camHeight/240);
        ofPoint pc3(pointClicked[3].x*camWidth/320,pointClicked[3].y*camHeight/240);

        ofPoint tTop(ofxLerp(pc0,pc1,f));
            ofPoint tBottom(ofxLerp(pc3,pc2,f));


        for (int y=0; y<=rows; y++) {
            float f = float(y)/rows;
            ofPoint v = ofxLerp(vTop,vBottom,f);
            mesh.addVertex(v);
            mesh.addTexCoord(ofxLerp(tTop,tBottom,f));
        }
    }

    for (float y=0; y<rows; y++) {
        for (float x=0; x<cols; x++) {
            mesh.addTriangle(ofxIndex(x,y,cols+1), ofxIndex(x+1,y,cols+1), ofxIndex(x,y+1,cols+1));
            mesh.addTriangle(ofxIndex(x+1,y,cols+1), ofxIndex(x+1,y+1,cols+1), ofxIndex(x,y+1,cols+1));
        }
    }

    ofTranslate(320,0);
    tex.getTextureReference().bind();
    mesh.draw();
    tex.getTextureReference().unbind();
    //mesh.drawVertices();
    ofTranslate(-320,0);


}

