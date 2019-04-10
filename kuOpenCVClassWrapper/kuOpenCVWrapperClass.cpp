#include "kuOpenCVWrapperClass.h"

using namespace kuOpenCVWrapper;

kuOpenCVWrapperClass::kuOpenCVWrapperClass() : kuOpenCVClassPtr(new kuOpenCVNativeClass())
{
	
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
