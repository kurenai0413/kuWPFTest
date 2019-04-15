#include <windows.h>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <opencv2/opencv.hpp>

#include "kuOpenGLNativeClass.h"

#define GLWNDWIDTH	640
#define GLWNDHEIGHT 480

class kuOpenGLNativeClass::kuOpenGLNativeClassImpl
{
public:
	kuOpenGLNativeClassImpl();
	~kuOpenGLNativeClassImpl();

	bool kuCreateOpenGLWindow(std::string windowName, int hWnd);
	void kuOpenGLShowFun();

private:
	GLFWwindow	*	m_GLFWWnd;
	std::thread		m_OpenGLDisplayThd;

	bool			m_fOpenGLDisplay;

	void kuOpenGLDisplayFun();

	bool			kuInitOpenGLModule();
	
};

kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLNativeClassImpl()
{
	m_fOpenGLDisplay = false;

	m_GLFWWnd		 = NULL;
}

kuOpenGLNativeClass::kuOpenGLNativeClassImpl::~kuOpenGLNativeClassImpl()
{
	m_fOpenGLDisplay = false;

	if (m_OpenGLDisplayThd.joinable())
	{
		m_OpenGLDisplayThd.join();
	}
}

bool kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuCreateOpenGLWindow(std::string windowName, int hWnd)
{
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed." << std::endl;
		return false;
	}
	//glfwWindowHint(GLFW_DECORATED, false);
	//glfwWindowHint(GLFW_VISIBLE, false);

	m_GLFWWnd = glfwCreateWindow(GLWNDWIDTH, GLWNDHEIGHT, "OpenGL Test Window", NULL, NULL);
	//HWND glfwHWND = glfwGetWin32Window(m_GLFWWnd);
	//::SetParent(hWnd, GetDlgItem(IDC_GLView)->m_hWnd);
	glfwShowWindow(m_GLFWWnd);

	glfwMakeContextCurrent(m_GLFWWnd);
	glViewport(0, 0, GLWNDWIDTH, GLWNDHEIGHT);

	#pragma region // window control region //
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(m_GLFWWnd, CursorPositionCallback);
	//glfwSetScrollCallback(m_GLFWWnd, ScrollCallback);
	//glfwSetKeyCallback(m_glWnd, KeyCallback);
	//glfwSetMouseButtonCallback(m_GLFWWnd, MouseButtonCallback);
	#pragma endregion

	// tell GLFW to capture our mouse
	//glfwSetInputMode(m_glWnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (m_GLFWWnd != NULL)
	{
		m_fOpenGLDisplay   = true;
		m_OpenGLDisplayThd = std::thread(&kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLDisplayFun, this);

		return true;
	}
	else
	{
		return false;
	}
}

void kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLDisplayFun()
{
	glfwMakeContextCurrent(m_GLFWWnd);

	glEnable(GL_DEPTH_TEST);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit failed, aborting." << std::endl;
		//return false;
	}

	while (m_fOpenGLDisplay)
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//std::cout << "Display thread." << std::endl;

		glfwSwapBuffers(m_GLFWWnd);
	}
}

void kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLShowFun()
{
	glfwPollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "Display thread." << std::endl;

	glfwSwapBuffers(m_GLFWWnd);
}

KUOPENGLNATIVECLASS_API kuOpenGLNativeClass::kuOpenGLNativeClass() : pimpl(new kuOpenGLNativeClassImpl)
{

}

KUOPENGLNATIVECLASS_API kuOpenGLNativeClass::~kuOpenGLNativeClass()
{
}

KUOPENGLNATIVECLASS_API bool kuOpenGLNativeClass::kuCreateOpenGLWindow(std::string windowName, int hWnd)
{
	return pimpl->kuCreateOpenGLWindow(windowName, hWnd);
}

KUOPENGLNATIVECLASS_API void kuOpenGLNativeClass::kuOpenGLShowFun()
{
	return pimpl->kuOpenGLShowFun();
}
