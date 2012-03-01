/**********************************************************************
    
  OpenGL
  Release Date: 10/2/2010
  Copyright (C) 2010	Zhijie Lee
                        email: onezeros.lee@gmail.com 
                        web: http://blog.csdn.net/onezeros

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
**********************************************************************/

#pragma once
#include "MagicCube.h"

class COpenGL
{
public:
	COpenGL(void);
	~COpenGL(void);

	HDC hDC;
	HGLRC hRC;
	void Init(void);
	bool SetupPixelFormat(HDC);
	void Reshape(int width,int height);
	void Render(void);	
	
public:	
	CMagicCube magicCube;

	void setEyePos(float x,float y,float z){
		eyePos.x=x;
		eyePos.y=y;
		eyePos.z=z;
	};
	
private:
	GLPoint3f eyePos;
	
};
