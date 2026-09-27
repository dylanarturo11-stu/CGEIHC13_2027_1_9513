/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh_tn.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList; //solo recibe xyz
std::vector<MeshColor*> meshListColor; // recibe xyz rgb
std::vector<MeshModel*> meshListModel; // recibe xyz uv nx ny nz
std::vector<Shader> shaderList;

Camera camera;
//Lista de Modelos a importar
Model Rover_M;
//Lista de Modelos a importar (ROVER)
Model baseBrazo;
Model extBrazo2;
Model roverCuerpo;
Model extBrazo1;
Model basePinza;
Model pinza;
Model baseRuedaFDer;
Model ejeRuedaFDer;
Model llantaRuedaFDer;
Model brazoRuedaFIzq;
Model ejeRuedaFIzq;
Model brazoRuedaCDer;
Model brazoRuedaTDer;
Model llantaRuedaCDer;

//Lista de Modelos a importar (HOLOCRON)
Model nucleoHolocron;
Model piramideFSI;
Model piramideFSD;
Model piramideFID;
Model piramideFII;
Model piramidePID;
Model piramidePII;
Model piramidePSI;
Model piramidePSD;


//Lista de Modelos a importar (Satelite)
Model antenaSatelite;
Model cuerpoSatelite;
Model panelDerSatelite;
Model panelIzqSatelite;

