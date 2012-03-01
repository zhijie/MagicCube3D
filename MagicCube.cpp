/*
 * @ Author: onezeros@yahoo.cn
 * @ blog  : blog.csdn.net/onezeros
 * @ Date  : 10/25/2010
 * @ Note  : You can use this program for any purpose if you keep this note. 
 *			 I'll appreciate if you can email bugs to me.
 *			 Have A Nice Day!
 */

#include "StdAfx.h"
#include "MagicCube.h"
#include "utilities.h"

#include <fstream>
using namespace std;

const GLubyte colorTable[7][3]={
	{0,0,255},{0,255,0},{255,0,0},{255,102,0},{255,255,255},{255,255,0},{0x99,0x99,0x99}
};

//store colors of every little aspect of magic cube ,in xyz order
//initialized with up white,down yellow,front blue,back green,left red,right orange
Color aspectColors[6][9]={
	//front
	{BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE},
	//back
	{GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN},
	//left
	{RED,RED,RED,RED,RED,RED,RED,RED,RED},
	//right
	{ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE},
	//up
	{WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
	//down
	{YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW}	
};
Color aspectColor_org[6][9]={
	//front
	{BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE},
	//back
	{GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN},
	//left
	{RED,RED,RED,RED,RED,RED,RED,RED,RED},
	//right
	{ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE},
	//up
	{WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
	//down
	{YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW}	
};
//index of points of aspects
const int aspectDotIndex[6][16]={
	//front
	{48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63},
	//back
	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
	//left
	{0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60},
	//right
	{3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63},
	//up
	{12,13,14,15,28,29,30,31,44,45,46,47,60,61,62,63},
	//down
	{0,1,2,3,16,17,18,19,32,33,34,35,48,49,50,51,}
};
//	coordinates of points: in zyx order
//length of little dice is 1
const GLfloat points[64][3]={
	{-1.5,-1.5,-1.5},{-0.5,-1.5,-1.5},{0.5,-1.5,-1.5},{1.5,-1.5,-1.5},//back
	{-1.5,-0.5,-1.5},{-0.5,-0.5,-1.5},{0.5,-0.5,-1.5},{1.5,-0.5,-1.5},
	{-1.5,0.5,-1.5},{-0.5,0.5,-1.5},{0.5,0.5,-1.5},{1.5,0.5,-1.5},
	{-1.5,1.5,-1.5},{-0.5,1.5,-1.5},{0.5,1.5,-1.5},{1.5,1.5,-1.5},
	{-1.5,-1.5,-0.5},{-0.5,-1.5,-0.5},{0.5,-1.5,-0.5},{1.5,-1.5,-0.5},//
	{-1.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{1.5,-0.5,-0.5},
	{-1.5,0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{1.5,0.5,-0.5},
	{-1.5,1.5,-0.5},{-0.5,1.5,-0.5},{0.5,1.5,-0.5},{1.5,1.5,-0.5},
	{-1.5,-1.5,0.5},{-0.5,-1.5,0.5},{0.5,-1.5,0.5},{1.5,-1.5,0.5},//
	{-1.5,-0.5,0.5},{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{1.5,-0.5,0.5},
	{-1.5,0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{1.5,0.5,0.5},
	{-1.5,1.5,0.5},{-0.5,1.5,0.5},{0.5,1.5,0.5},{1.5,1.5,0.5},
	{-1.5,-1.5,1.5},{-0.5,-1.5,1.5},{0.5,-1.5,1.5},{1.5,-1.5,1.5},//front
	{-1.5,-0.5,1.5},{-0.5,-0.5,1.5},{0.5,-0.5,1.5},{1.5,-0.5,1.5},
	{-1.5,0.5,1.5},{-0.5,0.5,1.5},{0.5,0.5,1.5},{1.5,0.5,1.5},
	{-1.5,1.5,1.5},{-0.5,1.5,1.5},{0.5,1.5,1.5},{1.5,1.5,1.5}
};

int indexArray[4]={0};

///////////////////////////////////////////////////
//draw aspects
///////////////////////////////////////////////////
//index of points table,including 4 elements
inline void vertexs(int* index)
{
	glVertex3fv(points[index[0]]);
	glVertex3fv(points[index[1]]);
	glVertex3fv(points[index[2]]);
	glVertex3fv(points[index[3]]);
}
//draw small aspect of big aspect asp,indexed vertex in aspectDotIndex by index
inline void drawAspect(Aspect asp,int index)
{
	int colorIndex=(index>>2)*3+index%4;
	glColor3ubv(colorTable[aspectColors[asp][colorIndex]]);
	int indexArray[4]={
		aspectDotIndex[asp][index],aspectDotIndex[asp][index+4],
		aspectDotIndex[asp][index+5],aspectDotIndex[asp][index+1]};
		glBegin(GL_QUADS);
		vertexs(indexArray);
		glEnd();

		glColor3ubv(colorTable[GRAY]);
		glLineWidth(2.f);
		glBegin(GL_LINE_LOOP);
		vertexs(indexArray);
		glEnd();
}
//draw a full aspect
inline void drawFullAspect(Aspect asp)
{
	for (int l=0;l<3;l++){//line
		for (int i=0;i<3;i++){//3 aspects of every line			
			int ind=l*4+i;
			drawAspect(asp,ind);				
		}
	}
}



void drawXRight(void)
{
	//right part
	drawFullAspect(RIGHT);
	for (int i=0;i<3;i++){
		//up part
		drawAspect(UP,2+(i<<2));
		//down part
		drawAspect(DOWN,2+(i<<2));
		//front part
		drawAspect(FRONT,2+(i<<2));
		//back part
		drawAspect(BACK,2+(i<<2));
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//right
	indexArray[0]=2;
	indexArray[1]=14;
	indexArray[2]=62;
	indexArray[3]=50;	
	glBegin(GL_QUADS);	
	vertexs(indexArray);
	glEnd();
}
void drawXMiddle(void)
{
	for (int i=0;i<3;i++){
		//up part
		drawAspect(UP,1+(i<<2));
		//down part
		drawAspect(DOWN,1+(i<<2));
		//front part
		drawAspect(FRONT,1+(i<<2));
		//back part
		drawAspect(BACK,1+(i<<2));
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//right
	indexArray[0]=2;
	indexArray[1]=14;
	indexArray[2]=62;
	indexArray[3]=50;	
	glBegin(GL_QUADS);	
	vertexs(indexArray);
	glEnd();
	//left
	indexArray[0]=1;
	indexArray[1]=13;
	indexArray[2]=61;
	indexArray[3]=49;	
	glBegin(GL_QUADS);	
	vertexs(indexArray);
	glEnd();
}
void drawXLeft(void)
{
	//left part
	drawFullAspect(LEFT);
	for (int i=0;i<3;i++){
		//up part
		drawAspect(UP,i<<2);
		//down part
		drawAspect(DOWN,i<<2);
		//front part
		drawAspect(FRONT,i<<2);
		//back part
		drawAspect(BACK,i<<2);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//left
	indexArray[0]=1;
	indexArray[1]=13;
	indexArray[2]=61;
	indexArray[3]=49;	
	glBegin(GL_QUADS);	
	vertexs(indexArray);
	glEnd();
}
void drawYDown(void)
{
	//down part
	drawFullAspect(DOWN);
	for (int i=0;i<3;i++){
		//left part
		drawAspect(LEFT,i<<2);
		//right part
		drawAspect(RIGHT,i<<2);
		//front part
		drawAspect(FRONT,i);
		//back part
		drawAspect(BACK,i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//down
	indexArray[0]=52;
	indexArray[1]=55;
	indexArray[2]=7;
	indexArray[3]=4;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}
void drawYMiddle(void)
{///////////////////////////////////////////////////?????????????????????????????
	for (int i=0;i<3;i++){
		//left part
		drawAspect(LEFT,1+(i<<2));
		//right part
		drawAspect(RIGHT,1+(i<<2));
		//front part
		drawAspect(FRONT,4+i);
		//back part
		drawAspect(BACK,4+i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//up
	indexArray[0]=56;
	indexArray[1]=59;
	indexArray[2]=11;
	indexArray[3]=8;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
	//down
	indexArray[0]=52;
	indexArray[1]=55;
	indexArray[2]=7;
	indexArray[3]=4;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}
void drawYUp(void)
{
	//up part
	drawFullAspect(UP);
	for (int i=0;i<3;i++){
		//left part
		drawAspect(LEFT,2+(i<<2));
		//right part
		drawAspect(RIGHT,2+(i<<2));
		//front part
		drawAspect(FRONT,8+i);
		//back part
		drawAspect(BACK,8+i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//up
	indexArray[0]=56;
	indexArray[1]=59;
	indexArray[2]=11;
	indexArray[3]=8;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}

void drawZFront()
{
	//front part
	drawFullAspect(FRONT);
	for (int i=8;i<=10;i++){		
		//left part
		drawAspect(LEFT,i);
		//right part
		drawAspect(RIGHT,i);
		//up part
		drawAspect(UP,i);
		//down part
		drawAspect(DOWN,i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//front
	indexArray[0]=32;
	indexArray[1]=35;
	indexArray[2]=47;
	indexArray[3]=44;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}
void drawZMiddle()
{	
	for (int i=4;i<=6;i++){
		//left part
		drawAspect(LEFT,i);
		//right part
		drawAspect(RIGHT,i);
		//up part
		drawAspect(UP,i);
		//down part
		drawAspect(DOWN,i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//front
	indexArray[0]=32;
	indexArray[1]=35;
	indexArray[2]=47;
	indexArray[3]=44;	
	glBegin(GL_QUADS);	
	vertexs(indexArray);
	glEnd();
	//back
	indexArray[0]=16;
	indexArray[1]=19;
	indexArray[2]=31;
	indexArray[3]=28;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}
void drawZBack()
{
	//back part
	drawFullAspect(BACK);	
	for (int i=0;i<=2;i++){
		//left part
		drawAspect(LEFT,i);
		//right part
		drawAspect(RIGHT,i);
		//up part
		drawAspect(UP,i);
		//down part
		drawAspect(DOWN,i);
	}
	//shielded part
	glColor3ubv(colorTable[GRAY]);
	//back
	indexArray[0]=16;
	indexArray[1]=19;
	indexArray[2]=31;
	indexArray[3]=28;	
	glBegin(GL_QUADS);
	vertexs(indexArray);
	glEnd();
}



typedef void (*PDrawBlock) ();
PDrawBlock pDrawBlocks[3][3]={
	{drawXLeft,drawXMiddle,drawXRight},
	{drawYDown,drawYMiddle,drawYUp},
	{drawZBack,drawZMiddle,drawZFront}
};

///////////////////////////////////////////////////
//rotate color table
///////////////////////////////////////////////////
//update color table when rotate a chunk
//	rotation clockwise once will be of same effect with rotation counterclockwise triple
//but this will be inefficient.so I will write code for the two situation seperately
//convention:look from positive to negative along axis to decide clockwise or not

void rotateFullAspectClockwise(Aspect asp,int* index)
{	
	Color t[2];
	for (int i=0;i<2;i++){
		t[i]=aspectColors[asp][index[i+6]];
	}
	for (int i=7;i>1;i--){
		aspectColors[asp][index[i]]=aspectColors[asp][index[i-2]];
	}
	for (int i=0;i<2;i++){
		aspectColors[asp][index[i]]=t[i];
	}	
}
void rotateFullAspectAnticlockwise(Aspect asp,int* index)
{
	Color t[2];
	for (int i=0;i<2;i++){
		t[i]=aspectColors[asp][index[i]];
	}
	for (int i=0;i<6;i++){
		aspectColors[asp][index[i]]=aspectColors[asp][index[i+2]];
	}
	for (int i=0;i<2;i++){
		aspectColors[asp][index[i+6]]=t[i];
	}
}
void rotateXLeftClockwise()
{
	int index[9]={6,7,8,5,2,1,0,3};
	rotateFullAspectClockwise(LEFT,index);

	//front ,down,back,up
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i];
		aspectColors[FRONT][i]=aspectColors[DOWN][i];
		aspectColors[DOWN][i]=aspectColors[BACK][6-i];
		aspectColors[BACK][6-i]=aspectColors[UP][6-i];
		aspectColors[UP][6-i]=t;
	}
}
void rotateXLeftAnticlockwise()
{
	int index[9]={6,7,8,5,2,1,0,3};
	rotateFullAspectAnticlockwise(LEFT,index);

	//front ,up,back,down	
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i];
		aspectColors[FRONT][i]=aspectColors[UP][6-i];
		aspectColors[UP][6-i]=aspectColors[BACK][6-i];	
		aspectColors[BACK][6-i]=aspectColors[DOWN][i];	
		aspectColors[DOWN][i]=t;
	}
}
void rotateXRightClockwise()
{
	int index[9]={6,7,8,5,2,1,0,3};
	rotateFullAspectClockwise(RIGHT,index);

	//front ,down,back,up
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i+2];
		aspectColors[FRONT][i+2]=aspectColors[DOWN][i+2];
		aspectColors[DOWN][i+2]=aspectColors[BACK][6-i+2];
		aspectColors[BACK][6-i+2]=aspectColors[UP][6-i+2];
		aspectColors[UP][6-i+2]=t;
	}
}
void rotateXRightAnticlockwise()
{
	int index[9]={6,7,8,5,2,1,0,3};
	rotateFullAspectAnticlockwise(RIGHT,index);

	//front ,up,back,down
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i+2];
		aspectColors[FRONT][i+2]=aspectColors[UP][6-i+2];
		aspectColors[UP][6-i+2]=aspectColors[BACK][6-i+2];	
		aspectColors[BACK][6-i+2]=aspectColors[DOWN][i+2];	
		aspectColors[DOWN][i+2]=t;
	}	
}
void rotateXMiddleClockwise()
{
	//front ,down,back,up
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i+1];
		aspectColors[FRONT][i+1]=aspectColors[DOWN][i+1];
		aspectColors[DOWN][i+1]=aspectColors[BACK][6-i+1];
		aspectColors[BACK][6-i+1]=aspectColors[UP][6-i+1];
		aspectColors[UP][6-i+1]=t;
	}
}
void rotateXMiddleAnticlockwise()
{
	//front ,up,back,down
	for (int i=0;i<=6;i+=3){
		Color t=aspectColors[FRONT][i+1];
		aspectColors[FRONT][i+1]=aspectColors[UP][6-i+1];
		aspectColors[UP][6-i+1]=aspectColors[BACK][6-i+1];	
		aspectColors[BACK][6-i+1]=aspectColors[DOWN][i+1];	
		aspectColors[DOWN][i+1]=t;
	}
}
void rotateYDownClockwise()
{
	int index[9]={6,3,0,1,2,5,8,7};
	rotateFullAspectClockwise(DOWN,index);

	//front,right,back,left
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][i];
		aspectColors[FRONT][i]=aspectColors[RIGHT][3*(2-i)];
		aspectColors[RIGHT][3*(2-i)]=aspectColors[BACK][2-i];
		aspectColors[BACK][2-i]=aspectColors[LEFT][i*3];
		aspectColors[LEFT][i*3]=t;
	}
}
void rotateYDownAnticlockwise()
{
	int index[9]={6,3,0,1,2,5,8,7};
	rotateFullAspectAnticlockwise(DOWN,index);

	//front,left,back,right
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][i];
		aspectColors[FRONT][i]=aspectColors[LEFT][3*i];
		aspectColors[LEFT][3*i]=aspectColors[BACK][2-i];
		aspectColors[BACK][2-i]=aspectColors[RIGHT][(2-i)*3];
		aspectColors[RIGHT][(2-i)*3]=t;
	}
}
void rotateYUpClockwise()
{
	int index[9]={6,3,0,1,2,5,8,7};
	rotateFullAspectClockwise(UP,index);
	//front,right,back,left
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][6+i];
		aspectColors[FRONT][6+i]=aspectColors[RIGHT][2+3*(2-i)];
		aspectColors[RIGHT][2+3*(2-i)]=aspectColors[BACK][6+2-i];
		aspectColors[BACK][6+2-i]=aspectColors[LEFT][2+i*3];
		aspectColors[LEFT][2+i*3]=t;
	}
}
void rotateYUpAnticlockwise()
{
	int index[9]={6,3,0,1,2,5,8,7};
	rotateFullAspectAnticlockwise(UP,index);
	//front,left,back,right
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][6+i];
		aspectColors[FRONT][6+i]=aspectColors[LEFT][2+3*i];
		aspectColors[LEFT][2+3*i]=aspectColors[BACK][6+2-i];
		aspectColors[BACK][6+2-i]=aspectColors[RIGHT][2+(2-i)*3];
		aspectColors[RIGHT][2+(2-i)*3]=t;
	}
}
void rotateYMiddleClockwise()
{
	//front,right,back,left
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][3+i];
		aspectColors[FRONT][3+i]=aspectColors[RIGHT][1+3*(2-i)];
		aspectColors[RIGHT][1+3*(2-i)]=aspectColors[BACK][3+2-i];
		aspectColors[BACK][3+2-i]=aspectColors[LEFT][1+i*3];
		aspectColors[LEFT][1+i*3]=t;
	}
}
void rotateYMiddleAnticlockwise()
{
	//front,left,back,right
	for (int i=0;i<3;i++){
		Color t=aspectColors[FRONT][3+i];
		aspectColors[FRONT][3+i]=aspectColors[LEFT][1+3*i];
		aspectColors[LEFT][1+3*i]=aspectColors[BACK][3+2-i];
		aspectColors[BACK][3+2-i]=aspectColors[RIGHT][1+(2-i)*3];
		aspectColors[RIGHT][1+(2-i)*3]=t;
	}
}
void rotateZFrontClockwise()
{
	int index[9]={0,3,6,7,8,5,2,1};
	rotateFullAspectClockwise(FRONT,index);

	Color t=aspectColors[UP][6];
	aspectColors[UP][6]=aspectColors[UP][8];
	aspectColors[UP][8]=t;
	t=aspectColors[DOWN][6];
	aspectColors[DOWN][6]=aspectColors[DOWN][8];
	aspectColors[DOWN][8]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][6],size);
	memcpy(&aspectColors[LEFT][6],&aspectColors[DOWN][6],size);
	memcpy(&aspectColors[DOWN][6],&aspectColors[RIGHT][6],size);
	memcpy(&aspectColors[RIGHT][6],&aspectColors[UP][6],size);
	memcpy(&aspectColors[UP][6],tmp,size);
}
void rotateZFrontAnticlockwise()
{
	int index[9]={0,3,6,7,8,5,2,1};
	rotateFullAspectAnticlockwise(FRONT,index);

	Color t=aspectColors[LEFT][6];
	aspectColors[LEFT][6]=aspectColors[LEFT][8];
	aspectColors[LEFT][8]=t;
	t=aspectColors[RIGHT][6];
	aspectColors[RIGHT][6]=aspectColors[RIGHT][8];
	aspectColors[RIGHT][8]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][6],size);
	memcpy(&aspectColors[LEFT][6],&aspectColors[UP][6],size);
	memcpy(&aspectColors[UP][6],&aspectColors[RIGHT][6],size);
	memcpy(&aspectColors[RIGHT][6],&aspectColors[DOWN][6],size);
	memcpy(&aspectColors[DOWN][6],tmp,size);
}
void rotateZBackClockwise()
{
	int index[9]={0,3,6,7,8,5,2,1};
	rotateFullAspectClockwise(BACK,index);

	Color t=aspectColors[UP][0];
	aspectColors[UP][0]=aspectColors[UP][2];
	aspectColors[UP][2]=t;
	t=aspectColors[DOWN][0];
	aspectColors[DOWN][0]=aspectColors[DOWN][2];
	aspectColors[DOWN][2]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][0],size);
	memcpy(&aspectColors[LEFT][0],&aspectColors[DOWN][0],size);
	memcpy(&aspectColors[DOWN][0],&aspectColors[RIGHT][0],size);
	memcpy(&aspectColors[RIGHT][0],&aspectColors[UP][0],size);
	memcpy(&aspectColors[UP][0],tmp,size);	
}
void rotateZBackAnticlockwise()
{
	int index[9]={0,3,6,7,8,5,2,1};
	rotateFullAspectAnticlockwise(BACK,index);

	Color t=aspectColors[LEFT][0];
	aspectColors[LEFT][0]=aspectColors[LEFT][2];
	aspectColors[LEFT][2]=t;
	t=aspectColors[RIGHT][0];
	aspectColors[RIGHT][0]=aspectColors[RIGHT][2];
	aspectColors[RIGHT][2]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][0],size);
	memcpy(&aspectColors[LEFT][0],&aspectColors[UP][0],size);
	memcpy(&aspectColors[UP][0],&aspectColors[RIGHT][0],size);
	memcpy(&aspectColors[RIGHT][0],&aspectColors[DOWN][0],size);
	memcpy(&aspectColors[DOWN][0],tmp,size);
}
void rotateZMiddleClockwise()
{
	Color t=aspectColors[UP][3];
	aspectColors[UP][3]=aspectColors[UP][5];
	aspectColors[UP][5]=t;
	t=aspectColors[DOWN][3];
	aspectColors[DOWN][3]=aspectColors[DOWN][5];
	aspectColors[DOWN][5]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][3],size);
	memcpy(&aspectColors[LEFT][3],&aspectColors[DOWN][3],size);
	memcpy(&aspectColors[DOWN][3],&aspectColors[RIGHT][3],size);
	memcpy(&aspectColors[RIGHT][3],&aspectColors[UP][3],size);
	memcpy(&aspectColors[UP][3],tmp,size);
}
void rotateZMiddleAnticlockwise()
{
	Color t=aspectColors[LEFT][3];
	aspectColors[LEFT][3]=aspectColors[LEFT][5];
	aspectColors[LEFT][5]=t;
	t=aspectColors[RIGHT][3];
	aspectColors[RIGHT][3]=aspectColors[RIGHT][5];
	aspectColors[RIGHT][5]=t;

	Color tmp[3];
	int size=3*sizeof(Color);
	memcpy(tmp,&aspectColors[LEFT][3],size);
	memcpy(&aspectColors[LEFT][3],&aspectColors[UP][3],size);
	memcpy(&aspectColors[UP][3],&aspectColors[RIGHT][3],size);
	memcpy(&aspectColors[RIGHT][3],&aspectColors[DOWN][3],size);
	memcpy(&aspectColors[DOWN][3],tmp,size);
}
//rotate color table functions
typedef void (*PRotateColorTable)();
PRotateColorTable pRotateColorTable[3][3][2]={
	//x from negative to positive,i.e. from left to right
	{{rotateXLeftClockwise,rotateXLeftAnticlockwise},
	{rotateXMiddleClockwise,rotateXMiddleAnticlockwise},
	{rotateXRightClockwise,rotateXRightAnticlockwise}},
	//y
	{{rotateYDownClockwise,rotateYDownAnticlockwise},
	{rotateYMiddleClockwise,rotateYMiddleAnticlockwise},
	{rotateYUpClockwise,rotateYUpAnticlockwise}},
	//z
	{{rotateZBackClockwise,rotateZBackAnticlockwise},
	{rotateZMiddleClockwise,rotateZMiddleAnticlockwise},
	{rotateZFrontClockwise,rotateZFrontAnticlockwise}},
};

