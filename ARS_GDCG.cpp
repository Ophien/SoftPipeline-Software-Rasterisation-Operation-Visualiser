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

#include "ARS_GDCG.h"

namespace ARS_ConsoleHandler{
#if WIN32
	//---------------------------DEFINIÇÕES BÁSICAS--------------------------
	HANDLE console; //ARS_COMMENT:pega handler do console atual padrão
	CONSOLE_SCREEN_BUFFER_INFO defaultConsoleInfo;
	//-----------------------------------------------------------------------
	BOOL setDefaultConsoleAtt(){
		return SetConsoleTextAttribute(console, defaultConsoleInfo.wAttributes);
	}
	//-----------------------------------------------------------------------
	BOOL getDefaultConsoleAtt(){
		return GetConsoleScreenBufferInfo(console, &defaultConsoleInfo);	
	}
	//-----------------------------------------------------------------------
	int getFinalColor(int background, int foreground){
		return 16*background + foreground; //ARS_COMMENT:shift de 16
	}
	//-----------------------------------------------------------------------
	BOOL setColor(int colorCode){
		return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
	}
	//-----------------------------------------------------------------------
	void ARS_ConsoleHandlerInit(){
		//ARS_COMMENT:var init
		console = GetStdHandle(STD_OUTPUT_HANDLE);

		//ARS_COMMENT:default calls
		getDefaultConsoleAtt();
	}
#else
	//ARS_TODO::definições para linux
#endif
};

namespace ARS_Math{
	ARS_ABasis::ARS_ABasis(void){
		this->dimension = 0;
		this->cols      = 0;
		this->lines     = 0;
	}
	//-----------------------------------------------------------------------
	ARS_ABasis::ARS_ABasis(int dim,
		int width,
		int height){
			this->dimension = dim;
			this->cols      = width;
			this->lines     = height;
	}
	//-----------------------------------------------------------------------
	ARS_ABasis::~ARS_ABasis(void){
	}
	//-----------------------------------------------------------------------
	int ARS_ABasis::getlines(){
		return lines;
	}
	//-----------------------------------------------------------------------
	int ARS_ABasis::getcols(){
		return cols;
	}
	//-----------------------------------------------------------------------
	int ARS_ABasis::getDimesion(){
		return dimension;
	}
};

namespace ARS_Rasterization{
	void calcBaricentric(
		int x,                  //ARS_COMMENT:coordenada no plano projetado
		int y,					//ARS_COMMENT:coordenada no plano projetado
		ARS_Math::Triangle<float> triangle,
		float& lambdaA, 
		float& lambdaB, 
		float& lambdaC){
			lambdaA = ((triangle.B.y - triangle.C.y)*((float)x - triangle.C.x) + 
				(triangle.C.x - triangle.B.x)*((float)y - triangle.C.y))/
				((triangle.B.y - triangle.C.y)*(triangle.A.x - triangle.C.x)   + 
				(triangle.C.x - triangle.B.x)*(triangle.A.y - triangle.C.y));

			lambdaB = ((triangle.C.y - triangle.A.y)*((float)x - triangle.C.x) + 
				(triangle.A.x - triangle.C.x)*((float)y - triangle.C.y))/
				((triangle.B.y - triangle.C.y)*(triangle.A.x - triangle.C.x)   + 
				(triangle.C.x - triangle.B.x)*(triangle.A.y - triangle.C.y));

			lambdaC = 1 - lambdaA - lambdaB;
	}

