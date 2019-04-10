#include <thread>

#include "kuOpenCVNativeClass.h"

void displayFun(kuOpenCVNativeClass * classObj)
{

}

void main()
{
	kuOpenCVNativeClass kuOpenCVClassObj;
	/*bool testFlag = kuOpenCVClassObj.kuLoadImage("33168590_1011670962334633_3301292501440135168_n.png");
	std::cout << testFlag << std::endl;
	kuOpenCVClassObj.kuCreateWindow("Test Image", 0.5f);
	kuOpenCVClassObj.kuShowImage();*/

	kuOpenCVClassObj.kuSetImageDefault();
	kuOpenCVClassObj.kuCreateWindow("Test Image", 0.5f);

	while (true)
	{
		kuOpenCVClassObj.kuShowImage();
	}

	//while (true)
	//{
	//	kuOpenCVClassObj.kuShowImage();
	//}

	
	/*bool camFlag = kuOpenCVClassObj.kuStartCamera(0);

	while (camFlag)
	{
		kuOpenCVClassObj.kuGetCamframe();
		kuOpenCVClassObj.kuShowImage();
	}*/

	system("pause");
}