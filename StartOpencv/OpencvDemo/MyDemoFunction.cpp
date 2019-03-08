
#include "MyDemoFunction.h"

const char *src_ng = "1.jpg";
const char *src_gj = "2.jpg";

const char *input1 = "input1 window";
const char *input2 = "input2 window";

const char *output = "output window";

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
	double t = (double)getTickCount();
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

//两张图片相加
void demo5() {
	Mat src1, src2, dst;
	src1 = imread("1.jpg");
	src2 = imread("2.jpg");
	if (!src1.data) {
		cout << "could not load image1..." << endl;
		return;
	}
	if (!src2.data) {
		cout << "cout not load image2..." << endl;
		return;
	}

	double alpha = 0.5;
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type()) {
		addWeighted(src1, alpha, src2, 1-alpha, 0, dst);
		namedWindow("input1", CV_WINDOW_AUTOSIZE);
		namedWindow("input2", CV_WINDOW_AUTOSIZE);
		namedWindow("output", CV_WINDOW_AUTOSIZE);
		imshow("input1", src1);
		imshow("input2", src2);
		imshow("output", dst);
	} else {
		cout << "two is difriend" << endl;
	}
}

//调整图像亮度和对比度
void demo6() {
	Mat src, dst;
	src = imread(src_ng);
	if (!src.data) {
		cout << "could not load image..." << endl;
		return;
	}
	cvtColor(src, src, CV_BGR2GRAY);
	dst = Mat::zeros(src.size(), src.type());

	int height = src.rows;
	int width = src.cols;
	double alpha = 0.8;
	double beta = 10;
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			if (src.channels() == 3) {
				Vec3b v = src.at<Vec3b>(row, col);
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(v[0]*alpha + beta);//blue
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(v[1]*alpha + beta);//green
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(v[2]*alpha + beta);//red
			} else if(src.channels() == 1){
				dst.at<uchar>(row, col) = saturate_cast<uchar>(src.at<uchar>(row, col)*alpha + beta);
			}
		}
	}
	namedWindow(input1, CV_WINDOW_AUTOSIZE);
	imshow(input1, src);

	namedWindow(output, CV_WINDOW_AUTOSIZE);
	imshow(output, dst);

}

void demo7() {
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 300;
	p2.y = 300;
	Scalar color = Scalar(0, 0, 255);

	Mat bgImage = imread(src_gj);
	if (!bgImage.data) {
		cout << "could not load image ..." << endl;
		return;
	}

	namedWindow(input1, CV_WINDOW_AUTOSIZE);
	line(bgImage, p1, p2, color, 1, LINE_8);//绘制直线

	Rect rect = Rect(10, 20, 30, 40);
	color = Scalar(255, 0, 0);
	rectangle(bgImage, rect, color, 2, LINE_8);//绘制矩形

	color = Scalar(0, 255, 0);
	ellipse(bgImage, Point(bgImage.cols/2, bgImage.rows/2), Size(bgImage.cols/4,bgImage.rows/8),90, 0, 360, color, 2, LINE_8);//绘制椭圆

	color = Scalar(0, 255, 255);
	Point center = Point(bgImage.cols/2, bgImage.rows/2);
	circle(bgImage, center, 100, color, 2, LINE_8);//绘制圆

	//绘制多边形
	Point ap[1][6];
	ap[0][0] = Point(20, 20);
	ap[0][1] = Point(40, 20);
	ap[0][2] = Point(50, 30);
	ap[0][3] = Point(40, 40);
	ap[0][4] = Point(20, 40);
	ap[0][5] = Point(20, 20);

	const Point *ppts[] = { ap[0] };
	int np = 6;
	color = Scalar(255, 255, 0);
	//fillPoly(bgImage, ppts, np, 1, color, LINE_8);


	//绘制文字
	putText(bgImage, "HEI HEI HEI", Point(50,50), CV_FONT_HERSHEY_COMPLEX, 1.0, color, 1, LINE_8);

	//绘制随机线
	RNG rng(123456);//高斯随机数
	Point pt1;
	Point pt2;
	for (int i = 0; i < 10000;  ++i) {
		pt1.x = rng.uniform(0, bgImage.cols);
		pt2.x = rng.uniform(0, bgImage.cols);
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);

		color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (waitKey(50) > 0) {
			break;
		}
		line(bgImage, pt1, pt2, color, 1, LINE_8);
		imshow(input1, bgImage);
	}

}