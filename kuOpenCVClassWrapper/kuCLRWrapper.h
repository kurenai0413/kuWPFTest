// CLR wrapper of native library 

#pragma once
#include <memory>

#include "kuOpenCVNativeCameraClass.h"

using namespace System;

namespace kuCLRWrapper
{
	public ref class kuOpenCVCameraClassWrapper
	{
	public:
		kuOpenCVCameraClassWrapper();
		~kuOpenCVCameraClassWrapper();

		void kuCreateWindow(System::String ^ windowName);
		void kuCreateWindow(System::String ^ windowName, int wndWidth, int wndHeight);
		void kuCreateWindow(System::String ^ windowName, int handle);
		void kuCreateWindow(System::String ^ windowName, int handle, int wndWidth, int wndHeight);
		void kuDestroyCurrentWindow();

		bool kuLoadImage(System::String ^ filepath);
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

		void kuSetHairHueColor(int hueValue);

	private:
		kuOpenCVNativeCameraClass * kuOpenCVClassPtr;
	};
}