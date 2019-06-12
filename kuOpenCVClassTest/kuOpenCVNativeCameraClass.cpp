#include "kuOpenCVNativeCameraClass.h"

KUOPENCVNATIVECAMERACLASS_API kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClass()
{
	m_isCameraOpened   = false;
	m_WindowCreateFlag = false;

	m_DefaultWidth	   = 1280;
	m_DefaultHeight	   = 720;

	std::cout << "Native constructor called." << std::endl;
}

KUOPENCVNATIVECAMERACLASS_API kuOpenCVNativeCameraClass::~kuOpenCVNativeCameraClass()
{
	if (m_isCameraOpened)
	{
		kuCloseCamera();
	}
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuSetParentHWND(HWND parentHWND)
{

}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuShowImage()
{
	cv::imshow(m_CurrnetWindowName, m_TestImage);
	cv::waitKey(33);
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuShowProcessedImage()
{
	cv::imshow(m_CurrnetWindowName, m_OriginalCameraFrame);
	cv::waitKey(33);
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuSetWindowName(std::string windowName)
{
	m_CurrnetWindowName = windowName;
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		kuSetWindowName(windowName);

		m_CurrnetWindowName = windowName;

		m_WindowCreateFlag = true;
	}
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
		kuSetWindowName(windowName);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, double imgScale)
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

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int handle)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		kuSetWindowName(windowName);

		HWND hWndCV		  = (HWND)cvGetWindowHandle(m_CurrnetWindowName.c_str());
		HWND hWndCVParent = ::GetParent(hWndCV);
		::SetParent(hWndCV, (HWND)handle);
		::ShowWindow(hWndCVParent, SW_HIDE);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 0);
		cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
		kuSetWindowName(windowName);

		HWND hWndCV = (HWND)cvGetWindowHandle(m_CurrnetWindowName.c_str());
		HWND hWndCVParent = ::GetParent(hWndCV);
		::SetParent(hWndCV, (HWND)handle);
		::ShowWindow(hWndCVParent, SW_HIDE);

		m_WindowCreateFlag = true;
	}
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuDestroyCurrentWindow()
{
	if (m_WindowCreateFlag)
	{
		cv::destroyWindow(m_CurrnetWindowName);
	}
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuLoadImage(std::string filePath)
{
	m_TestImage = cv::imread(filePath, 1);

	if (!m_TestImage.empty())
		return true;
	else
		return false;
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuSaveImage(std::string filePath)
{
	cv::imwrite(filePath, m_TestImage);
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuSetImageDefault()
{
	m_TestImage = cv::Mat::zeros(m_DefaultHeight, m_DefaultWidth, CV_8UC1);
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuStartCamera(int cameraIdx)
{
	m_CameraIdx = cameraIdx;
	if (!m_CamCapture.isOpened())
	{		
		m_CamCapture.open(cameraIdx);

		if (m_CamCapture.isOpened())
		{
			bool setFourCCFlag = m_CamCapture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
			bool setWidthFlag  = m_CamCapture.set(cv::CAP_PROP_FRAME_WIDTH, m_DefaultWidth);
			bool setHeightFlag = m_CamCapture.set(cv::CAP_PROP_FRAME_HEIGHT, m_DefaultHeight);

			if (m_OriginalCameraFrame.empty())
			{
				m_OriginalCameraFrame = cv::Mat::zeros(m_DefaultHeight, m_DefaultWidth, CV_8UC3);
			
				#ifdef _DEBUG
				cv::imshow("Original camera frame", m_OriginalCameraFrame);
				#endif
			}

			m_isCameraOpened = true;

			return m_isCameraOpened;
		}
		else
		{
			return false;
		}
	}
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuGetCamframe()
{
	m_CamCapture >> m_TestImage;

	return true;
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuGetCameraStatus()
{
	if (m_CamCapture.isOpened())
		return true;
	else
		return false;
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuGetProcessingFrame()
{
	m_TestImage.copyTo(m_OriginalCameraFrame);

	return true;
}

KUOPENCVNATIVECAMERACLASS_API bool kuOpenCVNativeCameraClass::kuGenerateHairMask()
{
	cv::cvtColor(m_OriginalCameraFrame, m_OriginalCameraFrame, CV_BGR2GRAY);

	return true;
}

KUOPENCVNATIVECAMERACLASS_API void kuOpenCVNativeCameraClass::kuCloseCamera()
{
	m_CamCapture.release();
}
