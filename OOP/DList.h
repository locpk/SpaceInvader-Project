#pragma once

#define size_ int
#define ts template<typename stuff>


template<class stuff = int>
class DList
{
private:
	struct node
	{
		stuff data;
		node* p, *n;
		node(stuff _data, node* _p) : data(_data), p(_p), n(NULL) {}
	};

	node* first, *last;
	size_ size;
	

public:
	DList() : size(0), first(NULL), last(NULL) {}
	~DList();
	DList(const DList<stuff> & _obj);
	DList<stuff>& operator=(const DList<stuff> & _obj);

	void clear();
	void push_back(stuff _data);
	void push_front(stuff _data);
	bool erase(int _index);
	stuff& operator[](int index);
	stuff const& operator[](int index) const;

	size_ Size() const { return size; }

};

ts
DList<stuff>::DList(const DList<stuff> & _obj)
{
	first = last = NULL;
	size = 0;
	int i = 0;
	for (; i < _obj.size; i++)
	{
		push_back(_obj[i]);
	}

}

ts
DList<stuff>& DList<stuff>::operator=(const DList<stuff> & _obj)
{
	if (this == _obj)
		return *this;
	first = last = NULL;
	size = 0;
	int i = 0;
	for (; i < _obj.size; i++)
	{
		push_back(_obj[i]);
	}


}


ts
DList<stuff>::~DList()
{
	node* temp = first;

	while (first)
	{
		first = first->n;
		delete temp;
		temp = first;
	}
}

ts
void DList<stuff>::clear()
{
	DList<stuff>::~DList();
	first = last = nullptr;
	size = 0;
}

ts
void DList<stuff>::push_front(stuff _data)
{
	node* temp = new node(_data, NULL);

	if (first)
	{
		temp->n = first;
		first->p = temp;
	}
		
	else
		last = temp;
	first = temp;
	++size;
}

ts
void DList<stuff>::push_back(stuff _data)
{
	node* temp = new node(_data, last);

	if (last)
		last->n = temp;
	else
		first = temp;

	last = temp;

	++size;
}

ts
bool DList<stuff>::erase(int _index)
{
	if (_index >= size)
		return false;
	node* temp;
	if (_index == 0 && first == last)
	{
		delete first;
		first = last = nullptr;
		--size;
		return true;
	}
	if (_index == size - 1) //if index is last
	{
		temp = last;
		temp->p->n = NULL;
		last = temp->p;
		delete temp;
		--size;
		return true;
	}
	temp = first;
	if (_index == 0) //if index is the first.
	{
		temp->n->p = NULL;
		first = temp->n;
		delete temp;
		--size;
		return true;
	}
	//
	
	int i = 0;
	for (; i < _index; i++)
	{
		temp = temp->n;
	}
	temp->p->n = temp->n;
	temp->n->p = temp->p;
	delete temp;
	--size;
	return true;
}

ts
stuff& DList<stuff>::operator[](int index)
{
	node* temp = first;
	int i = 0;
	for (; i < index; ++i)
		temp = temp->n;

	return temp->data;
}

ts
stuff const& DList<stuff>::operator[](int index) const
{
	node* temp = first;
	int i = 0;
	for (; i < index; ++i)
		temp = temp->n;

	return temp->data;
}
