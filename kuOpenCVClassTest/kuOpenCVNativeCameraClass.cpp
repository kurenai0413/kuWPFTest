#include "kuOpenCVNativeCameraClass.h"

#ifdef _DEBUG
#define ShowDebugImage true
#endif

//#define SingleImageTest true

#pragma region // Pre-processor define //
#define ResizeScale						3

#define IndentScaleX					0.25
#define UpperYIndentScale				0.05
#define LowerYIndentScale				0.15

#define PaddingScaleX					0.8		// 0.65
#define UpperYPaddingScale				0.85
#define LowerYPaddingScale				1.2

#define FaceRegionInPaddingScaleY		1.0
#define FaceRegionInPaddingScaleYDown	1.0
#define FaceRegionInPaddingScaleX		0.5		// 0.35

#define ForeheadRegion					60
#define ForeheadRegionScale				0.1

#define ColorHue						120

#pragma endregion

#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace cv;

#pragma region // kuOpenCVNativeCameraClassImpl define //
class kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl {
public:
	kuOpenCVNativeCameraClassImpl();
	~kuOpenCVNativeCameraClassImpl();

	void kuSetParentHWND(HWND parentHWND);
	void kuSetWindowName(std::string windowName);
		 
	void kuCreateWindow(std::string windowName);
	void kuCreateWindow(std::string windowName, int wndWidth, int wndHeight);
	void kuCreateWindow(std::string windowName, double imgScale);
	void kuCreateWindow(std::string windowName, int handle);
	void kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight);
	void kuDestroyCurrentWindow();
		 
	bool kuLoadImage(std::string filePath);
	void kuSaveImage(std::string filePath);
	void kuSetImageDefault();
	void kuShowImage();
	void kuShowProcessedImage();
		 
	bool kuStartCamera(int cameraIdx);
	void kuCloseCamera();
		 
	bool kuGetCamframe();
	bool kuGetCameraStatus();
		 
	bool kuGetProcessingFrame();
	bool kuGenerateHairMask();

	bool kuLoadDlibModels();

	void kuShowFinalHairMask();

private:
	int								m_DefaultWidth;
	int								m_DefaultHeight;

	Mat								m_TestImage;
	Mat								m_OriginalCameraFrame;
	Mat								m_FinalHairMask;	
	
	std::string						m_CurrnetWindowName;

	Mat								displayImg;
	Mat								updatedHSVImg;
	Mat								updatedCamFrame;

	VideoCapture					m_CamCapture;

	dlib::shape_predictor			poseModel;
	dlib::frontal_face_detector		detector;

	int								m_CameraIdx;

	bool							m_isCameraOpened;
	bool							m_WindowCreateFlag;

	void FindMaxAreaFace(std::vector<dlib::rectangle> faces, int &maxAreaFaceIdx);
	void GenerateNewPt(cv::Point oriPt, int faceWidth, float faceHeight, float xShiftScale, float yShiftScale, cv::Point &newPt);
	void JudgeCoodinateVal(int upperLevel, int &coordinateVal);
	void CalculateRegionMeanAndSTD(cv::Mat faceYCrCbImg, double &YMean, double &YStd, double &CrMean, double &CrStd, double &CbMean, double &CbStd);
	void CalculatePathChannelSum(cv::Mat patchImg, double &sumA, double &sumB, double &sumC, double &sqSumA, double &sqSumB, double &sqSumC);
	void GrabCutExtractOriginalForeground(cv::Mat maskImg, cv::Mat originalImg, cv::Point tlPtInOri, cv::Mat & foregroundImg);
	void CalculateRGBRegionMeanAndSTDExcludeBlack(cv::Mat RGBPatch, double &firstMean, double &firstStd, double &secondMean, double &secondStd, double &thirdMean, double &thirdStd);
	void CalculateRGBPatchChannelSumExcludeBlack(cv::Mat RGBPatch, int &validPixelNum, double &sumA, double &sumB, double &sumC, double &sqSumA, double &sqSumB, double &sqSumC);


};
#pragma endregion

#pragma region // kuOpenCVNativeCameraClass implementation //
kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClass() : pimpl(new kuOpenCVNativeCameraClassImpl)
{

}

kuOpenCVNativeCameraClass::~kuOpenCVNativeCameraClass()
{

}

void kuOpenCVNativeCameraClass::kuSetParentHWND(HWND parentHWND)
{
	pimpl->kuSetParentHWND(parentHWND);
}

void kuOpenCVNativeCameraClass::kuSetWindowName(std::string windowName)
{
	pimpl->kuSetWindowName(windowName);
}

void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName)
{
	pimpl->kuCreateWindow(windowName);
}

void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	pimpl->kuCreateWindow(windowName, wndWidth, wndHeight);
}

void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, double imgScale)
{
	pimpl->kuCreateWindow(windowName, imgScale);
}

void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int handle)
{
	pimpl->kuCreateWindow(windowName, handle);
}

void kuOpenCVNativeCameraClass::kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight)
{
	pimpl->kuCreateWindow(windowName, handle, wndWidth, wndHeight);
}

void kuOpenCVNativeCameraClass::kuDestroyCurrentWindow()
{
	pimpl->kuDestroyCurrentWindow();
}

bool kuOpenCVNativeCameraClass::kuLoadImage(std::string filePath)
{
	return pimpl->kuLoadImage(filePath);
}

void kuOpenCVNativeCameraClass::kuSaveImage(std::string filePath)
{
	pimpl->kuSaveImage(filePath);
}

