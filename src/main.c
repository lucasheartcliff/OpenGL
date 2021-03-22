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

GLint **coordenatesList;
GLint listSize = 0;

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
void setDefaultConfigs(GLint maxValue){
    GLint negativeValue = maxValue * -1;

    glClearColor(R, G, B, 1.0);
    gluOrtho2D(negativeValue, maxValue, negativeValue, maxValue);
}
void draw(){
    GLint **pointer = coordenatesList;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    for (GLint index = 0; index < listSize;index++){
        glVertex2i(pointer[index][0], pointer[index][1]);
    }

    glEnd();
    glFlush();
}

GLint getMaxValueFromCoordenates(){
    GLint maxValue = 0;
    GLint** pointer = coordenatesList;

    for (GLint index = 0; index < listSize;index++){
        for (GLint i=0;i<=1;i++){ 
            if (pointer[index][i] > maxValue){
                maxValue = pointer[index][i];
            }
        }
    }
    
    return maxValue;
}

void analyseCoordenatesFromFile(){
    GLchar row[50];
    GLchar *str;
    FILE *file = openFile();

    GLint count = 0;
    coordenatesList = (GLint **)malloc(10 * sizeof(GLint*));

    while((fgets(row,50,file)) != NULL){
        GLint x, y;
        GLint* coordenates = (GLint *)malloc(2 * sizeof(GLint));
        GLboolean updated = 0;

        str = strtok(row, DELIMITER);
        while(str!=NULL){
            if(updated == 0)
                x = atoi(str); 
            else
                y = atoi(str);
            updated = 1;
            str = strtok(NULL, DELIMITER);
        }

        if((count+1) % 10 == 0){
            coordenatesList = realloc(coordenatesList, (count + 11)  * sizeof(GLint *));
        }

        coordenates[0] = x;
        coordenates[1] = y;

        coordenatesList[count] = coordenates;
        count++;
    }
    listSize = count;
    closeFile(file);
}

void main(GLint argc, GLchar** argv){
    analyseCoordenatesFromFile();
    GLint maxValue = getMaxValueFromCoordenates();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(TITLE);
    setDefaultConfigs(maxValue);
    glutDisplayFunc(draw);
    glutMainLoop();
}