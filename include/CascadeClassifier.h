#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#define SIMD_OPENCV_ENABLE
#include <Simd/SimdDetection.hpp>
#include <Simd/SimdDrawing.hpp>
#pragma once


namespace GAZE
{
	typedef Simd::Detection<Simd::Allocator> Detection;
	class CascadeClassifier
	{

	public:
        CascadeClassifier(std::string cascadePath);
		Detection::Objects  Detect(cv::Mat frame);
	private:
        bool inited;
		Detection detection;
	};
	typedef std::shared_ptr<CascadeClassifier> CascadeClassifierPtr;
}
