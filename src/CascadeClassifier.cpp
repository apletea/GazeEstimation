#include "CascadeClassifier.h"

namespace GAZE {
typedef Simd::Detection<Simd::Allocator> Detection;
CascadeClassifier::CascadeClassifier (std::string cascadePath) {
    if (!this->detection.Load (cascadePath)) {
        std::cout << "Error on loading cascadePath" << std::endl;
    }
     this->inited = false;
}

Detection::Objects CascadeClassifier::Detect (cv::Mat frame) {

    Detection::View image = frame;
    if (!this->inited) {
        detection.Init (image.Size (), 1.2, image.Size ()/20 );
        this->inited = true;
    }

    Detection::Objects objects;
    detection.Detect (image, objects);

    return objects;
}
}
