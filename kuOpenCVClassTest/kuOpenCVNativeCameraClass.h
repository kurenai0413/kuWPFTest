#pragma once
#ifdef KUOPENCVNATIVECAMERACLASS_EXPORTS
#define KUOPENCVNATIVECAMERACLASS_API __declspec(dllexport)
#else
#define KUOPENCVNATIVECAMERACLASS_API __declspec(dllimport)
#endif

#include <windows.h>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;

class kuOpenCVNativeCameraClass
{
public:

	KUOPENCVNATIVECAMERACLASS_API kuOpenCVNativeCameraClass();
	KUOPENCVNATIVECAMERACLASS_API ~kuOpenCVNativeCameraClass();

	KUOPENCVNATIVECAMERACLASS_API void kuSetParentHWND(HWND parentHWND);
	KUOPENCVNATIVECAMERACLASS_API void kuSetWindowName(std::string windowName);

	KUOPENCVNATIVECAMERACLASS_API void kuCreateWindow(std::string windowName);
	KUOPENCVNATIVECAMERACLASS_API void kuCreateWindow(std::string windowName, int wndWidth, int wndHeight);
	KUOPENCVNATIVECAMERACLASS_API void kuCreateWindow(std::string windowName, double imgScale);
	KUOPENCVNATIVECAMERACLASS_API void kuCreateWindow(std::string windowName, int handle);
	KUOPENCVNATIVECAMERACLASS_API void kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight);
	KUOPENCVNATIVECAMERACLASS_API void kuDestroyCurrentWindow();
	
	KUOPENCVNATIVECAMERACLASS_API bool kuLoadImage(std::string filePath);
	KUOPENCVNATIVECAMERACLASS_API void kuSaveImage(std::string filePath);
	KUOPENCVNATIVECAMERACLASS_API void kuSetImageDefault();
	KUOPENCVNATIVECAMERACLASS_API void kuShowImage();

	KUOPENCVNATIVECAMERACLASS_API bool kuStartCamera(int cameraIdx);
	KUOPENCVNATIVECAMERACLASS_API void kuCloseCamera();

	KUOPENCVNATIVECAMERACLASS_API bool kuGetCamframe();
	KUOPENCVNATIVECAMERACLASS_API bool kuGetCameraStatus();
	

private:
	int				m_DefaultWidth;
	int				m_DefaultHeight;

	Mat				m_TestImage;
	std::string		m_CurrnetWindowName;

	VideoCapture	m_CamCapture;

	int				m_CameraIdx;

	bool			m_isCameraOpened;
	bool			m_WindowCreateFlag;

	void			kuCameraThdFun();
};