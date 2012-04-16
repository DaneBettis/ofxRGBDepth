//
//  ofxRGBDMediaTake.cpp
//  ScreenLabRenderer
//
//  Created by James George on 4/16/12.
//

#include "ofxRGBDMediaTake.h"

ofxRGBDMediaTake::ofxRGBDMediaTake(){
	hasCalibrationDirectory = false;
    hasDepthFolder = false;
    hasLargeVideoFile = false;
    hasSmallVideoFile = false;
}

bool ofxRGBDMediaTake::loadFromFolder(string sourceMediaFolder){
	
	mediaFolder = sourceMediaFolder;
    
	hasCalibrationDirectory = false;
    hasDepthFolder = false;
    hasLargeVideoFile = false;
    hasSmallVideoFile = false;
    
    calibrationDirectory = "";
    lowResVideoPath = "";
    hiResVideoPath = "";
    depthFolder = "";
    pairingsFile = "";
	
    ofDirectory dataDirectory(mediaFolder);
    if(!dataDirectory.exists()){
        ofSystemAlertDialog("Error loading media folder " + mediaFolder + " -- Directory not found.");
        return false;
    }
    
	dataDirectory.listDir();    
	int numFiles = dataDirectory.numFiles();
    if(numFiles == 0){
        ofSystemAlertDialog("Error loading media folder " + mediaFolder + " -- Directory is empty.");
        return false;        
    }
    
	for(int i = 0; i < numFiles; i++){
		string testFile = dataDirectory.getName(i);
		if(testFile.find("calibration") != string::npos){
			calibrationDirectory = dataDirectory.getPath(i);
            hasCalibrationDirectory = true;
		}
		
		if(testFile.find("depth") != string::npos || testFile.find("TAKE") != string::npos){
			depthFolder = dataDirectory.getPath(i);
            hasDepthFolder = true;
		}
		
		if(testFile.find("mov") != string::npos || testFile.find("MOV") != string::npos ){
			if(testFile.find("small") == string::npos){
				hiResVideoPath = dataDirectory.getPath(i);
                hasLargeVideoFile = true;
			}
			else {
				lowResVideoPath = dataDirectory.getPath(i);
                hasSmallVideoFile = true;
			}
		}		
		
		if(testFile.find("pairings") != string::npos){
			pairingsFile = dataDirectory.getPath(i);
		}
	}
	
	if(!hasSmallVideoFile){
		ofSystemAlertDialog("Error loading media folder " + mediaFolder + " no Small Video File found.");
		return false;
	}
    
	if(!hasCalibrationDirectory){
		ofSystemAlertDialog("Error loading media folder " + mediaFolder + ". No calibration/ directory found.");
		return false;	
	}
    
	if(!hasDepthFolder){
		ofSystemAlertDialog("Error loading media folder " + mediaFolder + ". No Depth directory found. Make sure the folder containing the depth images has 'depth' or 'take' in the name");
		return false;	
	}
	
	if(pairingsFile == ""){
		pairingsFile = ofFilePath::removeExt(lowResVideoPath) + "_pairings.xml";
	}
  
	return true;
}

bool ofxRGBDMediaTake::valid(){
    return  hasCalibrationDirectory && hasDepthFolder && hasSmallVideoFile;

}

