#ifndef _BS_FUC_H_
#define _BS_FUC_H_
//*******************************************************************
/*this head file is to define some basic function

  */
//*******************************************************************
typedef double db;
typedef int in;
typedef char ch;
typedef long int lin;
typedef unsigned int uin;
typedef double* dbp;
typedef int* inp;
typedef char* chp;
typedef char** chpp;

typedef const double cdb;
typedef const int cin;
typedef const long int clin;
typedef const unsigned int cuin;
typedef const double* cdbp;
typedef const int* cinp;
typedef const char* cchp;
//*******************************************************************

template<class T>
inline void _swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

template<class T>
inline T _maxim(T&a, T&b){
	return (a>b)? a:b ;
}

template<class T>
inline T _minim(T&a, T&b){
	return (a<b)? a:b ;
}

template<class T>
inline T& _positive(T&a){
	a = (a>0)? a:0;
	return a;
}
#endif
