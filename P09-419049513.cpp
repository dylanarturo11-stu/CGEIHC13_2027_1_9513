/*
Práctica 7: Iluminación 1 
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

#include "Window.h" //LISTO
#include "Mesh_tn.h" //LISTO
#include "Shader_light.h" //LISTO
#include "Camera.h" //LISTO
#include "Texture.h" //LISTO
#include "Sphere.h"//LISTO
#include"Model.h" //LISTO
#include "Skybox.h" //LISTO

//para iluminación
#include "CommonValues.h" //LISTO
#include "DirectionalLight.h"//LISTO
#include "PointLight.h"//LISTO
#include "SpotLight.h"//LISTO
#include "Material.h"//LISTO
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<MeshModel*> meshListModel; // recibe xyz uv nx ny nz
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
// Añadir Texturas del dado y del holocron
Texture dadoTexture;
Texture holocronTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;


Model Blackhawk_M;
Model Rover_M; 
//Sustituir por sus propios Rovers Con jerarquía

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

//Añadir modelo del avión.
//Model Avion_M;
Model Holocron_M2;
Model avion;
Model starFighter;

//Lista de Modelos a importar (Satelite)
Model antenaSatelite;
Model cuerpoSatelite;
Model panelDerSatelite;
Model panelIzqSatelite;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

// para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];   // Arreglo 1: Verde, Azul, Roja, Blanca
PointLight pointLights2[MAX_POINT_LIGHTS];  // Arreglo 2: Blanca, Verde, Azul, Roja
SpotLight spotLights[MAX_SPOT_LIGHTS];

//variables para animación
bool avanza;

float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
float movCoche = 0.0f;
float movOffset = 0.2f;
float rotLlanta = 0.0;
float rotLlantaInc = 2.0;
bool dirMovimientoCarro = 0;

// Variables para animación del avión (Circuito rectangular con esquinas de 1/4 de círculo)
int estadoAvion = 0;           // Máquina de estados (0 a 7)
float movAvionX = 0.0f;        // Desplazamiento relativo en X
float movAvionZ = 0.0f;        // Desplazamiento relativo en Z
float rotAvionY = 0.0f;        // Ángulo de orientación del avión (Yaw)
float anguloAvion = 0.0f;      // Ángulo theta (0 a 360 grados) para los 4 cuartos de círculo

float velAvionRecto = 0.3f;    // Velocidad en tramos rectos
float velAvionGiro = 1.5f;     // Velocidad angular en las curvas (grados por frame * deltaTime)
float radioCurva = 15.0f;      // Radio (R) de los 1/4 de circunferencia
float tramoLargoZ = 40.0f;     // Longitud de los lados largos (eje Z)
float tramoCortoX = 15.0f;     // Longitud de los lados cortos (eje X)

//Variables para satilete
float movSatX = 0;
float movSatZ = 0;
float anguloSat = 0;
float rotSatX = 0;
float rotSatY = 0;
float rotSatZ = 0;
float rotPanelIzq = 0;
float rotPanelDer = 0;
float rotAntena = 0;
int estadoSatelite = 0;
float velSatGiro = 0.15f;     // Velocidad angular en las curvas (grados por frame * deltaTime)
float radioCurva2 = 15.0f;


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


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
	
	MeshModel *obj1 = new MeshModel();
	obj1->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj1);

	MeshModel *obj2 = new MeshModel();
	obj2->CreateMeshModel(vertices, indices, 32, 12);
	meshListModel.push_back(obj2);

	MeshModel *obj3 = new MeshModel();
	obj3->CreateMeshModel(floorVertices, floorIndices, 32, 6);
	meshListModel.push_back(obj3);

	MeshModel *obj4 = new MeshModel();
	obj4->CreateMeshModel(vegetacionVertices, vegetacionIndices, 64, 12);
	meshListModel.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


void CrearDado() //sustituir con su propio dado, para que tenga la textura de la práctica 6
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

	};	GLfloat cubo_vertices[] = {
			// front (Cara 1 - Verde: "1")
			//x        y      z        S        T         NX     NY     NZ
			-0.5f, -0.5f,  0.5f,   0.484f,  0.356f,     0.0f,  0.0f,  -1.0f,  // (Punto H)
			 0.5f, -0.5f,  0.5f,   0.674f,  0.354f,     0.0f,  0.0f,  -1.0f,  // (Punto N)
			 0.5f,  0.5f,  0.5f,   0.675f,  0.623f,     0.0f,  0.0f,  -1.0f,  // (Punto I)
			-0.5f,  0.5f,  0.5f,   0.481f,  0.622f,     0.0f,  0.0f,  -1.0f,  // (Punto G)

			// right (Cara 2 - Azul: "2")
			//x        y      z        S        T         NX     NY     NZ
			 0.5f, -0.5f,  0.5f,   0.674f,  0.354f,    -1.0f,  0.0f,  0.0f,  // (Punto N)
			 0.5f, -0.5f, -0.5f,   0.865f,  0.356f,    -1.0f,  0.0f,  0.0f,  // (Punto M)
			 0.5f,  0.5f, -0.5f,   0.864f,  0.623f,    -1.0f,  0.0f,  0.0f,  // (Punto L)
			 0.5f,  0.5f,  0.5f,   0.675f,  0.623f,    -1.0f,  0.0f,  0.0f,  // (Punto I)

			 // back (Cara 6 - Amarillo: "6")
			 //x        y      z        S        T         NX     NY     NZ
			 -0.5f, -0.5f, -0.5f,   0.294f,  0.355f,     0.0f,  0.0f,  1.0f,  // (Punto E)
			  0.5f, -0.5f, -0.5f,   0.105f,  0.357f,     0.0f,  0.0f,  1.0f,  // (Punto D)
			  0.5f,  0.5f, -0.5f,   0.105f,  0.624f,     0.0f,  0.0f,  1.0f,  // (Punto C)
			 -0.5f,  0.5f, -0.5f,   0.294f,  0.625f,     0.0f,  0.0f,  1.0f,  // (Punto F)

			 // left (Cara 5 - Morado: "5")
			 //x        y      z        S        T         NX     NY     NZ
			 -0.5f, -0.5f, -0.5f,   0.294f,  0.355f,     1.0f,  0.0f,  0.0f,  // (Punto E)
			 -0.5f, -0.5f,  0.5f,   0.484f,  0.356f,     1.0f,  0.0f,  0.0f,  // (Punto H)
			 -0.5f,  0.5f,  0.5f,   0.481f,  0.622f,     1.0f,  0.0f,  0.0f,  // (Punto G)
			 -0.5f,  0.5f, -0.5f,   0.294f,  0.625f,     1.0f,  0.0f,  0.0f,  // (Punto F)

			 // bottom (Cara 3 - Rosa: "3")
			 //x        y      z        S        T         NX     NY     NZ
			 -0.5f, -0.5f,  0.5f,   0.484f,  0.356f,     0.0f,  1.0f,  0.0f,  // (Punto H)
			  0.5f, -0.5f,  0.5f,   0.674f,  0.354f,     0.0f,  1.0f,  0.0f,  // (Punto N)
			  0.5f, -0.5f, -0.5f,   0.674f,  0.086f,     0.0f,  1.0f,  0.0f,  // (Punto P)
			 -0.5f, -0.5f, -0.5f,   0.482f,  0.088f,     0.0f,  1.0f,  0.0f,  // (Punto O)

			 // UP (Cara 4 - Naranja: "4")
			 //x        y      z        S        T         NX     NY     NZ
			 -0.5f,  0.5f,  0.5f,   0.481f,  0.622f,     0.0f, -1.0f,  0.0f,  // (Punto G)
			  0.5f,  0.5f,  0.5f,   0.675f,  0.623f,     0.0f, -1.0f,  0.0f,  // (Punto I)
			  0.5f,  0.5f, -0.5f,   0.674f,  0.896f,     0.0f, -1.0f,  0.0f,  // (Punto J)
			 -0.5f,  0.5f, -0.5f,   0.482f,  0.895f,     0.0f, -1.0f,  0.0f,  // (Punto K)

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
		 0.049649f,  2.440128f, -2.417217f,   0.07f, 1.0f,   0.0f,  -1.0f,  0.0f, // V0 (P2)
		 0.051152f,  2.399781f,  2.545043f,   0.07f, 0.87f,   0.0f,  -1.0f,  0.0f, // V1 (P3)
		 2.521206f,  2.448241f,  0.063388f,   0.13f, 0.94f,   0.0f,  -1.0f,  0.0f, // V2 (P14)
		-2.451372f,  2.421759f,  0.077538f,   0.0f, 0.94f,   0.0f,  -1.0f,  0.0f, // V3 (P15)

		// // 2. Cara Frontal (+Z) -> Normal (0, 0, 1)
-2.646786f, -0.139047f,  2.493757f,   0.45f, 0.67f,   0.0f, 0.0f, -1.0f, // V4 (P4: Izquierda -> D1)
-0.140696f, -2.601934f,  2.558561f,   0.56f, 0.58f,   0.0f, 0.0f, -1.0f, // V5 (P8: Abajo     -> C1)
 2.593003f, -0.085222f,  2.505755f,   0.67f, 0.67f,   0.0f, 0.0f, -1.0f, // V6 (P6: Derecha   -> E1)
 0.051152f,  2.399781f,  2.545043f,   0.56f, 0.77f,   0.0f, 0.0f, -1.0f, // V7 (P3: Arriba    -> B1)

 // 3. Cara Derecha (+X) -> Normal (1, 0, 0)
  2.593003f, -0.085222f,  2.505755f,   0.72f, 0.69f,   -1.0f,  0.0f,  0.0f, // V8 (P6)
  2.632201f, -2.553892f,  0.007226f,   0.82f, 0.58f,   -1.0f,  0.0f,  0.0f, // V9 (P13)
  2.534944f, -0.061146f, -2.580280f,   0.91f, 0.69f,   -1.0f,  0.0f,  0.0f, // V10 (P9)
  2.521206f,  2.448241f,  0.063388f,   0.82f, 0.80f,   -1.0f,  0.0f,  0.0f, // V11 (P14)

  // 4. Cara Trasera (-Z) -> Normal (0, 0, -1)
   2.534944f, -0.061146f, -2.580280f,   0.21f, 0.42f,   0.0f,  0.0f, 1.0f, // V12 (P9)
   0.081432f, -2.513204f, -2.426005f,   0.31f, 0.32f,   0.0f,  0.0f, 1.0f, // V13 (P11)
  -2.453980f, -0.063388f, -2.477451f,   0.42f, 0.42f,   0.0f,  0.0f, 1.0f, // V14 (P12)
   0.049649f,  2.440128f, -2.417217f,   0.31f, 0.53f,   0.0f,  0.0f, 1.0f, // V15 (P2)

   // 5. Cara Izquierda (-X) -> Normal (-1, 0, 0)
   -2.453980f, -0.063388f, -2.477451f,   0.21f, 0.18f,  1.0f,  0.0f,  0.0f, // V16 (P12)
   -2.517274f, -2.579095f,  0.002115f,   0.32f, 0.08f,  1.0f,  0.0f,  0.0f, // V17 (P0)
   -2.646786f, -0.139047f,  2.493757f,   0.42f, 0.18f,  1.0f,  0.0f,  0.0f, // V18 (P4)
   -2.451372f,  2.421759f,  0.077538f,   0.32f, 0.30f,  1.0f,  0.0f,  0.0f, // V19 (P15)

   // 6. Cara Inferior (-Y) -> Normal (0, -1, 0)
   -2.517274f, -2.579095f,  0.002115f,   0.45f, 0.19f,   0.0f, 1.0f,  0.0f, // V20 (P0)
	0.081432f, -2.513204f, -2.426005f,   0.57f, 0.08f,   0.0f, 1.0f,  0.0f, // V21 (P11)
	2.632201f, -2.553892f,  0.007226f,   0.68f, 0.19f,   0.0f, 1.0f,  0.0f, // V22 (P13)
   -0.140696f, -2.601934f,  2.558561f,   0.57f, 0.30f,   0.0f, 1.0f,  0.0f, // V23 (P8)

   // ---------------------------------------------------------
   // ESQUINAS TRIANGULARES
   // ---------------------------------------------------------
   // 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
// 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
// 7. Esquina Superior Frontal-Izquierda -> Normal (-0.577, 0.577, 0.577)
-2.451372f,  2.421759f, 0.077538f,  0.42f, 1.00f,  0.577f, -0.577f, -0.577f, // V24
-2.646786f, -0.139047f, 2.493757f,  0.32f, 0.88f,  0.577f, -0.577f, -0.577f, // V25 
 0.051152f,  2.399781f, 2.545043f,  0.22f, 1.00f,  0.577f, -0.577f, -0.577f, // V26 

 // 8. Esquina Superior Frontal-Derecha -> Normal (0.577, 0.577, 0.577)
  0.051152f,  2.399781f,  2.545043f,   0.46f, 0.87f,   -0.577f,  -0.577f,  -0.577f, // V27 (P3)
  2.593003f, -0.085222f,  2.505755f,   0.68f, 0.87f,   -0.577f,  -0.577f,  -0.577f, // V28 (P6)
  2.521206f,  2.448241f,  0.063388f,   0.56f, 1.00f,   -0.577f,  -0.577f,  -0.577f, // V29 (P14)

  // 9. Esquina Superior Trasera-Derecha -> Normal (0.577, 0.577, -0.577)
   2.521206f,  2.448241f,  0.063388f,   0.72f, 0.87f,   -0.577f,  -0.577f, 0.577f, // V30 (P14)
   2.534944f, -0.061146f, -2.580280f,   0.91f, 0.87f,   -0.577f,  -0.577f, 0.577f, // V31 (P9)
   0.049649f,  2.440128f, -2.417217f,   0.81f, 1.00f,   -0.577f,  -0.577f, 0.577f, // V32 (P2)

   // 10. Esquina Superior Trasera-Izquierda -> Normal (-0.577, 0.577, -0.577)
	0.049649f,  2.440128f, -2.417217f,   0.00f, 0.65f,  0.577f,  -0.577f, 0.577f, // V33 (P2)
   -2.453980f, -0.063388f, -2.477451f,   0.14f, 0.65f,  0.577f,  -0.577f, 0.577f, // V34 (P12)
   -2.451372f,  2.421759f,  0.077538f,   0.06f, 0.78f,  0.577f,  -0.577f, 0.577f, // V35 (P15)

   // 11. Esquina Inferior Frontal-Izquierda -> Normal (-0.577, -0.577, 0.577)
   -2.646786f, -0.139047f,  2.493757f,   0.21f, 0.62f,  0.577f, 0.577f,  -0.577f, // V36 (P4)
   -2.517274f, -2.579095f,  0.002115f,   0.42f, 0.62f,  0.577f, 0.577f,  -0.577f, // V37 (P0)
   -0.140696f, -2.601934f,  2.558561f,   0.32f, 0.81f,  0.577f, 0.577f,  -0.577f, // V38 (P8)

   // 12. Esquina Inferior Frontal-Derecha -> Normal (0.577, -0.577, 0.577)
	2.593003f, -0.085222f,  2.505755f,   0.45f, 0.37f,   -0.577f, 0.577f,  -0.577f, // V39 (P6)
   -0.140696f, -2.601934f,  2.558561f,   0.67f, 0.37f,   -0.577f, 0.577f,  -0.577f, // V40 (P8)
	2.632201f, -2.553892f,  0.007226f,   0.56f, 0.56f,   -0.577f, 0.577f,  -0.577f, // V41 (P13)

	// 13. Esquina Inferior Trasera-Derecha -> Normal (0.577, -0.577, -0.577)
	 2.534944f, -0.061146f, -2.580280f,   0.72f, 0.37f,   -0.577f, 0.577f, 0.577f, // V42 (P9)
	 2.632201f, -2.553892f,  0.007226f,   0.92f, 0.37f,   -0.577f, 0.577f, 0.577f, // V43 (P13)
	 0.081432f, -2.513204f, -2.426005f,   0.82f, 0.54f,   -0.577f, 0.577f, 0.577f, // V44 (P11)

	 // 14. Esquina Inferior Trasera-Izquierda -> Normal (-0.577, -0.577, -0.577)
	 -2.453980f, -0.063388f, -2.477451f,   0.72f, 0.12f,  0.577f, 0.577f, 0.577f, // V45 (P12)
	  0.081432f, -2.513204f, -2.426005f,   0.92f, 0.12f,  0.577f, 0.577f, 0.577f, // V46 (P11)
	 -2.517274f, -2.579095f,  0.002115f,   0.81f, 0.28f,  0.577f, 0.577f, 0.577f  // V47 (P0)
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

	//TEXTURAS

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();

	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();

	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	dadoTexture = Texture("Textures/dado-de-numerosEscalada.png");
	dadoTexture.LoadTextureA();

	holocronTexture = Texture("Textures/swLogosV3.png");
	holocronTexture.LoadTextureA();

	//MODELOS


	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	//MODELOS ROVER
	Rover_M = Model();
	Rover_M.LoadModel("Models/rovermodificado.obj");

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

	//Cargar modelos SATELITE
	antenaSatelite = Model();
	antenaSatelite.LoadModel("Models/antenaSatelite.obj");

	cuerpoSatelite = Model();
	cuerpoSatelite.LoadModel("Models/cuerpoSatelite.obj");

	panelDerSatelite = Model();
	panelDerSatelite.LoadModel("Models/panelDerSatelite.obj");

	panelIzqSatelite = Model();
	panelIzqSatelite.LoadModel("Models/panelIzqSatelite.obj");
	
	//Añadir modelo del avión
	//Avion_M = Model();
	//Avion_M.LoadModel("Models/");

	Holocron_M2 = Model();
	Holocron_M2.LoadModel("Models/holocronTX.obj");

	avion = Model();
	avion.LoadModel("Models/avionModelo.obj");

	starFighter = Model();
	starFighter.LoadModel("Models/starFighter.obj");

	//Nuevos objetos practica 9

	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,	// Color
		0.3f, 0.3f,									// (Ia:Intensidad Ambiental, Id : Intensidad difusa)
		0.0f, 0.0f, -1.0f);							// Orientación/dirección
	//contador de luces puntuales
	unsigned int pointLightCount = 0;


	// ARREGLO 1 (pointLights): [0] = Holocron, [1] = Pinza
	
	// 2.- Luz puntual azul claro en la posición del Holocron 
	pointLights[0] = PointLight(
		0.0f, 0.75f, 1.0f,      // Color: Azul claro
		0.2f, 1.5f,             // Ia, Id
		-10.0f, 0.5f, 6.0f,     // Posición inicial (se actualiza con el Holocron)
		1.0f, 0.09f, 0.032f);   // Atenuación (con, lin, exp)
	pointLightCount++;

	// 3.- Luz puntual verde en el extremo de la pinza del Rover
	pointLights[1] = PointLight(
		0.0f, 1.0f, 0.0f,       // Color: Verde
		0.8f, 1.5f,             // Ia, Id
		-30.0f, 8.0f, 15.0f,    // Posición inicial 
		1.0f, 0.49f, 0.032f);   // Atenuación (con, lin, exp)
	pointLightCount++;

	// ARREGLO 2 (pointLights2): Orden invertido -> [0] = Pinza, [1] = Holocron

	pointLights2[0] = pointLights[1]; // [0] = Pinza (Verde)
	pointLights2[1] = pointLights[0]; // [1] = Holocron (Azul claro)

	/*
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f, // Color
		0.0f, 1.0f,								  // (Ia:Intensidad Ambiental, Id : Intensidad difusa)
		-6.0f, 1.5f, 1.5f,						  // Posicion
		0.3f, 0.2f, 0.1f);						  // Atenuacion
	pointLightCount++;
	
	*/

	// 4.- Luz puntual en la parte superior de la nave 
	pointLights[2] = PointLight(
		1.0f, 0.2f, 0.0f,      // Color
		0.1f, 1.0f,             // Ia, Id
		0.0f, 21.8f, 40.0f,     // Posición inicial 
		1.0f, 0.045f, 0.055f);   // Atenuación (con, lin, exp)
	pointLightCount++;

	//coordenadas nave 0.0f, 20.0f, 40.0f
    // Luz puntual en motor derecho nave 
	pointLights[3] = PointLight(
		0.15f, 0.6f, 1.0f,      // Color
		2.5f, 1.0f,             // Ia,Id
		-6.5f, 20.0f, 43.44f,   // Posición inicial 
		1.0f, 0.35f, 0.44f);    // Atenuación 
	pointLightCount++;

	// Luz puntual en motor izquierdo nave 
	pointLights[4] = PointLight(
		0.15f, 0.6f, 1.0f,      // Color
		2.5f, 1.0f,             // Ia,Id
		-6.5f, 20.0f, 36.56f,   // Posición inicial 
		1.0f, 0.35f, 0.44f);    // atenuación
	pointLightCount++;

	
	//linterna
	unsigned int spotLightCount = 0;
	GLfloat linternaOn = 1.0f; // 0.0f = Apagada por completo | 1.0f = Encendida
	spotLights[0] = SpotLight(1.0f * linternaOn, 1.0f * linternaOn, 1.0f * linternaOn, // Color
		0.1f, 0.3f,								// -Ia,Id - (Ia:Intensidad Ambiental, Id: Intensidad difusa)
		0.0f, 0.0f, 0.0f,						// Posicion
		0.0f, -1.0f, 0.0f,						// Direccion
		1.0f, 0.0f, 0.25f,						// Atenuacion
		15.0f);									// Angulo
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight AÑADIDAS

	// 1. Faro frontal del Rover 
	
	spotLights[2] = SpotLight(
		1.0f, 0.9f, 0.6f,       // Color (Blanco cálido / amarillento)
		0.0f, 2.0f,             // Intensidad Ambiental (Ia), Intensidad Difusa (Id)
		-50.0f, 2.0f, 20.0f,    // Posición inicial (se actualizará en el while)
		-1.0f, -0.2f, 0.0f,     // Dirección: hacia adelante (-X) y ligeramente abajo
		1.0f, 0.09f, 0.0032f,  // Atenuación (Constante, Lineal, Exponencial) -> Limita el alcance
		20.0f);                 // Ángulo de apertura del cono (edge)
	spotLightCount++;

	// 2. Faro inferior del Avión 
	spotLights[3] = SpotLight(
		1.0f, 1.0f, 1.0f,       // Color (Blanco)
		0.0f, 2.5f,             // Ia, Id
		-24.5f, 2.5f, 0.0f,     // Posición inicial
		0.0f, -1.0f, 0.0f,      // Dirección: totalmente hacia abajo (-Y)
		1.0f, 0.09f, 0.0032f,  // Atenuación con límite de distancia
		25.0f);                 // Ángulo de apertura
	spotLightCount++;

	// 3. Faro frontal del Avión en la nariz de la hélice 
	spotLights[4] = SpotLight(
		1.0f, 1.0f, 0.7f,       // Color (Blanco cálido/amarillento para distinguirlo del inferior)
		0.0f, 3.5f,             // Ia, Id (mayor intensidad para alcanzar el suelo al frente)
		-24.5f, 2.5f, 0.0f,     // Posición inicial
		0.0f, -0.4f, 1.0f,      // Dirección: hacia el frente (+Z) e inclinado hacia el suelo (-Y)
		1.0f, 0.03f, 0.003f,    // Atenuación
		18.0f);                 // Ángulo de apertura
	spotLightCount++;

	// 4. Faro inferior de la nave espacial apuntando al suelo 
	spotLights[5] = SpotLight(
		0.8f, 0.9f, 1.0f,       // Color: Blanco azulado
		0.2f, 4.0f,             // Ia, Id 
		0.0f, 19.2f, 40.0f,     // Posición inicial
		0.0f, -1.0f, 0.0f,      // Dirección
		1.0f, 0.014f, 0.0007f,  // Atenuación
		22.0f);                 // Ángulo de apertura del cono
	spotLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	//DECLARACIONES, VARIABLES

	glm::vec3 lowerLight;
	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelaux2(1.0);
	glm::vec3 color;
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
	//glm::vec3 posLuzNaveArriba;
	//glm::vec3 posLuzNaveAbajo;
	//glm::vec3 posLuzAvionFrente;
	//glm::vec3 dirLuzAvionFrente;

	
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 0.5f * deltaTime;

		//rover avanza < >
		if (dirMovimientoCarro == false) 
		{
			if (movCoche > -250.0f)
			{
				movCoche -= movOffset * deltaTime;
				rotLlanta += rotLlantaInc * deltaTime;
			}
			else
			{
				dirMovimientoCarro = true; 
			}
		}
		else if (dirMovimientoCarro == true) 
		{
			if (movCoche < -40.0f) 
			{
				movCoche += movOffset * deltaTime;
				rotLlanta -= rotLlantaInc * deltaTime;
			}
			else
			{
				dirMovimientoCarro = false; 
			}
		}

		// --- ANIMACIÓN DEL AVIÓN (Rectángulo con esquinas de 1/4 de circunferencia) ---
		switch (estadoAvion)
		{
		case 0: // 1. Vuelo recto largo hacia adelante (-Z)
			if (movAvionZ > -tramoLargoZ)
			{
				movAvionZ -= velAvionRecto * deltaTime;
			}
			else
			{
				movAvionZ = -tramoLargoZ;
				estadoAvion = 1;
			}
			break;

		case 1: // 2. Primer giro de 1/4 de circunferencia (0° a 90° -> gira hacia +X)
			if (anguloAvion < 90.0f)
			{
				anguloAvion += velAvionGiro * deltaTime;
				// Centro del arco 1: Cx = radioCurva, Cz = -tramoLargoZ
				movAvionX = radioCurva - radioCurva * cos(anguloAvion * toRadians);
				movAvionZ = -tramoLargoZ - radioCurva * sin(anguloAvion * toRadians);
				rotAvionY = -anguloAvion; // Gira la nariz del avión junto con el arco
			}
			else
			{
				anguloAvion = 90.0f;
				movAvionX = radioCurva;
				movAvionZ = -tramoLargoZ - radioCurva;
				rotAvionY = -90.0f;
				estadoAvion = 2;
			}
			break;

		case 2: // 3. Vuelo recto corto hacia la derecha (+X)
			if (movAvionX < radioCurva + tramoCortoX)
			{
				movAvionX += velAvionRecto * deltaTime;
			}
			else
			{
				movAvionX = radioCurva + tramoCortoX;
				estadoAvion = 3;
			}
			break;

		case 3: // 4. Segundo giro de 1/4 de circunferencia (90° a 180° -> gira hacia +Z)
			if (anguloAvion < 180.0f)
			{
				anguloAvion += velAvionGiro * deltaTime;
				// Centro del arco 2: Cx = radioCurva + tramoCortoX, Cz = -tramoLargoZ
				movAvionX = (radioCurva + tramoCortoX) - radioCurva * cos(anguloAvion * toRadians);
				movAvionZ = -tramoLargoZ - radioCurva * sin(anguloAvion * toRadians);
				rotAvionY = -anguloAvion;
			}
			else
			{
				anguloAvion = 180.0f;
				movAvionX = (2.0f * radioCurva) + tramoCortoX;
				movAvionZ = -tramoLargoZ;
				rotAvionY = -180.0f;
				estadoAvion = 4;
			}
			break;

		case 4: // 5. Vuelo recto largo de regreso (+Z)
			if (movAvionZ < 0.0f)
			{
				movAvionZ += velAvionRecto * deltaTime;
			}
			else
			{
				movAvionZ = 0.0f;
				estadoAvion = 5;
			}
			break;

		case 5: // 6. Tercer giro de 1/4 de circunferencia (180° a 270° -> gira hacia -X)
			if (anguloAvion < 270.0f)
			{
				anguloAvion += velAvionGiro * deltaTime;
				// Centro del arco 3: Cx = radioCurva + tramoCortoX, Cz = 0.0f
				movAvionX = (radioCurva + tramoCortoX) - radioCurva * cos(anguloAvion * toRadians);
				movAvionZ = 0.0f - radioCurva * sin(anguloAvion * toRadians);
				rotAvionY = -anguloAvion;
			}
			else
			{
				anguloAvion = 270.0f;
				movAvionX = radioCurva + tramoCortoX;
				movAvionZ = radioCurva;
				rotAvionY = -270.0f;
				estadoAvion = 6;
			}
			break;

		case 6: // 7. Vuelo recto corto de regreso (-X)
			if (movAvionX > radioCurva)
			{
				movAvionX -= velAvionRecto * deltaTime;
			}
			else
			{
				movAvionX = radioCurva;
				estadoAvion = 7;
			}
			break;

		case 7: // 8. Cuarto giro de 1/4 de circunferencia (270° a 360° -> regresa al origen)
			if (anguloAvion < 360.0f)
			{
				anguloAvion += velAvionGiro * deltaTime;
				// Centro del arco 4: Cx = radioCurva, Cz = 0.0f
				movAvionX = radioCurva - radioCurva * cos(anguloAvion * toRadians);
				movAvionZ = 0.0f - radioCurva * sin(anguloAvion * toRadians);
				rotAvionY = -anguloAvion;
			}
			else
			{
				// Reinicia valores exactamente en el origen para repetir el circuito sin desfase
				anguloAvion = 0.0f;
				movAvionX = 0.0f;
				movAvionZ = 0.0f;
				rotAvionY = 0.0f;
				estadoAvion = 0;
			}
			break;
		}
		

		
		//ESTADOS SATELITE
		
		
		switch (estadoSatelite)
		{
		case 0: // 1er cuarto (0° a 90°): Orbita y el cuerpo gira 90° para mirar hacia arriba
			if (anguloSat < 90.0f)
			{
				anguloSat += velSatGiro * deltaTime;
				movSatX = radioCurva2 * sin(anguloSat * toRadians);
				movSatZ = -radioCurva2 + radioCurva2 * cos(anguloSat * toRadians);
				rotSatY = anguloSat; // Mantiene el frente orientado hacia el Holocron

				rotSatX += velSatGiro * deltaTime; // Sube la mirada de 0° a +90°
			}
			else
			{
				anguloSat = 90.0f;
				movSatX = radioCurva2;
				movSatZ = -radioCurva2;
				rotSatY = 90.0f;
				rotSatX = 90.0f;
				estadoSatelite = 1;
			}
			break;

		case 1: // 2do cuarto (90° a 180°): Paneles giran 90° hacia el Holocron + ligero giro de antena
			if (anguloSat < 180.0f)
			{
				anguloSat += velSatGiro * deltaTime;
				movSatX = radioCurva2 * sin(anguloSat * toRadians);
				movSatZ = -radioCurva2 + radioCurva2 * cos(anguloSat * toRadians);
				rotSatY = anguloSat;

				// Compensan los +90° del cuerpo girando a -90° para mirar al Holocron
				rotPanelDer -= velSatGiro * deltaTime;
				rotPanelIzq -= velSatGiro * deltaTime;
				rotAntena -= (0.5f * velSatGiro) * deltaTime; // Giro de ajuste (-45°)
			}
			else
			{
				anguloSat = 180.0f;
				movSatX = 0.0f;
				movSatZ = -2.0f * radioCurva2;
				rotSatY = 180.0f;
				rotPanelDer = -90.0f;
				rotPanelIzq = -90.0f;
				rotAntena = -45.0f;
				estadoSatelite = 2;
			}
			break;

		case 2: // 3er cuarto (180° a 270°): Cuerpo gira 180° para mirar abajo (+90° a -90°) y paneles/antena se ajustan
			if (anguloSat < 270.0f)
			{
				anguloSat += velSatGiro * deltaTime;
				movSatX = radioCurva2 * sin(anguloSat * toRadians);
				movSatZ = -radioCurva2 + radioCurva2 * cos(anguloSat * toRadians);
				rotSatY = anguloSat;

				// Como recorre 180° mientras la órbita avanza 90°, se mueve al doble de velocidad
				rotSatX -= (2.0f * velSatGiro) * deltaTime;     // Pasa de +90° (arriba) a -90° (abajo)
				rotPanelDer += (2.0f * velSatGiro) * deltaTime; // Pasa de -90° a +90° para seguir mirando al Holocron
				rotPanelIzq += (2.0f * velSatGiro) * deltaTime;
				rotAntena += 1 + velSatGiro * deltaTime;            // Pasa de -45° a +45°
			}
			else
			{
				anguloSat = 270.0f;
				movSatX = -radioCurva2;
				movSatZ = -radioCurva2;
				rotSatY = 270.0f;
				rotSatX = -90.0f;
				rotPanelDer = 90.0f;
				rotPanelIzq = 90.0f;
				rotAntena = 45.0f;
				estadoSatelite = 3;
			}
			break;

		case 3: // 4to cuarto (270° a 360°): Cuerpo gira 90° de regreso a 0° junto con paneles y antena
			if (anguloSat < 360.0f)
			{
				anguloSat += velSatGiro * deltaTime;
				movSatX = radioCurva2 * sin(anguloSat * toRadians);
				movSatZ = -radioCurva2 + radioCurva2 * cos(anguloSat * toRadians);
				rotSatY = anguloSat;

				rotSatX += velSatGiro * deltaTime;              // Regresa de -90° a 0°
				rotPanelDer -= velSatGiro * deltaTime;          // Regresa de +90° a 0°
				rotPanelIzq -= velSatGiro * deltaTime;
				rotAntena -= (0.5f * velSatGiro) * deltaTime;   // Regresa de +45° a 0°
			}
			else
			{
				// Reinicia todos los valores en el origen para repetir el ciclo sin desfase
				anguloSat = 0.0f;
				movSatX = 0.0f;
				movSatZ = 0.0f;
				rotSatX = 0.0f;
				rotSatY = 0.0f;
				rotPanelDer = 0.0f;
				rotPanelIzq = 0.0f;
				rotAntena = 0.0f;
				estadoSatelite = 0;
			}
			break;
		}
		
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
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);

		//Reinicializando variables cada ciclo de reloj
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		toffset = glm::vec2(0.0f, 0.0f);

		// Selección dinámica de PointLights activas (incluyendo la nave con la tecla H)
		PointLight lucesPuntualesActivas[MAX_POINT_LIGHTS];
		unsigned int numPointActivas = 0;
		
		if (!mainWindow.getUsarArreglo2())
		{
			if (mainWindow.getLuzHolocronOn())
				lucesPuntualesActivas[numPointActivas++] = pointLights[0]; // Holocron (Tecla F)
			if (mainWindow.getLuzPinzaOn())
				lucesPuntualesActivas[numPointActivas++] = pointLights[1]; // Pinza (Tecla G)
		}
		else
		{
			if (mainWindow.getLuzPinzaOn())
				lucesPuntualesActivas[numPointActivas++] = pointLights2[0]; // Pinza (Tecla G)
			if (mainWindow.getLuzHolocronOn())
				lucesPuntualesActivas[numPointActivas++] = pointLights2[1]; // Holocron (Tecla F)
		}

		if (mainWindow.getLuzNaveOn())
		{
			lucesPuntualesActivas[numPointActivas++] = pointLights[2]; // Luz superior Nave (Tecla H)
		}

		if (mainWindow.getLuzMotor1On())
		{
			lucesPuntualesActivas[numPointActivas++] = pointLights[3]; // Motor 1 (Tecla J)
		}

		if (mainWindow.getLuzMotor2On())
		{
			lucesPuntualesActivas[numPointActivas++] = pointLights[4]; // Motor 2 (Tecla K)
		}

		shaderList[0].SetPointLights(lucesPuntualesActivas, numPointActivas);
		



		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshListModel[2]->RenderMeshModel();
	
		//BLACKHAWK
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Dado
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 5.0f, 6.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshListModel[4]->RenderMeshModel();

		//ROVER PROFESOR

				//Rover: Sustituir por su propio Rover con jerarquía

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -1.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rover_M.RenderModel();


		//*****------------*INICIA DIBUJO Satelite*-------------------*****///////

		/*
		Model antenaSatelite;
		Model cuerpoSatelite;
		Model panelDerSatelite;
		Model panelIzqSatelite;
		*/



		//cuerpo Principal
		color = glm::vec3(1.0f, 0.0f, 0.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f + movSatX, 30.0f, 0.0f + movSatZ));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		// 1. Primero rotSatY para que el satélite apunte siempre hacia el Holocron durante la órbita
		model = glm::rotate(model, glm::radians(rotSatY), glm::vec3(0.0f, 1.0f, 0.0f));
		// 2. Después rotSatX para que incline su nariz hacia arriba (+90°) o hacia abajo (-90°)
		model = glm::rotate(model, glm::radians(rotSatX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotSatZ), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		modelaux2 = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoSatelite.RenderModel();

		//**************PANELES***************/////////////////

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.047f, 0.0f, -0.05f));
		model = glm::rotate(model, glm::radians(rotPanelDer), glm::vec3(1.0f, 0.0f, 0.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		panelDerSatelite.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.05f, 0.0f, -0.05f));
		model = glm::rotate(model, glm::radians(rotPanelIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		panelIzqSatelite.RenderModel();

		//**************ANTENA***************/////////////////

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.135f));
		// Rotación en X (1, 0, 0) para que la antena se incline buscando al Holocron
		model = glm::rotate(model, glm::radians(rotAntena), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antenaSatelite.RenderModel();


		//Rover: Sustituir por su propio Rover con jerarquía
		
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

		
		// Modelo Inicial 
		color = glm::vec3(0.0f, 0.0f, 1.0f); // modelo de color azul

		model = glm::mat4(1.0);
		// Se suma mainWindow.getmuevex() en X para mover todo el Rover y su jerarquía
		model = glm::translate(model, glm::vec3( -40.0f + movCoche, 2.0f, 15.0f));
		modelaux = model;
		modelaux2 = model;

		// --- LUZ FRONTAL UNIDA A LA JERARQUÍA DEL ROVER ---
		// Calculamos la posición mundial del frente del chasis (flecha naranja) a partir de 'modelaux2'
		glm::vec3 posLuzRover = glm::vec3(modelaux2 * glm::vec4(-2.5f, 0.3f, 0.0f, 1.0f));
		glm::vec3 dirLuzRover = glm::vec3(-1.0f, -0.2f, 0.0f); // Ilumina hacia adelante (-X) y un poco al suelo
		spotLights[2].SetFlash(posLuzRover, dirLuzRover);
		// --------------------------------------------------

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		roverCuerpo.RenderModel();
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

		
		glm::vec3 posPuntaPinza = glm::vec3(modelaux * glm::vec4(-2.5f, 1.5f, 0.0f, 1.0f));
		pointLights[1].SetPos(posPuntaPinza);  // En Arreglo 1 es el índice [1]
		pointLights2[0].SetPos(posPuntaPinza); // En Arreglo 2 es el índice [0]

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
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ejeRuedaFIzq.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.25f, -1.5f, 0.7f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, 1.0f));
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
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ejeRuedaFDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.25f, -1.5f, -0.7f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaFDer.RenderModel();

		//

		//*****************PARTES rueda central Der*****************************//

		model = modelaux2;
		model = glm::translate(model, glm::vec3(2.7f, 0.3f, -3.2f));
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaCDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -2.0f, -1.2f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda trasera Der*****************************//

		model = modelaux2;
		model = glm::translate(model, glm::vec3(3.7f, 0.3f, -3.2f));
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaTDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.3f, -2.0f, -1.2f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda central Izq*****************************//

		model = modelaux2;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-3.7f, 0.3f, -3.2f));
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaCDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -2.0f, -1.2f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, -1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();

		//*****************PARTES rueda trasera Izq*****************************//

		model = modelaux2;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.7f, 0.3f, -3.2f));
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoRuedaTDer.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.3f, -2.0f, -1.2f));
		model = glm::rotate(model, glm::radians(rotLlanta), glm::vec3(0.0f, 0.0f, -1.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaRuedaCDer.RenderModel();
		
		//*****************TERMINA DIBUJADO ROVER*****************************//


		//Holocron por codigo

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color que multiplica a la información de color de la textura
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::mat4(1.0);
		//-30.0f + mainWindow.getmuevex(), 2.0f, 15.0f
		model = glm::translate(model, glm::vec3(-15.0f, 30.0f, -15.0));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glm::vec3 posHolocron = glm::vec3(model * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		pointLights[0].SetPos(posHolocron);  // En Arreglo 1 es el índice [0]
		pointLights2[1].SetPos(posHolocron); // En Arreglo 2 es el índice [1]
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		holocronTexture.UseTexture();
		meshListModel[5]->RenderMeshModel();

		

		// Avion de Blender
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		model = glm::mat4(1.0f);
		// Se suman getMueveAvionX() y getMueveAvionY() a la posición base del avión
		// 1. Traslación: Posición inicial (-24.5, 2.5, 20.0) + desplazamiento de la animación
		model = glm::translate(model, glm::vec3(
			-24.5f + movAvionX + mainWindow.getMueveAvionX(),
			2.5f + mainWindow.getMueveAvionY(),
			20.0f + movAvionZ));
		// 2. Rotación: Orienta el avión en la dirección de la trayectoria (eje Y)
		model = glm::rotate(model, rotAvionY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 modelAvionAux = model;

		glm::vec3 colorFaroAbajo;
		switch (mainWindow.getColorFaroAvion())
		{
		case 0: colorFaroAbajo = glm::vec3(1.0f, 0.0f, 0.0f); break; // Rojo
		case 1: colorFaroAbajo = glm::vec3(1.0f, 1.0f, 0.0f); break; // Amarillo
		case 2: colorFaroAbajo = glm::vec3(0.0f, 1.0f, 0.0f); break; // Verde
		case 3: colorFaroAbajo = glm::vec3(0.0f, 1.0f, 1.0f); break; // Cian
		case 4: colorFaroAbajo = glm::vec3(0.0f, 0.0f, 1.0f); break; // Azul
		case 5: colorFaroAbajo = glm::vec3(1.0f, 0.0f, 1.0f); break; // Magenta
		}
		spotLights[3].SetColor(colorFaroAbajo);
		glm::vec3 posLuzAvionAbajo = glm::vec3(modelAvionAux * glm::vec4(0.0f, -0.6f, 0.0f, 1.0f));
		spotLights[3].SetFlash(posLuzAvionAbajo, glm::vec3(0.0f, -1.0f, 0.0f));


		// La dirección del faro frontal rota automáticamente con modelAvionAux
		glm::vec3 posLuzAvionFrente = glm::vec3(modelAvionAux * glm::vec4(0.0f, -0.15f, 0.4f, 1.0f));
		glm::vec3 dirLuzAvionFrente = glm::normalize(glm::vec3(modelAvionAux * glm::vec4(0.0f, -0.4f, -1.0f, 0.0f)));
		spotLights[4].SetFlash(posLuzAvionFrente, dirLuzAvionFrente);

		// Actualizamos el arreglo de SpotLights en el shader para reflejar el movimiento
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		avion.RenderModel();

		//Dibujo de la nave

		// --- DIBUJO DE LA NAVE Y SUS LUCES ---
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 20.0f, 40.0f));

		// 1. PointLight superior 
		glm::vec3 posLuzNaveArriba = glm::vec3(model * glm::vec4(0.0f, 1.8f, 0.0f, 1.0f));
		pointLights[2].SetPos(posLuzNaveArriba);

		// 2. PointLight Motor  - Derecho 
		glm::vec3 posLuzMotor1 = glm::vec3(model * glm::vec4(-6.5f, 0.0f, 3.44f, 1.0f));
		pointLights[3].SetPos(posLuzMotor1);

		// 3. PointLight Motor Izquierdo 
		glm::vec3 posLuzMotor2 = glm::vec3(model * glm::vec4(-6.5f, 0.0f, -3.44f, 1.0f));
		pointLights[4].SetPos(posLuzMotor2);

		// 4. SpotLight inferior apuntando al suelo
		glm::vec3 posLuzNaveAbajo = glm::vec3(model * glm::vec4(0.0f, -0.8f, 0.0f, 1.0f));
		spotLights[5].SetFlash(posLuzNaveAbajo, glm::vec3(0.0f, -1.0f, 0.0f));

		// Encender o apagar spotLights[5]
		if (mainWindow.getLuzNaveOn())
			shaderList[0].SetSpotLights(spotLights, spotLightCount);     
		else
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 1); 

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		starFighter.RenderModel();

		glDisable(GL_BLEND);


		//PRUEBA POS
		//-4.05f, 20.0f, 43.44f,
		/*
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.25f, 20.0f, 36.56f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshListModel[4]->RenderMeshModel();
		*/

		//Agave ¿qué sucede si lo renderizan antes del helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshListModel[3]->RenderMeshModel();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
