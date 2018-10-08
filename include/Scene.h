#include "BasicTypes.h"
#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#pragma once
namespace GAZE {

class Scene {
    public:
    Scene (std::string path)
    : faceTemplatePath (path) {
    }
    std::string videoFilePath;
    std::string faceTemplatePath;

    cv::Mat curFrame;

    std::vector<Rect> faces;
    std::vector<Rect> eyes;

    std::vector<Point> detectedEyes;

    struct DrawerParams {
        bool drawFaces = false;
        bool drawEyes  = true;
        bool showImg   = true;
    } drawerParams;
};


typedef std::shared_ptr<Scene> ScenePtr;
}
