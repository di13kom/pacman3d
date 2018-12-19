#include <iostream>
//#include <fstream>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <FL/Fl_Shared_Image.H>
#include <algorithm>
//sound
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

//
#include "readfile.h"
#define MQAUDS 128
#define YCoor -0.19f
#define SLICES 10 //reduce cpu load
#define STACKS 10 //reduce cpu load


GLfloat ambient[]   = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat specular[]  = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = { 0.9 * 128.0 };          // 1=dull, 127=shiny
GLfloat emission[]  = { 0.0, 0.0, 0.0, 0.0 };
////
GLfloat ambient2[]   = { 0.0, 0.3, 0.8, 1.0 };
GLfloat diffuse2[]   = { 0.0, 0.3, 0.8, 1.0 };
GLfloat specular2[]  = { 0.0, 0.3, 0.8, 1.0 };
//
GLfloat ambient3[]   = { 0.7, 0.7, 0.7, 1.0 };
GLfloat diffuse3[]   = { 0.4, 0.4, 0.4, 1.0 };
GLfloat specular3[]  = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_position[] = {  0.0,  1.05,  0.0, 0.0 };  // XYZW (W=0: xyz=direction, W!=0, xyz=position)
GLfloat light_white[]    = {  0.5,  0.5,  0.5, 1.0 };
//GLfloat PacPos[] = {  0.0, -0.1, 0.0 };
GLfloat spot_direction_[] = {  0.0, -0.1, 0.0 };
GLfloat angle = 2.0;
GLint expa = 128;
///pacman yellow
GLfloat ambient4[]   = { 1.0, 1.0, 0.0, 1.0 };
GLfloat diffuse4[]   = { 1.0, 1.0, 0.0, 1.0 };
GLfloat specular4[]  = { 1.0, 1.0, 0.0, 1.0 };
//ghosts red
GLfloat ambient5[]   = { 1.0, 0.0, 0.0, 1.0 };
GLfloat diffuse5[]   = { 1.0, 0.0, 0.0, 1.0 };
GLfloat specular5[]  = { 1.0, 0.0, 0.0, 1.0 };
//ghosts green
GLfloat ambient6[]   = { 1.0, 1.0, 0.2, 1.0 };
GLfloat diffuse6[]   = { 1.0, 1.0, 0.2, 1.0 };
GLfloat specular6[]  = { 1.0, 1.0, 0.2, 1.0 };
//ghosts blue
GLfloat ambient7[]   = { 0.4, 1.0, 1.0, 1.0 };
GLfloat diffuse7[]   = { 0.4, 1.0, 1.0, 1.0 };
GLfloat specular7[]  = { 0.4, 1.0, 1.0, 1.0 };
//ghosts oragne
GLfloat ambient8[]   = { 1.0, 0.6, 0.8, 1.0 };
GLfloat diffuse8[]   = { 1.0, 0.6, 0.8, 1.0 };
GLfloat specular8[]  = { 1.0, 0.6, 0.8, 1.0 };
///light1
GLfloat light_position1[] = {  0.12,1.0,0.12, 1.0 };  // XYZW (W=0: xyz=direction, W!=0, xyz=position)
GLfloat light1[]    = {  1.0,  1.0,  1.0, 1.0 };
GLfloat spot_direction1[] = {  0.08, -0.2, 0.08};
GLfloat angle1 = 50.0;
GLint exp1 = 28;
//
///light2
GLfloat light_position2[] = {  -0.12,  1.0,  -0.12, 1.0 };  // XYZW (W=0: xyz=direction, W!=0, xyz=position)
GLfloat spot_direction2[] = {  -0.08, -0.2, -0.08};
//light3
GLfloat light_position3[] = {  0.12,1.0,-0.12, 1.0 };  // XYZW (W=0: xyz=direction, W!=0, xyz=position)
GLfloat spot_direction3[] = {  0.08, -0.2, -0.08};
//light4
GLfloat light_position4[] = {  -0.12,1.0,0.12, 1.0 };  // XYZW (W=0: xyz=direction, W!=0, xyz=position)
GLfloat spot_direction4[] = {  -0.08, -0.2, 0.08};
//ghosts blue
GLfloat ambient9[]   = { 0.0, 0.0, 1.0, 1.0 };
GLfloat diffuse9[]   = { 0.0, 0.0, 1.0, 1.0 };
GLfloat specular9[]  = { 0.0, 0.0, 1.0, 1.0 };
//tabletoragne
GLfloat ambient10[]   = { 1.0, 0.5, 0.0, 1.0 };
GLfloat diffuse10[]   = { 1.0, 0.5, 0.0, 1.0 };
GLfloat specular10[]  = { 1.0, 0.5, 0.0, 1.0 };

class MyGlWindow:public Fl_Gl_Window
{
	bool Paused;
	bool Reflected;
	bool Motion;
	bool NightMode;
	bool DMode;
	bool TbltShown;
	bool Blueness;
	int OffsetX;
	int OffsetZ;
	int ExOffsetX;
	int ExOffsetZ;
	GLUquadricObj* Sphere;
	GLUquadricObj* Cylinder;
	const char *texturefilename;
	GLuint TexID;
	GLfloat dis;
	GLfloat XX;
	int state;
	GLfloat i,j;
	GLfloat *MiniQuads;
	GLfloat *MiniTex;
	char* text;
	float TextX,TextY;
	char *txt;
	int Secs;
	bool PointsShow;
	int KilledGhosts;
	int cnt;
	bool LostLife;
	bool DotEaten;
	bool TabletEaten;
	ALuint buffer[7], source[7];
	ALint PlayState;
	//int PacPoint;
	void draw();
	void InitAl();
	void PlaySound(int);
	public:
	~MyGlWindow();
	void CalcQuads(GLfloat Am);
	MyGlWindow (int X, int Y, int W, int H, const char *L);
	void PrintMap();
	int handle(int e);
	void LoadTexture (const char *filename, GLuint & TexID);
	const char *TextureFilename () const;
	void DrawFloor();
	void DrawPacman();
	void DrawGhosts();
	void MovePacman();
	void MoveGhst();
	static void Movement(void *UserData);
	static void GhostsBlue(void *UserData);
};
