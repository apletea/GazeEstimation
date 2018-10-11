#include "DataDrawer.h"

namespace GAZE {
DataDrawer::DataDrawer (Scene& scene) {
}

void DataDrawer::Run (Scene& scene) {
    cv::Mat frame (scene.curFrame);
    if (true) {
        for (int i = 0; i < scene.faces.size (); i++) {
            cv::rectangle (
            frame, scene.faces[i],
            cv::Scalar (255, 0, 0));
        }
    }
    if (true) {
        for (int i = 0; i < scene.detectedEyes.size(); i++) {
            cv::circle (frame,
            cv::Point (scene.detectedEyes[i]),
            4, cv::Scalar (0, 255, 0), -1);
            std::cout << "i =" << i << "  x = " << scene.detectedEyes[i].x << " y =" << scene.detectedEyes[i].y << std::endl;
        }
    }
    if (true) {
        cv::imshow ("frame", frame);
        cv::waitKey ();
    }
}
}
