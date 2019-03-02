#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {

	Mat mat = imread("gujian3.jpg");
	if (!mat.data) {
		cout << "could not load imge..." << endl;
		return -1;
	}

	namedWindow("input", CV_WINDOW_AUTOSIZE);

	imshow("input", mat);

	waitKey(0);

	return 0;
}