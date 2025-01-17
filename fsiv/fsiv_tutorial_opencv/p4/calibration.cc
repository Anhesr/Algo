#include <iostream>
#include <exception>
#include <vector>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,vector<vector<Point2f> > imagePoints );
void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
                  Settings::Pattern patternType /*= Settings::CHESSBOARD*/);

int main(int argc, char const *argv[])
{
	Settings s;
	const string inputSettingsFile = argc > 1 ? argv[1] : "default.xml";
	FileStorage fs(inputSettingsFile, FileStorage::READ); // Read the settings
	if (!fs.isOpened())
	{
	  cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
	  return -1;
	}
	fs["Settings"] >> s;
	fs.release();                                         // close Settings file

	if (!s.goodInput)
	{
	  cout << "Invalid input detected. Application stopping. " << endl;
	  return -1;
	}
	for(int i = 0;;++i)
	{
	  Mat view;
	  bool blinkOutput = false;

	  view = s.nextImage();

	  //-----  If no more image, or got enough, then stop calibration and show result -------------
	  if( mode == CAPTURING && imagePoints.size() >= (unsigned)s.nrFrames )
	  {
	        if( runCalibrationAndSave(s, imageSize,  cameraMatrix, distCoeffs, imagePoints))
	              mode = CALIBRATED;
	        else
	              mode = DETECTION;
	  }
	  if(view.empty())          // If no more images then run calibration, save and stop loop.
	  {
	            if( imagePoints.size() > 0 )
	                  runCalibrationAndSave(s, imageSize,  cameraMatrix, distCoeffs, imagePoints);
	            break;
	  imageSize = view.size();  // Format input image.
	  if( s.flipVertical )    flip( view, view, 0 );
	  }
	  vector<Point2f> pointBuf;

	  bool found;
	  switch( s.calibrationPattern ) // Find feature points on the input format
	  {
	  case Settings::CHESSBOARD:
	    found = findChessboardCorners( view, s.boardSize, pointBuf,
	    CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
	    break;
	  case Settings::CIRCLES_GRID:
	    found = findCirclesGrid( view, s.boardSize, pointBuf );
	    break;
	  case Settings::ASYMMETRIC_CIRCLES_GRID:
	    found = findCirclesGrid( view, s.boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID );
	    break;
	  }
	  if ( found)                // If done with success,
  		{	
      // improve the found corners' coordinate accuracy for chessboard
        if( s.calibrationPattern == Settings::CHESSBOARD)
        {
            Mat viewGray;
            cvtColor(view, viewGray, CV_BGR2GRAY);
            cornerSubPix( viewGray, pointBuf, Size(11,11),
              Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
        }

        if( mode == CAPTURING &&  // For camera only take new samples after delay time
            (!s.inputCapture.isOpened() || clock() - prevTimestamp > s.delay*1e-3*CLOCKS_PER_SEC) )
        {
            imagePoints.push_back(pointBuf);
            prevTimestamp = clock();
            blinkOutput = s.inputCapture.isOpened();
        }

        // Draw the corners.
        //----------------------------- Output Text ------------------------------------------------
		string msg = (mode == CAPTURING) ? "100/100" :
		          mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);

		if( mode == CAPTURING )
		{
		  if(s.showUndistorsed)
		    msg = format( "%d/%d Undist", (int)imagePoints.size(), s.nrFrames );
		  else
		    msg = format( "%d/%d", (int)imagePoints.size(), s.nrFrames );
		}

		putText( view, msg, textOrigin, 1, 1, mode == CALIBRATED ?  GREEN : RED);

		if( blinkOutput )
		   bitwise_not(view, view);

				//------------------------- Video capture  output  undistorted ------------------------------
		if( mode == CALIBRATED && s.showUndistorsed )
		{
		  Mat temp = view.clone();
		  undistort(temp, view, cameraMatrix, distCoeffs);
		}
		//------------------------------ Show image and check for input commands -------------------
		imshow("Image View", view);
		char key =  waitKey(s.inputCapture.isOpened() ? 50 : s.delay);
		if( key  == ESC_KEY )
		      break;

		if( key == 'u' && mode == CALIBRATED )
		   s.showUndistorsed = !s.showUndistorsed;

		if( s.inputCapture.isOpened() && key == 'g' )
		{
		  mode = CAPTURING;
		  imagePoints.clear();
		}
		if( s.inputType == Settings::IMAGE_LIST && s.showUndistorsed )
		{
		  Mat view, rview, map1, map2;
		  initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		      getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		      imageSize, CV_16SC2, map1, map2);

		  for(int i = 0; i < (int)s.imageList.size(); i++ )
		  {
		      view = imread(s.imageList[i], 1);
		      if(view.empty())
		          continue;
		      remap(view, rview, map1, map2, INTER_LINEAR);
		      imshow("Image View", rview);
		      char c = waitKey();
		      if( c  == ESC_KEY || c == 'q' || c == 'Q' )
		          break;
		  }
		}


   


}

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,vector<vector<Point2f> > imagePoints )
{
 vector<Mat> rvecs, tvecs;
 vector<float> reprojErrs;
 double totalAvgErr = 0;

 bool ok = runCalibration(s,imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
                          reprojErrs, totalAvgErr);
 cout << (ok ? "Calibration succeeded" : "Calibration failed")
     << ". avg re projection error = "  << totalAvgErr ;

 if( ok )   // save only if the calibration was done with success
     saveCameraParams( s, imageSize, cameraMatrix, distCoeffs, rvecs ,tvecs, reprojErrs,
                         imagePoints, totalAvgErr);
 return ok;
}

void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
                  Settings::Pattern patternType /*= Settings::CHESSBOARD*/)
{
corners.clear();

switch(patternType)
{
case Settings::CHESSBOARD:
case Settings::CIRCLES_GRID:
  for( int i = 0; i < boardSize.height; ++i )
    for( int j = 0; j < boardSize.width; ++j )
        corners.push_back(Point3f(float( j*squareSize ), float( i*squareSize ), 0));
  break;

case Settings::ASYMMETRIC_CIRCLES_GRID:
  for( int i = 0; i < boardSize.height; i++ )
     for( int j = 0; j < boardSize.width; j++ )
        corners.push_back(Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
  break;
}
}