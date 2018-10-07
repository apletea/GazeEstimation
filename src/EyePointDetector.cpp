#include "EyePointDetector.h"

namespace GAZE
{
	EyePointDetector::EyePointDetector(Scene & scene)
	{

	}

	bool EyePointDetector::Run(Scene & scene)
	{
        cv::Mat grayImg;
        if (scene.curFrame.channels() == 3)
		{
		    Simd::View<Simd::Allocator> simdGray(scene.curFrame.rows, scene.curFrame.cols, Simd::View<Simd::Allocator>::Gray8);
			Simd::View<Simd::Allocator> img = scene.curFrame;
		    Simd::BgrToGray(img,simdGray);
			grayImg = (cv::Mat)simdGray; 
	    }
		else
		{
			grayImg = scene.curFrame;
		}
		for (int i = 0; i < scene.eyes.size(); i++)
		{
		    cv::Mat eyeImg = grayImg(cv::Rect(scene.eyes[i].first.first,
									          scene.eyes[i].first.second,
											  scene.eyes[i].second.first  - scene.eyes[i].first.first,
											  scene.eyes[i].second.second - scene.eyes[i].first.second)
			);
			bool eyeFound = false;
			cv::Point eyePos = this->EyePointDetect(eyeImg, eyeFound);
            if (eyeFound)
			{
                 scene.detectedEyes.push_back({eyePos.x + scene.eyes[i].first.first,
											   eyePos.y + scene.eyes[i].first.second});
				 
			}
	   	}
        return true;
	}

	cv::Point EyePointDetector::EyePointDetect(cv::Mat imEye, bool & isLocateCorrect)
	{
        cv::Mat blurImg;
	    cv::GaussianBlur(imEye, blurImg, cv::Size(9,9), 0);
	    
	    float kernel[3] = {-0.5f, 0.0f, 0.5f};
	    cv::Mat filterX(1, 3, CV_32F, kernel);
	    cv::Mat filterY(3, 1, CV_32F, kernel);
        cv::Mat Lx,Ly;
        cv::filter2D(blurImg, Lx, CV_32F, filterX, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);
        cv::filter2D(blurImg, Ly, CV_32F, filterY, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);
       
        cv::Mat Lxx, Lxy, Lyx, Lyy;
        cv::filter2D(Lx, Lxx, CV_32F, filterX, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);
        cv::filter2D(Ly, Lyy, CV_32F, filterY, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);
        cv::filter2D(Lx, Lxy, CV_32F, filterY, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);
        cv::filter2D(Ly, Lyx, CV_32F, filterX, cv::Point (-1, -1), 0, cv::BORDER_REPLICATE);

        cv::Mat Lx2, Ly2, Lvv, Lw, Lw15;
        cv::pow(Ly, 2, Ly2);
        cv::pow(Lx, 2, Lx2);
       	Lvv = Ly2.mul(Lxx) - 2* Lx.mul(Lxy).mul(Ly) + Lx2.mul(Lyy);
		Lw  = Lx2 + Ly2;
		cv::pow(Lw, 1.5, Lw15);

		cv::Mat k, LwoverLvv, Dx, Dy;
		cv::divide(-Lvv, Lw15, k);
		cv::divide(Lw, Lvv, LwoverLvv);
		Dx = -Lx.mul(LwoverLvv);
		Dy = -Ly.mul(LwoverLvv);
        
		cv::Mat Dx2, Dy2, magnitude_diplacement;
		cv::pow(Dx, 2, Dx2);
		cv::pow(Dy, 2, Dy2);
		cv::sqrt(Dx2 + Dy2, magnitude_diplacement);

		cv::Mat Lxx2, Lxy2, Lyy2, curvednestemp, curvedness;
	    cv::pow(Lxx, 2, Lxx2);
	    cv::pow(Lxy, 2, Lxy2);
	    cv::pow(Lyy, 2, Lyy2);
	    cv::sqrt(Lxx2 + 2 * Lxy2 + Lyy2, curvednestemp);
	    curvedness = cv::abs(curvednestemp);
	   
	    const int height = blurImg.rows;
	    const int width  = blurImg.cols;
	    cv::Mat centerMap(height, width, CV_32F, 0.0f);
	    for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (Dx.at<float>(i,j) == 0.0f && Dy.at<float>(i,j) == 0.0f)
				{
					continue;
				}
				int dstx = i + (int)Dx.at<float>(i,j);
				int dsty = j + (int)Dy.at<float>(i,j);
				int radius = (int)magnitude_diplacement.at<float>(i,j);
				if (dstx > 0 && dsty > 0 && dstx < width && dsty << height)
				{
					if (k.at<float>(i,j) < 0)
					{
						if (radius >= MINRAD && radius <= MAXRAD)
						{
							if (imEye.at<float>(i,j) < DARKPIXELVALUE)
							{
								centerMap.at<float>(dsty, dstx) += curvedness.at<float>(i,j);
							}
						}
					}
				}
			}
		}
	    
	    cv::Mat gausBluredCenterMap(height, width, CV_32F, 0.0f);
	    cv::GaussianBlur(centerMap, gausBluredCenterMap, cv::Size(5,5),0);
	    
	    double maxv = 0, minv = 0;
	    cv::Point minLocation, maxLocation;
	    cv::minMaxLoc(gausBluredCenterMap, &minv, &maxv, &minLocation, & maxLocation);
	    if (maxv > RESULTTHRESHOLD)
		{
			isLocateCorrect = true;
		}	
		else
		{
			isLocateCorrect = false;
		}
        return maxLocation;

	}
}
