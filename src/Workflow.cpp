#include "Workflow.h"
#define LOG_RUN_TIME   printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
namespace GAZE
{

	bool Workflow::ReInitScene()
	{
        LOG_RUN_TIME
        LOG_RUN_TIME
//        scenePtr->faceTemplatePath.resize((*res)["input_temp"].as<std::string>().size());
//        scenePtr->faceTemplatePath = (*res)["input_temp"].as<std::string>();
        scenePtr.reset(new Scene(parmsPtr->faceTemplatePath));
        this->vc >> scenePtr->curFrame;
        LOG_RUN_TIME

		scenePtr->drawerParams.drawFaces = parmsPtr->drawerParams.drawFaces;
		LOG_RUN_TIME

		scenePtr->drawerParams.drawEyes  = parmsPtr->drawerParams.drawEyes;
		LOG_RUN_TIME

		scenePtr->drawerParams.showImg   = parmsPtr->drawerParams.showImg;

	}

    bool Workflow::SetUpOpt(int argc, char ** argv)
	{
		cxxopts::Options options("libGaze","lib for gaze detection using simd intrsutions");
		options
                .positional_help("[optional args]")
                .show_positional_help();
		options
		.allow_unrecognised_options()
		.add_options()
				("input_temp","input harcascade template",cxxopts::value<std::string>()->default_value("../../data/template/haarcascade_frontalface_default.xml"))
				("input_vid","input video path", cxxopts::value<std::string>()->default_value("../../data/vids/VID_20181007_154019.mp4"))
				("drawFaces","is drawer should draw faces",cxxopts::value<bool>()->default_value("true"))
				("drawEyes","is drawer shoud draw eyes",cxxopts::value<bool>()->default_value("true"))
				("showImg","is drawer should show img",cxxopts::value<bool>()->default_value("true"));
		//auto res = options.parse(argc, argv);
        this->res = new cxxopts::ParseResult(options.parse(argc, argv));
		this->vc.open((*res)["input_vid"].as<std::string>());
        LOG_RUN_TIME
        parmsPtr.reset(new Scene((*res)["input_temp"].as<std::string>()));
        parmsPtr->drawerParams.drawFaces = (*res)["drawFaces"].as<bool>();
        parmsPtr->drawerParams.drawEyes  = (*res)["drawEyes"].as<bool>();
        parmsPtr->drawerParams.showImg   = (*res)["showImg"].as<bool>();
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
        LOG_RUN_TIME
	    while (this->ReInitScene())
		{
            LOG_RUN_TIME
			roiDetectorPtr->Run(*scenePtr);
            LOG_RUN_TIME
            eyePointDetectorPtr->Run(*scenePtr);
            LOG_RUN_TIME
            dataWriterPtr->Run(*scenePtr);
            LOG_RUN_TIME
			dataWriterPtr->Run(*scenePtr);
		}	
    }
}
