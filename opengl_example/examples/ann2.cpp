#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>

GLuint octahedronList; // îêòàýäð
GLuint torusList;	// òîð
GLuint sphereList; // ñôåðà

double x_pos = 3.0, y_pos = 3.0, z_pos = 3.0, deep_pos = 0.0;
double r_diff = 1.0, g_diff = 1.0, b_diff = 1.0;

GLuint LoadTexture(const char * filename)
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

void init(void) {
	// èíèöèàëèçàöèÿ îñâåùåíèÿ è ôèãóð

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 }; // öâåò çåðêàëüíîãî îñâåùåíèÿ
	GLfloat position[] = { x_pos, y_pos, z_pos, deep_pos };

	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat local_view[] = { 0.0 };

	// ïàðàìåòðû ñâåòà
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); // ôîíîâîâîå îñâåùåíèå
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); // îïðåäåëÿåò öâåò ñâåòà èñòî÷íèêà
	glLightfv(GL_LIGHT0, GL_POSITION, position); // ìåñòîïîëîæåíèå
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	octahedronList = glGenLists(1);
	glNewList(octahedronList, GL_COMPILE);
	glutSolidOctahedron();
	glEndList();

	torusList = glGenLists(2);
	glNewList(torusList, GL_COMPILE);
	glutSolidTorus(1.0, 2.0, 200.0, 300.0);
	glEndList();

	sphereList = glGenLists(3);
	glNewList(sphereList, GL_COMPILE);
	glutSolidSphere(3.0, 200.0, 200.0);
	glEndList();
}

// ðåíäåð îêòàýäðîíà
void renderOctahedron(GLfloat x, GLfloat y, GLfloat ambr, GLfloat ambg, GLfloat ambb, GLfloat difr,
	GLfloat difg, GLfloat difb, GLfloat difa, GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
	GLfloat mat[4]; // ìàòåðèàë
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glTranslatef(x, y, 0.0);
	mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = difr; mat[1] = difg; mat[2] = difb; mat[3] = difa;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr; mat[1] = specg; mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);

	GLuint texture;	// load texture
	texture = LoadTexture("image.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);

	glCallList(octahedronList);

	glDisable(GL_TEXTURE_GEN_S); // disable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// ðåíäåð òîðà
void renderTorus(GLfloat x, GLfloat y, GLfloat ambr, GLfloat ambg, GLfloat ambb, GLfloat difr,
	GLfloat difg, GLfloat difb, GLfloat difa, GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
	GLfloat mat[4];
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glTranslatef(x, y, 0.0);
	mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = difr; mat[1] = difg; mat[2] = difb;  mat[3] = difa; // alfa - ïðîçðà÷íîñòü
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr; mat[1] = specg; mat[2] = specb;  mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);

	glEnable(GL_BLEND);		// íàëîæåíèå ñ ïðîçðà÷íîñòüþ
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCallList(torusList);
	glDisable(GL_BLEND);	// îòêëþ÷åíèå ïðîçðà÷íîñòè
	glPopMatrix();
}

// ðåíäåð ñôåðû
void renderSphere(GLfloat x, GLfloat y, GLfloat ambr, GLfloat ambg, GLfloat ambb, GLfloat difr,
	GLfloat difg, GLfloat difb, GLfloat difa, GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
	GLfloat mat[4];
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glTranslatef(x, y, 0.0);
	mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);  // ðàññåèâàþùèé
	mat[0] = difr; mat[1] = difg; mat[2] = difb; mat[3] = difa;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);  // äèôôóçíî-ðàññåèâàþùèé
	mat[0] = specr; mat[1] = specg; mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);  // îòðàæåííûé ñâåò
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);	// ñòåïåíü îòðàæåííîãî ñâåòà
	glCallList(sphereList);
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat diffuse[] = { r_diff, g_diff, b_diff, 1.0 };
	GLfloat position[] = { x_pos, y_pos, z_pos, deep_pos };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	glRotatef(0, 0, 0, 0);


	renderOctahedron(10.0, 5.0, 0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 1.0, 0.3, 0.3, 0.3, 0.015);


	renderTorus(15.0, 5.0, 0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 0.5, 0.3, 0.3, 0.3, 0.015);
	renderSphere(5.0, 5.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.9, 0.9, 0.9, 1.0);

	glFlush();
}



void Reshape(GLint w, GLint h) {
	//Width = w; Height = h;
	// óñòàíàâëèâàåì ðàçìåðû îáëàñòè îòîáðàæåíèÿ
	glViewport(0, 0, w, h);
	// îðòîãðàôè÷åñêàÿ ïðîåêöèÿ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 10.0 * w / h, 0.0, 10.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;

	case 'a':	// âëåâî
		x_pos -= 1.0;
		break;
	case 'w':	// ââåðõ
		y_pos += 1.0;
		break;
	case 'd':	// âïðàâî
		x_pos += 1.0;
		break;
	case 's':	// âíèç
		y_pos -= 1.0;
		break;
	case 'z':	// äàëüøå
		z_pos += 1.0;
		break;
	case 'x':	// áëèæå
		z_pos -= 1.0;
		break;

	case 'r':	// red -
		r_diff -= 0.2;
		break;
	case 'R':	// red +
		r_diff += 0.2;
		break;
	case 'g':	// green -
		g_diff -= 0.2;
		break;
	case 'G':	// green +
		g_diff += 0.2;
		break;
	case 'b':	// blue -
		b_diff -= 0.2;
		break;
	case 'B':	// blue +
		b_diff += 0.2;
		break;
	case 'o':	// èíòåíñèâíîñòü
		deep_pos -= 0.05;
		break;
	case 'O':	// èíòåíñèâíîñòü
		deep_pos += 0.05;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}