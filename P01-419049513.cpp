#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <thread>
#include <chrono>
#include <random> 

// Motor aleatorio con semilla basada en hardware (evita la misma secuencia al reiniciar el programa)
std::random_device rd;

// (Motor Mersenne Twister): Es un generador de números pseudoaleatorios de 32 bits. Utiliza el algoritmo Mersenne Twister con un periodo extremadamente largo de 2^{19937}-1
//antes de repetir patron
std::mt19937 gen(rd());

std::uniform_int_distribution<int> distribucion(0, 2); // Genera enteros entre 0 y 2

// Variables de estado para el color activo y el control de tiempo
int ultimoIntervalo = -1;
float colorActual[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;

//LENGUAJE DE SHADER (SOMBRAS) GLSL
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.84f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		
		// ==================== LETRA D (8 Triángulos) ====================
		-0.7f,  0.6f, 0.0f,
		-0.7f,  -0.6f, 0.0f,
		-0.6f,  -0.6f, 0.0f,

		-0.7f,  0.6f, 0.0f,
		-0.6f,  0.6f, 0.0f,
		-0.6f,  -0.6f, 0.0f,

		-0.6f,  0.6f, 0.0f,
		-0.7f,  0.5f, 0.0f,
		-0.3f,  0.3f, 0.0f,

		-0.7f,  0.5f, 0.0f,
		-0.4f,  0.2f, 0.0f,
		-0.3f,  0.3f, 0.0f,

		-0.3f,  0.3f, 0.0f,
		-0.3f, -0.3f, 0.0f,
		-0.4f,  0.2f, 0.0f,

		-0.4f,  0.2f, 0.0f,
		-0.4f, -0.2f, 0.0f,
		-0.3f, -0.3f, 0.0f,

		-0.4f, -0.2f, 0.0f,
		-0.3f, -0.3f, 0.0f,
		-0.6f, -0.6f, 0.0f,

		-0.4f, -0.2f, 0.0f,
		-0.7f, -0.5f, 0.0f,
		-0.6f, -0.6f, 0.0f,

		// ==================== LETRA Y (6 Triángulos) ====================
		-0.2f,  0.6f, 0.0f,
		-0.1f,  0.6f, 0.0f,
		 0.0f,  0.0f, 0.0f,

		-0.2f,  0.6f, 0.0f,
		0.0f,  0.0f, 0.0f,
		-0.1f,  0.0f, 0.0f,

		0.1f,  0.6f, 0.0f,
		0.2f,  0.6f, 0.0f,
		0.1f,  0.0f, 0.0f,

		0.1f,  0.6f, 0.0f,
		0.1f,  0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,

		-0.1f,  0.0f, 0.0f,
		0.1f,  0.0f, 0.0f,
		0.1f, -0.6f, 0.0f,

		-0.1f,  0.0f, 0.0f,
		-0.1f, -0.6f, 0.0f,
		0.1f, -0.6f, 0.0f,

		// ==================== LETRA L (4 Triángulos) ====================
		0.3f,  0.6f, 0.0f,
		0.4f,  0.6f, 0.0f,
		0.3f, -0.5f, 0.0f,

		0.4f,  0.6f, 0.0f,
		0.3f, -0.5f, 0.0f,
		0.4f, -0.5f, 0.0f,

		0.3f, -0.5f, 0.0f,
		0.7f, -0.5f, 0.0f,
		0.3f, -0.6f, 0.0f,

		0.7f, -0.5f, 0.0f,
		0.3f, -0.6f, 0.0f,
		0.7f, -0.6f, 0.0f

	};

	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica

//the Program recibe los datos de theShader

{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	//****  LAS SIGUIENTES 4 LÍNEAS SE COMENTAN EN DADO CASO DE QUE AL USUARIO NO LE FUNCIONE LA VENTANA Y PUEDA CONOCER LA VERSIÓN DE OPENGL QUE TIENE ****/

	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Llamada a las funciones creadas antes del main
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		// Se crea un array de flotantes 3x4 que contiene la combinacion de colores para un fondo rojo, negro y azul
		float colores[3][4] = {
			{ 1.0f, 0.0f, 0.0f, 1.0f }, // Rojo
			{ 0.0f, 1.0f, 0.0f, 1.0f }, // Verde
			{ 0.0f, 0.0f, 1.0f, 1.0f }  // Azul
		};

		// Se invoca a la funcion getTime para obtener el tiempo transcurrido desde el inicio de la ejecucion
		double tiempoActual = glfwGetTime();
		//el valor de último intervalo esta hardcodeado como -1 entrara por primera vez en el arranque, cuando se cumple la condicion el color de fondo se mantiene hasta el
		//siguiente intervalo de 2 segs. Por lo tanto: primer intervalo 0-2, valor intActual 0. Segundo 2-4, valor intActual 1. Tercero 4-6, valor intActual 2, y asi sucesivamente.
		int intervaloActual = static_cast<int>(tiempoActual / 2.0);

		// Solo entra aquí una vez cada 2 segundos
		if (intervaloActual != ultimoIntervalo)
		{
			ultimoIntervalo = intervaloActual; 

			// Seleccionar un índice aleatorio entre 0, 1 y 2
			int indiceRandom = distribucion(gen);

			// Guardar el nuevo color en la variable de estado
			colorActual[0] = colores[indiceRandom][0];
			colorActual[1] = colores[indiceRandom][1];
			colorActual[2] = colores[indiceRandom][2];
			colorActual[3] = colores[indiceRandom][3];
		}

		// En cada frame se aplica el color guardado (sin recalcular aleatorios)
		glClearColor(colorActual[0], colorActual[1], colorActual[2], colorActual[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);


		//los valores de 0 a 15 indican la cantidad de vertices que se procesan en el gpu para generar los triangulos. Para este ejercicio, 15 en total.
		glDrawArrays(GL_TRIANGLES,0,54);
		glBindVertexArray(0);

		glUseProgram(0);


		glfwSwapBuffers(mainWindow);
		 
		//NO ESCRIBIR NINGUNA LÍNEA DESPUÉS DE glfwSwapBuffers(mainWindow); 
	}


	return 0;
}