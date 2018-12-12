#include "playground3.h"

extern vector<point> pnt;
extern pacman *pcm;
extern vector <brick> brk;
extern vector <tablet> tblt;
extern vector <ghost> ghst;

void MyGlWindow::InitAl()
{
	alutInit(0, NULL);

	// Capture errors
	alGetError();
	//
	//         // Load pcm data into buffer
	buffer[0] = alutCreateBufferFromFile("sounds/pacman_eatghost.wav");
	buffer[1] = alutCreateBufferFromFile("sounds/pacman_death.wav");
	buffer[2] = alutCreateBufferFromFile("sounds/pacman_begining.wav");
	//buffer[3] = alutCreateBufferFromFile("sounds/PacmanCoin.wav");
	buffer[3] = alutCreateBufferFromFile("sounds/dot.wav");
	buffer[4] = alutCreateBufferFromFile("sounds/pacman_extrapac.wav");
	//buffer[4] = alutCreateBufferFromFile("sounds/energizer.wav");
	buffer[5] = alutCreateBufferFromFile("sounds/siren.wav");
	//
	alGetError();
	// Create sound source (use buffer to fill source)
	alGenSources(7, source);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[3], AL_BUFFER, buffer[3]);
	alSourcei(source[4], AL_BUFFER, buffer[4]);
	alSourcei(source[5], AL_BUFFER, buffer[5]);
}

void MyGlWindow::PlaySound(int ind)
{
	switch (ind)
	{
		case 0:
			alSourcePlay(source[0]);
			break;
		case 1:
			alSourcePlay(source[1]);
			break;
		case 2:
			alSourcePlay(source[2]);
			do
			{
				alGetSourcei(source[2], AL_SOURCE_STATE, &PlayState);
			}
			while (PlayState == AL_PLAYING);
			break;
		case 3:
			alSourcePlay(source[3]);
			break;
		case 4:
			alSourcePlay(source[4]);
			break;
		case 5:
			alSourcePlay(source[5]);
			break;
	}

	// Play
	/*alGetSourcei(source, AL_SOURCE_STATE, &PlayState);
	  if(PlayState == AL_PLAYING)
	  {
	  alSourceRewind(source);
	  }*/
	///alSourcePlay(source);
	//
	//         // Wait for the song to complete
	/*do
	  {
	  alGetSourcei(source, AL_SOURCE_STATE, &PlayState);
	  }
	  while (PlayState == AL_PLAYING);*/
}

MyGlWindow::~MyGlWindow()
{
	delete [] txt;
	delete [] text;
	delete [] MiniTex;
	delete [] MiniQuads;
	alDeleteSources(7, source);
	//alDeleteBuffers(7, buffer);

	// Exit everything
	cout<<"tst\n";
	alutExit();
}