///////////////////////////////////////////////////
//auto solve
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//operations
#undef L
#undef S

PRotateColorTable F=rotateZFrontClockwise;

PRotateColorTable Fr=rotateZFrontAnticlockwise;
PRotateColorTable B=rotateZBackAnticlockwise;
PRotateColorTable Br=rotateZBackClockwise;

PRotateColorTable R=rotateXRightClockwise;
PRotateColorTable Rr=rotateXRightAnticlockwise;
PRotateColorTable L=rotateXLeftAnticlockwise;
PRotateColorTable Lr=rotateXLeftClockwise;

PRotateColorTable U=rotateYUpClockwise;
PRotateColorTable Ur=rotateYUpAnticlockwise;
PRotateColorTable D=rotateYDownAnticlockwise;
PRotateColorTable Dr=rotateYDownClockwise;

//rotate middle layer along y axis clockwisely
PRotateColorTable E=rotateYMiddleClockwise;
PRotateColorTable Er=rotateYMiddleAnticlockwise;
void E2(){
	E();E();
}
//rotate middle layer along x axis clockwisely
PRotateColorTable M=rotateXMiddleClockwise;
PRotateColorTable Mr=rotateXMiddleAnticlockwise;
void M2(){
	E();E();
}
//rotate middle layer along z axis clockwisely
PRotateColorTable S=rotateZMiddleClockwise;
PRotateColorTable Sr=rotateZMiddleClockwise;
void S2(){
	S();S();
}

