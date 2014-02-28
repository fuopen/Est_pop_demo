//#include"mat.h"
#include"Linear_eq.h"//"mat.h"
#include"allele_freq.h"
//#include"bs_fuc.h"
void print_star(cuin m,cuin n){
	for(uin j=0;j<m;j++){
		for(uin i=0;i<n;i++){
			cout<<"*";
		}
		cout<<endl;
	}
}
void print_and(cuin m,cuin n){
	for(uin j=0;j<m;j++){
		for(uin i=0;i<n;i++){
			cout<<"&";
		}
		cout<<endl;
	}
}
int main(int argc,char** argv){
	in devnm,sap_size;
	switch(argc){
	case 2:
		devnm = atoi(argv[1]);
		sap_size = 10;
		break;
	case 3:
		devnm = atoi(argv[2]);
		sap_size = atoi(argv[1]);
		break;
	default:
		devnm =10;
		sap_size =10;
		break;
	}
	fremat_generate fg(sap_size,devnm);
	fg.generate_mat();	
	solve_linear sleq;
	db d = 0.0;
	svac_i indx(devnm);
	for(int i=0;i<devnm;i++){
		indx[i]=i;
	}
	mat<double> mc(*(fg.generate_all_mat));
	//fg.generate_all_mat->_show();
	fg.show_fremat();
	//cout<<"****"<<endl;
	//cout<<endl;
	//mc._show();
	//cout<<"****"<<endl;
	//fg.expe_abs_time->show();
	//cout<<"\n****"<<endl;
	dbp suck = new db[devnm];
	for(int i=0;i<devnm;i++)
		suck[i]=1.0;
	svac_d s0(suck,devnm);
	mat<db> s1(s0);
	(mc*s1)._show();
	sleq.ludcmp(*(fg.generate_all_mat),indx,d);
	sleq.lubksb(*(fg.generate_all_mat),indx,*(fg.expe_abs_time));
	mat<double> ms2(*(fg.expe_abs_time));
	//(ms1)._show();
	//(mc*ms2)._show();
	cout<<"\n****"<<endl;
	fg.expe_abs_time->show();
	cout<<"\n****"<<endl;
	//(mc*ms2)._show();
	cout<<endl;
	return 0;
}
	
