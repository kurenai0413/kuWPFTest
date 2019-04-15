#include <kuOpenGLNativeClass.h>

void main()
{
	kuOpenGLNativeClass nativeClassObj;

	nativeClassObj.kuCreateOpenGLWindow("OpenGL Test Window", 123);

	while (true)
	{
		nativeClassObj.kuOpenGLShowFun();
	}

	system("pause");
}