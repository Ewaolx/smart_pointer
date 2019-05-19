#include <iostream>

using namespace std;

class eg           // test class
{
public:
	int t;
	char *a;
	eg(int x,const char *ch)
	{
		int s = sizeof(ch);
		t = x;
		a = new char[s+1];
		int i = 0;
		for (i = 0; i < s; i++)
			a[i] = ch[i];
		a[i] = '\0';
	}
	eg(const eg* obj)    // deep copy
	{
		this->t = obj->t;
		int s = sizeof(obj->a);
		this->a = new char[s + 1];
		int i = 0;
		for (i = 0; i < s; i++)
			this->a[i] = obj->a[i];
		this->a[i] = '\0';
	}
	~eg()
	{
		cout << "Freeing the memory..." << endl;
		delete[] a;
		a = NULL;
	}
	void print()
	{
		cout << "t:" << t << endl;
		cout << "a:" << a << endl;
	}
};

class rf   // class for keeping the reference count for objects 
{
private:
	int count;
public:
	rf()
	{
		count = 0;
	}
	void add()
	{
		count += 1;
	}
	void rem()
	{
		count -= 1;
	}
	int get()
	{
		return count;
	}
};


template <class T>
class smp                  // smart pointer class
{
private:
	T* t;
	rf *r;
public:
	
	smp(T* t)
	{
		this->t = t;
		r = new rf();
		r->add();
		cout << "In create:" << r->get() << endl;
	}
	smp(const smp<T>& obj)
	{
	    //this->t = new eg(obj.t); //deep copy
		this->t = (obj.t);   // shallow copy
		this->r = obj.r;
		r->add();
		cout << "In copy:" << r->get() << endl;
	}
	T* operator ->()
	{
		return t;
	}
	~smp()
	{
		r->rem();
		if (r->get() == 0)  // all references down, free the memory
		{
			delete t;
			t = NULL;
		}
		this->check();
	}
	void check()
	{
		if (t == NULL)
			cout << "obj is NULL" << endl;
		else
			cout << "obj is not NULL" << endl;
	}
	void check_(smp<T>& s2)
	{
		if (this->t == s2.t)                  // should not be equal in case of deep copy
			cout << "objs are equal" << endl;
		else
			cout << "objs are not equal" << endl;
	}
};

int  main()
{  
	{
	 smp<eg>  s1(new eg(10,"Jil"));
     { 
		smp<eg> s2(s1);  
	 } // destroying s2
	}  // destroying s1
    return 0; 
}
