// Práctica 2: Dibujo de Personaje con Shaders Personaje
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>

// GLM 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Clases auxiliares del proyecto
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

const float toRadians = 3.14159265f / 180.0f;
Window mainWindow;

std::vector<MeshColor*> meshColorList;
std::vector<Shader> shaderList;

// =======================================================
// SHADERS DEL PERSONAJE
// =======================================================
static const char* vShaderColor = "shaders/shaderpersonaje.vert";
static const char* fShaderColor = "shaders/shaderpersonaje.frag";

// =======================================================
// SECCIÓN DE PALETA DE COLORES (RGB)
// =======================================================
namespace Colores {
    const float CAFE_BOTA[3] = { 0.824f, 0.584f, 0.220f }; 
    const float CAFE_CAMISA[3] = { 0.478f, 0.255f, 0.067f };
    const float ROJO[3] = { 0.850f, 0.100f, 0.100f };
    const float DORADO[3] = { 0.950f, 0.750f, 0.100f };
    const float AMARILLO[3] = { 1.000f, 1.000f, 0.000f };
    const float MORADO[3] = { 0.300f, 0.180f, 0.310f };
    const float MORADO_CINTURON[3] = { 0.150f, 0.070f, 0.150f };
    const float PIEL[3] = { 0.860f, 0.610f, 0.310f };
    const float BLANCO[3] = { 1.000f, 1.000f, 1.000f };
    const float GRIS_OSCURO[3] = { 0.200f, 0.200f, 0.200f };
    const float MARRON_CODERA[3] = { 0.72f, 0.58f, 0.35f };
    const float MARRON_CODERA_INT[3] = { 0.712f, 0.583f, 0.447f };
    const float ROJO_OSCURO[3] = { 0.302f, 0.000f, 0.055f };
    const float NEGRO[3] = { 0.0f, 0.0f, 0.0f };
}

// =======================================================
// EXPORTACIÓN DE VÉRTICES DE LA BOTA DERECHA (GeoGebra)
// =======================================================
void CrearBotaDerecha()
{
    // Selección del color por defecto para la bota
#define R Colores::CAFE_BOTA[0]
#define G Colores::CAFE_BOTA[1]
#define B Colores::CAFE_BOTA[2]

// Arreglo de vértices: X, Y, Z, R, G, B (21 Triángulos = 63 vértices = 378 floats)
    GLfloat vertices_bota_Der[] = {
        // Triángulo t1 (C, D, E)
         0.59f, -0.78f, 0.0f,   R, G, B,
         0.55f, -0.75f, 0.0f,   R, G, B,
         0.61f, -0.74f, 0.0f,   R, G, B,

         // Triángulo t2 (D, F, G)
          0.55f, -0.75f, 0.0f,   R, G, B,
          0.52f, -0.69f, 0.0f,   R, G, B,
          0.58f, -0.72f, 0.0f,   R, G, B,

          // Triángulo t3 (E, G, D)
           0.61f, -0.74f, 0.0f,   R, G, B,
           0.58f, -0.72f, 0.0f,   R, G, B,
           0.55f, -0.75f, 0.0f,   R, G, B,

           // Triángulo t4 (E, H, G)
            0.61f, -0.74f, 0.0f,   R, G, B,
            0.62f, -0.71f, 0.0f,   R, G, B,
            0.58f, -0.72f, 0.0f,   R, G, B,

            // Triángulo t5 (F, I, G)
             0.52f, -0.69f, 0.0f,   R, G, B,
             0.50f, -0.65f, 0.0f,   R, G, B,
             0.58f, -0.72f, 0.0f,   R, G, B,

             // Triángulo t6 (H, J, G)
              0.62f, -0.71f, 0.0f,   R, G, B,
              0.63f, -0.66f, 0.0f,   R, G, B,
              0.58f, -0.72f, 0.0f,   R, G, B,

              // Triángulo t7 (J, I, G)
               0.63f, -0.66f, 0.0f,   R, G, B,
               0.50f, -0.65f, 0.0f,   R, G, B,
               0.58f, -0.72f, 0.0f,   R, G, B,

               // Triángulo t8 (J, K, I)
                0.63f, -0.66f, 0.0f,   R, G, B,
                0.62f, -0.60f, 0.0f,   R, G, B,
                0.50f, -0.65f, 0.0f,   R, G, B,

                // Triángulo t9 (I, L, K)
                 0.50f, -0.65f, 0.0f,   R, G, B,
                 0.47f, -0.61f, 0.0f,   R, G, B,
                 0.62f, -0.60f, 0.0f,   R, G, B,

                 // Triángulo t10 (K, M, L)
                  0.62f, -0.60f, 0.0f,   R, G, B,
                  0.60f, -0.56f, 0.0f,   R, G, B,
                  0.47f, -0.61f, 0.0f,   R, G, B,

                  // Triángulo t11 (L, N, M)
                   0.47f, -0.61f, 0.0f,   R, G, B,
                   0.44f, -0.59f, 0.0f,   R, G, B,
                   0.60f, -0.56f, 0.0f,   R, G, B,

                   // Triángulo t12 (M, O, N)
                    0.60f, -0.56f, 0.0f,   R, G, B,
                    0.58f, -0.53f, 0.0f,   R, G, B,
                    0.44f, -0.59f, 0.0f,   R, G, B,

                    // Triángulo t13 (N, P, O)
                     0.44f, -0.59f, 0.0f,   R, G, B,
                     0.42f, -0.56f, 0.0f,   R, G, B,
                     0.58f, -0.53f, 0.0f,   R, G, B,

                     // Triángulo t14 (O, Q, P)
                      0.58f, -0.53f, 0.0f,   R, G, B,
                      0.58f, -0.51f, 0.0f,   R, G, B,
                      0.42f, -0.56f, 0.0f,   R, G, B,

                      // Triángulo t15 (P, R, Q)
                       0.42f, -0.56f, 0.0f,   R, G, B,
                       0.42f, -0.54f, 0.0f,   R, G, B,
                       0.58f, -0.51f, 0.0f,   R, G, B,

                       // Triángulo t16 (Q, S, R)
                        0.58f, -0.51f, 0.0f,   R, G, B,
                        0.58f, -0.49f, 0.0f,   R, G, B,
                        0.42f, -0.54f, 0.0f,   R, G, B,

                        // Triángulo t17 (R, T, S)
                         0.42f, -0.54f, 0.0f,   R, G, B,
                         0.42f, -0.51f, 0.0f,   R, G, B,
                         0.58f, -0.49f, 0.0f,   R, G, B,

                         // Triángulo t18 (S, U, T)
                          0.58f, -0.49f, 0.0f,   R, G, B,
                          0.57f, -0.46f, 0.0f,   R, G, B,
                          0.42f, -0.51f, 0.0f,   R, G, B,

                          // Triángulo t19 (T, V, U)
                           0.42f, -0.51f, 0.0f,   R, G, B,
                           0.43f, -0.47f, 0.0f,   R, G, B,
                           0.57f, -0.46f, 0.0f,   R, G, B,

                           // Triángulo t20 (U, W, V)
                            0.57f, -0.46f, 0.0f,   R, G, B,
                            0.55f, -0.44f, 0.0f,   R, G, B,
                            0.43f, -0.47f, 0.0f,   R, G, B,

                            // Triángulo t21 (V, Z, W)
                             0.43f, -0.47f, 0.0f,   R, G, B,
                             0.49f, -0.45f, 0.0f,   R, G, B,
                             0.55f, -0.44f, 0.0f,   R, G, B,



    };

#undef R
#undef G
#undef B

    MeshColor* botaDerecha = new MeshColor();
    botaDerecha->CreateMeshColor(vertices_bota_Der, 378);
    meshColorList.push_back(botaDerecha); // Índice 0
}


