#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void updatePoint(GLfloat *point, float dampeningFactor, float t);

float x, y;

int main() {
    GLFWwindow *window;
    
    if (!glfwInit())
        return 1;
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Test", nullptr, nullptr);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment
    
    float t = -2;
    x = y = t;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    GLfloat pointVertex[] = {0, 0};
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glEnable( GL_POINT_SMOOTH ); // make the point circular
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glPointSize( 10 ); // must be added before glDrawArrays is called
        glVertexPointer( 2, GL_FLOAT, 0, pointVertex ); // point to the vertices to be used
        glDrawArrays( GL_POINTS, 0, 1 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
        glDisable( GL_POINT_SMOOTH ); // stop the smoothing to make the points circular
        
        updatePoint(pointVertex, 1, t);

        t += 0.1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}


void updatePoint(GLfloat *point, float dampeningFactor, float t) {
    // passed by reference?
    point[0] = dampeningFactor*(x*x + x*t + y);
    point[1] = dampeningFactor*(x*x - y*y - t*t - x*y + y*t - x + y);
    
    std::cout << point[0] << " " << point[1] << std::endl;
}
