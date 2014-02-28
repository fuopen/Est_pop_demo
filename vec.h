#ifndef _VEC_H_
#define _VEC_H_
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<iostream>
using namespace std;
//*******************************************************************
/*this head file is used to define the basic template class
vec, and its basic function*/
//*******************************************************************
//define the template class vec
template <class T>
class vec{
protected:
	int size;
	T*  mem;
	T*  beg;
	T*  end;
public:
	vec();
	vec(const int&,const T*);
	vec(const T*,const int&);
	vec(const int&,const T&);
	vec(const int&);
	vec(const vec&);
	inline T& operator[](const int&);
	inline const T& operator[](const int&)const; 
	virtual ~vec();
	void suicide();
	vec& operator =(const vec&);
	const int _size()const;
};

template <class T>
vec<T>::vec():size(0),mem(NULL),beg(NULL),end(NULL){
}

template <class T>
vec<T>::vec(const int& v_size, const T* v_mem){
	size = v_size;
	mem = new T[size+1];
	memcpy(mem,v_mem,size*sizeof(T));
	beg = mem;
	end = mem + size;
}

template <class T>
vec<T>::vec(const T* v_mem,const int& v_size){
	size = v_size;
	mem = new T[size+1];
	memcpy(mem,v_mem,size*sizeof(T));
	beg = mem;
	end = mem + size;
}

template <class T>
vec<T>::vec(const int& con_size,const T& ini){
	size = con_size;
	mem  = new T[size+1];
	beg  = mem;
	end  = mem + size;
	for(int i=0;i<size;i++){
		*(mem+i)=ini;
	}
}

template <class T>
vec<T>::vec(const int& con_size){
	size = con_size;
	mem  = new T[size+1];
	beg  = mem;
	end  = mem + size;
	memset(mem,0,size*sizeof(T));
}

template <class T>
vec<T>::vec(const vec& cpv){
	size = cpv.size;
	mem  = new T[size+1];
	memcpy(mem,cpv.mem,size*sizeof(T));
	beg = mem;
	end = mem + size;
}

template <class T>
vec<T>::~vec(){
	suicide();
}

template <class T>
inline T& vec<T>::operator [](const int& i){
	//cout<<"fuck isn't const"<<endl;
	return mem[i]; 
}

template <class T>
inline const T& vec<T>::operator [](const int& i)const{
	//cout<<"fuck is const"<<endl;
	return mem[i];
}

template <class T>
void vec<T>::suicide(){
	delete[] mem;
	mem = NULL;
	beg = NULL;
	end = NULL;
}

template <class T>
vec<T>& vec<T>::operator =(const vec<T>& ass){
	if(this == &ass) return *this;
	else{
		delete[] mem;
		size = ass.size;
		mem  = new T[size+1];
		memcpy(mem,ass.mem,size*sizeof(T));
		beg  = mem;
		end  = mem + size;
		return *this;
	}
}

template <class T>
const int vec<T>::_size()const{
	return size;
}
#endif