// =========================================================
// EXPORTACIÓN DE VÉRTICES DE LA BOTA IZQUIERDA (GeoGebra)
// =========================================================
void CrearBotaIzquierda()
{
    // Selección del color por defecto para la bota izquierda (Rojo)
#define R Colores::CAFE_BOTA[0]
#define G Colores::CAFE_BOTA[1]
#define B Colores::CAFE_BOTA[2]

// Arreglo de vértices: X, Y, Z, R, G, B (23 Triángulos = 69 vértices = 414 floats)
    GLfloat vertices_bota_izquierda[] = {
        // Triángulo t1 (C, D, E)
        -0.25f, -0.30f, 0.0f,  R, G, B,
        -0.25f, -0.32f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t2 (D, F, E)
        -0.25f, -0.32f, 0.0f,  R, G, B,
        -0.25f, -0.34f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t3 (F, G, E)
        -0.25f, -0.34f, 0.0f,  R, G, B,
        -0.24f, -0.34f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t4 (G, H, E)
        -0.24f, -0.34f, 0.0f,  R, G, B,
        -0.23f, -0.35f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t5 (H, I, E)
        -0.23f, -0.35f, 0.0f,  R, G, B,
        -0.20f, -0.34f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t6 (I, C, E)
        -0.20f, -0.34f, 0.0f,  R, G, B,
        -0.25f, -0.30f, 0.0f,  R, G, B,
        -0.23f, -0.32f, 0.0f,  R, G, B,

        // Triángulo t7 (I, J, C)
        -0.20f, -0.34f, 0.0f,  R, G, B,
        -0.17f, -0.33f, 0.0f,  R, G, B,
        -0.25f, -0.30f, 0.0f,  R, G, B,

        // Triángulo t8 (C, K, J)
        -0.25f, -0.30f, 0.0f,  R, G, B,
        -0.23f, -0.28f, 0.0f,  R, G, B,
        -0.17f, -0.33f, 0.0f,  R, G, B,

        // Triángulo t9 (J, L, K)
        -0.17f, -0.33f, 0.0f,  R, G, B,
        -0.10f, -0.28f, 0.0f,  R, G, B,
        -0.23f, -0.28f, 0.0f,  R, G, B,

        // Triángulo t10 (K, M, L)
        -0.23f, -0.28f, 0.0f,  R, G, B,
        -0.20f, -0.24f, 0.0f,  R, G, B,
        -0.10f, -0.28f, 0.0f,  R, G, B,

        // Triángulo t11 (L, N, M)
        -0.10f, -0.28f, 0.0f,  R, G, B,
        -0.08f, -0.26f, 0.0f,  R, G, B,
        -0.20f, -0.24f, 0.0f,  R, G, B,

        // Triángulo t12 (N, O, M)
        -0.08f, -0.26f, 0.0f,  R, G, B,
        -0.08f, -0.13f, 0.0f,  R, G, B,
        -0.20f, -0.24f, 0.0f,  R, G, B,

        // Triángulo t13 (M, P, O)
        -0.20f, -0.24f, 0.0f,  R, G, B,
        -0.20f, -0.21f, 0.0f,  R, G, B,
        -0.08f, -0.13f, 0.0f,  R, G, B,

        // Triángulo t14 (P, Q, O)
        -0.20f, -0.21f, 0.0f,  R, G, B,
        -0.21f, -0.18f, 0.0f,  R, G, B,
        -0.08f, -0.13f, 0.0f,  R, G, B,

        // Triángulo t15 (Q, R, O)
        -0.21f, -0.18f, 0.0f,  R, G, B,
        -0.25f, -0.14f, 0.0f,  R, G, B,
        -0.08f, -0.13f, 0.0f,  R, G, B,

        // Triángulo t16 (R, S, O)
        -0.25f, -0.14f, 0.0f,  R, G, B,
        -0.21f, -0.04f, 0.0f,  R, G, B,
        -0.08f, -0.13f, 0.0f,  R, G, B,

        // Triángulo t17 (O, T, S)
        -0.08f, -0.13f, 0.0f,  R, G, B,
        -0.07f, -0.12f, 0.0f,  R, G, B,
        -0.21f, -0.04f, 0.0f,  R, G, B,

        // Triángulo t18 (T, U, S)
        -0.07f, -0.12f, 0.0f,  R, G, B,
        -0.07f, -0.02f, 0.0f,  R, G, B,
        -0.21f, -0.04f, 0.0f,  R, G, B,

        // Triángulo t19 (U, V, W)
        -0.07f, -0.02f, 0.0f,  R, G, B,
        -0.11f, -0.02f, 0.0f,  R, G, B,
        -0.11f, -0.03f, 0.0f,  R, G, B,

        // Triángulo t20 (V, Z, W)
        -0.11f, -0.02f, 0.0f,  R, G, B,
        -0.14f, -0.02f, 0.0f,  R, G, B,
        -0.11f, -0.03f, 0.0f,  R, G, B,

        // Triángulo t21 (Z, A1, W)
        -0.14f, -0.02f, 0.0f,  R, G, B,
        -0.16f, -0.02f, 0.0f,  R, G, B,
        -0.11f, -0.03f, 0.0f,  R, G, B,

        // Triángulo t22 (A1, B1, W)
        -0.16f, -0.02f, 0.0f,  R, G, B,
        -0.18f, -0.03f, 0.0f,  R, G, B,
        -0.11f, -0.03f, 0.0f,  R, G, B,

        // Triángulo t23 (B1, S, W)
        -0.18f, -0.03f, 0.0f,  R, G, B,
        -0.21f, -0.04f, 0.0f,  R, G, B,
        -0.11f, -0.03f, 0.0f,  R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* botaIzquierda = new MeshColor();
    botaIzquierda->CreateMeshColor(vertices_bota_izquierda, 414);
    meshColorList.push_back(botaIzquierda); // Índice 1
}

// ========================================================
// EXPORTACIÓN DE VÉRTICES DE LA ESPINILLERA (GeoGebra)
// ========================================================
void crearEspinilleraDer()
{
    // Selección del color por defecto para la espinillera
#define R Colores::DORADO[0]
#define G Colores::DORADO[1]
#define B Colores::DORADO[2]

// Arreglo de vértices: X, Y, Z, R, G, B (21 Triángulos = 63 vértices = 378 floats)
    GLfloat verticesEspinilleraDer[] = {
        // Triángulo t1 (C, D, E)
         0.43f, -0.47f, 0.0f,   R, G, B,
         0.42f, -0.51f, 0.0f,   R, G, B,
         0.39f, -0.47f, 0.0f,   R, G, B,

         // Triángulo t2 (D, F, E)
          0.42f, -0.51f, 0.0f,   R, G, B,
          0.41f, -0.53f, 0.0f,   R, G, B,
          0.39f, -0.47f, 0.0f,   R, G, B,

          // Triángulo t3 (E, G, F)
           0.39f, -0.47f, 0.0f,   R, G, B,
           0.35f, -0.49f, 0.0f,   R, G, B,
           0.41f, -0.53f, 0.0f,   R, G, B,

           // Triángulo t4 (F, H, G)
            0.41f, -0.53f, 0.0f,   R, G, B,
            0.42f, -0.57f, 0.0f,   R, G, B,
            0.35f, -0.49f, 0.0f,   R, G, B,

            // Triángulo t5 (C, I, E)
             0.43f, -0.47f, 0.0f,   R, G, B,
             0.42f, -0.43f, 0.0f,   R, G, B,
             0.39f, -0.47f, 0.0f,   R, G, B,

             // Triángulo t6 (I, G, E)
              0.42f, -0.43f, 0.0f,   R, G, B,
              0.35f, -0.49f, 0.0f,   R, G, B,
              0.39f, -0.47f, 0.0f,   R, G, B,

              // Triángulo t7 (I, J, G)
               0.42f, -0.43f, 0.0f,   R, G, B,
               0.36f, -0.29f, 0.0f,   R, G, B,
               0.35f, -0.49f, 0.0f,   R, G, B,

               // Triángulo t8 (G, K, J)
                0.35f, -0.49f, 0.0f,   R, G, B,
                0.30f, -0.45f, 0.0f,   R, G, B,
                0.36f, -0.29f, 0.0f,   R, G, B,

                // Triángulo t9 (K, L, J)
                 0.30f, -0.45f, 0.0f,   R, G, B,
                 0.17f, -0.38f, 0.0f,   R, G, B,
                 0.36f, -0.29f, 0.0f,   R, G, B,

                 // Triángulo t10 (J, M, L)
                  0.36f, -0.29f, 0.0f,   R, G, B,
                  0.33f, -0.27f, 0.0f,   R, G, B,
                  0.17f, -0.38f, 0.0f,   R, G, B,

                  // Triángulo t11 (M, N, L)
                   0.33f, -0.27f, 0.0f,   R, G, B,
                   0.31f, -0.25f, 0.0f,   R, G, B,
                   0.17f, -0.38f, 0.0f,   R, G, B,

                   // Triángulo t12 (N, O, L)
                    0.31f, -0.25f, 0.0f,   R, G, B,
                    0.27f, -0.24f, 0.0f,   R, G, B,
                    0.17f, -0.38f, 0.0f,   R, G, B,

                    // Triángulo t13 (O, P, L)
                     0.27f, -0.24f, 0.0f,   R, G, B,
                     0.25f, -0.25f, 0.0f,   R, G, B,
                     0.17f, -0.38f, 0.0f,   R, G, B,

                     // Triángulo t14 (L, Q, R)
                      0.17f, -0.38f, 0.0f,   R, G, B,
                      0.14f, -0.35f, 0.0f,   R, G, B,
                      0.19f, -0.34f, 0.0f,   R, G, B,

                      // Triángulo t15 (Q, S, R)
                       0.14f, -0.35f, 0.0f,   R, G, B,
                       0.13f, -0.34f, 0.0f,   R, G, B,
                       0.19f, -0.34f, 0.0f,   R, G, B,

                       // Triángulo t16 (S, T, R)
                        0.13f, -0.34f, 0.0f,   R, G, B,
                        0.14f, -0.33f, 0.0f,   R, G, B,
                        0.19f, -0.34f, 0.0f,   R, G, B,

                        // Triángulo t17 (T, U, V)
                         0.14f, -0.33f, 0.0f,   R, G, B,
                         0.16f, -0.30f, 0.0f,   R, G, B,
                         0.18f, -0.34f, 0.0f,   R, G, B,

                         // Triángulo t18 (U, W, Z)
                          0.16f, -0.30f, 0.0f,   R, G, B,
                          0.17f, -0.29f, 0.0f,   R, G, B,
                          0.17f, -0.32f, 0.0f,   R, G, B,

                          // Triángulo t19 (P, A1, R)
                           0.25f, -0.25f, 0.0f,   R, G, B,
                           0.22f, -0.25f, 0.0f,   R, G, B,
                           0.19f, -0.34f, 0.0f,   R, G, B,

                           // Triángulo t20 (A1, B1, C1)
                            0.22f, -0.25f, 0.0f,   R, G, B,
                            0.21f, -0.27f, 0.0f,   R, G, B,
                            0.21f, -0.30f, 0.0f,   R, G, B,

                            // Triángulo t21 (D1, V, R)
                             0.19f, -0.33f, 0.0f,   R, G, B,
                             0.18f, -0.34f, 0.0f,   R, G, B,
                             0.19f, -0.34f, 0.0f,   R, G, B,


                             // Triángulo FIX1
              0.42f, -0.57f, 0.0f, R, G, B,
              0.42f, -0.53f, 0.0f, R, G, B,
              0.38f, -0.52f, 0.0f, R, G, B,

              // Triángulo FIX2
              0.42f, -0.53f, 0.0f, R, G, B,
              0.38f, -0.52f, 0.0f, R, G, B,
              0.42f, -0.5f, 0.0f, R, G, B,

              // Triángulo FIX2
                0.29f, -0.26f, 0.0f, R, G, B,
                0.24f, -0.25f, 0.0f, R, G, B,
                0.17f, -0.37f, 0.0f, R, G, B,

                // Triángulo FIX2
                 0.16f, -0.37f, 0.0f, R, G, B,
                 0.15f, -0.34f, 0.0f, R, G, B,
                 0.21f, -0.36f, 0.0f, R, G, B,
    };

#undef R
#undef G
#undef B

    MeshColor* espinilleraDerecha = new MeshColor();
    espinilleraDerecha->CreateMeshColor(verticesEspinilleraDer, 450);
    meshColorList.push_back(espinilleraDerecha); //INDICE 2
}

void crearEspinilleraIzq()
{
    // Selección del color por defecto para la espinillera
#define R Colores::DORADO[0]
#define G Colores::DORADO[1]
#define B Colores::DORADO[2]

// Arreglo de vértices: X, Y, Z, R, G, B (21 Triángulos = 63 vértices = 378 floats)
    GLfloat verticesEspinilleraIzquierda[] = {

        // t1: C, D, E
        -0.25f, -0.14f, 0.0f,    R, G, B,
        -0.24f, -0.14f, 0.0f,    R, G, B,
        -0.20f, -0.04f, 0.0f,    R, G, B,

        // t2: E, F, C
        -0.20f, -0.04f, 0.0f,    R, G, B,
        -0.21f, -0.02f, 0.0f,    R, G, B,
        -0.25f, -0.14f, 0.0f,    R, G, B,

        // t3: F, G, C
        -0.21f, -0.02f, 0.0f,    R, G, B,
        -0.24f,  0.01f, 0.0f,    R, G, B,
        -0.25f, -0.14f, 0.0f,    R, G, B,

        // t4: C, H, G
        -0.25f, -0.14f, 0.0f,    R, G, B,
        -0.32f, -0.11f, 0.0f,    R, G, B,
        -0.24f,  0.01f, 0.0f,    R, G, B,

        // t5: G, I, H
        -0.24f,  0.01f, 0.0f,    R, G, B,
        -0.28f,  0.00f, 0.0f,    R, G, B,
        -0.32f, -0.11f, 0.0f,    R, G, B,

        // t6: I, J, H
        -0.28f,  0.00f, 0.0f,    R, G, B,
        -0.30f,  0.01f, 0.0f,    R, G, B,
        -0.32f, -0.11f, 0.0f,    R, G, B,

        // t7: H, K, J
        -0.32f, -0.11f, 0.0f,    R, G, B,
        -0.53f, -0.02f, 0.0f,    R, G, B,
        -0.30f,  0.01f, 0.0f,    R, G, B,

        // t8: J, L, K
        -0.30f,  0.01f, 0.0f,    R, G, B,
        -0.31f,  0.01f, 0.0f,    R, G, B,
        -0.53f, -0.02f, 0.0f,    R, G, B,

        // t9: K, M, L
        -0.53f, -0.02f, 0.0f,    R, G, B,
        -0.34f,  0.01f, 0.0f,    R, G, B,
        -0.31f,  0.01f, 0.0f,    R, G, B,

        // t10: L, N, M
        -0.31f,  0.01f, 0.0f,    R, G, B,
        -0.34f,  0.04f, 0.0f,    R, G, B,
        -0.34f,  0.01f, 0.0f,    R, G, B,

        // t11: M, O, K
        -0.34f,  0.01f, 0.0f,    R, G, B,
        -0.36f,  0.03f, 0.0f,    R, G, B,
        -0.53f, -0.02f, 0.0f,    R, G, B,

        // t12: K, P, O
        -0.53f, -0.02f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,
        -0.36f,  0.03f, 0.0f,    R, G, B,

        // t13: O, Q, P
        -0.36f,  0.03f, 0.0f,    R, G, B,
        -0.38f,  0.05f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t14: P, R, S
        -0.55f, -0.01f, 0.0f,    R, G, B,
        -0.60f,  0.03f, 0.0f,    R, G, B,
        -0.56f,  0.09f, 0.0f,    R, G, B,

        // t15: S, T, U
        -0.56f,  0.09f, 0.0f,    R, G, B,
        -0.56f,  0.11f, 0.0f,    R, G, B,
        -0.54f,  0.09f, 0.0f,    R, G, B,

        // t16: U, P, S
        -0.54f,  0.09f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,
        -0.56f,  0.09f, 0.0f,    R, G, B,

        // t17: Q, V, W
        -0.38f,  0.05f, 0.0f,    R, G, B,
        -0.43f,  0.07f, 0.0f,    R, G, B,
        -0.41f,  0.05f, 0.0f,    R, G, B,

        // t18: W, Z, P
        -0.41f,  0.05f, 0.0f,    R, G, B,
        -0.44f,  0.06f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t19: Z, A1, P
        -0.44f,  0.06f, 0.0f,    R, G, B,
        -0.47f,  0.06f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t20: A1, B1, P
        -0.47f,  0.06f, 0.0f,    R, G, B,
        -0.52f,  0.06f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t21: B1, C1, P
        -0.52f,  0.06f, 0.0f,    R, G, B,
        -0.53f,  0.06f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t22: C1, D1, P
        -0.53f,  0.06f, 0.0f,    R, G, B,
        -0.54f,  0.06f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t23: D1, U, P
        -0.54f,  0.06f, 0.0f,    R, G, B,
        -0.54f,  0.09f, 0.0f,    R, G, B,
        -0.55f, -0.01f, 0.0f,    R, G, B,

        // t24: Q, V, W
        -0.38f, 0.05f, 0.0f, R, G, B,
        -0.55f, -0.01f, 0.0f, R, G, B,
        -0.41f, 0.05f, 0.0f, R, G, B,
    };

#undef R
#undef G
#undef B

    MeshColor* espinilleraIzquierda = new MeshColor();
    espinilleraIzquierda->CreateMeshColor(verticesEspinilleraIzquierda, 432);
    meshColorList.push_back(espinilleraIzquierda); //INDICE 2
}

void CrearPiernas()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MORADO[0]
#define G Colores::MORADO[1]
#define B Colores::MORADO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_Piernas[] = {
        // t1: C, D, E
         0.17f, -0.29f,  0.0f,  R, G, B,
         0.17f, -0.31f,  0.0f,  R, G, B,
         0.19f, -0.30f,  0.0f,  R, G, B,

         // t2: D, F, E
          0.17f, -0.31f,  0.0f,  R, G, B,
          0.17f, -0.32f,  0.0f,  R, G, B,
          0.19f, -0.30f,  0.0f,  R, G, B,

          // t3: F, G, H
           0.17f, -0.32f,  0.0f,  R, G, B,
           0.19f, -0.32f,  0.0f,  R, G, B,
           0.18f, -0.33f,  0.0f,  R, G, B,

           // t4: G, E, F
            0.19f, -0.32f,  0.0f,  R, G, B,
            0.19f, -0.30f,  0.0f,  R, G, B,
            0.17f, -0.32f,  0.0f,  R, G, B,

            // t5: G, I, E
             0.19f, -0.32f,  0.0f,  R, G, B,
             0.20f, -0.30f,  0.0f,  R, G, B,
             0.19f, -0.30f,  0.0f,  R, G, B,

             // t6: I, J, E
              0.20f, -0.30f,  0.0f,  R, G, B,
              0.21f, -0.27f,  0.0f,  R, G, B,
              0.19f, -0.30f,  0.0f,  R, G, B,

              // t7: J, C, E
               0.21f, -0.27f,  0.0f,  R, G, B,
               0.17f, -0.29f,  0.0f,  R, G, B,
               0.19f, -0.30f,  0.0f,  R, G, B,

               // t8: J, K, C
                0.21f, -0.27f,  0.0f,  R, G, B,
                0.22f, -0.25f,  0.0f,  R, G, B,
                0.17f, -0.29f,  0.0f,  R, G, B,

                // t9: K, L, M
                 0.22f, -0.25f,  0.0f,  R, G, B,
                 0.26f, -0.24f,  0.0f,  R, G, B,
                 0.22f, -0.23f,  0.0f,  R, G, B,

                 // t10: C, M, K
                  0.17f, -0.29f,  0.0f,  R, G, B,
                  0.22f, -0.23f,  0.0f,  R, G, B,
                  0.22f, -0.25f,  0.0f,  R, G, B,

                  // t11: C, N, O
                   0.17f, -0.29f,  0.0f,  R, G, B,
                   0.16f, -0.31f,  0.0f,  R, G, B,
                   0.14f, -0.28f,  0.0f,  R, G, B,

                   // t12: N, P, O
                    0.16f, -0.31f,  0.0f,  R, G, B,
                    0.14f, -0.33f,  0.0f,  R, G, B,
                    0.14f, -0.28f,  0.0f,  R, G, B,

                    // t13: P, Q, O
                     0.14f, -0.33f,  0.0f,  R, G, B,
                     0.13f, -0.34f,  0.0f,  R, G, B,
                     0.14f, -0.28f,  0.0f,  R, G, B,

                     // t14: Q, R, S
                      0.13f, -0.34f,  0.0f,  R, G, B,
                      0.13f, -0.35f,  0.0f,  R, G, B,
                      0.04f, -0.29f,  0.0f,  R, G, B,

                      // t15: M, T, C
                       0.22f, -0.23f,  0.0f,  R, G, B,
                       0.19f, -0.20f,  0.0f,  R, G, B,
                       0.17f, -0.29f,  0.0f,  R, G, B,

                       // t16: T, U, C
                        0.19f, -0.20f,  0.0f,  R, G, B,
                        0.18f, -0.17f,  0.0f,  R, G, B,
                        0.17f, -0.29f,  0.0f,  R, G, B,

                        // t17: O, U, C
                         0.14f, -0.28f,  0.0f,  R, G, B,
                         0.18f, -0.17f,  0.0f,  R, G, B,
                         0.17f, -0.29f,  0.0f,  R, G, B,

                         // t18: O, S, Q
                          0.14f, -0.28f,  0.0f,  R, G, B,
                          0.04f, -0.29f,  0.0f,  R, G, B,
                          0.13f, -0.34f,  0.0f,  R, G, B,

                          // t19: S, V, O
                           0.04f, -0.29f,  0.0f,  R, G, B,
                           0.02f, -0.28f,  0.0f,  R, G, B,
                           0.14f, -0.28f,  0.0f,  R, G, B,

                           // t20: V, W, U
                            0.02f, -0.28f,  0.0f,  R, G, B,
                            0.00f, -0.26f,  0.0f,  R, G, B,
                            0.18f, -0.17f,  0.0f,  R, G, B,

                            // t21: O, U, V
                             0.14f, -0.28f,  0.0f,  R, G, B,
                             0.18f, -0.17f,  0.0f,  R, G, B,
                             0.02f, -0.28f,  0.0f,  R, G, B,

                             // t22: U, Z, W
                              0.18f, -0.17f,  0.0f,  R, G, B,
                              0.13f, -0.14f,  0.0f,  R, G, B,
                              0.00f, -0.26f,  0.0f,  R, G, B,

                              // t23: W, A1, Z
                               0.00f, -0.26f,  0.0f,  R, G, B,
                              -0.08f, -0.18f,  0.0f,  R, G, B,
                               0.13f, -0.14f,  0.0f,  R, G, B,

                               // t24: Z, B1, A1
                                0.13f, -0.14f,  0.0f,  R, G, B,
                                0.09f, -0.05f,  0.0f,  R, G, B,
                               -0.08f, -0.18f,  0.0f,  R, G, B,

                               // t25: A1, C1, B1
                               -0.08f, -0.18f,  0.0f,  R, G, B,
                               -0.07f, -0.13f,  0.0f,  R, G, B,
                                0.09f, -0.05f,  0.0f,  R, G, B,

                                // t26: C1, D1, A1
                                -0.07f, -0.13f,  0.0f,  R, G, B,
                                -0.08f, -0.13f,  0.0f,  R, G, B,
                                -0.08f, -0.18f,  0.0f,  R, G, B,

                                // t27: C1, E1, B1
                                -0.07f, -0.13f,  0.0f,  R, G, B,
                                -0.07f, -0.03f,  0.0f,  R, G, B,
                                 0.09f, -0.05f,  0.0f,  R, G, B,

                                 // t28: B1, F1, E1
                                  0.09f, -0.05f,  0.0f,  R, G, B,
                                  0.00f,  0.07f,  0.0f,  R, G, B,
                                 -0.07f, -0.03f,  0.0f,  R, G, B,

                                 // t29: E1, G1, F1
                                 -0.07f, -0.03f,  0.0f,  R, G, B,
                                 -0.11f, -0.02f,  0.0f,  R, G, B,
                                  0.00f,  0.07f,  0.0f,  R, G, B,

                                  // t30: F1, H1, G1
                                   0.00f,  0.07f,  0.0f,  R, G, B,
                                   0.01f,  0.12f,  0.0f,  R, G, B,
                                  -0.11f, -0.02f,  0.0f,  R, G, B,

                                  // t31: G1, I1, J1
                                  -0.11f, -0.02f,  0.0f,  R, G, B,
                                  -0.16f, -0.02f,  0.0f,  R, G, B,
                                  -0.14f,  0.02f,  0.0f,  R, G, B,

                                  // t32: I1, K1, J1
                                  -0.16f, -0.02f,  0.0f,  R, G, B,
                                  -0.19f, -0.03f,  0.0f,  R, G, B,
                                  -0.14f,  0.02f,  0.0f,  R, G, B,

                                  // t33: K1, L1, M1
                                  -0.19f, -0.03f,  0.0f,  R, G, B,
                                  -0.21f, -0.04f,  0.0f,  R, G, B,
                                  -0.25f,  0.01f,  0.0f,  R, G, B,

                                  // t34: J1, M1, K1
                                  -0.14f,  0.02f,  0.0f,  R, G, B,
                                  -0.25f,  0.01f,  0.0f,  R, G, B,
                                  -0.19f, -0.03f,  0.0f,  R, G, B,

                                  // t35: M1, N1, O1
                                  -0.25f,  0.01f,  0.0f,  R, G, B,
                                  -0.30f,  0.00f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,

                                  // t36: N1, P1, O1
                                  -0.30f,  0.00f,  0.0f,  R, G, B,
                                  -0.31f,  0.01f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,

                                  // t37: P1, Q1, O1
                                  -0.31f,  0.01f,  0.0f,  R, G, B,
                                  -0.33f,  0.03f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,

                                  // t38: Q1, R1, O1
                                  -0.33f,  0.03f,  0.0f,  R, G, B,
                                  -0.34f,  0.03f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,

                                  // t39: R1, S1, T1
                                  -0.34f,  0.03f,  0.0f,  R, G, B,
                                  -0.33f,  0.01f,  0.0f,  R, G, B,
                                  -0.34f,  0.01f,  0.0f,  R, G, B,

                                  // t40: T1, U1, R1
                                  -0.34f,  0.01f,  0.0f,  R, G, B,
                                  -0.38f,  0.05f,  0.0f,  R, G, B,
                                  -0.34f,  0.03f,  0.0f,  R, G, B,

                                  // t41: U1, V1, O1
                                  -0.38f,  0.05f,  0.0f,  R, G, B,
                                  -0.42f,  0.07f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,

                                  // t42: R1, O1, U1
                                  -0.34f,  0.03f,  0.0f,  R, G, B,
                                  -0.28f,  0.04f,  0.0f,  R, G, B,
                                  -0.38f,  0.05f,  0.0f,  R, G, B,

                                  // t43: V1, W1, Z1
                                  -0.42f,  0.07f,  0.0f,  R, G, B,
                                  -0.41f,  0.05f,  0.0f,  R, G, B,
                                  -0.44f,  0.06f,  0.0f,  R, G, B,

                                  // t44: Z1, A2, V1
                                  -0.44f,  0.06f,  0.0f,  R, G, B,
                                  -0.48f,  0.06f,  0.0f,  R, G, B,
                                  -0.42f,  0.07f,  0.0f,  R, G, B,

                                  // t45: A2, B2, C2
                                  -0.48f,  0.06f,  0.0f,  R, G, B,
                                  -0.52f,  0.06f,  0.0f,  R, G, B,
                                  -0.50f,  0.10f,  0.0f,  R, G, B,

                                  // t46: B2, D2, C2
                                  -0.52f,  0.06f,  0.0f,  R, G, B,
                                  -0.54f,  0.06f,  0.0f,  R, G, B,
                                  -0.50f,  0.10f,  0.0f,  R, G, B,
                                   
                                    // t47: D2, E2, C2
                                    -0.54f, 0.06f, 0.0f, R, G, B,
                                    -0.54f, 0.06f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,

                                    // t48: E2, F2, C2
                                    -0.54f, 0.06f, 0.0f, R, G, B,
                                    -0.54f, 0.08f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,

                                    // t49: F2, G2, C2
                                    -0.54f, 0.08f, 0.0f, R, G, B,
                                    -0.55f, 0.09f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,

                                    // t50: G2, H2, C2
                                    -0.55f, 0.09f, 0.0f, R, G, B,
                                    -0.55f, 0.11f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,

                                    // t51: I2, J2, K2
                                    -0.60f, 0.03f, 0.0f, R, G, B,
                                    -0.61f, 0.04f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t52: J2, L2, K2
                                    -0.61f, 0.04f, 0.0f, R, G, B,
                                    -0.62f, 0.06f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t53: L2, M2, K2
                                    -0.62f, 0.06f, 0.0f, R, G, B,
                                    -0.62f, 0.07f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t54: M2, N2, K2
                                    -0.62f, 0.07f, 0.0f, R, G, B,
                                    -0.61f, 0.10f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t55: N2, O2, K2
                                    -0.61f, 0.10f, 0.0f, R, G, B,
                                    -0.59f, 0.12f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t56: O2, P2, K2
                                    -0.59f, 0.12f, 0.0f, R, G, B,
                                    -0.57f, 0.14f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t57: P2, H2, K2
                                    -0.57f, 0.14f, 0.0f, R, G, B,
                                    -0.55f, 0.11f, 0.0f, R, G, B,
                                    -0.58f, 0.05f, 0.0f, R, G, B,

                                    // t58: P2, Q2, H2
                                    -0.57f, 0.14f, 0.0f, R, G, B,
                                    -0.42f, 0.21f, 0.0f, R, G, B,
                                    -0.55f, 0.11f, 0.0f, R, G, B,

                                    // t59: H2, O1, Q2
                                    -0.55f, 0.11f, 0.0f, R, G, B,
                                    -0.28f, 0.04f, 0.0f, R, G, B,
                                    -0.42f, 0.21f, 0.0f, R, G, B,

                                    // t60: V1, C2, A2
                                    -0.42f, 0.07f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,
                                    -0.48f, 0.06f, 0.0f, R, G, B,

                                    // t61: V1, C2, O1
                                    -0.42f, 0.07f, 0.0f, R, G, B,
                                    -0.50f, 0.10f, 0.0f, R, G, B,
                                    -0.28f, 0.04f, 0.0f, R, G, B,

                                    // t62: Q2, R2, O1
                                    -0.42f, 0.21f, 0.0f, R, G, B,
                                    -0.31f, 0.21f, 0.0f, R, G, B,
                                    -0.28f, 0.04f, 0.0f, R, G, B,

                                    // t63: R2, J1, O1
                                    -0.31f, 0.21f, 0.0f, R, G, B,
                                    -0.14f, 0.02f, 0.0f, R, G, B,
                                    -0.28f, 0.04f, 0.0f, R, G, B,

                                    // t64: J1, M1, O1
                                    -0.14f, 0.02f, 0.0f, R, G, B,
                                    -0.25f, 0.01f, 0.0f, R, G, B,
                                    -0.28f, 0.04f, 0.0f, R, G, B,

                                    // t65: R2, H1, G1
                                    -0.31f, 0.21f, 0.0f, R, G, B,
                                    0.01f, 0.12f, 0.0f, R, G, B,
                                    -0.11f, -0.02f, 0.0f, R, G, B,

                                    // t66: H1, S2, T2
                                    0.01f, 0.12f, 0.0f, R, G, B,
                                    -0.04f, 0.18f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t67: S2, U2, T2
                                    -0.04f, 0.18f, 0.0f, R, G, B,
                                    -0.08f, 0.22f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t68: U2, V2, T2
                                    -0.08f, 0.22f, 0.0f, R, G, B,
                                    -0.15f, 0.24f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t69: V2, W2, T2
                                    -0.15f, 0.24f, 0.0f, R, G, B,
                                    -0.20f, 0.25f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t70: W2, Z2, T2
                                    -0.20f, 0.25f, 0.0f, R, G, B,
                                    -0.24f, 0.24f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t71: Z2, A3, T2
                                    -0.24f, 0.24f, 0.0f, R, G, B,
                                    -0.26f, 0.20f, 0.0f, R, G, B,
                                    -0.15f, 0.17f, 0.0f, R, G, B,

                                    // t72: 
                                    -0.25f, 0.21f, 0.0f, R, G, B,
                                    -0.26f, 0.19f, 0.0f, R, G, B,
                                     0.01f, 0.11f, 0.0f, R, G, B,

                                    // t73: 
                                    -0.24f, 0.24f, 0.0f, R, G, B,
                                    -0.25f, 0.21f, 0.0f, R, G, B,
                                    0.01f, 0.12f, 0.0f, R, G, B,
                                   
                                    // t74: 
                                    -0.02f, 0.09f, 0.0f, R, G, B,
                                    -0.01f, 0.14f, 0.0f, R, G, B,
                                    -0.22f, 0.22f, 0.0f, R, G, B,


    };