void MyGlWindow::draw ()
{
	if (!valid ())
	{
		valid (1);
		glClearColor (0.0, 0.0, 0.0, 1.0);
		glClearAccum(0.0, 0.0, 0.0, 1.0);
		//printf("hello1\n");
		glEnable(GL_NORMALIZE);
		//glEnable(GL_POINT_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
		glGenTextures (1, &TexID);
		glBindTexture (GL_TEXTURE_2D, TexID);
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
		// Load texture image, bind to TexID
		LoadTexture (TextureFilename (), TexID);
		glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//
		//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
		//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glEnable (GL_TEXTURE_2D);

	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glViewport (0, 0, w (), h ());
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//----gluPerspective(120.0,/*1.0*/w()/h(),1.0,10.0);
	glFrustum(-0.5,0.5,-0.5,0.5,dis,5);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	//----gluLookAt(5,10,2,0,0,0,0,1,0);
	if(DMode)
	{
		gluLookAt(XX,2,2,1,1,1,0,1,0);
	}
	else
	{
		gluLookAt(0.01,3,0,0,0,0,0,1,0);
		glRotatef(90,0,1,0);
	}
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_white);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction_);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, expa);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, angle);
	///light1
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, exp1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, angle1);
	///
	///light2
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT,  light1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
	glLighti(GL_LIGHT2, GL_SPOT_EXPONENT, exp1);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, angle1);
	//light3
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT3, GL_AMBIENT,  light1);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
	glLighti(GL_LIGHT3, GL_SPOT_EXPONENT, exp1);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, angle1);

	//light4
	glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
	glLightfv(GL_LIGHT4, GL_AMBIENT,  light1);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction4);
	glLighti(GL_LIGHT4, GL_SPOT_EXPONENT, exp1);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, angle1);

	if(!NightMode)
	{
		//cout<<"NightMode off"<<endl;
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
	}
	else
	{
		//cout<<"NightMode on"<<endl;
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
	}
	glEnable(GL_LIGHTING);
	///
	if(Reflected)
	{
		glDisable(GL_DEPTH_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		DrawFloor();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if ==1 */
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		glPushMatrix();

		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0,0.35,0.0);

		//PrintMap();
		DrawGhosts();
		DrawPacman();
		glPopMatrix();
		glDisable(GL_STENCIL_TEST);

		glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		DrawFloor();
		glDisable(GL_BLEND);
		DrawPacman();
		if(Motion)
		{
			//glDrawBuffer(GL_BACK);
			//glReadBuffer(GL_BACK);
			glAccum(GL_MULT, 0.4);
			glAccum(GL_ACCUM, 0.6);
			glAccum(GL_RETURN, 1.0);
			//glFlush();
		}
		PrintMap();
		DrawGhosts();
	}
	else
	{
		DrawFloor();
		DrawPacman();
		if(Motion)
		{
			//glDrawBuffer(GL_BACK);
			//glReadBuffer(GL_BACK);
			glAccum(GL_MULT, 0.4);
			glAccum(GL_ACCUM, 0.6);
			glAccum(GL_RETURN, 1.0);
			//glFlush();
		}
		PrintMap();
		DrawGhosts();
	}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHTING);
	if(!DMode)
		glRotatef(-90,0,1,0);
	if(Paused)
	{
		glColor3f(1.0,1.0,1.0);
		gl_font(1,20);
		strcpy(text,"Press Space to continue");
		//gl_draw(text,strlen(text),TextX,TextY);
		gl_draw(text,strlen(text),-.8f,1.2f);
	}
	else
	{
		glColor3f(0.7,1.0,0.0);
		gl_font(5,16);
		sprintf(txt,"Points: %d", pcm->Points);
		//cout<<txt<<endl;
		gl_draw(txt,strlen(txt),0.7f,1.2f);
		sprintf(txt,"Lives : %d", pcm->lives);
		//cout<<txt<<endl;
		gl_draw(txt,strlen(txt),0.7f,1.1f);
		glColor3f(0.0,1.0,1.0);
		gl_font(2,10);
		sprintf(txt,"Reflection: %s", Reflected ?"Yes" :"No");
		gl_draw(txt,strlen(txt),0.7f,1.3f);
		sprintf(txt,"Motion blur: %s", Motion?"Yes" :"No");
		gl_draw(txt,strlen(txt),0.7f,1.4f);
		sprintf(txt,"NightMode: %s", NightMode?"Yes" :"No");
		gl_draw(txt,strlen(txt),0.7f,1.5f);
		sprintf(txt,"3dMode: %s", DMode?"Yes" :"No");
		gl_draw(txt,strlen(txt),0.7f,1.6f);
	}
	if(Blueness)
	{
		//cout<<"helloblue"<<endl;
		glColor3f(1.0,0.0,0.0);
		gl_font(1,15);
		sprintf(txt,"Super Power: %d", Secs);
		gl_draw(txt,strlen(txt),-0.8f,1.2f);
		if(TabletEaten)
		{
			PlaySound(4);
			TabletEaten=false;
		}
	}
	if(PointsShow)
	{
		//cout<<"hello Point Test"<<endl;
		glColor3f(0.0,1.0,0.0);
		gl_font(1,8);
		glPushMatrix();
		//glTranslatef(PointsCoor[0],-0.18,PointsCoor[1]);
		sprintf(txt,"+%d",200*cnt);
		gl_draw(txt,strlen(txt),0.0f,0.0f);
		glPopMatrix();
		PointsShow=false;
		PlaySound(0);
	}
	if(LostLife)
	{
		glColor3f(1.0,0.0,0.0);
		gl_font(1,18);
		glPushMatrix();
		//glTranslatef(PointsCoor[0],-0.18,PointsCoor[1]);
		sprintf(txt,"oops,remain %d lives",pcm->lives);
		gl_draw(txt,strlen(txt),-1.0f,1.0f);
		glPopMatrix();
		PlaySound(1);
		LostLife=false;
	}
	if(DotEaten)
	{
		PlaySound(3);
		DotEaten=false;
	}
	if(!Paused)
	PlaySound(5);
}

