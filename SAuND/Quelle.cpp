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

double getSquare(int x, int y, int rows, int cols) 
{
	int counter = 0;
	double avg = 0;

	for (int i =x; i < x + rows; i++) {
		for (int j= y; j < y + cols; j++) {
			avg += (int) LOWRES.at<uchar>(i, j);
			counter++;
		}
	}

	avg = avg / counter;

	if (avg > 128) {
		avg *= 1.2;
		if (avg > 255) {
			avg = 255;
		}
	}
	else {
		avg *= 0.7;
	}

	return avg;
}

void runVideo(float pixelScale, String windowName, bool showCam) 
{
	VideoCapture cap = getWebcam(0);
	int i = 0;
	double * avgVals;
	double rows = 3;
	double cols = 4;
	avgVals = (double*) malloc (rows * cols * sizeof(int));

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

		double avg = getSquare(0, 0, 8, 8);
		system("cls");
		for (int i = 0; i < 24; i += 8) {
			cout << endl;
			for (int j = 0; j < 32; j += 8) {
				avg = getSquare(i, j, 8, 8);
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


