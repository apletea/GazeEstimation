#include "RoiDetector.h"

namespace GAZE {
RoiDetector::RoiDetector (Scene& scene) {
    this->faceFinder.reset (new FaceFinder (scene.faceTemplatePath));
}
bool RoiDetector::Run (Scene& scene) {
    scene.faces = this->faceFinder->FindFaces (scene.curFrame);
    scene.eyes  = this->LocalizeEye (scene.faces, scene.curFrame);
    return true;
}


std::vector<Rect> RoiDetector::LocalizeEye (std::vector<Rect> faces,const cv::Mat & frame) {
    std::vector<Rect> ans (faces.size () * 2);
    for (int i = 0; i < faces.size (); i++) {

        Rect face  = faces[i];
        int dist1  = (face.width) >> 3;
        int dist2  = (face.width) >> 2;
        ans[i * 2] = Rect(face.x + dist1, face.y + dist2, dist1 + dist2,dist2);
        ans[i * 2 + 1] =  Rect(face.x + 2 * dist1 + dist2, face.y + dist2, dist1 + dist2, dist2);

    }
    return ans;
}
}
