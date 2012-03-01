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

#include "StdAfx.h"
#include "OpenGL.h"

COpenGL::COpenGL(void):eyePos(4,4.5,5)
{
}

COpenGL::~COpenGL(void)
{
	wglMakeCurrent(hDC, NULL);
	wglDeleteContext(hRC);
}

void COpenGL::Init(void)
{
	glClearColor(0,0,0,1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool COpenGL::SetupPixelFormat(HDC hDC0)
{
	int nPixelFormat;					  
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    
		1,                                
		PFD_DRAW_TO_WINDOW |              
		PFD_SUPPORT_OPENGL |              
		PFD_DOUBLEBUFFER,                 
		PFD_TYPE_RGBA,                    
		24,                               
		0, 0, 0, 0, 0, 0,                 
		0,                                
		0,                                
		0,                                
		0, 0, 0, 0,                       
		32,                               
		0,                                
		0,                                
		PFD_MAIN_PLANE,                   
		0,                                
		0, 0, 0                           
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ MessageBox(NULL,"can not find proper mode","Error",MB_OK|MB_ICONEXCLAMATION);
	return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);
	hRC = wglCreateContext(hDC);          
	wglMakeCurrent(hDC, hRC);             
	return TRUE;
}

void COpenGL::Reshape(int width,int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(GLfloat)width/(GLfloat)height,0.1,3000.0);
	glMatrixMode(GL_MODELVIEW);
}

void COpenGL::Render()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	

	glLoadIdentity();
	gluLookAt(eyePos.x,eyePos.y,eyePos.z,0,0,0,0,1,0);
		
	magicCube.display();

	glFlush();
	SwapBuffers(hDC);
}