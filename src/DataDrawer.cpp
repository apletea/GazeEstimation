#include "DataDrawer.h"

namespace GAZE {
DataDrawer::DataDrawer (Scene& scene) {
}

void DataDrawer::Run (Scene& scene) {
    cv::Mat frame (scene.curFrame);
    if (true) {
        for (int i = 0; i < scene.faces.size (); i++) {
            cv::rectangle (
            frame, cv::Rect (scene.faces[i].first.first, scene.faces[i].first.second,
                   scene.faces[i].second.first - scene.faces[i].first.first,
                   scene.faces[i].second.second - scene.faces[i].first.second),
            cv::Scalar (255, 0, 0));
        }
    }
    if (true) {
        for (int i = 0; i < scene.eyes.size (); i++) {
            cv::circle (frame,
            cv::Point (scene.detectedEyes[i].first, scene.detectedEyes[i].second),
            4, cv::Scalar (0, 255, 0), -1);
        }
    }
    if (true) {
        cv::imshow ("frame", frame);
        cv::waitKey (40);
    }
}
}
