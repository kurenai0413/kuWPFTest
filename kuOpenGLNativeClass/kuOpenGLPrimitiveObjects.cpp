#include "kuOpenGLPrimitiveObjects.h"

#define pi			3.1415926
#define VertexSize	6			// 3 for position and 3 for normal

const GLchar * vertexShaderSource =
"#version 410 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 normal;\n"
"in vec3 color;\n"
"out vec3 vertexColor;\n"
"out vec3 vertexNormal;\n"
"out vec3 vertexPosition;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view * model * vec4(position, 1.0);\n"
"vertexNormal = mat3(transpose(inverse(model))) * normal;\n"
"vertexPosition = vec3(model * vec4(position, 1.0f));\n"
"vertexColor = color;\n"
"}\0";

const GLchar * fragmentShaderSource =
"#version 410 core\n"
"in vec3 vertexColor;\n"
"in vec3 vertexPosition;\n"
"in vec3 vertexNormal;\n"
"out vec4 outColor;\n"
"uniform vec3 cameraPos;\n"
"uniform vec4 objectColor;\n"
"void main()\n"
"{\n"
"vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);\n"
"vec3 lightPos = cameraPos;\n"
"vec3 objColor = vec3(objectColor.r, objectColor.g, objectColor.b);\n"
// Ambient
"float ambientStrenth = 0.1f;\n"
"vec3 ambient = ambientStrenth * lightColor;\n"
// Diffuse
"vec3 norm = normalize(vertexNormal);\n"
"vec3 lightDir = normalize(lightPos - vertexPosition);\n"
"float diff = max(dot(norm, lightDir), 0.0f);\n"
"vec3 diffuse = diff * lightColor;\n"
"outColor = vec4((ambient + diffuse) * objColor, objectColor.a);\n"
"}\n";

using namespace kuGLModule;

void kuGLPrimitiveObject::SetCameraConfiguration(glm::mat4 projectionMat, glm::mat4 viewMat, glm::vec3 cameraPos)
{
	m_Shader.Use();

	GLuint viewMatLoc, projectionMatLoc, cameraPosLoc;
	viewMatLoc = glGetUniformLocation(m_Shader.GetShaderProgramID(), "view");
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	projectionMatLoc = glGetUniformLocation(m_Shader.GetShaderProgramID(), "projection");
	glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
	cameraPosLoc = glGetUniformLocation(m_Shader.GetShaderProgramID(), "cameraPos");
	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraPos));
}

void kuGLPrimitiveObject::SetPosition(glm::vec3 pos)
{
	m_ModelMat = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f,
						   pos.x, pos.y, pos.z, 1.0);

	UpdateModelMat();
}

void kuGLPrimitiveObject::RotateToVec(glm::vec3 newUpVec)
{
	glm::vec3 start = glm::normalize(m_UpVector);
	glm::vec3 dest  = glm::normalize(newUpVec);
	glm::vec3 rotationAxis;

	glm::quat rotationQuat;

	float cosTheta = glm::dot(start, dest);

	if (cosTheta < -1 + 0.001f)
	{
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);

		if (glm::length2(rotationAxis) < 0.01f)
			rotationAxis = glm::normalize(rotationAxis);

		rotationQuat = glm::quat(glm::radians(180.0f), rotationAxis);
	}
	else
	{
		rotationAxis = glm::cross(start, dest);
		float s = sqrt((1 + cosTheta) * 2);
		float invs = 1 / s;

		rotationQuat = glm::quat(0.5f* s,
								 rotationAxis.x * invs,
								 rotationAxis.y * invs,
								 rotationAxis.z * invs);
	}

	m_ModelMat *= glm::toMat4(rotationQuat);
	m_UpVector = newUpVec;
	UpdateModelMat();
}

void kuGLPrimitiveObject::SetColor(float R, float G, float B, float alpha)
{
	m_Shader.Use();
	GLuint objectColorLoc = glGetUniformLocation(m_Shader.GetShaderProgramID(), "objectColor");
	glUniform4fv(objectColorLoc, 1, glm::value_ptr(glm::vec4(R, G, B, alpha)));
}

