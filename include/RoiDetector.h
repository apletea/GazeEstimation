#include "BasicTypes.h"
#include "FaceFinder.h"
#pragma once

namespace GAZE {
class RoiDetector {
    public:
    RoiDetector (Scene& scene);
    bool Run (Scene& scene);

    private:
    std::vector<Rect> LocalizeEye (std::vector<Rect> faces, const cv::Mat & frame);

    FaceFinderPtr faceFinder;
};
typedef std::shared_ptr<RoiDetector> RoiDetectorPtr;
}
