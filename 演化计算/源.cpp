#include<math.h>
#include"Gentic.h"

double negSigmoid(double x)//relu?
{
	return 1 / (1 + pow(2.7182818, x));//f->[0,1]
}


double Fun(double x)
{
	double tag_num = targetFunc(x);
/*#if DEBUG
	std::cout<<x<<" " << tag_num<<std::endl;
#endif*/ // DEBUG 4.84375
	//4.86763		  -12.8561
	//4.84375		  -12.8382
	//4.85352		  -12.8676
	//-7.73438        -12.7628
	//-1.39849        -12.7562
	double tmp = negSigmoid(tag_num/2);//映射到0，1 值越小tmp越大



	return tmp;//tmp
}

double tagFun(double x)
{
	double tag_num = targetFunc(x);
	double tmp = pow(0.9, tag_num);
	return tmp / (2 + tmp);
}


int main()
{
	Genetic g(tagFun);
	g.findResult();
	return 0;
//4.86763		  -12.8561
//4.84375		  -12.8382
//4.85352		  -12.8676
//-7.73438        -12.7628
//-1.39849        -12.7562
}