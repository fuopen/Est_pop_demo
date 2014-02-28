#ifndef _MAT_H_
#define _MAT_H_
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<iostream>
#include"smart_vec.h"

using namespace std;
//*******************************************************************
/*this is define the matrix template class
*/
//*******************************************************************
template <class T>
class mat{
protected:
	int row;
	int col;
	T** mat_mem;
public:
//constructor and destructor define
	//friend class smart_vec<T>;
	mat();
	mat(const int&,const int&,const T**);
	mat(T**,const int&,const int&);
	mat(const T*,const int&,const int&);
	mat(const int&,const int&);
	mat(const int&,const int&,const T&);
	mat(const int&);
	mat(const int&,const T&);
	mat(const mat&);
	mat(const smart_vec<T>&,bool bycol = true); 
	~mat();
//basic operator overloading
	mat operator +(const mat&)const;//plus operator
	mat operator -(const mat&)const;//substract operator
	mat operator *(const mat&)const;//multiply operator
	mat& operator =(const mat&);//assignment operator
	mat& operator +=(const mat&);//self plus operator
	mat& operator -=(const mat&);//self substract operator
	mat& operator *=(const mat&);//self multiply operator
	mat  operator *(const T&)const;//multiply coef;
	/*smart_vec<T> operator [](const int&);//get the row
	const smart_vec<T> operator[](const int&)const; */
	smart_vec<T> operator()(const int&);
	const smart_vec<T> operator()(const int&)const;
	T* operator [](const int&);
	const T* operator [](const int&)const;
	//T* operator ()(const int&);
	//const T* operator ()(const int&)const;
//basic function
	int _row();
	int _col();
	void _show();
};

template <class T>
mat<T>::mat():row(0),col(0),mat_mem(NULL){
}

template <class T>
mat<T>::mat(const int& nrow,const int& ncol,const T** array_2d):row(nrow),col(ncol),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*ncol];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*ncol;
		//memcpy(mat_mem[i],array_2d[i],ncol*sizeof(T));
	}
	memcpy(mat_mem[0],array_2d[0],nrow*ncol*sizeof(T));
}

template <class T>
mat<T>::mat(T** array_2d,const int& nrow,const int& ncol):row(nrow),col(ncol),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*ncol];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*ncol;
		//memcpy(mat_mem[i],array_2d[i],ncol*sizeof(T));
	}
	memcpy(mat_mem[0],array_2d[0],nrow*ncol*sizeof(T));
}
	
template <class T>
mat<T>::mat(const T* array,const int& nrow,const int& ncol):row(nrow),col(ncol),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*ncol];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*ncol;
	}
	memcpy(mat_mem[0],array,nrow*ncol*sizeof(T));
}

template <class T>
mat<T>::mat(const int& nrow,const int& ncol):row(nrow),col(ncol),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*ncol];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*ncol;
	}
	memset(mat_mem[0],0,nrow*ncol*sizeof(T));
}

template <class T>
mat<T>::mat(const int& nrow,const int& ncol,const T& ini):row(nrow),col(ncol),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*ncol];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*ncol;
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_mem[i][j]=ini;
		}
	}
}

template <class T>
mat<T>::mat(const int& nrow):row(nrow),col(nrow),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*nrow];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*nrow;
	}
	memset(mat_mem[0],0,nrow*nrow*sizeof(T));
}

template <class T>
mat<T>::mat(const int& nrow,const T& ini):row(nrow),col(nrow),mat_mem(new T*[nrow]){
	mat_mem[0] = new T[nrow*nrow];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*col;
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_mem[i][j]=ini;
		}
	}
}

template <class T>
mat<T>::mat(const mat& cp_mat):row(cp_mat.row),col(cp_mat.col),mat_mem(new T*[cp_mat.row]){
	mat_mem[0] = new T[row*col];
	for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*col;
	}
	memcpy(mat_mem[0],cp_mat.mat_mem[0],row*col*sizeof(T));
}

template <class T>
mat<T>::mat(const smart_vec<T>& svec,bool bycol){
	if(bycol==true){
		row = svec._size();
		col = 1;
		mat_mem = new T*[row];
		mat_mem[0] = new T[row];
		for(int i=0;i<row;i++){
		mat_mem[i]=mat_mem[0]+i*col;
	    }
		for(int i=0;i<row;i++){
			mat_mem[i][0] = svec[i];
		}
	}
	else{
		row = 1;
		col = svec._size();
		mat_mem = new T*[1];
		mat_mem[0] = new T[col];
		for(int i=0;i<col;i++){
			mat_mem[0][i] = svec[i];
		}
	}
}

template <class T>
mat<T>::~mat(){
	delete mat_mem[0];
	delete[] mat_mem;
	mat_mem = NULL;
}