void F2(){
	F();F();
}
void B2(){
	B();B();
}
void R2(){
	R();R();
}
void L2(){
	L();L();
}
void U2(){
	U();U();
}
void D2(){
	D();D();
}
//rotate whole cube along x axis clockwisely
void x(){
	rotateXLeftClockwise();
	rotateXMiddleClockwise();
	rotateXRightClockwise();
}
void xr(){
	rotateXLeftAnticlockwise();
	rotateXMiddleAnticlockwise();
	rotateXRightAnticlockwise();
}
void x2(){
	x();x();
}
//rotate whole cube along y axis clockwisely
void y(){
	rotateYDownClockwise();
	rotateYMiddleClockwise();
	rotateYUpClockwise();
}
void yr(){
	rotateYDownAnticlockwise();
	rotateYMiddleAnticlockwise();
	rotateYUpAnticlockwise();
}
void y2(){
	y();y();
}
//rotate whole cube along z axis clockwisely
void z(){
	rotateZBackClockwise();
	rotateZMiddleClockwise();
	rotateZFrontClockwise();
}
void zr(){
	rotateZBackAnticlockwise();
	rotateZMiddleAnticlockwise();
	rotateZFrontAnticlockwise();
}
void z2(){
	z();z();
}
//rotate top two layer clockwisely
void u(){
	rotateYUpClockwise();
	rotateYMiddleClockwise();
}
void ur(){
	rotateYUpAnticlockwise();
	rotateYMiddleAnticlockwise();
}
void u2(){
	u();u();
}
//rotate right two layer clockwisely
void r(){
	rotateXRightClockwise();
	rotateXMiddleClockwise();
}
void rr(){
	rotateXRightAnticlockwise();
	rotateXMiddleAnticlockwise();
}
void r2(){
	r();r();
}
//rotate front two layer clockwisely
void f(){
	rotateZFrontClockwise();
	rotateZMiddleClockwise();
}
void fr(){
	rotateZFrontAnticlockwise();
	rotateZMiddleAnticlockwise();
}
void f2(){
	f();f();
}
//rotate down two layer anticlockwisely
void d(){
	rotateYMiddleAnticlockwise();
	rotateYDownAnticlockwise();
}
void dr(){
	rotateYDownClockwise();
	rotateYMiddleClockwise();
}
void d2(){
	d();d();
}
//rotate left two layer anticlockwisely
void l(){
	rotateXMiddleAnticlockwise();
	rotateXLeftAnticlockwise();
}
void lr(){
	rotateXMiddleClockwise();
	rotateXLeftClockwise();
}
void l2(){
	l();l();
}
//rotate back two layer anticlockwisely
void b(){
	rotateZMiddleAnticlockwise();
	rotateZBackAnticlockwise();
}
void br(){
	rotateZMiddleClockwise();
	rotateZBackClockwise();
}
void b2(){
	b();b();
}

///////////////////////////////////////////////////
//internal operations ,only command string manipulation added.
//another way to do this is set parameter for these functions.
//e.g. F(bool b){rotate and if b ,then string manipulation }
//for such short functions ,I prefer write another set of functions.
///////////////////////////////////////////////////
#define COMMANDLEN 500
//store operation string
static char cmdString[COMMANDLEN];
static int cmdStrPtr;

void _F(){
	F();
	cmdString[cmdStrPtr++]='F';
}
void _Fr(){
	Fr();
	cmdString[cmdStrPtr++]='F';
	cmdString[cmdStrPtr++]='\'';
}
void _F2(){
	F();F();
	cmdString[cmdStrPtr++]='F';
	cmdString[cmdStrPtr++]='2';
}
void _B(){
	B();
	cmdString[cmdStrPtr++]='B';
}
void _Br(){
	Br();
	cmdString[cmdStrPtr++]='B';
	cmdString[cmdStrPtr++]='\'';
}
void _B2(){
	B();B();
	cmdString[cmdStrPtr++]='B';
	cmdString[cmdStrPtr++]='2';
}
void _R(){
	R();
	cmdString[cmdStrPtr++]='R';
}
void _Rr(){
	Rr();
	cmdString[cmdStrPtr++]='R';
	cmdString[cmdStrPtr++]='\'';
}
void _R2(){
	R();R();
	cmdString[cmdStrPtr++]='R';
	cmdString[cmdStrPtr++]='2';
}
void _L(){
	L();
	cmdString[cmdStrPtr++]='L';
}
void _Lr(){
	Lr();
	cmdString[cmdStrPtr++]='L';
	cmdString[cmdStrPtr++]='\'';
}
void _L2(){
	L();L();
	cmdString[cmdStrPtr++]='L';
	cmdString[cmdStrPtr++]='2';
}
void _U(){
	U();
	cmdString[cmdStrPtr++]='U';
}
void _Ur(){
	Ur();
	cmdString[cmdStrPtr++]='U';
	cmdString[cmdStrPtr++]='\'';
}
void _U2(){
	U();U();
	cmdString[cmdStrPtr++]='U';
	cmdString[cmdStrPtr++]='2';
}
void _D(){
	D();
	cmdString[cmdStrPtr++]='D';
}
void _Dr(){
	Dr();
	cmdString[cmdStrPtr++]='D';
	cmdString[cmdStrPtr++]='\'';
}
void _D2(){
	D();D();
	cmdString[cmdStrPtr++]='D';
	cmdString[cmdStrPtr++]='2';
}
void _E(){
	E();
	cmdString[cmdStrPtr++]='E';
}
void _Er(){
	Er();
	cmdString[cmdStrPtr++]='E';
	cmdString[cmdStrPtr++]='\'';
}
void _E2(){
	E();E();
	cmdString[cmdStrPtr++]='E';
	cmdString[cmdStrPtr++]='2';
}
void _M(){
	M();
	cmdString[cmdStrPtr++]='M';
}
void _Mr(){
	Mr();
	cmdString[cmdStrPtr++]='M';
	cmdString[cmdStrPtr++]='\'';
}
//interesting ,some functions' name are macros defined by vc
#undef _M2
void _M2(){
	M();M();
	cmdString[cmdStrPtr++]='M';
	cmdString[cmdStrPtr++]='2';
}
void _S(){
	S();
	cmdString[cmdStrPtr++]='S';
}
void _Sr(){
	Sr();
	cmdString[cmdStrPtr++]='S';
	cmdString[cmdStrPtr++]='\'';
}
void _S2(){
	S();S();
	cmdString[cmdStrPtr++]='S';
	cmdString[cmdStrPtr++]='2';
}
void _x(){
	x();
	cmdString[cmdStrPtr++]='x';
}
void _xr(){
	xr();
	cmdString[cmdStrPtr++]='x';
	cmdString[cmdStrPtr++]='\'';
}
void _x2(){
	x();x();
	cmdString[cmdStrPtr++]='x';
	cmdString[cmdStrPtr++]='2';
}
void _y(){
	y();
	cmdString[cmdStrPtr++]='y';
}
void _yr(){
	yr();
	cmdString[cmdStrPtr++]='y';
	cmdString[cmdStrPtr++]='\'';
}
void _y2(){
	y();y();
	cmdString[cmdStrPtr++]='y';
	cmdString[cmdStrPtr++]='2';
}
void _z(){
	z();
	cmdString[cmdStrPtr++]='z';
}
void _zr(){
	zr();
	cmdString[cmdStrPtr++]='z';
	cmdString[cmdStrPtr++]='\'';
}
void _z2(){
	z();z();
	cmdString[cmdStrPtr++]='z';
	cmdString[cmdStrPtr++]='2';
}
void _u(){
	u();
	cmdString[cmdStrPtr++]='u';
}
void _ur(){
	ur();
	cmdString[cmdStrPtr++]='u';
	cmdString[cmdStrPtr++]='\'';
}
void _u2(){
	u();u();
	cmdString[cmdStrPtr++]='u';
	cmdString[cmdStrPtr++]='2';
}
void _r(){
	r();
	cmdString[cmdStrPtr++]='r';
}
void _rr(){
	rr();
	cmdString[cmdStrPtr++]='r';
	cmdString[cmdStrPtr++]='\'';
}
void _r2(){
	r();r();
	cmdString[cmdStrPtr++]='r';
	cmdString[cmdStrPtr++]='2';
}
void _f(){
	f();
	cmdString[cmdStrPtr++]='f';
}
void _fr(){
	fr();
	cmdString[cmdStrPtr++]='f';
	cmdString[cmdStrPtr++]='\'';
}
void _f2(){
	f();f();
	cmdString[cmdStrPtr++]='f';
	cmdString[cmdStrPtr++]='2';
}
void _d(){
	d();
	cmdString[cmdStrPtr++]='d';
}
void _dr(){
	dr();
	cmdString[cmdStrPtr++]='d';
	cmdString[cmdStrPtr++]='\'';
}
void _d2(){
	d();d();
	cmdString[cmdStrPtr++]='d';
	cmdString[cmdStrPtr++]='2';
}
void _l(){
	l();
	cmdString[cmdStrPtr++]='l';
}
void _lr(){
	lr();
	cmdString[cmdStrPtr++]='l';
	cmdString[cmdStrPtr++]='\'';
}
void _l2(){
	l();l();
	cmdString[cmdStrPtr++]='l';
	cmdString[cmdStrPtr++]='2';
}
void _b(){
	b();
	cmdString[cmdStrPtr++]='b';
}
void _br(){
	br();
	cmdString[cmdStrPtr++]='b';
	cmdString[cmdStrPtr++]='\'';
}
void _b2(){
	b();b();
	cmdString[cmdStrPtr++]='b';
	cmdString[cmdStrPtr++]='2';
}
///////////////////////////////////////////////////