	void ARS_RastTriangle(
		ARS_GDCG::ARS_FrameBuffer& buffer, 
		ARS_Math::Triangle<float>& triangle, 
		ARS_Math::Triangle<float>& tColor){

			int minX = (int)min(triangle.A.x, min(triangle.B.x, triangle.C.x));
			int minY = (int)min(triangle.A.y, min(triangle.B.y, triangle.C.y));
			int maxX = (int)max(triangle.A.x, max(triangle.B.x, triangle.C.x));
			int maxY = (int)max(triangle.A.y, max(triangle.B.y, triangle.C.y));

			minX = max(minX, 0);
			minY = max(minY, 0);
			maxX = min(maxX, buffer.width  - 1);
			maxY = min(maxY, buffer.height - 1);

			for(int y = minY; y <= maxY; y++){		

				//ARS_Comment:Poda
				if(minY < 0 || y > buffer.height)
					continue;

				for(int x = minX; x <= maxX; x++){			
					float lambdaA=0, lambdaB=0, lambdaC=0,
						bariX  =0 , bariY =0 , bariZ =0;

					//ARS_COMMENT:gerar coord. baricentrica de cada triangulo e ver se pode setar ou não o pixel interno
					calcBaricentric(x, y, 
						triangle,
						lambdaA,
						lambdaB,
						lambdaC);

					//ARS_COMMENT:poda
					if(minX < 0 || x > buffer.width)
						continue;

					bool insideTriangle = false;					

					//ARS_COMMENT:testa pixel, e configura wireframe ou não
					if(ARS_GDCG::wireframe){
						//if(checkPixel(bariX, bariY)){
						if(( lambdaA >= - 0.01 && lambdaA <= 0.01) || 
							(lambdaB >= - 0.01 && lambdaB <= 0.01) ||
							(lambdaC >= - 0.01 && lambdaC <= 0.01)){
								if(lambdaA <= 1 + epslon && lambdaB <= 1 + epslon && lambdaC <= 1 + epslon && 
									lambdaA >=   - epslon && lambdaB >=   - epslon && lambdaC >=   - epslon){
										insideTriangle = true;	
								}
						}
					}else{
						//if(checkPixel(bariX, bariY)){
						if(lambdaA <= 1 + epslon && lambdaB <= 1 + epslon && lambdaC <= 1 + epslon && 
							lambdaA >=   - epslon && lambdaB >=   - epslon && lambdaC >=   - epslon){
								insideTriangle = true;	
						}
					}

					//ARS_COMMENT:setar Z-buffer
					if(insideTriangle){
						if(ARS_GDCG::depthtest){
							bool ZBufferTest   = false;
							float* depthBuffer = (float*)buffer.depthData;
							int coordZBuffer   = y*buffer.width+x;

							bariZ = lambdaA*triangle.A.z + lambdaB*triangle.B.z + lambdaC*triangle.C.z;

							if(bariZ <= depthBuffer[coordZBuffer]){
								depthBuffer[coordZBuffer] = bariZ;
								ZBufferTest               = true;
							}				

							//ARS_COMMENT:fazer teste de Z-buffer
							if(ZBufferTest){
								//ARS_COMMENT:rasterizar pixel aqui
								float* colorBuffer = (float*)buffer.colorData;
								//TODO:mudar cor
								int currentColorPixel = (y * buffer.width + x)*3; // para dar o salto de 3 pixels;
								ARS_Math::Vec4<float> cFinal;

								if(ARS_GDCG::wireframe){
									cFinal.x = 1.0f;cFinal.y = 1.0f;cFinal.z = 1.0f;
								}else{
									//ARS_COMMENT:interpolação da cor dos vertices
									cFinal = tColor.A*lambdaA + tColor.B*lambdaB + tColor.C*lambdaC; 
								}

								colorBuffer[currentColorPixel  ] = cFinal.x;//.5;
								colorBuffer[currentColorPixel+1] = cFinal.y;//.5;
								colorBuffer[currentColorPixel+2] = cFinal.z;//.5;
							}//Fim ZBufferTest
						}else{
							//ARS_COMMENT:rasterizar pixel aqui
							float* colorBuffer = (float*)buffer.colorData;
							//TODO:mudar cor
							int currentColorPixel = (y * buffer.width + x)*3; // para dar o salto de 3 pixels;
							ARS_Math::Vec4<float> cFinal;

							if(ARS_GDCG::wireframe){
								cFinal.x = 1.0f;cFinal.y = 1.0f;cFinal.z = 1.0f;
							}else{
								//ARS_COMMENT:interpolação da cor dos vertices
								cFinal = tColor.A*lambdaA + tColor.B*lambdaB + tColor.C*lambdaC; 
							}

							colorBuffer[currentColorPixel  ] = cFinal.x;//.5;
							colorBuffer[currentColorPixel+1] = cFinal.y;//.5;
							colorBuffer[currentColorPixel+2] = cFinal.z;//.5;
						}//Fim else zbuffer
					}//Fim inside triangle
				}//Fim for
			}//Fim for
	}//Fim ARS_RastTriangle
};

namespace ARS_GDCG{
	//ARS_COMMENT:variaveis importantes
	ARS_ClearColor							  clearColor;
	ARS_Math::ARS_Mat<float> projection     = ARS_Math::ARS_Mat<float>(4, 4);
	ARS_Math::ARS_Mat<float> modelview		= ARS_Math::ARS_Mat<float>(4, 4);
	std::vector<ARS_Math::ARS_Mat<float>>   matStack;
	std::vector<ARS_Math::ARS_Mat<float>>   subMatStack;

