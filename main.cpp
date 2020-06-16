
//  main.cpp
//  Proyecto Final
//
//  Created by Cristina De León and Lourdes  Navarretes
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <strstream>

using namespace std;
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawCuarto(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPata2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPata3(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPata4(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPata1(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawMesa(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawVentana(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawVaso(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPlane(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawPlane2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);


GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat translationX = 0.0f;
GLfloat translationY = 0.0f;
GLfloat movePlaneX = 0.0f;
GLfloat moveVasoX = 0.0f;


int main(void)
{
    GLFWwindow* window;

    // Inicializar la librerÌa
    if (!glfwInit())
    {
        return -1;
    }

    // Crear la ventana
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    // Declarar que se recibir·n comando del teclado
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);



    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);


    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    // Se crea el contexto de la ventana
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // Especifica en que parte de la ventana se dibujaran los elementos
    glMatrixMode(GL_PROJECTION); // Se crea la matriz de proyecciÛn
    glLoadIdentity(); // Se crea de la matriz identidad
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // Establecer el sistema de coordenadas
    glMatrixMode(GL_MODELVIEW); // Matriz de transformaciÛn



    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;




    // Loop en donde se estar· dibujando la ventana
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        
//      Comienza la elaboración del los objetos aquí
        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500); // Coloca la escena al centro de la pantalla
        glTranslated(translationX, translationY, 0); // Mueve mueve la escena (perspectiva) usando las teclas de flechas.
        glRotatef(rotationX, 1, 0, 0); // Rotar escena en X
        glRotatef(rotationY, 0, 1, 0); // Rotar escena en Y
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
        DrawCuarto(halfScreenWidth, halfScreenHeight, -500, 500); // se le aplican la tranformaciones a la escena y lo que conlleva.

        glPopMatrix();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}


// LLamar mandar las teclas
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


    const GLfloat rotationSpeed = 10;

    // Switch en donde se determinan los movimientos del alguno objetos en base a las teclas
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            rotationX -= rotationSpeed;
            break;
        case GLFW_KEY_DOWN:
            rotationX += rotationSpeed;
            break;
        case GLFW_KEY_RIGHT:
            rotationY += rotationSpeed;
            break;
        case GLFW_KEY_LEFT:
            rotationY -= rotationSpeed;
            break;
        case GLFW_KEY_A:
            translationX -= 10;
            break;
        case GLFW_KEY_S:
            translationX += 10;
            break;
        case GLFW_KEY_W:
            translationY += 10;
            break;
        case GLFW_KEY_X:
            translationY -= 10;
            break;
        case GLFW_KEY_J:
                if(moveVasoX - 10 >= -70) // genera limites para que el vaso no sobre pase la mesa
                    moveVasoX -= 10;
                break;
        case GLFW_KEY_K:
            if(moveVasoX + 10 <= 80) // genera limites para que el vaso no sobre pase la mesa
                moveVasoX += 10;
            break;
        }


    }
}

// Función para dibujar la escena (el cuarto)
void DrawCuarto(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,  // Abajo Izquierda
        
        0,0,0,
        0,0,0,
        0,0,0,
        0,0,0,
        
        0,0,0,
        0,0,0,
        0,0,0,
        0,0,0,
        
        0,0,0,
        0,0,0,
        0,0,0,
        0,0,0,
    };

    GLfloat colour[] = {
        25.0, 200.0, 20.0,
        25.0, 200.0, 20.0,
        25.0, 200.0, 20.0,
        255.0, 0.0, 20.0,
        200.0, 25.0, 0.0,
        200.0, 200.0, 0.0,
        200.0, 25.0, 0.0,
        25.0, 200.0, 0.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0
    };
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

//  Aquí se dibujan aquellas figuras que desees que apliquen la transformación de la figura creada en
//  esta función (que en este caso es la escena)
    DrawPata2(halfScreenWidth, halfScreenHeight - 149, -600, 200);
    DrawPata3(halfScreenWidth, halfScreenHeight - 149, -600, 200);
    DrawPata4(halfScreenWidth + 100, halfScreenHeight - 149, -600, 200);
    DrawPata1(halfScreenWidth + 100, halfScreenHeight - 149, -600, 200);
    DrawMesa(halfScreenWidth, halfScreenHeight - 149, -600, 200);
    DrawVentana(halfScreenWidth, halfScreenHeight, -250, 200);
    
//  Aquí se crea la transformación del vaso.
//  Toda transformación se comiensa con pushMatrix()
    glPushMatrix();
    glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glTranslated(moveVasoX, 0, 0); // Mueve el vaso con las teclas J y K al manipularse la variable moveVasoX
        glScalef(0.5, 0.5, 0.5); // se escala el vaso a que este más pequeño
    glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
        DrawVaso(halfScreenWidth + 75, halfScreenHeight - 120, -660, 200); // se aplican transformaciones al vaso al ser llamado
                                                                           // dentro del pushMatrix()
    glPopMatrix(); // Termina transformación
    
}

