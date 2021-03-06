#include "DataDrawer.h"
#include "DataWriter.h"
#include "EyePointDetector.h"
#include "RoiDetector.h"
#include "Scene.h"
#include "cxxopts.hpp"
#include <bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

#pragma once

namespace GAZE {
class Workflow {
    public:
    bool Init (int argc, char** argv);
    bool Run ();

    private:
    bool SetUpOpt (int argc, char** argv);
    bool ReInitScene ();

    cv::VideoCapture vc;
    cxxopts::ParseResult* res;

    std::shared_ptr<cxxopts::Options> optsPtr;
    ScenePtr scenePtr;
    ScenePtr parmsPtr;
    RoiDetectorPtr roiDetectorPtr;
    EyePointDetectorPtr eyePointDetectorPtr;
    DataDrawerPtr dataDrawerPtr;
    DataWriterPtr dataWriterPtr;
};

typedef std::shared_ptr<Workflow> WorkflowPtr;
}
