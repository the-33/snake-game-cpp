#include<iostream>
#include<windows.h>
#include<conio.h>
#include<list>
#include<algorithm>
#include<iterator>
#include <stdlib.h>
#include <time.h>
using namespace std;

int width = 60; //default 119
int height = 26; //default 30
int playerpos[2] = {width/2,height/2};
int manzanapos[2] = {30, 17};
char murochar = '#';
char techochar = murochar;
char playerchar = 'O';
char cuerpochar = 'X';
char manzanachar = '*';
char fondochar = ' ';
int vhorizontal = 1;
int vvertical = 1;
bool vivo = true;
bool jugando = false;

class cuerpo
{
	public:
	int pos[2];
	int alantepos[2];	
	cuerpo(int posx, int posy, int alanteposx, int alanteposy)
	{
		this->pos[0] = posx;
		this->pos[1] = posy;
		this->alantepos[0] = alanteposx;
		this->alantepos[1] = alanteposy;
	}
	void setpos (int x, int y);
	void setalantepos (int x, int y);
};

void cuerpo::setpos(int x, int y)
{
	pos[0] = x;
	pos[1] = y;
}

void cuerpo::setalantepos(int x, int y)
{
	alantepos[0] = x;
	alantepos[1] = y;
}

list<cuerpo> serpiente;

void drawline(bool ultima)
{
	for(int i = 0; i <= width; i++)
	{
		if (i<width)
		{
			cout<<techochar;
		}
		else if(!ultima)
		{
			cout<<endl;
		}
	}
}

void drawwall(int linea)
{
	for(int i = 0; i <= width; i++)
	{
		if (i == 0)
		{
			cout<<murochar;
		}
		else if (i > 0 && i < width-1)
		{
			if(linea == manzanapos[1] && i == manzanapos[0])
			{
				cout<<manzanachar;
			}
			else
			{
				cout<<fondochar;
			}			
		}
		else if (i == width-1)
		{
			cout<<murochar;
		}
		else
		{
			cout<<endl;
		}
	}
}

void drawplayer(int linea, bool lineaplayer)
{
	for(int i = 0; i <= width; i++)
	{
		if (i == 0)
		{
			cout<<murochar;
		}
		else if (i == playerpos[0] && lineaplayer)
		{
			cout<<playerchar;
		}
		else if (i == width-1)
		{
			cout<<murochar;
		}
		else
		{
			bool playerdibujado = false;
			int pos = i;
			for(cuerpo var : serpiente)
			{
				if (linea == var.pos[1] && pos == var.pos[0])
				{
					cout<<cuerpochar;
					playerdibujado = true;
					break;
				}
			}
			if (!playerdibujado)
			{
				if(linea == manzanapos[1] && i == manzanapos[0])
				{
					cout<<manzanachar;
				}
				else
				{
					cout<<fondochar;
				}			
			}
		}
	}
	cout<<endl;
}

void actualizarpantalla()
{
	system("cls");
	for(int i = 0; i < height; i++)
	{
		if(i == playerpos[1])
		{
			drawplayer(i, true);
		}
		else if(i == 0)
		{
			drawline(false);
		}
		else if (i == height - 1)
		{
			drawline(true);
		}
		else
		{
			int pos = i;
			bool playerdibujado = false;
			for (cuerpo var : serpiente)
			{
				if (pos == var.pos[1])
				{
					drawplayer(pos, false);
					playerdibujado = true;
					break;
				}
			}
			if (!playerdibujado)
			{
				drawwall(i);
			}			
		}
	}
}


void sumarcuerpo()
{
	list <cuerpo>::iterator itr = serpiente.end();
	advance(itr, -1);
	list <cuerpo>::iterator itr2 = serpiente.end();
	advance(itr2, -2);
	
	if(itr == serpiente.begin())
	{
		if((*itr).pos[0] != playerpos[0])
		{
			if ((*itr).pos[0] < playerpos[0])
			{
				serpiente.push_back(cuerpo((*itr).pos[0]-1, (*itr).pos[1], (*itr).alantepos[0], (*itr).alantepos[1]));
			}
			else
			{
				serpiente.push_back(cuerpo((*itr).pos[0]+1, (*itr).pos[1], (*itr).alantepos[0], (*itr).alantepos[1]));
			}
		}
		
		if((*itr).pos[1] != playerpos[1])
		{
			if ((*itr).pos[1] < playerpos[1])
			{
				serpiente.push_back(cuerpo((*itr).pos[0], (*itr).pos[1]-1, (*itr).alantepos[0], (*itr).alantepos[1]));
			}
			else
			{
				serpiente.push_back(cuerpo((*itr).pos[0], (*itr).pos[1]+1, (*itr).alantepos[0], (*itr).alantepos[1]));
			}
		}
	}
	else
	{
		if((*itr).pos[0] != (*itr2).pos[0])
		{
			if ((*itr).pos[0] < (*itr2).pos[0])
			{
				serpiente.push_back(cuerpo((*itr).pos[0]-1, (*itr).pos[1], (*itr).alantepos[0], (*itr).alantepos[1]));
			}
			else
			{
				serpiente.push_back(cuerpo((*itr).pos[0]+1, (*itr).pos[1], (*itr).alantepos[0], (*itr).alantepos[1]));
			}
		}
		
		if((*itr).pos[1] != (*itr2).pos[1])
		{
			if ((*itr).pos[1] < (*itr2).pos[1])
			{
				serpiente.push_back(cuerpo((*itr).pos[0], (*itr).pos[1]-1, (*itr).alantepos[0], (*itr).alantepos[1]));
			}
			else
			{
				serpiente.push_back(cuerpo((*itr).pos[0], (*itr).pos[1]+1, (*itr).alantepos[0], (*itr).alantepos[1]));
			}
		}
	}
}

