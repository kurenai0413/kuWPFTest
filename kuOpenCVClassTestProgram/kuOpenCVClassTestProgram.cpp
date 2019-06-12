#include <thread>

#include "kuOpenCVNativeCameraClass.h"

void displayFun(kuOpenCVNativeCameraClass * classObj)
{

}

void main()
{
	kuOpenCVNativeCameraClass kuOpenCVClassObj;

	kuOpenCVClassObj.kuCreateWindow("Test Image", 1.0f);

	bool camFlag = kuOpenCVClassObj.kuStartCamera(0);

	int frameCnt = 0;

	/*while (camFlag)
	{
		kuOpenCVClassObj.kuGetCamframe();
		kuOpenCVClassObj.kuShowImage();
		
		frameCnt++;

		std::cout << frameCnt << std::endl;
	}*/

	kuOpenCVClassObj.kuGetCamframe();
	kuOpenCVClassObj.kuGetProcessingFrame();
	kuOpenCVClassObj.kuGenerateHairMask();
	kuOpenCVClassObj.kuShowProcessedImage();

	system("pause");
}