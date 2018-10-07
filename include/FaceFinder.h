#include "Scene.h"
#include "BasicTypes.h"
#include "CascadeClassifier.h"
namespace GAZE
{
	class FaceFinder
	{
	public:
		FaceFinder(std::string cascadePath);
		std::vector<Rect> FindFaces(cv::Mat frame);
    private:
		CascadeClassifierPtr faceCascade;
	};
	typedef std::shared_ptr<FaceFinder> FaceFinderPtr;
}