// Función para dibujar la mesa (una de las cuatro patas)
void DrawPata2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// Pata adelante izq
        // Cara Frontal
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70

    };
    //Arreglo para agregar color
    GLfloat colour[] = {
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
    };

    glEnable(GL_DEPTH_TEST); //Agregar la proyecciÛn de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyecciÛn de profundidad
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar la mesa (una de las cuatro patas)
void DrawPata3(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// pata atras izq
        // Cara Frontal
        centerPosX - halfSideLength, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength, centerPosY, centerPosZ - 30, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ - 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ - 30, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ - 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70

    };
    //Arreglo para agregar color
    GLfloat colour[] = {
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
             0.0, 0.0, 0.0,
    };

    glEnable(GL_DEPTH_TEST); //Agregar la proyecciÛn de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyecciÛn de profundidad
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar la mesa (una de las cuatro patas)
void DrawPata4(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// pata adelante derecha
        // Cara Frontal
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ + 70, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 30, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 30, // Arriba Dereccha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 70 , // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX, centerPosY, centerPosZ + 30, // Abajo Derecha
        centerPosX, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ + 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ + 70

    };
    GLfloat colour[] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
    };
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar la mesa (una de las cuatro patas)
void DrawPata1(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// pata adelante derecha
        // Cara Frontal
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ - 70, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 30, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ - 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 30, // Arriba Dereccha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX, centerPosY, centerPosZ - 70, // Arriba Izquierda
        centerPosX, centerPosY, centerPosZ - 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 70, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 70 , // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY, centerPosZ - 30, // Arriba Derecha
        centerPosX, centerPosY, centerPosZ - 30, // Abajo Derecha
        centerPosX, centerPosY, centerPosZ - 70, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 70, // Arriba Izquierda
        centerPosX - halfSideLength + 60, centerPosY - halfSideLength, centerPosZ - 30, // Arriba Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 30, // Abajo Derecha
        centerPosX, centerPosY - halfSideLength, centerPosZ - 70

    };
    GLfloat colour[] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
    };
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar la mesa (pieza central)
void DrawMesa(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// EDIFICIO CENTRO
        // Cara Frontal
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ + 70, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ + 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ - 70, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ - 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ - 70, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ - 70, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY, centerPosZ - 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ - 70, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ + 70, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength, centerPosY , centerPosZ + 70 , // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY  , centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY  , centerPosZ - 70, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY  , centerPosZ + 70, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + 40, centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ - 70, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY + 40, centerPosZ + 70

    };
    GLfloat colour[] = {
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
           0.0, 0.0, 0.0,
    };

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar el vaso sobre la mesa
void DrawVaso(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        //// Pata adelante izq
        // Cara Frontal
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY, centerPosZ + 30, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda

        // Cara Derecha
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 70, // Arriba Izquierda
        centerPosX + halfSideLength - 160, centerPosY, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength, centerPosZ + 70, // Abajo Izquierda


        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + 30, // Arriba Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength + 10, centerPosZ + 30, // Abajo Derecha
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength + 10, centerPosZ + 70,
        
        0,0,0,
        0,0,0,
        0,0,0,
        0,0,0
        

    };
    //Arreglo para agregar color
    GLfloat colour[] = {
        0.0, 255.0, 0.0,
        0.0, 255.0, 0.0,
        0.0, 255.0, 0.0,
        0.0, 255.0, 0.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0,
        0.0,0.0,255.0
    };
    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;


    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glPushMatrix();
    
    // Aquí se intento utilizar lo investigado de glfwSetTime,
    // sin embargo no funcionó al cien y decidimos realizarlo de
    // otra manera.
    
    //glfwSetTime(0.0f);
    //if (glfwGetTime() > 0.0f)
    //{
    //    rotationY += 0.1;
    //    DrawVaso(halfScreenWidth + 75, halfScreenHeight - 10, -620, 200);
    //    glfwSetTime(0.0f);
    //}
    //glTranslatef(halfScreenWidth + 75, halfScreenHeight, -620);
    //glTranslated(moveVasoX, 0, 0);
    //glTranslatef(-(halfScreenWidth + 75), -(halfScreenHeight - 10), 200);
    
    // con esta variable se logra mantener en movimiento el avión
    movePlaneX += 3; // el valor debe ser < 1 en caso de ser Windows
    glTranslatef(halfScreenWidth, halfScreenHeight, -500);
    glRotatef(movePlaneX, 0, 1, 0); // aquí es donde se lográ mover la figura cte mente.
    glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
    DrawPlane(halfScreenWidth, halfScreenHeight+150, -325, 200); // Figura que se asigne dentro de pushMatrix()
    DrawPlane2(halfScreenWidth, halfScreenHeight+150, -325, 200); // Figura que se le aplican las tranformaciones anteriores.
    glPopMatrix();
}

