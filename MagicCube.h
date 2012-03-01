#pragma once
#include "StdAfx.h"
#include "utilities.h"

class CMagicCube
{
public:
	CMagicCube(void);
	~CMagicCube(void);

	void setRotateInfo(RotateInfo& info){rotateInfo=info;}
	void display(void);
	void initialize(void);
	void rotateColor(void);
	CString restore(void);

	/*void save(char* filename);
	void open(char* filename);*/

	char* getColorsPtr();
	
private:
		
	RotateInfo rotateInfo;

};