//check whether the user edited cube is a valid cube
bool IsValidLayout(void)
{
	return false;
}
//find the four facelets on edge for a color
void GetFacelet4(Facelet* facelet,Color color)
{
	int pointer=0;
	int index[4]={1,3,5,7};//facelets numbered 1,3,5,7 is on edges
	for (int i=0;i<6;i++){		
		for (int j=0;j<4;j++){
			if (aspectColors[i][index[j]]==color){			
				facelet[pointer].asp=(Aspect)i;
				facelet[pointer].index=index[j];
				facelet[pointer].color=aspectColors[facelet[pointer].asp][facelet[pointer].index];
				pointer++;
				if (pointer>=4){//all have been found
					return;
				}
			}
		}
	}
	ASSERT(pointer==4);
}
//find the other facelet on the same edge
Facelet GetNeighborEdgeFacelet(Facelet facelet)
{
	Facelet faceletNeighbor;
	switch(facelet.asp){
		case FRONT:
			faceletNeighbor.index=7;
			switch (facelet.index){				
		case 1:
			faceletNeighbor.asp=DOWN;
			break;
		case 3:
			faceletNeighbor.asp=LEFT;
			break;
		case 5:
			faceletNeighbor.asp=RIGHT;
			break;
		case 7:
			faceletNeighbor.asp=UP;
			break;
		default:
			break;
			}
			break;
		case BACK:
			faceletNeighbor.index=1;
			switch (facelet.index){				
		case 1:
			faceletNeighbor.asp=DOWN;
			break;
		case 3:
			faceletNeighbor.asp=LEFT;
			break;
		case 5:
			faceletNeighbor.asp=RIGHT;
			break;
		case 7:
			faceletNeighbor.asp=UP;
			break;
		default:
			break;
			}
			break;
		case RIGHT:
			faceletNeighbor.index=5;
			switch (facelet.index){				
		case 1:					
			faceletNeighbor.asp=BACK;
			break;
		case 3:
			faceletNeighbor.asp=DOWN;
			break;
		case 5:
			faceletNeighbor.asp=UP;
			break;
		case 7:
			faceletNeighbor.asp=FRONT;
			break;
		default:
			break;
			}
			break;
		case LEFT:
			faceletNeighbor.index=3;
			switch (facelet.index){				
		case 1:
			faceletNeighbor.asp=BACK;
			break;
		case 3:
			faceletNeighbor.asp=DOWN;
			break;
		case 5:
			faceletNeighbor.asp=UP;
			break;
		case 7:
			faceletNeighbor.asp=FRONT;
			break;
		default:
			break;
			}
			break;
		case UP:
			switch (facelet.index){
		case 1:
			faceletNeighbor.asp=BACK;
			faceletNeighbor.index=7;
			break;
		case 3:
			faceletNeighbor.asp=LEFT;
			faceletNeighbor.index=5;
			break;
		case 5:
			faceletNeighbor.asp=RIGHT;
			faceletNeighbor.index=5;
			break;
		case 7:
			faceletNeighbor.asp=FRONT;
			faceletNeighbor.index=7;
			break;
		default:
			break;
			}
			break;
		case DOWN:
			switch (facelet.index){
		case 1:
			faceletNeighbor.asp=BACK;
			faceletNeighbor.index=1;
			break;
		case 3:
			faceletNeighbor.asp=LEFT;
			faceletNeighbor.index=3;
			break;
		case 5:
			faceletNeighbor.asp=RIGHT;
			faceletNeighbor.index=3;
			break;
		case 7:
			faceletNeighbor.asp=FRONT;
			faceletNeighbor.index=1;
			break;
		default:
			break;
			}
			break;
		default:
			break;
	}
	faceletNeighbor.color=aspectColors[faceletNeighbor.asp][faceletNeighbor.index];
	return faceletNeighbor;
}
//find the other two facelets on the same corner
void GetNeighborCornerFacelets(Facelet* neighbor2,Facelet facelet)
{
	if (facelet.asp==FRONT){
		switch(facelet.index){
			case 0:
				neighbor2[0].asp=LEFT;
				neighbor2[0].index=6;
				neighbor2[1].asp=DOWN;
				neighbor2[1].index=6;
				break;
			case 2:
				neighbor2[0].asp=DOWN;
				neighbor2[0].index=8;
				neighbor2[1].asp=RIGHT;
				neighbor2[1].index=6;
				break;
			case 6:
				neighbor2[0].asp=LEFT;
				neighbor2[0].index=8;
				neighbor2[1].asp=UP;
				neighbor2[1].index=6;
				break;
			case 8:
				neighbor2[0].asp=UP;
				neighbor2[0].index=8;
				neighbor2[1].asp=RIGHT;
				neighbor2[1].index=8;
				break;
			default:
				break;
		}
	}else if(facelet.asp==BACK){
		switch(facelet.index){
			case 0:
				neighbor2[0].asp=LEFT;
				neighbor2[0].index=0;
				neighbor2[1].asp=DOWN;
				neighbor2[1].index=0;
				break;
			case 2:
				neighbor2[0].asp=DOWN;
				neighbor2[0].index=2;
				neighbor2[1].asp=RIGHT;
				neighbor2[1].index=0;
				break;
			case 6:
				neighbor2[0].asp=UP;
				neighbor2[0].index=0;
				neighbor2[1].asp=LEFT;
				neighbor2[1].index=2;
				break;
			case 8:
				neighbor2[0].asp=UP;
				neighbor2[0].index=2;
				neighbor2[1].asp=RIGHT;
				neighbor2[1].index=2;
				break;
			default:
				break;
		}
	}

	neighbor2[0].color=aspectColors[neighbor2[0].asp][neighbor2[0].index];
	neighbor2[1].color=aspectColors[neighbor2[1].asp][neighbor2[1].index];
}
//find the edge contains the two given color ,in which first is color 
//main face ,the second is color of side face
Edge GetEdge(Color colorMain,Color colorSide)
{
	Edge edge;
	Facelet facelets[4];
	GetFacelet4(facelets,colorMain);
	Facelet faceletOther;
	for (int i=0;i<4;i++){
		faceletOther=GetNeighborEdgeFacelet(facelets[i]);
		if (faceletOther.color==colorSide){
			edge.faceletMain=facelets[i];
			edge.faceletSide=faceletOther;
			return edge;
		}
	}
	return edge;
}
//whether the cross has been built
bool IsCrossed()
{	
	for (int i=1;i<8;i+=2){
		if (aspectColors[FRONT][4]!=aspectColors[FRONT][i]){
			return false;
		}
	}
	for (int i=2;i<=5;i++){
		if (aspectColors[i][4]!=aspectColors[i][7]){
			return false;
		}
	}
	return true;
}
//rotate cube to cross state,and the cross is built on down face
CString Cross(void)
{
	//two method to make cross:rule database or search
	//rules are used here

	/* for an edge which contained in the cross,there are 24 situations.
	*but I categorize them into 3 kinds in a clear way which came up my
	*mind in a sudden.Set front face is the face on which the cross will
	*be built.colorMain on LEFT/RIGHT/BACK contains 12 situations,while 
	*colorSide on LEFT/RIGHT/BACK contains 12 situations too.
	*4 situations was repetive.there 4 situations are on the front face.
	*/
	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;
	while (!IsCrossed()){		
		testCount++;
		if (testCount>3){
			CString filename="bug/Cross.ml";
			CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			MessageBox(NULL,"bug emerged in function:Cross,saved as Cross.ml","error",MB_OK);
			break;
		}

		//record number of faces done 
		int numDone=0;

		//check whether there is a facelet is of same color with center on FRONT face
		/*Facelet facelet;
		facelet.asp=FRONT;
		for (int i=1;i<9;i+=2){
		if (aspectColors[FRONT][i]==aspectColors[FRONT][4]){
		facelet.index=i;
		facelet.color=aspectColors[FRONT][4];
		break;
		}
		}*/
		//it will work still,if this 'if' sentence does not exist.
		//this is a special situation detection
		//if (facelet.index>=0){//found
		//	//turn the facelet to left
		//	if (facelet.index==1){
		//		_F();
		//	}else if (facelet.index==7){
		//		_Fr();
		//	}else if (facelet.index==5){
		//		_F2();
		//	}
		//	//get neighbor's color
		//	Facelet f=GetNeighborEdgeFacelet(facelet);
		//	//turn corresponding face to position
		//	if(aspectColors[3][4]==f.color){
		//		_b2();
		//	}else if (aspectColors[4][4]==f.color){
		//		_b();
		//	}else if (aspectColors[5][4]==f.color){
		//		_br();
		//	}
		//	numDone=1;
		//	_zr();
		//}
		while (numDone<4){
			//find edges
			Edge edge=GetEdge(aspectColors[FRONT][4],aspectColors[UP][4]);
			if (edge.faceletMain.asp==LEFT){//main facelet 
				//move main color to position 5 first
				if (edge.faceletMain.index==7){
					_Lr();_Ur();
				}else if (edge.faceletMain.index==1){
					/* numDone estimation is to check whether there is a need to 
					*turn side rotated back .this can reduce the steps needed to
					*restore the cube.but is hindered optimization of program*/
					_L();_Ur();
					if (numDone!=0){
						_Lr();
					}
				}else if (edge.faceletMain.index==3){										
					_L2();_Ur();
					if (numDone!=0){
						_L2();
					}
				}else if (edge.faceletMain.index==5){//5
					_Ur();
				}
				//then
				//_Ur();
			}else if (edge.faceletMain.asp==RIGHT){
				//move main color to position 5 first
				if (edge.faceletMain.index==7){
					_R();_U();
				}else if (edge.faceletMain.index==1){
					_Rr();_U();
					if (numDone==3){
						_R();
					}
				}else if (edge.faceletMain.index==3){
					_R2();_U();
					if (numDone==3){
						_R2();
					}
				}else if (edge.faceletMain.index==5){//5
					_U();
				}
				//then
				//_U();
			}else if (edge.faceletMain.asp==BACK&&edge.faceletMain.index==1){
				//move main color to position 7 first			
				_B2();_U2();
			}else if (edge.faceletMain.asp==BACK&&edge.faceletMain.index==7){
				_U2();

				/*else if (edge.faceletMain.index==3){
				_Br();
				}else if (edge.faceletMain.index==5){
				_B();
				}*/
				//then
				//_U2();
			}else if (edge.faceletSide.asp==LEFT){//side facelet
				//move side color to position 1 first
				if (edge.faceletSide.index==3){
					_L();_Br();
					if (numDone!=0){
						_Lr();
					}	
					_U2();
				}else if (edge.faceletSide.index==5){
					_Lr();_Br();
					if (numDone!=0){
						_L();
					}	
					_U2();
				}else if (edge.faceletSide.index==7){
					if (numDone==0){
						_F();
					}else{
						_L2();_Br();
						if (numDone!=0){
							_L2();
						}
						_U2();
					}				
				}else if (edge.faceletSide.index==1){
					_Br();_U2();
				}
				//then
				//_U2();
			}else if (edge.faceletSide.asp==RIGHT){
				//move side color to position 1 first
				if (edge.faceletSide.index==3){
					_Rr();_B();
					if (numDone==3){
						_R();
					}
					_U2();
				}else if (edge.faceletSide.index==5){
					_R();_B();
					if (numDone==3){
						_Rr();
					}
					_U2();
				}else if (edge.faceletSide.index==7){
					if (numDone==0){
						_Fr();
					}else{
						_R2();_B();
						if (numDone==3){
							_R2();
						}
						_U2();
					}				
				}else if (edge.faceletSide.index==1){
					_Br();_U2();
				}
				//then
				//_U2();
			}else if (edge.faceletSide.asp==BACK&&edge.faceletSide.index==7){
				//for the symmetry of code,I did not merge the code below

				_B();_L();_Ur();
				if (numDone!=0){
					_Lr();
				}
			}/*else if (edge.faceletSide.index==3){
			 _L();_Ur();
			 if (numDone!=0){
			 _Lr();
			 }
			 }*/else if (edge.faceletSide.asp==BACK&&edge.faceletSide.index==1){
				 _B();_Rr();_U();
				 if (numDone==3){
					 _R();
					}
				 /*else if (edge.faceletSide.index==5){
				 _Rr();_U();
				 if (numDone==3){
				 _R();
					}
					}*/
			}else if (edge.faceletMain.asp==FRONT){
				if (edge.faceletMain.index==1){//special situations on FRONT face
					if (numDone==0){
						_F2();
					}else{
						_D2();_B2();_U2();					
					}				
				}//else{
				//	//in correct position
				//}
			}else if (edge.faceletSide.asp==FRONT){
				if (edge.faceletSide.index==1){
					_D();_Rr();_B();_U2();
					if (numDone==3){
						_R();
					}
				}else{//7
					_U();_Lr();_Br();_U2();
					if (numDone!=0){
						_L();
					}
				}
			}	

			_zr();		
			numDone++;
		}
	}

	return CString(cmdString);

}

