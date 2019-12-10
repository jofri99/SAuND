#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

Mat LOWRES;

VideoCapture getWebcam(int webcam) {
	VideoCapture cap;
	if (!cap.open(webcam)) {
		cout << "Webcam not found" << endl;
		_Exit(0);
		return NULL;
	}

	return cap;
}

double normieren(double val, double min, double max) {
	if (val > max) {
		val = max;
	}
	else if (val < min) {
		val = min;
	}
	return (255.0f * ((val - min) / (max - min)));
}

double getSquareNorm(int x, int y, int rows, int cols,double hVal, double lVal) 
{
	int counter = 0;
	double avg = 0;
	double diff = hVal - lVal;

	for (int i =x; i < x + rows; i++) {
		for (int j= y; j < y + cols; j++) {
			avg += (int) LOWRES.at<uchar>(i, j);
			counter++;
		}
	}

	avg = avg / counter;
	

	

	return normieren(avg,30,190);
}

double getSquare(int x, int y, int rows, int cols, double hVal, double lVal)
{
	int counter = 0;
	double avg = 0;
	double diff = hVal - lVal;

	for (int i = x; i < x + rows; i++) {
		for (int j = y; j < y + cols; j++) {
			avg += (int)LOWRES.at<uchar>(i, j);
			counter++;
		}
	}

	avg = avg / counter;




	return avg;
}

void analalyze(VideoCapture c,float pS,double  * hVal, double * lVal) {
	Mat frame, grey;
	c >> frame;

	if (frame.empty()) {
		return;
	}

	//make a grey frame
	cvtColor(frame, grey, COLOR_BGR2GRAY);

	//Resize image with given factor "pixelScale"
	resize(grey, LOWRES, Size(), pS, pS);


	*hVal = -1;
	*lVal = 256;

	double avg;
	for (int i = 0; i < 24; i += 8) {
		for (int j = 0; j < 32; j += 8) {
			avg = getSquare(i, j, 8, 8, 60, 150);
			if (avg > *hVal) {
				*hVal = avg;
			}

			if (avg < *lVal) {
				*lVal = avg;
			}
		}
	}
	
	cout << *hVal << endl;
	cout << *lVal << endl;
}

void runVideo(float pixelScale, String windowName, bool showCam) 
{
	VideoCapture cap = getWebcam(0);
	int i = 0;
	double * avgVals;
	double rows = 3;
	double cols = 4;
	avgVals = (double*) malloc (rows * cols * sizeof(int));

	
	double hVal,lVal; 
	analalyze(cap, pixelScale, &hVal,&lVal);

	cout << hVal << endl;
	cout << lVal << endl;


	for (;;) {
		Mat frame, grey;
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		//make a grey frame
		cvtColor(frame, grey, COLOR_BGR2GRAY);
		
		//Resize image with given factor "pixelScale"
		resize(grey, LOWRES, Size(), pixelScale, pixelScale);

		if (showCam) {
			namedWindow(windowName, 0);
			resizeWindow(windowName, 640, 480);
			imshow(windowName, LOWRES);
		}

		double avg = getSquareNorm(0, 0, 8, 8,lVal,hVal);
		system("cls");
		for (int i = 0; i < 24; i += 8) {
			cout << endl;
			for (int j = 0; j < 32; j += 8) {
				avg = getSquareNorm(i, j, 8, 8,lVal,hVal);
				cout << avg << "\t";
			}
		}

		if (waitKey(10) == 27) { //Esc(27) stop capturing
			break;
		}
	}
	
}
int main()
{
	runVideo(0.05,"Webcam",true);
	return 0;
}