void MyGlWindow::CalcQuads(GLfloat Am)
{
	GLfloat TempX,TempZ,TempX1,TempZ1;
	GLfloat TempXt,TempZt,TempX1t,TempZ1t;
	GLfloat Step=(2)/Am;
	GLfloat TexStep=1/Am;
	int i,j;
	int r=0;
	int k=0;
	for(i=0;i<Am;i++)
	{
		if(i==0)
		{
			TempZ=-1.0+Step*i;	
			TempZt=-1.0+TexStep*i;
		}
		else
		{
			TempZ=TempZ1;
			TempZt=TempZ1t;
		}
		TempZ1=-1.0+Step*(i+1);	
		TempZ1t=-1.0+TexStep*(i+1);
		for(j=0;j<Am;j++)
		{
			if(j==0)
			{
				TempX=-1.0+Step*j;	
				TempXt=-1.0+TexStep*j;
			}
			else
			{
				TempX=TempX1;
				TempXt=TempX1t;
			}
			TempX1=-1.0+Step*(j+1);	
			TempX1t=-1.0+TexStep*(j+1);
			////
			MiniQuads[r++]=TempX;
			MiniQuads[r++]=-0.2;
			MiniQuads[r++]=TempZ;

			MiniQuads[r++]=TempX;
			MiniQuads[r++]=-0.2;
			MiniQuads[r++]=TempZ1;

			MiniQuads[r++]=TempX1;
			MiniQuads[r++]=-0.2;
			MiniQuads[r++]=TempZ1;

			MiniQuads[r++]=TempX1;
			MiniQuads[r++]=-0.2;
			MiniQuads[r++]=TempZ;

			MiniTex[k++]=TempXt;
			MiniTex[k++]=TempZt;

			MiniTex[k++]=TempXt;
			MiniTex[k++]=TempZ1t;

			MiniTex[k++]=TempX1t;
			MiniTex[k++]=TempZ1t;

			MiniTex[k++]=TempX1t;
			MiniTex[k++]=TempZt;
		}
	}
	//printf("r:%d\n",r);
}

MyGlWindow::MyGlWindow (int X, int Y, int W, int H, const char *L = 0):Fl_Gl_Window (X, Y, W, H, L)
{
	mode (FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE | FL_ACCUM | FL_STENCIL);
	dis=1;
	XX=2;
	state=0;
	texturefilename="index.jpeg";
	Sphere=gluNewQuadric();
	Cylinder=gluNewQuadric();
	MiniTex = new GLfloat[MQAUDS*MQAUDS*3*4];
	MiniQuads = new GLfloat[MQAUDS*MQAUDS*3*4];
	CalcQuads(MQAUDS);
	TextX=-1.8f;
	TextY=1.f;
	MakeMap((char*)"level1.mf");
	//pcm->X=pcm->X;
	//pcm->Z=pcm->Z;
	OffsetX=0;
	OffsetZ=0;
	ExOffsetX=0;
	ExOffsetZ=0;
	Paused=1;
	Reflected=0;
	//PacPoint=0;
	Motion=0;
	NightMode=0;
	DMode=1;
	TbltShown=1;
	Secs=10;
	PointsShow=false;
	KilledGhosts=1;
	Blueness=false;
	txt = new char[20];
	text = new char[40];
	InitAl();
	LostLife=false;
	DotEaten=false;
	TabletEaten=false;
}

