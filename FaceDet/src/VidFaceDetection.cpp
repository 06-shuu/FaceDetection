#include <opencv2/opencv.hpp>
#include <iostream>

// Global variables
int framePosition = 0;

// Function prototypes
void onTrackbarSlide(int position, void*);

int main() {
    cv::VideoCapture cap;
    cap.open("res/videos/em.mp4");

    cv::CascadeClassifier facedet;
    facedet.load("res/classifiers/haarcascade_frontalface_default.xml"); // Pre-trained face detector
    cv::Mat frame;

    if (!cap.isOpened() || facedet.empty()) {
        std::cerr << "Error: Unable to open video or load cascade classifier." << std::endl;
        return -1;
    }

    int totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);

    std::string window = "Video Face Detection";
    cv::namedWindow(window);

    cv::createTrackbar("Frame Position", window, &framePosition, totalFrames - 1, onTrackbarSlide);

    while (true) {
        cap.set(cv::CAP_PROP_POS_FRAMES, framePosition);
        cap >> frame;

        if (frame.empty())
            break;

        std::vector<cv::Rect> faces;
        facedet.detectMultiScale(frame, faces, 1.3, 5);

        for (int i = 0; i < faces.size(); i++) {
            cv::rectangle(frame, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);
            cv::putText(frame, std::to_string(faces.size()), cv::Point(10, 40),
                cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(50, 50, 255), 2.3);
        }

        cv::imshow(window, frame);

        int key = cv::waitKey(10);
        if (key == 27) // Check if the 'esc' key was pressed (ASCII code 27)
            break;
        // To close the window when left-clicking on 'x' at the upper right corner of the window
        if (cv::getWindowProperty(window, cv::WND_PROP_VISIBLE) < 1)
            break;
    }

    cv::destroyAllWindows();
    return 0;
}

void onTrackbarSlide(int position, void*) {
    framePosition = position;
}
