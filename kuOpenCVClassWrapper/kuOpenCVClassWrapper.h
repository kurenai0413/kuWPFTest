#pragma once
#include "kuOpenCVClassTest.h"

using namespace System;

namespace kuOpenCV
{
	public ref class kuOpenCVWrapper
	{
	public:
		kuOpenCVWrapper();

	private:
		kuOpenCVClass * kuOpenCVClassPtr;
	};
}