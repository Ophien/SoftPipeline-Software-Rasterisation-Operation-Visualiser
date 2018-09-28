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

#if WIN32
	#include <Windows.h> //ARS_COMMENT:trabalhar com handlers e chamadas de sistema
#else
	//ARS_TODO::definições para linux
#endif

#include <stdio.h>   //ARS_COMMENT:input    output       , scanf  , printf
#include <ostream>   //ARS_COMMENT:standard output stream, cout
#include <iostream>  //ARS_COMMENT:standard input  stream, cin
#include <stdlib.h>  //ARS_COMMENT:standard library      , rand   , malloc  , free
#include <stdarg.h>  //ARS_COMMENT:basic    macros       , va_list, va_start, va_end, va_arg
#include <string.h>  //ARS_COMMENT:string   manipulation
#include <typeinfo>  //ARS_COMMENT:para     usar           typeid
#include <gl\GL.h>   //ARS_COMMENT:OGL default
#include <math.h>    //ARS_COMMENT:operações fundamentais
#include <stack>     //ARS_COMMENT:pilha
#include <vector>    //ARS_COMMENT:vetor
#include <algorithm> //ARS_COMMENT:para manipulações complexas
