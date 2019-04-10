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

		void kuCreateWindow(System::String ^ windowName);
		void kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight);

		bool kuLoadImage(std::string filename);
		void kuSetImageDefault();
		void kuShowImage();

	private:
		kuOpenCVNativeClass * kuOpenCVClassPtr;
	};
}