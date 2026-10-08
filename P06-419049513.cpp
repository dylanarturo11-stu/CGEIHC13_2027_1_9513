/*
Práctica 6: Texturizado
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

#include "Window.h"
#include "Mesh_tn.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList; //solo recibe xyz
std::vector<MeshColor*> meshListColor; // recibe xyz rgb
std::vector<MeshModel*> meshListModel; // recibe xyz uv nx ny nz

std::vector<Shader> shaderList;

Camera camera;

Texture plainTexture;
Texture pisoTexture;
Texture dadoTexture;
Texture holocronTexture;

Model Kitt_M;
Model Llanta_M;
Model Dado_M;
Model Holocron_M;
Model Holocron_M2;
Model avion;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_texture.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_texture.frag";





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

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};



	MeshModel* obj1 = new MeshModel();
	obj1->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj1);

	MeshModel* obj2 = new MeshModel();
	obj2->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj2);

	MeshModel* obj3 = new MeshModel();
	obj3->CreateMeshModel(floorVertices, floorIndices, 32, 6);
	meshListModel.push_back(obj3);

	MeshModel* obj4 = new MeshModel();
	obj4->CreateMeshModel(vegetacionVertices, vegetacionIndices, 64, 12);
	meshListModel.push_back(obj4);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.26f,  0.34f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.49f,	0.34f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.49f,	0.66f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.26f,	0.66f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	1.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

	};

	MeshModel* dado = new MeshModel();
	dado->CreateMeshModel(cubo_vertices, cubo_indices, 192, 36);
	meshListModel.push_back(dado);

}


void CrearHolocron() {
	// =========================================================
	// ÍNDICES DE RENDERIZADO (60 índices para 20 triángulos)
	// =========================================================
	unsigned int holocron_indices[] = {
		// 6 Caras Cuadradas (2 triángulos por cara = 36 índices)
		0, 3, 2,   1, 2, 3,   // 1. Superior (+Y)

		4,  5,  6,    4,  6,  7,   // 2. Frontal (+Z)

		8,  9, 10,    8, 10, 11,   // 3. Derecha (+X)

		12, 13, 14,   12, 14, 15,   // 4. Trasera (-Z)

		16, 17, 18,   16, 18, 19,   // 5. Izquierda (-X)

		20, 21, 22,   20, 22, 23,   // 6. Inferior (-Y)

		// 8 Esquinas Triangulares (1 triángulo por cara = 24 índices)
		24, 25, 26,   // 7. Superior Frontal-Izquierda
		27, 28, 29,   // 8. Superior Frontal-Derecha
		30, 31, 32,   // 9. Superior Trasera-Derecha
		33, 34, 35,   // 10. Superior Trasera-Izquierda
		36, 37, 38,   // 11. Inferior Frontal-Izquierda
		39, 40, 41,   // 12. Inferior Frontal-Derecha
		42, 43, 44,   // 13. Inferior Trasera-Derecha
		45, 46, 47    // 14. Inferior Trasera-Izquierda
	};

	// =========================================================
	// VÉRTICES DESACOUPLADOS (48 vértices * 8 atributos = 384 GLfloat)
	// Formato: X, Y, Z, S, T, NX, NY, NZ
	// =========================================================
	GLfloat holocron_vertices[] = {
		// ---------------------------------------------------------
		// CARAS CUADRADAS
		// ---------------------------------------------------------
		// 1. Cara Superior (+Y) -> Normal (0, 1, 0)
		 0.049649f,  2.440128f, -2.417217f,   0.07f, 1.0f,   0.0f,  1.0f,  0.0f, // V0 (P2)
		 0.051152f,  2.399781f,  2.545043f,   0.07f, 0.87f,   0.0f,  1.0f,  0.0f, // V1 (P3)
		 2.521206f,  2.448241f,  0.063388f,   0.13f, 0.94f,   0.0f,  1.0f,  0.0f, // V2 (P14)
		-2.451372f,  2.421759f,  0.077538f,   0.0f, 0.94f,   0.0f,  1.0f,  0.0f, // V3 (P15)

		// // 2. Cara Frontal (+Z) -> Normal (0, 0, 1)
-2.646786f, -0.139047f,  2.493757f,   0.45f, 0.67f,   0.0f, 0.0f, 1.0f, // V4 (P4: Izquierda -> D1)
-0.140696f, -2.601934f,  2.558561f,   0.56f, 0.58f,   0.0f, 0.0f, 1.0f, // V5 (P8: Abajo     -> C1)
 2.593003f, -0.085222f,  2.505755f,   0.67f, 0.67f,   0.0f, 0.0f, 1.0f, // V6 (P6: Derecha   -> E1)
 0.051152f,  2.399781f,  2.545043f,   0.56f, 0.77f,   0.0f, 0.0f, 1.0f, // V7 (P3: Arriba    -> B1)

		 // 3. Cara Derecha (+X) -> Normal (1, 0, 0)
		  2.593003f, -0.085222f,  2.505755f,   0.72f, 0.69f,   1.0f,  0.0f,  0.0f, // V8 (P6)
		  2.632201f, -2.553892f,  0.007226f,   0.82f, 0.58f,   1.0f,  0.0f,  0.0f, // V9 (P13)
		  2.534944f, -0.061146f, -2.580280f,   0.91f, 0.69f,   1.0f,  0.0f,  0.0f, // V10 (P9)
		  2.521206f,  2.448241f,  0.063388f,   0.82f, 0.80f,   1.0f,  0.0f,  0.0f, // V11 (P14)

		  // 4. Cara Trasera (-Z) -> Normal (0, 0, -1)
		   2.534944f, -0.061146f, -2.580280f,   0.21f, 0.42f,   0.0f,  0.0f, -1.0f, // V12 (P9)
		   0.081432f, -2.513204f, -2.426005f,   0.31f, 0.32f,   0.0f,  0.0f, -1.0f, // V13 (P11)
		  -2.453980f, -0.063388f, -2.477451f,   0.42f, 0.42f,   0.0f,  0.0f, -1.0f, // V14 (P12)
		   0.049649f,  2.440128f, -2.417217f,   0.31f, 0.53f,   0.0f,  0.0f, -1.0f, // V15 (P2)

		   // 5. Cara Izquierda (-X) -> Normal (-1, 0, 0)
		   -2.453980f, -0.063388f, -2.477451f,   0.21f, 0.18f,  -1.0f,  0.0f,  0.0f, // V16 (P12)
		   -2.517274f, -2.579095f,  0.002115f,   0.32f, 0.08f,  -1.0f,  0.0f,  0.0f, // V17 (P0)
		   -2.646786f, -0.139047f,  2.493757f,   0.42f, 0.18f,  -1.0f,  0.0f,  0.0f, // V18 (P4)
		   -2.451372f,  2.421759f,  0.077538f,   0.32f, 0.30f,  -1.0f,  0.0f,  0.0f, // V19 (P15)

		   // 6. Cara Inferior (-Y) -> Normal (0, -1, 0)
		   -2.517274f, -2.579095f,  0.002115f,   0.45f, 0.19f,   0.0f, -1.0f,  0.0f, // V20 (P0)
			0.081432f, -2.513204f, -2.426005f,   0.57f, 0.08f,   0.0f, -1.0f,  0.0f, // V21 (P11)
			2.632201f, -2.553892f,  0.007226f,   0.68f, 0.19f,   0.0f, -1.0f,  0.0f, // V22 (P13)
		   -0.140696f, -2.601934f,  2.558561f,   0.57f, 0.30f,   0.0f, -1.0f,  0.0f, // V23 (P8)

		   // ---------------------------------------------------------
		   // ESQUINAS TRIANGULARES
		   // ---------------------------------------------------------
		   // 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
// 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
// 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
-2.451372f,  2.421759f, 0.077538f,  0.42f, 1.00f,  -0.577f, 0.577f, 0.577f, // V24 (Arriba-Izquierda 3D) -> Punta Derecha UV
-2.646786f, -0.139047f, 2.493757f,  0.32f, 0.88f,  -0.577f, 0.577f, 0.577f, // V25 (Abajo-Punta 3D)       -> Base Texto UV (Centro)
 0.051152f,  2.399781f, 2.545043f,  0.22f, 1.00f,  -0.577f, 0.577f, 0.577f, // V26 (Arriba-Derecha 3D)   -> Punta Izquierda UV

			// 8. Esquina Superior Frontal-Derecha -> Normal (0.577, 0.577, 0.577)
			 0.051152f,  2.399781f,  2.545043f,   0.46f, 0.87f,   0.577f,  0.577f,  0.577f, // V27 (P3)
			 2.593003f, -0.085222f,  2.505755f,   0.68f, 0.87f,   0.577f,  0.577f,  0.577f, // V28 (P6)
			 2.521206f,  2.448241f,  0.063388f,   0.56f, 1.00f,   0.577f,  0.577f,  0.577f, // V29 (P14)

			 // 9. Esquina Superior Trasera-Derecha -> Normal (0.577, 0.577, -0.577)
			  2.521206f,  2.448241f,  0.063388f,   0.72f, 0.87f,   0.577f,  0.577f, -0.577f, // V30 (P14)
			  2.534944f, -0.061146f, -2.580280f,   0.91f, 0.87f,   0.577f,  0.577f, -0.577f, // V31 (P9)
			  0.049649f,  2.440128f, -2.417217f,   0.81f, 1.00f,   0.577f,  0.577f, -0.577f, // V32 (P2)

			  // 10. Esquina Superior Trasera-Izquierda -> Normal (-0.577, 0.577, -0.577)
			   0.049649f,  2.440128f, -2.417217f,   0.00f, 0.65f,  -0.577f,  0.577f, -0.577f, // V33 (P2)
			  -2.453980f, -0.063388f, -2.477451f,   0.14f, 0.65f,  -0.577f,  0.577f, -0.577f, // V34 (P12)
			  -2.451372f,  2.421759f,  0.077538f,   0.06f, 0.78f,  -0.577f,  0.577f, -0.577f, // V35 (P15)

			  // 11. Esquina Inferior Frontal-Izquierda -> Normal (-0.577, -0.577, 0.577)
			  -2.646786f, -0.139047f,  2.493757f,   0.21f, 0.62f,  -0.577f, -0.577f,  0.577f, // V36 (P4)
			  -2.517274f, -2.579095f,  0.002115f,   0.42f, 0.62f,  -0.577f, -0.577f,  0.577f, // V37 (P0)
			  -0.140696f, -2.601934f,  2.558561f,   0.32f, 0.81f,  -0.577f, -0.577f,  0.577f, // V38 (P8)

			  // 12. Esquina Inferior Frontal-Derecha -> Normal (0.577, -0.577, 0.577)
			   2.593003f, -0.085222f,  2.505755f,   0.45f, 0.37f,   0.577f, -0.577f,  0.577f, // V39 (P6)
			  -0.140696f, -2.601934f,  2.558561f,   0.67f, 0.37f,   0.577f, -0.577f,  0.577f, // V40 (P8)
			   2.632201f, -2.553892f,  0.007226f,   0.56f, 0.56f,   0.577f, -0.577f,  0.577f, // V41 (P13)

			   // 13. Esquina Inferior Trasera-Derecha -> Normal (0.577, -0.577, -0.577)
				2.534944f, -0.061146f, -2.580280f,   0.72f, 0.37f,   0.577f, -0.577f, -0.577f, // V42 (P9)
				2.632201f, -2.553892f,  0.007226f,   0.92f, 0.37f,   0.577f, -0.577f, -0.577f, // V43 (P13)
				0.081432f, -2.513204f, -2.426005f,   0.82f, 0.54f,   0.577f, -0.577f, -0.577f, // V44 (P11)

				// 14. Esquina Inferior Trasera-Izquierda -> Normal (-0.577, -0.577, -0.577)
				-2.453980f, -0.063388f, -2.477451f,   0.72f, 0.12f,  -0.577f, -0.577f, -0.577f, // V45 (P12)
				 0.081432f, -2.513204f, -2.426005f,   0.92f, 0.12f,  -0.577f, -0.577f, -0.577f, // V46 (P11)
				-2.517274f, -2.579095f,  0.002115f,   0.81f, 0.28f,  -0.577f, -0.577f, -0.577f  // V47 (P0)
	};

	MeshModel* holocron = new MeshModel();
	// 384 valores GLfloat (48 vértices * 8 atributos) y 60 índices (20 triángulos * 3 vértices)
	holocron->CreateMeshModel(holocron_vertices, holocron_indices, 384, 60);
	meshListModel.push_back(holocron);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CrearHolocron();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado-de-numeros.png");
	dadoTexture.LoadTextureA();
	holocronTexture = Texture("Textures/swLogosV3.png");
	holocronTexture.LoadTextureA();

	Holocron_M = Model();
	Holocron_M.LoadModel("Models/holocron_simple.obj");

	Holocron_M2 = Model();
	Holocron_M2.LoadModel("Models/holocronTX.obj");

	avion = Model();
	avion.LoadModel("Models/avionModelo.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
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
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la información de color de la textura

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshListModel[2]->RenderMeshModel();




		//Dado de Opengl
		//Ejercicio 1: Texturizar su dado con la imagen ya optimizada por ustedes con logos de star wars
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshListModel[4]->RenderMeshModel();

		//Ejercicio 2:Importar el cubo texturizado en el programa de modelado con 
		//la imagen ya optimizada por ustedes

		/*
		//Dado importado
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 3.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado_M.RenderModel();
		*/




		/*Reporte de práctica :

		Ejercicio 1: Crear o modificar el holocron y texturizarlo por medio de código
		Ejercicio 2: Importar el modelo del holocron texturizardo en el programa de modelado
		Ejercicio 3: Importar un modelo de avión con con la textura de la cara del personaje de la imagen del previo:
		Vidrio fonrtal: OJOS
		Frente del avión: Nariz y Sonrisa
		Alas: Logos del universo del personaje

		*/


		//Holocrones
		color = glm::vec3(0.0f, 1.0f, 0.0f);//color que multiplica a la información de color de la textura
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.5f, 4.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		holocronTexture.UseTexture();
		meshListModel[5]->RenderMeshModel();


		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la información de color de la textura
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.5f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Holocron_M.RenderModel();

		//Holocron texturizado star wars

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-14.5f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		Holocron_M2.RenderModel();

		//Avion de Blender

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-24.5f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		avion.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/