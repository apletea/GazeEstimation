#include "Scene.h"
#include "BasicTypes.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#pragma once

namespace GAZE
{
    class DataDrawer
	{
	public:
        DataDrawer(Scene & scene);
        void Run(Scene & scene);

	};
	typedef std::shared_ptr<DataDrawer> DataDrawerPtr;
}
