#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLint WIDTH = 128,HEIGHT=128;

GLfloat R = 0.0,
		G = 0.0,
		B = 0.0;

GLchar *FILE_PATH = "./resources/data.txt"; // relative from root path
GLchar *TITLE = "Lucas Camilo de Morais";
GLchar *DELIMITER = " ";

FILE* openFile(){
    FILE *file;
    file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    return file;
}

void closeFile(FILE* file){
    fclose(file);
}
void setColors(){
    glClearColor(R, G, B, 1.0);
	gluOrtho2D(-256.0, 256.0, -256.0, 256.0);
}
void draw(void){
    GLchar row[50];
    GLchar *str;
    FILE *file = openFile();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    while((fgets(row,50,file)) != NULL){
        GLint x, y;
        GLint updated = 0;
        str = strtok(row, DELIMITER);
        while(str!=NULL){
            if(updated == 0)
                x = atoi(str); 
            else
                y = atoi(str);
            updated = 1;
            str = strtok(NULL, DELIMITER);
        }
        // printf("x: %d, y: %d\n", x, y);
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
    closeFile(file);
}

void main(GLint argc, GLchar** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(TITLE);
    setColors();
    glutDisplayFunc(draw);
    glutMainLoop();
}