//Lista de Skybox a crear
Skybox skybox;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	MeshModel *obj1 = new MeshModel();
	obj1->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj1);

	MeshModel *obj2 = new MeshModel();
	obj2->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj2);

	MeshModel *obj3 = new MeshModel();
	obj3->CreateMeshModel(floorVertices, floorIndices, 32, 6);
	meshListModel.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);
	//Cargar modelos
	Rover_M = Model();
	Rover_M.LoadModel("Models/RoverModificado.obj");
	//Cargar modelos
	baseBrazo = Model();
	baseBrazo.LoadModel("Models/baseBrazo.obj");

	extBrazo2 = Model();
	extBrazo2.LoadModel("Models/extBrazo2.obj");

	roverCuerpo = Model();
	roverCuerpo.LoadModel("Models/roverCuerpo.obj");

	extBrazo1 = Model();
	extBrazo1.LoadModel("Models/extBrazo1.obj");

	basePinza = Model();
	basePinza.LoadModel("Models/basePinza.obj");

	pinza = Model();
	pinza.LoadModel("Models/pinza.obj");

	baseRuedaFDer = Model();
	baseRuedaFDer.LoadModel("Models/baseRuedaFDer.obj");

	ejeRuedaFDer = Model();
	ejeRuedaFDer.LoadModel("Models/ejeRuedaFDer.obj");

	llantaRuedaFDer = Model();
	llantaRuedaFDer.LoadModel("Models/llantaRuedaFDer.obj");

	brazoRuedaFIzq = Model();
	brazoRuedaFIzq.LoadModel("Models/brazoRuedaFIzq.obj");

	ejeRuedaFIzq = Model();
	ejeRuedaFIzq.LoadModel("Models/ejeRuedaFIzq.obj");

	brazoRuedaCDer = Model();
	brazoRuedaCDer.LoadModel("Models/brazoRuedaCDer.obj");

	brazoRuedaTDer = Model();
	brazoRuedaTDer.LoadModel("Models/brazoRuedaTDer.obj");

	llantaRuedaCDer = Model();
	llantaRuedaCDer.LoadModel("Models/llantaRuedaCDer.obj");


	//CARGA MODELOS HOLOCRON

	//Cargar modelos
	nucleoHolocron = Model();
	nucleoHolocron.LoadModel("Models/nucleoHolocron.obj");

	piramideFSI = Model();
	piramideFSI.LoadModel("Models/piramideFSI.obj");

	piramideFSD = Model();
	piramideFSD.LoadModel("Models/piramideFSD.obj");

	piramideFID = Model();
	piramideFID.LoadModel("Models/piramideFID.obj");

	piramideFII = Model();
	piramideFII.LoadModel("Models/piramideFII.obj");

	piramidePID = Model();
	piramidePID.LoadModel("Models/piramidePID.obj");

	piramidePII = Model();
	piramidePII.LoadModel("Models/piramidePII.obj");

	piramidePSI = Model();
	piramidePSI.LoadModel("Models/piramidePSI.obj");

	piramidePSD = Model();
	piramidePSD.LoadModel("Models/piramidePSD.obj");


	//Cargar modelos SATELITE
	antenaSatelite = Model();
	antenaSatelite.LoadModel("Models/antenaSatelite.obj");

	cuerpoSatelite = Model();
	cuerpoSatelite.LoadModel("Models/cuerpoSatelite.obj");

	panelDerSatelite = Model();
	panelDerSatelite.LoadModel("Models/panelDerSatelite.obj");

	panelIzqSatelite = Model();
	panelIzqSatelite.LoadModel("Models/panelIzqSatelite.obj");


	//Crear Skybox con sus 6 texturas
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0, uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelaux2(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 ejeDiagonal(0.0);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshListModel[2]->RenderMeshModel();

		//*****------------*INICIA DIBUJO Satelite*-------------------*****///////

		/*
		Model antenaSatelite;
		Model cuerpoSatelite;
		Model panelDerSatelite;
		Model panelIzqSatelite;
		*/

		//cuerpo Principal

		color = glm::vec3(1.0f, 0.0f, 0.0f); //modelo de gris

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion19()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion20()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion21()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		modelaux2 = model;
		//modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoSatelite.RenderModel();

		//**************PANELES***************/////////////////

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.047f, 0.0f, -0.05f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion22()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		panelDerSatelite.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.05f, 0.0f, -0.05f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion23()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		panelIzqSatelite.RenderModel();

		//**************ANTENA***************/////////////////

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.135f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion24()), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antenaSatelite.RenderModel();



		//*****------------*INICIA DIBUJO HOLOCRON*-------------------*****///////
		/*
		Model nucleoHolocron;
		Model piramideFSI;
		Model piramideFSD;
		Model piramideFID;
		Model piramideFII;
		Model piramidePID;
		Model piramidePII;
		Model piramidePSI;
		Model piramidePSD;
		*/

		//NUCLEO

		color = glm::vec3(0.6f, 0.6f, 0.6f); //modelo de gris

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 6.0f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		//modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		nucleoHolocron.RenderModel();


		//************PIRAMIDES CARA FRONTAL**********************S///////////////

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(-1.0f, 1.0f, -1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion11()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(-3.9f, 3.8f, -3.9f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramideFSI.RenderModel();

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(-1.0f, 1.0f, 1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion12()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(-3.85f, 3.9f, 3.85f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramideFSD.RenderModel();

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(-1.0f, -1.0f, 1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion13()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(-3.85f, -3.9f, 3.85f));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramideFID.RenderModel();

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion14()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(-3.85f, -3.9f, -3.85f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramideFII.RenderModel();

		//************PIRAMIDES CARA FRONTAL**********************S///////////////

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(1.0f, 1.0f, -1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion15()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(4.0f, 3.9f, -4.0f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramidePSI.RenderModel();

		model = modelaux;

		// Vector hacia la esquina (ejemplo para Frontal-Superior-Derecho)
		ejeDiagonal = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion16()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(3.85f, 3.9f, 3.85f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramidePSD.RenderModel();

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(1.0f, -1.0f, 1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion17()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(3.85f, -3.9f, 3.85f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramidePID.RenderModel();

		model = modelaux;
		ejeDiagonal = glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f));
		// Rotamos sobre el vector diagonal arbitrario
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion18()), ejeDiagonal);
		model = glm::translate(model, glm::vec3(3.85f, -3.9f, -3.85f));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piramidePII.RenderModel();

		//*****------------*INICIA DIBUJO DE ROVER*-------------------*****///////
		/*
		Model baseBrazo;
		Model extBrazo2;
		Model roverCuerpo;
		Model extBrazo1;
		Model basePinza;
		Model pinza;
		Model baseRuedaFDer;
		Model ejeRuedaFDer;
		Model llantaRuedaFDer;
		Model brazoRuedaFIzq;
		Model ejeRuedaFIzq;
		Model brazoRuedaCDer;
		Model brazoRuedaTDer;
		Model llantaRuedaCDer;	
		*/

		//Modelo Inicial
		color = glm::vec3(0.0f, 0.0f, 1.0f); //modelo de color azul
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		//modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		roverCuerpo.RenderModel();//modificar por el modelo de solo cuerpo del Rover, para que se pueda separar el brazo y las llantas
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		//En sesión se separara una parte del modelo y se unirá por jeraquía al cuerpo
		
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//*****************PARTES PARA EL BRAZO*****************************//

		//base

		model = modelaux;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-2.6f, 1.2f, 1.2f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		baseBrazo.RenderModel();

		//extremidad1

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		extBrazo1.RenderModel();

		//extremidad2

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.4f, 2.7f, 0.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		extBrazo2.RenderModel();
		
		//base pinza

		model = modelaux;
		model = glm::translate(model, glm::vec3(3.0f, 2.9f, -0.1f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		basePinza.RenderModel();

		//pinza

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.45f, 0.4f, 0.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinza.RenderModel();

		//*****************PARTES rueda frontal IZQ*****************************//
		//brazo principal

		model = modelaux2;
		model = glm::translate(model, glm::vec3(-2.0f, 1.1f, 3.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaFIzq.RenderModel();

		//L de rueda

		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.45f, -1.1f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ejeRuedaFIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.25f, -1.5f, 0.7f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaFDer.RenderModel();

		//*****************PARTES rueda frontal Der*****************************//

		model = modelaux2;
		model = glm::translate(model, glm::vec3(-2.0f, 1.1f, -3.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		baseRuedaFDer.RenderModel();

		//L de rueda

		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.45f, -1.1f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ejeRuedaFDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.25f, -1.5f, -0.7f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaFDer.RenderModel();

		//

		//*****************PARTES rueda central Der*****************************//

		model = modelaux2;
		model = glm::translate(model, glm::vec3(2.7f, 0.3f, -3.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaCDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -2.0f, -1.2f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda trasera Der*****************************//

		model = modelaux2;
		model = glm::translate(model, glm::vec3(3.7f, 0.3f, -3.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaTDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.3f, -2.0f, -1.2f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda central Izq*****************************//

		model = modelaux2;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-3.7f, 0.3f, -3.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaCDer.RenderModel();
		
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -2.0f, -1.2f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda trasera Izq*****************************//

		model = modelaux2;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.7f, 0.3f, -3.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaTDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.3f, -2.0f, -1.2f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();
	

		//Siguientes modelos
		/* Ejercicio:
		1.- Separar las llantas
		2.- Hacer que al presionar una tecla cada pata de rueda pueda rotar un máximo de 45° "hacia adelante y hacia atrás"
		*/

		//	Llanta delantera derecha
		modelaux = model;

		//	Llanta delantera izquierda
		modelaux = model;


		//Llanta media derecha
		modelaux = model;	
		
		// Llanta media izquierda
		modelaux = model;

		//Llanta trasera derecha
		modelaux = model;

		//	Llanta trasera izquierda
		modelaux = model;


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
