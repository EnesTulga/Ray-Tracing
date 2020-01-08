#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
GLFWwindow* window;
unsigned int shader;
unsigned int width = 640;
unsigned int height = 480;
float cameraPosition[3] = {0,0,-902};
float eyePosition[3] = { 0,0,-1002};
float lightPosition[3] = { 0,5, 0 };
float cameraAngles[3] = { 0,0, 0 };
float spheres[8] = {0,0,10,3, 0,-11,10,7 };	// (x_Position, y_Position, z_Position, Radius)
GLubyte* PixelBuffer = new GLubyte[0];
bool pressing[512];
bool sphereAnim = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		pressing[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		pressing[key] = false;
	}
	
}

void handleCallBacks() {
	if (pressing[GLFW_KEY_S]) {			//	Decreasing Y Position of Light	: S
		lightPosition[1] -= 0.4f;
	}
	else if (pressing[GLFW_KEY_W]) {	//	Increasing Y Position of Light	: W
		lightPosition[1] += 0.4f;
	}
	if (pressing[GLFW_KEY_D]) {			//	Decreasing X Position of Light	: D
		lightPosition[0] += 0.4f;
	}
	else if (pressing[GLFW_KEY_A]) {	//	Increasing X Position of Light	: A
		lightPosition[0] -= 0.4f;
	}
	if (pressing[GLFW_KEY_Q]) {			//	Decreasing Z Position of Light	: Q
		lightPosition[2] -= 0.4f;
	}
	else if (pressing[GLFW_KEY_E]) {	//	Increasing Z Position of Light	: E
		lightPosition[2] += 0.4f;
	}
	if (pressing[GLFW_KEY_RIGHT]) {		//	Increasing X Position of View	: Right Arrow
		cameraPosition[0] += 0.4f;
		eyePosition[0] += 0.4f;
	}
	else if (pressing[GLFW_KEY_LEFT]) {	//	Decreasing X Position of View	: Left Arrow
		cameraPosition[0] -= 0.4f;
		eyePosition[0] -= 0.4f;
	}
	if (pressing[GLFW_KEY_UP]) {		//	Increasing Y Position of View	: Up Arrow
		cameraPosition[1] += 0.4f;
		eyePosition[1] += 0.4f;
	}
	else if (pressing[GLFW_KEY_DOWN]) {	//	Decreasing Y Position of View	: Down Arrow
		cameraPosition[1] -= 0.4f;
		eyePosition[1] -= 0.4f;
	}
	if (pressing[GLFW_KEY_T]) {			//	Increasing Z Position of View	: T
		cameraPosition[2] += 4;
		eyePosition[2] += 4;
	}
	else if (pressing[GLFW_KEY_R]) {	//	Decreasing Z Position of View	: R
		cameraPosition[2] -= 4;
		eyePosition[2] -= 4;
	}

	// For rotating camera in Z Axis.
	/*if (pressing[GLFW_KEY_K]) {
		cameraAngles[2] += 0.4;
	}
	else if (pressing[GLFW_KEY_J]) {
		cameraAngles[2] -= 0.4;
	}*/
}

// For Handling Compiling Shaders
static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	return id;
}

