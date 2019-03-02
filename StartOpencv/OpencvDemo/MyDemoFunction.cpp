
#include "MyDemoFunction.h"


void demo1() {
	Mat src = imread("gujian3.jpg");
	if (!src.data) {
		cout << "could not load image..." << endl;
		return ;
	}

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;

	//dst = Mat(src.size(), src.type());
	//dst = Scalar(0, 0, 127);

	//dst = src.clone();

	//src.copyTo(dst);

	//cvtColor(src, dst, CV_BGR2GRAY);

	//dst.create(src.size(), src.type());
	//dst = Scalar(222, 111, 0);

	Mat kernel = (Mat_<char>(3, 3) << 0,-1,0,-1,5,-1,0,-1,0);
	filter2D(src, dst, -1,kernel);

	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);
}


void demo2() {
	Mat src = imread("gujian3.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return ;
	}
	namedWindow("test opencv setup", CV_WINDOW_AUTOSIZE);
	imshow("test opencv setup", src);

	namedWindow("output windows", CV_WINDOW_AUTOSIZE);
	Mat output_image;
	cvtColor(src, output_image, CV_BGR2HSV);
	imshow("output windows", output_image);

	imwrite("gujian3hls.jpg", output_image);
}