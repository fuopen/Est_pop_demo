#ifndef _LINEAR_EQ_H_
#define _LINEAR_EQ_H_
#include"mat.h"
#include<cmath>
class solve_linear{
public:
	//void test(mat_db&);
	void ludcmp(mat_db&,svac_i&,db&);
	void lubksb(mat_db&,svac_i&,svac_d&);
	void mat_inverse(mat_db&,svac_i&,db&,svac_d&);
};
#endif
