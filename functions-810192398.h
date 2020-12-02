// 810192398 - Hossein Souri.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int Testshape(char input[100]);
//this function tests inpot of shape argument;
int Judge(int cell[4][4],int cube[4][4]);
//this function show quarto;
void Cleaner();
//this function prepair new line;
int Changeplayer(int playername);
//this function changes the player;
int Testcell(int cube[4][4],int *pointer);
//this function shaw the irritation of selectcell;
int Testend(int playername,int argoman,int *reapet);
//this function tests if the game ends;
int Tsetpiecereapet(int *pieceptr,int cell[4][4],int *testptr);
//this function tests if the selectpiece repeats;.