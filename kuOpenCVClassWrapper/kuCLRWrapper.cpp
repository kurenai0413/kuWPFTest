#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include "kuCLRWrapper.h"

using namespace kuCLRWrapper;
using namespace msclr::interop;

#pragma region // kuOpenCVCameraClassWrapper //
kuOpenCVCameraClassWrapper::kuOpenCVCameraClassWrapper()
{
	kuOpenCVClassPtr = new kuOpenCVNativeCameraClass;
	std::cout << "Wrapper constructor called." << std::endl;
}

kuCLRWrapper::kuOpenCVCameraClassWrapper::~kuOpenCVCameraClassWrapper()
{
	delete kuOpenCVClassPtr;
	kuOpenCVClassPtr = NULL;
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuStartCamera(int cameraIdx)
{
	return kuOpenCVClassPtr->kuStartCamera(cameraIdx);
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuGetCamframe()
{
	return kuOpenCVClassPtr->kuGetCamframe();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuGetCameraStatus()
{
	return kuOpenCVClassPtr->kuGetCameraStatus();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuGetProcessingFrame()
{
	return kuOpenCVClassPtr->kuGetProcessingFrame();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuGenerateHairMask()
{
	return kuOpenCVClassPtr->kuGenerateHairMask();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuChangeHairColor()
{
	return kuOpenCVClassPtr->kuChangeHairColorPublic();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuLoadDlibModels()
{
	return kuOpenCVClassPtr->kuLoadDlibModels();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuShowFinalHairMask()
{
	kuOpenCVClassPtr->kuShowFinalHairMask();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuSetHairHueColor(int hueValue)
{
	kuOpenCVClassPtr->kuSetHairHueColor(hueValue);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuCloseCamera()
{
	kuOpenCVClassPtr->kuCloseCamera();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, wndWidth, wndHeight);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int handle)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, handle);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int handle, int wndWidth, int wndHeight)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, handle, wndWidth, wndHeight);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuDestroyCurrentWindow()
{
	kuOpenCVClassPtr->kuDestroyCurrentWindow();
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuLoadImage(System::String ^ filepath)
{
	std::string stdWindowName = marshal_as<std::string>(filepath);
	return kuOpenCVClassPtr->kuLoadImage(stdWindowName);
}

bool kuCLRWrapper::kuOpenCVCameraClassWrapper::kuLoadProcessingImage(System::String ^ filePath)
{
	std::string stdWindowName = marshal_as<std::string>(filePath);
	return kuOpenCVClassPtr->kuLoadProcessingImage(stdWindowName);
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuSetImageDefault()
{
	kuOpenCVClassPtr->kuSetImageDefault();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuShowImage()
{
	kuOpenCVClassPtr->kuShowImage();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuShowProcessedImage()
{
	kuOpenCVClassPtr->kuShowProcessedImage();
}
#pragma endregion