#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include "kuOpenGLWrapperClass.h"

using namespace kuOpenGLWrapper;
using namespace msclr::interop;

kuOpenGLWrapperClass::kuOpenGLWrapperClass()
{
	m_kuOpenGLClassPtr = new kuOpenGLNativeClass;
}

kuOpenGLWrapperClass::~kuOpenGLWrapperClass()
{
	
}

bool kuOpenGLWrapper::kuOpenGLWrapperClass::kuCreateOpenGLWindow(System::String ^ windowName, int handle)
{
	std::string stdWindowName = marshal_as<std::string>(windowName);
	m_kuOpenGLClassPtr->kuCreateOpenGLWindow(stdWindowName, handle);

	return false;
}