// Función para dibujar el avión (el cuerpo)
void DrawPlane(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        //// EDIFICIO CENTRO
        // Cara Frontal
        centerPosX - halfSideLength+50, centerPosY  , centerPosZ  + 70, // Arriba Izquierda
        centerPosX + halfSideLength-50, centerPosY , centerPosZ + 70, // Arriba Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ + 70, // Abajo Derecha
        centerPosX - halfSideLength+50, centerPosY- 40, centerPosZ + 70, // Abajo Izquierda
        
        // Cara Posterior
        centerPosX - halfSideLength+50, centerPosY , centerPosZ  - 70, // Arriba Izquierda
        centerPosX + halfSideLength-50, centerPosY , centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ - 70, // Abajo Derecha
        centerPosX - halfSideLength+50, centerPosY - 40, centerPosZ - 70, // Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - halfSideLength+50, centerPosY , centerPosZ  + 70, // Arriba Izquierda
        centerPosX - halfSideLength+50, centerPosY , centerPosZ - 70, // Arriba Dereccha
        centerPosX - halfSideLength+50, centerPosY  - 40, centerPosZ  - 70, // Abajo Derecha
        centerPosX - halfSideLength+50, centerPosY - 40, centerPosZ + 70, // Abajo Izquierda
        
        // Cara Derecha
        centerPosX + halfSideLength-50, centerPosY , centerPosZ+ 70, // Arriba Izquierda
        centerPosX + halfSideLength-50, centerPosY  , centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ - 70, // Abajo Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ + 70, // Abajo Izquierda
        
        // Cara Superior
        centerPosX - halfSideLength+50, centerPosY , centerPosZ  + 70 , // Arriba Izquierda
        centerPosX - halfSideLength+50, centerPosY  , centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength-50, centerPosY  , centerPosZ - 70, // Abajo Derecha
        centerPosX + halfSideLength-50, centerPosY  , centerPosZ  + 70, // Abajo Izquierda
        
        // Cara Inferior
        centerPosX - halfSideLength+50, centerPosY - 40, centerPosZ + 70, // Arriba Izquierda
        centerPosX - halfSideLength+50, centerPosY - 40, centerPosZ - 70, // Arriba Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ  - 70, // Abajo Derecha
        centerPosX + halfSideLength-50, centerPosY - 40, centerPosZ  + 70
    
    };
    GLfloat colour[] = {
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           255.0, 255.0, 255.0,
           
        };
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

