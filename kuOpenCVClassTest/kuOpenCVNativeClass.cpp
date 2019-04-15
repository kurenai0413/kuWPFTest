#include "kuOpenCVNativeClass.h"

KUOPENCVCLASSTEST_API kuOpenCVNativeClass::kuOpenCVNativeClass()
{
	m_CameraFlag	   = false;
	m_WindowCreateFlag = false;

	m_DefaultWidth  = 640;
	m_DefaultHeight = 480;

	std::cout << "Native constructor called." << std::endl;
}

KUOPENCVCLASSTEST_API kuOpenCVNativeClass::~kuOpenCVNativeClass()
{
	
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuSetParentHWND(HWND parentHWND)
{

}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuShowImage()
{
	cv::imshow(m_CurrnetWindowName, m_TestImage);
	cv::waitKey(1);
}

//KUOPENCVCLASSTEST_API void kuOpenCVClass::kuShowDefault()
//{
//	m_TestImage = cv::Mat::zeros(m_DefaultHeight, m_DefaultWidth, CV_8UC1);
//	cv::imshow(m_WindowName, m_TestImage);
//	cv::waitKey(0);
//}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuSetWindowName(std::string windowName)
{
	m_CurrnetWindowName = windowName;
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		kuSetWindowName(windowName);

		m_CurrnetWindowName = windowName;

		m_WindowCreateFlag = true;
	}
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 0);
		cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
		kuSetWindowName(windowName);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName, double imgScale)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 0);
		if (!m_TestImage.empty())
			cv::resizeWindow(windowName, cv::Size(imgScale * m_TestImage.cols, imgScale * m_TestImage.rows));

		kuSetWindowName(windowName);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName, int handle)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 0);
		kuSetWindowName(windowName);

		HWND hWndCV = (HWND)cvGetWindowHandle(m_CurrnetWindowName.c_str());
		HWND hWndCVParent = ::GetParent(hWndCV);
		::SetParent(hWndCV, (HWND)handle);
		::ShowWindow(hWndCVParent, SW_HIDE);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuDestroyCurrentWindow()
{
	if (m_WindowCreateFlag)
	{
		cv::destroyWindow(m_CurrnetWindowName);
	}
}

KUOPENCVCLASSTEST_API bool kuOpenCVNativeClass::kuLoadImage(std::string filePath)
{
	m_TestImage = cv::imread(filePath, 1);

	if (!m_TestImage.empty())
		return true;
	else
		return false;
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuSetImageDefault()
{
	m_TestImage = cv::Mat::zeros(m_DefaultHeight, m_DefaultWidth, CV_8UC1);
}

KUOPENCVCLASSTEST_API bool kuOpenCVNativeClass::kuStartCamera(int cameraIdx)
{
	m_CameraIdx = cameraIdx;

	if (!m_CamCapture.isOpened())
	{
		m_CamCapture.open(cameraIdx);

		if (m_CamCapture.isOpened())
		{
			m_CameraFlag = true;

			return m_CameraFlag;
		}
		else
		{
			return false;
		}
	}
}

KUOPENCVCLASSTEST_API bool kuOpenCVNativeClass::kuGetCamframe()
{
	m_CamCapture >> m_TestImage;

	return true;
}

KUOPENCVCLASSTEST_API bool kuOpenCVNativeClass::kuGetCameraStatus()
{
	if (m_CamCapture.isOpened())
		return true;
	else
		return false;
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCloseCamera(int cameraIdx)
{
	m_CamCapture.release();
}