#undef R
#undef G
#undef B

    MeshColor* piernas = new MeshColor();
    piernas->CreateMeshColor(vertices_Piernas, 1332); 
    meshColorList.push_back(piernas);
}

void CrearCinturon()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MORADO_CINTURON[0]
#define G Colores::MORADO_CINTURON[1]
#define B Colores::MORADO_CINTURON[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_cinturon[] = {
        // t1: C, D, E
0.01f, 0.11f, 0.0f, R, G, B,
-0.03f, 0.17f, 0.0f, R, G, B,
0.02f, 0.13f, 0.0f, R, G, B,

// t2: E, F, D
0.02f, 0.13f, 0.0f, R, G, B,
0.03f, 0.16f, 0.0f, R, G, B,
-0.03f, 0.17f, 0.0f, R, G, B,

// t3: F, G, D
0.03f, 0.16f, 0.0f, R, G, B,
0.01f, 0.19f, 0.0f, R, G, B,
-0.03f, 0.17f, 0.0f, R, G, B,

// t4: G, H, D
0.01f, 0.19f, 0.0f, R, G, B,
-0.07f, 0.26f, 0.0f, R, G, B,
-0.03f, 0.17f, 0.0f, R, G, B,

// t5: D, I, H
-0.03f, 0.17f, 0.0f, R, G, B,
-0.10f, 0.22f, 0.0f, R, G, B,
-0.07f, 0.26f, 0.0f, R, G, B,

