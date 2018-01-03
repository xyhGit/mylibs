#include <list>
#include <functional>

template<typename _Tp, typename _Sequence = std::list<_Tp>, 
		typename _Compare = std::less<_Tp> >
class ordered_list {

public:
	typedef typename _Sequence::value_type					value_type;
	typedef typename _Sequence::iterator					iterator;
	typedef typename _Sequence::reference                 	reference;
	typedef typename _Sequence::const_reference           	const_reference;
	typedef typename _Sequence::size_type                 	size_type;
	typedef          _Sequence                            	container_type;

protected:
	_Sequence 	seqs;
	_Compare   	comp;

public:
	ordered_list(const _Compare& __x = _Compare(),
		     const _Sequence& __s = _Sequence())
      : seqs(__s), comp(__x){}

	bool empty()
	{
		return seqs.empty();
	}

	size_t size()
	{
		return seqs.size();
	}

	iterator insert(_Tp& obj)
	{
		seqs.push_back(obj);
		iterator it = seqs.end();
		--it;
		after_update(it);
		return it;
	}

	void evict(iterator it_obj)
	{
		seqs.erase(it_obj);
	}

	iterator front()
	{
		return seqs.begin();
	}

	void update(iterator it_obj)
	{
		if (it_obj == seqs.end())
			return;
		// move the @it_obj towards the head of the list
		if (it_obj != seqs.begin())
		{
			iterator curr = it_obj;
			iterator prev = --it_obj;
			while (!comp(*prev, *curr))
			{
				std::swap(*prev, *curr);
				if(prev == seqs.begin())
					break;
				--prev;
				--curr;
			}
		}
		// move the @it_obj towards the end of the list
		if (it_obj != seqs.end())
		{
			iterator curr = it_obj;
			iterator next = ++it_obj;
			while (next != seqs.end() && !comp(*curr, *next))
			{
				std::swap(*next, *curr);
				++next;
				++curr;
			}
		}
	}

	

	void for_each(std::function<void(_Tp &i)> func)
	{
		for( _Tp &i : seqs )
			func(i);
	}


};
//}
