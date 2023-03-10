#include "Library.h"
#include <string>

class cardRead {
public:
	//----------------------------------------- GETTER AND SETTER FUNCTIONS ---------------------------------------------------

	bool getVar(int varNum) {
		switch (varNum) {
		case 1:
			return msg;
			break;
		case 2:
			return show;
			break;
		default:
			std::cout << "invalid var number" << "\n";
			break;
		}
	}

	void setVar(bool check) {
		msg = check;
	}

	int getCount() {
		return count;
	}

	void setCount(int num) {
		count = count + num;
	}

    //-----------------------------------------------------------------------------------------------------------------------



	//---------------------------------------------- CHECK FUNCTIONS --------------------------------------------------------

	int checkBorder(cv::Mat img, int x, int x2, int y1, int mode) { //Dual function checks for white border / Takes RGB values on given row by h. 
		int sum = 0;
		for (x; x < x2; ++x) {
			long int rgb[6] = { 0,0,0,0,0,0 };
			for (int n = 0; n < 3; ++n) { 
				rgb[n] = img.at<cv::Vec3b>( x, y1)[n];
				
				if (mode != 0) { 
					rgb[n + 3] = img.at<cv::Vec3b>(x, mode)[n];
				}
			};
			for (int i = 0; i < 6; ++i) { sum = sum + rgb[i]; }
		};
		std::cout << sum << "\n"; //testing line

		if (mode != 0) {
			if (sum  > 160000) { std::cout << "Eurika" << "\n" << "\n" << "\n";  bool check = true; setVar(check); };
		};//checks sum value, closes window on white detection.

		return sum;
	};

	int checkBrightness(cv::Mat brightImg) { //Stripped and modified stack overflow code. Checks brightness of an image.
		const auto result = cv::mean(brightImg);

		std::cout << "Brightness: " << result[2] << "\n";
		return result[2];
	}
	int checkContrast(cv::Mat brightImg) { //Stripped and modified stack overflow code. Checks contrast of an image.
		const auto result = cv::mean(brightImg);

		std::cout << result[1];
		return result[1];
	}
	int checkGamma(cv::Mat brightImg) { //Stripped and modified stack overflow code. Checks gamma of an image.
		const auto result = cv::mean(brightImg);

		std::cout << result[3];
		return result[3];
	}

	void checkMsg(cv::Mat img) { //checks message status.
		switch (msg) {
		case true:
			std::cout << "message passed";
			cv::destroyWindow("Display Window");
			imwrite("image.bmp", img);
			break;
		default:
			std::cout << "message not passed";
			break;
		};
	};

    //-----------------------------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------- DRAW FUNCTIONS ---------------------------------------------------------------
	void drawTangle(cv::Mat img) {
		cv::Point p1(160, 120); cv::Point p2(480, 400);
		int thickness = 2;
		rectangle(img, p1, p2, cv::Scalar(255, 255, 255), thickness, cv::LINE_8);
	}
	void drawLine(cv::Mat img) {
		cv::Point start(160, 400); cv::Point end(480, 400);
		cv::Scalar lineRgb(211, 0, 211);
		int thick = 2;

		cv::Point start1(160, 120); cv::Point end1(480, 120);
		cv::Scalar lineRgb1(211, 0, 211);
		int thick1 = 2;

		line(img, start, end, lineRgb, thick);
		line(img, start1, end1, lineRgb1, thick1);
	}

