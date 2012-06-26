#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutWireTeapot(0.5);
    glFlush();
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    int win = glutCreateWindow("Yet another teapot");

    /* Create a forward closure to avoid keeping global window state */
    void keypress_handler(unsigned char key, int x, int y){
        key_pressed(key, x, y, win);
    }

    glutDisplayFunc(display);
    glutKeyboardFunc(keypress_handler);

    glClearColor(0.0,0.0,0.0,0.0);
    glutMainLoop();
    
    return 0;
}
