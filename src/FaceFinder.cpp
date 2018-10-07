#include "FaceFinder.h"

namespace GAZE
{
	FaceFinder::FaceFinder(std::string cascadePath)
	{
        faceCascade.reset(new CascadeClassifier(cascadePath));
	}

	std::vector<Rect> FaceFinder::FindFaces(cv::Mat frame)
	{
		Detection::Objects obj = faceCascade->Detect(frame);
		std::vector<Rect> ans(obj.size());
		for (int i = 0; i < obj.size(); i++)
		{
			cv::Rect cvRect = obj[i].rect;
			ans[i].first.first = cvRect.x;
			ans[i].first.second = cvRect.y;
			ans[i].second.first = cvRect.x + cvRect.width;
			ans[i].second.second = cvRect.y + cvRect.height;
		}
		return ans;
	}
		
}
