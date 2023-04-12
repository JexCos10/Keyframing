#include <GL/glut.h>

struct Posicion {
    float x;
    float y;
};

struct Keyframe {
    int tiempo;
    Posicion pos;
};

Keyframe keyframes[4] = { {0, {-0.8, 0.0}}, {1000, {0.8, 0.0}}, {2000, {-0.8, 0.0}}, {3000, {0.8, 0.0}} };

Posicion Interpolar(Keyframe k1, Keyframe k2, int tiempoActual) {
    float t = (float)(tiempoActual - k1.tiempo) / (float)(k2.tiempo - k1.tiempo);
    float x = k1.pos.x + t * (k2.pos.x - k1.pos.x);
    float y = k1.pos.y + t * (k2.pos.y - k1.pos.y);
    return { x, y };
}

void DibujarObjeto(Posicion pos) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.1, 20, 20);
    glFlush();
}

void DibujarObjetoSinArgumentos() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Posicion pos = Interpolar(keyframes[0], keyframes[1], 0);
    glTranslatef(pos.x, pos.y, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.1, 20, 20);
    glFlush();
}

void Actualizar(int valor) {
    int tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    for (int i = 0; i < 3; i++) {
        if (tiempoActual >= keyframes[i].tiempo && tiempoActual < keyframes[i + 1].tiempo) {
            Posicion pos = Interpolar(keyframes[i], keyframes[i + 1], tiempoActual);
            DibujarObjeto(pos);
            break;
        }
    }
    glutTimerFunc(16, Actualizar, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Animacion con Keyframing");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(DibujarObjetoSinArgumentos);
    glutTimerFunc(0, Actualizar, 0);
    glutMainLoop();

    return 0;
}
