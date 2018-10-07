#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#include "Scene.h"
#include "RoiDetector.h"
#include "EyePointDetector.h"
#include "DataDrawer.h"
#include "DataWriter.h"
#include "cxxopts.hpp"

namespace GAZE
{
    class Workflow
    {
	public:
        bool Init(int argc,char **  argv);
        bool Run();
	private:
        bool SetUpOpt(int argc, char ** argv);
		bool ReInitScene();

    	cv::VideoCapture vc;
		cxxopts::ParseResult *res;

		ScenePtr scenePtr;
		RoiDetectorPtr roiDetectorPtr;
		EyePointDetectorPtr eyePointDetectorPtr;
		DataDrawerPtr dataDrawerPtr;
		DataWriterPtr dataWriterPtr;
	    std::shared_ptr<cxxopts::Options> optsPtr;	
    };

	typedef std::shared_ptr<Workflow> WorkflowPtr;
}
