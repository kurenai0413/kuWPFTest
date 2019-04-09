#include "kuOpenCVClassTest.h"

KUOPENCVCLASSTEST_API kuOpenCVClass::kuOpenCVClass()
{
	m_CameraFlag = false;
}

KUOPENCVCLASSTEST_API kuOpenCVClass::~kuOpenCVClass()
{

}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuSetParentHWND(HWND parentHWND)
{

}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuShowImage()
{
	cv::imshow(m_WindowName, m_TestImage);
	cv::waitKey(1);
}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuSetWindowName(std::string windowName)
{
	m_WindowName = windowName;
}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuCreateWindow(std::string windowName)
{
	cv::namedWindow(windowName, 1);
	kuSetWindowName(windowName);
}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	cv::namedWindow(windowName, 0);
	cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
	kuSetWindowName(windowName);
}

KUOPENCVCLASSTEST_API void kuOpenCVClass::kuCreateWindow(std::string windowName, double imgScale)
{
	cv::namedWindow(windowName, 0);
	if (!m_TestImage.empty())
		cv::resizeWindow(windowName, cv::Size(imgScale * m_TestImage.cols, imgScale * m_TestImage.rows));
	
	kuSetWindowName(windowName);
}

KUOPENCVCLASSTEST_API bool kuOpenCVClass::kuLoadImage(std::string filePath)
{
	m_TestImage = cv::imread(filePath, 1);
	//kuCreateWindow("Test Image");
}

KUOPENCVCLASSTEST_API bool kuOpenCVClass::kuStartCamera(int cameraIdx)
{
	if (!m_CamCapture.isOpened())
	{
		m_CamCapture.open(cameraIdx);

		if (m_CamCapture.isOpened())
		{
			// Start thread
			// m_CameraThd = std::thread(&kuOpenCVClass::kuCameraThdFun, this);
			m_CameraFlag = true;

			return m_CameraFlag;
		}
		else
		{
			return false;
		}
	}
}

KUOPENCVCLASSTEST_API bool kuOpenCVClass::kuGetCamframe()
{
	m_CamCapture >> m_TestImage;

	return true;
}

KUOPENCVCLASSTEST_API bool kuOpenCVClass::kuGetCameraStatus()
{
	if (m_CamCapture.isOpened())
		return true;
	else
		return false;
}

void kuOpenCVClass::kuCameraThdFun()
{
	/*while (m_CamCapture.isOpened())
	{
		m_CamCapture >> m_TestImage;
		kuShowImage();
	}*/
}