void MyGlWindow::PrintMap()
{
	//points
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular3);
	for(unsigned i=0;i<pnt.size();i++)
	{
		glPushMatrix();
		glTranslatef(pnt[i].X/100,-0.18,pnt[i].Z/100);
		gluSphere(Sphere,0.012,SLICES,STACKS);
		glPopMatrix();

	}
	glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  specular2);
	glColor3f(0.0,0.0,0.5);// glColor3f(0,0,0);

	for(unsigned i=0;i<brk.size();i++)
	{
		glPushMatrix();
		switch (brk[i].type)
		{
			case 1:
				glTranslatef((brk[i].X-5)/100,-0.18,brk[i].Z/100);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				break;

			case 2:
				glTranslatef(brk[i].X/100,-0.18,(brk[i].Z-5)/100);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				break;

			case 3:
				glTranslatef(brk[i].X/100,-0.18,brk[i].Z/100);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;

			case 4:
				glTranslatef(brk[i].X/100,-0.18,brk[i].Z/100);
				glRotatef(270.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glRotatef(270.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;

			case 5:
				glTranslatef(brk[i].X/100,-0.18,brk[i].Z/100);
				glRotatef(270.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;

			case 6:
				glTranslatef(brk[i].X/100,-0.18,brk[i].Z/100);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;
			case 7:
				glTranslatef(brk[i].X/100,-0.18,(brk[i].Z-5)/100);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glTranslatef(-0.05,0.00,0.05);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				break;

			case 8:
				glTranslatef((brk[i].X-5)/100,-0.18,brk[i].Z/100);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				glRotatef(-90.0,0.0,1.0,0.0);
				glTranslatef(0.05,0.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;

			case 9:
				glTranslatef(brk[i].X/100,-0.18,(brk[i].Z-5)/100);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				glTranslatef(0,0,0.05);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				break;

			case 0:
				glTranslatef((brk[i].X-5)/100,-0.18,brk[i].Z/100);
				glRotatef(90.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.05,SLICES,STACKS);
				glTranslatef(0.05,0,0.05);
				glRotatef(270.0,0.0,1.0,0.0);
				gluCylinder(Cylinder,0.015,0.015,0.1,SLICES,STACKS);
				break;
		}
		glPopMatrix();
	}
	//tablets
	if(TbltShown)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient10);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse10);
		glMaterialfv(GL_FRONT, GL_SPECULAR,specular10);
		for(unsigned i=0;i<tblt.size();i++)
		{
			glPushMatrix();
			glTranslatef(tblt[i].X/100,-0.18,tblt[i].Z/100);
			gluSphere(Sphere,0.02,SLICES,STACKS);
			glPopMatrix();

		}
	}
}

int MyGlWindow::handle(int e)
{
	switch(e)
	{
		case FL_MOUSEWHEEL:
			{
				if(Fl::event_dy() > 0)
				{
					if(dis<2)dis+=0.1;
				}
				else 
				{
					if(dis>0.8)dis-=0.1;
				}
				redraw();
				return 1;
			}

		case FL_DRAG:
			{
				if(XX<=2.5&&XX>=1.5)
				{
					if(Fl::event_x()>state) 
					{
						XX+=0.1;
						if(XX>2.5)XX=2.5;
					}
					else 
					{
						XX-=0.1;
						if(XX<1.5)XX=1.5;
					}
					state=Fl::event_x();
				}
				redraw();
				return 1;
			}
		case FL_PUSH:
			{
				return 1;
			}
		case FL_SHORTCUT:
			{
				switch(Fl::event_key())
				{
					case FL_Page_Up:
						if(angle<90)
							angle+=1;
						redraw();
						//printf("angle - %f\n",angle);
						return 1;
					case FL_Page_Down:
						if(angle>1)
							angle-=1;
						redraw();
						//printf("angle - %f\n",angle);
						return 1;
					case FL_Left:
						OffsetX=-10;
						OffsetZ=0;
						return 1;
					case FL_Right:
						OffsetX=+10;
						OffsetZ=0;
						return 1;
					case FL_Up:
						OffsetZ=-10;
						OffsetX=0;
						return 1;
					case FL_Down:
						OffsetZ=+10;
						OffsetX=0;
						return 1;
					case 32:
						Paused=!Paused;
						if(!Paused)
						{
							Fl::add_timeout(0.4,Movement, this);
						}
						else
						{
							Fl::remove_timeout(Movement);
							redraw();
						}
						//cout<<Paused<<endl;
						return 1;
					case 114:
						Reflected=!Reflected;
						if(Paused)redraw();
						return 1;
					case 109:
						Motion=!Motion;
						if(Motion)
						{
							glClear(GL_ACCUM_BUFFER_BIT);
						}
						if(Paused)redraw();
						return 1;
					case 110:
						NightMode=!NightMode;
						if(Paused)redraw();
						//cout<<"nigh:"<<NightMode<<endl;
						return 1;
					case 100:
						DMode=!DMode;
						if(Paused)redraw();
						//redraw();
						return 1;
				}
			}
	}
	return Fl_Gl_Window::handle(e);
}

