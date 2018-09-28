/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//----------------------------------------------------------------
#include "ARS_GDCG.h"
//----------------------------------------------------------------
using namespace ARS_Math;
using namespace ARS_ConsoleHandler;
using namespace ARS_GDCG;
//----------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM); //ARS_COMMENT:trata eventos da janela
void EnableOpenGL		   (HWND hwnd, HDC*, HGLRC*);	 //ARS_COMMENT:configura e habilita OGL
void DisableOpenGL		   (HWND, HDC, HGLRC);			 //ARS_COMMENT:desativa e mata OGL
//----------------------------------------------------------------
typedef void (*ARS_Update)(float time);
typedef void (*ARS_Draw)  (float time);
typedef void (*ARS_WindowResize) (int, int);
//----------------------------------------------------------------
ARS_Update		 GLupdate;
ARS_Draw		 GLdraw;
ARS_Update		 ARSupdate;
ARS_Draw		 ARSdraw;
ARS_WindowResize resize;
ARS_WindowResize sizing;
//----------------------------------------------------------------
int windowWidth  = 512;
int windowHeight = 512;
//-------------------------------TEST ZONE------------------------
ARS_FrameBuffer* GlobalBuffer;
float* pixels;
int size = windowWidth*windowHeight;
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
//---------------------------------
void testFunction(){
	ARS_ConsoleHandlerInit();

	printf("Teste\n\n");

	ARS_Mat<int> myMat(1, 3,
					    1, 2, 1);

	ARS_Mat<int> myMatB(3, 1,
						 3,
						 1,
						 2);

	{
		ARS_Mat<int> myMatC(2, 2);
	
		myMatC = myMatB * myMat;

	//myMatC *= myMat;

		myMatC.print(0, FONT_C_I_RED);
	}

	getchar();
}
//---------------------------------
void testBufferInit(){
	//ARS_COMMENT:configura buffer do OGL
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
	}

	//ARS_COMMENT:configurando meu buffer de visualização
	{
		//ARS_COMMENT:rasterização esquerda para direita
		//            esquerda para cima
		//            
		//	 |
		//	 |------------>
		//	 |------------>
		//	 |---width*pixelFormat>
		//	 |______________________
		//for(int i=0;i<256*256*3;i+=1) {
		//	pixels[i] = 1;
		//
		GlobalBuffer = new ARS_FrameBuffer(windowWidth, windowHeight, GL_RGB, GL_FLOAT);
		ARS_SetClearColor(0.5f,0.5f,1.0f);
	}

	ARS_InitGDCG();
	//ARS_SetPerspective(0.00001, 10000);
}
//---------------------------------OGL_TEST
float theta = 0.0f;
float gama  = 0.0f;
float alpha = 0.0f;
void GLupdateTest(float time){
}
//---------------------------------OGL_TEST
void GLdrawTest(float time){
	glPushMatrix();
    glRotatef(theta, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

    glEnd();

    glPopMatrix();
}
//---------------------------------ARS_TEST
void ARSupdateTest(float time){
	 theta += 0.05f;
	 gama  += 0.025f;
	 alpha += 0.015f;
}
//---------------------------------ARS_TEST
void ARSdrawTest(float time){
	ARS_Clear(*GlobalBuffer);

	ARS_RenderQuad();

	ARS_PushMatrix();   //ARS_COMMENT:para não modificar a modelView
	ARS_LoadIdentity();
	ARS_Translate(-0.5, -0.5, -0.5);
	ARS_Rotate(gama, theta, alpha);	
	ARS_Scale(100,100,100);
	ARS_Translate(128, 128, 128);
	ARS_RenderToFrameBuffer(*GlobalBuffer);

	ARS_RenderQuad();

	ARS_PushMatrix();   //ARS_COMMENT:para não modificar a modelView
	ARS_LoadIdentity();
	ARS_Translate(-0.5, -0.5, -0.5);
	ARS_Rotate(alpha, gama, theta);	
	ARS_Scale(50,50,50);
	ARS_Translate(128, 100, 0);
	ARS_RenderToFrameBuffer(*GlobalBuffer);

	ARS_PushMatrix();   //ARS_COMMENT:para não modificar a modelView
	ARS_LoadIdentity();
	ARS_Translate(-0.5, -0.5, -0.5);
	ARS_Rotate(alpha, gama, theta);	
	ARS_Scale(100,100,3);
	ARS_Translate(300, 100, 0);
	ARS_RenderToFrameBuffer(*GlobalBuffer);

	ARS_Enable(ARS_WIREFRAME);
	ARS_PushMatrix();   //ARS_COMMENT:para não modificar a modelView
	ARS_LoadIdentity();
	ARS_Translate(-0.5, -0.5, -0.5);
	ARS_Rotate(0, theta, -theta);	
	ARS_Scale(300,300,300);
	ARS_Translate(300, 200, 500);
	ARS_RenderToFrameBuffer(*GlobalBuffer);
	ARS_Disable(ARS_WIREFRAME);

	ARS_PushMatrix();   //ARS_COMMENT:para não modificar a modelView
	ARS_LoadIdentity();
	ARS_Translate(-0.5, -0.5, -0.5);
	ARS_Rotate(theta, 0, theta);	
	ARS_Scale(15,15,15);
	ARS_Translate(300, 200, 500);
	ARS_RenderToFrameBuffer(*GlobalBuffer);
	ARS_Disable(ARS_WIREFRAME);

	ARS_PopMatrix();
}
//---------------------------------
void sisingEvent(int width, int height){
	windowWidth = width;
	windowWidth = height;
	//glViewport(0, 0, width, height);
	//ARS_SetViewPort(width, height, *GlobalBuffer);
}
//-------------------------------TEST ZONE------------------------
//----------------------------------------------------------------
//ARS_COMMENT:Trocar subsistema do linker para windows para linkar corretamente a chamada principal
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR	 lpCmdLine,
                   int		 nCmdShow)
{
    WNDCLASSEX wcex;
    HWND	   hwnd;
    HDC		   hDC;
    HGLRC	   hRC;
    MSG		   msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wcex.cbSize			= sizeof(WNDCLASSEX);
    wcex.style			= CS_OWNDC;
    wcex.lpfnWndProc	= WindowProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= "GLSample";
    wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);;
	
	//--TESTE--utilizado para testar ponteiros de função
	//-------------------------------TEST ZONE------------------------
	testBufferInit();

	GLupdate  = GLupdateTest;
	GLdraw    = GLdrawTest;
	ARSupdate = ARSupdateTest;
	ARSdraw   = ARSdrawTest;
	resize    = sisingEvent;
	//sizing    = sisingEvent;
	//-------------------------------TEST ZONE------------------------

    if (!RegisterClassEx(&wcex))
        return 0;

    //ARS_COMMENT::apenas cria handler da janela com as devidas propriedades
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "ARS_GDCG",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          windowWidth,
                          windowHeight,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

	//ARS_COMMENT::ativa opengl
    EnableOpenGL(hwnd, &hDC, &hRC);

    //ARS_COMMENT::main loop do programa, trata mensagens da janela do windows
    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
			//ARS_COMMENT:chamada padrão para cada frame
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//ARS_COMMENT:ARS_GDCG normal render pipeline
			{
				ARSupdate(0);
				ARSdraw(0);
			}

			//ARS_COMMENT:OGL default cicle
			{
				//GLupdate(0);
				//GLdraw(0);
				SwapBuffers(hDC);
			}

			//ARS_COMMENT:para não ficar muito rápido (POG)
			//Sleep (1);            
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);

    return msg.wParam;
}
//----------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int width;
    int height;

    switch (uMsg)
    {
		case WM_SIZE:
			width  = LOWORD(lParam);  // Macro to get the low-order word.
            height = HIWORD(lParam); // Macro to get the high-order word.
           
		   if(resize != 0x0)
            resize(width, height);
		break;

		//case WM_SIZING:
			//width = LOWORD(lParam);  // Macro to get the low-order word.
            //height = HIWORD(lParam); // Macro to get the high-order word.

           //if(sizing != 0x0)
           // sizing(width, height);	
		//break;

        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
//----------------------------------------------------------------
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}
//----------------------------------------------------------------
void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
//----------------------------------------------------------------
void ARS_SetUpdateFunction(ARS_Update func){
	ARSupdate = func;
}
//----------------------------------------------------------------
void ARS_SetDrawFunction(ARS_Update func){
	ARSdraw = func;
}
//----------------------------------------------------------------
void ARS_SetGLUpdateFunction(ARS_Update func){
	GLupdate = func;
}
//----------------------------------------------------------------
void ARS_SetGLDrawFunction(ARS_Update func){
	GLdraw = func;
}