//whether corner of first layer is ready
bool IsFirstLayerCornerRestored()
{
	if (aspectColors[FRONT][0]==aspectColors[FRONT][1]&&
		aspectColors[FRONT][2]==aspectColors[FRONT][1]&&
		aspectColors[BACK][0]==aspectColors[BACK][1]&&
		aspectColors[BACK][2]==aspectColors[BACK][1]&&
		aspectColors[LEFT][0]==aspectColors[LEFT][3]&&
		aspectColors[LEFT][6]==aspectColors[LEFT][3]&&
		aspectColors[RIGHT][0]==aspectColors[RIGHT][3]&&
		aspectColors[RIGHT][6]==aspectColors[RIGHT][3]){
			bool allSame=true;
			for (int i=1;i<9;i+=2){
				if (aspectColors[DOWN][i]!=aspectColors[DOWN][4]){
					allSame=false;
					break;
				}
			}
			if (allSame){
				return true;
			}
	}
	return false;
}
//restore corners of first layer
CString RestoreFirstLayerCorner()
{
	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;
	while (!IsFirstLayerCornerRestored()){
		testCount++;
		if (testCount>20){
			MessageBox(NULL,"bug emerged in function:RestoreFirstLayerCorner","error",MB_OK);
			CString filename="bug/RestoreFirstLayerCorner.ml";
			CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			exit(-1);
		}
		bool searchUp=true;
		//search corners on top which should be on bottom
		for (int i=0;i<4;i++){
			bool found=false;
			//find and adjust the correct corner block
			if (aspectColors[FRONT][6]==aspectColors[DOWN][4]){//left
				if (aspectColors[UP][6]==aspectColors[FRONT][4]){// UP FRONT
					if (aspectColors[LEFT][8]==aspectColors[LEFT][4]){//LEFT LEFT
						_yr();
					}else{//LEFT RIGHT
						_Ur();
					}
				}else if (aspectColors[UP][6]==aspectColors[LEFT][4]){//UP LEFT
					if (aspectColors[LEFT][8]==aspectColors[FRONT][4]){//LEFT FRONT
						_yr();
					}else{//LEFT BACK
						_U();_y2();
					}
				}else if (aspectColors[LEFT][8]==aspectColors[FRONT][4]){//LEFT FRONT
					_Ur();
				}else if (aspectColors[LEFT][8]==aspectColors[LEFT][4]){//LEFT LEFT
					_U();_y2();
				}else {//left front corner should be on right back
					_U2();_y();
				}
				found=true;
			}else if (aspectColors[FRONT][8]==aspectColors[DOWN][4]){//right
				if (aspectColors[UP][8]==aspectColors[FRONT][4]){// UP FRONT
					if (aspectColors[RIGHT][8]==aspectColors[RIGHT][4]){//RIGHT RIGHT
						//on correct position
					}else{//RIGHT LEFT
						//_U();_yr();
						_d();
					}
				}else if (aspectColors[UP][8]==aspectColors[RIGHT][4]){//UP RIGHT
					if (aspectColors[RIGHT][8]==aspectColors[FRONT][4]){//RIGHT FRONT
						//on correct position
					}else{//RIGHT BACK
						//_Ur();_y();
						_dr();
					}
				}else if (aspectColors[RIGHT][8]==aspectColors[FRONT][4]){//RIGHT FRONT
					_d();
				}else if (aspectColors[RIGHT][8]==aspectColors[RIGHT][4]){//RIGHT RIGHT
					_dr();
				}else{//right front corner should be on left back
					_U2();_y2();
				}
				found=true;
			}

			if (found){//if found ,use formula to restore the corner
				//the corner is on FRT corner	
				if (aspectColors[FRONT][8]==aspectColors[DOWN][4]){
					_U();_R();_Ur();_Rr();
				}else{
					_R();_U();_Rr();
				}
				searchUp=false;
				break;/* for */
			}else{//if not found,search next side
				_y();
			}
		}
		//search top if target not found on sides
		bool searchDown=false;
		if (!searchUp){
			continue;/* while */
		}else{
			bool found=true;
			//search top and adjust 
			if (aspectColors[UP][0]==aspectColors[DOWN][4]){
				_y2();
			}else if (aspectColors[UP][2]==aspectColors[DOWN][4]){
				_y();
			}else if (aspectColors[UP][6]==aspectColors[DOWN][4]){
				_yr();
			}else if (aspectColors[UP][8]==aspectColors[DOWN][4]){
				//correct
			}else {
				searchDown=true;
				found=false;
			}
			if (found){
				//adjustment
				if (aspectColors[FRONT][8]==aspectColors[FRONT][4]){
					_d();
				}else if (aspectColors[RIGHT][8]==aspectColors[RIGHT][4]){
					_dr();
				}else {
					_d2();
				}
				//formula
				_R();_U2();_Rr();_Ur();
				//then to another situation
				//_R();_U();_Rr();
			}
		}
		if (searchDown){
			//search bottom and adjust
			for (int i=0;i<4;i++){
				bool found=true;
				if (aspectColors[FRONT][0]==aspectColors[DOWN][4]){
					_yr();
				}else if (aspectColors[FRONT][2]==aspectColors[DOWN][4]){
					//correct
				}else{
					if (aspectColors[DOWN][6]==aspectColors[DOWN][4]&&
						aspectColors[FRONT][0]!=aspectColors[FRONT][4]){
							_R();_U();_Rr();							
					}
					_y();
					found=false;
				}
				if (found){
					//restore
					if (aspectColors[RIGHT][6]==aspectColors[DOWN][4]){
						_R();_U();_Rr();_U();
						//then
						//_R();_U();_Rr();
					}else if (aspectColors[FRONT][2]==aspectColors[DOWN][4]){
						_R();_Ur();_Rr();
						//then
						//_U();_R();_Ur();_Rr();
					}
					break;
				}
			}
		}
	}
	return CString(cmdString);
}
//whether edges on second layer are restored
bool IsSecondLayerEdgeRestored(void)
{
	if (aspectColors[FRONT][4]==aspectColors[FRONT][3]&&
		aspectColors[FRONT][4]==aspectColors[FRONT][5]&&
		aspectColors[BACK][4]==aspectColors[BACK][3]&&
		aspectColors[BACK][4]==aspectColors[BACK][5]&&
		aspectColors[LEFT][4]==aspectColors[LEFT][1]&&
		aspectColors[LEFT][4]==aspectColors[LEFT][7]&&
		aspectColors[RIGHT][4]==aspectColors[RIGHT][1]&&
		aspectColors[RIGHT][4]==aspectColors[RIGHT][7]){
			return true;
	}
	return false;
}

