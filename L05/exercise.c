#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#define FRAMERATE_FPS 60
#define REDRAW_PERIOD_NS 1000000000 / FRAMERATE_FPS

/* Returns: the time difference, in us */
long timediff(const struct timeval *start, const struct timeval *end){
    return 1000000 * (end->tv_sec - start->tv_sec) + 
        (end->tv_usec - start->tv_usec);
}

struct timeval last_render;

/* Global angular state. This is bad, bad, BAD. But not worth refactoring for
 * the sake of a tutorial exercise. */
GLfloat rtri = 0.0f, rquad = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

    glMatrixMode(GL_MODELVIEW);
}

void draw_scene(){
    struct timeval render_time;
    long wait_time;
    struct timespec wait_spec;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);

    /* Rotate the triangle on the Y axis. */
    glRotatef(rtri, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        //Front Face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        //Right Face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        //Back Face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        //Left Face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(1.5f, 0.0f, -7.0f);

    glRotatef(rquad, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        //Cube Top Face
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f,  1.0f);
        glVertex3f( 1.0f, 1.0f,  1.0f);

        //Bottom Face
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3f( 1.0f,-1.0f,  1.0f);
        glVertex3f(-1.0f,-1.0f,  1.0f);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);

        //Front Face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 1.0f, 1.0f,  1.0f);
        glVertex3f(-1.0f, 1.0f,  1.0f);
        glVertex3f(-1.0f,-1.0f,  1.0f);
        glVertex3f( 1.0f,-1.0f,  1.0f);

        //Back Face
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f( 1.0f, 1.0f, -1.0f);

        //Left Face
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f,  1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glVertex3f(-1.0f,-1.0f,  1.0f);

        //Right Face
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, -1.0f);
        glVertex3f( 1.0f, 1.0f,  1.0f);
        glVertex3f( 1.0f,-1.0f,  1.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);

    glEnd();
    glFlush();

    rtri += 0.8f;
    rquad -= 0.6f;

    gettimeofday(&render_time, NULL);
    wait_time = REDRAW_PERIOD_NS - (1000 * timediff(&last_render, &render_time));
    last_render.tv_sec = render_time.tv_sec;
    last_render.tv_usec = render_time.tv_usec;

    wait_spec.tv_nsec = wait_time % 1000000000;
    wait_spec.tv_sec = wait_time / 1000000000;
    nanosleep(&wait_spec, NULL);

    glutPostRedisplay();
}

void key_pressed(unsigned char key, int x, int y, int win){
    printf("Pressed key %c on coordinates (%d, %d)\n", key, x, y);
    if(key == 'q'){
        printf("Got q, so quitting\n");
        glutDestroyWindow(win);
        exit(0);
    }
}

int main(int argc, char **argv){
    /* Initialize glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);

    int win = glutCreateWindow("NeHe Lesson 2");

    /* Create a forward closure to avoid keeping global window state */
    void keypress_handler(unsigned char key, int x, int y){
        key_pressed(key, x, y, win);
    }

    glutDisplayFunc(draw_scene);
    glutKeyboardFunc(keypress_handler);

    glClearColor(0.0,0.0,0.0,0.0);
    InitGL(640, 480);
    gettimeofday(&last_render, NULL);
    glutMainLoop();
    
    return 0;
}
