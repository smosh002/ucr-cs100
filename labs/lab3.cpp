#include <iostream>
#include <math.h>
#include <vector>
#include <list>

using namespace std;


class Base
{
	public:
		/* Constructors */
		Base() { };

		/* Pure Virtual Functions */
		virtual double evaluate() = 0;
};

class Op : public Base
{
	public:
		double value;
		void setValue(double val)
		{
			value = val;
		}
	double evaluate()
	{
		return value;
	}
};

class Comp1 : public Base
{
	protected:
		Base* child;
	public:
		void setChild(Base* val)
		{
			child = val;
		}
};

class Comp2 : public Base
{
	protected:
		Base* left;
		Base* right;
	public:
		void setLeft(Base* val)
		{
			left = val;
		}
		void setRight(Base* val)
		{
			right = val;
		}
};

class Sqr: public Comp1
{
	public:
		double evaluate()
		{
			return sqrt(child->evaluate());
		}
};

class Add : public Comp2
{
	double evaluate()
	{
		double d1 = left->evaluate();
		double d2 = right->evaluate();
		return d1 + d2;
	}
};

class Sub : public Comp2
{
	double evaluate()
	{
		double d1 = left->evaluate();
		double d2 = right->evaluate();
		return d1 - d2;
	}
};

class Mult : public Comp2
{
	double evaluate()
	{
		double d1 = left->evaluate();
		double d2 = right->evaluate();
		return d1*d2;
	}
};

class Div : public Comp2
{
	double evaluate()
	{
		double d1 = left->evaluate();
		double d2 = right->evaluate();
		if (d2 == 0)
		{
			cout << endl <<  "Cannot divide by zero" << endl;
			return 0;
		} else
		{
			return d1/d2;
		}
	}
};

class Sort;

class Container
{
	protected:
		Sort* sort_function;
	public:
		Container() : sort_function(NULL){};
		Container(Sort* function) : sort_function(function){};

		void set_sort_function(Sort* sort_function);

		virtual void add_element(Base* element) = 0;
		virtual void print() = 0;
		virtual void sort() = 0;
		virtual void swap(int i, int j) = 0;
		virtual Base* at(int i) = 0;
		virtual int size() = 0;
};

void Container::set_sort_function(Sort* sort_function)
{
	this->sort_function = sort_function;
}

class VecContainer: public Container
{
	public:
		vector<Base*> tVec;

		void add_element(Base* item)
		{
			tVec.push_back(item);
		}

		void print()
		{
			for(int i = 0; i < tVec.size(); i++)
			{
				cout << "Tree #" << i << " evaluates to: " << tVec.at(i)->evaluate() << endl <<  endl;
			}
		}

		void sort();

		Base* at(int i)
		{
			if ((unsigned int)i >= tVec.size() || i < 0)
			{
				cout << "OUT OF BOUNDS" << endl;
				return NULL;
			}
			return tVec.at(i);
		}

		void swap(int a, int b)
		{
			if ((unsigned int)a >= tVec.size() || (unsigned int)b >= tVec.size() || a < 0 || b < 0)
			{
				cout << "OUT OF BOUNDS" << endl;
			}

			Base* tempSwap;
			tempSwap = tVec.at(a);
			tVec.at(a) = tVec.at(b);
			tVec.at(b) = tempSwap;
		}

		int size()
		{
			return (int)tVec.size();
		}
};

class ListContainer: public Container
{
	public:
		list<Base*> tList;
		
		void add_element(Base* item)
		{
			tList.push_back(item);
		}

		void print()
		{
			int k = 0;
			for (list<Base*>::iterator i = tList.begin(); i != tList.end(); i++)
			{
				k++;
				cout << "Tree #" << k << " evaluates to: " << (*i)->evaluate() << endl << endl;
			}
		}

		void sort();

		void swap(int a, int b)
		{
			if((unsigned int)a >= tList.size() || (unsigned int)b >= tList.size() || a < 0 || b < 0 )
			{
				cout << "OUT OF BOUNDS" << endl;
				return;
			}

			list<Base*>::iterator temp1 = tList.begin();
			list<Base*>::iterator temp2 = tList.begin();

			for (int i = 0; i < b; i++)
			{
				temp1++;
			}

			for (int i = 0; i < a; i++)
			{
				temp2++;
			}

			Base* temp3 = (*temp1);
			(*temp1) = (*temp2);
			(*temp2) = temp3;
		}