//restore edges of second layer
CString RestoreSecondLayerEdge()
{
	ASSERT(IsFirstLayerCornerRestored());

	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;
	while(!IsSecondLayerEdgeRestored()){
		testCount++;
		if (testCount>10){
			MessageBox(NULL,"bug emerged in function:RestoreSecondLayerEdge","error",MB_OK);
			CString filename="bug/RestoreSecondLayerEdge.ml";
			CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			exit(-1);
		}
		bool found=false;
		for (int i=0;i<4;i++){
			if (aspectColors[FRONT][7]!=aspectColors[UP][4]&&
				aspectColors[UP][7]!=aspectColors[UP][4]){//found			
					if (aspectColors[FRONT][7]!=aspectColors[FRONT][4]){//front not matched
						//rotate to match
						if (aspectColors[FRONT][7]==aspectColors[LEFT][4]){
							_d();
						}else if (aspectColors[FRONT][7]==aspectColors[RIGHT][4]){
							_dr();
						}else if (aspectColors[FRONT][7]==aspectColors[BACK][4]){
							_d2();
						}
					}
					_yr();//adjustment
					//formula					
					if (aspectColors[UP][5]==aspectColors[FRONT][4]){//RIGHT FRONT
						_Rr();_Ur();_Rr();_Ur();_Rr();_U();_R();_U();_R();
					}else {//RIGHT BACK
						_R();_U();_R();_U();_R();_Ur();_Rr();_Ur();_Rr();
					}

					found=true;
					break;
			}
			_y();
		}
		if (!found){//search middle layer
			for (int i=0;i<4;i++){
				if (aspectColors[FRONT][5]!=aspectColors[FRONT][4]){
					_Rr();_Ur();_Rr();_Ur();_Rr();_U();_R();_U();_R();
					break;
				}
				_y();
			}
		}
	}
	return CString(cmdString);
}
//whether F2L is done
bool IsF2L()
{
	if (IsFirstLayerCornerRestored()&&
		IsSecondLayerEdgeRestored()){
			return true;
	}
	return false;
}
//restore First 2 Layer
CString F2L(void)
{
	CString ret;
	ret="#Cross:\r\n\t#";
	//make cross
	ret+=Cross();
	xr();
	ret+="#\r\nRotate to bottom:\r\n\t#";
	ret+="x'";
	//restore corners of first layer
	ret+="#\r\nRestore Corners of First Layer:\r\n\t#";
	ret+=RestoreFirstLayerCorner();
	//restore edges of second layer
	ret+="#\r\nRestore Edges of Second Layer:\r\n\t#";
	ret+=RestoreSecondLayerEdge();

	return ret;
}

///////////////////////////////////////////////////
//whether top cross is built
bool IsTopCrossed()
{
	for (int i=1;i<9;i+=2){
		if (aspectColors[UP][i]!=aspectColors[UP][4]){
			return false;
		}
	}
	return true;
}
//built cross on top
CString BuildTopCross()
{
	ASSERT(IsF2L());

	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;
	while(!IsTopCrossed()){
		testCount++;
		if (testCount>5){
			CString filename="bug/BuildTopCross.ml";
			CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			MessageBox(NULL,"bug emerged in function:BuildTopCross","error",MB_OK);
			exit(-1);
		}

		if (aspectColors[UP][3]==aspectColors[UP][4]&&
			aspectColors[UP][5]==aspectColors[UP][4]){//situation 1a
				if (aspectColors[FRONT][7]!=aspectColors[UP][4]){
					//adjustment
					_y2();
				}
				_F();_R();_U();_Rr();_Ur();_Fr();
		}else if (aspectColors[UP][1]==aspectColors[UP][4]&&//situation 1b
			aspectColors[UP][7]==aspectColors[UP][4]){
				_y();
				if (aspectColors[FRONT][7]!=aspectColors[UP][4]){
					//adjustment
					_y2();
				}
				_F();_R();_U();_Rr();_Ur();_Fr();
		}else if (aspectColors[UP][3]==aspectColors[UP][4]){//situation 2a
			bool isTwo=false;
			if(aspectColors[UP][7]==aspectColors[UP][4]){
				_y();
				isTwo=true;
			}else if (aspectColors[UP][1]==aspectColors[UP][4]){
				isTwo=true;
			}
			if (isTwo){
				_F();_U();_R();_Ur();_Rr();_Fr();
			}
		}else if (aspectColors[UP][5]==aspectColors[UP][4]){//situation 2b
			bool isTwo=false;
			if(aspectColors[UP][7]==aspectColors[UP][4]){
				_y2();
				isTwo=true;
			}else if (aspectColors[UP][1]==aspectColors[UP][4]){
				_yr();
				isTwo=true;
			}
			if (isTwo){
				_F();_U();_R();_Ur();_Rr();_Fr();
			}
		}else{//situation 3
			for (int i=0;i<4;i++){
				if (aspectColors[FRONT][7]==aspectColors[UP][4]&&
					aspectColors[RIGHT][5]==aspectColors[UP][4]){
						_F();_U();_R();_Ur();_Rr();_Fr();
						//then
						//_F();_R();_U();_Rr();_Ur();_Fr();
						break;
				}
				_y();
			}			
		}
	}
	return CString(cmdString);
}
void Executor(const char* cmd)
{
	//space,'(' and ')' can be filtered first,and "'2" can be replaced by 2

	while(*cmd){
		switch(*cmd){
			case ' ':				
			case '(':
			case ')':				
				break;
			case '#':				
				do{
					cmd++;
				}while(*cmd!='#'&&*cmd);
				break;
			case 'F':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						F2();
						cmd++;
					}else{
						Fr();
					}		
					cmd++;
				}else if (*(cmd+1)=='2'){
					F2();
					cmd++;
				}else{
					F();
				}
				break;
			case 'B':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						B2();
						cmd++;
					}else{
						Br();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					B2();
					cmd++;
				}else{
					B();
				}
				break;
			case 'L':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						L2();
						cmd++;
					}else{
						Lr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					L2();
					cmd++;
				}else{
					L();
				}
				break;
			case 'R':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						R2();
						cmd++;
					}else{
						Rr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					R2();
					cmd++;
				}else{
					R();
				}
				break;
			case 'U':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						U2();
						cmd++;
					}else{
						Ur();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					U2();
					cmd++;
				}else{
					U();
				}
				break;
			case 'D':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						D2();
						cmd++;
					}else{
						Dr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					D2();
					cmd++;
				}else{
					D();
				}
				break;
			case 'x':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						x2();
						cmd++;
					}else{
						xr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					x2();
					cmd++;
				}else{
					x();
				}
				break;
			case 'y':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						y2();
						cmd++;
					}else{
						yr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					y2();
					cmd++;
				}else{
					y();
				}
				break;
			case 'z':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						z2();
						cmd++;
					}else{
						zr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					z2();
					cmd++;
				}else{
					z();
				}
				break;
			case 'f':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						f2();
						cmd++;
					}else{
						fr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					f2();
					cmd++;
				}else{
					f();
				}
				break;
			case 'b':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						b2();
						cmd++;
					}else{
						br();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					b2();
					cmd++;
				}else{
					b();
				}
				break;
			case 'l':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						l2();
						cmd++;
					}else{
						lr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					l2();
					cmd++;
				}else{
					l();
				}
				break;
			case 'r':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						r2();
						cmd++;
					}else{
						rr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					r2();
					cmd++;
				}else{
					r();
				}
				break;
			case 'u':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						u2();
						cmd++;
					}else{
						ur();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					u2();
					cmd++;
				}else{
					u();
				}
				break;
			case 'd':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						d2();
						cmd++;
					}else{
						dr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					d2();
					cmd++;
				}else{
					d();
				}
				break;
			case 'E':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						E2();
						cmd++;
					}else{
						Er();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					E2();
					cmd++;
				}else{
					E();
				}
				break;
			case 'M':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						M2();
						cmd++;
					}else{
						Mr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					M2();
					cmd++;
				}else{
					M();
				}
				break;
			case 'S':
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2
						S2();
						cmd++;
					}else{
						Sr();
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					S2();
					cmd++;
				}else{
					S();
				}
				break;
			default:
				break;
		}
		cmd++;
	}
}