// t6: I, J, H
-0.10f, 0.22f, 0.0f, R, G, B,
-0.16f, 0.24f, 0.0f, R, G, B,
-0.07f, 0.26f, 0.0f, R, G, B,

// t7: H, K, J
-0.07f, 0.26f, 0.0f, R, G, B,
-0.10f, 0.28f, 0.0f, R, G, B,
-0.16f, 0.24f, 0.0f, R, G, B,

// t8: K, L, J
-0.10f, 0.28f, 0.0f, R, G, B,
-0.16f, 0.30f, 0.0f, R, G, B,
-0.16f, 0.24f, 0.0f, R, G, B,

// t9: J, M, L
-0.16f, 0.24f, 0.0f, R, G, B,
-0.19f, 0.24f, 0.0f, R, G, B,
-0.16f, 0.30f, 0.0f, R, G, B,

// t10: M, N, L
-0.19f, 0.24f, 0.0f, R, G, B,
-0.26f, 0.24f, 0.0f, R, G, B,
-0.16f, 0.30f, 0.0f, R, G, B,

// t11: N, O, L
-0.26f, 0.24f, 0.0f, R, G, B,
-0.25f, 0.26f, 0.0f, R, G, B,
-0.16f, 0.30f, 0.0f, R, G, B,

// t12: L, P, O
-0.16f, 0.30f, 0.0f, R, G, B,
-0.19f, 0.30f, 0.0f, R, G, B,
-0.25f, 0.26f, 0.0f, R, G, B,

// t13: O, Q, N
-0.25f, 0.26f, 0.0f, R, G, B,
-0.26f, 0.25f, 0.0f, R, G, B,
-0.26f, 0.24f, 0.0f, R, G, B,

    };

#undef R
#undef G
#undef B

    MeshColor* cinturon = new MeshColor();
    cinturon->CreateMeshColor(vertices_cinturon, 1278);
    meshColorList.push_back(cinturon);
}

void CrearTorso()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MORADO[0]
#define G Colores::MORADO[1]
#define B Colores::MORADO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_torso[] = {
        // t1: C, D, E[cite: 31]
         0.02f,  0.17f, 0.0f, R, G, B,
         0.02f,  0.25f, 0.0f, R, G, B,
        -0.08f,  0.26f, 0.0f, R, G, B,

        // t2: D, F, G[cite: 31]
         0.02f,  0.25f, 0.0f, R, G, B,
         0.05f,  0.21f, 0.0f, R, G, B,
         0.06f,  0.37f, 0.0f, R, G, B,

         // t3: F, H, G[cite: 31]
          0.05f,  0.21f, 0.0f, R, G, B,
          0.06f,  0.22f, 0.0f, R, G, B,
          0.06f,  0.37f, 0.0f, R, G, B,

          // t4: G, I, H[cite: 31]
           0.06f,  0.37f, 0.0f, R, G, B,
           0.11f,  0.35f, 0.0f, R, G, B,
           0.06f,  0.22f, 0.0f, R, G, B,

           // t5: I, J, H[cite: 31]
            0.11f,  0.35f, 0.0f, R, G, B,
            0.14f,  0.34f, 0.0f, R, G, B,
            0.06f,  0.22f, 0.0f, R, G, B,

            // t6: H, K, J[cite: 31]
             0.06f,  0.22f, 0.0f, R, G, B,
             0.07f,  0.21f, 0.0f, R, G, B,
             0.14f,  0.34f, 0.0f, R, G, B,

             // t7: K, L, J[cite: 31]
              0.07f,  0.21f, 0.0f, R, G, B,
              0.09f,  0.20f, 0.0f, R, G, B,
              0.14f,  0.34f, 0.0f, R, G, B,

              // t8: L, M, J[cite: 31]
               0.09f,  0.20f, 0.0f, R, G, B,
               0.11f,  0.21f, 0.0f, R, G, B,
               0.14f,  0.34f, 0.0f, R, G, B,

               // t9: E, N, G[cite: 31]
               -0.08f,  0.26f, 0.0f, R, G, B,
               -0.14f,  0.29f, 0.0f, R, G, B,
                0.06f,  0.37f, 0.0f, R, G, B,

                // t10: D, G, E[cite: 31]
                 0.02f,  0.25f, 0.0f, R, G, B,
                 0.06f,  0.37f, 0.0f, R, G, B,
                -0.08f,  0.26f, 0.0f, R, G, B,

                // t11: N, O, P[cite: 31]
                -0.14f,  0.29f, 0.0f, R, G, B,
                -0.18f,  0.29f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,

                // t12: G, Q, N[cite: 31]
                 0.06f,  0.37f, 0.0f, R, G, B,
                 0.02f,  0.37f, 0.0f, R, G, B,
                -0.14f,  0.29f, 0.0f, R, G, B,

                // t13: Q, P, N[cite: 31]
                 0.02f,  0.37f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,
                -0.14f,  0.29f, 0.0f, R, G, B,

                // t14: O, R, S[cite: 31]
                -0.18f,  0.29f, 0.0f, R, G, B,
                -0.21f,  0.28f, 0.0f, R, G, B,
                -0.23f,  0.35f, 0.0f, R, G, B,

                // t15: S, T, O[cite: 31]
                -0.23f,  0.35f, 0.0f, R, G, B,
                -0.17f,  0.31f, 0.0f, R, G, B,
                -0.18f,  0.29f, 0.0f, R, G, B,

                // t16: U, V, T[cite: 31]
                -0.19f,  0.32f, 0.0f, R, G, B,
                -0.16f,  0.32f, 0.0f, R, G, B,
                -0.17f,  0.31f, 0.0f, R, G, B,

                // t17: W, Z, P[cite: 31]
                -0.18f,  0.32f, 0.0f, R, G, B,
                -0.19f,  0.35f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,

                // t18: V, W, P[cite: 31]
                -0.16f,  0.32f, 0.0f, R, G, B,
                -0.18f,  0.32f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,

                // t19: Z, A1, P[cite: 31]
                -0.19f,  0.35f, 0.0f, R, G, B,
                -0.19f,  0.37f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,

                // t20: A1, B1, P[cite: 31]
                -0.19f,  0.37f, 0.0f, R, G, B,
                -0.19f,  0.38f, 0.0f, R, G, B,
                -0.06f,  0.40f, 0.0f, R, G, B,

                // t21: P, C1, B1[cite: 31]
                -0.06f,  0.40f, 0.0f, R, G, B,
                -0.06f,  0.42f, 0.0f, R, G, B,
                -0.19f,  0.38f, 0.0f, R, G, B,

                // t22: B1, D1, C1[cite: 31]
                -0.19f,  0.38f, 0.0f, R, G, B,
                -0.16f,  0.42f, 0.0f, R, G, B,
                -0.06f,  0.42f, 0.0f, R, G, B,

                // t23: C1, E1, D1[cite: 31]
                -0.06f,  0.42f, 0.0f, R, G, B,
                -0.07f,  0.46f, 0.0f, R, G, B,
                -0.16f,  0.42f, 0.0f, R, G, B,

                // t24: D1, F1, E1[cite: 31]
                -0.16f,  0.42f, 0.0f, R, G, B,
                -0.15f,  0.47f, 0.0f, R, G, B,
                -0.07f,  0.46f, 0.0f, R, G, B,

                // t25: F1, G1, H1[cite: 31]
                -0.15f,  0.47f, 0.0f, R, G, B,
                -0.16f,  0.45f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t26: G1, I1, H1[cite: 31]
                -0.16f,  0.45f, 0.0f, R, G, B,
                -0.17f,  0.44f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t27: I1, J1, H1[cite: 31]
                -0.17f,  0.44f, 0.0f, R, G, B,
                -0.21f,  0.44f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t28: J1, K1, H1[cite: 31]
                -0.21f,  0.44f, 0.0f, R, G, B,
                -0.21f,  0.45f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t29: K1, L1, H1[cite: 31]
                -0.21f,  0.45f, 0.0f, R, G, B,
                -0.20f,  0.48f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t30: L1, F1, H1[cite: 31]
                -0.20f,  0.48f, 0.0f, R, G, B,
                -0.15f,  0.47f, 0.0f, R, G, B,
                -0.18f,  0.47f, 0.0f, R, G, B,

                // t31: L1, M1, E1[cite: 31]
                -0.20f,  0.48f, 0.0f, R, G, B,
                -0.13f,  0.52f, 0.0f, R, G, B,
                -0.07f,  0.46f, 0.0f, R, G, B,

                // t32: M1, N1, O1[cite: 31]
                -0.13f,  0.52f, 0.0f, R, G, B,
                -0.12f,  0.54f, 0.0f, R, G, B,
                -0.07f,  0.53f, 0.0f, R, G, B,

                // t33: E1, O1, M1[cite: 31]
                -0.07f,  0.46f, 0.0f, R, G, B,
                -0.07f,  0.53f, 0.0f, R, G, B,
                -0.13f,  0.52f, 0.0f, R, G, B,

                // t34: E1, P1, O1[cite: 31]
                -0.07f,  0.46f, 0.0f, R, G, B,
                -0.04f,  0.50f, 0.0f, R, G, B,
                -0.07f,  0.53f, 0.0f, R, G, B,

                // t35: N1, Q1, R1[cite: 31]
                -0.12f,  0.54f, 0.0f, R, G, B,
                -0.16f,  0.55f, 0.0f, R, G, B,
                -0.11f,  0.59f, 0.0f, R, G, B,

                // t36: R1, S1, O1[cite: 31]
                -0.11f,  0.59f, 0.0f, R, G, B,
                -0.04f,  0.63f, 0.0f, R, G, B,
                -0.07f,  0.53f, 0.0f, R, G, B,

                // t37: O1, N1, R1[cite: 31]
                -0.07f,  0.53f, 0.0f, R, G, B,
                -0.12f,  0.54f, 0.0f, R, G, B,
                -0.11f,  0.59f, 0.0f, R, G, B,

                // t38: S1, T1, U1[cite: 31]
                -0.04f,  0.63f, 0.0f, R, G, B,
                 0.04f,  0.65f, 0.0f, R, G, B,
                 0.04f,  0.60f, 0.0f, R, G, B,

                 // t39: O1, U1, S1[cite: 31]
                 -0.07f,  0.53f, 0.0f, R, G, B,
                  0.04f,  0.60f, 0.0f, R, G, B,
                 -0.04f,  0.63f, 0.0f, R, G, B,

                 // t40: P1, U1, O1[cite: 31]
                 -0.04f,  0.50f, 0.0f, R, G, B,
                  0.04f,  0.60f, 0.0f, R, G, B,
                 -0.07f,  0.53f, 0.0f, R, G, B,

                 // t41: P1, V1, U1[cite: 31]
                 -0.04f,  0.50f, 0.0f, R, G, B,
                  0.00f,  0.53f, 0.0f, R, G, B,
                  0.04f,  0.60f, 0.0f, R, G, B,

                  // t42: V1, W1, U1[cite: 31]
                   0.00f,  0.53f, 0.0f, R, G, B,
                   0.02f,  0.53f, 0.0f, R, G, B,
                   0.04f,  0.60f, 0.0f, R, G, B,

                   // t43: W1, Z1, U1[cite: 31]
                    0.02f,  0.53f, 0.0f, R, G, B,
                    0.07f,  0.50f, 0.0f, R, G, B,
                    0.04f,  0.60f, 0.0f, R, G, B,

                    // t44: U1, A2, Z1[cite: 31]
                     0.04f,  0.60f, 0.0f, R, G, B,
                     0.13f,  0.58f, 0.0f, R, G, B,
                     0.07f,  0.50f, 0.0f, R, G, B,

                     // t45: A2, B2, Z1[cite: 31]
                      0.13f,  0.58f, 0.0f, R, G, B,
                      0.16f,  0.56f, 0.0f, R, G, B,
                      0.07f,  0.50f, 0.0f, R, G, B,

                    // t46: Z1, C2, B2
                    0.07f, 0.50f, 0.0f, R, G, B,
                    0.07f, 0.46f, 0.0f, R, G, B,
                    0.16f, 0.56f, 0.0f, R, G, B,

                    // t47: C2, D2, B2
                    0.07f, 0.46f, 0.0f, R, G, B,
                    0.09f, 0.46f, 0.0f, R, G, B,
                    0.16f, 0.56f, 0.0f, R, G, B,

                    // t48: D2, E2, B2
                    0.09f, 0.46f, 0.0f, R, G, B,
                    0.12f, 0.47f, 0.0f, R, G, B,
                    0.16f, 0.56f, 0.0f, R, G, B,

                    // t49: E2, F2, B2
                    0.12f, 0.47f, 0.0f, R, G, B,
                    0.18f, 0.49f, 0.0f, R, G, B,
                    0.16f, 0.56f, 0.0f, R, G, B,

                    // t50: F2, G2, B2
                    0.18f, 0.49f, 0.0f, R, G, B,
                    0.21f, 0.49f, 0.0f, R, G, B,
                    0.16f, 0.56f, 0.0f, R, G, B,

                    // t51: G2, H2, I2
                    0.21f, 0.49f, 0.0f, R, G, B,
                    0.27f, 0.48f, 0.0f, R, G, B,
                    0.26f, 0.50f, 0.0f, R, G, B,

                    // t52: I2, J2, G2
                    0.26f, 0.50f, 0.0f, R, G, B,
                    0.22f, 0.52f, 0.0f, R, G, B,
                    0.21f, 0.49f, 0.0f, R, G, B,

                    // t53: J2, K2, G2
                    0.22f, 0.52f, 0.0f, R, G, B,
                    0.18f, 0.53f, 0.0f, R, G, B,
                    0.21f, 0.49f, 0.0f, R, G, B,

                    // t54: J2, K2, G2
                    -0.18f, 0.3f, 0.0f, R, G, B,
                    -0.04f, 0.29f, 0.0f, R, G, B,
                    -0.07f, 0.44f, 0.0f, R, G, B,

                    // t55: J2, K2, G2
                    -0.07f, 0.45f, 0.0f, R, G, B,
                    -0.06f, 0.48f, 0.0f, R, G, B,
                    -0.15f, 0.51f, 0.0f, R, G, B,

                    // t56: J2, K2, G2
                    -0.07f, 0.45f, 0.0f, R, G, B,
                    -0.15f, 0.51f, 0.0f, R, G, B,
                    -0.19f, 0.48f, 0.0f, R, G, B,

                    // t56: J2, K2, G2
                    -0.17f, 0.46f, 0.0f, R, G, B,
                    -0.12f, 0.48f, 0.0f, R, G, B,
                    -0.19f, 0.49f, 0.0f, R, G, B,

                    // t57: J2, K2, G2
                    -0.18f, 0.49f, 0.0f, R, G, B,
                    -0.14f, 0.47f, 0.0f, R, G, B,
                    -0.2f, 0.47f, 0.0f, R, G, B,
    };

