#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//template<typename T>
//class AutoPtr
//{
//public:
//	AutoPtr()
//		:_ptr(NULL)
//	{}
//
//	AutoPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	~AutoPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = NULL;
//		}
//	}
//
//	AutoPtr<T>(AutoPtr<T>& ap)
//		: _ptr(ap._ptr)
//	{
//		ap._ptr = NULL;
//	}
//
//	AutoPtr<T>& operator = (AutoPtr<T>& ap)
//	{
//		if (this != &ap)
//		{
//			delete _ptr;
//			_ptr = ap._ptr;
//			ap._ptr = NULL;
//		}
//
//		return *this;
//	}
//
//
//	T& operator*()
//	{
//		return *_ptr;
//
//	}
//
//	T* GerPtr()
//	{
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};
//
//int main()
//{
//	AutoPtr<int> ap1=new int(1);
//	AutoPtr<int> ap2(ap1);
//	AutoPtr<int> ap3 = new int(3);
//	ap3 = ap2;
//	system("pause");
//	return 0;
//}

//template<class T>
//class scopedPtr
//{
//public:
//	scopedPtr()
//		:_ptr(NULL)
//	{}
//
//	scopedPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	~scopedPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = NULL;
//		}
//	}
//	
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	T* GetPtr()
//	{
//		return _ptr;
//	}
//
//protected: //����protected���Է�ֹʹ��������֮�ⶨ�忽�����������������غ���
//	scopedPtr<T>(const scopedPtr<T>& sp);		//����ʹ����ʹ�ÿ��������Է�ֹ����������ֻ����������
//	scopedPtr<T>& operator=(const scopedPtr<T>& sp);
//
//private:
//	T* _ptr;
//};
//
//int main()
//{
//	scopedPtr<int> sp1 = new int(1);
//	system("pause");
//	return 0;
//}

template<class T>
class SharePtr
{
public:
	SharePtr(T* ptr)
		:_ptr(ptr)
		, _pCount(new int(1))
	{}

	//SharePtr(Shar)
	//	:_ptr(sp._ptr)
	//{
	//	*_pCount = 1;
	//}

	~SharePtr()
	{
		if (_ptr)
		{
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
				_ptr = NULL;
				_pCount = NULL;
			}

			_ptr = NULL;
		}
	}

	SharePtr<T>(const SharePtr<T>& sp)
	{
		_ptr = sp._ptr;
		_pCount = sp._pCount;
		++(*_pCount);
	}

	SharePtr<T>& operator=(const SharePtr<T>& sp)
	{
		if (this != &sp)
		{
			if (--(*_pCount) == 0)	//����Ҫ�������˭��һ���߼���Ҫ�������
			{
				delete _ptr;
				delete _pCount;
				_ptr = NULL;
				_pCount = NULL;
			}

			_ptr = sp._ptr;
			_pCount = sp._pCount;
			++(*_pCount);
		}
		return *this;
	}

private:
	T* _ptr;
	int* _pCount;
};

int main()
{
	SharePtr<int> sp1 = new int(1);
	SharePtr<int> sp2(sp1);
	SharePtr<int> sp3 = new int(3);
	sp3 = sp1;
	system("pause");
	return 0;
}