GLuint kuGLPrimitiveObject::GetShaderProgramID()
{
	return m_Shader.GetShaderProgramID();
}

void kuGLPrimitiveObject::CreateRenderBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(GLfloat), &m_Vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void kuGLPrimitiveObject::UpdateModelMat()
{
	m_Shader.Use();
	GLuint modelMatLoc = glGetUniformLocation(m_Shader.GetShaderProgramID(), "model");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(m_ModelMat));
}

#pragma region // Cylinder object //
kuCylinderObject::kuCylinderObject()
{

}

kuCylinderObject::kuCylinderObject(float radius, float length)
{
	SetParameters(radius, length);
}

kuCylinderObject::~kuCylinderObject()
{

}

void kuCylinderObject::SetParameters(float radius, float length)
{
	m_Radius = radius;
	m_Length = length;
	m_VerticesNum = 2 * (m_DivisionNum + 1);

	CreateModel();
	CreateRenderBuffers();

	m_Shader.CompileShaders(vertexShaderSource, fragmentShaderSource);

	m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void kuCylinderObject::Draw()
{
	m_Shader.Use();	
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLE_STRIP, m_VerticesNum, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLE_FAN, m_DivisionNum + 2, GL_UNSIGNED_INT, (GLvoid*)((m_VerticesNum) * sizeof(int)));
	glDrawElements(GL_TRIANGLE_FAN, m_DivisionNum + 2, GL_UNSIGNED_INT, (GLvoid*)((m_VerticesNum + m_DivisionNum + 2) * sizeof(int)));
	glBindVertexArray(0);
}

void kuCylinderObject::CreateModel()
{
	if (m_Vertices.size() != 0)
		m_Vertices.clear();

	if (m_Indices.size() != 0)
		m_Indices.clear();

	#pragma region // Generate top and bottom vertices //
	std::vector<GLfloat> verticesTop;
	std::vector<GLfloat> verticesBottom;

	for (int i = 0; i <= m_DivisionNum; i++)
	{
		float	theta  = -((float)360.0f / (float)m_DivisionNum) * i;
		float	cosVal = (float)cos(theta * pi / 180);
		float	sinVal = (float)sin(theta * pi / 180);

		// Top vertices positions
		verticesTop.push_back(m_Radius * cosVal);
		verticesTop.push_back(0.5f * m_Length);
		verticesTop.push_back(m_Radius * sinVal);

		// Bottom vertex positions
		verticesBottom.push_back(m_Radius * cosVal);
		verticesBottom.push_back(-0.5f * m_Length);
		verticesBottom.push_back(m_Radius * sinVal);
	}
	#pragma endregion

	#pragma region // Set side faces vertices and indices: 0 ~ (2 * (m_DivisionNum + 1) - 1) //
	// Side triangle strip vertices.
	for (int i = 0; i <= m_DivisionNum; i++)
	{
		// Top circle vertex
		m_Vertices.push_back(verticesTop[3 * i]);
		m_Vertices.push_back(verticesTop[3 * i + 1]);
		m_Vertices.push_back(verticesTop[3 * i + 2]);
		// Top circle normal
		m_Vertices.push_back(verticesTop[3 * i]);
		m_Vertices.push_back(0);
		m_Vertices.push_back(verticesTop[3 * i + 2]);

		// Index
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

		// Bottom circle vertex
		m_Vertices.push_back(verticesBottom[3 * i]);
		m_Vertices.push_back(verticesBottom[3 * i + 1]);
		m_Vertices.push_back(verticesBottom[3 * i + 2]);
		// Bottom circle normal
		m_Vertices.push_back(verticesBottom[3 * i]);
		m_Vertices.push_back(0);
		m_Vertices.push_back(verticesTop[3 * i + 2]);
	
		// Index
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
	}
	#pragma endregion

	#pragma region // Set top face vertices and indices: 2 * (m_DivisionNum + 1) ~ 2 * (m_DivisionNum + 1) + (m_DivisionNum + 2) - 1 //
	// Top center
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.5f * m_Length);
	m_Vertices.push_back(0.0f);
	// Top center normal
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);

	// Set top center index
	m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

	int topStride = 2 * (m_DivisionNum + 1) + 1;
	for (int i = 0; i <= m_DivisionNum; i++)
	{
		m_Vertices.push_back(verticesTop[3 * i]);
		m_Vertices.push_back(verticesTop[3 * i + 1]);
		m_Vertices.push_back(verticesTop[3 * i + 2]);

		// Top normal
		m_Vertices.push_back(0.0f);
		m_Vertices.push_back(1.0f);
		m_Vertices.push_back(0.0f);

		// Indices
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
	}
	#pragma endregion

	#pragma region // Set bottom face vertices and indcies: 2 * (m_DivisionNum + 1) + (m_DivisionNum + 2) ~ 2 * (m_DivisionNum + 1) + 2 * (m_DivisionNum + 2) - 1 //
	// Bottom center
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.5f * m_Length);
	m_Vertices.push_back(0.0f);
	// Bottom center normal
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);

	// Set bottom center index
	m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

	for (int i = 0; i <= m_DivisionNum; i++)
	{
		// Bottom vertex
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i)]);
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i) + 1]);
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i) + 2]);

		// Bottom normal
		m_Vertices.push_back(0.0f);
		m_Vertices.push_back(-1.0f);
		m_Vertices.push_back(0.0f);
		
		// Index
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
	}
	#pragma endregion
}
#pragma endregion

