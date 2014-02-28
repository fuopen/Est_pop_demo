#ifndef _ALLELE_FREQ_H_
#define _ALLELE_FREQ_H_
#include"bs_fuc.h"
#include"mat.h" 
class fremat_generate{
private:
	dbp coal_time;
	dbp coal_point;
	in nm_time_interval;
	in sap_size;
	dbp all_fre;
	//dbp mean_point;
	mat<db>* all_fre_mat; 
	mat<db>* mean_point;
public:
	fremat_generate(cuin&,cuin&);
	~fremat_generate();	
	mat<db>* generate_all_mat;
	svac_d* expe_abs_time;
	void generate_mat();
	void show_fremat();		
};
#endif
