#include "stdafx.h"

using namespace System;
using namespace kuOpenCVWrapper;

int main(array<System::String ^> ^args)
{
	kuOpenCVWrapperClass ^ wrapperObj = gcnew kuOpenCVWrapperClass();

	wrapperObj->kuSetImageDefault();
	wrapperObj->kuCreateWindow("TestImage", 1280, 720);

	while (true)
	{
		wrapperObj->kuShowImage();
	}

    return 0;
}