#undef R
#undef G
#undef B

    MeshColor* torso = new MeshColor();
    torso->CreateMeshColor(vertices_torso, 1026);
    meshColorList.push_back(torso);
}
void CrearBufanda()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::DORADO[0]
#define G Colores::DORADO[1]
#define B Colores::DORADO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_bufanda[] = {
        // t1: C, D, E
        -0.19f,  0.35f, 0.0f, R, G, B,
        -0.18f,  0.32f, 0.0f, R, G, B,
        -0.21f,  0.33f, 0.0f, R, G, B,

        // t2: C, F, G
        -0.19f,  0.35f, 0.0f, R, G, B,
        -0.18f,  0.37f, 0.0f, R, G, B,
        -0.19f,  0.38f, 0.0f, R, G, B,

        // t3: G, H, I
        -0.19f,  0.38f, 0.0f, R, G, B,
        -0.17f,  0.41f, 0.0f, R, G, B,
        -0.20f,  0.41f, 0.0f, R, G, B,

        // t4: H, J, I
        -0.17f,  0.41f, 0.0f, R, G, B,
        -0.16f,  0.44f, 0.0f, R, G, B,
        -0.20f,  0.41f, 0.0f, R, G, B,

        // t5: J, K, L
        -0.15f,  0.44f, 0.0f, R, G, B,
        -0.15f,  0.47f, 0.0f, R, G, B,
        -0.17f,  0.45f, 0.0f, R, G, B,

        // t6: L, M, J
        -0.17f,  0.45f, 0.0f, R, G, B,
        -0.18f,  0.44f, 0.0f, R, G, B,
        -0.16f,  0.44f, 0.0f, R, G, B,

        // t7: M, I, J
        -0.18f,  0.44f, 0.0f, R, G, B,
        -0.20f,  0.41f, 0.0f, R, G, B,
        -0.15f,  0.44f, 0.0f, R, G, B,

        // t8: M, N, I
        -0.18f,  0.44f, 0.0f, R, G, B,
        -0.22f,  0.44f, 0.0f, R, G, B,
        -0.20f,  0.41f, 0.0f, R, G, B,

        // t9: E, O, C
        -0.21f,  0.33f, 0.0f, R, G, B,
        -0.24f,  0.35f, 0.0f, R, G, B,
        -0.19f,  0.35f, 0.0f, R, G, B,

        // t10: G, O, C
        -0.19f,  0.38f, 0.0f, R, G, B,
        -0.24f,  0.35f, 0.0f, R, G, B,
        -0.19f,  0.35f, 0.0f, R, G, B,

        // t11: O, P, G
        -0.24f,  0.35f, 0.0f, R, G, B,
        -0.26f,  0.38f, 0.0f, R, G, B,
        -0.19f,  0.38f, 0.0f, R, G, B,

        // t12: P, Q, G
        -0.26f,  0.38f, 0.0f, R, G, B,
        -0.26f,  0.41f, 0.0f, R, G, B,
        -0.19f,  0.38f, 0.0f, R, G, B,

        // t13: I, Q, G
        -0.20f,  0.41f, 0.0f, R, G, B,
        -0.26f,  0.41f, 0.0f, R, G, B,
        -0.19f,  0.38f, 0.0f, R, G, B,

        // t14: Q, N, I
        -0.26f,  0.41f, 0.0f, R, G, B,
        -0.22f,  0.44f, 0.0f, R, G, B,
        -0.20f,  0.41f, 0.0f, R, G, B,

        // t15: Q, R, N
        -0.26f,  0.41f, 0.0f, R, G, B,
        -0.24f,  0.48f, 0.0f, R, G, B,
        -0.22f,  0.44f, 0.0f, R, G, B,

        // t16: N, S, T
        -0.22f,  0.44f, 0.0f, R, G, B,
        -0.19f,  0.50f, 0.0f, R, G, B,
        -0.22f,  0.49f, 0.0f, R, G, B,

        // t17: T, R, N
        -0.22f,  0.49f, 0.0f, R, G, B,
        -0.24f,  0.48f, 0.0f, R, G, B,
        -0.22f,  0.44f, 0.0f, R, G, B,

        // t18: S, U, V
        -0.19f,  0.50f, 0.0f, R, G, B,
        -0.15f,  0.52f, 0.0f, R, G, B,
        -0.16f,  0.50f, 0.0f, R, G, B,

        // t19: S, W, V
        -0.19f,  0.50f, 0.0f, R, G, B,
        -0.20f,  0.47f, 0.0f, R, G, B,
        -0.16f,  0.50f, 0.0f, R, G, B,

        // t20: V, Z, U
        -0.16f,  0.50f, 0.0f, R, G, B,
        -0.13f,  0.52f, 0.0f, R, G, B,
        -0.15f,  0.52f, 0.0f, R, G, B,

        // t21: Z, A1, U
        -0.13f,  0.52f, 0.0f, R, G, B,
        -0.13f,  0.54f, 0.0f, R, G, B,
        -0.15f,  0.52f, 0.0f, R, G, B,

        // t22: U, B1, A1
        -0.15f,  0.52f, 0.0f, R, G, B,
        -0.16f,  0.55f, 0.0f, R, G, B,
        -0.13f,  0.54f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* bufanda = new MeshColor();
    bufanda->CreateMeshColor(vertices_bufanda, 396);
    meshColorList.push_back(bufanda);
}

void CrearCoderaExterna()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MARRON_CODERA[0]
#define G Colores::MARRON_CODERA[1]
#define B Colores::MARRON_CODERA[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_coderaExterna[] = {
        // t1: C, D, E
        0.27f, 0.49f, 0.0f, R, G, B,
        0.32f, 0.47f, 0.0f, R, G, B,
        0.30f, 0.47f, 0.0f, R, G, B,

        // t2: D, F, E
        0.32f, 0.47f, 0.0f, R, G, B,
        0.35f, 0.42f, 0.0f, R, G, B,
        0.30f, 0.47f, 0.0f, R, G, B,

        // t3: F, G, E
        0.35f, 0.42f, 0.0f, R, G, B,
        0.33f, 0.43f, 0.0f, R, G, B,
        0.30f, 0.47f, 0.0f, R, G, B,

        // t4: F, H, I
        0.35f, 0.42f, 0.0f, R, G, B,
        0.36f, 0.36f, 0.0f, R, G, B,
        0.34f, 0.41f, 0.0f, R, G, B,

        // t5: I, G, F
        0.34f, 0.41f, 0.0f, R, G, B,
        0.33f, 0.43f, 0.0f, R, G, B,
        0.35f, 0.42f, 0.0f, R, G, B,

        // t6: H, J, I
        0.36f, 0.36f, 0.0f, R, G, B,
        0.34f, 0.36f, 0.0f, R, G, B,
        0.34f, 0.41f, 0.0f, R, G, B,

        // t7: J, K, H
        0.34f, 0.36f, 0.0f, R, G, B,
        0.33f, 0.34f, 0.0f, R, G, B,
        0.36f, 0.36f, 0.0f, R, G, B,

        // t8: H, L, K
        0.36f, 0.36f, 0.0f, R, G, B,
        0.34f, 0.33f, 0.0f, R, G, B,
        0.33f, 0.34f, 0.0f, R, G, B,

        // t9: L, M, K
        0.34f, 0.33f, 0.0f, R, G, B,
        0.31f, 0.32f, 0.0f, R, G, B,
        0.33f, 0.34f, 0.0f, R, G, B,

        // t10: M, N, K
        0.31f, 0.32f, 0.0f, R, G, B,
        0.27f, 0.33f, 0.0f, R, G, B,
        0.33f, 0.34f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* coderaExt = new MeshColor();
    coderaExt->CreateMeshColor(vertices_coderaExterna, 180);
    meshColorList.push_back(coderaExt);
}

void CrearCoderaInterna()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MARRON_CODERA_INT[0]
#define G Colores::MARRON_CODERA_INT[1]
#define B Colores::MARRON_CODERA_INT[2]

    GLfloat vertices_coderaInterna[] = {
        // t1: C, D, E
        0.33f, 0.43f, 0.0f, R, G, B,
        0.34f, 0.42f, 0.0f, R, G, B,
        0.35f, 0.39f, 0.0f, R, G, B,

        // t2: E, F, C
        0.35f, 0.39f, 0.0f, R, G, B,
        0.35f, 0.36f, 0.0f, R, G, B,
        0.33f, 0.43f, 0.0f, R, G, B,

        // t3: C, G, E
        0.33f, 0.43f, 0.0f, R, G, B,
        0.30f, 0.41f, 0.0f, R, G, B,
        0.35f, 0.39f, 0.0f, R, G, B,

        // t4: G, H, I
        0.30f, 0.41f, 0.0f, R, G, B,
        0.28f, 0.39f, 0.0f, R, G, B,
        0.32f, 0.39f, 0.0f, R, G, B,

        // t5: I, E, G
        0.32f, 0.39f, 0.0f, R, G, B,
        0.35f, 0.39f, 0.0f, R, G, B,
        0.30f, 0.41f, 0.0f, R, G, B,

        // t6: H, J, K
        0.28f, 0.39f, 0.0f, R, G, B,
        0.25f, 0.34f, 0.0f, R, G, B,
        0.27f, 0.33f, 0.0f, R, G, B,

        // t7: I, K, H
        0.32f, 0.39f, 0.0f, R, G, B,
        0.27f, 0.33f, 0.0f, R, G, B,
        0.28f, 0.39f, 0.0f, R, G, B,

        // t8: K, L, I
        0.27f, 0.33f, 0.0f, R, G, B,
        0.30f, 0.33f, 0.0f, R, G, B,
        0.32f, 0.39f, 0.0f, R, G, B,

        // t9: L, M, I
        0.30f, 0.33f, 0.0f, R, G, B,
        0.33f, 0.34f, 0.0f, R, G, B,
        0.32f, 0.39f, 0.0f, R, G, B,

        // t10: M, F, I
        0.33f, 0.34f, 0.0f, R, G, B,
        0.35f, 0.36f, 0.0f, R, G, B,
        0.32f, 0.39f, 0.0f, R, G, B,

        // t11: F, C, I
        0.35f, 0.36f, 0.0f, R, G, B,
        0.33f, 0.43f, 0.0f, R, G, B,
        0.32f, 0.39f, 0.0f, R, G, B,

    };

#undef R
#undef G
#undef B

    MeshColor* coderaInt = new MeshColor();
    coderaInt->CreateMeshColor(vertices_coderaInterna, 198);
    meshColorList.push_back(coderaInt);
}



void CrearCamisa()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::CAFE_CAMISA[0]
#define G Colores::CAFE_CAMISA[1]
#define B Colores::CAFE_CAMISA[2]


    GLfloat vertices_camisa[] = {
        // t1: C, D, E
    0.33f, 0.43f, 0.0f, R, G, B,
    0.31f, 0.47f, 0.0f, R, G, B,
    0.29f, 0.39f, 0.0f, R, G, B,

    // t2: E, F, G
    0.29f, 0.39f, 0.0f, R, G, B,
    0.27f, 0.37f, 0.0f, R, G, B,
    0.26f, 0.41f, 0.0f, R, G, B,

    // t3: G, H, F
    0.26f, 0.41f, 0.0f, R, G, B,
    0.24f, 0.37f, 0.0f, R, G, B,
    0.27f, 0.37f, 0.0f, R, G, B,

    // t4: H, I, F
    0.24f, 0.37f, 0.0f, R, G, B,
    0.26f, 0.34f, 0.0f, R, G, B,
    0.27f, 0.37f, 0.0f, R, G, B,

    // t5: I, J, K
    0.26f, 0.34f, 0.0f, R, G, B,
    0.18f, 0.35f, 0.0f, R, G, B,
    0.21f, 0.36f, 0.0f, R, G, B,

    // t6: H, K, I
    0.24f, 0.37f, 0.0f, R, G, B,
    0.21f, 0.36f, 0.0f, R, G, B,
    0.26f, 0.34f, 0.0f, R, G, B,

    // t7: K, L, H
    0.21f, 0.36f, 0.0f, R, G, B,
    0.23f, 0.38f, 0.0f, R, G, B,
    0.24f, 0.37f, 0.0f, R, G, B,

    // t8: L, M, H
    0.23f, 0.38f, 0.0f, R, G, B,
    0.23f, 0.40f, 0.0f, R, G, B,
    0.24f, 0.37f, 0.0f, R, G, B,

    // t9: M, G, H
    0.23f, 0.40f, 0.0f, R, G, B,
    0.26f, 0.41f, 0.0f, R, G, B,
    0.24f, 0.37f, 0.0f, R, G, B,

    // t10: D, G, E
    0.31f, 0.47f, 0.0f, R, G, B,
    0.26f, 0.41f, 0.0f, R, G, B,
    0.29f, 0.39f, 0.0f, R, G, B,

    // t11: M, N, G
    0.23f, 0.40f, 0.0f, R, G, B,
    0.21f, 0.43f, 0.0f, R, G, B,
    0.26f, 0.41f, 0.0f, R, G, B,

    // t12: N, D, G
    0.21f, 0.43f, 0.0f, R, G, B,
    0.31f, 0.47f, 0.0f, R, G, B,
    0.26f, 0.41f, 0.0f, R, G, B,

    // t13: D, O, N
    0.31f, 0.47f, 0.0f, R, G, B,
    0.27f, 0.49f, 0.0f, R, G, B,
    0.21f, 0.43f, 0.0f, R, G, B,

    // t14: N, P, O
    0.21f, 0.43f, 0.0f, R, G, B,
    0.18f, 0.46f, 0.0f, R, G, B,
    0.27f, 0.49f, 0.0f, R, G, B,

    // t15: O, Q, P
    0.27f, 0.49f, 0.0f, R, G, B,
    0.21f, 0.49f, 0.0f, R, G, B,
    0.18f, 0.46f, 0.0f, R, G, B,

    // t16: P, R, Q
    0.18f, 0.46f, 0.0f, R, G, B,
    0.16f, 0.47f, 0.0f, R, G, B,
    0.21f, 0.49f, 0.0f, R, G, B,

    // t17: Q, S, R
    0.21f, 0.49f, 0.0f, R, G, B,
    0.18f, 0.49f, 0.0f, R, G, B,
    0.16f, 0.47f, 0.0f, R, G, B,

    // t18: S, T, R
    0.18f, 0.49f, 0.0f, R, G, B,
    0.14f, 0.48f, 0.0f, R, G, B,
    0.16f, 0.47f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* camisa = new MeshColor();
    camisa->CreateMeshColor(vertices_camisa, 1278);
    meshColorList.push_back(camisa);
}