template <class T>
mat<T> mat<T>::operator +(const mat& add_mat)const{
	assert(row==add_mat.row&&col==add_mat.col);
	mat<T>* mat_plus = new mat(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_plus->mat_mem[i][j] = mat_mem[i][j] + add_mat.mat_mem[i][j];
		}
	}
	return *mat_plus;
}

template <class T>
mat<T> mat<T>::operator -(const mat& sub_mat)const{
	assert(row==sub_mat.row&&col==sub_mat.col);
	mat<T>* mat_minus = new mat(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_minus->mat_mem[i][j] = mat_mem[i][j] - sub_mat.mat_mem[i][j];
		}
	}
	return *mat_minus;
}

template <class T>
mat<T> mat<T>::operator *(const mat& mul_mat)const{
	assert(col== mul_mat.row);
	mat<T>* mat_mul = new mat(row,mul_mat.col);
	for(int i=0;i<row;i++){
		for(int j=0;j<mul_mat.col;j++){
			for(int k=0;k<col;k++){
				mat_mul->mat_mem[i][j] += mat_mem[i][k]*mul_mat.mat_mem[k][j];
			}
		}
	}
	return *mat_mul;
} 

template <class T>
mat<T>& mat<T>::operator =(const mat& eq_mat){
	if(this==&eq_mat){
		return *this;
	}
	else{
		delete mat_mem[0];
		delete[] mat_mem;
		row = eq_mat.row;
		col = eq_mat.col;
		mat_mem = new T*[row];
		mat_mem[0] = new T[row*col];
		memcpy(mat_mem[0],eq_mat.mat_mem[0],row*col*sizeof(T));
		return *this;
	}
}

template <class T>
mat<T>& mat<T>::operator +=(const mat& adeq){
	assert(row == adeq.row && col== adeq.col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_mem[i][j] +=adeq.mat_mem[i][j];
		}
	}
	return *this;
}

template <class T>
mat<T>& mat<T>::operator -=(const mat& sbeq){
	assert(row == sbeq.row && col== sbeq.col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mat_mem[i][j] -=sbeq.mat_mem[i][j];
		}
	}
	return *this;
}

template <class T>
mat<T>& mat<T>::operator *=(const mat& mul_mat){
	assert(col== mul_mat.row);
	mat<T>* smul = new mat(row,mul_mat.col);
	for(int i=0;i<row;i++){
		for(int j=0;j<mul_mat.col;j++){
			for(int k=0;k<col;k++){
				smul->mat_mem[i][j] += mat_mem[i][k]*mul_mat.mat_mem[k][j];
			}
		}
	}
	*this = *smul;
	delete smul;
	return *this;
} 

template <class T>
mat<T> mat<T>::operator *(const T& coeff)const{
	mat<T>* pure_mul = new mat(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			pure_mul->mat_mem[i][j] = mat_mem[i][j]*coeff;
		}
	}
	return *pure_mul;
}

/*template <class T>
smart_vec<T> mat<T>::operator [](const int& index){
	smart_vec<T>* vec_row = new smart_vec<T>(col,mat_mem[index]);
	cout<<"isn't const svac"<<endl;
	return *vec_row; 
}

template <class T>
const smart_vec<T> mat<T>::operator [](const int& index)const{
	const smart_vec<T>* vec_row = new smart_vec<T>(col,mat_mem[index]);
	cout<<"is const svac"<<endl;
	return *vec_row;
}*/

template <class T>
smart_vec<T> mat<T>::operator ()(const int& index){
	smart_vec<T>* vec_col = new smart_vec<T>(row,mat_mem[0][index]);
	for(int i=0;i<row;i++){
		(*vec_col)[i] = mat_mem[i][index];
	}
	return *vec_col;
}

template <class T>
const smart_vec<T> mat<T>::operator ()(const int& index)const{
	const smart_vec<T>* vec_col = new smart_vec<T>(row,mat_mem[0][index]);
	for(int i=0;i<row;i++){
		(*vec_col)[i] = mat_mem[i][index];
	}
	return *vec_col;
}

template <class T>
T* mat<T>::operator [](const int& index){
	return mat_mem[index];
}

template <class T>
const T* mat<T>::operator [](const int& index)const{
	return mat_mem[index];
}

template <class T>
int mat<T>::_row(){
	return row;
}

template <class T>
int mat<T>::_col(){
	return col;
}

template <class T>
void mat<T>::_show(){
	if(col==1){
		for(int i=0;i<row;i++){
			cout<<mat_mem[i][0]<<" ";
		}
	}
	else{
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				cout<<mat_mem[i][j]<<" ";
			}
			cout<<endl;
		}
	}
}

typedef mat<int>    mat_in;
typedef mat<double> mat_db;				
#endif
