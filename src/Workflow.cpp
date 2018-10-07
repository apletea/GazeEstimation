#include "Workflow.h"

namespace GAZE
{

	bool Workflow::ReInitScene()
	{
		scenePtr.reset(new Scene());
        this->vc >> scenePtr->curFrame;

		scenePtr->faceTemplatePath = (*res)["input_temp"].as<std::string>();

		scenePtr->drawerParams.drawFaces = (*res)["drawerParams.drawFaces"].as<bool>();
		scenePtr->drawerParams.drawEyes  = (*res)["drawerParams.drawEyes"].as<bool>();
		scenePtr->drawerParams.showImg   = (*res)["drawerParams.showImg"].as<bool>();

	}

    bool Workflow::SetUpOpt(int argc, char ** argv)
	{
		cxxopts::Options options("libGaze","lib for gaze detection using simd intrsutions");
		options
		.allow_unrecognised_options()
		.add_options()
				("it,input_temp","input harcascade template",cxxopts::value<std::string>()->default_value("data/template/haarcascade_frontalface_default.xml"))
				("iv,input_vid","input video path", cxxopts::value<std::string>()->default_value("data/vids/VID_20181007_154019.mp4"))
				("drawerParams.drawFaces","is drawer should draw faces",cxxopts::value<bool>()->default_value("true"))
				("drawerParams.drawEyes","is drawer shoud draw eyes",cxxopts::value<bool>()->default_value("true"))
				("drawerParams.showImg","is drawer should show img",cxxopts::value<bool>()->default_value("true"));
		

		auto res = options.parse(argc, argv);
        this->res = &res;
		this->vc = cv::VideoCapture(res["input_vid"].as<std::string>());
		ReInitScene();

	}

	
	
    bool Workflow::Init(int argc, char **argv)
    {
        SetUpOpt(argc, argv);
        roiDetectorPtr.reset(new RoiDetector(*scenePtr));
        eyePointDetectorPtr.reset(new EyePointDetector(*scenePtr));
        dataDrawerPtr.reset(new DataDrawer(*scenePtr));
        dataWriterPtr.reset(new DataWriter(*scenePtr));
    }

    bool Workflow::Run()
    {
	    while (this->ReInitScene())
		{
			roiDetectorPtr->Run(*scenePtr);
			eyePointDetectorPtr->Run(*scenePtr);
			dataWriterPtr->Run(*scenePtr);
			dataWriterPtr->Run(*scenePtr);
		}	
    }
}
