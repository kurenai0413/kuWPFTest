#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include "kuOpenCVWrapperClass.h"

using namespace kuOpenCVWrapper;
using namespace msclr::interop;

kuOpenCVWrapperClass::kuOpenCVWrapperClass()
{
	kuOpenCVClassPtr = new kuOpenCVNativeClass;
	std::cout << "Wrapper constructor called." << std::endl;
}

kuOpenCVWrapper::kuOpenCVWrapperClass::~kuOpenCVWrapperClass()
{
	delete kuOpenCVClassPtr;
	kuOpenCVClassPtr = NULL;
}

bool kuOpenCVWrapper::kuOpenCVWrapperClass::kuStartCamera(int cameraIdx)
{
	return kuOpenCVClassPtr->kuStartCamera(cameraIdx);
}

bool kuOpenCVWrapper::kuOpenCVWrapperClass::kuGetCamframe()
{
	return kuOpenCVClassPtr->kuGetCamframe();
}

bool kuOpenCVWrapper::kuOpenCVWrapperClass::kuGetCameraStatus()
{
	return kuOpenCVClassPtr->kuGetCameraStatus();
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuCloseCamera()
{
	kuOpenCVClassPtr->kuCloseCamera(0);
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuCreateWindow(System::String ^ windowName)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName);
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	kuOpenCVClassPtr->kuCreateWindow(stdWindowName, wndWidth, wndHeight);
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuDestroyCurrentWindow()
{
	kuOpenCVClassPtr->kuDestroyCurrentWindow();
}

bool kuOpenCVWrapper::kuOpenCVWrapperClass::kuLoadImage(std::string filename)
{
	return kuOpenCVClassPtr->kuLoadImage(filename);
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuSetImageDefault()
{
	kuOpenCVClassPtr->kuSetImageDefault();
}

void kuOpenCVWrapper::kuOpenCVWrapperClass::kuShowImage()
{
	kuOpenCVClassPtr->kuShowImage();
}
