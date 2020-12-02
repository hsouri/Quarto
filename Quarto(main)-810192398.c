// 810192398 - Hossein Souri.
#include"gfx.h"
#include"functions-810192398.h"
#define cellSize 19
int main(){
	initScreen();           /* initialize table */
	int piece=0,makan=0,x=0,y=0,*pieceptr=NULL,playername=1,*testptr=NULL,reapet=0,*reapeter=NULL,test=0,*pointer=NULL,endgame=0;
	char input[100];       /* initialize*/  /*set input array*/ 
	int cell[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},cube[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},reapettest,argoman,i,j;
	testptr=&test;        /* specify pointer for testing*/
	drawTable(0,0,cellSize);
	while(true){          /* infinity loop*/
		while(true){      /* infinity loop*/
			printf("Player %d is to pick (e.g. cwfl,rbhs,cbhs): ",playername);
            scanf("%s", input);   /* getting shape argument from user*/
			piece=Testshape(input); /* using Testshape argument for testing irritation*/
			if(piece==3){
				Cleaner();           /* prepair new line*/
				printf("Invalid shape argument!Try again.\n");
                continue; /* back to the loop and continue*/
				}
			pieceptr=&piece;
			reapettest=Tsetpiecereapet(pieceptr,cell,testptr); /* using Testpiecereapet to test repetitive pieces*/
			if(reapettest)
				continue;  /* back to the loop and continue*/
			else{
				playername=Changeplayer(playername); /* using Changeplayer function to change the player*/
				break;  /* get out of loop*/
				}
			}
		Cleaner();			/* prepair new line*/
		pointer=&playername;
		makan=Testcell(cube,pointer);   /*using Testcell function to test reapititive cell;*/
		x=makan/10;					/*specify the <x> .*/
		y=makan%10;					/*specify the <x> .*/
		cell[x-1][y-1]=piece;       /*specify the cell array .*/
		cube[x-1][y-1]=makan;		/*specify the cube array .*/
		i=2+(x-1)*23+x;             /*                specify location of shape*/
        j=2+(y-1)*23+y;				/*                                         */
        drawPiece(j,i, piece, 19);   /* draw piece*/
		Cleaner();					/* prepair new line*/
		argoman=Judge(cell,cube);	/*using Judge function to judge about the game*/
		reapeter=&reapet;
		endgame=Testend(playername,argoman,reapeter);  /* using Testend to show if thw game ended or not*/
		if(endgame)
			break;
		else
		continue;
		}
	return 0;
}