// Función para dibujar el avión (las alas)
void DrawPlane2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        // Cara Frontal
                centerPosX - halfSideLength+100, centerPosY  , centerPosZ  + 40, // Arriba Izquierda
                centerPosX + halfSideLength-100, centerPosY , centerPosZ + 40, // Arriba Derecha
                centerPosX + halfSideLength-20, centerPosY - 40, centerPosZ + 40, // Abajo Derecha
                centerPosX - halfSideLength+20, centerPosY- 40, centerPosZ + 40, // Abajo Izquierda
                
                // Cara Posterior
                centerPosX - halfSideLength+100, centerPosY , centerPosZ  - 40, // Arriba Izquierda
                centerPosX + halfSideLength-100, centerPosY , centerPosZ - 40, // Arriba Derecha
                centerPosX + halfSideLength-20, centerPosY - 40, centerPosZ - 40, // Abajo Derecha
                centerPosX - halfSideLength+20, centerPosY - 40, centerPosZ - 40, // Abajo Izquierda
                
                // Cara Izquierda
                centerPosX - halfSideLength+100, centerPosY , centerPosZ  + 40, // Arriba Izquierda
                centerPosX - halfSideLength+100, centerPosY , centerPosZ - 40, // Arriba Dereccha
                centerPosX - halfSideLength+20, centerPosY  - 40, centerPosZ  - 40, // Abajo Derecha
                centerPosX - halfSideLength+20, centerPosY - 40, centerPosZ + 40, // Abajo Izquierda
                
                // Cara Derecha
                centerPosX + halfSideLength-100, centerPosY , centerPosZ+ 40, // Arriba Izquierda
                centerPosX + halfSideLength-100, centerPosY  , centerPosZ - 40, // Arriba Derecha
                centerPosX + halfSideLength-20, centerPosY - 40, centerPosZ - 40, // Abajo Derecha
                centerPosX + halfSideLength-20, centerPosY - 40, centerPosZ + 40, // Abajo Izquierda
                
                // Cara Superior
                centerPosX - halfSideLength+100, centerPosY , centerPosZ  + 40 , // Arriba Izquierda
                centerPosX - halfSideLength+100, centerPosY  , centerPosZ - 40, // Arriba Derecha
                centerPosX + halfSideLength-100, centerPosY  , centerPosZ - 40, // Abajo Derecha
                centerPosX + halfSideLength-100, centerPosY  , centerPosZ  + 40, // Abajo Izquierda
                
                // Cara Inferior
                centerPosX - halfSideLength+100, centerPosY - 40, centerPosZ + 40, // Arriba Izquierda
                centerPosX - halfSideLength+100, centerPosY - 40, centerPosZ - 40, // Arriba Derecha
                centerPosX + halfSideLength-100, centerPosY - 40, centerPosZ  - 40, // Abajo Derecha
                centerPosX + halfSideLength-100, centerPosY - 40, centerPosZ  + 40
            
            };
            GLfloat colour[] = {
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                
                   
                };
            
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);
            glEnableClientState( GL_VERTEX_ARRAY );
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer( 3, GL_FLOAT, 0, vertices );
            glColorPointer(3, GL_FLOAT, 0, colour);
            glDrawArrays( GL_QUADS, 0, 24 );
            glDisableClientState( GL_VERTEX_ARRAY );
            glDisableClientState(GL_COLOR_ARRAY);
        
}

// Función para dibujar la ventana en la pared del cuarto
void DrawVentana(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f - 20;

    GLfloat vertices[] =
    {
        //// EDIFICIO CENTRO
        // Cara Frontal
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ + 10, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ + 10, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ + 10, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ + 10, // Abajo Izquierda

        // Cara Posterior
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ - 10, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ - 10, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ - 10, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ - 10, // Abajo Izquierda

        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ + 10, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ - 10, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY, centerPosZ - 10, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY, centerPosZ + 10, // Abajo Izquierda

        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ + 10, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ - 10, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ - 10, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY, centerPosZ + 10, // Abajo Izquierda

        // Cara Superior
        centerPosX - halfSideLength, centerPosY , centerPosZ + 10 , // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY  , centerPosZ - 10, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY  , centerPosZ - 10, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY  , centerPosZ + 10, // Abajo Izquierda

        // Cara Inferior
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ + 10, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + 100, centerPosZ - 10, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ - 10, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY + 100, centerPosZ + 10

    };
    GLfloat colour[] = {
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
           0.0, 0.0, 1.0,
    };

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colour);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
