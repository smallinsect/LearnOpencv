
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

void demo3() {
	Mat src, dst;
	src = imread("gujian3.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return ;
	}
	namedWindow("src windows", CV_WINDOW_AUTOSIZE);
	imshow("src windows", src);

	//int cols = (src.cols - 1) * src.channels();//列 宽度
	//int offsetx = src.channels();
	//int rows = src.rows;//行 高度
	//dst = Mat::zeros(src.size(), src.type());
	//for (int row = 1; row < (rows - 1); ++row) {
	//	const uchar *previous = src.ptr<uchar>(row - 1);
	//	const uchar *current = src.ptr<uchar>(row);
	//	const uchar *next = src.ptr<uchar>(row + 1);
	//	uchar *output = dst.ptr<uchar>(row);
	//	for (int col = offsetx; col < cols; ++col) {
	//		output[col] = saturate_cast<uchar>(5*current[col]-(current[col-offsetx]+current[col+offsetx]+next[col]));
	//	}
	//}
	double t = getTickCount();
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, dst, src.depth(), kernel);
	double timeconsume = (getTickCount() - t) / getTickFrequency();
	printf("tim_comsume %.2lf\n", timeconsume);

	namedWindow("constrast image demo", CV_WINDOW_AUTOSIZE);
	imshow("constrast image demo", dst);
}

void demo4() {
	Mat src = imread("gujian3.jpg");
	if (!src.data) {
		cout << "could not load image..." << endl;
		return ;
	}

	Mat dst;

	//cvtColor(src, dst, CV_BGR2GRAY);//获取灰度值
	src.copyTo(dst);

	int width = src.cols;
	int height = src.rows;
	int channels = src.channels();
	//for (int row = 0; row < height; ++row) {
	//	uchar *current = dst.ptr<uchar>(row);
	//	for (int col = 0; col < width; ++col) {
	//		current[col] = 255 - current[col];
	//	}
	//}
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			if (channels == 1) {
				int gray = dst.at<uchar>(row, col);
				dst.at<uchar>(row, col) = 255 - gray;
			} else {
				Vec3b &v = dst.at<Vec3b>(row, col);
				int b = v[0];
				int g = v[1];
				int r = v[2];
				v[0] = 255 - b;
				v[1] = 255 - g;
				v[2] = 255 - r;
			}
		}
	}

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);

}