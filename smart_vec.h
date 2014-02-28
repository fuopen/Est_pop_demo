#ifndef _SMART_VEC_H_
#define _SMART_VEC_H_
#include"vec.h"
#include"bs_fuc.h"
//#include"mat.h"
#include<iostream>
#include<cmath>
using namespace std;
//*******************************************************************
/* this head file define the derived class inherited from 
the base class vec*/
//*******************************************************************
//define smart vec

template <class T>
class smart_vec:public vec<T>{
public:
//constructor and destructor
	//friend class mat<T>;
	smart_vec();
	smart_vec(const int&,const T*);
	smart_vec(const T*, const int&);
	smart_vec(const int&,const T&);
	smart_vec(const int&);
	smart_vec(const smart_vec&);
	~smart_vec();
//basic function
	smart_vec operator +(const smart_vec&)const;//vec plus
	smart_vec operator -(const smart_vec&)const;//vec substract
	T operator *(const smart_vec&)const;//vec product
	smart_vec operator *(const T&)const;//vec multiply 
	smart_vec& operator +=(const smart_vec&);
	smart_vec& operator -=(const smart_vec&);
	smart_vec& operator =(const smart_vec&);
//extension function	
	T _norm();
	T _mid();
	T _vec_sum();
	void show();
};

template <class T>
smart_vec<T>::smart_vec():vec<T>(){
}

template <class T>
smart_vec<T>::smart_vec(const int& svec_size,const T* svec_mem):vec<T>(svec_size,svec_mem){
}

template <class T>
smart_vec<T>::smart_vec(const T* svec_mem, const int& svec_size):vec<T>(svec_size,svec_mem){
}

template <class T>
smart_vec<T>::smart_vec(const int& in_size,const T& ini):vec<T>(in_size,ini){
}

template <class T>
smart_vec<T>::smart_vec(const int& in_size):vec<T>(in_size){
}

template <class T>
smart_vec<T>::smart_vec(const smart_vec& cp_svec):vec<T>(cp_svec){
}

template <class T>
smart_vec<T>::~smart_vec(){
	this->suicide();
}

template <class T>
smart_vec<T> smart_vec<T>::operator +(const smart_vec& add)const{
	if(this->size == add.size){
		smart_vec<T>* plus = new smart_vec(this->size);
		for(int i =0;i!=plus->size;i++){
			*(plus->mem+i) = *(this->mem + i) + *(add.mem + i);
		}
		plus->beg = plus->mem;
		plus->end = plus->mem + plus->size;
		return *plus;
	}
}

template <class T>
smart_vec<T> smart_vec<T>::operator -(const smart_vec& sub)const{
	if(this->size == sub.size){
		smart_vec<T>* minus = new smart_vec(this->size);
		for(int i =0;i!=minus->size;i++){
			*(minus->mem+i) = *(this->mem + i) - *(sub.mem + i);
		}
		minus->beg = minus->mem;
		minus->end = minus->mem + minus->size;
		return *minus;
	}
}

template <class T>
T smart_vec<T>::operator *(const smart_vec& mult)const{
	if(this->size == mult.size){
		T temp = *(this->beg)* *(mult.beg);
		for(int i=1;i<this->size;i++){
			temp += *(this->mem+i)* *(mult.mem+i);
		}
	return temp;
	}		
}

template <class T>
smart_vec<T> smart_vec<T>::operator *(const T& coef)const{
	smart_vec<T>* pu_mul = new smart_vec<T>(this->size);
	for(int i=0;i<pu_mul->size;i++){
		*(pu_mul->mem+i) = *(this->mem+i)*coef;
	}
	return *pu_mul;
}

template <class T>
smart_vec<T>& smart_vec<T>::operator +=(const smart_vec& ad_eq){
	if(this->size == ad_eq.size){
		for(int i=0;i<this->size;i++){
			*(this->mem+i)= *(this->mem+i)+ *(ad_eq.mem+i);
		}
	}
	return *this;	
}

template <class T>
smart_vec<T>& smart_vec<T>::operator -=(const smart_vec& sb_eq){
	if(this->size == sb_eq.size){
		for(int i=0;i<this->size;i++){
			*(this->mem+i)= *(this->mem+i)- *(sb_eq.mem+i);
		}
	}
	return *this;	
}

template <class T>
smart_vec<T>& smart_vec<T>::operator =(const smart_vec& eq){
	delete[] this->mem;
	this->size = eq.size;
	this->mem = new T[this->size+1];
	memcpy(this->mem,eq.mem,this->size*sizeof(T));
	this->beg = this->mem;
	this->end = this->mem + this->size;
	return *this;
}

template <class T>
T smart_vec<T>::_norm(){
	return (*this* *this);
}

template <class T>
T smart_vec<T>::_mid(){
	if((this->size)%2 == 0) return *(this->mem+this->size/2);
	else return *(this->mem + (this->size-1)/2);
}

template <class T>
T smart_vec<T>::_vec_sum(){
	T temp = *(this->beg);
	for(int i=1;i<this->size;i++){
		temp +=(this->mem+i);
	}
	return temp;
}

template <class T>
void smart_vec<T>::show(){
	//cout<<"the size is: "<<this->size<<endl;
	for(T* seek = this->beg;seek!=this->end;seek++)
		cout<<*seek<<" ";
	//cout<<endl;
}

typedef smart_vec<int>    svac_i;
typedef smart_vec<char>   svac_c;
typedef smart_vec<double> svac_d;			
#endif