void MyGlWindow::LoadTexture (const char *filename, GLuint & TexID)
{
	Fl_Shared_Image *img = Fl_Shared_Image::get (filename); // load texturemap
	if (!img)
	{
		fprintf (stderr, "%s: unknown image format\n", filename);
		exit (1);
	}
	if (img->d () != 3)
	{
		fprintf (stderr,
				"%s: image depth is %d (expected 3)\n", filename, img->d ());
		exit (1);
	}
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, img->w (), img->h (), 0,
			GL_RGB, GL_UNSIGNED_BYTE, img->data ()[0]);
	img->release ();
}

const char *MyGlWindow::TextureFilename () const
{
	return (texturefilename);
}

void MyGlWindow::DrawFloor()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION,  emission);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, MiniQuads);
	glTexCoordPointer(2, GL_FLOAT, 0,MiniTex);
	glDrawArrays(GL_QUADS, 0, MQAUDS*MQAUDS*4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MyGlWindow::DrawPacman()
{
	//pac
	//glColor3f(1.0,1.0,0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular4);
	//UP
	//curve
	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z-5)/100);
	glRotatef(68.0,0.0,1.0,0.0);
	gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z-5)/100);
	glRotatef(-68.0,0.0,1.0,0.0);
	gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
	glPopMatrix();
	//curve2
	if(ExOffsetX>0)
	{
		glPushMatrix();
		glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z-3)/100);
		if(pcm->Step==0)
		{
			glRotatef(15.0,0.0,1.0,0.0);
		}
		else
		{
			glRotatef(-45.0,0.0,1.0,0.0);
		}
		gluCylinder(Cylinder,0.007,0.007,0.04,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z-3)/100);
		glRotatef(-15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.045,SLICES,STACKS);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z-3)/100);
		if(pcm->Step==0)
		{
			glRotatef(-15.0,0.0,1.0,0.0);
		}
		else
		{
			glRotatef(45.0,0.0,1.0,0.0);
		}
		gluCylinder(Cylinder,0.007,0.007,0.045,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z-3)/100);
		glRotatef(15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.04,SLICES,STACKS);
		glPopMatrix();
	}
	//pnt
	//curv
	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z-5)/100);
	gluSphere(Cylinder,0.007,SLICES,STACKS);
	glPopMatrix();

	//curv2
	glPushMatrix();
	glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z-3)/100);
	gluSphere(Cylinder,0.01,SLICES,STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z-3)/100);
	gluSphere(Cylinder,0.01,SLICES,STACKS);
	glPopMatrix();

	//glPushMatrix();
	//glRotatef(180,0.0,1.0,0.0);
	//Down
	//curve
	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z+5)/100);
	glRotatef(180.0,1.0,0.0,0.0);
	glRotatef(68.0,0.0,1.0,0.0);
	gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z+5)/100);
	glRotatef(180.0,1.0,0.0,0.0);
	glRotatef(-68.0,0.0,1.0,0.0);
	gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
	glPopMatrix();
	//curve2
	if(ExOffsetX>0)
	{
		glPushMatrix();
		glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z+3)/100);
		glRotatef(180.0,1.0,0.0,0.0);
		if(pcm->Step==0)
		{
			glRotatef(15.0,0.0,1.0,0.0);
		}
		else
		{
			glRotatef(-45.0,0.0,1.0,0.0);
		}
		gluCylinder(Cylinder,0.007,0.007,0.045,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z+3)/100);
		glRotatef(180.0,1.0,0.0,0.0);
		glRotatef(-15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.04,SLICES,STACKS);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z+3)/100);
		glRotatef(180.0,1.0,0.0,0.0);
		if(pcm->Step==0)
		{
			glRotatef(-15.0,0.0,1.0,0.0);
		}
		else
		{
			glRotatef(45.0,0.0,1.0,0.0);
		}
		gluCylinder(Cylinder,0.007,0.007,0.04,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z+3)/100);
		glRotatef(180.0,1.0,0.0,0.0);
		glRotatef(15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.04,SLICES,STACKS);
		glPopMatrix();
	}
	//pnt
	//curv
	glPushMatrix();
	glTranslatef((pcm->X)/100,YCoor,(pcm->Z+5)/100);
	gluSphere(Cylinder,0.007,SLICES,STACKS);
	glPopMatrix();

	//curv2
	glPushMatrix();
	glTranslatef((pcm->X+3)/100,YCoor,(pcm->Z+3)/100);
	glRotatef(180.0,1.0,0.0,0.0);
	gluSphere(Cylinder,0.01,SLICES,STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((pcm->X-3)/100,YCoor,(pcm->Z+3)/100);
	glRotatef(180.0,1.0,0.0,0.0);
	gluSphere(Cylinder,0.01,SLICES,STACKS);
	glPopMatrix();
	//glPopMatrix();
}