	//------------------------------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------- COMPARE FUNCTIONS -------------------------------------------------------------
	int readData(cv::Mat image, std::string imageName, int mode, int gridWant) {
		int grid[5] = { 0,0,0,0,0 }; //value of total rgb in grid.
		cv::imread(imageName);
		int coords[10] = { 0,0,0,0,0,0,0,0,0,0 };
		int heightMin = 0;
		int h = 0;
		switch (mode) {
		case 1:
			//coords[10] = { 160,224, 224,288, 288,352, 352,416, 416,480 };
			coords[0] = 160;
			coords[1] = 224;
			coords[2] = 224;
			coords[3] = 288;
			coords[4] = 288;
			coords[5] = 352;
			coords[6] = 352;
			coords[7] = 416;
			coords[8] = 416;
			coords[9] = 440;
			heightMin = 160;
			break;
			//coords of all grids
		case 0:
			coords[0] = 0;
			coords[1] = 64;
			coords[2] = 64;
			coords[3] = 128;
			coords[4] = 128;
			coords[5] = 192;
			coords[6] = 192;
			coords[7] = 256;
			coords[8] = 256;
			coords[9] = 280;
			heightMin = 0;
			break;
			//coords of card grids
		};

		for (int gridNum = 0; gridNum < 5; ++gridNum) { //looping through all grids
			int gridSum = 0; //sum of a grid
			int x[2] = { 0,0 }; //chooses grid coord variable
			switch (mode) {
			case 0:
				h = 280;
				break;
			default:
				h = 400;
				break;
			}
			switch (gridNum) {
			case 0:
				x[0] = coords[0];
				x[1] = coords[1];
				break;
			case 1:
				x[0] = coords[2];
				x[1] = coords[3];
				break;
			case 2:
				x[0] = coords[4];
				x[1] = coords[5];
				break;
			case 3:
				x[0] = coords[6];
				x[1] = coords[7];
				break;
			case 4:
				x[0] = coords[8];
				x[1] = coords[9];
				break;
			};
			while (h > heightMin) { //runs through height top down
				gridSum = gridSum + checkBorder(image, x[0], x[1], h, 0); //uses checkborder function to pull rgb values
				--h;

			};
			//std::cout << "\n" << "\n" << "\n" << gridSum; //prints sum of each grid for testing
			grid[gridNum] = gridSum; //saves grid sum to corresponding grid number
		};

		return grid[gridWant];
		
	};

	void compareData(cv::Mat image, std::string filename) { /*||||HERE||||*/
		int gridOne[5] = {0,0,0,0,0};
		int gridTwo[5] = { 0,0,0,0,0 };
		cv::Mat Test = cv::imread("Test.bmp");
		for (int i = 0; i < 5; ++i) {
		     gridOne[i] = readData(image, filename, 0, i); //To DO: Replace Test and Test.bmp with proper prefix (As detailed in function arguments). This has been left to test the functionality of compareData.
		}
		for (int i = 0; i < 5; ++i) {
			gridTwo[i] = readData(getCard(), "Card.bmp", 0, i);
		}
		
		double totalBrightness = (((checkBrightness(getCard()) - (double)checkBrightness(image)) / 100) + 1 );

		std::cout << "\n Brightness Modifier: " << totalBrightness << "\n";

		/*for (int i = 0; i < 5; ++i) { //testing loop (archived)
			std::cout <<" " << gridOne[i];
			}
		for (int i = 0; i < 5; ++i) {
			std::cout << " " << gridTwo[i];
		}
		*/

		for (int i = 0; i < 5; ++i) {
			int modGrid = gridOne[i] * (totalBrightness);
			std::cout << "\noriginal grid = " << gridOne[i] << "\n";
			if (modGrid > gridTwo[i] - 1000000 && modGrid < gridTwo[i] + 1000000) {
				setCount(1);
			}
			std::cout << totalBrightness << "\n";
			std::cout << " Grid set: " << i << " Modded Grid: " <<  modGrid << " Card Grid : " << gridTwo[i] << "\n"; //testing line
			std::cout << " Passwords Matched:" << getCount() << "\n"; //testing line
		}

		
		
	
		//for (int i = 0; i < 5; ++i) { std::cout << gridOne[i]; }; //testing line

	}

	//------------------------------------------------------------------------------------------------------------------------------------

protected:

	//--------------------------------------- PROTECTED SECTION ---------------------------------------------------------------------------
	//Paints Main Window
	void paintWindow() {
		cv::Mat loadImage = cv::imread("Card.bmp");
		cv::namedWindow("Please Be Patient", cv::WINDOW_AUTOSIZE);
		while (true) {
			cv::imshow("Please Be Patient", loadImage);

			cv::waitKey(25);
		};
	}

	cv::Mat getCard() {

		cv::Mat cardImage = cv::imread("Card.bmp");
		return cardImage;
	}

	//-------------------------------------------------------------------------------------------------------------------------------------
private:

	//------------------------------------ PRIVATE VARIABLES FOR CLASS --------------------------------------------------------------------
	//message send and check variables for loop.
	bool msg = false; //1
	bool show = false; //2
	//count for correct comparison
	int count = 0;
	//storage for grid variables
	long int gridValue[5];
	long int gridValueTwo[5];

	//-------------------------------------------------------------------------------------------------------------------------------------
};
