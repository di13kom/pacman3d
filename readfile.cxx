#include "readfile.h"

vector<point> pnt;
pacman *pcm;
vector <brick> brk;
vector <tablet> tblt;
vector <ghost> ghst;

void MakeMap(char *filename)
{
	std::ifstream Xfile;
	string buff;
	int m=0;
	int i,j=-100.0;
	Xfile.open(filename);
	int lines=0;
	//int crs=0;
	//while(Xfile>>buff&&lines<=20)
	while(getline(Xfile,buff,'\n')&&lines<=20)
	{
		i=-100.0;
		m=0;
		//while(/*(buff[m]!='\0')&&*/(buff[m]!='\n')&& m<=20)
		while(/*(buff[m]!='\0')&&(buff[m]!='\n')&&*/ m<20)
		{
			switch(buff[m])
			{
				//wall
				case '1':
					brk.push_back(brick(i+5,j+5,1));
					break;
				case '2':
					brk.push_back(brick(i+5,j+5,2));
					break;
				case '3':
					brk.push_back(brick(i+5,j+5,3));
					break;
				case '4':
					brk.push_back(brick(i+5,j+5,4));
					break;
				case '5':
					brk.push_back(brick(i+5,j+5,5));
					break;
				case '6':
					brk.push_back(brick(i+5,j+5,6));
					break;
				case '7':
					brk.push_back(brick(i+5,j+5,7));
					break;
				case '8':
					brk.push_back(brick(i+5,j+5,8));
					break;
				case '9':
					brk.push_back(brick(i+5,j+5,9));
					break;
				case '0':
					brk.push_back(brick(i+5,j+5,0));
					break;
					//wall end
				case 'X':
					pcm = new pacman(i+5,j+5);
					break;
				case 'Z':
					tblt.push_back(tablet(i+5,j+5));
					break;
				case 'Y':
					ghst.push_back(ghost(i+5,j+5));
					break;
				case 'W':
					pnt.push_back(point(i+5,j+5));
					break;
			}
			i+=10.0;
			m++;
		}
		j+=10.0;
		lines++;
	}
	Xfile.close();
}
