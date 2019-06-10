#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include "kuOpenCVCameraClassWrapper.h"

using namespace kuOpenCVWrapper;
using namespace msclr::interop;

kuOpenCVCameraClassWrapper::kuOpenCVCameraClassWrapper()
{
	kuOpenCVClassPtr = new kuOpenCVNativeClass;
	std::cout << "Wrapper constructor called." << std::endl;
}

kuOpenCVWrapper::kuOpenCVCameraClassWrapper::~kuOpenCVCameraClassWrapper()
{
	delete kuOpenCVClassPtr;
	kuOpenCVClassPtr = NULL;
}

bool kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuStartCamera(int cameraIdx)
{
	return kuOpenCVClassPtr->kuStartCamera(cameraIdx);
}

bool kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuGetCamframe()
{
	return kuOpenCVClassPtr->kuGetCamframe();
}

bool kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuGetCameraStatus()
{
	return kuOpenCVClassPtr->kuGetCameraStatus();
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuCloseCamera()
{
	kuOpenCVClassPtr->kuCloseCamera();
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName);
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, wndWidth, wndHeight);
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int handle)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, handle);
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuCreateWindow(System::String ^ windowName, int handle, int wndWidth, int wndHeight)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, handle, wndWidth, wndHeight);
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuDestroyCurrentWindow()
{
	kuOpenCVClassPtr->kuDestroyCurrentWindow();
}

bool kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuLoadImage(System::String ^ filepath)
{
	std::string stdWindowName = marshal_as<std::string>(filepath);
	return kuOpenCVClassPtr->kuLoadImage(stdWindowName);
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuSetImageDefault()
{
	kuOpenCVClassPtr->kuSetImageDefault();
}

void kuOpenCVWrapper::kuOpenCVCameraClassWrapper::kuShowImage()
{
	kuOpenCVClassPtr->kuShowImage();
}