void MyGlWindow::DrawGhosts()
{
	//ghosts
	for(unsigned i=0;i<ghst.size();i++)
	{
		if(ghst[i].Blue)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient9);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse9);
			glMaterialfv(GL_FRONT, GL_SPECULAR,specular9);
		}
		else
		{
			switch(i)
			{
				case 0:
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient5);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse5);
					glMaterialfv(GL_FRONT, GL_SPECULAR,specular5);
					break;
				case 1:
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient6);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse5);
					glMaterialfv(GL_FRONT, GL_SPECULAR,specular6);
					break;
				case 2:
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient7);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse7);
					glMaterialfv(GL_FRONT, GL_SPECULAR,specular7);
					break;
				case 3:
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient8);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse8);
					glMaterialfv(GL_FRONT, GL_SPECULAR,specular8);
					break;
			}
		}
		//vertical
		glPushMatrix();
		glTranslatef((ghst[i].X-4)/100,YCoor,(ghst[i].Z+3)/100);
		gluCylinder(Cylinder,0.007,0.005,0.05,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X+4)/100,YCoor,(ghst[i].Z+3)/100);
		gluCylinder(Cylinder,0.007,0.007,0.05,SLICES,STACKS);
		glPopMatrix();
		//curve
		glPushMatrix();
		glTranslatef((ghst[i].X)/100,YCoor,(ghst[i].Z-3)/100);
		glRotatef(68.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X)/100,YCoor,(ghst[i].Z-3)/100);
		glRotatef(-68.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.03,SLICES,STACKS);
		glPopMatrix();
		//curve2
		glPushMatrix();
		glTranslatef((ghst[i].X+3)/100,YCoor,(ghst[i].Z-1)/100);
		glRotatef(15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.045,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X-3)/100,YCoor,(ghst[i].Z-1)/100);
		glRotatef(-15.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.007,0.007,0.045,SLICES,STACKS);
		glPopMatrix();
		//pnt
		//curv
		glPushMatrix();
		glTranslatef((ghst[i].X)/100,YCoor,(ghst[i].Z-3)/100);
		gluSphere(Cylinder,0.01,SLICES,STACKS);
		glPopMatrix();

		//curv2
		glPushMatrix();
		glTranslatef((ghst[i].X+3)/100,YCoor,(ghst[i].Z-1)/100);
		gluSphere(Cylinder,0.01,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X-3)/100,YCoor,(ghst[i].Z-1)/100);
		gluSphere(Cylinder,0.01,SLICES,STACKS);
		glPopMatrix();
		//legs
		glPushMatrix();
		glTranslatef((ghst[i].X-4)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(-205.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.005,0.03,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X+4)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(205.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.007,0.03,SLICES,STACKS);
		glPopMatrix();
		//legs2
		glPushMatrix();
		glTranslatef((ghst[i].X-2)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(-155.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.005,0.03,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X+2)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(155.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.007,0.03,SLICES,STACKS);
		glPopMatrix();
		//legs3
		glPushMatrix();
		glTranslatef((ghst[i].X-2)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(-205.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.005,0.03,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X+2)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(205.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.007,0.03,SLICES,STACKS);
		glPopMatrix();
		//legs4
		glPushMatrix();
		glTranslatef((ghst[i].X)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(-155.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.005,0.03,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X)/100,YCoor,(ghst[i].Z+8)/100);
		glRotatef(155.0,0.0,1.0,0.0);
		gluCylinder(Cylinder,0.002,0.007,0.03,SLICES,STACKS);
		glPopMatrix();
		//eyes
		//if(ghst[i].Blue)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
			glMaterialfv(GL_FRONT, GL_SPECULAR,specular3);
		}
		/*else
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient9);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse9);
			glMaterialfv(GL_FRONT, GL_SPECULAR,specular9);
		}*/
		glPushMatrix();
		glTranslatef((ghst[i].X+2)/100,YCoor,(ghst[i].Z+1)/100);
		gluSphere(Cylinder,0.015,SLICES,STACKS);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((ghst[i].X-2)/100,YCoor,(ghst[i].Z+1)/100);
		gluSphere(Sphere,0.015,SLICES,STACKS);
		glPopMatrix();
	//ghosts end
	}
}

