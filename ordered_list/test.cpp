#include "ordered_list.hpp"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Obj
{
public:
	Obj(int &a):value(a){}
	int value;
	bool operator < (const Obj& rhs) const
	{
		return value < rhs.value;
	}

	friend std::ostream& operator << (std::ostream &out, const Obj& obj)
	{
		out << obj.value;
		return out;
	}
};
class cmp
{
public:
bool operator () (const Obj& lhs, const Obj& rhs)
	{
		return lhs.value < rhs.value;
	}
};

void print(Obj& obj)
{
	cout << obj << " ";
}

void test(ordered_list<Obj, std::list<Obj>, std::less<Obj>>& ol)
{
	ol.for_each(print);
	cout << endl;
}

int main()
{
    ordered_list<Obj, std::list<Obj>, std::less<Obj>> ol;

    char opt;
    while (1)
    {
    	cin >> opt;
    	int idx = 0, value = 0;
    	switch (opt)
    	{
    	case 'i':
    		cin >> value;
    		ol.insert(value);
    		break;
    	case 'u':
    		cin >> idx >> value;
    		ol.insert(value);
    		break;
    	case 'd':
    		cin >> idx >> value;
    		ol.insert(value);
    		break;
    	}
    }

	vector<int> a{3,1,7,2,9};
	vector<Obj> b;
	int j = 0;
	for ( int &i:a )
	{
		b.push_back(i);
		ol.insert(b[j++]);
		test(ol);
	}

	test(ol);
    
    while(!ol.empty())
    {
        cout << ol.front()->value << " ";
        ol.evict(ol.front());
		test(ol);
    }
    test(ol);
    return 0;
}