void cambiarmanzana()
{
	srand(time(NULL));
			int numeros[2];
			bool validos = false;
			
			while(!validos)
			{
				numeros[0] = 1+rand()%(width-2);
				numeros[1] = 1+rand()%(height-3);
				
				for (cuerpo var : serpiente)
				{
					if(var.pos[0] != numeros[0] && var.pos[1] != numeros[1])
					{
						validos = true;
					}
					else
					{
						validos = false;
					}
				}
			}
			
			manzanapos[0] = numeros[0];
			manzanapos[1] = numeros[1];
}

void morir()
{
	vivo = false;
}

void reset()
{
	playerpos[0] = width/2;
	playerpos[1] = height/2;
	list <cuerpo>::iterator itr;	
	while(serpiente.size() != 0)
	{
		itr = serpiente.begin();
		serpiente.erase(itr);
	}
	vivo = true;
}

int main()
{
	if(!jugando)
	{
		cout<<"                     ,--.                      ,--.           "<<endl<<"  .--.--.          ,--.'|   ,---,          ,--/  /|    ,---,. "<<endl<<" /  /    '.    ,--,:  : |  '  .' \\\\      ,---,': / '  ,'  .' | "<<endl<<"|  :  /`. / ,`--.'`|  ' : /  ;    '.    :   : '/ / ,---.'   | "<<endl<<";  |  |--`  |   :  :  | |:  :       \\   |   '   ,  |   |   .' "<<endl<<"|  :  ;_    :   |   \\ | ::  |   /\\   \\  '   |  /   :   :  |-, "<<endl<<" \\  \\    `. |   : '  '; ||  :  ' ;.   : |   ;  ;   :   |  ;/| "<<endl<<"  `----.   \\'   ' ;.    ;|  |  ;/  \\   \\:   '   \\  |   :   .' "<<endl<<"  __ \\  \\  ||   | | \\   |'  :  | \\  \\ ,'|   |    ' |   |  |-, "<<endl<<" /  /`--'  /'   : |  ; .'|  |  '  '--'  '   : |.  \\'   :  ;/| "<<endl<<"'--'.     / |   | '`--'  |  :  :        |   | '_\\.'|   |    \\ "<<endl<<"  `--'---'  '   : |      |  | ,'        '   : |    |   :   .' "<<endl<<"            ;   |.'      `--''          ;   |,'    |   | ,'   "<<endl<<"            '---'                       '---'      `----'     "<<endl<<"pulsa enter para jugar";
		getch();
		jugando = true;
	}
	
	system("color b0");
	serpiente.push_back(cuerpo(playerpos[0]+1, playerpos[1], playerpos[0], playerpos[1]));
	cambiarmanzana();
	actualizarpantalla();
	while(vivo)
	{		
		for (cuerpo var : serpiente)
		{
			if (var.pos[0] == playerpos[0] && var.pos[1] == playerpos[1])
			{
				morir();
			}
		}
		
		if(playerpos[0] == manzanapos[0] && playerpos[1] == manzanapos[1])
		{
			sumarcuerpo();
			cambiarmanzana();
		}
		
		char input = getch();
		bool semovio = false;
		list <cuerpo>::iterator itr = serpiente.begin();
		switch(input)
		{
			default:
				break;
			case 'a':				
				if (playerpos[0] - vhorizontal > 0)
				{
					if(playerpos[0] - vhorizontal != (*itr).pos[0])
					{
						playerpos[0] -= vhorizontal;
						semovio = true;
					}
				}
				else
				{
					morir();
				}
				break;
			case 'd':
				if (playerpos[0] + vhorizontal < width-1)
				{
					if(playerpos[0] + vhorizontal != (*itr).pos[0])
					{
						playerpos[0] += vhorizontal;
						semovio = true;
					}
				}
				else
				{
					morir();
				}
				break;
			case 'w':
				if (playerpos[1] - vvertical > 0)
				{
					if(playerpos[1] - vvertical != (*itr).pos[1])
					{
						playerpos[1] -= vvertical;
						semovio = true;						
					}
				}
				else
				{
					morir();
				}
				break;
			case 's':
				if (playerpos[1] + vvertical < height-1)
				{
					if(playerpos[1] + vvertical != (*itr).pos[1])
					{
						playerpos[1] += vvertical;
						semovio = true;
					}
				}
				else
				{
					morir();
				}
				break;
		}
		
		if (semovio)
		{
			int i = 0;
			int pos[2];
			list <cuerpo>::iterator itr;
			for(itr = serpiente.begin(); itr != serpiente.end(); itr++) 
			{
			    (*itr).setpos((*itr).alantepos[0], (*itr).alantepos[1]);
				if (i == 0)
				{
					(*itr).setalantepos(playerpos[0], playerpos[1]);
				}
				else
				{
					(*itr).setalantepos(pos[0], pos[1]);
				}
				pos[0] = (*itr).pos[0];
				pos[1] = (*itr).pos[1];
				i++;
			}
			
			actualizarpantalla();
		}
	}
	
	system("cls&color 4f&echo has muerto");
	cout<<"Pulsa una tecla para volver a jugar";
	getch();
	reset();
	main();
	
	return 0;
}
