#pragma once
#include <memory>

#include "kuOpenCVNativeClass.h"

using namespace System;

namespace kuOpenCVWrapper
{
	public ref class kuOpenCVWrapperClass
	{
	public:
		kuOpenCVWrapperClass();
		~kuOpenCVWrapperClass();

		bool kuStartCamera(int cameraIdx);
		bool kuGetCamframe();
		bool kuGetCameraStatus();
		void kuCloseCamera();

		void kuCreateWindow(System::String ^ windowName);
		void kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight);
		void kuCreateWindow(System::String ^ windowName, int handle);
		void kuDestroyCurrentWindow();

		bool kuLoadImage(std::string filename);
		void kuSetImageDefault();
		void kuShowImage();

	private:
		kuOpenCVNativeClass * kuOpenCVClassPtr;
	};
}