void MyGlWindow::MovePacman()
{
	//MyGlWindow *UsrTC = (MyGlWindow*) UserData;
	if(++pcm->Step>1)pcm->Step=0;
	for(unsigned i=0;i<pnt.size();i++)
	{
		if((pcm->X==pnt[i].X)&&(pcm->Z==pnt[i].Z))
		{
			pnt.erase(pnt.begin()+i);
			//UsrTC->PacPoint+=10;
			pcm->Points+=10;
			DotEaten=true;
			break;
		}
	}
	for(unsigned i=0;i<tblt.size();i++)
	{
		if((pcm->X==tblt[i].X)&&(pcm->Z==tblt[i].Z))
		{
			tblt.erase(tblt.begin()+i);
			for(unsigned i=0;i<ghst.size();i++)
				ghst[i].Blue=1;
			Blueness=true;
			TabletEaten=true;
			Secs=10;
			Fl::remove_timeout(GhostsBlue);
			Fl::add_timeout(1,GhostsBlue,this);
			break;
		}
	}

	for(unsigned i=0;i<brk.size();i++)
	{
		if((pcm->X+OffsetX==brk[i].X)&&(pcm->Z+OffsetZ==brk[i].Z))
		{
			for(unsigned i=0;i<brk.size();i++)
			{
				if((pcm->X+ExOffsetX==brk[i].X)&&(pcm->Z+ExOffsetZ==brk[i].Z))
				{
					//Fl::repeat_timeout(0.4,MovePacman,UserData);
					return;
				}
			}
			pcm->X+=ExOffsetX;
			pcm->Z+=ExOffsetZ;
			//Fl::repeat_timeout(0.4,MovePacman,UserData);
			//UsrTC->redraw();
			return;
		}
	}
	pcm->X+=OffsetX;
	pcm->Z+=OffsetZ;
	ExOffsetX=OffsetX;
	ExOffsetZ=OffsetZ;
	if(pcm->X<(-95))
	{
		pcm->X=95;
	}
	if(pcm->X>(95))
	{
		pcm->X=-95;
	}
	if(pcm->Z<(-95))
	{
		pcm->Z=95;
	}
	if(pcm->Z>(95))
	{
		pcm->Z=-95;
	}
	//UsrTC->redraw();
	//Fl::repeat_timeout(0.4,MovePacman,UserData);
	return;
}

