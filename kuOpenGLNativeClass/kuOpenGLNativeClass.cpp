#include <windows.h>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <opencv2/opencv.hpp>

#include "kuOpenGLNativeClass.h"
#include "kuShaderHandler.h"
#include "kuOpenGLPrimitiveObjects.h"

#define GLWNDWIDTH	1024
#define GLWNDHEIGHT 768

using namespace kuGLModule;

#pragma region // kuOpenGLNativeClassImpl //
class kuOpenGLNativeClass::kuOpenGLNativeClassImpl
{
public:
	kuOpenGLNativeClassImpl();
	~kuOpenGLNativeClassImpl();

	bool			kuCreateOpenGLWindow(std::string windowName, int hWnd);
	void			kuOpenGLRenderFun();

private:
	GLFWwindow		*	m_GLFWWnd;
	std::thread			m_OpenGLDisplayThd;

	bool				m_fOpenGLDisplay;

	//void			kuOpenGLDisplayFun(GLFWwindow * glfwWnd);
	//bool			kuInitOpenGLModule();

	glm::mat4			m_ProjectionMat;
	glm::mat4			m_ViewMat;

	glm::vec3			m_CameraPos;
	glm::vec3			m_CameraTarget;
	glm::vec3			m_CameraFront;
	glm::vec3			m_WorldUp;
	glm::vec3			m_CameraRight;
	glm::vec3			m_CameraUp;

	kuSphereObject		m_TestSphereObj;
};

kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLNativeClassImpl()
{
	m_fOpenGLDisplay = false;
	m_GLFWWnd		 = NULL;
}

kuOpenGLNativeClass::kuOpenGLNativeClassImpl::~kuOpenGLNativeClassImpl()
{
	m_fOpenGLDisplay = false;

	//if (m_OpenGLDisplayThd.joinable())
	//{
	//	m_OpenGLDisplayThd.join();
	//}
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
	//glfwShowWindow(m_GLFWWnd);
	glfwMakeContextCurrent(m_GLFWWnd);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		//return false;
	}

	#pragma region // window control region //
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(m_GLFWWnd, CursorPositionCallback);
	//glfwSetScrollCallback(m_GLFWWnd, ScrollCallback);
	//glfwSetKeyCallback(m_glWnd, KeyCallback);
	//glfwSetMouseButtonCallback(m_GLFWWnd, MouseButtonCallback);
	#pragma endregion

	// tell GLFW to capture our mouse
	//glfwSetInputMode(m_glWnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glViewport(0, 0, GLWNDWIDTH, GLWNDHEIGHT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	#pragma region // For Camera Test Settings //
	m_CameraPos	   = glm::vec3(-3.0f, 3.0f, 5.0f);		// 0.0f, 1.5f, -5.0f
	m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_CameraFront  = glm::normalize(m_CameraPos - m_CameraTarget);
	m_WorldUp	   = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraRight  = glm::normalize(glm::cross(m_WorldUp, m_CameraFront));
	m_CameraUp	   = glm::cross(m_CameraFront, m_CameraRight);

	m_ProjectionMat = glm::perspective(glm::radians(45.0f), (float)GLWNDWIDTH / (float)GLWNDHEIGHT, 0.1f, 100.0f);
	m_ViewMat		= glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	#pragma endregion

	m_TestSphereObj.SetParameters(0.5f);
	m_TestSphereObj.SetCameraConfiguration(m_ProjectionMat, m_ViewMat, m_CameraFront);
	m_TestSphereObj.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_TestSphereObj.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	if (m_GLFWWnd != NULL)
	{
		//m_fOpenGLDisplay   = true;
		//m_OpenGLDisplayThd = std::thread(&kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLDisplayFun, this, m_GLFWWnd);

		return true;
	}
	else
	{
		return false;
	}
}

//void kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLDisplayFun(GLFWwindow * glfwWnd)
//{
//	while (m_fOpenGLDisplay)
//	{
//		glfwPollEvents();
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//		//std::cout << "Display thread." << std::endl;
//
//		glfwSwapBuffers(glfwWnd);
//	}
//}

void kuOpenGLNativeClass::kuOpenGLNativeClassImpl::kuOpenGLRenderFun()
{
	glfwPollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//std::cout << "Display thread." << std::endl;

	m_TestSphereObj.Draw();

	glfwSwapBuffers(m_GLFWWnd);
}
#pragma endregion

#pragma region // kuOpenGLNativeClass //
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
	return pimpl->kuOpenGLRenderFun();
}
#pragma endregion
