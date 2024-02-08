#include <opencv2/opencv.hpp>
#include <iostream>


int main() {

	cv::Mat grey, img;
	img = cv::imread("res/images/unps.jpg", cv::IMREAD_COLOR);
	std::string window = "anime face detection";

	cv::CascadeClassifier facedet;
	facedet.load("res/classifiers/lbpcascade_animeface.xml");
	cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(grey, grey); 


	std::vector<cv::Rect> faces;
	facedet.detectMultiScale(grey, faces, 1.1, 5, cv::CASCADE_SCALE_IMAGE);


	for (int i = 0; i < faces.size(); i++) {
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);
		cv::putText(img, std::to_string(faces.size()), cv::Point(10, 40),
			cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(50, 50, 255), 2.3);
	}

	/*for (const auto& face : faces) {
		cv::rectangle(img, face, cv::Scalar(0, 0, 255), 2);
	}*/


	cv::Size windowSize(800, 600);
	cv::resize(img, img, windowSize);

	cv::namedWindow(window);
	cv::imshow(window, img);

	cv::waitKey(0); // Check if the 'esc' key was pressed (ASCII code 27)

	//To close the window when left click on 'x' at the upper right corner of the window 
	cv::getWindowProperty(window, cv::WND_PROP_VISIBLE) < 1;

	return 0; 
}