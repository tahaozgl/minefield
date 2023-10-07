#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 8
#define bomb 10
#define WIN 1
#define LOSE -1
#define CONTINUE 0

int i,j,rest;
int fmatrix[size][size];
int smatrix[size][size];

void crtfmatrix();
void crtsmatrix();
void ftable();
void stable();
void setbomb(int r,int c);
void open(int r, int c);
int explorer(int r,int c);
void control();

int main(){
	int r,c;
	int status,d_count=0,replay;
	char action;
	int first=0;
	printf("Mayin Tarlasi oyununa hos geldiniz :)\n");
	crtfmatrix();
	crtsmatrix();
	
	do{
	ftable();
	printf("Lutfen su formatta giriniz: a,satir,sutun veya b,satir,sutun\n");
    scanf(" %c,%d,%d",&action,&r,&c);
    printf("\n");
    
    if(action == 'a' && r!=0 && c!=0){
    	if(first==0){
    		setbomb(r-1,c-1);
    		first++;
		}
		status=explorer(r-1,c-1);
    }
    else if(action == 'b' && r!=0 && c!=0){
    	if(fmatrix[r-1][c-1]=='B'){
    		fmatrix[r-1][c-1]='#';
    		d_count--;
		}
		else if(d_count<bomb){
			fmatrix[r-1][c-1]='B';
			d_count++;
		}
		else{printf("bomba sayisini gectiniz, bayrak koyamazsiniz");}
    }
    
    control();
    if(rest==bomb){
    	status=WIN;
	}
	
	if(status==LOSE){
		stable();
		printf("Mayina bastiniz, Kaybettiniz :(\n");
	
	}
	
	if(status==WIN){
		stable();
		printf("Tebrikler. Kazandiniz :)\n");
	}
	
	while(1){
	if(status==LOSE || status==WIN){
		printf("\n0- Tekrar, 1- Cikis\n");
		scanf("%d",&replay);
		switch(replay){
		case 0:
			first=0;
			d_count=0;
            status=CONTINUE;
            crtfmatrix();
			crtsmatrix();
			break;
		case 1:
			printf("Oynadiginiz icin tesekkurler. iyi gunler :)");
			return 0;
			break;
		default:
			printf("Lutfen gecerli bir rakam giriniz (0 veya 1)\n");
			break;
		}
		replay=getchar();
	}
	else{
		break;
	}
	}
	
	}
	while(1);
	
	return 0;
}

void crtfmatrix(){
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			fmatrix[i][j]='#';
		}
	}
}

void crtsmatrix(){
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			smatrix[i][j]=0;
		}
	}
}

void ftable(){
	
	for(i=1;i<=size;i++){
		printf("%2d ",i);
	}
	printf("\n");
	for(i=1;i<=size;i++){
		printf(" - ");
	}
	printf("\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(fmatrix[i][j]=='#' || fmatrix[i][j]=='B'){
				printf("%2c ",fmatrix[i][j]);
			}
			else{
				printf("%2d ",fmatrix[i][j]);
			}
		}
		printf("|%d\n",i+1);
	}
	printf("\n");
}

void stable(){
	for(i=1;i<=size;i++){
		printf("%2d ",i);
	}
	printf("\n");
	for(i=1;i<=size;i++){
		printf(" - ");
	}
	printf("\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%2d ",smatrix[i][j]);
		}
		printf("|%d\n",i+1);
	}
	printf("\n");
}

void setbomb(int r,int c){
	int a,b,i,j;
	int same;
	int l1,l2;
	srand(time(NULL));
	int control=0;
	while(control!=bomb){
		l1=rand()%size;
		l2=rand()%size;
		same=0;
		for(a=-1;a<=1;a++){
			for(b=-1;b<=1;b++){
				if(size>(c+b) && (c+b)>=0){
					if(l1==r+a && l2==c+b){
						same=1;
					}
				}
			}
		}
		if(same==0 && smatrix[l1][l2]!=-1){
			smatrix[l1][l2]=-1;
			control++;
		}
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(smatrix[i][j]==-1){
				for(a=-1;a<=1;a++){
					for(b=-1;b<=1;b++){
						if(size>(j+b) && (j+b)>=0){
							if(smatrix[i+a][j+b]!=-1){
							smatrix[i+a][j+b]++;
							}
						}
					}
				}
			}
		}
	}
}

void open(int r, int c) {
	int i, j;
	
	fmatrix[r][c]=smatrix[r][c];

	for (i=-1;i<=1;i++) {
		for (j=-1;j<=1;j++){
			if(size>(c+j) && (c+j)>=0){
				if (smatrix[r+i][c+j]>0 && fmatrix[r+i][c+j]=='#'){
					fmatrix[r+i][c+j]=smatrix[r+i][c+j];
				}
				else if (smatrix[r+i][c+j]==0 && fmatrix[r+i][c+j]=='#'){
					open(r+i,c+j);
				}
			}
		}
	}
}

int explorer(int r,int c){
	int x=0;
	if(smatrix[r][c]==-1){
		x=LOSE;
	}
	else if(smatrix[r][c]>0){
		fmatrix[r][c]=smatrix[r][c];
		x=CONTINUE;
	}
	else{
		open(r,c);
	}
	return x;
}

void control(){
	int i,j;
	rest=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(fmatrix[i][j]=='#' || fmatrix[i][j]=='B'){
				rest++;
			}
		}
	}
}

