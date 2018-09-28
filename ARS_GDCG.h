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

#pragma once

#include "ARS_Global.h"

#include <vector>

namespace ARS_ConsoleHandler{
#if WIN32
#define FONT_C_BLACK 0
#define FONT_C_BLUE  1
#define FONT_C_GREEN 2
#define FONT_C_CYAN 3
#define FONT_C_RED 4
#define FONT_C_MAGENTA 5
#define FONT_C_BROWN 6
#define FONT_C_WHITE 7
#define FONT_C_GRAY 8
#define FONT_C_I_BLUE 9
#define FONT_C_I_GREEN 10
#define FONT_C_I_CYAN 11
#define FONT_C_I_RED 12
#define FONT_C_I_MAGENTA 13
#define FONT_C_I_YELLOW 14
#define FONT_C_I_WHITE 15

	//ARS_COMMENT:basic bool opp, configura console para padrão
	BOOL setDefaultConsoleAtt();
	BOOL getDefaultConsoleAtt();
	BOOL setColor			 (int color);

	//ARS_COMMENT:basic int opp, combinar código de cores
	int getFinalColor(int background, int foreground);

	//ARS_COMMENT:basic deff, handler para trabalhar com console
	extern HANDLE					   console;
	extern CONSOLE_SCREEN_BUFFER_INFO  defaultConsoleInfo;

	//ARS_COMMENT:inicializa variáveis para controle
	void ARS_ConsoleHandlerInit();
#else
	//ARS_TODO::definições para linux
#endif
};
//--------------------------------NAMESPACE START---------------------------------------------------------------------
namespace ARS_Math{
	//-----------------------------------------------------------------------
	template <class T>
	class Vec2{
	public:
		Vec2(void){
				if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
				x = 0; y = 0;
		}
		Vec2(T x, T y){
			if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
			this->x = x; this->y = y;
		}
		T x, y;
	};
	//-----------------------------------------------------------------------
	template <class T>
	class Vec3{
	public:
		Vec3(void){
				if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
				x = 0; y = 0; z = 0;
		}
		Vec3(T x, T y, T z){
			if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
			this->x = x; this->y = y; this->z = z;
		}
		T x, y, z;
	};
	//-----------------------------------------------------------------------
	template <class T>
	class Vec4{
	public:
		Vec4(void){
				if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
				x = 0; y = 0; z = 0; w = 0;
		}
		Vec4(T x, T y, T z, T w){
			if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
			this->x = x; this->y = y; this->z = z; this->w = w;		
		}

		T x, y, z, w;
	};
	//-----------------------------------------------------------------------
	template <class T>
	class Triangle{
	public:
		Triangle(void){
			if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
		}
		Triangle(Vec4<T> A, Vec4<T> B, Vec4<T> C){
			if(typeid(T) != typeid(int)   &&
				typeid(T) != typeid(float) &&
				typeid(T) != typeid(double)){
					//ARS_TODO:tratar erro
					printf("Tipo invalido para matriz !\n");
					exit(-1);
			}
			this->A = A; this->B = B; this->C = C;
		}

		Vec4<T> A, B, C;
	};
	//-----------------------------------------------------------------------
	class ARS_ABasis{
	public:
		ARS_ABasis(void);
		ARS_ABasis(int dim,
			int cols,
			int lines);
		virtual ~ARS_ABasis(void);

		int getDimesion();
		int getcols();
		int getlines();
		void setDimension(int value);
		void setcols(int value);
		void setlines(int value);

	protected:
		int dimension;
		int cols;
		int lines;
	};
	//-----------------------------------------------------------------------
	template <class T>
	class ARS_Mat : public ARS_ABasis{
	public:
		ARS_Mat(void);
		ARS_Mat(int lines, int cols, ...);
		virtual ~ARS_Mat(void);

		//ARS_COMMENT:Pega elemento de uma determinada linha e coluna