void kuOpenCVNativeCameraClass::kuSetImageDefault()
{
	pimpl->kuSetImageDefault();
}

void kuOpenCVNativeCameraClass::kuShowImage()
{
	pimpl->kuShowImage();
}

void kuOpenCVNativeCameraClass::kuShowProcessedImage()
{
	pimpl->kuShowProcessedImage();
}

bool kuOpenCVNativeCameraClass::kuStartCamera(int cameraIdx)
{
	return pimpl->kuStartCamera(cameraIdx);
}

void kuOpenCVNativeCameraClass::kuCloseCamera()
{
	pimpl->kuCloseCamera();
}

bool kuOpenCVNativeCameraClass::kuGetCamframe()
{
	return pimpl->kuGetCamframe();
}

bool kuOpenCVNativeCameraClass::kuGetCameraStatus()
{
	return pimpl->kuGetCameraStatus();
}

bool kuOpenCVNativeCameraClass::kuGetProcessingFrame()
{
	return pimpl->kuGetProcessingFrame();
}

bool kuOpenCVNativeCameraClass::kuGenerateHairMask()
{
	return pimpl->kuGenerateHairMask();
}

bool kuOpenCVNativeCameraClass::kuLoadDlibModels()
{
	return pimpl->kuLoadDlibModels();
}

void kuOpenCVNativeCameraClass::kuShowFinalHairMask()
{
	pimpl->kuShowFinalHairMask();
}
#pragma endregion

#pragma region // kuOpenCVNativeCameraClassImpl implementation //
kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuOpenCVNativeCameraClassImpl()
{
	m_isCameraOpened   = false;
	m_WindowCreateFlag = false;

	m_DefaultWidth	   = 1280;
	m_DefaultHeight	   = 720;

	//std::cout << "Native constructor called." << std::endl;
}

kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::~kuOpenCVNativeCameraClassImpl()
{
	if (m_isCameraOpened)
	{
		kuCloseCamera();
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuSetParentHWND(HWND parentHWND)
{

}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuShowImage()
{
	cv::imshow(m_CurrnetWindowName, m_TestImage);
	cv::waitKey(33);
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuShowProcessedImage()
{
	cv::imshow(m_CurrnetWindowName, m_OriginalCameraFrame);
	cv::waitKey(33);
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuSetWindowName(std::string windowName)
{
	m_CurrnetWindowName = windowName;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCreateWindow(std::string windowName)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		kuSetWindowName(windowName);

		m_CurrnetWindowName = windowName;

		m_WindowCreateFlag = true;
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCreateWindow(std::string windowName, int wndWidth, int wndHeight)
{
	if (!m_WindowCreateFlag)
	{
		cv::namedWindow(windowName, 1);
		cv::resizeWindow(windowName, cv::Size(wndWidth, wndHeight));
		kuSetWindowName(windowName);

		m_WindowCreateFlag = true;
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCreateWindow(std::string windowName, double imgScale)
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

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCreateWindow(std::string windowName, int handle)
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

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight)
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

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuDestroyCurrentWindow()
{
	if (m_WindowCreateFlag)
	{
		cv::destroyWindow(m_CurrnetWindowName);
	}
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuLoadImage(std::string filePath)
{
	m_TestImage = cv::imread(filePath, 1);

	if (!m_TestImage.empty())
		return true;
	else
		return false;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuSaveImage(std::string filePath)
{
	cv::imwrite(filePath, m_TestImage);
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuSetImageDefault()
{
	m_TestImage = cv::Mat::zeros(m_DefaultHeight, m_DefaultWidth, CV_8UC1);
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuStartCamera(int cameraIdx)
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

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuGetCamframe()
{
	m_CamCapture >> m_TestImage;

	return true;
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuGetCameraStatus()
{
	if (m_CamCapture.isOpened())
		return true;
	else
		return false;
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuGetProcessingFrame()
{
#ifdef SingleImageTest
	m_OriginalCameraFrame = imread("UniColor_Peggy_A2.jpg", 1);
#else
	m_TestImage.copyTo(m_OriginalCameraFrame);
#endif
	
	return true;
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuGenerateHairMask()
{
	//cv::cvtColor(m_OriginalCameraFrame, m_OriginalCameraFrame, CV_RGB2HSV);
	//return true;
	
	cv::Mat			colorImgQuarter;
	cv::Mat			grayImgQuarter;
	cv::Mat			faceContourRegionImg;

	cv::Mat			indentROIImg, indentROIImgGray, indentROIHSVImg;
	cv::Mat			paddingROIImg, paddingROIHSVImg;

	cv::Mat			paddingFaceContourRegionImg;
	cv::Mat			paddingFaceContourRegionColorImg;

	cv::Mat			FGMask;

	cv::Mat			filteredHairMask;

	cv::Rect		faceROI, indentROI, paddingROI, newFaceROI;

	cv::Point		indentTLPt, indentBRPt;
	cv::Point		paddingTLPt, paddingBRPt;

	std::vector<dlib::rectangle>	faces;

	double SkinHMean, SkinSMean, SkinVMean, SkinHStd, SkinSStd, SkinVStd;
	double chinHMean, chinHStd, chinSMean, chinSStd, chinVMean, chinVStd;
	double foreheadHMean, foreheadHStd, foreheadSMean, foreheadSStd, foreheadVMean, foreheadVStd;

	float scale = (float)1 / (float)ResizeScale;

#ifdef SingleImageTest
	cv::resize(m_OriginalCameraFrame, m_OriginalCameraFrame, cv::Size(1280, 720));
#endif

	m_OriginalCameraFrame.copyTo(displayImg);
	cv::resize(m_OriginalCameraFrame, colorImgQuarter, cv::Size(scale * m_OriginalCameraFrame.cols, scale * m_OriginalCameraFrame.rows));

	faceContourRegionImg = cv::Mat::zeros(displayImg.rows, displayImg.cols, CV_8UC3);
	updatedHSVImg		 = cv::Mat::zeros(displayImg.rows, displayImg.cols, CV_8UC3);

	#pragma region // Color space conversion //
	cv::cvtColor(m_OriginalCameraFrame, updatedHSVImg, CV_RGB2HSV);	

	cv::imshow("Updated HSV Image", updatedHSVImg);
	#pragma endregion

	#pragma region // Detect faces //
	cv::cvtColor(colorImgQuarter, grayImgQuarter, CV_BGRA2GRAY);
	dlib::cv_image<uchar> imgQuarter_dlib(grayImgQuarter);

	// Detect faces 
	faces = detector(imgQuarter_dlib);
	#pragma endregion

	int maxAreaFaceIdx;

	if (faces.size() <= 0)
	{
		return false;
	}
	else
	{
		FindMaxAreaFace(faces, maxAreaFaceIdx);

		#pragma region // Extract facial region by shape components //
		std::vector<dlib::full_object_detection> shapes;
		shapes.push_back(poseModel(imgQuarter_dlib, faces[maxAreaFaceIdx]));

		std::vector<std::vector<cv::Point>> faceContour;
		std::vector<cv::Point>				tempContour;

		if (shapes.size() != 0)
		{
			#pragma region // Arrange facial landmark points //
			for (int i = 0; i <= 16; i++)
			{
				cv::Point2f landmarkPt = cv::Point2f(ResizeScale * shapes[0].part(i).x(), ResizeScale * shapes[0].part(i).y());
				//cv::circle(displayImg, landmarkPt, 0, CV_RGB(255, 0, 0), 2, CV_AA);

				tempContour.push_back(cv::Point(landmarkPt.x, landmarkPt.y));

				//std::string idxText = std::to_string(i);
				//int baseline;
				//cv::Size textSize = cv::getTextSize(idxText, cv::FONT_HERSHEY_COMPLEX, 1, 1, &baseline);
				//cv::putText(displayImg, idxText, landmarkPt, CV_FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0, 255, 0), 1, CV_AA);
			}

			for (int i = 26; i >= 17; i--)
			{
				cv::Point2f landmarkPt = cv::Point2f(ResizeScale * shapes[0].part(i).x(), ResizeScale * shapes[0].part(i).y());
				//cv::circle(displayImg, landmarkPt, 0, CV_RGB(255, 0, 0), 2, CV_AA);

				tempContour.push_back(cv::Point(landmarkPt.x, landmarkPt.y));
			}

			faceContour.push_back(tempContour);
			#pragma endregion

			cv::drawContours(faceContourRegionImg, faceContour, 0, CV_RGB(255, 255, 255), CV_FILLED, CV_AA);
			cv::cvtColor(faceContourRegionImg, faceContourRegionImg, CV_BGR2GRAY);
			//cv::imshow("Face contour region", faceContourRegionImg);
		}
		#pragma endregion

		#pragma region // Define face detection result region //
		cv::Point2f tlCorner = cv::Point2f(ResizeScale * (float)faces[maxAreaFaceIdx].left(), ResizeScale * (float)faces[maxAreaFaceIdx].top());
		cv::Point2f brCorner = cv::Point2f(ResizeScale * (float)(faces[maxAreaFaceIdx].left() + faces[maxAreaFaceIdx].width()),
			ResizeScale * (float)(faces[maxAreaFaceIdx].top() + faces[maxAreaFaceIdx].height()));
		faceROI = cv::Rect(tlCorner, brCorner);
		//std::cout << faceROI.x << ", " << faceROI.y << " | " << faceROI.width << ", " << faceROI.height << std::endl;
		//faceROIImg = colorImg(faceROI);
		#pragma endregion

		int originalFaceWidth	= ResizeScale * (int)abs(faces[maxAreaFaceIdx].left() - faces[maxAreaFaceIdx].right());
		int originalFaceHeight  = ResizeScale * (int)abs(faces[maxAreaFaceIdx].top() - faces[maxAreaFaceIdx].bottom());
		int originalFaceCenterX = 0.5 * ResizeScale * ((int)abs(faces[maxAreaFaceIdx].left() + faces[maxAreaFaceIdx].right()));
		int originalFaceCenterY = 0.5 * ResizeScale * ((int)abs(faces[maxAreaFaceIdx].top() + faces[maxAreaFaceIdx].bottom()));

		cv::Point2f faceCenter = cv::Point2f(originalFaceCenterX, originalFaceCenterY);

		#pragma region // Crop indent ROI image //
		GenerateNewPt(tlCorner, originalFaceWidth, originalFaceHeight, IndentScaleX, -UpperYIndentScale, indentTLPt);
		GenerateNewPt(brCorner, originalFaceWidth, originalFaceHeight, -IndentScaleX, -LowerYIndentScale, indentBRPt);
		indentROI = cv::Rect(indentTLPt.x, indentTLPt.y, abs(indentBRPt.x - indentTLPt.x), abs(indentBRPt.y - indentTLPt.y));
		indentROIImg = m_OriginalCameraFrame(indentROI);

		cv::Mat indentROIImgHSV;
		cv::cvtColor(indentROIImg, indentROIImgHSV, CV_BGR2HSV);
		//CalculateHistogramYCrCb(indentROIImgYCrCb);
		//CalculateHistogramHSV(indentROIImgHSV);

		//cv::imwrite("TestImage_IndentROIImage.bmp", indentROIImg);
		cv::imshow("Indent ROI Image", indentROIImg);
		#pragma endregion
	
		#pragma region // Crop padding ROI image //
		GenerateNewPt(indentTLPt, originalFaceWidth, originalFaceHeight, -PaddingScaleX, -UpperYPaddingScale, paddingTLPt);
		GenerateNewPt(indentBRPt, originalFaceWidth, originalFaceHeight, PaddingScaleX, LowerYPaddingScale, paddingBRPt);
		paddingROI = cv::Rect(paddingTLPt.x, paddingTLPt.y, abs(paddingBRPt.x - paddingTLPt.x), abs(paddingBRPt.y - paddingTLPt.y));
		paddingROIImg = m_OriginalCameraFrame(paddingROI);

		cv::imshow("Padding ROI Image", paddingROIImg);
		cv::imwrite("PaddingROIImage.bmp", paddingROIImg);
		#pragma endregion

		#pragma region // Paddingface contour region color image //
		paddingFaceContourRegionImg = faceContourRegionImg(paddingROI);

		cv::Mat dilateStruct = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(15, 15));
		cv::dilate(paddingFaceContourRegionImg, paddingFaceContourRegionImg, dilateStruct);

		paddingFaceContourRegionColorImg = cv::Mat::zeros(paddingFaceContourRegionImg.rows, paddingFaceContourRegionImg.cols, CV_8UC3);

		for (int j = 0; j < paddingFaceContourRegionImg.rows; j++)
		{
			for (int i = 0; i < paddingFaceContourRegionImg.cols; i++)
			{
				uchar val = paddingFaceContourRegionImg.at<uchar>(j, i);

				if (val == 255)
				{
					int idxInOriX = i + paddingROI.x;
					int idxInOriY = j + paddingROI.y;

					paddingFaceContourRegionColorImg.at<uchar>(j, 3 * i)	 = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX);
					paddingFaceContourRegionColorImg.at<uchar>(j, 3 * i + 1) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 1);
					paddingFaceContourRegionColorImg.at<uchar>(j, 3 * i + 2) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 2);
				}
			}
		}

		cv::imshow("Padding face contour region", paddingFaceContourRegionImg);
		//cv::imwrite("PaddingFaceContourRegionColorImage.bmp", paddingFaceContourRegionColorImg);
		cv::imwrite("paddingFaceContourRegionImg.bmp", paddingFaceContourRegionImg);
		#pragma endregion

		#pragma region // Determine color model region //
		std::vector<std::vector<cv::Point>>		contours;
		cv::findContours(paddingFaceContourRegionImg, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
		std::cout << contours.size() << std::endl;

		cv::Point minimalYPos = cv::Point(0, 0);
		cv::Point maximumYPos = cv::Point(0, 0);
		int minY = paddingFaceContourRegionImg.rows;
		int maxY = 0;
		for (int i = 0; i < contours[0].size(); i++)
		{
			if (contours[0][i].y < minY)
			{
				minY = contours[0][i].y;

				minimalYPos = contours[0][i];
			}

			if (contours[0][i].y > maxY)
			{
				maxY = contours[0][i].y;

				maximumYPos = contours[0][i];
			}
		}

		//cv::Point minimalYPos = FindMinimumYPos(paddingFaceContourRegionImg);
		std::cout << minimalYPos << std::endl;

		cv::Point foreheadRegionTLPoint = cv::Point(minimalYPos.x - 0.5 * ForeheadRegionScale * faceROI.width, minimalYPos.y - ForeheadRegionScale * faceROI.width);
		cv::Point foreheadRegionBRPoint = cv::Point(minimalYPos.x + 0.5 * ForeheadRegionScale * faceROI.width, minimalYPos.y);

		cv::Point chinRegionTLPoint = cv::Point(maximumYPos.x - 0.5 * ForeheadRegionScale * faceROI.width, maximumYPos.y);
		cv::Point chinRegionBRPoint = cv::Point(maximumYPos.x + 0.5 * ForeheadRegionScale * faceROI.width, maximumYPos.y + ForeheadRegionScale * faceROI.width);

		//std::cout << foreheadRegionTLPoint << std::endl;
		//std::cout << foreheadRegionBRPoint << std::endl;

		//cv::rectangle(paddingROIImg, chinRegionTLPoint, chinRegionBRPoint, CV_RGB(0, 255, 0), 1, CV_AA);
		#pragma endregion

		#pragma region // Extract skin color model //
		cv::Mat foreheadROIImg = paddingROIImg(cv::Rect(foreheadRegionTLPoint, foreheadRegionBRPoint));
		cv::Mat chinROIImg = paddingROIImg(cv::Rect(chinRegionTLPoint, chinRegionBRPoint));
		cv::Mat foreheadROIHSVImg;
		cv::Mat foreheadROIYCrCbImg;
		cv::Mat chinROIHSVImg;

		cv::cvtColor(paddingROIImg, paddingROIHSVImg, CV_BGR2HSV);
		cv::cvtColor(indentROIImg, indentROIHSVImg, CV_BGR2HSV);

		cv::cvtColor(foreheadROIImg, foreheadROIHSVImg, CV_BGR2HSV);
		cv::cvtColor(chinROIImg, chinROIHSVImg, CV_BGR2HSV);

		cv::imshow("paddingROIHSVImg", paddingROIHSVImg);
		cv::imshow("chinROIHSVImg", chinROIHSVImg);

		CalculateRegionMeanAndSTD(indentROIImgHSV, SkinHMean, SkinHStd, SkinSMean, SkinSStd, SkinVMean, SkinVStd);
		CalculateRegionMeanAndSTD(chinROIHSVImg, chinHMean, chinHStd, chinSMean, chinSStd, chinVMean, chinVStd);
		CalculateRegionMeanAndSTD(foreheadROIHSVImg, foreheadHMean, foreheadHStd, foreheadSMean, foreheadSStd, foreheadVMean, foreheadSStd);

		std::cout << "Chin: " << std::endl;
		std::cout << chinHMean << ", " << chinHStd << std::endl;
		std::cout << chinSMean << ", " << chinSStd << std::endl;
		std::cout << chinVMean << ", " << chinVStd << std::endl;
		std::cout << std::endl;

		//cv::cvtColor(indentROIImg, indentROIYCrCbImg, CV_BGR2YCrCb);
		//cv::cvtColor(paddingROIImg, paddingROIYCrCbImg, CV_BGR2YCrCb);
		//CalculateRegionMeanAndSTD(indentROIYCrCbImg, SkinYMean, SkinYStd, SkinCrMean, SkinCrStd, SkinCbMean, SkinCbStd);

		/*std::fstream file;
		file.open("Statics_IndentFace.txt", std::ios::out);
		file << "H: " << SkinHMean << ", " << SkinHStd << std::endl;
		file << "S: " << SkinSMean << ", " << SkinSStd << std::endl;
		file << "V: " << SkinVMean << ", " << SkinVStd << std::endl;
		file << std::endl;
		file << "Y: " << SkinYMean << ", " << SkinYStd << std::endl;
		file << "Cr: " << SkinCrMean << ", " << SkinCrStd << std::endl;
		file << "Cb: " << SkinCbMean << ", " << SkinCbStd << std::endl;
		file.close();*/
		#pragma endregion

		#pragma region // Extract new face region //
		cv::Point newFaceTLPt = cv::Point(faceROI.x - paddingROI.x - FaceRegionInPaddingScaleX * faceROI.width, faceROI.y - FaceRegionInPaddingScaleY * faceROI.height - paddingROI.y);
		cv::Point newFaceBRPt = cv::Point(faceROI.x + FaceRegionInPaddingScaleX * faceROI.width + faceROI.width - paddingROI.x, faceROI.y + faceROI.height + FaceRegionInPaddingScaleYDown * faceROI.height - paddingROI.y);

		if (newFaceBRPt.x > paddingROI.width)
			newFaceBRPt.x = paddingROI.width;
		if (newFaceBRPt.y > paddingROI.height)
			newFaceBRPt.y = paddingROI.height;

		if (newFaceTLPt.x < 0)
			newFaceTLPt.y = 0;
		if (newFaceTLPt.y < 0)
			newFaceTLPt.y = 0;

		newFaceROI = cv::Rect(newFaceTLPt, newFaceBRPt);
		//std::cout << newFaceROI << std::endl;
		#pragma endregion

		#pragma region // Perform grabcut //
		cv::Mat fgModel, bgModel;

		cv::grabCut(paddingROIImg, FGMask, newFaceROI, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);
		cv::compare(FGMask, cv::GC_PR_FGD, FGMask, cv::CMP_EQ);

		cv::imshow("mask", FGMask);

		cv::Mat extractedForeGround;
		extractedForeGround = cv::Mat::zeros(FGMask.rows, FGMask.cols, CV_8UC3);
		GrabCutExtractOriginalForeground(FGMask, m_OriginalCameraFrame, cv::Point(paddingROI.x, paddingROI.y), extractedForeGround);

		cv::imshow("extracted foreground", extractedForeGround);
		cv::imwrite("ExtractedForeground.bmp", extractedForeGround);

		#pragma region // Filtered out over-whitened pixels //
		for (int j = 0; j < extractedForeGround.rows; j++)
		{
			for (int i = 0; i < extractedForeGround.cols; i++)
			{
				uchar bVal = extractedForeGround.at<uchar>(j, 3 * i);
				uchar gVal = extractedForeGround.at<uchar>(j, 3 * i + 1);
				uchar rVal = extractedForeGround.at<uchar>(j, 3 * i + 2);

				// Difference less than a thres
				// or
				// Direct threshold

				if ((bVal >= 120) && (gVal >= 120) && (rVal >= 120))
				{
					FGMask.at<uchar>(j, i) = 0;
				}
			}
		}

		cv::imshow("over-whiten pixel filtered mask", FGMask);
		#pragma endregion
		#pragma endregion
	
		#pragma region // Remove facial parts region from foreground mask //
		cv::Mat maskWithoutFace = cv::Mat::zeros(paddingROIImg.rows, paddingROIImg.cols, CV_8UC1);

		for (int j = 0; j < paddingROIImg.rows; j++)
		{
			for (int i = 0; i < paddingROIImg.cols; i++)
			{
				uchar valInFaceContour = paddingFaceContourRegionImg.at<uchar>(j, i);
				uchar valInPyrUpMask = FGMask.at<uchar>(j, i);

				if (valInPyrUpMask == 255)
				{
					if (valInFaceContour == 255)
					{
						maskWithoutFace.at<uchar>(j, i) = 0;
					}
					else
					{
						int idxInOriX = i + paddingROI.x;
						int idxInOriY = j + paddingROI.y;

						maskWithoutFace.at<uchar>(j, i) = 255;
					}
				}
			}
		}

		cv::imshow("maskWithoutFace", maskWithoutFace);
	
		cv::Mat maskWithoutFaceColorImg = cv::Mat::zeros(paddingROIImg.rows, paddingROIImg.cols, CV_8UC3);
			
		for (int j = 0; j < FGMask.rows; j++)
		{
			for (int i = 0; i < FGMask.cols; i++)
			{
				uchar valInMaskWithoutFace = maskWithoutFace.at<uchar>(j, i);

				if (valInMaskWithoutFace == 255)
				{
					int idxInOriX = i + paddingROI.x;
					int idxInOriY = j + paddingROI.y;

					maskWithoutFaceColorImg.at<uchar>(j, 3 * i)		= m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX);
					maskWithoutFaceColorImg.at<uchar>(j, 3 * i + 1) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 1);
					maskWithoutFaceColorImg.at<uchar>(j, 3 * i + 2) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 2);
				}
			}
		}

		cv::imshow("maskWithoutFaceColorImg", maskWithoutFaceColorImg);
		#pragma endregion

		#pragma region // Filter skin pixel in maskWithoutFace //
		cv::Mat hairMask = cv::Mat::zeros(paddingROIImg.rows, paddingROIImg.cols, CV_8UC1);
		cv::Mat hairMaskColorImg = cv::Mat::zeros(paddingROIImg.rows, paddingROIImg.cols, CV_8UC3);
		filteredHairMask = cv::Mat::zeros(paddingROIImg.rows, paddingROIImg.cols, CV_8UC1);

		for (int j = 0; j < FGMask.rows; j++)
		{
			for (int i = 0; i < FGMask.cols; i++)
			{
				uchar valInPyrUpMask = FGMask.at<uchar>(j, i);

				if (valInPyrUpMask == 255)
				{
					uchar HVal = paddingROIHSVImg.at<uchar>(j, 3 * i);
					uchar SVal = paddingROIHSVImg.at<uchar>(j, 3 * i + 1);
					uchar VVal = paddingROIHSVImg.at<uchar>(j, 3 * i + 2);

					uchar valInFacialRegion = maskWithoutFace.at<uchar>(j, i);

					if (valInFacialRegion == 255)
					{
						if ((HVal > (SkinHMean - 3 * SkinHStd)) && (HVal < (SkinHMean + 3 * SkinHStd)) &&
							(SVal > (SkinSMean - 3 * SkinSStd)) && (SVal < (SkinSMean + 3 * SkinSStd)) &&
							(VVal > (SkinVMean - 3 * SkinVStd)) && (SVal < (SkinVMean + 3 * SkinVStd)))
						{

						}
						else
						{
							int idxInOriX = i + paddingROI.x;
							int idxInOriY = j + paddingROI.y;

							filteredHairMask.at<uchar>(j, i) = 255;

							hairMaskColorImg.at<uchar>(j, 3 * i)	 = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX);
							hairMaskColorImg.at<uchar>(j, 3 * i + 1) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 1);
							hairMaskColorImg.at<uchar>(j, 3 * i + 2) = m_OriginalCameraFrame.at<uchar>(idxInOriY, 3 * idxInOriX + 2);

							// Apply new hair color to image //
							//updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX)	  = ColorHue;
							//updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX + 1) = 91;
							//updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX + 2) = 190;
						}
					}
				}
			}
		}

		cv::imshow("hairMaskColorImg", hairMaskColorImg);
		#pragma endregion
	
		if (!m_FinalHairMask.empty())
		{
			m_FinalHairMask.release();
		}

		//cv::Mat filteredHairImg = cv::Mat::zeros(hairMaskColorImg.rows, hairMaskColorImg.cols, CV_8UC3);
		cv::Mat filteredHairColorImg = cv::Mat::zeros(hairMaskColorImg.rows, hairMaskColorImg.cols, CV_8UC3);
		cv::Mat	hairMaskHSVImg;
		cv::cvtColor(hairMaskColorImg, hairMaskHSVImg, CV_BGR2HSV);

		cv::imshow("hairMaskHSVImg", hairMaskHSVImg);
		cv::imwrite("hairMaskHSVImg.bmp", hairMaskHSVImg);
		
		#pragma region // Filtering out residual pixels //	
		m_FinalHairMask = cv::Mat::zeros(hairMaskColorImg.rows, hairMaskColorImg.cols, CV_8UC3);

		double newBMean, newBStd, newGMean, newGStd, newRMean, newRStd;
		double newHMean, newHStd, newSMean, newSStd, newVMean, newVStd;

		CalculateRGBRegionMeanAndSTDExcludeBlack(hairMaskColorImg, newBMean, newBStd, newGMean, newGStd, newRMean, newRStd);

		int maxSVal, minSVal;
		int maxVVal, minVVal;

		int firstCnt = 0;
		int validPixelNum = 0;

		for (int j = 0; j < hairMaskColorImg.rows; j++)
		{
			for (int i = 0; i < hairMaskColorImg.cols; i++)
			{
				int idxInOriX = i + paddingROI.x;
				int idxInOriY = j + paddingROI.y;

				uchar BVal = hairMaskColorImg.at<uchar>(j, 3 * i);
				uchar GVal = hairMaskColorImg.at<uchar>(j, 3 * i + 1);
				uchar RVal = hairMaskColorImg.at<uchar>(j, 3 * i + 2);

				uchar HVal = hairMaskHSVImg.at<uchar>(j, 3 * i);
				uchar SVal = hairMaskHSVImg.at<uchar>(j, 3 * i + 1);
				uchar VVal = hairMaskHSVImg.at<uchar>(j, 3 * i + 2);

				if ((BVal > (newBMean - newBStd)) && (BVal < (newBMean + newBStd)) &&
					(GVal > (newGMean - newGStd)) && (GVal < (newGMean + newGStd)) &&
					(RVal > (newRMean - newRStd)) && (RVal < (newRMean + newRStd)))
				{
					m_FinalHairMask.at<uchar>(j, 3 * i) = 255;
					m_FinalHairMask.at<uchar>(j, 3 * i + 1) = 255;
					m_FinalHairMask.at<uchar>(j, 3 * i + 2) = 255;

					// Apply new hair color to image //
					updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX)	  = ColorHue;
					updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX + 1) = 1.5 * SVal;
					updatedHSVImg.at<uchar>(idxInOriY, 3 * idxInOriX + 2) = 1.5 * VVal;
				}
			}
		}

		cv::imshow("filteredHairImg", m_FinalHairMask);
		#pragma endregion
		
		cv::cvtColor(updatedHSVImg, updatedCamFrame, CV_HSV2RGB);
		cv::imshow("Updated Camera Frame", updatedCamFrame);

		return true;
	}
}

bool kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuLoadDlibModels()
{
	detector = dlib::get_frontal_face_detector();
	dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> poseModel;

	return true;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuShowFinalHairMask()
{
	cv::imshow("Final Hair Mask", m_FinalHairMask);
	cv::waitKey(33);
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::kuCloseCamera()
{
	m_CamCapture.release();
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::FindMaxAreaFace(std::vector<dlib::rectangle> faces, int & maxAreaFaceIdx)
{
	int maxFaceArea = 0;
	int maxFaceIdx = 0;

	for (int i = 0; i < faces.size(); i++)
	{
		int area = faces[i].width() * faces[i].height();

		if (area > maxFaceArea)
		{
			maxFaceArea = area;
			maxFaceIdx = i;
		}
	}

	maxAreaFaceIdx = maxFaceIdx;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::GenerateNewPt(cv::Point oriPt, int faceWidth, float faceHeight, float xShiftScale, float yShiftScale, cv::Point & newPt)
{
	int newX = oriPt.x + xShiftScale * faceWidth;
	int newY = oriPt.y + yShiftScale * faceHeight;

	JudgeCoodinateVal(m_DefaultWidth, newX);
	JudgeCoodinateVal(m_DefaultHeight, newY);

	newPt = cv::Point(newX, newY);
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::JudgeCoodinateVal(int upperLevel, int & coordinateVal)
{
	if (coordinateVal < 0)
		coordinateVal = 0;
	else if (coordinateVal > upperLevel)
		coordinateVal = upperLevel - 1;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::CalculateRegionMeanAndSTD(cv::Mat faceYCrCbImg, double & YMean, double & YStd, double & CrMean, double & CrStd, double & CbMean, double & CbStd)
{
	if (!faceYCrCbImg.empty())
	{
		double	ySum = 0, crSum = 0, cbSum = 0;
		double	ySqSum = 0, crSqSum = 0, cbSqSum = 0;
		int		pixelNum = faceYCrCbImg.rows * faceYCrCbImg.cols;
		double	yMean, crMean, cbMean;
		double	yStd, crStd, cbStd;

		/*for (int j = 0; j < faceYCrCbImg.rows; j++)
		{
			for (int i = 0; i < faceYCrCbImg.cols; i++)
			{
				int YVal  = faceYCrCbImg.at<uchar>(j, 3 * i);
				int CrVal = faceYCrCbImg.at<uchar>(j, 3 * i + 1);
				int CbVal = faceYCrCbImg.at<uchar>(j, 3 * i + 2);

				ySum  += YVal;
				crSum += CrVal;
				cbSum += CbVal;

				ySqSum  += pow(YVal, 2);
				crSqSum += pow(CrVal, 2);
				cbSqSum += pow(CbVal, 2);
			}
		}*/

		CalculatePathChannelSum(faceYCrCbImg, ySum, crSum, cbSum, ySqSum, crSqSum, cbSqSum);
		//std::cout << ySum << ", " << crSum << ", " << cbSum << " | " << ySqSum << ", " << cbSqSum << ", " << crSqSum << std::endl;

		yMean = (double)ySum / (double)pixelNum;
		crMean = (double)crSum / (double)pixelNum;
		cbMean = (double)cbSum / (double)pixelNum;

		yStd = (double)ySqSum / (double)pixelNum;
		crStd = (double)crSqSum / (double)pixelNum;
		cbStd = (double)cbSqSum / (double)pixelNum;

		//std::cout << "crstd" << crStd;

		yStd -= pow(yMean, 2);
		crStd -= pow(crMean, 2);
		cbStd -= pow(cbMean, 2);

		YMean = yMean;
		CrMean = crMean;
		CbMean = cbMean;

		YStd = sqrt(yStd);
		CrStd = sqrt(crStd);
		CbStd = sqrt(cbStd);
	}
	else
	{
		YMean = 0;
		CrMean = 0;
		CbMean = 0;

		YStd = 0;
		CrStd = 0;
		CbStd = 0;
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::CalculatePathChannelSum(cv::Mat patchImg, double & sumA, double & sumB, double & sumC, double & sqSumA, double & sqSumB, double & sqSumC)
{
	double sumY = 0, sumCr = 0, sumCb = 0;
	double sqSumY = 0, sqSumCr = 0, sqSumCb = 0;

	for (int j = 0; j < patchImg.rows; j++)
	{
		for (int i = 0; i < patchImg.cols; i++)
		{
			int YVal  = patchImg.at<uchar>(j, 3 * i);
			int CrVal = patchImg.at<uchar>(j, 3 * i + 1);
			int CbVal = patchImg.at<uchar>(j, 3 * i + 2);

			sumY  += YVal;
			sumCr += CrVal;
			sumCb += CbVal;

			sqSumY  += pow(YVal, 2);
			sqSumCr += pow(CrVal, 2);
			sqSumCb += pow(CbVal, 2);
		}
	}

	sumA = sumY;
	sumB = sumCr;
	sumC = sumCb;

	sqSumA = sqSumY;
	sqSumB = sqSumCr;
	sqSumC = sqSumCb;
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::GrabCutExtractOriginalForeground(cv::Mat maskImg, cv::Mat originalImg, cv::Point tlPtInOri, cv::Mat & foregroundImg)
{
	for (int j = 0; j < maskImg.rows; j++)
	{
		for (int i = 0; i < maskImg.cols; i++)
		{
			int idxInOriX = tlPtInOri.x + i;
			int idxInOriY = tlPtInOri.y + j;

			uchar val = maskImg.at<uchar>(j, i);

			if (val == 255)
			{
				foregroundImg.at<uchar>(j, 3 * i) = originalImg.at<uchar>(idxInOriY, 3 * idxInOriX);
				foregroundImg.at<uchar>(j, 3 * i + 1) = originalImg.at<uchar>(idxInOriY, 3 * idxInOriX + 1);
				foregroundImg.at<uchar>(j, 3 * i + 2) = originalImg.at<uchar>(idxInOriY, 3 * idxInOriX + 2);
			}
		}
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::CalculateRGBRegionMeanAndSTDExcludeBlack(cv::Mat RGBRegion, double & firstMean, double & firstStd, double & secondMean, double & secondStd, double & thirdMean, double & thirdStd)
{
	if (!RGBRegion.empty())
	{
		double	firstSum = 0, secondSum = 0, thirdSum = 0;
		double	firstSqSum = 0, secondSqSum = 0, thirdSqSum = 0;
		int		pixelNum; // = testImageRGB.rows * testImageRGB.cols;

		double	meanA, meanB, meanC;
		double	stdA, stdB, stdC;

		CalculateRGBPatchChannelSumExcludeBlack(RGBRegion, pixelNum, firstSum, secondSum, thirdSum,
			firstSqSum, secondSqSum, thirdSqSum);
		std::cout << "Valid pixel num: " << pixelNum << std::endl;

		meanA = (double)firstSum / (double)pixelNum;
		meanB = (double)secondSum / (double)pixelNum;
		meanC = (double)thirdSum / (double)pixelNum;

		stdA = (double)firstSqSum / (double)pixelNum;
		stdB = (double)secondSqSum / (double)pixelNum;
		stdC = (double)thirdSqSum / (double)pixelNum;

		//std::cout << "crstd" << crStd;

		stdA -= pow(meanA, 2);
		stdB -= pow(meanB, 2);
		stdC -= pow(meanC, 2);

		firstMean = meanA;
		secondMean = meanB;
		thirdMean = meanC;

		firstStd = sqrt(stdA);
		secondStd = sqrt(stdB);
		thirdStd = sqrt(stdC);
	}
	else
	{
		firstMean = 0;
		secondMean = 0;
		thirdMean = 0;

		firstStd = 0;
		secondStd = 0;
		thirdStd = 0;
	}
}

void kuOpenCVNativeCameraClass::kuOpenCVNativeCameraClassImpl::CalculateRGBPatchChannelSumExcludeBlack(cv::Mat RGBPatch, int & validPixelNum, double & sumA, double & sumB, double & sumC, double & sqSumA, double & sqSumB, double & sqSumC)
{
	double firstSum = 0, secondSum = 0, thirdSum = 0;
	double firstSqSum = 0, secondSqSum = 0, thirdSqSum = 0;

	int	   pixelNum = 0;

	for (int j = 0; j < RGBPatch.rows; j++)
	{
		for (int i = 0; i < RGBPatch.cols; i++)
		{
			int BVal = RGBPatch.at<uchar>(j, 3 * i);
			int GVal = RGBPatch.at<uchar>(j, 3 * i + 1);
			int RVal = RGBPatch.at<uchar>(j, 3 * i + 2);

			if ((BVal > 10) && (GVal > 10) && (RVal > 10))
			{
				firstSum += BVal;
				secondSum += GVal;
				thirdSum += RVal;

				firstSqSum += pow(BVal, 2);
				secondSqSum += pow(GVal, 2);
				thirdSqSum += pow(RVal, 2);

				pixelNum++;
			}
		}
	}

	sumA = firstSum;
	sumB = secondSum;
	sumC = thirdSum;

	sqSumA = firstSqSum;
	sqSumB = secondSqSum;
	sqSumC = thirdSqSum;

	validPixelNum = pixelNum;
}
#pragma endregion