#pragma region // Cube object //
kuCubeObject::kuCubeObject()
{

}

kuCubeObject::kuCubeObject(float size)
{
	SetParameters(size);
}

kuCubeObject::~kuCubeObject()
{

}

void kuCubeObject::SetParameters(float size)
{
	m_Size = size;
	m_VerticesNum = 8;

	CreateVertices();
	CreateIndices();
	CreateRenderBuffers();
}

void kuCubeObject::Draw(kuShaderHandler shader)
{

}

void kuCubeObject::CreateVertices()
{

}

void kuCubeObject::CreateIndices()
{

}

void kuCubeObject::CreateRenderBuffers()
{

}
#pragma endregion

#pragma region // Cone object //
kuConeObject::kuConeObject()
{

}

kuConeObject::kuConeObject(float radius, float length)
{
	SetParameters(radius, length);
}

kuConeObject::~kuConeObject()
{

}

void kuConeObject::SetParameters(float radius, float length)
{
	m_Radius = radius;
	m_Length = length;
	m_VerticesNum = 2 * (m_DivisionNum + 1) + 2;		// First 1: circle first = last, + 2: Tip and bottom center

	CreateModel();
	CreateRenderBuffers();

	m_Shader.CompileShaders(vertexShaderSource, fragmentShaderSource);

	m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void kuConeObject::Draw()
{
	m_Shader.Use();
	glBindVertexArray(m_VAO);
	// Render sides
	glDrawElements(GL_TRIANGLE_FAN, m_DivisionNum + 2, GL_UNSIGNED_INT, 0);
	// Render bottom
	glDrawElements(GL_TRIANGLE_STRIP, 2 * (m_DivisionNum + 1), GL_UNSIGNED_INT, (GLvoid*)((m_DivisionNum + 2) * sizeof(int)));
	glBindVertexArray(0);
}

void kuConeObject::CreateModel()
{
	std::vector<GLfloat>	verticesBottom;
	#pragma region // Generate circle vertices //
	for (int i = 0; i <= m_DivisionNum; i++)
	{
		float	theta  = -(float)i * 360.0f / (float)m_DivisionNum;
		float	cosVal =  (float)cos(theta * pi / 180);
		float	sinVal =  (float)sin(theta * pi / 180);

		verticesBottom.push_back(m_Radius * cosVal);			// X
		verticesBottom.push_back(0.0f);							// Y
		verticesBottom.push_back(m_Radius * sinVal);			// Z
	}
	#pragma endregion

	#pragma region // Set bottom face vertices and indcies: 0 ~ (m_DivisionNum + 2) - 1 //
	// Bottom center vertex
	m_Vertices.push_back(0.0f);									// X
	m_Vertices.push_back(0.0f);									// Y
	m_Vertices.push_back(0.0f);									// Z
	// Normal
	m_Vertices.push_back(0.0f);									// X
	m_Vertices.push_back(-1.0f);								// Y
	m_Vertices.push_back(0.0f);									// Z

	m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

	for (int i = 0; i <= m_DivisionNum; i++)
	{
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i)]);			// X
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i) + 1]);		// Y
		m_Vertices.push_back(verticesBottom[3 * (m_DivisionNum - i) + 2]);		// Z
		// Normal
		m_Vertices.push_back(0);
		m_Vertices.push_back(-1.0f);
		m_Vertices.push_back(0);

		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
	}
	#pragma endregion

	#pragma region // Set bottom face vertices and indcies: (m_DivisionNum + 2) ~ (m_DivisionNum + 2) + 2 * (m_DivisionNum + 1) - 1 //
	// Side triangle strip vertices.
	for (int i = 0; i <= m_DivisionNum; i++)
	{
		int firstIdx, secondIdx;
		firstIdx = i;
		if (i == m_DivisionNum)
			secondIdx = 0;
		else
			secondIdx = i + 1;

		glm::vec3 topVertex		= glm::vec3(0.0f, m_Length, 0.0f);
		glm::vec3 bottomVertexA = glm::vec3(verticesBottom[3 * firstIdx], verticesBottom[3 * firstIdx + 1], verticesBottom[3 * firstIdx + 2]);
		glm::vec3 bottomVertexB = glm::vec3(verticesBottom[3 * secondIdx], verticesBottom[3 * secondIdx + 1], verticesBottom[3 * secondIdx + 2]);

		glm::vec3 topNormalFace = glm::cross(glm::vec3(bottomVertexA - topVertex), glm::vec3(bottomVertexB - topVertex));
		glm::vec3 topNormal		= glm::cross(glm::vec3(bottomVertexA - topVertex), topNormalFace);

		// Top circle vertex
		m_Vertices.push_back(0.0f);
		m_Vertices.push_back(m_Length);
		m_Vertices.push_back(0.0f);
		// Top circle normal
		m_Vertices.push_back(topNormal.x);
		m_Vertices.push_back(topNormal.y);
		m_Vertices.push_back(topNormal.z);

		// Index
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

		// Bottom circle vertex
		m_Vertices.push_back(verticesBottom[3 * i]);
		m_Vertices.push_back(verticesBottom[3 * i + 1]);
		m_Vertices.push_back(verticesBottom[3 * i + 2]);
		// Bottom circle normal
		m_Vertices.push_back(verticesBottom[3 * i]);
		m_Vertices.push_back(0);
		m_Vertices.push_back(verticesBottom[3 * i + 2]);

		// Index
		m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
	}
	#pragma endregion
}
#pragma endregion

