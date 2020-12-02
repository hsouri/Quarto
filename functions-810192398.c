// 810192398 - Hossein Souri.
#include "functions-810192398.h"
#include "gfx.h"
#define SHAPE_BIT_MASK 0xFF000000
#define COLOR_BIT_MASK 0x00FF0000
#define FILL_BIT_MASK 0x0000FF00
#define SIZE_BIT_MASK 0x000000FF
int Testshape(char input[100]){
	int inputLength=0,piece=0;                    /* initialize*/
	inputLength = strlen(input);
	while(true){
				if (inputLength != 4) {           /* test inputlength*/
					piece=3;
					break;
				}
				piece=0;
                if(input[1] == 'w' || input[1] == 'W') ;
                else if(input[1] == 'b' || input[1] == 'B') {                /* testing color*/
                    piece |= COLOR_BIT_MASK;
                }
                else {
					piece=3;
					break;
                }
                if(input[2] == 'h' || input[2] == 'H') ;                    /* testing fll or hole */
                else if(input[2] == 'f' || input[2] == 'F') {
                    piece |= FILL_BIT_MASK;
                }
                else {
					piece=3;
					break;
                }
                
                if(input[3] == 's' || input[3] == 'S') ;                    /* testing the size; */
                else if(input[3] == 'l' || input[3] == 'L') {
                    piece |= SIZE_BIT_MASK;
                }
                else {
					piece=3;
					break;
                }
				if(input[0] == 'c' || input[0] == 'C');                     /* testing regtangle or circle; */
				else if(input[0] == 'r' || input[0] == 'R') {
                    piece |= SHAPE_BIT_MASK;
				}
				else {
					piece=3;
					break;
				}
				break;
	}
	return piece;
}
int Judge(int cell[4][4],int cube[4][4]){
	int counter,i3,argoman1,argoman2,j3,argoman=0,test=0;               /* initialize  */
	while(true){
				for(i3=0;i3<4;i3++){
				counter=0;                                             /*loop for testing the coloums. */
				argoman1=~(0);
				argoman2=0;
				for(j3=0;j3<4;j3++){
				if(cube[i3][j3]!=0){                                    /* testing the coloums */
									counter=counter+1;                       /* count the hole cells */
									argoman1=(cell[i3][j3])&argoman1;
									argoman2=(cell[i3][j3])|argoman2;
								}
							}
							if(counter==4){
							argoman=~(argoman1^argoman2);
							if(argoman!=0){
							test=1;
								break;
							}
							}
							}
							if(test==1)
								break;
							test=0;
							for(i3=0;i3<4;i3++){                                  /*loop for testing the rows. */    
								counter=0;                                       /* initialize  */
								argoman1=~(0);
								argoman2=0;
							for(j3=0;j3<4;j3++){                                    /* testing the rows */              
								if(cube[j3][i3]!=0){
									counter=counter+1;                              /* count the hole cells */
									argoman1=(cell[j3][i3])&argoman1;
									argoman2=(cell[j3][i3])|argoman2;
								}
							}
							if(counter==4){
							argoman=~(argoman1^argoman2);
							if(argoman!=0){
								test=1;
								break;
							}
							}
							}
							if(test==1)
								break;
							i3=0;										/* initialization */
							j3=-1;                                      /* initialization */
							argoman1=~(0);								/* initialization */
							argoman2=0;									/* initialization */
							counter=0;									/* initialization */
						for(i3=0;i3<4;i3++){
							j3=j3+1;
							if(cube[j3][i3]!=0){                        /* testing diameter . */
								counter=counter+1;
								argoman1=(cell[j3][i3])&argoman1;
								argoman2=(cell[j3][i3])|argoman2;
							}
						}
							if(counter==4){
						argoman=~(argoman1^argoman2);
						if(argoman!=0){
							test=1;
							break;
						}
						}
						i3=0;										/* initialization */
						j3=4;										/* initialization */
						argoman1=~(0);								/* initialization */
						argoman2=0;									/* initialization */
						counter=0;									/* initialization */
						for(i3=0;i3<4;i3++){
							j3=j3-1;
							if(cube[j3][i3]!=0){                    /* testing diameter . */
								counter=counter+1;
								argoman1=(cell[j3][i3])&argoman1;
								argoman2=(cell[j3][i3])|argoman2;
							}
						}
						if(counter==4){
						argoman=~(argoman1^argoman2);
						if(argoman!=0){
							test=1;
							break;
						}
						}
						break;
	}
	return argoman;
}
void Cleaner(){                                         /* using function to clear the line. */
	gotoxy(0, FIRST_LOG_LINE);
	clearLine(10);
}
int Changeplayer(int playername){                      /* changing the player, */
			if(playername==1)
				playername=2;
			else
				playername=1;
	return playername;
}
int Testcell(int cube[4][4],int *pointer){             /* testing irritation cells*/
	int taeen,i2,j2,makan=0;
	while(true){
		fflush(stdin);
		printf("Player %d, Plz choose a valid cell (e.g. 14,23,11):",*pointer);     /* get cell. */
		scanf("%d",&makan);
		if((makan!=11) && (makan!=12) && (makan!=13) && (makan!=14) && (makan!=21) && (makan!=22) && (makan!=23) && (makan!=24) && (makan!=31) && (makan!=32) && (makan!=33) && (makan!=34) && (makan!=41) && (makan!=42) && (makan!=43) && (makan!=44)){
			Cleaner();
			printf("Wrong cell! Plz try again.\n");          /* tseting wrong cell. */
            continue;
			}
		else{
			taeen=0;
			for(i2=0;i2<4;i2++){
				for(j2=0;j2<4;j2++){
					if(makan==cube[i2][j2]){                 /* testing irritate cell */
						Cleaner();
						printf("Already taken! Plz choose another cell.\n");
						taeen=1;
						}
					}
				}
			if(taeen)
				continue;
			else
				break;                    /* get out of loop.,., */
			}
		}
	return makan;
}
int Testend(int playername,int argoman,int *reapet){
	int endgame=0;
	if(argoman!=0){                                        /* determind the winner*/
		printf("player %d won!!!\n\n",playername);        /*  print it*/
		endgame=1;
		}
	*reapet=*reapet+1;
	if(*reapet==16){
		/* game can continue for 16 time. so we should test it!!!!!!!!!*/
		printf("game end ! no one won!!!\n");
		endgame=1;
		}
	return endgame;
}
int Tsetpiecereapet(int *pieceptr,int cell[4][4],int *testptr){
	// Testpiecereapet is a number that shows if the selectpiece eaped or not  */
	int reapettest=0,i,j;
	while(true){
		if(*pieceptr==0){
		if(*testptr==1){
			Cleaner();
			printf("Already taken!Try again.\n");
			reapettest=1;
			break;
		}
		else
			*pieceptr=5;
			*testptr=1;
		}
			for(i=0;i<4;i++){                                 /* lopp for including the all cells. */
				for(j=0;j<4;j++){                             /* inner loop */
					if(*pieceptr==cell[i][j]){                /* testing irritate piece */
						Cleaner();
						printf("Already taken!Try again.\n");  /*print warning*/
					    reapettest=1;
						}
					}
				}
			break;
	}
			if(*pieceptr==5)                                        /* reinitialize*/
				*pieceptr=0;
			return reapettest;
}