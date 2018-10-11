#include "BasicTypes.h"
#include "Scene.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#define SIMD_OPENCV_ENABLE
#include "Simd/SimdLib.hpp"

// eyeball radius range
#define MINRAD 10
#define MAXRAD 25
// dark pixel value threshold
#define DARKPIXELVALUE 10
// voting result threshold
#define RESULTTHRESHOLD 3.0
#pragma once

namespace GAZE {
class EyePointDetector {
    public:
    EyePointDetector (Scene& scene);
    bool Run (Scene& scene);

    private:
    cv::Point EyePointDetect (cv::Mat & imEye, bool& isLocateCorrect);
};
typedef std::shared_ptr<EyePointDetector> EyePointDetectorPtr;
}
