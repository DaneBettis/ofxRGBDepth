/*
 *  ofxRGBDRenderer.h
 *  ofxRGBDepthCaptureOpenNI
 *
 *  Created by Jim on 12/17/11.
 *  
 *  The ofxRGBDRenderer is capable of actually rendering a depth image aligned to a
 *  an RGB image from an external camera.
 *
 *  It requres a calibration file generated by a ofxRGBDAlignment from a series of checkerboard calibration pairs,
 *  a depth image and an rgb image from cameras from the same perspective
 *  
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class ofxRGBDRenderer {
  public:
	ofxRGBDRenderer();
	~ofxRGBDRenderer();
	
	void setup(string calibrationDirectory);
	
	void setRGBTexture(ofBaseHasTexture& rgbTexture); 
	void setDepthImage(unsigned short* depthPixelsRaw);
	void update();

	//fudge factors to apply during alignment
	float xshift;
	float yshift;
	float xscale;
	float yscale;

	void drawMesh();
	void drawPointCloud();
		
	//populated with vertices, texture coords, and indeces
	ofVboMesh & getMesh();

	ofVec3f getMeshCenter();
	float getMeshDistance();
	
	bool applyShader;
	ofShader rgbdShader;

  protected:
	
	bool hasDepthImage;
	bool hasColorImage;
	bool hasPointCloud;
	
	ofBaseHasTexture* currentColorImage;
	unsigned short* currentDepthImage;
	
	vector<Point2f> imagePoints;    
	ofVboMesh mesh;
    vector<ofIndexType> indeces;
    vector<ofVec2f> texcoords;
    vector<ofVec3f> vertices;
	
	ofVec3f meshCenter;
	float meshDistance;
	
};