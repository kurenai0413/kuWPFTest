#include <thread>

#include "kuOpenCVNativeCameraClass.h"

void displayFun(kuOpenCVNativeClass * classObj)
{

}

void main()
{
	kuOpenCVNativeClass kuOpenCVClassObj;

	kuOpenCVClassObj.kuCreateWindow("Test Image", 1.0f);

	bool camFlag = kuOpenCVClassObj.kuStartCamera(0);

	int frameCnt = 0;

	while (camFlag)
	{
		kuOpenCVClassObj.kuGetCamframe();
		kuOpenCVClassObj.kuShowImage();
		
		frameCnt++;

		std::cout << frameCnt << std::endl;
	}

	system("pause");
}