#pragma region // Sphere object //
kuSphereObject::kuSphereObject()
{

}

kuSphereObject::kuSphereObject(float radius)
{
	SetParameters(radius);
	
	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

kuSphereObject::~kuSphereObject()
{

}

void kuSphereObject::SetParameters(float radius)
{
	m_Radius = radius;

	CreateModel();
	CreateRenderBuffers();

	m_Shader.CompileShaders(vertexShaderSource, fragmentShaderSource);
}

void kuSphereObject::Draw()
{
	m_Shader.Use();
	glBindVertexArray(m_VAO);
	for (int i = 0; i < 2 * m_Level; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 2 * (m_DivisionNum + 1), GL_UNSIGNED_INT, (GLvoid*)(2 * (m_DivisionNum + 1) * i * sizeof(int)));
	}
	glBindVertexArray(0);
}

void kuSphereObject::CreateModel()
{
	#pragma region // Generate sphere vertices //
	std::vector<std::vector<GLfloat>>		verticesStacks;
	verticesStacks.resize(m_Level + 1);
	for (int i = 0; i <= m_Level; i++)
	{	
		float phi	 = ((float)180 / (2.0f * (float)m_Level)) * (float)i;
		float cosPhi = (float)cos(phi * pi / 180.0f);
		float sinPhi = (float)sin(phi * pi / 180.0f);

		for (int j = 0; j <= m_DivisionNum; j++)
		{
			float	theta = ((float)360.0f / (float)m_DivisionNum) * j;
			float	cosTheta = (float)cos(theta * pi / 180);
			float	sinTheta = (float)sin(theta * pi / 180);

			// Vertex position
			verticesStacks[i].push_back(m_Radius * cosPhi * cosTheta);
			verticesStacks[i].push_back(m_Radius * sinPhi);
			verticesStacks[i].push_back(m_Radius * cosPhi * sinTheta);
		}
	}
	#pragma endregion

	#pragma region // Upper half sphere vertices and indices //
	for (int i = 0; i < m_Level; i++)
	{
		for (int j = 0; j <= m_DivisionNum; j++)
		{
			// Push lower circle
			// Vertex position
			m_Vertices.push_back(verticesStacks[i][3 * j]);
			m_Vertices.push_back(verticesStacks[i][3 * j + 1]);
			m_Vertices.push_back(verticesStacks[i][3 * j + 2]);
			// Vertex normal
			m_Vertices.push_back(verticesStacks[i][3 * j]);
			m_Vertices.push_back(verticesStacks[i][3 * j + 1]);
			m_Vertices.push_back(verticesStacks[i][3 * j + 2]);

			m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

			// Push upper circle
			// Vertex position
			m_Vertices.push_back(verticesStacks[i + 1][3 * j]);
			m_Vertices.push_back(verticesStacks[i + 1][3 * j + 1]);
			m_Vertices.push_back(verticesStacks[i + 1][3 * j + 2]);
			// Vertex normal					  
			m_Vertices.push_back(verticesStacks[i + 1][3 * j]);
			m_Vertices.push_back(verticesStacks[i + 1][3 * j + 1]);
			m_Vertices.push_back(verticesStacks[i + 1][3 * j + 2]);

			m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
		}

		for (int j = 0; j <= m_DivisionNum; j++)
		{
			// Push lower circle
			// Vertex position
			m_Vertices.push_back( verticesStacks[i][3 * (m_DivisionNum - j)]);
			m_Vertices.push_back(-verticesStacks[i][3 * (m_DivisionNum - j) + 1]);
			m_Vertices.push_back( verticesStacks[i][3 * (m_DivisionNum - j) + 2]);
			// Vertex normal							
			m_Vertices.push_back( verticesStacks[i][3 * (m_DivisionNum - j)]);
			m_Vertices.push_back(-verticesStacks[i][3 * (m_DivisionNum - j) + 1]);
			m_Vertices.push_back( verticesStacks[i][3 * (m_DivisionNum - j) + 2]);

			m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);

			// Push upper circle
			// Vertex position
			m_Vertices.push_back( verticesStacks[i + 1][3 * (m_DivisionNum - j)]);
			m_Vertices.push_back(-verticesStacks[i + 1][3 * (m_DivisionNum - j) + 1]);
			m_Vertices.push_back( verticesStacks[i + 1][3 * (m_DivisionNum - j) + 2]);
			// Vertex normal					  			
			m_Vertices.push_back( verticesStacks[i + 1][3 * (m_DivisionNum - j)]);
			m_Vertices.push_back(-verticesStacks[i + 1][3 * (m_DivisionNum - j) + 1]);
			m_Vertices.push_back( verticesStacks[i + 1][3 * (m_DivisionNum - j) + 2]);

			m_Indices.push_back((int)m_Vertices.size() / VertexSize - 1);
		}
	}
	#pragma endregion
}
#pragma endregion