void CrearManga()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]


    GLfloat vertices_manga[] = {
        // t1: C, D, E (C=(0.18, 0.35), D=(0.21, 0.36), E=(0.2, 0.37))
        0.18f, 0.35f, 0.0f, R, G, B,
        0.21f, 0.36f, 0.0f, R, G, B,
        0.20f, 0.37f, 0.0f, R, G, B,

        // t2: D, F, E (D=(0.21, 0.36), F=(0.22, 0.37), E=(0.2, 0.37))
        0.21f, 0.36f, 0.0f, R, G, B,
        0.22f, 0.37f, 0.0f, R, G, B,
        0.20f, 0.37f, 0.0f, R, G, B,

        // t3: E, G, F (E=(0.2, 0.37), G=(0.21, 0.38), F=(0.22, 0.37))
        0.20f, 0.37f, 0.0f, R, G, B,
        0.21f, 0.38f, 0.0f, R, G, B,
        0.22f, 0.37f, 0.0f, R, G, B,

        // t4: F, H, G (F=(0.22, 0.37), H=(0.23, 0.39), G=(0.21, 0.38))
        0.22f, 0.37f, 0.0f, R, G, B,
        0.23f, 0.39f, 0.0f, R, G, B,
        0.21f, 0.38f, 0.0f, R, G, B,

        // t5: G, I, H (G=(0.21, 0.38), I=(0.22, 0.4), H=(0.23, 0.39))
        0.21f, 0.38f, 0.0f, R, G, B,
        0.22f, 0.40f, 0.0f, R, G, B,
        0.23f, 0.39f, 0.0f, R, G, B,

        // t6: H, J, I (H=(0.23, 0.39), J=(0.23, 0.4), I=(0.22, 0.4))
        0.23f, 0.39f, 0.0f, R, G, B,
        0.23f, 0.40f, 0.0f, R, G, B,
        0.22f, 0.40f, 0.0f, R, G, B,

        // t7: I, K, J (I=(0.22, 0.4), K=(0.21, 0.41), J=(0.23, 0.4))
        0.22f, 0.40f, 0.0f, R, G, B,
        0.21f, 0.41f, 0.0f, R, G, B,
        0.23f, 0.40f, 0.0f, R, G, B,

        // t8: J, L, K (J=(0.23, 0.4), L=(0.21, 0.43), K=(0.21, 0.41))
        0.23f, 0.40f, 0.0f, R, G, B,
        0.21f, 0.43f, 0.0f, R, G, B,
        0.21f, 0.41f, 0.0f, R, G, B,

        // t9: K, M, L (K=(0.21, 0.41), M=(0.19, 0.44), L=(0.21, 0.43))
        0.21f, 0.41f, 0.0f, R, G, B,
        0.19f, 0.44f, 0.0f, R, G, B,
        0.21f, 0.43f, 0.0f, R, G, B,

        // t10: L, N, M (L=(0.21, 0.43), N=(0.17, 0.47), M=(0.19, 0.44))
        0.21f, 0.43f, 0.0f, R, G, B,
        0.17f, 0.47f, 0.0f, R, G, B,
        0.19f, 0.44f, 0.0f, R, G, B,

        // t11: M, O, N (M=(0.19, 0.44), O=(0.17, 0.46), N=(0.17, 0.47))
        0.19f, 0.44f, 0.0f, R, G, B,
        0.17f, 0.46f, 0.0f, R, G, B,
        0.17f, 0.47f, 0.0f, R, G, B,

        // t12: O, P, N (O=(0.17, 0.46), P=(0.14, 0.47), N=(0.17, 0.47))
        0.17f, 0.46f, 0.0f, R, G, B,
        0.14f, 0.47f, 0.0f, R, G, B,
        0.17f, 0.47f, 0.0f, R, G, B,

        // t13: N, Q, P (N=(0.17, 0.47), Q=(0.15, 0.48), P=(0.14, 0.47))
        0.17f, 0.47f, 0.0f, R, G, B,
        0.15f, 0.48f, 0.0f, R, G, B,
        0.14f, 0.47f, 0.0f, R, G, B,

        // t14: Q, R, P (Q=(0.15, 0.48), R=(0.13, 0.48), P=(0.14, 0.47))
        0.15f, 0.48f, 0.0f, R, G, B,
        0.13f, 0.48f, 0.0f, R, G, B,
        0.14f, 0.47f, 0.0f, R, G, B,

        // t15: P, S, R (P=(0.14, 0.47), S=(0.12, 0.47), R=(0.13, 0.48))
        0.14f, 0.47f, 0.0f, R, G, B,
        0.12f, 0.47f, 0.0f, R, G, B,
        0.13f, 0.48f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* manga = new MeshColor();
    manga->CreateMeshColor(vertices_manga, 270);
    meshColorList.push_back(manga);
}

void CrearGuante()
{
#define R Colores::DORADO[0]
#define G Colores::DORADO[1]
#define B Colores::DORADO[2]


    GLfloat vertices_guante[] = {
        // t1: C, D, E
        0.13f, 0.34f, 0.0f, R, G, B,
        0.16f, 0.34f, 0.0f, R, G, B,
        0.14f, 0.37f, 0.0f, R, G, B,

        // t2: E, F, D
        0.14f, 0.37f, 0.0f, R, G, B,
        0.19f, 0.36f, 0.0f, R, G, B,
        0.16f, 0.34f, 0.0f, R, G, B,

        // t3: F, G, H
        0.19f, 0.36f, 0.0f, R, G, B,
        0.21f, 0.37f, 0.0f, R, G, B,
        0.16f, 0.39f, 0.0f, R, G, B,

        // t4: H, I, G
        0.16f, 0.39f, 0.0f, R, G, B,
        0.18f, 0.41f, 0.0f, R, G, B,
        0.21f, 0.37f, 0.0f, R, G, B,

        // t5: G, J, I
        0.21f, 0.37f, 0.0f, R, G, B,
        0.22f, 0.39f, 0.0f, R, G, B,
        0.18f, 0.41f, 0.0f, R, G, B,

        // t6: I, K, J
        0.18f, 0.41f, 0.0f, R, G, B,
        0.21f, 0.42f, 0.0f, R, G, B,
        0.22f, 0.39f, 0.0f, R, G, B,

        // t7: I, L, K
        0.18f, 0.41f, 0.0f, R, G, B,
        0.19f, 0.44f, 0.0f, R, G, B,
        0.21f, 0.42f, 0.0f, R, G, B,

        // t8: I, M, L
        0.18f, 0.41f, 0.0f, R, G, B,
        0.15f, 0.44f, 0.0f, R, G, B,
        0.19f, 0.44f, 0.0f, R, G, B,

        // t9: L, N, M
        0.19f, 0.44f, 0.0f, R, G, B,
        0.16f, 0.47f, 0.0f, R, G, B,
        0.15f, 0.44f, 0.0f, R, G, B,

        // t10: M, O, N
        0.15f, 0.44f, 0.0f, R, G, B,
        0.12f, 0.47f, 0.0f, R, G, B,
        0.16f, 0.47f, 0.0f, R, G, B,

        // t11: M, P, O
        0.15f, 0.44f, 0.0f, R, G, B,
        0.08f, 0.46f, 0.0f, R, G, B,
        0.12f, 0.47f, 0.0f, R, G, B,

        // t12: H, E, F
        0.16f, 0.39f, 0.0f, R, G, B,
        0.14f, 0.37f, 0.0f, R, G, B,
        0.19f, 0.36f, 0.0f, R, G, B,

        // t13: P, I, M
        0.08f, 0.46f, 0.0f, R, G, B,
        0.18f, 0.41f, 0.0f, R, G, B,
        0.15f, 0.44f, 0.0f, R, G, B,

        // t14: H, P, I
        0.16f, 0.39f, 0.0f, R, G, B,
        0.08f, 0.46f, 0.0f, R, G, B,
        0.18f, 0.41f, 0.0f, R, G, B,

        // t15: E, P, H
        0.14f, 0.37f, 0.0f, R, G, B,
        0.08f, 0.46f, 0.0f, R, G, B,
        0.16f, 0.39f, 0.0f, R, G, B,

        // t16: C, Q, E
        0.13f, 0.34f, 0.0f, R, G, B,
        0.08f, 0.36f, 0.0f, R, G, B,
        0.14f, 0.37f, 0.0f, R, G, B,

        // t17: Q, P, E
        0.08f, 0.36f, 0.0f, R, G, B,
        0.08f, 0.46f, 0.0f, R, G, B,
        0.14f, 0.37f, 0.0f, R, G, B,

        // t18: Q, R, P
        0.08f, 0.36f, 0.0f, R, G, B,
        0.00f, 0.37f, 0.0f, R, G, B,
        0.08f, 0.46f, 0.0f, R, G, B,

        // t19: P, S, R
        0.08f, 0.46f, 0.0f, R, G, B,
        0.07f, 0.46f, 0.0f, R, G, B,
        0.00f, 0.37f, 0.0f, R, G, B,

        // t20: S, T, U
        0.07f, 0.46f, 0.0f, R, G, B,
        0.07f, 0.50f, 0.0f, R, G, B,
        0.03f, 0.53f, 0.0f, R, G, B,

        // t21: S, V, U
        0.07f, 0.46f, 0.0f, R, G, B,
       -0.01f, 0.53f, 0.0f, R, G, B,
        0.03f, 0.53f, 0.0f, R, G, B,

        // t22: S, W, V
        0.07f, 0.46f, 0.0f, R, G, B,
       -0.04f, 0.51f, 0.0f, R, G, B,
       -0.01f, 0.53f, 0.0f, R, G, B,

       // t23: W, Z, A1
      -0.04f, 0.51f, 0.0f, R, G, B,
      -0.07f, 0.47f, 0.0f, R, G, B,
      -0.01f, 0.47f, 0.0f, R, G, B,

      // t24: A1, S, W
     -0.01f, 0.47f, 0.0f, R, G, B,
      0.07f, 0.46f, 0.0f, R, G, B,
     -0.04f, 0.51f, 0.0f, R, G, B,

     // t25: A1, B1, Z
    -0.01f, 0.47f, 0.0f, R, G, B,
    -0.07f, 0.44f, 0.0f, R, G, B,
    -0.07f, 0.47f, 0.0f, R, G, B,

    // t26: A1, C1, B1
   -0.01f, 0.47f, 0.0f, R, G, B,
    0.02f, 0.43f, 0.0f, R, G, B,
   -0.07f, 0.44f, 0.0f, R, G, B,

   // t27: C1, S, A1
   0.02f, 0.43f, 0.0f, R, G, B,
   0.07f, 0.46f, 0.0f, R, G, B,
  -0.01f, 0.47f, 0.0f, R, G, B,

  // t28: R, C1, S
  0.00f, 0.37f, 0.0f, R, G, B,
  0.02f, 0.43f, 0.0f, R, G, B,
  0.07f, 0.46f, 0.0f, R, G, B,

  // t29: R, D1, C1
  0.00f, 0.37f, 0.0f, R, G, B,
 -0.06f, 0.39f, 0.0f, R, G, B,
  0.02f, 0.43f, 0.0f, R, G, B,

  // t30: D1, E1, C1
 -0.06f, 0.39f, 0.0f, R, G, B,
 -0.07f, 0.41f, 0.0f, R, G, B,
  0.02f, 0.43f, 0.0f, R, G, B,

  // t31: B1, E1, C1
 -0.07f, 0.44f, 0.0f, R, G, B,
 -0.07f, 0.41f, 0.0f, R, G, B,
  0.02f, 0.43f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* guante = new MeshColor();
    guante->CreateMeshColor(vertices_guante, 558);
    meshColorList.push_back(guante);
}

void CrearDetalleGuanteRojo()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::ROJO_OSCURO[0]
#define G Colores::ROJO_OSCURO[1]
#define B Colores::ROJO_OSCURO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_detalleGR[] = {
        // t1: C, D, E
    -0.02f, 0.44f, 0.0f, R, G, B,
     0.00f, 0.44f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t2: C, F, E
    -0.02f, 0.44f, 0.0f, R, G, B,
    -0.02f, 0.43f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t3: F, G, E
    -0.02f, 0.43f, 0.0f, R, G, B,
    -0.02f, 0.40f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t4: G, H, E
    -0.02f, 0.40f, 0.0f, R, G, B,
    -0.01f, 0.39f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t5: H, I, E
    -0.01f, 0.39f, 0.0f, R, G, B,
     0.01f, 0.39f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t6: I, J, E
     0.01f, 0.39f, 0.0f, R, G, B,
     0.01f, 0.41f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,

    // t7: J, D, E
     0.01f, 0.41f, 0.0f, R, G, B,
     0.00f, 0.44f, 0.0f, R, G, B,
    -0.01f, 0.41f, 0.0f, R, G, B,
    };

#undef R
#undef G
#undef B

    MeshColor* detalleGR = new MeshColor();
    detalleGR->CreateMeshColor(vertices_detalleGR, 126);
    meshColorList.push_back(detalleGR);
}

