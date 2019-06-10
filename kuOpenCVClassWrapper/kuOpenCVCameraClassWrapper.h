// CLR wrapper of native library 

#pragma once
#include <memory>

#include "kuOpenCVNativeCameraClass.h"

using namespace System;

namespace kuOpenCVWrapper
{
	public ref class kuOpenCVCameraClassWrapper
	{
	public:
		kuOpenCVCameraClassWrapper();
		~kuOpenCVCameraClassWrapper();

		bool kuStartCamera(int cameraIdx);
		bool kuGetCamframe();
		bool kuGetCameraStatus();
		void kuCloseCamera();

		void kuCreateWindow(System::String ^ windowName);
		void kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight);
		void kuCreateWindow(System::String ^ windowName, int handle);
		void kuCreateWindow(System::String ^ windowName, int handle, int wndWidth, int wndHeight);
		void kuDestroyCurrentWindow();

		bool kuLoadImage(System::String ^ filepath);
		void kuSetImageDefault();
		void kuShowImage();

	private:
		kuOpenCVNativeClass * kuOpenCVClassPtr;
	};
}