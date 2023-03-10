#include "Library.h"
#include "cardRead.h"

int main() {


//to do : add function to choose wether to login or change main credential

	//defines class object and image var.
		cardRead card1;
		cv::Mat image;

	//opens a window and defines capture type.
	cv::namedWindow("Display Window");
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {std::cout << "Error 0: Failed to open camera.";} //error check for camera open.

	//image capture loop.
	while (card1.getVar(2) == card1.getVar(1)) { //message checker on card read.

		cap >> image;

		//draw functions.
		card1.drawTangle(image);
		card1.drawLine(image);

		//display frame.
		imshow("Display Window", image);

		//reading captured frame for change.
		card1.checkBorder(image,160,480,400,120);
		card1.checkMsg(image);
		cv::waitKey(25);
		
	}
	
	//Displays new window when loop is broken while reading data from taken image
	card1.checkBrightness(image); //brightness check of image taken
	card1.compareData(image, "image.bmp");

	return 0;
}
