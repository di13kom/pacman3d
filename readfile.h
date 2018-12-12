//#include <iostream>
#include <vector>
#include <fstream>
#include <string>
//#include <iomanip>
#include <cmath>
using namespace std;

class brick//:public base
{
	public:
		float X;
		float Z;
		int type;
		brick(float _X,float _Z, int tp): X(_X),Z(_Z),type(tp){}
};

class pacman//:public base
{
	public:
		float X;
		float Z;
		unsigned lives;
		unsigned Points;
		float StartPosX;
		float StartPosZ;
		unsigned Step;
		pacman(float _X,float _Z)//: X(_X),Z(_Z) {}
		{
			X=_X;
			Z=_Z;
			StartPosX=_X;
			StartPosZ=_Z;
			lives=3;
			Points=0;
			Step=0;
		}
};

class tablet//:public base
{
	public:
		float X;
		float Z;
		//static int Height;
		tablet(float _X,float _Z): X(_X),Z(_Z) {}
};

class ghost//:public base
{
	public:
		float X;
		float Z;
		int PrevStep;
		float StartPosX;
		float StartPosZ;
		bool Blue;
		ghost(float _X,float _Z)//: X(_X),Z(_Z),StartPosZ(_Z),StartPosX(_X) {}
		{
			X=_X;
			Z=_Z;
			StartPosX=_X;
			StartPosZ=_Z;
			Blue=false;
		}
};

class point//:public base
{
	public:
		float X;
		float Z;
		point(float _X,float _Z): X(_X),Z(_Z) {}
};

void MakeMap(char *);
