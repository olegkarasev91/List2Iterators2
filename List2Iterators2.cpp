// List2.cpp 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
//#define DEBUG
class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size; // размер списка
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG

		}
		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{

		}
		~Iterator()
		{

		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG

			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	ConstReverseIterator crend()const
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;// Если список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		*/
		*this = other;// из конструктора копирования вызываем оператор присваивания
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
		cout << "\n--------------------------------------\n";
	}
	//Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	// Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//Когда в списке появляется первый элемент
			//он одновременно является и головой и хвостом
			Head = Tail = new Element(Data);
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size) {
			cout << "Error: Выход за пределы списка!" << endl;
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;

		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;

	}
	// Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	// Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << " Количество элементов списка: " << size << endl;
	}
	void print_reverse()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
	}
};
void print_list(const List& list)
{
	for (List::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
void reverse_print_list(const List& list)
{
	for (List::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
}
//#define BASE_CHECK


void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();
	cout << "\n--------------------------------------\n";
	/*list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.print_reverse();
#endif // BASE_CHECK
	List list = { 3, 5, 8, 13,21 };
	list.print();

	List list1;
	list1 = list;
	//list1.print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (List::ConstReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
	reverse_print_list(list1);
	print_list(list1);
}