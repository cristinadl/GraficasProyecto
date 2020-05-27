//
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
void DrawVaso(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);


GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat translationX = 0.0f;
GLfloat translationY = 0.0f;


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

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // EspecÌfica en que parte de la ventana se dibujaran los elementos
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

        // Render (Se crea el cubo y se generan los cambios en los vectores de transformaciÛn
        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500); // Coloca el cubo al centro de la pantalla
        glTranslated(translationX, translationY, 0); // Mueve el cubo con las variables de las teclas (Vector de TraslaciÛn
        //AquÌ se crearÌa el vector de escalado
        glRotatef(rotationX, 1, 0, 0); // Rotar escena en X
        glRotatef(rotationY, 0, 1, 0); // Rotar escena en Y
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
//        glScalef(1.0f, 1.0f, 1.0f);
        DrawCuarto(halfScreenWidth, halfScreenHeight, -500, 500);
        DrawPata2(halfScreenWidth, halfScreenHeight -149, -600, 200);
        DrawPata3(halfScreenWidth, halfScreenHeight -149, -600, 200);
        DrawPata4(halfScreenWidth + 100, halfScreenHeight -149, -600, 200);
        DrawPata1(halfScreenWidth + 100, halfScreenHeight -149, -600, 200);
        DrawMesa(halfScreenWidth, halfScreenHeight -149, -600, 200);
        DrawVaso(halfScreenWidth + 75, halfScreenHeight - 10, -620, 200);


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

    // Switch en donde se determinan los movimientos del cubo en base a las teclas
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
        }


    }
}


void DrawCuarto( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
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
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // Abajo Izquierda
    };
    
    GLfloat colour[] = {
        200.0, 25.0, 0.0,
        200.0, 200.0, 0.0,
        200.0, 25.0, 0.0,
        25.0, 200.0, 0.0,
        25.0, 200.0, 20.0,
        25.0, 200.0, 20.0,
        25.0, 200.0, 20.0,
        255.0, 0.0, 20.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0,
        25.0, 0.0, 0.0
    };
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(4, GL_FLOAT, 0, colour);
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}


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

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // Se comentÛ esta linea para quitar poder hacer solidos a los objetos
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

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // Se comentÛ esta linea para quitar poder hacer solidos a los objetos
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
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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
        centerPosX + halfSideLength - 160, centerPosY - halfSideLength + 10, centerPosZ + 70

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
    
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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