//
bool IsTopCrossMatched(void)
{
	if (aspectColors[FRONT][7]!=aspectColors[FRONT][4]){
		return false;
	}
	if (aspectColors[BACK][7]!=aspectColors[BACK][4]){
		return false;
	}
	if (aspectColors[LEFT][5]!=aspectColors[LEFT][4]){
		return false;
	}
	if (aspectColors[RIGHT][5]!=aspectColors[RIGHT][4]){
		return false;
	}
	return true;
}
CString MatchTopCross(void)
{
	ASSERT(IsTopCrossed());

	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;
	while (!IsTopCrossMatched()){
		testCount++;
		if (testCount>1){
			MessageBox(NULL,"bug emerged in function:MatchTopCross,saved in MatchTopCross.ml","error",MB_OK);
			CString filename="bug/MatchTopCross.ml";
			CFile fileout(filename.GetBuffer(filename.GetLength()),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			exit(-1);
		}
		//match edge first,then use formula
		for (int jj=0;jj<4;jj++){
			//match
			for (int i=0;i<4;i++){//match Back
				if (aspectColors[BACK][4]!=aspectColors[BACK][7]){
					_U();
				}else{
					break;
				}
			}
			if (IsTopCrossMatched()){
				return CString(cmdString);
			}
			//formula
			if (aspectColors[LEFT][4]==aspectColors[LEFT][5]){//LEFT match
				char* formula="(RU2R')(U'RU'R')U'";
				Executor(formula);
				strcpy(cmdString+cmdStrPtr,formula);
				cmdStrPtr+=strlen(formula);
				return CString(cmdString);
			}else if (aspectColors[FRONT][4]==aspectColors[FRONT][7]){//RIGHT match
				char* formula="(RU2R')(U'RU'R')y(RU2R')(U'RU'R')U'";
				Executor(formula);
				strcpy(cmdString+cmdStrPtr,formula);
				cmdStrPtr+=strlen(formula);
				return CString(cmdString);
			}
			_yr();
		}
		MessageBox(NULL,"special situation not recorded found,saved in file :MatchTopCross-special.ml","error",MB_OK);
		CString filename="MatchTopCross-special.ml";
		CFile fileout(filename.GetBuffer(filename.GetLength()),CFile::modeCreate|CFile::modeWrite);
		fileout.Write(aspectColors,sizeof(aspectColors));
		fileout.Close();
	}	
	return CString(cmdString);
}
//calculate a hash value for a corner to differ from other corners
//according to its colors.there are various methods
int HashCorner(Color c1,Color c2,Color c3)
{
	return (c1+1)*(c2+1)*(c3+1);
}

bool IsTopCornerBack(void)
{
	int cornerHashDst[4];//hash value of this corner should be
	int cornerHashSrc[4];//hash value for current corners
	//start from leftFront corner,counterclockwise
	cornerHashDst[0]=HashCorner(aspectColors[UP][4],aspectColors[LEFT][4],aspectColors[FRONT][4]);
	cornerHashDst[1]=HashCorner(aspectColors[UP][4],aspectColors[FRONT][4],aspectColors[RIGHT][4]);
	cornerHashDst[2]=HashCorner(aspectColors[UP][4],aspectColors[RIGHT][4],aspectColors[BACK][4]);
	cornerHashDst[3]=HashCorner(aspectColors[UP][4],aspectColors[BACK][4],aspectColors[LEFT][4]);

	cornerHashSrc[0]=HashCorner(aspectColors[UP][6],aspectColors[LEFT][8],aspectColors[FRONT][6]);
	cornerHashSrc[1]=HashCorner(aspectColors[UP][8],aspectColors[FRONT][8],aspectColors[RIGHT][8]);
	cornerHashSrc[2]=HashCorner(aspectColors[UP][2],aspectColors[RIGHT][2],aspectColors[BACK][8]);
	cornerHashSrc[3]=HashCorner(aspectColors[UP][0],aspectColors[BACK][6],aspectColors[LEFT][2]);
	for (int i=0;i<4;i++){
		if (cornerHashSrc[i]!=cornerHashDst[i]){
			return false;
		}
	}
	return true;
}
CString PutBackTopCorner(void)
{
	ASSERT(IsTopCrossMatched());

	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;

	int testCount=0;		
	while(!IsTopCornerBack()){
		testCount++;
		if (testCount>3){
			CString filename="bug/PutBackTopCorner.ml";
			CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
			fileout.Write(aspectColors,sizeof(aspectColors));
			fileout.Close();
			MessageBox(NULL,"bug emerged in function:PutBackTopCorner","error",MB_OK);
			exit(-1);
		}

		int cornerHashDst[4];//hash value of this corner should be
		int cornerHashSrc[4];//hash value for current corners
		//start from leftFront corner,counterclockwise
		cornerHashDst[0]=HashCorner(aspectColors[UP][4],aspectColors[LEFT][4],aspectColors[FRONT][4]);
		cornerHashDst[1]=HashCorner(aspectColors[UP][4],aspectColors[FRONT][4],aspectColors[RIGHT][4]);
		cornerHashDst[2]=HashCorner(aspectColors[UP][4],aspectColors[RIGHT][4],aspectColors[BACK][4]);
		cornerHashDst[3]=HashCorner(aspectColors[UP][4],aspectColors[BACK][4],aspectColors[LEFT][4]);

		cornerHashSrc[0]=HashCorner(aspectColors[UP][6],aspectColors[LEFT][8],aspectColors[FRONT][6]);
		cornerHashSrc[1]=HashCorner(aspectColors[UP][8],aspectColors[FRONT][8],aspectColors[RIGHT][8]);
		cornerHashSrc[2]=HashCorner(aspectColors[UP][2],aspectColors[RIGHT][2],aspectColors[BACK][8]);
		cornerHashSrc[3]=HashCorner(aspectColors[UP][0],aspectColors[BACK][6],aspectColors[LEFT][2]);

		//analysis
		//find backed corner first
		bool found=false;
		for (int i=0;i<4;i++){
			if (cornerHashDst[i]==cornerHashSrc[i]){
				found=true;
				//analyze relative positions of the other three corners
				RotateDirection direction;
				if (cornerHashDst[(i+1)%4]==cornerHashSrc[(i+2)%4]){//clockwise
					direction=CLOCKWISE;					
				}else if (cornerHashDst[(i+2)%4]==cornerHashSrc[(i+1)%4]){//clockwise
					direction=COUNTERCLOCKWISE;
				}else {
					MessageBox(NULL,"something wrong with PutBackTopCorner","error",MB_OK);
					exit(-1);
				}
				if (direction==COUNTERCLOCKWISE){
					//adjust direction of the cube
					if (i==3){
						_yr();
					}else if (i==2){
						_y2();
					}else if (i==1){
						_y();
					}
					char* formula="RU'L'UR'U'LU";
					Executor(formula);
					strcpy(cmdString+cmdStrPtr,formula);
					cmdStrPtr+=strlen(formula);
				}else {
					if (i==3){
						_y2();
					}else if (i==2){
						_y();
					}else if (i==1){
						_yr();
					}
					char* formula="L'URU'LUR'U'";
					Executor(formula);
					strcpy(cmdString+cmdStrPtr,formula);
					cmdStrPtr+=strlen(formula);
				}
			}
		}
		if (!found){//none of the four corners is in right position
			char* formula="RU'L'UR'U'LUy";
			Executor(formula);
			strcpy(cmdString+cmdStrPtr,formula);
			cmdStrPtr+=strlen(formula);
		}
	}
	return CString(cmdString);
}
bool IsTopCornerRestored(void)
{
	if (aspectColors[UP][0]!=aspectColors[UP][4]||
		aspectColors[UP][2]!=aspectColors[UP][4]||
		aspectColors[UP][6]!=aspectColors[UP][4]||
		aspectColors[UP][8]!=aspectColors[UP][4]||
		aspectColors[LEFT][2]!=aspectColors[LEFT][4]||
		aspectColors[LEFT][8]!=aspectColors[LEFT][4]||
		aspectColors[RIGHT][2]!=aspectColors[RIGHT][4]||
		aspectColors[RIGHT][8]!=aspectColors[RIGHT][4]||
		aspectColors[FRONT][6]!=aspectColors[FRONT][4]||
		aspectColors[FRONT][8]!=aspectColors[FRONT][4]||
		aspectColors[BACK][6]!=aspectColors[BACK][4]||
		aspectColors[BACK][8]!=aspectColors[BACK][4]){
			return false;
	}

	return true;
}
CString RestoreTopCorner(void)
{
	memset(cmdString,0,COMMANDLEN);
	cmdStrPtr=0;
	//TOP FRONT:RF'R'F twice
	//TOP RIGHT:F'RFR' twice
	//ASSERT(IsTopCornerBack());
	if (!IsTopCornerRestored()){
		//find a start corner
		for (int i=0;i<4;i++){
			if (aspectColors[UP][8]!=aspectColors[UP][4]){
				break;
			}
			_y();
		}
		int testCount=0;
		while(!IsTopCornerRestored()){
			testCount++;
			if (testCount>12){
				MessageBox(NULL,"bug merged in function:RestoreTopCorner","error",MB_OK);
				CString filename="bug/RestoreTopCorner.ml";
				CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
				fileout.Write(aspectColors,sizeof(aspectColors));
				fileout.Close();
				exit(-1);
			}
			if (aspectColors[UP][8]!=aspectColors[UP][4]){
				if (aspectColors[FRONT][8]==aspectColors[UP][4]){
					char* formula="RF'R'FRF'R'F";
					Executor(formula);
					strcpy(cmdString+cmdStrPtr,formula);
					cmdStrPtr+=strlen(formula);
				}else {
					char* formula="F'RFR'F'RFR'";
					Executor(formula);
					strcpy(cmdString+cmdStrPtr,formula);
					cmdStrPtr+=strlen(formula);
				}
			}else{
				_U();
			}
		}

		//last step to restore
		if (aspectColors[FRONT][7]!=aspectColors[FRONT][4]){
			if (aspectColors[BACK][7]!=aspectColors[FRONT][4]){
				_U2();
			}else if (aspectColors[LEFT][5]!=aspectColors[FRONT][4]){
				_Ur();
			}else if (aspectColors[RIGHT][5]!=aspectColors[FRONT][4]){
				_U();
			}

		}else{
			//bingo
		}

	}
	return CString(cmdString);
}
//get command string which can restore the state before 
//execution of the parameter string
CString UndoCmdString(const char* cmd)
{
	CString undoCmd;
	while(*cmd){
		switch(*cmd){
			case ' ':
			case '(':
			case ')':
				break;
			case '#':				
				do{
					cmd++;
				}while(*cmd!='#'&&*cmd);
				break;
			case 'F':
			case 'B':
			case 'L':
			case 'R':
			case 'U':
			case 'D':
			case 'x':
			case 'y':
			case 'z':
			case 'u':
			case 'r':
			case 'f':
			case 'd':
			case 'l':
			case 'b':
			case 'E':
			case 'M':
			case 'S':
				undoCmd.Insert(0,*cmd);
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2						
						undoCmd.Insert(1,'2');
						cmd++;
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					undoCmd.Insert(1,'2');
					cmd++;
				}else{
					undoCmd.Insert(1,'\'');
				}
				break;
			default:
				break;					
		}
		cmd++;
	}


	return undoCmd;
}
//calculate how many steps does the restoration takes
int CountSteps(const char* cmd)
{
	//method:
	int steps=0;
	while(*cmd){
		switch(*cmd){
			case ' ':
			case '(':
			case ')':
				break;
			case '#':				
				do{
					cmd++;
				}while(*cmd!='#'&&*cmd);
				break;
			case 'F':
			case 'B':
			case 'L':
			case 'R':
			case 'U':
			case 'D':
				/*case 'x'://do not counts
				case 'y':
				case 'z':*/
			case 'u':
			case 'r':
			case 'f':
			case 'd':
			case 'l':
			case 'b':
			case 'E':
			case 'M':
			case 'S':
				steps++;
				if (*(cmd+1)=='\''){
					if (*(cmd+2)=='2'){//E'2==E2						
						//steps++;
						cmd++;
					}
					cmd++;
				}else if (*(cmd+1)=='2'){
					//steps++;
					cmd++;
				}
				break;
			default:
				break;					
		}
		cmd++;
	}
	return steps;
}
CString MethodFewerFormula()
{
	CString cmd;
	cmd=F2L();
	cmd+="#\r\nBuil Cross On Top Aspect:\r\n\t#";
	cmd+=BuildTopCross();
	cmd+="#\r\nMatch Top Cross:\r\n\t#";
	cmd+=MatchTopCross();
	cmd+="#\r\nPut Back Top Corners:\r\n\t#";
	cmd+=PutBackTopCorner();
	cmd+="#\r\nRestore Top Corners:\r\n\t#";
	cmd+=RestoreTopCorner();

	int len=CountSteps(cmd.GetBuffer());
	CString str;
	str.Format("#\r\n\r\nStep Number:\r\n\t%d#",len);
	cmd+=str;
	//the view is not updated,and we should undo all the operations 
	//during the steps above
	CString undo=UndoCmdString(cmd.GetBuffer(cmd.GetLength()));
	Executor(undo.GetBuffer(undo.GetLength()));

	return cmd;
}
///////////////////////////////////////////////////
CMagicCube::CMagicCube(void)
{	
	//PRotateColorTable pRotateColor[3][3][2]={
	//	//x from negative to positive,i.e. from left to right
	//	{{&CMagicCube::rotateXLeftClockwise,&CMagicCube::rotateXLeftAnticlockwise},
	//	{&CMagicCube::rotateXMiddleClockwise,&CMagicCube::rotateXMiddleAnticlockwise},
	//	{&CMagicCube::rotateXRightClockwise,&CMagicCube::rotateXRightAnticlockwise}},
	//	//y
	//	{{&CMagicCube::rotateYDownClockwise,&CMagicCube::rotateYDownAnticlockwise},
	//	{&CMagicCube::rotateYMiddleClockwise,&CMagicCube::rotateYMiddleAnticlockwise},
	//	{&CMagicCube::rotateYUpClockwise,&CMagicCube::rotateYUpAnticlockwise}},
	//	//z
	//	{{&CMagicCube::rotateZBackClockwise,&CMagicCube::rotateZBackAnticlockwise},
	//	{&CMagicCube::rotateZMiddleClockwise,&CMagicCube::rotateZMiddleAnticlockwise},
	//	{&CMagicCube::rotateZFrontClockwise,&CMagicCube::rotateZFrontAnticlockwise}},
	//};
	//memcpy(pRotateColorTable,pRotateColor,sizeof(pRotateColor));
	//
	//PDrawBlock pDrawBlocksTmp[3][3]={
	//	{&CMagicCube::drawXLeft,&CMagicCube::drawXMiddle,&CMagicCube::drawXRight},
	//	{&CMagicCube::drawYDown,&CMagicCube::drawYMiddle,&CMagicCube::drawYUp},
	//	{&CMagicCube::drawZBack,&CMagicCube::drawZMiddle,&CMagicCube::drawZFront}
	//};
	//memcpy(pDrawBlocks,pDrawBlocksTmp,sizeof(pDrawBlocksTmp));

	////x
	//pRotateColorTable[0][0][0]=&CMagicCube::rotateXLeftClockwise;
	//pRotateColorTable[0][0][1]=&CMagicCube::rotateXLeftAnticlockwise;
	//pRotateColorTable[0][1][0]=&CMagicCube::rotateXMiddleClockwise;
	//pRotateColorTable[0][1][1]=&CMagicCube::rotateXMiddleAnticlockwise;
	//pRotateColorTable[0][2][0]=&CMagicCube::rotateXRightClockwise;
	//pRotateColorTable[0][2][1]=&CMagicCube::rotateXRightAnticlockwise;
	////y
	//pRotateColorTable[1][0][0]=&CMagicCube::rotateYDownClockwise;
	//pRotateColorTable[1][0][1]=&CMagicCube::rotateYDownAnticlockwise;
	//pRotateColorTable[1][1][0]=&CMagicCube::rotateYMiddleClockwise;
	//pRotateColorTable[1][1][1]=&CMagicCube::rotateYMiddleAnticlockwise;
	//pRotateColorTable[1][2][0]=&CMagicCube::rotateYUpClockwise;
	//pRotateColorTable[1][2][1]=&CMagicCube::rotateYUpAnticlockwise;
	////z
	//pRotateColorTable[2][0][0]=&CMagicCube::rotateZBackClockwise;
	//pRotateColorTable[2][0][1]=&CMagicCube::rotateZBackAnticlockwise;
	//pRotateColorTable[2][1][0]=&CMagicCube::rotateZMiddleClockwise;
	//pRotateColorTable[2][1][1]=&CMagicCube::rotateZMiddleAnticlockwise;
	//pRotateColorTable[2][2][0]=&CMagicCube::rotateZFrontClockwise;
	//pRotateColorTable[2][2][1]=&CMagicCube::rotateZFrontAnticlockwise;
	

	/*pDrawBlocks[0][0]=&CMagicCube::drawXLeft;
	pDrawBlocks[0][1]=&CMagicCube::drawXMiddle;	
	pDrawBlocks[0][2]=&CMagicCube::drawXRight;
	pDrawBlocks[1][0]=&CMagicCube::drawYDown;
	pDrawBlocks[1][1]=&CMagicCube::drawYMiddle;
	pDrawBlocks[1][2]=&CMagicCube::drawYUp;
	pDrawBlocks[2][0]=&CMagicCube::drawZBack;
	pDrawBlocks[2][1]=&CMagicCube::drawZMiddle;
	pDrawBlocks[2][2]=&CMagicCube::drawZFront;*/
}

