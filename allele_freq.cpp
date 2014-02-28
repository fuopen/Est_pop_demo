#include"allele_freq.h"
#include"mymath.h"
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<iostream>
#define TMAX 10
using namespace std;

fremat_generate::fremat_generate(cuin& sap_sz,cuin& dev_nm):sap_size(sap_sz),nm_time_interval(dev_nm),all_fre_mat(new mat<db>(dev_nm)),mean_point(new mat<db>(dev_nm)),generate_all_mat(new mat<db>(dev_nm)),expe_abs_time(new svac_d(dev_nm)){
	coal_time = new db[dev_nm];
	coal_point= new db[dev_nm+1];
	//mean_point= new db[dev_nm];
	all_fre = new db[dev_nm];
	db s = (db) dev_nm;
	db delta = (double) TMAX/s;
	for(in i=0;i<dev_nm;i++){		
		coal_time[i] = delta;
		all_fre[i] = (i+1.00)/(s+0.00001);
	}
	for(in i = 0;i<=dev_nm;i++){
		if(i==0){
			coal_point[i]=0.0;
		}
		else{
			coal_point[i]=coal_point[i-1]+delta;
		}
		//cout<<i<<" : "<<coal_point[i]<<endl;
	}
	//cout<<endl;
	/*for(in i = 0;i<dev_nm;i++){
		mean_point[i]=local_mean_p(all_fre[i],sap_sz,coal_point[i],coal_point[i+1]);
		//cout<<i<<" : "<<local_mean_p(all_fre[i],sap_sz,coal_point[i],coal_point[i+1])<<" ";
		mean_point[i]=(coal_point[i+1]-mean_point[i])/delta;
		cout<<"["<<coal_point[i]<<", "<<coal_point[i+1]<<"]: "<<local_mean_p(all_fre[i],sap_sz,coal_point[i],coal_point[i+1])<<" "<<mean_point[i]<<endl;
		cout<<"************"<<endl;
	}*/
	db sasz = (db) sap_sz;
	for(uin i=0;i<dev_nm;i++){
		for(uin j=0;j<dev_nm;j++){
				(*all_fre_mat)[i][j] = /*cdf(all_fre[i],(lin) sasz,coal_point[j+1])-*/cdf(all_fre[i],(lin) sasz,coal_point[j]);
				//cout<<(*all_fre_mat)[i][j]<<" "<<endl;
				//cout
		}
	}
	//cout<<"construtor funtion finish!"<<endl;
	db cnm1 = 0.0, cnm2 = 0.0;
	for(int k=0;k<dev_nm;k++){
		for(int i=0;i<dev_nm;i++){
			(*mean_point)[k][i]=local_mean_p(all_fre[k],sap_sz,coal_point[i],coal_point[i+1]);
			(*mean_point)[k][i]=(coal_point[i+1]-(*mean_point)[k][i])/delta;
			cnm1 += (coal_point[i+1]-(*mean_point)[k][i]*delta)*(cdf(all_fre[k],sasz,coal_point[i+1])-cdf(all_fre[k],sasz,coal_point[i]));
			cnm2 += (1-(*mean_point)[k][i]*cdf(all_fre[k],sasz,coal_point[i+1])-(1-(*mean_point)[k][i])*cdf(all_fre[k],sasz,coal_point[i]))*delta;
		}
		//cout<<"when allele frequency is: "<<all_fre[k]<<endl;
		//cout<<"caonima 1 is : "<< cnm1<<endl;
		//cout<<"caonima 2 is : "<< cnm2<<endl;
		//cout<<"caonima 3 is : "<<expe_t(all_fre[k],sasz)<<endl;
		cnm1 =0.0;
		cnm2 =0.0;
	}
}
fremat_generate::~fremat_generate(){
	delete all_fre_mat;
	delete generate_all_mat;
	delete expe_abs_time;
	delete mean_point;
	delete[] coal_time;
	delete[] coal_point;
	delete[] all_fre;
	all_fre_mat = NULL;
	generate_all_mat = NULL;
	expe_abs_time = NULL;
	coal_time = NULL;
	coal_point = NULL;
	all_fre = NULL;
	mean_point = NULL;
}

void fremat_generate::generate_mat(){
	for(uin i=0;i<nm_time_interval;i++){
		for(uin j=0;j<nm_time_interval;j++){
			(*generate_all_mat)[i][j] = (1-cdf(all_fre[i],(lin) sap_size,coal_point[j])*(1-(*mean_point)[i][j])-cdf(all_fre[i],(lin) sap_size,coal_point[j+1])*(*mean_point)[i][j])*coal_time[j];
		}
		(*expe_abs_time)[i] = expe_t(all_fre[i],(lin) sap_size)-expe_tml(all_fre[i],(lin) sap_size,coal_point[nm_time_interval]);
	}
	//cout<<"funciton 2 finished!"<<endl;
}

void fremat_generate::show_fremat(){
	all_fre_mat->_show();
	cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	cout<<"************************************"<<endl;
	generate_all_mat->_show();
}