void CrearDetalleGuanteBlanco()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_detalleGB[] = {
        // t8: K, L, M
        0.06f, 0.37f, 0.0f, R, G, B,
        0.06f, 0.37f, 0.0f, R, G, B,
        0.06f, 0.40f, 0.0f, R, G, B,

        // t9: K, N, M
         0.06f, 0.37f, 0.0f, R, G, B,
         0.07f, 0.37f, 0.0f, R, G, B,
         0.06f, 0.40f, 0.0f, R, G, B,

         // t10: N, O, M
          0.07f, 0.37f, 0.0f, R, G, B,
          0.08f, 0.39f, 0.0f, R, G, B,
          0.06f, 0.40f, 0.0f, R, G, B,

          // t11: O, P, M
           0.08f, 0.39f, 0.0f, R, G, B,
           0.07f, 0.43f, 0.0f, R, G, B,
           0.06f, 0.40f, 0.0f, R, G, B,

           // t12: L, Q, M
            0.06f, 0.37f, 0.0f, R, G, B,
            0.05f, 0.39f, 0.0f, R, G, B,
            0.06f, 0.40f, 0.0f, R, G, B,

            // t13: Q, R, M
             0.05f, 0.39f, 0.0f, R, G, B,
             0.05f, 0.43f, 0.0f, R, G, B,
             0.06f, 0.40f, 0.0f, R, G, B,

             // t14: P, S, M
              0.07f, 0.43f, 0.0f, R, G, B,
              0.07f, 0.44f, 0.0f, R, G, B,
              0.06f, 0.40f, 0.0f, R, G, B,

              // t15: S, R, M
               0.07f, 0.44f, 0.0f, R, G, B,
               0.05f, 0.43f, 0.0f, R, G, B,
               0.06f, 0.40f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* detalleGB = new MeshColor();
    detalleGB->CreateMeshColor(vertices_detalleGB, 144);
    meshColorList.push_back(detalleGB);
}

void CrearCasco()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::ROJO_OSCURO[0]
#define G Colores::ROJO_OSCURO[1]
#define B Colores::ROJO_OSCURO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_casco[] = {
        // t1: C, D, E[cite: 21]
        -0.04f, 0.62f, 0.0f, R, G, B,
         0.02f, 0.64f, 0.0f, R, G, B,
        -0.02f, 0.65f, 0.0f, R, G, B,

        // t2: E, F, C[cite: 21]
        -0.02f, 0.65f, 0.0f, R, G, B,
        -0.08f, 0.63f, 0.0f, R, G, B,
        -0.04f, 0.62f, 0.0f, R, G, B,

        // t3: C, G, F[cite: 21]
        -0.04f, 0.62f, 0.0f, R, G, B,
        -0.10f, 0.59f, 0.0f, R, G, B,
        -0.08f, 0.63f, 0.0f, R, G, B,

        // t4: F, H, G[cite: 21]
        -0.08f, 0.63f, 0.0f, R, G, B,
        -0.15f, 0.59f, 0.0f, R, G, B,
        -0.10f, 0.59f, 0.0f, R, G, B,

        // t5: G, I, H[cite: 21]
        -0.10f, 0.59f, 0.0f, R, G, B,
        -0.13f, 0.56f, 0.0f, R, G, B,
        -0.15f, 0.59f, 0.0f, R, G, B,

        // t6: H, J, F[cite: 21]
        -0.15f, 0.59f, 0.0f, R, G, B,
        -0.16f, 0.61f, 0.0f, R, G, B,
        -0.08f, 0.63f, 0.0f, R, G, B,

        // t7: J, K, F[cite: 21]
        -0.16f, 0.61f, 0.0f, R, G, B,
        -0.16f, 0.65f, 0.0f, R, G, B,
        -0.08f, 0.63f, 0.0f, R, G, B,

        // t8: E, L, D[cite: 21]
        -0.02f, 0.65f, 0.0f, R, G, B,
         0.00f, 0.72f, 0.0f, R, G, B,
         0.02f, 0.64f, 0.0f, R, G, B,

         // t9: E, K, L[cite: 21]
         -0.02f, 0.65f, 0.0f, R, G, B,
         -0.16f, 0.65f, 0.0f, R, G, B,
          0.00f, 0.72f, 0.0f, R, G, B,

          // t10: K, F, E[cite: 21]
          -0.16f, 0.65f, 0.0f, R, G, B,
          -0.08f, 0.63f, 0.0f, R, G, B,
          -0.02f, 0.65f, 0.0f, R, G, B,

          // t11: K, M, N[cite: 21]
          -0.16f, 0.65f, 0.0f, R, G, B,
          -0.21f, 0.61f, 0.0f, R, G, B,
          -0.21f, 0.63f, 0.0f, R, G, B,

          // t12: M, O, N[cite: 21]
          -0.21f, 0.61f, 0.0f, R, G, B,
          -0.22f, 0.62f, 0.0f, R, G, B,
          -0.21f, 0.63f, 0.0f, R, G, B,

          // t13: O, P, N[cite: 21]
          -0.22f, 0.62f, 0.0f, R, G, B,
          -0.23f, 0.64f, 0.0f, R, G, B,
          -0.21f, 0.63f, 0.0f, R, G, B,

          // t14: N, Q, P[cite: 21]
          -0.21f, 0.63f, 0.0f, R, G, B,
          -0.20f, 0.65f, 0.0f, R, G, B,
          -0.23f, 0.64f, 0.0f, R, G, B,

          // t15: P, R, Q[cite: 21]
          -0.23f, 0.64f, 0.0f, R, G, B,
          -0.22f, 0.67f, 0.0f, R, G, B,
          -0.20f, 0.65f, 0.0f, R, G, B,

          // t16: R, S, Q[cite: 21]
          -0.22f, 0.67f, 0.0f, R, G, B,
          -0.21f, 0.69f, 0.0f, R, G, B,
          -0.20f, 0.65f, 0.0f, R, G, B,

          // t17: S, T, U[cite: 21]
          -0.21f, 0.69f, 0.0f, R, G, B,
          -0.22f, 0.71f, 0.0f, R, G, B,
          -0.20f, 0.73f, 0.0f, R, G, B,

          // t18: U, V, K[cite: 21]
          -0.20f, 0.73f, 0.0f, R, G, B,
          -0.18f, 0.75f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t19: Q, U, S[cite: 21]
          -0.20f, 0.65f, 0.0f, R, G, B,
          -0.20f, 0.73f, 0.0f, R, G, B,
          -0.21f, 0.69f, 0.0f, R, G, B,

          // t20: K, Q, N[cite: 21]
          -0.16f, 0.65f, 0.0f, R, G, B,
          -0.20f, 0.65f, 0.0f, R, G, B,
          -0.21f, 0.63f, 0.0f, R, G, B,

          // t21: U, Q, K[cite: 21]
          -0.20f, 0.73f, 0.0f, R, G, B,
          -0.20f, 0.65f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t22: V, W, K[cite: 21]
          -0.18f, 0.75f, 0.0f, R, G, B,
          -0.12f, 0.78f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t23: W, Z, K[cite: 21]
          -0.12f, 0.78f, 0.0f, R, G, B,
          -0.08f, 0.78f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t24: Z, A_1, K[cite: 21]
          -0.08f, 0.78f, 0.0f, R, G, B,
          -0.04f, 0.76f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t25: A_1, B_1, K[cite: 21]
          -0.04f, 0.76f, 0.0f, R, G, B,
          -0.02f, 0.75f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t26: B_1, L, K[cite: 21]
          -0.02f, 0.75f, 0.0f, R, G, B,
           0.00f, 0.72f, 0.0f, R, G, B,
          -0.16f, 0.65f, 0.0f, R, G, B,

          // t27: L, C_1, B_1[cite: 21]
           0.00f, 0.72f, 0.0f, R, G, B,
           0.01f, 0.73f, 0.0f, R, G, B,
          -0.02f, 0.75f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* casco = new MeshColor();
    casco->CreateMeshColor(vertices_casco, 486);
    meshColorList.push_back(casco);
}

void CrearDetallesCasco()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::DORADO[0]
#define G Colores::DORADO[1]
#define B Colores::DORADO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_detalles_casco[] = {
        // t1: C, D, E
        -0.09f, 0.64f, 0.0f, R, G, B,
        -0.10f, 0.69f, 0.0f, R, G, B,
        -0.08f, 0.69f, 0.0f, R, G, B,

        // t2: D, F, C
        -0.10f, 0.69f, 0.0f, R, G, B,
        -0.12f, 0.68f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t3: F, G, C
        -0.12f, 0.68f, 0.0f, R, G, B,
        -0.14f, 0.66f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t4: G, H, C
        -0.14f, 0.66f, 0.0f, R, G, B,
        -0.14f, 0.63f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t5: H, I, C
        -0.14f, 0.63f, 0.0f, R, G, B,
        -0.13f, 0.61f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t6: I, J, C
        -0.13f, 0.61f, 0.0f, R, G, B,
        -0.12f, 0.60f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t7: J, K, C
        -0.12f, 0.60f, 0.0f, R, G, B,
        -0.10f, 0.59f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t8: K, L, C
        -0.10f, 0.59f, 0.0f, R, G, B,
        -0.04f, 0.63f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t9: L, M, C
        -0.04f, 0.63f, 0.0f, R, G, B,
        -0.04f, 0.65f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t10: M, N, C
        -0.04f, 0.65f, 0.0f, R, G, B,
        -0.05f, 0.67f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t11: N, O, C
        -0.05f, 0.67f, 0.0f, R, G, B,
        -0.06f, 0.68f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t12: O, E, C
        -0.06f, 0.68f, 0.0f, R, G, B,
        -0.08f, 0.69f, 0.0f, R, G, B,
        -0.09f, 0.64f, 0.0f, R, G, B,

        // t13: P, Q, R
        -0.22f, 0.63f, 0.0f, R, G, B,
        -0.22f, 0.66f, 0.0f, R, G, B,
        -0.24f, 0.66f, 0.0f, R, G, B,

        // t14: Q, S, T
        -0.22f, 0.66f, 0.0f, R, G, B,
        -0.21f, 0.69f, 0.0f, R, G, B,
        -0.23f, 0.68f, 0.0f, R, G, B,

        // t15: T, R, Q
        -0.23f, 0.68f, 0.0f, R, G, B,
        -0.24f, 0.66f, 0.0f, R, G, B,
        -0.22f, 0.66f, 0.0f, R, G, B,

        // t16: U, V, S
        -0.23f, 0.68f, 0.0f, R, G, B,
        -0.23f, 0.70f, 0.0f, R, G, B,
        -0.21f, 0.69f, 0.0f, R, G, B,

        // t17: W, V, S
        -0.22f, 0.71f, 0.0f, R, G, B,
        -0.23f, 0.70f, 0.0f, R, G, B,
        -0.21f, 0.69f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* detallesCasco = new MeshColor();
    detallesCasco->CreateMeshColor(vertices_detalles_casco, 306);
    meshColorList.push_back(detallesCasco);
}

void CrearVisor()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::NEGRO[0]
#define G Colores::NEGRO[1]
#define B Colores::NEGRO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_visor[] = {
        // t1: Polígono(C, D, E)
        -0.15f,  0.60f, 0.0f, R, G, B, // C (-0.15, 0.6)
        -0.17f,  0.59f, 0.0f, R, G, B, // D (-0.17, 0.59)
        -0.16f,  0.61f, 0.0f, R, G, B, // E (-0.16, 0.61)

        // t2: Polígono(E, F, G)
        -0.16f,  0.61f, 0.0f, R, G, B, // E (-0.16, 0.61)
        -0.16f,  0.65f, 0.0f, R, G, B, // F (-0.16, 0.65)
        -0.21f,  0.61f, 0.0f, R, G, B, // G (-0.21, 0.61)

        // t3: Polígono(D, G, E)
        -0.17f,  0.59f, 0.0f, R, G, B, // D (-0.17, 0.59)
        -0.21f,  0.61f, 0.0f, R, G, B, // G (-0.21, 0.61)
        -0.16f,  0.61f, 0.0f, R, G, B, // E (-0.16, 0.61)

        // t4: Polígono(G, H, I)
        -0.21f,  0.61f, 0.0f, R, G, B, // G (-0.21, 0.61)
        -0.19f,  0.59f, 0.0f, R, G, B, // H (-0.19, 0.59)
        -0.18f,  0.59f, 0.0f, R, G, B, // I (-0.18, 0.59)

        // t5: Polígono(I, D, G)
        -0.18f,  0.59f, 0.0f, R, G, B, // I (-0.18, 0.59)
        -0.17f,  0.59f, 0.0f, R, G, B, // D (-0.17, 0.59)
        -0.21f,  0.61f, 0.0f, R, G, B, // G (-0.21, 0.61)

    };

#undef R
#undef G
#undef B

    MeshColor* visor = new MeshColor();
    visor->CreateMeshColor(vertices_visor, 90);
    meshColorList.push_back(visor);
}

void CrearOjo()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_ojo[] = {

    -0.18f,  0.60f, 0.0f, R, G, B, // J (-0.18, 0.6)
    -0.18f,  0.63f, 0.0f, R, G, B, // K (-0.18, 0.63)
    -0.2f,  0.61f, 0.0f, R, G, B  // L (-0.2, 0.61)

    };

#undef R
#undef G
#undef B

    MeshColor* ojo = new MeshColor();
    ojo->CreateMeshColor(vertices_ojo, 18);
    meshColorList.push_back(ojo);
}