	//ARS_COMMENT:triangle assembler
	std::vector<ARS_Math::Triangle<float>>  triangleList;
	std::vector<ARS_Math::Triangle<float>>  trianglesVertexColorList;
	std::vector<ARS_Math::Triangle<float>>  projectedTriangles;

	ARS_Math::ARS_Mat<float> currentTransform = ARS_Math::ARS_Mat<float>(4,4);

	float* vertexList;
	int    vertexCount;
	float* vertexColorList;
	int    colorCount;

	bool   dirtyVertexList = true;
	bool   dirtyModelView  = true;
	bool   faceCulling     = false;
	bool   rastBackFaces   = false;
	bool   wireframe       = false;
	bool   depthtest       = true;
	//ARS_COMMENT:apenas desenha pixels no framebuffer do OGL
	//---------------------------------
	void ARS_RenderQuad(){
		float vertex[]= {
			0,0,0, 1,0,0, 1,1,0,
			0,0,0, 0,1,0, 1,1,0,

			0,0,0, 0,0,1, 0,1,1,
			0,0,0, 0,1,0, 0,1,1,

			1,0,0, 1,1,1, 1,0,1,
			1,0,0, 1,1,0, 1,1,1,

			0,0,0, 0,0,1, 1,0,0,
			1,0,0, 0,0,1, 1,0,1,

			0,1,0, 1,1,0, 0,1,1,
			1,1,0, 0,1,1, 1,1,1,

			0,1,1, 1,1,1, 1,0,1,
			0,0,1, 0,1,1, 1,0,1};

			float color [] = {
				1,0,0, 0,1,0, 1,0,1,
				1,0,0, 0,0,1, 1,0,1,

				1,0,0, 1,0,1, 0,1,0,
				1,0,0, 0,0,1, 0,1,0,

				0,1,0, 1,0,0, 0,0,1,
				0,1,0, 1,0,1, 1,0,0,

				1,0,0, 1,0,1, 0,1,0,
				0,1,0, 1,0,1, 0,0,1,

				0,0,1, 1,0,1, 0,1,0,
				1,0,1, 0,1,0, 1,0,0,

				0,1,0, 1,0,0, 0,0,1,
				1,0,1, 0,1,0, 0,0,1};

				ARS_SetVertexBuffer(vertex, 108);
				ARS_SetColorBuffer (color , 108);
	}
	//-----------------------------------------------------------------------
	void ARS_RenderToFrameBuffer(ARS_FrameBuffer& buffer){
		//----------------ARS_COMMENT:meu pipeline----------------
		//ARS_COMMENT:montador de triangulos
		if(dirtyVertexList)
		{
			dirtyVertexList = false;
			triangleList.clear();
			trianglesVertexColorList.clear();

			ARS_TriangleAssembler(vertexList, vertexColorList, triangleList, trianglesVertexColorList);
		}

		//ARS_COMMENT:verificar lista de triangulos
		if(triangleList.size() == 0)
			return;

		//ARS_COMMENT:aplica transformações e projeta cada triangulo
		ARS_Math::Triangle<float> transformedTriangle;

		if(dirtyModelView){
			dirtyModelView = false;
			projectedTriangles.clear();

			currentTransform = projection * modelview;

			//ARS_COMMENT:configurando transformação compacta
			if(matStack.size()>0){
				currentTransform = currentTransform * matStack.back();
			}

			for(unsigned int i = 0; i < triangleList.size(); i++){

				transformedTriangle = triangleList.at(i);

				transformedTriangle = currentTransform * transformedTriangle;

				if(subMatStack.size()>0){
					//for(int i = subMatStack.size() - 1; i >= 0; i--){
					//	transformedTriangle = subMatStack[i] * transformedTriangle;
					//}
					for(unsigned int i = 0; i < subMatStack.size(); i++){
						transformedTriangle = subMatStack[i] * transformedTriangle;
					}
				}

				projectedTriangles.push_back(transformedTriangle);
			}//Fim for triangulos

			subMatStack.clear();
		}//Fim if dirtyModelView

		//ARS_COMMENT:rasteriza todos os triangulos
		for(unsigned int i = 0; i < projectedTriangles.size(); i++){
			//ARS_COMMENT, se CW rasteriza, senão CCW não processa
			if(faceCulling){
				if(projectedTriangles[i].A.x > projectedTriangles[i].B.x){
					if(rastBackFaces){
						//ARS_TODO:otimizar isto aqui
						ARS_Math::Triangle<float> colorTri;

						colorTri.A.x = 0.5;colorTri.A.y = 0.5;colorTri.A.z = 0.5;
						colorTri.B.x = 0.5;colorTri.B.y = 0.5;colorTri.B.z = 0.5;
						colorTri.C.x = 0.5;colorTri.C.y = 0.5;colorTri.C.z = 0.5;

						ARS_Rasterization::ARS_RastTriangle(buffer, projectedTriangles[i], colorTri);
					}else{
						continue;
					}
				}
			}

			//ARS_COMMENT:rasterizar
			ARS_Rasterization::ARS_RastTriangle(buffer, projectedTriangles[i], trianglesVertexColorList[i]);
		}

		//ARS_COMMENT:calcular iluminação

		//ARS_COMMENT:setar pixelfinal
		//ARS_COMMENT:criar textura aqui e renderizar normal para evitar peso
		glDrawPixels(buffer.width, buffer.height, buffer.format, buffer.type, buffer.colorData);

		//ARS_COMMENT:limpa lista de dados necessarios para desenho de frame
	}
	//-----------------------------------------------------------------------
	void ARS_TriangleAssembler  (
		float* vertexList,
		float* vertexColorList,
		std::vector<ARS_Math::Triangle<float>>& triangleList,
		std::vector<ARS_Math::Triangle<float>>& triangleVertexColorList){
			if(vertexCount < 9){
				return;
			}

			for(int i = 0; i < vertexCount; i+=9){
				//ARS_COMMENT:monta triangulo
				ARS_Math::Triangle<float> triangle;
				ARS_Math::Triangle<float> triangleColor;
				triangle.A.x = vertexList[i];
				triangle.A.y = vertexList[i+1];
				triangle.A.z = vertexList[i+2];
				triangle.A.w = 1;

				triangle.B.x = vertexList[i+3];
				triangle.B.y = vertexList[i+4];
				triangle.B.z = vertexList[i+5];
				triangle.B.w = 1;

				triangle.C.x = vertexList[i+6];
				triangle.C.y = vertexList[i+7];
				triangle.C.z = vertexList[i+8];
				triangle.C.w = 1;


				//ARS_COMMENT:associa cor
				//ARS_COMMENT:zerar cor inicial para evitar erros
				triangleColor.A.x = 0;
				triangleColor.A.y = 0;
				triangleColor.A.z = 0;
				triangleColor.B.x = 0;
				triangleColor.B.y = 0;
				triangleColor.B.z = 0;
				triangleColor.C.x = 0;
				triangleColor.C.y = 0;
				triangleColor.C.z = 0;

				if(i < colorCount){
					int a, b, c, d, e, f, g, h, k;
					a = i; b = i+1; c = i+2; d = i+3; e = i+4; f = i+5; g = i+6; h = i+7; k = i+8;

					triangleColor.A.x = vertexColorList[a];
					if(b < colorCount)
						triangleColor.A.y = vertexColorList[b];
					if(c < colorCount)
						triangleColor.A.z = vertexColorList[c];
					if(d < colorCount)
						triangleColor.B.x = vertexColorList[d];
					if(e < colorCount)
						triangleColor.B.y = vertexColorList[e];
					if(f < colorCount)
						triangleColor.B.z = vertexColorList[f];
					if(g < colorCount)
						triangleColor.C.x = vertexColorList[g];
					if(h < colorCount)
						triangleColor.C.y = vertexColorList[h];
					if(k < colorCount)
						triangleColor.C.z = vertexColorList[k];
				}//Fim if
				triangleList		   .push_back(triangle);
				triangleVertexColorList.push_back(triangleColor);
			}//Fim for
	}
	//-----------------------------------------------------------------------
	void ARS_SetVertexBuffer    (float vertexListParam[], int size){
		delete vertexList;
		vertexList = new float[size];

		for(int i = 0; i < size; i++)
			vertexList[i] = vertexListParam[i];

		vertexCount = size;

		//ARS_COMMENT:configurar dirty aqui
		dirtyVertexList = true;
	}
	//-----------------------------------------------------------------------
	void ARS_SetColorBuffer     (float colorList[], int size){
		delete vertexColorList;
		vertexColorList = new float[size];

		for(int i = 0; i < size; i++)
			vertexColorList[i] = colorList[i];

		colorCount = size;

		//ARS_COMMENT:configurar dirty aqui
		dirtyVertexList = true;
	}
	//-----------------------------------------------------------------------
	void ARS_SetPixel(int x, int y, float r, float g, float b, ARS_FrameBuffer& buffer){
		int coord            = y*buffer.width + x;
		float* pixelBuffer   = (float*)buffer.colorData;
		pixelBuffer[coord]   = r;
		pixelBuffer[coord+1] = g;
		pixelBuffer[coord+2] = b;
	}
	//-----------------------------------------------------------------------
	void ARS_SetDepthData       (int x, int y, float d, ARS_FrameBuffer& buffer){
		int coord          = y*buffer.width + x;
		float* depthBuffer = (float*)buffer.depthData;
		depthBuffer[coord] = d;
	}
	//-----------------------------------------------------------------------
	void ARS_Clear(ARS_FrameBuffer& buffer){
		//ARS_COMMENT:limpa color buffer
		//#pragma omp parallel for
		for(int i = 0; i < buffer.width*buffer.height*3; i+=3){
			float* pixelBuffer = (float*)buffer.colorData;
			pixelBuffer[i]     = clearColor.r;
			pixelBuffer[i+1]   = clearColor.g;
			pixelBuffer[i+2]   = clearColor.b;

			float* depthBuffer = (float*)buffer.depthData;
			depthBuffer[i/3]   = 100000;
		}

		//ARS_COMMENT:limpa depth buffer
		/*for(int i = 0; i < buffer.width*buffer.height; i+=1){

		}*/
	}
	//-----------------------------------------------------------------------
	void ARS_SetViewPort(int width, int height, ARS_FrameBuffer& buffer){
		buffer.width  = width;
		buffer.height = height;

		delete [] buffer.colorData;
		buffer.colorData = new float[buffer.width*buffer.height*3];

		delete [] buffer.depthData;
		buffer.depthData = new float[buffer.width*buffer.height];
	}
	//-----------------------------------------------------------------------
	void ARS_SetClearColor(float r, float g, float b){
		clearColor.r = r;
		clearColor.g = g;
		clearColor.b = b;
	}
	//-----------------------------------------------------------------------
	void ARS_SetPerspective(float nearPlane, float farPlane){
		projection.setZero();
		projection.setElement(0,0, 1							 );
		projection.setElement(1,1, 1							 );
		projection.setElement(2,2, (nearPlane+farPlane)/nearPlane);
		projection.setElement(2,3, -1*farPlane					 );
		projection.setElement(3,2, 1/nearPlane					 );
	}
	//-----------------------------------------------------------------------
	void ARS_SetOrtho(){
		projection.loadIdendity();
	}
	//-----------------------------------------------------------------------	
	void ARS_PushMatrix         (){
		ARS_Math::ARS_Mat<float> newMat = ARS_Math::ARS_Mat<float>(4,4);
		matStack.push_back(newMat);
	}
	//-----------------------------------------------------------------------
	void ARS_PopMatrix          (){
		matStack.pop_back();
	}
	//-----------------------------------------------------------------------
	void ARS_LoadIdentity(){
		dirtyModelView = true;

		if(matStack.size() == 0){
			modelview.loadIdendity();
		}else{
			matStack.back().loadIdendity();
		}
	}
	//-----------------------------------------------------------------------
	void ARS_InitGDCG(){
		//ARS_COMMENT:apenas configura matrizes iniciais
		ARS_SetOrtho();
		ARS_LoadIdentity();
	}
	//-----------------------------------------------------------------------	
	void ARS_Translate          (float x, float y, float z){
		dirtyModelView = true;

		ARS_Math::ARS_Mat<float> mat = ARS_Math::ARS_Mat<float>(4,4);
		mat.loadIdendity();

		mat.setElement(0,3,x);
		mat.setElement(1,3,y);
		mat.setElement(2,3,z);

		subMatStack.push_back(mat);
	}
	//-----------------------------------------------------------------------
	void ARS_Scale              (float x, float y, float z){
		dirtyModelView = true;

		dirtyModelView = true;

		ARS_Math::ARS_Mat<float> mat = ARS_Math::ARS_Mat<float>(4,4);
		mat.loadIdendity();

		mat.setElement(0,0,x);
		mat.setElement(1,1,y);
		mat.setElement(2,2,z);

		subMatStack.push_back(mat);
	}
	//-----------------------------------------------------------------------
	void ARS_Rotate             (float angleX, float angleY, float angleZ){
		dirtyModelView = true;

		//ARS_COMMENT:angulos de euler compactados
		//			float m1, m2, m3, m4, m5, m6, m7, m8, m9;
		float cosAngleX, cosAngleY, cosAngleZ, sinAngleX, sinAngleY, sinAngleZ;
		cosAngleX = cos(angleX);cosAngleY = cos(angleY);cosAngleZ = cos(angleZ);
		sinAngleX = sin(angleX);sinAngleY = sin(angleY);sinAngleZ = sin(angleZ);

		/*m1 = cosAngleY*cosAngleZ;
		m2 = cosAngleX*cosAngleZ+sinAngleX*sinAngleY*sinAngleZ;
		m3 = sinAngleX*sinAngleZ-cosAngleX*sinAngleY*cosAngleZ;
		m4 = -cosAngleY*sinAngleZ;
		m5 = cosAngleX*cosAngleZ - sinAngleX*sinAngleY*sinAngleZ;
		m6 = sinAngleX*cosAngleZ+cosAngleX*sinAngleY*sinAngleZ;
		m7 = sinAngleY;
		m8 = -sinAngleX*cosAngleY;
		m9 = cosAngleX*cosAngleY;
		*/

		ARS_Math::ARS_Mat<float> rotationX = ARS_Math::ARS_Mat<float>(4,4);
		ARS_Math::ARS_Mat<float> rotationY = ARS_Math::ARS_Mat<float>(4,4);
		ARS_Math::ARS_Mat<float> rotationZ = ARS_Math::ARS_Mat<float>(4,4);
		//rotation.loadIdendity();

		rotationX.loadIdendity();
		rotationX.setElement(1,1,cosAngleX);
		rotationX.setElement(1,2,sinAngleX);
		rotationX.setElement(2,1,-sinAngleX);
		rotationX.setElement(2,2,cosAngleX);

		rotationY.loadIdendity();
		rotationY.setElement(0,0,cosAngleY);
		rotationY.setElement(0,2,-sinAngleY);
		rotationY.setElement(2,0,sinAngleY);
		rotationY.setElement(2,2,cosAngleY);

		rotationZ.loadIdendity();
		rotationZ.setElement(0,0,cosAngleZ);
		rotationZ.setElement(0,1,sinAngleZ);
		rotationZ.setElement(1,0,-sinAngleZ);
		rotationZ.setElement(1,1,cosAngleZ);

		/*rotationX.setElement(0,0,m1);
		rotationX.setElement(0,1,m2);
		rotationX.setElement(0,2,m3);
		rotationX.setElement(0,3,0);
		rotationX.setElement(1,0,m4);
		rotationX.setElement(1,1,m5);
		rotationX.setElement(1,2,m6);
		rotationX.setElement(1,3,0);
		rotationX.setElement(2,0,m7);
		rotationX.setElement(2,1,m8);
		rotationX.setElement(2,2,m9);
		rotationX.setElement(2,3,0);
		rotationX.setElement(3,0,0);
		rotationX.setElement(3,1,0);
		rotationX.setElement(3,2,0);
		rotationX.setElement(3,3,1);*/

		ARS_Math::ARS_Mat<float> mat = ARS_Math::ARS_Mat<float>(4,4);
		mat.loadIdendity();

		mat = rotationZ * rotationY * rotationX;
		subMatStack.push_back(mat);
	}
	//-----------------------------------------------------------------------
	void ARS_Enable(int code){
		switch(code){
		case ARS_FACECULL:
			faceCulling   = true;
			break;
		case ARS_BACKFACES:
			rastBackFaces = true;
			break;
		case ARS_WIREFRAME:
			wireframe     = true;
			break;
		case ARS_DEPTHTEST:
			depthtest     = true;
			break;
		}
	}
	//-----------------------------------------------------------------------
	void ARS_Disable(int code){
		switch(code){
		case ARS_FACECULL:
			faceCulling   = false;
			break;
		case ARS_BACKFACES:
			rastBackFaces = false;
			break;
		case ARS_WIREFRAME:
			wireframe     = false;
			break;
		case ARS_DEPTHTEST:
			depthtest     = false;
			break;
		}
	}
	//-----------------------------------------------------------------------
};
