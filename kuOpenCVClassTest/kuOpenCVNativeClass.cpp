#include "kuOpenCVNativeClass.h"

KUOPENCVCLASSTEST_API kuOpenCVNativeClass::kuOpenCVNativeClass()
{
	m_CameraFlag = false;

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
	cv::imshow(m_WindowName, m_TestImage);
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
	m_WindowName = windowName;
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName)
{
	cv::namedWindow(windowName, 1);
	kuSetWindowName(windowName);
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	cv::namedWindow(windowName, 0);
	cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
	kuSetWindowName(windowName);
}

KUOPENCVCLASSTEST_API void kuOpenCVNativeClass::kuCreateWindow(std::string windowName, double imgScale)
{
	cv::namedWindow(windowName, 0);
	if (!m_TestImage.empty())
		cv::resizeWindow(windowName, cv::Size(imgScale * m_TestImage.cols, imgScale * m_TestImage.rows));
	
	kuSetWindowName(windowName);
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

void kuOpenCVNativeClass::kuCameraThdFun()
{
	/*while (m_CamCapture.isOpened())
	{
		m_CamCapture >> m_TestImage;
		kuShowImage();
	}*/
}