#pragma region // Arraw object //
kuArrawObject::kuArrawObject()
{

}

kuArrawObject::kuArrawObject(float radius, float length)
{
	SetParameters(radius, length);
}

kuArrawObject::~kuArrawObject()
{

}

void kuArrawObject::SetCameraConfiguration(glm::mat4 projectionMat, glm::mat4 viewMat, glm::vec3 cameraPos)
{
	m_ArrawTip.SetCameraConfiguration(projectionMat, viewMat, cameraPos);
	m_ArrawBody.SetCameraConfiguration(projectionMat, viewMat, cameraPos);
}

void kuArrawObject::SetParameters(float radius, float length)
{
	m_Radius = radius;
	m_Length = length;

	m_ArrawTip.SetParameters(1.5f * m_Radius, 0.2f * m_Length);
	m_ArrawBody.SetParameters(0.85f * m_Radius, 0.8f * m_Length);
	
	m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Position = glm::vec3(0.0f, 0.0f ,0.0f);

	SetPosition(m_Position);
}

void kuArrawObject::SetColor(float R, float G, float B, float alpha)
{
	m_ArrawTip.SetColor(R, G, B, alpha);
	m_ArrawBody.SetColor(R, G, B, alpha);
}

void kuArrawObject::SetPosition(glm::vec3 pos)
{
	m_Position	   = pos;

	m_TipPosition  = pos + 0.3f * m_UpVector;
	m_BodyPosition = pos - 0.1f * m_UpVector;

	m_ArrawTip.SetPosition(m_TipPosition);
	m_ArrawBody.SetPosition(m_BodyPosition);
}