		//ARS_MAT_INDEXING
		/*  posX = line, posY = col
		*
		*             col[0] col[1] col[2]
		*  line[0] -> ( 0 )  ( 0 )   ( 0 ) 
		*  line[1] -> ( 0 )  ( 0 )   ( 0 )
		*  line[2] -> ( 0 )  ( 0 )   ( 0 )
		*
		*  acess op => cols*posY + posX
		*/
		T getElement      (int line, int col);
		bool setElement   (int line, int col, T value);
		void setZero      ();
		void loadIdendity ();
		void loadRotation (float angle);

		virtual void print();

#if WIN32
		virtual void print(int background, int foreground);
#else
		//ARS_TODO:definir para linux
#endif

		//ARS_COMMENT:OPERADOR DE CÓPIA
		/*ARS_Mat& operator=(ARS_Mat& value){
		//ARS_TODO:fazer coleta de lixo e limpar dados
		mat.clear();
		delete this;
		this = new ARS_Mat<T>(value.lines, value.cols);
		for(int col = 0; col < value.getcols(); col++){
		for(int line = 0; line < value.getlines(); line){
		T elem = value->getElement(line,col);
		this->setElement(line,col,elem);
		}
		}

		return *this;
		}*/

	private:
		std::vector<T> mat;
	};
	//----------------------------IMP ARS_Mat--------------------------------
	//ARS_COMMENT:sobrecarga fora da classe, operadores binários
	template <class T> ARS_Mat<T> operator+ (ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator+ (ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator- (ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator* (ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator+ (ARS_Mat<T>& A, T scalar);
	template <class T> ARS_Mat<T> operator- (ARS_Mat<T>& A, T scalar);
	template <class T> ARS_Mat<T> operator* (ARS_Mat<T>& A, T scalar);
	template <class T> ARS_Mat<T> operator+=(ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator-=(ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator*=(ARS_Mat<T>& A, ARS_Mat<T>& B);
	template <class T> ARS_Mat<T> operator+=(ARS_Mat<T>& A, T scalar);
	template <class T> ARS_Mat<T> operator-=(ARS_Mat<T>& A, T scalar);
	template <class T> ARS_Mat<T> operator*=(ARS_Mat<T>& A, T scalar);

	template <class T> Triangle<T> operator* (ARS_Mat<T>& B, Triangle<T>& A);
	template <class T> Vec2<T>     operator* (ARS_Mat<T>& B, Vec2<T>& A);
	template <class T> Vec3<T>     operator* (ARS_Mat<T>& B, Vec3<T>& A);
	template <class T> Vec3<T>     operator* (Vec3<T>& A   , float scalar);
	template <class T> Vec3<T>     operator+ (Vec3<T>& A   , Vec3<T>& B);
	template <class T> Vec4<T>     operator* (ARS_Mat<T>& B, Vec4<T>& A);
	template <class T> Vec4<T>     operator* (Vec4<T>& A   , float scalar);
	template <class T> Vec4<T>     operator+ (Vec4<T>& A   , Vec4<T>& B);
	//ARS_TODO:configurar nova matriz para operadores binários
	//ARS_TODO:configurar ponteiro inteligente para deletar da memória
	//-----------------------------------------------------------------------
	template <class T> Vec4<T>     operator+ (Vec4<T>& A   , Vec4<T>& B){
		if(typeid(B.x) != typeid(A.x)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec4<T> result;

		result.x = A.x + B.x;
		result.y = A.y + B.y;
		result.z = A.z + B.z;
		result.w = 1;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Vec4<T>     operator* (Vec4<T>& A, float scalar){
		if(typeid(A.x) != typeid(scalar)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec4<T> result;

		result.x = A.x * scalar;
		result.y = A.y * scalar;
		result.z = A.z * scalar;
		result.w = 1;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Vec3<T>     operator+ (Vec3<T>& A, Vec3<T>& B){
		if(typeid(B.x) != typeid(A.x)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec3<T> result;

		result.x = A.x + B.x;
		result.y = A.y + B.y;
		result.z = A.z + B.z;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Vec3<T>     operator* (Vec3<T>& A, float scalar){
		if(typeid(A.x) != typeid(scalar)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec3<T> result;

		result.x = A.x * scalar;
		result.y = A.y * scalar;
		result.z = A.z * scalar;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Triangle<T> operator* (ARS_Mat<T>& B, Triangle<T>& A){
		if(B.getlines() < 4 || B.getcols() < 4){
			printf("Tamanhos invalidos\n");
			getchar();
			exit(-1);
		}

		if(typeid(A.A.x) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Triangle<T> result;// = new Triangle<T>();

		float m1,  m2,  m3,  m4;
		float m5,  m6,  m7,  m8;
		float m9,  m10, m11, m12;
		float m13, m14, m15, m16;

		m1  = B.getElement(0,0); m2  = B.getElement(0,1); m3  = B.getElement(0,2); m4  = B.getElement(0,3);
		m5  = B.getElement(1,0); m6  = B.getElement(1,1); m7  = B.getElement(1,2); m8  = B.getElement(1,3);
		m9  = B.getElement(2,0); m10 = B.getElement(2,1); m11 = B.getElement(2,2); m12 = B.getElement(2,3);
		m13 = B.getElement(3,0); m14 = B.getElement(3,1); m15 = B.getElement(3,2); m16 = B.getElement(3,3);

		result.A.x = A.A.x*m1  + A.A.y*m2  + A.A.z*m3  + A.A.w*m4;
		result.A.y = A.A.x*m5  + A.A.y*m6  + A.A.z*m7  + A.A.w*m8;
		result.A.z = A.A.x*m9  + A.A.y*m10 + A.A.z*m11 + A.A.w*m12;
		result.A.w = 1;

		result.B.x = A.B.x*m1  + A.B.y*m2  + A.B.z*m3  + A.B.w*m4;
		result.B.y = A.B.x*m5  + A.B.y*m6  + A.B.z*m7  + A.B.w*m8;
		result.B.z = A.B.x*m9  + A.B.y*m10 + A.B.z*m11 + A.B.w*m12;
		result.B.w = 1;

		result.C.x = A.C.x*m1  + A.C.y*m2  + A.C.z*m3  + A.C.w*m4;
		result.C.y = A.C.x*m5  + A.C.y*m6  + A.C.z*m7  + A.C.w*m8;
		result.C.z = A.C.x*m9  + A.C.y*m10 + A.C.z*m11 + A.C.w*m12;
		result.C.w = 1;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Vec2<T> operator* (ARS_Mat<T>& B, Vec2<T>& A){
		if(B.getlines() < 2 || B.getcols() < 2){
			printf("Tamanhos invalidos\n");
			getchar();
			exit(-1);
		}	

		if(typeid(A.x) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		float m1,  m2;
		float m5,  m6;

		m1  = B.getElement(0,0); m2  = B.getElement(0,1);
		m5  = B.getElement(1,0); m6  = B.getElement(1,1);

		Vec2<T> result;// = new Vec2<T>();
		
		result.x = A.x*m1  + A.y*m2;
		result.y = A.y*m5  + A.y*m6;

		return result;		
	}
	//-----------------------------------------------------------------------
	template <class T> Vec3<T>     operator* (ARS_Mat<T>& B, Vec3<T>& A){
		if(B.getlines() < 3 || B.getcols() < 3){
			printf("Tamanhos invalidos\n");
			getchar();
			exit(-1);
		}

		if(typeid(A.x) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec3<T> result;// = new Vec3<T>();

		float m1,  m2,  m3;
		float m5,  m6,  m7;
		float m9,  m10, m11;

		m1  = B.getElement(0,0); m2  = B.getElement(0,1); m3  = B.getElement(0,2);
		m5  = B.getElement(1,0); m6  = B.getElement(1,1); m7  = B.getElement(1,2);
		m9  = B.getElement(2,0); m10 = B.getElement(2,1); m11 = B.getElement(2,2);

		result.x = A.x*m1  + A.y*m2  + A.z*m3;
		result.y = A.y*m5  + A.y*m6  + A.z*m7;
		result.z = A.x*m9  + A.y*m10 + A.z*m11;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> Vec4<T>     operator* (ARS_Mat<T>& B, Vec4<T>& A){
		if(B.getlines() < 4 || B.getcols() < 4){
			printf("Tamanhos invalidos\n");
			getchar();
			exit(-1);
		}

		if(typeid(A.x) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		Vec4<T> result;// = new Vec4<T>();

		float m1,  m2,  m3,  m4;
		float m5,  m6,  m7,  m8;
		float m9,  m10, m11, m12;
		float m13, m14, m15, m16;

		m1  = B.getElement(0,0); m2  = B.getElement(0,1); m3  = B.getElement(0,2); m4  = B.getElement(0,3);
		m5  = B.getElement(1,0); m6  = B.getElement(1,1); m7  = B.getElement(1,2); m8  = B.getElement(1,3);
		m9  = B.getElement(2,0); m10 = B.getElement(2,1); m11 = B.getElement(2,2); m12 = B.getElement(2,3);
		m13 = B.getElement(3,0); m14 = B.getElement(3,1); m15 = B.getElement(3,2); m16 = B.getElement(3,3);

		result.x = A.x*m1  + A.y*m2  + A.z*m3  + A.w*m4;
		result.y = A.y*m5  + A.y*m6  + A.z*m7  + A.w*m8;
		result.z = A.x*m9  + A.y*m10 + A.z*m11 + A.w*m12;
		result.w = A.x*m10 + A.y*m14 + A.z*m15 + A.w*m16;

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator+(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getcols() ||
			B.getcols()  != A.getcols()){
				//ARS_TODO:tratar erro aqui
				exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		ARS_Mat<T> result = ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemB   = B.getElement(line, col);
				T elemRes = elemA + elemB;
				result->setElement(line, col, elemRes);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator-(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getcols() ||
			B.getcols()  != A.getcols()){
				//ARS_TODO:tratar erro aqui
				exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		ARS_Mat<T> result = ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemB   = B.getElement(line, col);
				T elemRes = elemA - elemB;
				result->setElement(line, col, elemRes);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator*(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getlines()){
			//ARS_TODO:tratar erro aqui
			exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		int new_cols  = B.getcols();
		int new_lines = A.getlines();

		ARS_Mat<T> result = ARS_Mat<T>(new_lines, new_cols);

		for(int k = 0; k < new_lines; k++){
			for(int m = 0; m < new_lines; m++){
				//ARS_COMMENT:inner sum
				T partial_sum = 0;
				for(int elem = 0; elem < B.getlines(); elem++){
					T a_elem = A.getElement(k, elem);
					T b_elem = B.getElement(elem, m);
					partial_sum += a_elem * b_elem;
				}

				result.setElement(k, m, partial_sum);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator+(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		ARS_Mat<T> result = ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA + scalar;
				result.setElement(line, col, elemRes);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator-(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		ARS_Mat<T> result = ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA - scalar;
				result.setElement(line, col, elemRes);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator*(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		ARS_Mat<T> result = ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA * scalar;
				result.setElement(line, col, elemRes);
			}
		}

		return result;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator+=(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getcols() ||
			B.getcols()  != A.getcols()){
				//ARS_TODO:tratar erro aqui
				exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		//ARS_Mat<T>* result = new ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemB   = B.getElement(line, col);
				T elemRes = elemA + elemB;
				A.setElement(line, col, elemRes);
			}
		}

		return A;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator-=(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getcols() ||
			B.getcols()  != A.getcols()){
				//ARS_TODO:tratar erro aqui
				exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		//ARS_Mat<T>* result = new ARS_Mat<T>(A.getlines(), A.getcols());

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemB   = B.getElement(line, col);
				T elemRes = elemA - elemB;
				A.setElement(line, col, elemRes);
			}
		}

		return A;
	}
	//-----------------------------------------------------------------------	
	template <class T> ARS_Mat<T> operator*=(ARS_Mat<T>& A, ARS_Mat<T>& B){
		if(A.getcols()  != B.getlines()){
			//ARS_TODO:tratar erro aqui
			exit(-1);
		}

		if(typeid(A.getElement(0,0)) != typeid(B.getElement(0,0))){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		int new_cols  = B.getcols();
		int new_lines = A.getlines();

		ARS_Mat<T> result = ARS_Mat<T>(new_lines, new_cols);

		for(int k = 0; k < new_lines; k++){
			for(int m = 0; m < new_lines; m++){
				//ARS_COMMENT:inner sum
				T partial_sum = 0;
				for(int elem = 0; elem < B.getlines(); elem++){
					T a_elem = A.getElement(k, elem);
					T b_elem = B.getElement(elem, m);
					partial_sum += a_elem * b_elem;
				}

				result->setElement(k, m, partial_sum);
			}
		}

		for(int k = 0; k < new_lines; k++)
			for(int m = 0; m < new_cols; m++)
				A.setElement(k,m, result->getElement(k,m));

		delete result;
		result = NULL;

		return A;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator+=(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA + scalar;
				A.setElement(line, col, elemRes);
			}
		}

		return A;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator-=(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA - scalar;
				A.setElement(line, col, elemRes);
			}
		}

		return A;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T> operator*=(ARS_Mat<T>& A, T scalar){
		if(typeid(A.getElement(0,0)) != typeid(T)){
			printf("Tipos incompativeis\n");
			getchar();
			exit(-1);
		}

		//ARS_COMMENT:exec op
		for(int col = 0; col < A.getcols(); col++){
			for(int line = 0; line < A.getlines(); line++){
				T elemA   = A.getElement(line, col);
				T elemRes = elemA * scalar;
				A.setElement(line, col, elemRes);
			}
		}

		return A;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T>::ARS_Mat(void){
		if(typeid(T) != typeid(int)   &&
			typeid(T) != typeid(float) &&
			typeid(T) != typeid(double)){
				//ARS_TODO:tratar erro
				printf("Tipo invalido para matriz !\n");
				exit(-1);
		}

		this->dimension = 0;
		this->cols      = 0;
		this->lines     = 0;
	}
	//-----------------------------------------------------------------------
	/*template <class T> ARS_Mat<T>::ARS_Mat(int lines, int cols){
	if(typeid(T) != typeid(int)   &&
	typeid(T) != typeid(float) &&
	typeid(T) != typeid(double)){
	//ARS_TODO:tratar erro
	printf("Tipo invalido para matriz !\n");
	exit(-1);
	}

	int total_args = cols*lines;

	for(int i = 0; i < total_args; i++){
	T gen;
	mat.push_back(gen);
	}

	dimension   = cols;
	this->cols  = cols;
	this->lines = lines;
	}*/
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T>::ARS_Mat(int lines, int cols, ...){
		if(typeid(T) != typeid(int)   &&
			typeid(T) != typeid(float) &&
			typeid(T) != typeid(double)){
				//ARS_TODO:tratar erro
				printf("Tipo invalido para matriz !\n");
				getchar();
				exit(-1);
		}

		int total_args = cols*lines;

		va_list list;
		va_start(list, cols);
		for(int i = 0; i < total_args; i++){
			T value   = va_arg(list, T);
			mat.push_back(value);
		}
		va_end(list);

		//ARS_COMMENT::Config properties
		dimension   = cols;
		this->cols  = cols;
		this->lines = lines;
	}
	//-----------------------------------------------------------------------
	template <class T> ARS_Mat<T>::~ARS_Mat(void){
		//ARS_TODO::implementar destrutor
		//printf("Destruindo matriz !!!\n");
	}
	//-----------------------------------------------------------------------
	template <class T> T ARS_Mat<T>::getElement(int line, int col){
		if(col > cols){
			printf("Dimensão x incompativel: %i", col);
			//ARS_TODO:tratar erro
			getchar();
			exit(-1);
		}

		if(line > lines){
			printf("Dimensão y incompativel: %i", line);
			//ARS_TODO:tratar erro
			getchar();
			exit(-1);
		}

		//ARS_IMPORTANT:conta importante, acesso a matriz
		int position = cols*line + col;

		if(position > cols*lines){
			printf("Posição inválida: %i\n", position);
			getchar();
			exit(-1);
			//ARS_TODO::tratar erro
		}
		return mat.at(position);
	}
	//-----------------------------------------------------------------------
	template <class T> bool ARS_Mat<T>::setElement(int line, int col, T value){
		bool ok = false;

		if(col > cols || line > lines){
			printf("Linha inválida...\n");
			getchar();
			//ARS_TODO:tratar erro
			exit(-1);
		}

		//ARS_IMPORTANT:conta importante, acesso a matriz
		int position = cols*line + col;

		mat.at(position) = value;

		return ok;
	}
	//-----------------------------------------------------------------------
	template <class T> void ARS_Mat<T>::print(){
		printf("\n ----Printing matrix---- \n\n");

		for(int i = 0; i < cols; i++){
			for(int j = 0; j < lines; j++){
				std::cout << getElement(i,j);
			}
			printf("\n");
		}

		printf("\n ---- Matrix printed---- \n");
	}
	//-----------------------------------------------------------------------
	template <class T> void ARS_Mat<T>::setZero(){
		for(int i = 0; i < lines*cols; i++)
			mat.at(i) = 0;
	}
	//-----------------------------------------------------------------------
	template <class T> void ARS_Mat<T>::loadIdendity(){
		for(int line = 0; line < lines; line++){
			for(int col = 0; col < cols; col++){
				if(line == col)
					setElement(line, col, 1.0);
				else
					setElement(line, col, 0.0);
			}
		}
	}
	//-----------------------------------------------------------------------
	template <class T> void ARS_Mat<T>::loadRotation (float angle){
	}
	//-----------------------------------------------------------------------
#if WIN32
	template <class T> void ARS_Mat<T>::print(int background, int foreground){
		ARS_ConsoleHandler::getDefaultConsoleAtt();

		//ARS_COMMENT:init color
		int final_color = ARS_ConsoleHandler::getFinalColor(FONT_C_BLACK, FONT_C_I_YELLOW);
		ARS_ConsoleHandler::setColor(final_color);

		printf("\n ----Printing matrix---- \n\n");

		//ARS_COMMENT:corpse color
		final_color = ARS_ConsoleHandler::getFinalColor(background, foreground);
		ARS_ConsoleHandler::setColor(final_color);

		for(int i = 0; i < lines; i++){
			std::cout << "|";

			for(int j = 0; j < cols; j++){
				std::cout << getElement(i, j);

				if(j!=cols-1)
					std::cout << "\t";
			}
			std::cout << "|";
			printf("\n");
		}

		//ARS_COMMENT:final color
		final_color = ARS_ConsoleHandler::getFinalColor(FONT_C_BLACK, FONT_C_I_YELLOW);
		ARS_ConsoleHandler::setColor(final_color);
		printf("\n -----Matrix printed---- \n");

		ARS_ConsoleHandler::setDefaultConsoleAtt();
	}
#else
	//ARS_TODO:definir para linux
#endif
	//template <typename T> struct ARS_Mat{
	//	static const char* name() { static_assert(false, "You are missing a DECL_TYPE_NAME"); }
	//};

	//template<> struct ARS_Mat<int> {static const char* name() {return "int";}};
	//-------------------------------OPERATIONS------------------------------
};
//--------------------------------NAMESPACE START---------------------------------------------------------------------
namespace ARS_GDCG{
	#define    ARS_FACECULL	 0x01
	#define    ARS_BACKFACES 0x02
	#define    ARS_WIREFRAME 0x03
	#define    ARS_DEPTHTEST 0x04

	//ARS_COMMENT:utilizado para armazenar matriz de pixels
	class ARS_FrameBuffer{
	public:
		ARS_FrameBuffer(GLsizei width, GLsizei height, GLenum format, GLenum type){
			//ARS_COMMENT:configurando color buffer
			colorData    = new float[width*height*3]; //RGB model ARS_COMMENT:
			memset((void*)colorData, 0, sizeof(float)*width*height*3);

			//ARS_COMMENT:configurando depth buffer
			depthData    = new float[width*height];
			memset((void*)depthData, 1, sizeof(float)*width*height);

			this->width  = width;
			this->height = height;
			this->format = format;
			this->type   = type;
		}

		GLsizei width, height;      //ARS_COMMENT:tamanho da janela
		GLenum format, type;        //ARS_COMMENT:formato de pixels e tipoe
		const GLvoid* colorData;    //ARS_COMMENT:vetor de pixels da imagem
		const GLvoid* depthData;    //ARS_COMMENT:buffer de profundidades
	};

	//ARS_COMMENT:definições padrões
	typedef struct ARS_ClearColor{
		float r, g, b;
	}ARS_ClearColor;

	//ARS_COMMENT:apenas desenha pixels no framebuffer do OGL
	void ARS_RenderToFrameBuffer(ARS_FrameBuffer& buffer);
	void ARS_InitGDCG			();
	void ARS_SetPixel           (int x, int y, float r, float g, float b, ARS_FrameBuffer& buffer);
	void ARS_SetDepthData       (int x, int y, float d, ARS_FrameBuffer& buffer);
	void ARS_Clear              (ARS_FrameBuffer& buffer);
	void ARS_SetClearColor      (float r, float g, float b);
	void ARS_SetViewPort        (int width, int height, ARS_FrameBuffer& buffer);
	void ARS_SetPerspective	    (float nearPlane, float farPlane);
	void ARS_SetOrtho			();
	void ARS_LoadIdentity       ();
	void ARS_PushMatrix         ();
	void ARS_PopMatrix          ();
	void ARS_SetVertexBuffer    (float* vertexList, int size);
	void ARS_SetColorBuffer     (float* colorList , int size);
	void ARS_TriangleAssembler  (float* vertexList,
								 float* vertexColorList,
								 std::vector<ARS_Math::Triangle<float>>& triangleList,
								 std::vector<ARS_Math::Triangle<float>>& triangleVertexColorList);
	void ARS_Enable				(int code);
	void ARS_Disable            (int code);
	
	//ARS_COMMENT::apenas para teste
	void ARS_RenderQuad();

	//ARS_COMMENT::transformações planas basicas
	void ARS_Translate          (float x, float y, float z);
	void ARS_Scale              (float x, float y, float z);
	void ARS_Rotate             (float angleX, float angleY, float angleZ);
	
	//controle
	extern std::vector<ARS_Math::Vec4<float>>      triangleAssembler;
	extern ARS_Math::Triangle<float>		       currentTriangle;
	extern ARS_Math::Triangle<float>		       currentTriangleColor;

	extern ARS_ClearColor clearColor;
	extern ARS_Math::ARS_Mat<float>                projection;
	extern ARS_Math::ARS_Mat<float>                modelview;
	extern std::vector<ARS_Math::ARS_Mat<float>>   matStack;
	extern std::vector<ARS_Math::ARS_Mat<float>>   subMatStack;

	//ARS_COMMENT:usado pelo assembler
	extern std::vector<ARS_Math::Triangle<float>> triangleList;
	extern std::vector<ARS_Math::Triangle<float>> trianglesVertexColorList;
	extern std::vector<ARS_Math::Triangle<float>> projectedTriangles;

	extern float* vertexList;
	extern int    vertexCount;
	extern float* vertexColorList;
	extern int    colorCount;

	extern bool   dirtyVertexList;
	extern bool   dirtyModelView;
	extern bool   faceCulling;
	extern bool   rastBackFaces;
	extern bool   wireframe;
	extern bool   depthtest;
};
//--------------------------------NAMESPACE END-----------------------------------------------------------------------
namespace ARS_Rasterization{
	//ARS_COMMENT:utilizado para arredondamento de coordenadas baricentricas do triangulo
	#define epslon 0.00001

	//ARS_COMMENT:rasterização de triângulos
	void calcBaricentric(
		int x,                  //ARS_COMMENT:coordenada no plano projetado
		int y,					//ARS_COMMENT:coordenada no plano projetado
		ARS_Math::Triangle<float> triangle,
		float& lambdaA, 
		float& lambdaB, 
		float& lambdaC);

	bool checkPixel(float baryX, float baryY);

	void ARS_RastTriangle(
		ARS_GDCG::ARS_FrameBuffer& buffer, 
		ARS_Math::Triangle<float>& triangle, 
		ARS_Math::Triangle<float>& tColor);
};
//--------------------------------NAMESPACE END-----------------------------------------------------------------------'
