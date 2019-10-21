#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

VideoCapture getWebcam(int webcam) {
	VideoCapture cap;
	if (!cap.open(webcam)) {
		cout << "Webcam not found" << endl;
		_Exit(0);
		return NULL;
	}

	return cap;
}

void runVideo(float pixelScale,int step,String windowName,bool logConsole,bool showCam) {
	VideoCapture cap = getWebcam(0);
	int i = 0;

	for (;;) {
		Mat frame, grey, lowRes;
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		//make a grey frame
		cvtColor(frame, grey, COLOR_BGR2GRAY);
		
		//Resize image with given factor "pixelScale"
		resize(grey, lowRes, Size(), pixelScale, pixelScale);

		if (showCam) {
			namedWindow(windowName, 0);
			resizeWindow(windowName, 640, 480);
			imshow(windowName, lowRes);
		}

		if(logConsole){
			if (i > step) {
				system("cls");
				//output of greyscales
				cout << lowRes << endl;
				cout << lowRes.size << endl;
				i = 0;
			}
			i++;
		}

		if (waitKey(10) == 27) { //Esc(27) stop capturing
			break;
		}
	}


}
int main()
{
	runVideo(0.1,5,"Webcam",true,false);
	return 0;
}