void CrearRostro()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::PIEL[0]
#define G Colores::PIEL[1]
#define B Colores::PIEL[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_rostro[] = {
        // t1: C, D, E
        -0.19f, 0.57f, 0.0f, R, G, B,
        -0.19f, 0.56f, 0.0f, R, G, B,
        -0.18f, 0.56f, 0.0f, R, G, B,

        // t2: E, F, C
        -0.18f, 0.56f, 0.0f, R, G, B,
        -0.18f, 0.56f, 0.0f, R, G, B,
        -0.19f, 0.57f, 0.0f, R, G, B,

        // t3: C, G, D
        -0.19f, 0.57f, 0.0f, R, G, B,
        -0.19f, 0.59f, 0.0f, R, G, B,
        -0.19f, 0.56f, 0.0f, R, G, B,

        // t4: G, H, C
        -0.19f, 0.59f, 0.0f, R, G, B,
        -0.19f, 0.59f, 0.0f, R, G, B,
        -0.19f, 0.57f, 0.0f, R, G, B,

        // t5: H, I, C
        -0.19f, 0.59f, 0.0f, R, G, B,
        -0.18f, 0.59f, 0.0f, R, G, B,
        -0.19f, 0.57f, 0.0f, R, G, B,

        // t6: F, I, C
        -0.18f, 0.56f, 0.0f, R, G, B,
        -0.18f, 0.59f, 0.0f, R, G, B,
        -0.19f, 0.57f, 0.0f, R, G, B,

        // t7: F, J, I
        -0.18f, 0.56f, 0.0f, R, G, B,
        -0.14f, 0.59f, 0.0f, R, G, B,
        -0.18f, 0.59f, 0.0f, R, G, B,

        // t8: I, K, J
        -0.18f, 0.59f, 0.0f, R, G, B,
        -0.15f, 0.60f, 0.0f, R, G, B,
        -0.14f, 0.59f, 0.0f, R, G, B,

        // t9: J, L, F
        -0.14f, 0.59f, 0.0f, R, G, B,
        -0.13f, 0.57f, 0.0f, R, G, B,
        -0.18f, 0.56f, 0.0f, R, G, B,

        // t10: L, M, F
        -0.13f, 0.57f, 0.0f, R, G, B,
        -0.16f, 0.54f, 0.0f, R, G, B,
        -0.18f, 0.56f, 0.0f, R, G, B,

    };

#undef R
#undef G
#undef B

    MeshColor* rostro = new MeshColor();
    rostro->CreateMeshColor(vertices_rostro, 216);
    meshColorList.push_back(rostro);
}

void CrearCoderaInterna2()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::MARRON_CODERA_INT[0]
#define G Colores::MARRON_CODERA_INT[1]
#define B Colores::MARRON_CODERA_INT[2]

    GLfloat vertices_coderaInterna2[] = {

        // t12: N, O, P
        0.05f, 0.23f, 0.0f, R, G, B,
        0.05f, 0.21f, 0.0f, R, G, B,
        0.06f, 0.21f, 0.0f, R, G, B,

        // t13: O, Q, R
        0.05f, 0.21f, 0.0f, R, G, B,
        0.03f, 0.21f, 0.0f, R, G, B,
        0.05f, 0.19f, 0.0f, R, G, B,

        // t14: R, P, O
        0.05f, 0.19f, 0.0f, R, G, B,
        0.06f, 0.21f, 0.0f, R, G, B,
        0.05f, 0.21f, 0.0f, R, G, B,

        // t15: R, S, P
        0.05f, 0.19f, 0.0f, R, G, B,
        0.08f, 0.17f, 0.0f, R, G, B,
        0.06f, 0.21f, 0.0f, R, G, B,

        // t16: P, T, S
        0.06f, 0.21f, 0.0f, R, G, B,
        0.08f, 0.20f, 0.0f, R, G, B,
        0.08f, 0.17f, 0.0f, R, G, B,

        // t17: T, U, S
        0.08f, 0.20f, 0.0f, R, G, B,
        0.09f, 0.20f, 0.0f, R, G, B,
        0.08f, 0.17f, 0.0f, R, G, B,

        // t18: S, V, U
        0.08f, 0.17f, 0.0f, R, G, B,
        0.10f, 0.16f, 0.0f, R, G, B,
        0.09f, 0.20f, 0.0f, R, G, B,

        // t19: V, W, U
        0.10f, 0.16f, 0.0f, R, G, B,
        0.11f, 0.17f, 0.0f, R, G, B,
        0.09f, 0.20f, 0.0f, R, G, B,

        // t20: U, Z, A1
        0.09f, 0.20f, 0.0f, R, G, B,
        0.11f, 0.21f, 0.0f, R, G, B,
        0.11f, 0.19f, 0.0f, R, G, B,

        // t21: W, A1, U
        0.11f, 0.17f, 0.0f, R, G, B,
        0.11f, 0.19f, 0.0f, R, G, B,
        0.09f, 0.20f, 0.0f, R, G, B
    };

#undef R
#undef G
#undef B

    MeshColor* coderaInt2 = new MeshColor();
    coderaInt2->CreateMeshColor(vertices_coderaInterna2, 180);
    meshColorList.push_back(coderaInt2);
}

void CrearSmashInfIzq()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_smashII[] = {

        // t7: L, M, N
     -0.718f, 0.677f, 0.0f, R, G, B,
     -0.685f, 0.676f, 0.0f, R, G, B,
     -0.684f, 0.629f, 0.0f, R, G, B,

     // t8: L, O, N
     -0.718f, 0.677f, 0.0f, R, G, B,
     -0.705f, 0.651f, 0.0f, R, G, B,
     -0.684f, 0.629f, 0.0f, R, G, B,

    };

#undef R
#undef G
#undef B

    MeshColor* smashInfIzq = new MeshColor();
    smashInfIzq->CreateMeshColor(vertices_smashII, 36);
    meshColorList.push_back(smashInfIzq);
}

void CrearSmashInfDer()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_smashID[] = {

        // t9: P, Q, R
       -0.633f, 0.677f, 0.0f, R, G, B,
       -0.634f, 0.605f, 0.0f, R, G, B,
       -0.513f, 0.676f, 0.0f, R, G, B,

       // t10: Q, S, T
       -0.634f, 0.605f, 0.0f, R, G, B,
       -0.609f, 0.604f, 0.0f, R, G, B,
       -0.610f, 0.624f, 0.0f, R, G, B,

       // t11: S, U, T
       -0.609f, 0.604f, 0.0f, R, G, B,
       -0.582f, 0.608f, 0.0f, R, G, B,
       -0.610f, 0.624f, 0.0f, R, G, B,

       // t12: U, V, T
       -0.582f, 0.608f, 0.0f, R, G, B,
       -0.557f, 0.622f, 0.0f, R, G, B,
       -0.610f, 0.624f, 0.0f, R, G, B,

       // t13: T, W, V
       -0.610f, 0.624f, 0.0f, R, G, B,
       -0.574f, 0.644f, 0.0f, R, G, B,
       -0.557f, 0.622f, 0.0f, R, G, B,

       // t14: V, Z, W
       -0.557f, 0.622f, 0.0f, R, G, B,
       -0.536f, 0.639f, 0.0f, R, G, B,
       -0.574f, 0.644f, 0.0f, R, G, B,

       // t15: W, A1, Z
       -0.574f, 0.644f, 0.0f, R, G, B,
       -0.547f, 0.659f, 0.0f, R, G, B,
       -0.536f, 0.639f, 0.0f, R, G, B,

       // t16: Z, B1, A1
       -0.536f, 0.639f, 0.0f, R, G, B,
       -0.520f, 0.660f, 0.0f, R, G, B,
       -0.547f, 0.659f, 0.0f, R, G, B,

       // t17: B1, R, A1
       -0.520f, 0.660f, 0.0f, R, G, B,
       -0.513f, 0.676f, 0.0f, R, G, B,
       -0.547f, 0.659f, 0.0f, R, G, B


    };

#undef R
#undef G
#undef B

    MeshColor* smashInfDer = new MeshColor();
    smashInfDer->CreateMeshColor(vertices_smashID, 162);
    meshColorList.push_back(smashInfDer);
}

void CrearSmashSupDer()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_smashSD[] = {

            // t1: E, F, G
            -0.634f, 0.698f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,
            -0.634f, 0.818f, 0.0f, R, G, B,

            // t2: E, H, F
            -0.634f, 0.698f, 0.0f, R, G, B,
            -0.508f, 0.697f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t3: H, I, F
            -0.508f, 0.697f, 0.0f, R, G, B,
            -0.508f, 0.726f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t4: I, J, F
            -0.508f, 0.726f, 0.0f, R, G, B,
            -0.516f, 0.754f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t5: G, K, F
            -0.634f, 0.818f, 0.0f, R, G, B,
            -0.605f, 0.820f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t6: K, L, F
            -0.605f, 0.820f, 0.0f, R, G, B,
            -0.577f, 0.813f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t7: J, M, F
            -0.516f, 0.754f, 0.0f, R, G, B,
            -0.527f, 0.774f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t8: L, N, F
            -0.577f, 0.813f, 0.0f, R, G, B,
            -0.554f, 0.801f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t9: N, O, F
            -0.554f, 0.801f, 0.0f, R, G, B,
            -0.539f, 0.789f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B,

            // t10: M, O, F
            -0.527f, 0.774f, 0.0f, R, G, B,
            -0.539f, 0.789f, 0.0f, R, G, B,
            -0.565f, 0.765f, 0.0f, R, G, B

    };

#undef R
#undef G
#undef B

    MeshColor* smashSupDer = new MeshColor();
    smashSupDer->CreateMeshColor(vertices_smashSD, 180);
    meshColorList.push_back(smashSupDer);
}

void CrearSmashSupIzq()
{
    // Selección del color por defecto para las piernas (Morado)
#define R Colores::BLANCO[0]
#define G Colores::BLANCO[1]
#define B Colores::BLANCO[2]

    // Arreglo de vértices: X, Y, Z, R, G, B (46 Triángulos = 138 vértices = 828 floats)
    GLfloat vertices_smashSI[] = {

        // t1: E, F, G
            -0.723f, 0.698f, 0.0f, R, G, B,
            -0.723f, 0.720f, 0.0f, R, G, B,
            -0.705f, 0.707f, 0.0f, R, G, B,

            // t2: H, G, E
            -0.685f, 0.697f, 0.0f, R, G, B,
            -0.705f, 0.707f, 0.0f, R, G, B,
            -0.723f, 0.698f, 0.0f, R, G, B,

            // t3: F, I, G
            -0.723f, 0.720f, 0.0f, R, G, B,
            -0.718f, 0.747f, 0.0f, R, G, B,
            -0.705f, 0.707f, 0.0f, R, G, B,

            // t4: I, J, G
            -0.718f, 0.747f, 0.0f, R, G, B,
            -0.704f, 0.773f, 0.0f, R, G, B,
            -0.705f, 0.707f, 0.0f, R, G, B,

            // t5: J, K, H
            -0.704f, 0.773f, 0.0f, R, G, B,
            -0.684f, 0.794f, 0.0f, R, G, B,
            -0.685f, 0.697f, 0.0f, R, G, B,

            // t6: H, J, G
            -0.685f, 0.697f, 0.0f, R, G, B,
            -0.704f, 0.773f, 0.0f, R, G, B,
            -0.705f, 0.707f, 0.0f, R, G, B

    };

#undef R
#undef G
#undef B

    MeshColor* smashSupIzq = new MeshColor();
    smashSupIzq->CreateMeshColor(vertices_smashSI, 108);
    meshColorList.push_back(smashSupIzq);
}


void CreateShaders()
{
    Shader* shaderPersonaje = new Shader();
    shaderPersonaje->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shaderPersonaje); // Índice 0
}

int main()
{
    mainWindow = Window(800, 800);
    mainWindow.Initialise();
    CreateShaders();       // Carga shaderpersonaje.vert y shaderpersonaje.frag en shaderList[0]
    CrearBotaDerecha();    // meshColorList[0]
    CrearBotaIzquierda();  // meshColorList[1]
    crearEspinilleraDer(); // meshColorList[2]
    crearEspinilleraIzq(); // meshColorList[3]
    CrearPiernas();        // meshColorList[4]
    CrearCinturon();       // meshColorList[5]
    CrearTorso();          // meshColorList[6]
    CrearBufanda();        // meshColorList[7]
    CrearCoderaExterna();  // meshColorList[8]
    CrearCoderaInterna();  // meshColorList[9]
    CrearCamisa();         // meshColorList[10]
    CrearManga();          // meshColorList[11]
    CrearDetalleGuanteRojo();  // meshColorList[12]
    CrearDetalleGuanteBlanco();  // meshColorList[13]
    CrearGuante();         // meshColorList[14]
    CrearDetallesCasco();  // meshColorList[15]
    CrearCasco();          // meshColorList[16]
    CrearOjo();            // meshColorList[17]
    CrearVisor();          // meshColorList[18]
    CrearRostro();         // meshColorList[19]
    CrearCoderaInterna2(); // meshColorList[20]
    CrearSmashSupIzq();    // meshColorList[21]
    CrearSmashSupDer();    // meshColorList[22]
    CrearSmashInfIzq();    // meshColorList[23]
    CrearSmashInfDer();    // meshColorList[24]

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;

    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    while (!mainWindow.getShouldClose())
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Uso exclusivo del shader de personaje
        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));



        ///********BOTAS***************///////

        // Renderizado de la bota derecha
        glm::mat4 model(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[0]->RenderMeshColor();

        // Renderizado de la bota izquierda
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[1]->RenderMeshColor();


        ///********ESPINILLERAS***************///////
        
        // Renderizado de las espinillera derecha
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[2]->RenderMeshColor();

        // Renderizado de las espinillera izquierda
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[3]->RenderMeshColor();
        ///********PIERNAS***************///////
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[4]->RenderMeshColor();


        ///********CINTURON***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[5]->RenderMeshColor();

        ///********TORSO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[6]->RenderMeshColor();

        ///********BUFANDA***************///////
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[7]->RenderMeshColor();

        ///********CODERA_EXTERNA***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[8]->RenderMeshColor();

        ///********CODERA_INTERNA***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[9]->RenderMeshColor();

        ///********CAMISA***************///////
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[10]->RenderMeshColor();

        ///********MANGA***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[11]->RenderMeshColor();

        
        ///********DETALLEGUANTEROJO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[12]->RenderMeshColor();

        ///********DETALLEGUANTEBLANCO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[13]->RenderMeshColor();

        ///********GUANTE***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[14]->RenderMeshColor();

        ///********DETALLES CASCO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[15]->RenderMeshColor();

        ///********CASCOROJO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[16]->RenderMeshColor();

        ///********OJO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[17]->RenderMeshColor();


        ///********VISOR***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[18]->RenderMeshColor();


        ///********ROSTRO***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[19]->RenderMeshColor();
        ///********Codera interna 2***************///////
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[20]->RenderMeshColor();
        
        ///********SMASH***************///////

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[21]->RenderMeshColor();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[22]->RenderMeshColor();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[23]->RenderMeshColor();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshColorList[24]->RenderMeshColor();

        
        

        glUseProgram(0);
        mainWindow.swapBuffers();
    }

    return 0;
}