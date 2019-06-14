#pragma once
#ifdef KUOPENCVNATIVECAMERACLASS_EXPORTS
#define KUOPENCVNATIVECAMERACLASS_API __declspec(dllexport)
#else
#define KUOPENCVNATIVECAMERACLASS_API __declspec(dllimport)
#endif

#include <windows.h>
#include <iostream>

class KUOPENCVNATIVECAMERACLASS_API kuOpenCVNativeCameraClass
{
public:
	kuOpenCVNativeCameraClass();
	~kuOpenCVNativeCameraClass();
	
	void kuSetParentHWND(HWND parentHWND);
	void kuSetWindowName(std::string windowName);

	void kuCreateWindow(std::string windowName);
	void kuCreateWindow(std::string windowName, int wndWidth, int wndHeight);
	void kuCreateWindow(std::string windowName, double imgScale);
	void kuCreateWindow(std::string windowName, int handle);
	void kuCreateWindow(std::string windowName, int handle, int wndWidth, int wndHeight);
	void kuDestroyCurrentWindow();

	bool kuLoadImage(std::string filePath);
	bool kuLoadProcessingImage(std::string filePath);
	void kuSaveImage(std::string filePath);
	void kuSetImageDefault();
	void kuShowImage();
	void kuShowProcessedImage();

	bool kuStartCamera(int cameraIdx);
	void kuCloseCamera();

	bool kuGetCamframe();
	bool kuGetCameraStatus();

	bool kuGetProcessingFrame();
	bool kuGenerateHairMask();
	bool kuChangeHairColorPublic();

	bool kuLoadDlibModels();

	void kuSetHairHueColor(int hueValue);

	#pragma region // For debug //
	void kuShowFinalHairMask();
	#pragma endregion

private:
	class kuOpenCVNativeCameraClassImpl;
	std::unique_ptr<kuOpenCVNativeCameraClassImpl> pimpl;
};