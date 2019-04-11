#include "stdafx.h"

using namespace System;
using namespace kuOpenCVWrapper;

int main(array<System::String ^> ^args)
{
	//kuOpenCVWrapperClass ^ wrapperObj = gcnew kuOpenCVWrapperClass();

	kuOpenCVWrapperClass wrapperObj;

	//wrapperObj.kuSetImageDefault();
	wrapperObj.kuStartCamera(0);
	wrapperObj.kuCreateWindow("TestImage", 1280, 720);

	while (true)
	{
		bool camFrameFlag = wrapperObj.kuGetCamframe();

		if (camFrameFlag)
		{
			wrapperObj.kuShowImage();
		}
	}

    return 0;
}
