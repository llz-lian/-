#pragma once
#include<bitset>
#include<vector>
#include<random>
#include<functional>
#include<math.h>
#include<map>
#include<algorithm>
#include<iostream>
#include  <memory>
#include<set>
#define DEBUG 0
const unsigned int bits = 30;

inline double targetFunc(double x)
{
	double res = 0;
	auto fun = [](double & x, int &j)->double { return j * cos((j + 1)*x + j); };
	for (int j = 1; j < 6; j++)
	{
		res += fun(x, j);
	}
	return res;
}

inline void changeBit(std::bitset<30> &bitset_a, std::bitset<30> &bitset_b, int pos)
{
	using bitset = std::bitset<30>;
	bitset a_tail(bitset_a.to_string(), pos, 30 - pos);
	bitset b_tail(bitset_b.to_string(), pos, 30 - pos);

	bitset_a ^= a_tail;
	bitset_b ^= b_tail;

	bitset_a |= b_tail;
	bitset_b |= a_tail;

}

inline long randGen()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long> u(LONG_MIN, LONG_MAX);
	return u(gen);
}

inline int randint()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> u(1, 10);
	return u(gen);
}


struct P
{
	std::bitset<30> p;
	double num = 0;
	double rel_num = 0;

	double to_double() {
		long long  p_num = p.to_ullong() * 20;
		num = p_num / 1073741824.0;
		num -= 10;
		return num;
	};
	P():num(0),rel_num(0) {

		long n = randGen();
#if DEBUG
		std::cout << n << std::endl;
#endif // DEBUG

		p = std::bitset<30>(n);
	};
	P(long i):p(i){};
	P(std::bitset<30> bitset):p(bitset) {};
	static bool cmp( P const* p1,  P const*p2)
	{
		return p1->rel_num > p2->rel_num;
	};
};
class Genetic {
private:
	using Group = std::vector<P*>;
	using Func = std::function<double(double)>;
	Group generation;//现代

	Group proliferate{};//子代 繁殖池
	Func func;//目标
	
	const int GROUP_SIZE = 10;
	const int HYBRID = 6;
	double group_rel_sum = 0;//适应总和
	std::map<double,double> best;//最优x
	double min_num = 15;

	void hybrid();//杂交
	void select();//选择下一代
	void addBest();//更新结果
	void nextGen();//生成下一代
	std::bitset <30> variation(std::bitset<30> d);//变异

	bool stop();//结束条件

	double best_num = 0;
	int best_cnt = 0;
	void restart();
public:
	
	void findResult();
	void showResult();//出结果
	inline void showGen() {
		for (P *p : generation)
		{
			std::cout << p->num << " ";
		}
		std::cout << std::endl;
	};


	Genetic(Func f);
	~Genetic();
};