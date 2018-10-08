#include "RoiDetector.h"

namespace GAZE {
RoiDetector::RoiDetector (Scene& scene) {
    this->faceFinder.reset (new FaceFinder (scene.faceTemplatePath));
}
bool RoiDetector::Run (Scene& scene) {
    scene.faces = this->faceFinder->FindFaces (scene.curFrame);
    scene.eyes  = this->LocalizeEye (scene.faces);
    return true;
}


std::vector<Rect> RoiDetector::LocalizeEye (std::vector<Rect> faces) {
    std::vector<Rect> ans (faces.size () * 2);
    for (int i = 0; i < faces.size (); i++) {
        Rect face  = faces[i];
        int dist1  = (face.second.first - face.first.first) >> 3;
        int dist2  = (face.second.first - face.first.first) >> 2;
        ans[i * 2] = { { face.first.first + dist1, face.first.second + dist2 },
            { face.first.first + 2 * dist1 + dist2, face.first.second + 2 * dist2 } };
        ans[i * 2 + 1] = { { face.first.first + 2 * dist1 + dist2, face.first.second + dist2 },
            { face.first.first + 3 * dist1 + 2 * dist2, face.first.second + 2 * dist2 } };
    }
    return ans;
}
}