CMagicCube::~CMagicCube(void)
{
}

void CMagicCube::initialize()
{
	memcpy(aspectColors,aspectColor_org,sizeof(aspectColor_org));
	rotateInfo=RotateInfo();
}

//rotate color table according to current rotateInfo
void CMagicCube::rotateColor()
{
	switch (rotateInfo.type){
		case 'F':
			if (rotateInfo.reversed){
				Fr();
			}else {
				F();
			}
			break;
		case 'B':
			if (rotateInfo.reversed){
				Br();
			}else {
				B();
			}
			break;
		case 'L':
			if (rotateInfo.reversed){
				Lr();
			}else {
				L();
			}
			break;
		case 'R':
			if (rotateInfo.reversed){
				Rr();
			}else {
				R();
			}
			break;
		case 'U':
			if (rotateInfo.reversed){
				Ur();
			}else {
				U();
			}
			break;
		case 'D':
			if (rotateInfo.reversed){
				Dr();
			}else {
				D();
			}
			break;
		case 'x':
			if (rotateInfo.reversed){
				xr();
			}else {
				x();
			}
			break;
		case 'y':
			if (rotateInfo.reversed){
				yr();
			}else {
				y();
			}
			break;
		case 'z':
			if (rotateInfo.reversed){
				zr();
			}else {
				z();
			}
			break;
		case 'u':
			if (rotateInfo.reversed){
				ur();
			}else {
				u();
			}
			break;
		case 'r':
			if (rotateInfo.reversed){
				rr();
			}else {
				r();
			}
			break;
		case 'f':
			if (rotateInfo.reversed){
				fr();
			}else {
				f();
			}
			break;
		case 'd':
			if (rotateInfo.reversed){
				dr();
			}else {
				d();
			}
			break;
		case 'l':
			if (rotateInfo.reversed){
				lr();
			}else {
				l();
			}
			break;
		case 'b':
			if (rotateInfo.reversed){
				br();
			}else {
				b();
			}
			break;
		case 'E':
			if (rotateInfo.reversed){
				Er();
			}else {
				E();
			}
			break;
		case 'M':
			if (rotateInfo.reversed){
				Mr();
			}else {
				M();
			}
			break;
		case 'S':
			if (rotateInfo.reversed){
				Sr();
			}else {
				S();
			}
			break;
		default:
			break;
	}
}

void CMagicCube::display()
{	
	static float rotateVect[3][2][3]={
		{{1,0,0},{-1,0,0}},{{0,1,0},{0,-1,0}},{{0,0,1},{0,0,-1}}
	};
	Axis axis;
	int direct;
	switch (rotateInfo.type){
		case 'F':
			axis=Z;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			drawZBack();
			drawZMiddle();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawZFront();
			glPopMatrix();
			break;
		case 'B':
			axis=Z;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}					
			drawZMiddle();
			drawZFront();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawZBack();
			glPopMatrix();
			break;
		case 'L':
			axis=X;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}
			drawXMiddle();
			drawXRight();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawXLeft();
			glPopMatrix();
			break;
		case 'R':
			axis=X;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			drawXMiddle();
			drawXLeft();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawXRight();
			glPopMatrix();
			break;
		case 'U':
			axis=Y;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			drawYMiddle();
			drawYDown();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawYUp();
			glPopMatrix();
			break;
		case 'D':
			axis=Y;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}
			drawYMiddle();
			drawYUp();
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawYDown();
			glPopMatrix();
			break;
		case 'x':
			axis=X;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawXLeft();
			drawXMiddle();
			drawXRight();
			glPopMatrix();
			break;
		case 'y':
			axis=Y;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawYDown();
			drawYMiddle();
			drawYUp();
			glPopMatrix();
			break;
		case 'z':
			axis=Z;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);
			drawZBack();
			drawZMiddle();
			drawZFront();
			glPopMatrix();
			break;
		case 'u':
			axis=Y;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawYMiddle();
			drawYUp();
			glPopMatrix();
			drawYDown();
			break;
		case 'r':
			axis=X;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawXMiddle();
			drawXRight();
			glPopMatrix();
			drawXLeft();
			break;
		case 'f':
			axis=Z;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawZMiddle();
			drawZFront();
			glPopMatrix();
			drawZBack();
			break;
		case 'd':
			axis=Y;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawYMiddle();
			drawYDown();
			glPopMatrix();
			drawYUp();
			break;
		case 'l':
			axis=X;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawXMiddle();
			drawXLeft();
			glPopMatrix();
			drawXRight();
			break;
		case 'b':
			axis=Z;
			if (rotateInfo.reversed){
				direct=1;
			}else {
				direct=0;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawZMiddle();
			drawZBack();
			glPopMatrix();
			drawZFront();
			break;
		case 'E':
			axis=Y;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawYMiddle();			
			glPopMatrix();
			drawYDown();
			drawYUp();
			break;
		case 'M':
			axis=X;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawXMiddle();
			glPopMatrix();
			drawXRight();
			drawXLeft();
			break;
		case 'S':
			axis=Z;
			if (rotateInfo.reversed){
				direct=0;
			}else {
				direct=1;
			}
			glPushMatrix();
			glRotatef(rotateInfo.angle,rotateVect[axis][direct][0],
				rotateVect[axis][direct][1],rotateVect[axis][direct][2]);			
			drawZMiddle();
			glPopMatrix();
			drawZFront();
			drawZBack();
			break;
		default:
			drawZMiddle();
			drawZFront();
			drawZBack();
			break;
	}
}

CString CMagicCube::restore()
{
	return MethodFewerFormula();
}
//void CMagicCube::save(char* filename)
//{
//	fstream fout(filename,ios::out);
//	fout.write((char*)aspectColors,sizeof(aspectColors));
//	fout.close();
//}
//void CMagicCube::open(char* filename)
//{
//	fstream fin(filename,ios::in);
//	fin.read((char*)aspectColors,sizeof(aspectColors));
//	fin.close();
//}
char* CMagicCube::getColorsPtr()
{
	return (char*)aspectColors;
}