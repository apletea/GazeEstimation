#include "EyePointDetector.h"
#define LOG_RUN_TIME \
    printf ("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
namespace GAZE {
EyePointDetector::EyePointDetector (Scene& scene) {
}

bool EyePointDetector::Run (Scene& scene) {
    cv::Mat grayImg;
    if (scene.curFrame.channels () == 3) {
#ifdef SIMD_CONV
        Simd::View<Simd::Allocator> simdGray (scene.curFrame.rows,
        scene.curFrame.cols, Simd::View<Simd::Allocator>::Gray8);
        Simd::View<Simd::Allocator> img = scene.curFrame;
        Simd::BgrToGray (img, simdGray);
        grayImg = (cv::Mat)simdGray;
#else
        cv::cvtColor(scene.curFrame, grayImg, cv::COLOR_RGB2HSV);
#endif
    } else {
        grayImg = scene.curFrame;
    }
    for (int i = 0; i < scene.eyes.size(); i++) {
        if (scene.eyes[i].x + scene.eyes[i].width > grayImg.cols || scene.eyes[i].y + scene.eyes[i].height > grayImg.rows)
            continue;
        cv::Mat eyeImg = grayImg (scene.eyes[i]);
        bool eyeFound    = false;
        cv::Point eyePos = this->EyePointDetect (eyeImg, eyeFound);
        if (eyeFound) {
            scene.detectedEyes.push_back (eyePos + scene.eyes[i].tl());
        }
        cv::circle(eyeImg,eyePos,5,cv::Scalar(255,0,0));
//        cv::imshow("eye",eyeImg);
//        cv::waitKey();

    }
    return true;
}
//fix blur
cv::Point EyePointDetector::EyePointDetect (cv::Mat & imeye, bool& is_locate_correct) {
    cv::Mat blurim;
    cv::GaussianBlur(imeye, blurim, cv::Size(9,9), 0);
    float kernel[3] = {-0.5f, 0.0f, 0.5f};
    cv::Mat filterX(1, 3, CV_32F, kernel);
    cv::Mat filterY(3, 1, CV_32F, kernel);
    cv::Mat Lx, Ly;
    cv::filter2D(blurim, Lx, CV_32F, filterX, Point (-1, -1), 0, cv::BORDER_REPLICATE);
    cv::filter2D(blurim, Ly, CV_32F, filterY, Point (-1, -1), 0, cv::BORDER_REPLICATE);
    cv::Mat Lxx, Lxy, Lyy, Lyx;
    cv::filter2D(Lx, Lxx, CV_32F, filterX, Point (-1, -1), 0, cv::BORDER_REPLICATE);
    cv::filter2D(Lx, Lxy, CV_32F, filterY, Point (-1, -1), 0, cv::BORDER_REPLICATE);
    cv::filter2D(Ly, Lyx, CV_32F, filterX, Point (-1, -1), 0, cv::BORDER_REPLICATE);
    cv::filter2D(Ly, Lyy, CV_32F, filterY, Point (-1, -1), 0, cv::BORDER_REPLICATE);

    cv::Mat Lx2, Ly2;
    cv::pow(Ly, 2, Ly2);
    cv::pow(Lx, 2, Lx2);
    cv::Mat Lvv = Ly2.mul(Lxx) - 2 * Lx.mul(Lxy).mul(Ly) + Lx2.mul(Lyy);
    cv::Mat Lw = Lx2 + Ly2;
    cv::Mat Lw15;
    cv::pow(Lw, 1.5, Lw15);
    cv::Mat k;
    cv::divide(-Lvv, Lw15, k);
    cv::Mat LwoverLvv;
    cv::divide(Lw, Lvv, LwoverLvv);
    cv::Mat Dx, Dy;
    Dx = -Lx.mul(LwoverLvv);
    Dy = -Ly.mul(LwoverLvv);
    cv::Mat Dx2, Dy2, magnitude_displacement;
    cv::pow(Dx, 2, Dx2);
    cv::pow(Dy, 2, Dy2);
    cv::sqrt(Dx2+Dy2, magnitude_displacement);
    cv::Mat Lxx2, Lxy2, Lyy2, curvednesstemp, curvedness;
    cv::pow(Lxx, 2, Lxx2);
    cv::pow(Lxy, 2, Lxy2);
    cv::pow(Lyy, 2, Lyy2);
    cv::sqrt(Lxx2 + 2 * Lxy2 + Lyy2 , curvednesstemp);
    curvedness = cv::abs(curvednesstemp);
    const int srcheight = blurim.rows;
    const int srcwidth = blurim.cols;
    cv::Mat center_map(srcheight, srcwidth, CV_32F, 0.0f);
    for(int y = 0; y < srcheight; y++)
    {
        for(int x = 0; x < srcwidth; x++)
        {
            if(Dx.at<float>(y, x) == 0.0f && Dy.at<float>(y, x) == 0.0f)
            {
                continue;
            }
            int dstx = x + (int)Dx.at<float>(y, x);
            int dsty = y + (int)Dy.at<float>(y, x);
            int radius = (int)magnitude_displacement.at<float>(y, x);
            if(dstx > 0 && dsty > 0 && dstx < srcwidth && dsty < srcheight)
            {
                //consider gradients from white to black only
                if(k.at<float>(y, x) < 0)
                {
                    if(radius >= MINRAD && radius <= MAXRAD)
                    {
                        if(imeye.at<float>(y, x) < DARKPIXELVALUE)
                        {
                            center_map.at<float>(dsty, dstx) += curvedness.at<float>(y, x);
                        }
                    }
                }
            }
        }
    }
    cv::Mat gauss_blured_center_map(srcheight, srcwidth, CV_32F, 0.0f);
    cv::GaussianBlur(center_map, gauss_blured_center_map, cv::Size(5,5), 0);
    double maxv = 0, minv = 0;
    cv::Point minlocation, maxlocation;
    cv::minMaxLoc(gauss_blured_center_map, &minv, &maxv, &minlocation, &maxlocation);
    if(maxv > RESULTTHRESHOLD)
    {
        is_locate_correct = true;
    }
    else
    {
        is_locate_correct = false;
    }
   // is_locate_correct = true;
    return maxlocation;
}
}
