#ifndef _MYMATH_H_
#define _MYMATH_H_
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<iostream>
#include<cstring>
#define TINY 0.0000001
using namespace std;

template<class T>
T nFr(const T& n,const unsigned int& r){//this function used calculate the factorize 
	T reval=n;
	if(r==0){
		reval=1;
	}
	else if(r==1){
		reval=n;
	}
	else{
		for(unsigned int i=1;i<r;i++){
			reval*=n-i;
		}
	}
	return reval;
}

template<class T>
T nfr(const T& n,const unsigned int& r){//this function used to calculate the inverse factorize 
	T reval=n;
	if(r==0){
		reval=1;
	}
	else if(r==1){
		reval=n;
	}
	else{
		for(unsigned int i=1;i<r;i++){
			reval*=n+i;
		}
	}
	return reval;
}

template<class T>
T nfac(const T& n){//this function used to calculate the factorize
	T reval=n;
	if(n==0||n==1){
		reval=1;
	}
	else{http://www.google.com/search?client=ubuntu&channel=fs&q=bit+byte&ie=utf-8&oe=utf-8
		for(unsigned int i=1;i<n;i++){
			reval*=n-i;
		}
	}
	return reval;
}

template<class T>
T nCr(const T& n, const unsigned int& r){//this function used to calculate the n choose r
	T reval=0;
	if(n<r){
		reval=0;
	}
	else{
		T r0= (T) r;
		reval=nFr(n,r)/nfac(r0);
	}
	return reval;
}

template<class T>
double phi(const double& x,const T& n,const unsigned int& k){
	double reval=0.0;
	double s=0.0;
	for(unsigned int i=1;i<=k;i++){
		s+=pow((1-x),(int) i)*pow((-1.0),(int)(k-i))*nCr((long int)k+i-2,k-1)*nCr((long int)k,i);
	}
	reval=s*(2*k-1)*nFr(n,k)/(k*nfr(n,k));
	//cout<<reval<<" ";
	return reval;
}	

template<class T>
double pdf(const double& x,const T& n,const double& t){
	double reval=0.0;
	double s=0.0;
	for(unsigned int k=2;k<=(unsigned int) n;k++){
		s+=exp(-nCr((long int)k,2)*t)*nCr((long int)k,2)*phi(x,n,k);
	}
	reval=-s/(1-x);
	return reval;
}

template<class T>
double expe_t(const double& x,const T& n){
	double s=0.0;
	double reval=0.0;
	for(unsigned int k=2;k<=(unsigned int) n;k++){
		s+=phi(x,n,k)/nCr((long int)k,2);
	}
	reval=-s/(1-x);
	return reval;
}

template<class T>
double cdf(const double& x, const T& n, const double& t){
	double s=0.0;
	double reval=1.0;
	for(unsigned int k=2;k<=(unsigned int) n;k++){
		s+=phi(x,n,k)*exp(-nCr((long int)k,2)*t);
	}
	reval+=s/(1-x);
	return reval;
}

template<class T>
double theta(const T& k,const double& t){
	double reval=(t+1.0/nCr((long int)k,2))*exp(-nCr((long int)k,2)*t);
	return reval;
}

template<class T>
double expe_loc(const double& x,const T& n, const double& t1, const double& t2){
	double reval=0.0;
	double s=0.0;
	for(unsigned int k=2;k<=(unsigned int) n;k++){
		s+=phi(x,n,k)*(theta(k,t2)-theta(k,t1));
	}
	reval=s/(1-x);
	return reval;
}

template<class T>
double expe_tml(const double& x,const T& n, const double& t1){
	double reval=0.0;
	double s=0.0;
	for(unsigned int k=2;k<=(unsigned int) n; k++){
		s+=phi(x,n,k)*(-theta(k,t1));
	}
	reval=s/(1-x);
	return reval;
}

template<class T>
double local_mean_p(const double& x,const T& n,const double& t1, const double& t2){
	double mu = cdf(x,n,t2)-cdf(x,n,t1);
	double reval=0.0;
	if(mu>=TINY)
		reval=expe_loc(x,n,t1,t2)/mu;
	else{
		cerr<<"Probability measure of the interval is not big enough!"<<endl;
		cout<<t1<<" "<<t2<<endl;
		exit(-1);
	}
	return reval;
}

template<class T>
double mean_cdf(const double* x, const int& size, const T& n, const double& t){
	double reval=cdf(x[0],n,t);
	for(unsigned int i=0;i<size;i++){
		reval+=cdf(x[i],n,t);
	}
	reval = reval/size;
	return reval;
}
#endif