void MyGlWindow::MoveGhst()
{
	//MyGlWindow *UsrTC = (MyGlWindow*) UserData;
	unsigned AmountUsedSteps;
	vector <int> UsedSteps;
	int /*flag,*/flag2;
	unsigned tmp;
	int XX,ZZ;
	for(int j=0;j<4;j++)UsedSteps.push_back(j);

	for(unsigned i=0;i<ghst.size();i++)
	{
		XX=0;
		ZZ=0;

		random_shuffle(UsedSteps.begin(),UsedSteps.end());
		AmountUsedSteps=0;

		for(unsigned j=0;j<UsedSteps.size()-1;j++)
		{
			if(UsedSteps[j]==ghst[i].PrevStep)
			{
				swap(UsedSteps[j],UsedSteps[3]);
				break;
			}
		}
		while(AmountUsedSteps<=3)
		{
			flag2=0;

			tmp=UsedSteps[AmountUsedSteps];
			AmountUsedSteps++;
			switch(tmp)
			{
				case 0:
					XX=-10;
					ZZ=0;
					break;
				case 1:
					XX=0;
					ZZ=-10;
					break;
				case 2:
					XX=10;
					ZZ=0;
					break;
				case 3:
					XX=0;
					ZZ=10;
					break;
			}

			//meeting with brick
			for(unsigned j=0;j<brk.size();j++)
			{
				if(ghst[i].X+XX==brk[j].X&&ghst[i].Z+ZZ==brk[j].Z)
				{
					XX=0;
					ZZ=0;
					flag2++;
					break;
				}
			}
			if(flag2)continue;

			break;
		}
		ghst[i].X+=XX;
		ghst[i].Z+=ZZ;
		if(ghst[i].X<(-95))
		{
			ghst[i].X=95;
		}
		if(ghst[i].X>(95))
		{
			ghst[i].X=-95;
		}
		if(ghst[i].Z<(-95))
		{
			ghst[i].Z=95;
		}
		if(ghst[i].Z>(95))
		{
			ghst[i].Z=-95;
		}
		//---UsedSteps.clear();
		switch(tmp)
		{
			case 0:
				ghst[i].PrevStep=2;
				break;
			case 1:
				ghst[i].PrevStep=3;
				break;
			case 2:
				ghst[i].PrevStep=0;
				break;
			case 3:
				ghst[i].PrevStep=1;
				break;
		}
	}
	//UsrTC->redraw();
	//Fl::repeat_timeout(0.4 ,MoveGhst, UserData);
	return;
}

void MyGlWindow::Movement(void *UserData)
{
	MyGlWindow *UsrTC = (MyGlWindow*) UserData;
	UsrTC->MovePacman();
	UsrTC->MoveGhst();
	int PrStpX;
	int PrStpZ;
	UsrTC->TbltShown=!UsrTC->TbltShown;
	for(unsigned i=0;i<ghst.size();i++)
	{
		PrStpZ=0;
		PrStpX=0;
		switch(ghst[i].PrevStep)
		{
			case 0:
				PrStpX=10;
				break;
			case 1:
				PrStpZ=10;
				break;
			case 2:
				PrStpX=-10;
				break;
			case 3:
				PrStpZ=-10;
				break;
		}
		if((ghst[i].X==pcm->X&&ghst[i].Z==pcm->Z)||(ghst[i].X-PrStpX==pcm->X&&ghst[i].Z-PrStpZ==pcm->Z&&ghst[i].X==pcm->X-UsrTC->ExOffsetX&&ghst[i].Z==pcm->Z-UsrTC->ExOffsetZ))
		{
			if(ghst[i].Blue)
			{
				pcm->Points+=200*UsrTC->KilledGhosts;
				UsrTC->PointsShow=true;
				UsrTC->cnt=UsrTC->KilledGhosts;
				//UsrTC->PointsCoor[0]=ghst[i].X;
				//UsrTC->PointsCoor[1]=ghst[i].Z;
				ghst[i].X=ghst[i].StartPosX;
				ghst[i].Z=ghst[i].StartPosZ;
				UsrTC->KilledGhosts++;
				ghst[i].Blue=0;
			}
			else
			{
				pcm->lives-=1;
				UsrTC->LostLife=true;
				pcm->X=pcm->StartPosX;
				pcm->Z=pcm->StartPosZ;
				for(unsigned i=0;i<ghst.size();i++)
				{
					ghst[i].X=ghst[i].StartPosX;
					ghst[i].Z=ghst[i].StartPosZ;
				}
			}
			//break;
		}
	}
	UsrTC->redraw();
	Fl::repeat_timeout(0.4 ,Movement, UserData);
}

void MyGlWindow::GhostsBlue(void *UserData)
{
	MyGlWindow *UsrTC = (MyGlWindow*) UserData;
	if(UsrTC->Secs)
	{
		UsrTC->Secs--;
		Fl::repeat_timeout(1,GhostsBlue,UserData);
		return;
	}
	else
	{
		for(unsigned i=0;i<ghst.size();i++)
			ghst[i].Blue=0;
		Fl::remove_timeout(GhostsBlue);
		//UsrTC->Secs=10;
		UsrTC->KilledGhosts=1;
		UsrTC->Blueness=false;
	}
}



int main ()
{
	fl_register_images ();
	Fl_Window win (800, 600, "OpenGL X");
	MyGlWindow mygl (10, 10, win.w () - 20, win.h () - 20);
	win.end ();
	//win.resizable (mygl);
	win.show ();
	return (Fl::run ());
}