// For Handling Linking Shaders to Main Program
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
void handleDisplay(GLFWwindow* window)
{

	//****	SPHERE GROWING ANIMATION	****
	if (!sphereAnim) {
		spheres[3] += 0.01f;
		if (spheres[3] > 4) {
			spheres[3] = 4;
			sphereAnim = true;
		}
	}
	else {
		spheres[3] -= 0.01f;
		if (spheres[3] < 3) {
			spheres[3] = 3;
			sphereAnim = false;
		}
	}
	//*****************************************


	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader);	// Using Shader

	// Sending Data Sets to Shader
	GLint colorRampUniformLocation = glGetUniformLocation(shader, "cameraPosition");
	glUniform1fv(colorRampUniformLocation, 3, cameraPosition);
	colorRampUniformLocation = glGetUniformLocation(shader, "eyePosition");
	glUniform1fv(colorRampUniformLocation, 3, eyePosition);
	colorRampUniformLocation = glGetUniformLocation(shader, "lightPosition");
	glUniform1fv(colorRampUniformLocation, 3, lightPosition);
	colorRampUniformLocation = glGetUniformLocation(shader, "cameraAngles");
	glUniform1fv(colorRampUniformLocation, 3, cameraAngles);
	colorRampUniformLocation = glGetUniformLocation(shader, "spheres");
	glUniform1fv(colorRampUniformLocation, 8, spheres);

	// Drawing every pixel.
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);

	glfwSwapBuffers(window);
}
int main(void)
{
	
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(640, 480, "Basic Ray Tracing", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error occured while defining GLEW." << std::endl;
	}

	//	Empty Vertex Shader
	std::string vertexShader =
		"#version 410 core\n"
		"void main()\n"
		"{\n"
		"}\n";
	//	All Fragment Shader Code that makes detection of Ray Collision with Spheres and calculation of Light Calculations.
	std::string fragmentShader =
		"#version 410 core\n"
		"uniform float cameraPosition[3];\n"
		"uniform float eyePosition[3];\n"
		"uniform float lightPosition[3];\n"
		"uniform float spheres[8];\n"
		"uniform float cameraAngles[3];\n"
		"out vec4 fragmentColor;\n"
		"\n"
		"vec4 returnCollision(vec3 rayPoint, vec3 Yon, int passingObjectIndex){\n"
		"	float realT = 0;\n"
		"	vec4 realVec = vec4(0,0,0,-1);\n"
		"	for(int i = 0; i < 8; i += 4){\n"
		"	float a = rayPoint[0] - spheres[i];\n"
		"	float a2 = Yon.x;\n"
		"	float a3 = 2 * a * a2;\n"
		"	a *= a;\n"
		"	a2 *= a2;\n"
		"	float b = rayPoint[1] - spheres[i + 1];\n"
		"	float b2 = Yon.y;\n"
		"	float b3 = 2 * b * b2;\n"
		"	b *= b;\n"
		"	b2 *= b2;\n"
		"	float c = rayPoint[2] - spheres[i + 2];\n"
		"	float c2 = Yon.z;\n"
		"	float c3 = 2 * c * c2;\n"
		"	c *= c;\n"
		"	c2 *= c2;\n"
		"	float t1 = a + b + c - spheres[i + 3] * spheres[i + 3];\n"
		"	float t2 = a2 + b2 + c2;\n"
		"	float t3 = a3 + b3 + c3;\n"
		"	float d = t3 * t3 - 4 * t2 * t1;\n"
		"	float t = 0;\n"
		"	float tt = 0;\n"
		"	if(d < 0)\n"
		"	{\n"
		"		continue;\n"
		"	}\n"
		"	else if(d == 0)\n"
		"	{\n"
		"		t = (-t3 + sqrt(d)) / (2 * t2);\n"
		"		if(t <= 0)\n"
		"		{\n"
		"			continue;\n"
		"		}else{\n"
		"			if(t < realT || realT == 0){\n"
		"			if(i == passingObjectIndex){continue;}\n"
		"				realT = t;\n"
		"				realVec = vec4(vec3(eyePosition[0], eyePosition[1], eyePosition[2]) + t * Yon,float(i));\n"
		"			}\n"
		"		}\n"
		"	}else{\n"
		"		t = (-t3 + sqrt(d)) / (2 * t2);\n"
		"		tt = (-t3 - sqrt(d)) / (2 * t2);\n"
		"		if(t > 0 && (t < tt || tt <= 0)){\n"
		"			if(t < realT || realT == 0){\n"
		"			if(i == passingObjectIndex){continue;}\n"
		"				realT = t;\n"
		"				realVec = vec4(vec3(eyePosition[0], eyePosition[1], eyePosition[2]) + t * Yon,float(i));\n"
		"			}\n"
		"		}\n"
		"		if(tt > 0 && (tt < t || t <= 0)){\n"
		"			if(t < realT || realT == 0){\n"
		"			if(i == passingObjectIndex){continue;}\n"
		"				realT = t;\n"
		"				realVec = vec4(vec3(eyePosition[0], eyePosition[1], eyePosition[2]) + t * Yon,float(i));\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"	}\n"
		"	return realVec;\n"
		"}\n"
		"vec4 rayCast()\n"
		"{\n"
		"	float radian = 0.0174532925;\n"
		"	vec4 firsPositionMatris = vec4((cameraPosition[0]) - 1.3f * (320 - gl_FragCoord.x) / 320, (cameraPosition[1]) - (240 - gl_FragCoord.y) / 240, cameraPosition[2], 1);\n"
		"	vec4 gecici = firsPositionMatris;\n"
		"   mat4 translationMatris = mat4(1,0,0,0,0,1,0,0,0,0,1,0,-firsPositionMatris.x,-firsPositionMatris.y,-firsPositionMatris.z,1);\n"
		"	gecici *= translationMatris;\n"
		"	mat4 rotatingMatris = mat4(cos(radian * cameraAngles[2]), sin(radian * cameraAngles[2]), 0, 0, -sin(radian * cameraAngles[2]), cos(radian * cameraAngles[2]), 0, 0, 0,0,1,0,0,0,0,1);\n"
		"	gecici *= rotatingMatris;\n"
		"   translationMatris = mat4(1,0,0,0,0,1,0,0,0,0,1,0,firsPositionMatris.x,firsPositionMatris.y,firsPositionMatris.z,1);\n"
		"	gecici *= translationMatris;\n"
		"	vec4 rayPointt = rotatingMatris * firsPositionMatris;\n"
		"	vec3 rayPoint = vec3(rayPointt.x, rayPointt.y, rayPointt.z);\n"
		"	vec3 Yon = normalize(rayPoint - vec3(eyePosition[0],eyePosition[1] , eyePosition[2]));\n"
		"	vec4 sonuc = returnCollision(vec3(eyePosition[0],eyePosition[1],eyePosition[2]), Yon, -1);\n"
		"	vec4 Clr = vec4(1,1,1,1);\n"
		"	if(sonuc.w < 0){\n"
		"		return vec4(0,0,0,1);\n"
		"	}\n"
		"	else{\n"
		"		rayPoint = vec3(sonuc.x,sonuc.y,sonuc.z);\n"
		"		Yon = normalize(vec3(lightPosition[0],lightPosition[1] , lightPosition[2]) - rayPoint);\n"
		"		vec3 Yon2 = normalize(rayPoint - vec3(spheres[int(sonuc.w)], spheres[int(sonuc.w) + 1], spheres[int(sonuc.w) + 2]));\n"
		"		sonuc = returnCollision(rayPoint, Yon, int(sonuc.w));\n"
		"		float dt = dot(Yon, Yon2);\n"
		"		if(dt > 0){//if(sonuc.w < 0){\n"
		"			//return vec4(1,1,1,1);\n"
		"		if(sonuc.w < 0){\n"
		"			return Clr;\n"
		"		}else{Clr.x /= 2; Clr.y /= 2;Clr.z/=2;return Clr;}\n"
		"		}\n"
		"		else{\n"
		"			//return vec4(0.5f,0.5f,0.5f,1);\n"
		"			Clr = vec4(0.5,0.5,0.5,1);\n"
		"			if(sonuc.w < 0){\n"
		"				return Clr;\n"
		"			}else if(dt <= 0){Clr.x /= 2; Clr.y /= 2;Clr.z/=2;return Clr;}\n"
		"		}\n"
		"	}\n"
		"	return Clr;\n"
		"}\n"
		"void main()\n"
		"{\n"
		"	fragmentColor = rayCast();\n"
		"}\n";

	shader = CreateShader(vertexShader, fragmentShader);
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		handleCallBacks();

		handleDisplay(window);
		
	}
	glfwTerminate();
	return 0;
}

//	Enes Tulga