#pragma once
#include "kuOpenGLNativeClass.h"

namespace kuOpenGLWrapper
{
	public ref class kuOpenGLWrapperClass
	{
	public:
		kuOpenGLWrapperClass();
		~kuOpenGLWrapperClass();

		bool kuCreateOpenGLWindow(System::String ^ windowName, int handle);

	private:
		kuOpenGLNativeClass * m_kuOpenGLClassPtr;
	};
}