void kuArrawObject::RotateToVec(glm::vec3 newUpVec)
{
	m_UpVector = newUpVec;
	SetPosition(m_Position);

	m_ArrawTip.RotateToVec(newUpVec);
	m_ArrawBody.RotateToVec(newUpVec);
}

void kuArrawObject::Draw()
{
	m_ArrawTip.Draw();
	m_ArrawBody.Draw();
}
#pragma endregion

#pragma region // Coordinate axes object //
kuCoordinateAxesObject::kuCoordinateAxesObject()
{
	m_Axes[0].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

kuCoordinateAxesObject::kuCoordinateAxesObject(float scale)
{
	SetParameters(scale);
}

kuCoordinateAxesObject::~kuCoordinateAxesObject()
{
}

void kuCoordinateAxesObject::SetCameraConfiguration(glm::mat4 projectionMat, glm::mat4 viewMat, glm::vec3 cameraPos)
{
	for (int i = 0; i < 3; i++)
	{
		m_Axes[i].SetCameraConfiguration(projectionMat, viewMat, cameraPos);
	}
	m_Sphere.SetCameraConfiguration(projectionMat, viewMat, cameraPos);
}

void kuCoordinateAxesObject::SetParameters(float scale)
{
	m_Scale		  = scale;

	// Set directions.
	m_UpVector	  = glm::vec3(0.0f, 1.0f, 0.0f);	// Y
	m_RightVector = glm::vec3(1.0f, 0.0f, 0.0f);	// X
	m_FrontVector = glm::vec3(0.0f, 0.0f, 1.0f);	// Z

	// Set default of the position.
	m_Position   = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 3; i++)
	{
		m_Axes[i].SetParameters(m_AxesRadius * scale, scale);
	}

	m_Axes[0].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Axes[1].SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Axes[2].SetColor(0.0f, 0.0f, 1.0f, 1.0f);

	m_Sphere.SetParameters(m_SphereRadius * scale);
	m_Sphere.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	SetPosition(m_Position);
}

void kuCoordinateAxesObject::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
	m_AxesPos[0] = m_Position + glm::vec3(0.5f * m_Scale, 0.0f, 0.0f) * m_RightVector;	// X
	m_AxesPos[1] = m_Position + glm::vec3(0.0f, 0.5f * m_Scale, 0.0f) * m_UpVector;		// Y
	m_AxesPos[2] = m_Position + glm::vec3(0.0f, 0.0f, 0.5f * m_Scale) * m_FrontVector;	// Z
	
	for (int i = 0; i < 3; i++)
	{
		m_Axes[i].SetPosition(m_AxesPos[i]);
	}

	m_Axes[0].RotateToVec(m_RightVector);		// X;
	m_Axes[1].RotateToVec(m_UpVector);			// Y;
	m_Axes[2].RotateToVec(m_FrontVector);		// Z;

	m_Sphere.SetPosition(m_Position);
}

void kuCoordinateAxesObject::RotateToVec(glm::vec3 newUpVec)
{

}

void kuCoordinateAxesObject::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		m_Axes[i].Draw();
	}
 	m_Sphere.Draw();
}
#pragma endregion