		Base* at(int i)
		{
			if((unsigned int)i >= tList.size() || i < 0)
			{
				cout << "OUT OF BOUNDS" << endl;
				return NULL;
			}

			list<Base*>::iterator it = tList.begin();
			for (int k = 0; k < i; k++)
			{
				it++;
			}

			return (*it);
		}

		int size()
		{
			return (int)tList.size();
		}
};

class Sort
{
	public:
		Sort();
		virtual void sort(Container* container) = 0;
};

Sort::Sort(){}

class SelectionSort: public Sort
{
	public:
		void sort(Container* container)
		{
			int smallest = 0;
			for(int i = container->size() - 1; i > 0; i--)
			{
				smallest = 0;
				for (int k = 1; k <= i; k++)
				{
					if ((container->at(k)->evaluate()) < (container->at(smallest)->evaluate()))
					{
						smallest = k;
					}
				}
				container->swap(smallest, i);
			}
		}
};

class BubbleSort: public Sort
{
	public:
		void sort(Container* container)
		{
			int flag = 1;
			for (int i = 0; (i <= container->size()) && flag; i++)
			{
				flag = 0;
				for (int k = 0; k < container->size() - 1; k++)
				{
					if ((container->at(k + 1)->evaluate()) > (container->at(k)->evaluate()))
					{
						container->swap(k, k + 1);
						flag = 1;
					}
				}
			}
		}
};

void ListContainer::sort()
{
	sort_function->sort(this);
}

void VecContainer::sort()
{
	sort_function->sort(this);
}

int main()
{
	Add addTest;
	Sub subTest;
	Mult multTest;
	Div divTest;
	Sqr sqrTest;

	Op testNum1;
	testNum1.setValue(1);
	Op testNum2;
	testNum2.setValue(-1);
	Op testNum3;
	testNum3.setValue(0);
	Op testNum4;
	testNum4.setValue(1.5);
	Op testNum5;
	testNum5.setValue(99);
	Op testNum6;
	testNum6.setValue(9);
	Op testNum7;
	testNum7.setValue(2);

	BubbleSort BSort;
	SelectionSort SSort;

	addTest.setLeft(&testNum1);		//1 + 1 = 2
	addTest.setRight(&testNum1);	

	subTest.setLeft(&testNum1);		//1 - 1 = 0
	subTest.setRight(&testNum1);

	multTest.setLeft(&testNum1);	//1 * 1.5 = 1.5
	multTest.setRight(&testNum4);

	divTest.setLeft(&testNum5);		//99 / 9 = 11
	divTest.setRight(&testNum6);	

	sqrTest.setChild(&testNum6);	//9^-1 = 3

	cout << "Vector Container" <<  endl << endl;
	
	VecContainer BSortCont;

	BSortCont.add_element(&addTest);
	BSortCont.add_element(&subTest);
	BSortCont.add_element(&multTest);
	BSortCont.add_element(&divTest);
	BSortCont.add_element(&sqrTest);

	BSortCont.set_sort_function(&BSort);
	BSortCont.sort();

	cout << "BUBBLE SORT:" << endl;

	BSortCont.print();
	
	VecContainer SSortCont;

	SSortCont.add_element(&addTest);
	SSortCont.add_element(&subTest);
	SSortCont.add_element(&multTest);
	SSortCont.add_element(&divTest);
	SSortCont.add_element(&sqrTest);

	SSortCont.set_sort_function(&SSort);
	SSortCont.sort();

	cout << "SELECTION SORT:" << endl;

	SSortCont.print();
	
	ListContainer BSortList;
	
	BSortList.add_element(&addTest);
	BSortList.add_element(&subTest);
	BSortList.add_element(&multTest);
	BSortList.add_element(&divTest);
	BSortList.add_element(&sqrTest);

	BSortList.set_sort_function(&BSort);
	BSortList.sort();

	cout << "BUBBLE SORT:" << endl;

	BSortList.print();

	VecContainer SSortList;

	SSortList.add_element(&addTest);
	SSortList.add_element(&subTest);
	SSortList.add_element(&multTest);
	SSortList.add_element(&divTest);
	SSortList.add_element(&sqrTest);

	SSortList.set_sort_function(&SSort);
	SSortList.sort();

	cout << "SELECTION SORT:" << endl;

	SSortList.print();



	return 0;
}
