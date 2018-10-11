#include "FaceFinder.h"

namespace GAZE {
FaceFinder::FaceFinder (std::string cascadePath) {
    faceCascade.reset (new CascadeClassifier (cascadePath));
}

std::vector<Rect> FaceFinder::FindFaces (cv::Mat frame) {
    Detection::Objects obj = faceCascade->Detect (frame);
	std::cout  << "Object size = " << obj.size() << std::endl;
    std::vector<Rect> ans (obj.size ());
    for (int i = 0; i < obj.size (); i++) {
        cv::Rect cvRect      = obj[i].rect;
//        ans[i].first.first   = cvRect.y;
//        ans[i].first.second  = cvRect.x;
//        ans[i].second.first  = cvRect.y + cvRect.height;
//        ans[i].second.second = cvRect.x + cvRect.width;
        ans[i] = cvRect;
    }
    return ans;
}
}
