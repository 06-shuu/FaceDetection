//face detection by a video 
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap;
    cap.open("res/videos/sr1.mp4"); 
    
    cv::CascadeClassifier facedet;
    facedet.load("res/classifiers/haarcascade_frontalface_default.xml"); //pre-trained face detector
    cv::Mat frame;

    if (!cap.isOpened() || facedet.empty()) {
        std::cerr << "Error: Unable to open video or load cascade classifier." << std::endl;
        return -1;
    }

    std::string window = "Frame";
    cv::namedWindow(window);

    while (true) {
        cap >> frame;

        if (frame.empty())
            break;

        std::vector<cv::Rect> faces;
        facedet.detectMultiScale(frame, faces, 1.3, 5);

        for (int i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i].tl(), faces[i].br(), cv::Scalar(50, 50, 255), 3);
            cv::putText(frame, std::to_string(faces.size()), cv::Point(10, 40),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 1);
        }

        cv::imshow(window, frame);

        int key = cv::waitKey(10);
        if (key == 27) // Check if the 'esc' key was pressed (ASCII code 27)
            break;
        //To close the window when left click on 'x' at the upper right corner of the window 
        if (cv::getWindowProperty(window, cv::WND_PROP_VISIBLE) < 1)
            break;
    }

    cv::destroyAllWindows();
    return 0;
}
