#pragma once
#include "kuOpenCVNativeClass.h"

using namespace System;

namespace kuOpenCVWrapper
{
	public ref class kuOpenCVWrapperClass
	{
	public:
		kuOpenCVWrapperClass();

		bool kuStartCamera(int cameraIdx);
		bool kuGetCamframe();
		bool kuGetCameraStatus();

		bool kuLoadImage(std::string filename);
		void kuSetImageDefault();
		void kuShowImage();

	private:
		kuOpenCVNativeClass * kuOpenCVClassPtr;
	};
}