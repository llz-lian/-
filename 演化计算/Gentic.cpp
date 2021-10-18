#include "Gentic.h"

void Genetic::hybrid()
{
	
	double pc = 0.7;//�ӽ�����
	int num_hybrid = 0.8*proliferate.size();//�ӽ�������
	std::vector<P*> selected;

	for (int i = 0; i < proliferate.size(); i++)
	{
		int randi = randint();
		if (randi >= 3)
		{
			selected.push_back(proliferate[i]);
		}
		if (selected.size() == 2)
		{
			//�ӽ�����
			auto bit_a = selected[0]->p;
			bit_a = variation(bit_a);
			auto bit_b = selected[1]->p;


			changeBit(bit_a, bit_b, randint() * 3);


			selected.pop_back();
			selected.pop_back();

			generation.push_back(new P(bit_a));
			generation.back()->rel_num =  func( generation.back()->to_double());
			generation.push_back(new P(bit_b));
			generation.back()->rel_num = func(generation.back()->to_double());
		}
	}
	std::sort(generation.begin(), generation.end(), P::cmp);
}

void Genetic::select()
{
	//����ǰ10
	int pop_num = generation.size() - GROUP_SIZE;
	while (pop_num-- > 0)
	{
		delete generation.back();
		generation.back() = nullptr;
		generation.pop_back();//й©��
	}
	for (int i = 0; i < proliferate.size(); i++)
	{
		if (proliferate[i] != nullptr)
		{
			delete proliferate[i];
			proliferate[i] = nullptr;
		}
	}
}

void Genetic::addBest()
{
	//generation[0], generation[1], generation[2];
	generation[0]->to_double();
	if (targetFunc(generation[0]->num) < -12)
	{
		best[generation[0]->num] = targetFunc(generation[0]->num);
	}
	if (best_num == generation[0]->num)
	{
		best_cnt++;
		if (best_cnt > 20)
		{
			restart();
			best_cnt = 0;
		}
	}
	else {
		best_num = generation[0]->num;
	}
}

void Genetic::nextGen()
{
	for (int i = 0; i < GROUP_SIZE; i++)
	{
		generation[i]->rel_num = func(generation[i]->to_double());
		group_rel_sum += generation[i]->rel_num;//������ֵ,׼��������һ��
	}
	addBest();//����Ŀǰ���Ž�
	for (int i = 0; i < GROUP_SIZE; i++)
	{
		//���������Ӧֵ
		double rel = generation[i]->rel_num / group_rel_sum;
		//������һ������
		int next_gen = floor(rel * GROUP_SIZE+0.01);
		//�����Ӵ���ֳ��
		for (int i = 0; i < next_gen; i++)
		{
			proliferate.push_back(new P(variation(generation[i]->p)));//�ڴ�й©
		}
	}
	hybrid();//�ӽ�
	select();//ѡ����һ��
	proliferate.clear();//���
	addBest();//�������Ž��
	group_rel_sum = 0;
}

std::bitset <30> Genetic::variation(std::bitset<30> d)
{
	auto is_var = [](){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> u(1, 100);
		return u(gen)<10;
	};
	for (int i = 0; i < 30; i++)
	{
		if (is_var())
		{
			d.set(i);
		}
	}
	std::bitset<30> new_bit = d;
	return new_bit;
}

void Genetic::restart()
{
	for (int i = 0; i < GROUP_SIZE; i++)
	{
		if (generation[i] != nullptr)
		{
			delete generation[i];
			generation[i] = nullptr;
		}
		generation[i] = new P();//���ɳ���
	}

}

void Genetic::findResult()
{
	while (true)
	{
		nextGen();
	}
}

void Genetic::showResult()
{

}

Genetic::Genetic(Func f):func(f)
{
	for (int i = 0; i < GROUP_SIZE; i++)
	{
		generation.push_back(new P());//���ɳ���
	}

}

Genetic::~Genetic()
{
	for (int i = 0; i < GROUP_SIZE; i++)
	{
		if (generation[i] != nullptr)
			delete generation[i];
	}
}
