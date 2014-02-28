#include"Linear_eq.h"
#include<iostream>
using namespace std;

void solve_linear::ludcmp(mat_db& a,svac_i& indx,db& d){
	cdb TINY = 1.0e-20;
	in i,imax,j,k;
	db big,dum,sum,temp;
	
	in n=a._row();
	svac_d vv(n);
	d = 1.0;
	//cout<<"The first step"<<endl;
	for(i=0;i<n;i++){
		big = 0.0;
		for(j=0;j<n;j++)
			if((temp=fabs(a[i][j]))>big){
				big = temp;
			}
		if(big==0.0){
			cerr<<"singular matrix in routine ludcmp"<<endl;
			exit(1);
		}
		vv[i]=1.0/big;
	}
	//cout<<"The second step"<<endl;
	for (j=0;j<n;j++){//Grout methods colunm loop
		for(i=0;i<j;i++){
			sum = a[i][j];
			for(k=0;k<i;k++){
				sum -= a[i][k]*a[k][j];
			}
			a[i][j] = sum;
		}
		//cout<<"1"<<endl;
		big=0.0;
		for(i=j;i<n;i++){
			sum = a[i][j];
			for(k=0;k<j;k++){ 
				sum-= a[i][k]*a[k][j];
			}
			a[i][j] = sum;
			if((dum=vv[i]*fabs(sum))>=big){
				big  = dum;
				imax = i;
			}
		}
		//cout<<"2"<<endl;
		if(j!= imax){
			for(k=0;k<n;k++){
				dum = a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k] = dum;
			}
			d = -d;
			vv[imax]=vv[j];
		}
		//cout<<"3"<<endl;
		indx[j] = imax;
		if(a[j][j]==0.0) a[j][j]=TINY;
		if(j!=n-1){
			dum = 1.0/(a[j][j]);
			for(i=j+1;i<n;i++){
				a[i][j] *= dum;
			}
		}
	}
	//cout<<"step 3"<<endl;
}

void solve_linear::lubksb(mat_db& a,svac_i& indx,svac_d& b){
	in i, ii=0,ip,j;
	db sum;
	
	in n = a._row();
	for(i=0;i<n;i++){
		ip = indx[i];
		sum = b[ip];
		b[ip] = b[i];
		if(ii !=0){
			for(j=ii-1;j<i;j++){
				sum -= a[i][j]*b[j];
			}
		}
		else if(sum!=0.0){
			ii = i+1;
		}
		b[i] = sum;
	}
	for(i = n-1;i>=0;i--){
		sum = b[i];
		for(j=i+1;j<n;j++){
			sum -= a[i][j]*b[j];
		}
		b[i] = sum/a[i][i];
	}
}

void solve_linear::mat_inverse(mat_db& a,svac_i& indx,db& d,svac_d& col){
	in i,j;
	ludcmp(a,indx,d);
	
	in n = a._row();
	mat_db* y = new mat_db(n);
	
	for(j=0;j<n;j++){
		for(i=0;i<n;i++){
			col[i]=0.0;
		}
		col[j]=1.0;
		lubksb(a,indx,col);
		for(i=0;i<n;i++){
			(*y)[i][j] = col[i];
		}
	}
	y->_show();
	//delete y;
}
						
	
