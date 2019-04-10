#pragma once
#ifdef KUOPENCVCLASSTEST_EXPORTS
#define KUOPENCVCLASSTEST_API __declspec(dllexport)
#else
#define KUOPENCVCLASSTEST_API __declspec(dllimport)
#endif

#include <windows.h>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;

class kuOpenCVNativeClass
{
public:

	KUOPENCVCLASSTEST_API kuOpenCVNativeClass();
	KUOPENCVCLASSTEST_API ~kuOpenCVNativeClass();

	KUOPENCVCLASSTEST_API void kuSetParentHWND(HWND parentHWND);
	KUOPENCVCLASSTEST_API void kuSetWindowName(std::string windowName);
	KUOPENCVCLASSTEST_API void kuCreateWindow(std::string windowName);
	KUOPENCVCLASSTEST_API void kuCreateWindow(std::string windowName, int wndWidth, int wndHeight);
	KUOPENCVCLASSTEST_API void kuCreateWindow(std::string windowName, double imgScale);
	
	KUOPENCVCLASSTEST_API bool kuLoadImage(std::string filePath);
	KUOPENCVCLASSTEST_API void kuSetImageDefault();
	KUOPENCVCLASSTEST_API void kuShowImage();
	//KUOPENCVCLASSTEST_API void kuShowDefault();

	KUOPENCVCLASSTEST_API bool kuStartCamera(int cameraIdx);
	KUOPENCVCLASSTEST_API bool kuGetCamframe();
	KUOPENCVCLASSTEST_API bool kuGetCameraStatus();


private:
	int				m_DefaultWidth;
	int				m_DefaultHeight;

	Mat				m_TestImage;
	std::string		m_WindowName;

	VideoCapture	m_CamCapture;

	bool			m_CameraFlag;

	void			kuCameraThdFun();
};