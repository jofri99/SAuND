#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture cap;
	if (!cap.open(0)) {
		return 0;
	}
	int i = 0;
	
	for (;;) {
		Mat frame, grey, lowRes;
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		//make a grey frame
		cvtColor(frame,grey, COLOR_BGR2GRAY);
		//Resize image with factor 0.05
		resize(grey, lowRes, Size(),0.05,0.05);

		
		imshow("Webcam", frame);
		imshow("Greycam", grey);
		imshow("lowRes", lowRes);
		if (i > 1) {
			system("cls");
			//output of greyscales
			cout << lowRes << endl;
			i = 0;
		}
		i++;

		if (waitKey(10) == 27) { //Esc(27) stop capturing
			break;
		}
	}
	cout << "Hellon" << endl;
	return 0;
}
