
#include <GL/glut.h>
#include <cmath>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Wywoływana w celu przerysowania sceny
void RenderScene(void)
{
	GLfloat x, y, z, angle; // Zmienne przechowujšce współrzędne i kąty
	GLfloat sizes[2]; // Do zapisania dopuszczalnego zakresu wielkoci
	GLfloat step; // Zapamiętuje obsługiwany przyrost rozmiaru
	GLfloat curSize; // Zapamęituje aktualny rozmiar
					 // Wyczyszczenie okna aktualnym kolorem czyszczšcym
	glClear(GL_COLOR_BUFFER_BIT);
	// Zapisanie stanu macierzy i wykonanie obrotu
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// Pobranie dopuszczalnych rozmiarów punktów
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	// Ustalenie poczštkowego rozmiaru punktu
	curSize = sizes[0];
	// Ustalenie pocztkowej współrzędnej z
	y = -50.0f;
	// Obracamy się w kółko trzy razy
	for (angle = 0.0f; angle <= (2.0f*3.1415f)*15.0f; angle += 0.35f)
	{
		// Wyliczenie wartoci x i y na kole
		x = 50.0f*sin(angle);
		z = 50.0f*cos(angle);
		// Zdefiniowanie rozmiaru punktu przed utworzeniem obiektu podstawowego
		glPointSize(curSize);
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
		// Powiększenie współrzędnej z i rozmiaru punktu
		y += 1.2f;
		curSize += step;
	}
	// Odtworzenie macierzy przekształceń
	glPopMatrix();
	// Wykonanie poleceń rysowania
	glutSwapBuffers();
}
// Ta funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
void SetupRC()
{
	// Czarne tło
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Będziemy rysować kolorem zielonym
	glColor3f(0.0f, 1.0f, 0.0f);
}
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	// Odwieżenie zawartoci okna
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wymiarów widoku na zgodnych z wymiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Utworzenie przestrzeni ograniczajšcej (lewo, prawo, dół, góra, blisko, daleko)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * (h / 4) / w, nRange*h / w, -nRange, nRange);
	else//*w / h
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Sruba");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}