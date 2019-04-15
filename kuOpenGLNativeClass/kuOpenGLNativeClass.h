#pragma once
#ifdef KUOPENGLNATIVECLASS_EXPORTS
#define KUOPENGLNATIVECLASS_API __declspec(dllexport)
#else
#define KUOPENGLNATIVECLASS_API __declspec(dllimport)
#endif

#include <memory>
#include <string>

class kuOpenGLNativeClass
{
public:
	KUOPENGLNATIVECLASS_API kuOpenGLNativeClass();
	KUOPENGLNATIVECLASS_API ~kuOpenGLNativeClass();

	KUOPENGLNATIVECLASS_API bool kuCreateOpenGLWindow(std::string windowName, int hWnd);
	KUOPENGLNATIVECLASS_API void kuOpenGLDisplayFun();
	KUOPENGLNATIVECLASS_API void kuOpenGLShowFun();

private:
	class										kuOpenGLNativeClassImpl;
	std::unique_ptr<kuOpenGLNativeClassImpl>	pimpl;
};

