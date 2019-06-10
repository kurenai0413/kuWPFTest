#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include "kuOpenCVCameraClassWrapper.h"

using namespace kuCLRWrapper;
using namespace msclr::interop;

kuOpenCVCameraClassWrapper::kuOpenCVCameraClassWrapper()
{
	kuOpenCVClassPtr = new kuOpenCVNativeClass;
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

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuSetImageDefault()
{
	kuOpenCVClassPtr->kuSetImageDefault();
}

void kuCLRWrapper::kuOpenCVCameraClassWrapper::kuShowImage()
{
	kuOpenCVClassPtr->kuShowImage();
}

kuCLRWrapper::kuOpenCVAlgorithmClassWrapper::kuOpenCVAlgorithmClassWrapper()
{
	throw gcnew System::NotImplementedException();
}

kuCLRWrapper::kuOpenCVAlgorithmClassWrapper::~kuOpenCVAlgorithmClassWrapper()
{
	throw gcnew System::NotImplementedException();
}
