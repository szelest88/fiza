

//#define FREEGLUT_STATIC
#include <windows.h>              // musi by�, nie mo�na u�y� <stdio.h> zamiast tego
#define GLUT_DISABLE_ATEXIT_HACK  // musi by� u�yte przed includowaniem "glut.h"
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <io.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
static int slices = 16;
static int stacks = 16;

float ampli2=2.5;//0.5
float ampli=2.5;
float xcentrum=0,ycentrum=0;
float kulkax=0, kulkay=0;
float kulka2x=0,kulka2y=0, y2centrum=0,x2centrum=0,ampli3=0;
bool set=0;
float kat_patrzenia=0;
/* GLUT callback Handlers */

using namespace std;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glFrustum(-1,1,-2,2,2.0,10.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
	//troch� bez sensu, ale interferuje. Mo�e jakie� odbicie, poprawki kosmetyczne, wyb�r centrum fal i gra.


	//og�lnie trzeba generowa� te fale od �rodka do pewnego momentu, od momentu inicjalizacji, i powinno by� ok (fale powstaj� chyba wtedy, kiedy
	//co� jest w tej wodzie, a potem ju� nic tam nie powstaje w sumie, wzi�� misk� i sprawdzi� empirycznie).

	//dlaczego, kurna, to jest takie rozci�gni�te? A... Ju� chyba wiem.

	//zaraz, kurde, ustawi� kamer� jakos :F
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*30.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
//glRotated(a,0,0,1);
    glPushMatrix();
    glTranslated(0,0,-2);
        glTranslated(0,0,-6);
        glRotated(165+kat_patrzenia,1,0,0); //
        glRotated(45,0,0,1);
        //to robi co� baaardzo dziwnego. Nie wiem, co, ale chyba nie powinno tego robi�.
        glPushMatrix();
        glTranslated(-kulkay*0.4,-kulkax*0.1,0);

        glutSolidSphere(0.1,slices,stacks);

        glPopMatrix();
//EOSS (End Of Something Strange)
//glPointSize(1.5);

glBegin(GL_POINTS);
		glColor3f(0,0,1);
double r1,r1prim,r2prim;
double r2, r3, r4;
double skok_up=0.075;
double skok_dziedz=0.02;
int max=200;
for(int i=-0.3*max;i<0.3*max;i++)
        	{
	if(ampli>0)ampli-=0.00006; //hm... e^-x egzaminu nie zdaje, od biedy to jest w pewnym zakresie dobre przybli�enie - dlatego?
									//shit! Jak tu zaaplikowa� exponent?
									//kurwa, spr�bowa� to potem zr�niczkowa�, bo chyba tylko tak da si� zaimplementowa� w p�tli gradient ekpotencjalny


									// ja pierdol�... SVN.
	if(ampli2>0)ampli2-=0.00006;
	if(ampli3>0)ampli3-=0.00006;// chyba ok
	for(int j=-1.2*max;j<1.2*max;j++)
	{

        	r1=sqrt( (double)((j+xcentrum)*skok_up)*(double)((j+xcentrum)*skok_up)+(double)(skok_up*(i+ycentrum)*(i+ycentrum)));
        	r2=sqrt( (double)((j+xcentrum)*skok_up)*(double)((j+xcentrum)*skok_up)+(double)(skok_up*(i+ycentrum)*(i+ycentrum))); //i ju�?

        	r1prim=sqrt( (double)((j+x2centrum)*skok_up)*(double)((j+x2centrum)*skok_up)+(double)(skok_up*(i+y2centrum)*(i+y2centrum))); //hm.
        	r2prim=sqrt( (double)((j+x2centrum)*skok_up)*(double)((j+x2centrum)*skok_up)+(double)(skok_up*(i+y2centrum)*(i+y2centrum))); //hm.


            	r3=sqrt( (double)((j)*skok_up)*(double)((j)*skok_up)+(double)(skok_up*(i)*(i)));			// nie mam, kurna, poj�cia, czy to jest ok.
            	r4=sqrt( (double)((j)*skok_up)*(double)((j)*skok_up)+(double)(skok_up*(i)*(i))); //i ju�?

            	glVertex3f(i*skok_up,
            				j*skok_dziedz,
            		ampli/(r1*ampli+5)*cos(2*r1-a*0.1) + ampli/(r1*ampli+5)*cos(2*r1-a*0.1)
            		+
            		ampli2/(r3*ampli2+5)*cos(2*r3-a*0.1) + ampli2/(r4*ampli2+5)*cos(2*r4-a*0.1)
            		//hm.
            		+
            		ampli3/(r1prim*ampli3+5)*cos(2*r1prim-a*0.1) + ampli3/(r2prim*ampli3+5)*cos(2*r2prim-a*0.1)
            		//hm.
            		);
            		//c�, chyba interferuje :) Jakie� tam kreski si� tworz�, chyba nawet na oko tak, jak powinny si� tworzy� linie interferencyjne.
					// http://sciaga.onet.pl/_i/fizyka_sciaga/fizyka_1.jpg //o, tak to powinno wygl�da�. Huhu.
					// por�bane to troch� w rezultacie, ale jako� dzia�a. Dorobi� punkt wyboru "uderzenia" i poprawi� spos�b wygasania fali.

            	//jak zaimplementowa� odbicie?
            	float odleglosc; //szerokosc shitu
            	if(r1<odleglosc)
            	{
            		//r1 okre�la wsp�rz�dn�... Teraz tylko kwestia odwr�cenia fazy. Pytanie - jak?

            		//a mo�e nie w ifie, tylko doda� odpowiedni� warto�� przy warto�ci funkcji w glVertex? W tym jest potencja�
            	}
        	}
}

        glEnd();

    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
        	ampli+=2.0;
        	ampli2+=2.0;
        	ampli3+=2.0;
        	break;
        case '-':
        	if(ampli>1.4)
        	{ampli-=1.5;}else
        		ampli=0.2;

        	if(ampli2>1.4)
        	        	{ampli2-=1.5;}else
        	        		ampli2=0.2;
        	if(ampli3>1.4)
        	        	        	{ampli3-=1.5;}else
        	        	        		ampli3=0.2;
        	break;
        case 'a':

        							kulkax-=0.4;
        							kulka2x-=0.4;

                	break;
        case 'd':

        							kulkax+=0.4;
        							kulka2x+=0.4;


break;
        case 's':

        							kulkay-=0.2;
        							kulka2y-=0.2;


                	break;
                case 'w':

						kulkay+=0.2;
						kulka2y+=0.2;

                        	break;

                case ' ':
                	kat_patrzenia++;
                	break;
                case 'i':
                	if(!set){
                		if(ampli==0)
                		{ampli=ampli2;}else{ampli=0;}
                		ycentrum=kulkay*5;
                		xcentrum=kulkax*5;
                		ampli=ampli2;
                		set=1;
                	}else{
                		if(ampli3==0)
                		{ampli3=ampli2;}else{ampli3=0;} //ampli3, y2centrum, kulka2x
                		y2centrum=kulka2y*5;
                		x2centrum=kulka2x*5;
                		ampli3=ampli2;
                		set=0;
                	}

                	break;

    }

    glutPostRedisplay();
}

static void mychon(int x, int y, int a, int b)
{
	// tu co� by�o, ale ju� nie ma.

}
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(300,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Falownik v. 1.0. by AMaaaaaaaaaaaa IS... SPARTAAA!!! '+' - przy�o�enie w wod� /odl");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mychon);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return(0);
}
