#include <iostream>
#include <fstream>
#include <string>
#include "HugeInt.h"

using namespace std;

HugeInt::HugeInt()
{
	this->sign = false;
	this->size = 0;
	this->decimal = 1;
	this->ds = nullptr;
}

HugeInt::HugeInt(ifstream& fin)
{

	string s;
	fin.ignore();
	char c = fin.peek();
	if (fin.peek() == '-')
	{
		fin.ignore();
		this->sign = true;
	}
	else if (fin.peek() == '+' || fin.peek() == ' ' || fin.peek() == '\n' || fin.peek() == '\t')
	{
		fin.ignore();
	}

	fin >> s;
	this->size = s.length();
	this->ds = new int[this->size];

	SetHIs(s);

}

HugeInt::HugeInt(const HugeInt& H2)
{

	this->sign = H2.sign;
	this->size = H2.size;
	this->decimal = H2.decimal;
	this->ds = new int[this->size];

	Initialize();

	for (int i = 0; i < this->size; i++)
		this->ds[i] = H2.ds[i];

}

HugeInt::HugeInt(int num)
{

	int count = getLengthInt(num);

	if (num < 0)
		this->sign = true;

	this->decimal = 1;
	this->size = count;
	this->ds = new int[this->size];

	this->Initialize();

	int i = 0;

	while (num != 0)
	{
		this->ds[i] = num % 10;
		num /= 10;
		i++;
	}

}

char* HugeInt::CopyCharPtr(const char* ptr)
{

	int length = 0;

	for (int i = 0; ptr[i] != '\0'; i++)
		length++;

	char* copy = new char[length];

	InitializeCharPtr(copy, length);

	for (int i = 0; i < length; i++)
		copy[i] = ptr[i];

	return copy;

}

void HugeInt::ShiftLeftChar(char* ptr)
{

	int length = 0;

	for (int i = 0; ptr[i] != '\0'; i++)
		length++;

	for (int i = 0; i < length; i++)
		ptr[i] = ptr[i + 1];

}

void HugeInt::ShiftLeftInt(int* ptr)
{

	int length = 0;

	for (int i = 0; ptr[i] != '\0'; i++)
		length++;

	for (int i = 0; i < length; i++)
		ptr[i] = ptr[i + 1];

}

HugeInt::HugeInt(const char* ptr)
{
	int i = 0;
	char* copy = nullptr;

	if (ptr[0] == '-')
	{
		this->sign = true;
		i++;
		copy = CopyCharPtr(ptr);
		ShiftLeftChar(copy);
	}
	else if (ptr[0] == '+')
	{
		i++;
		copy = CopyCharPtr(ptr);
		ShiftLeftChar(copy);
	}
	else
	{
		copy = CopyCharPtr(ptr);
	}

	int count = 0;



	for (i = 0; copy[i] != '\0'; i++)
		count++;

	this->size = count;
	this->ds = new int[this->size];

	Initialize();

	for (int i = 0, j = this->size - 1; i < this->size; i++, j--)
		this->ds[i] = copy[j] - '0';

}

void HugeInt::Initialize()
{

	for (int i = 0; i < this->size; i++)
		this->ds[i] = 0;

	this->ds[this->size] = '\0';

}

void InitializeIntPtr(int* ptr, int length)
{

	for (int i = 0; i < length; i++)
		ptr[i] = 0;

	ptr[length] = '\0';

}

void HugeInt::InitializeCharPtr(char* ptr, int length)
{

	for (int i = 0; i < length; i++)
		ptr[i] = 0;

	ptr[length] = '\0';

}

void HugeInt::SetHIs(string s)
{

	Initialize();

	for (int i = 0, j = size - 1; i < this->size; i++, j--)
	{
		if (s[j] == '.')
			this->decimal = s[j];
		else
			this->ds[i] = s[j] - '0';
	}

}

void HugeInt::RegrowIntArr(int* arr, int size)
{

	int* temp = nullptr;

	temp = arr;

	arr = new int[size];

	for (int i = 0; i < size - 1; i++)
		arr[i] = temp[i];

}

int HugeInt::getLengthInt(int num)
{
	int count = 0;
	int temp = num;

	if (temp == 0)
	{
		count = 1;
		return count;
	}

	while (temp != 0)
	{
		temp /= 10;
		count++;
	}

	return count;
}

int HugeInt::Atoi()
{

	int r = 0;

	for (int i = 0; i < this->size; i++)
	{
		r = r * 10 + this->ds[i] - '0';
	}

	return r;

}

istream& operator>>(istream& CIN, HugeInt& H1)
{

	string s;
	cin >> s;
	H1.size = s.length();
	H1.ds = new int[H1.size];

	H1.SetHIs(s);

	return CIN;

}

int HugeInt::getDec()
{

	return this->decimal;

}

ostream& operator<<(ostream& COUT, HugeInt& H1)
{

	if (H1.sign)
		cout << '-';

	for (int i = H1.size - 1; i >= 0; i--)
	{
		if (i == H1.getDec())
			COUT << '.';
		else
			COUT << H1[i];
	}

	return COUT;

}

const void HugeInt::operator=(const HugeInt& H2)
{

	this->sign = H2.sign;
	this->size = H2.size;
	this->ds = new int[this->size];

	for (int i = 0; i < this->size; i++)
		this->ds[i] = H2.ds[i];

}

const void HugeInt::operator=(int num)
{

	this->size = 1;
	this->ds = new int[this->size];

	while (num != 0)
	{
		this->ds[this->size - 1] = num % 10;
		num /= 10;
		this->size++;
		RegrowIntArr(this->ds, this->size);
	}

	this->size--;
	this->ds[this->size] = '\0';

}

const void HugeInt::operator=(const char* ptr)
{

	int count = 0;

	for (int i = 0; ptr[i] != '\0'; i++)
		count++;

	this->size = count;
	this->ds = new int[this->size];

	Initialize();

	for (int i = 0, j = size - 1; i < this->size; i++, j--)
		this->ds[i] = ptr[j] - '0';

}

bool HugeInt::operator==(const HugeInt& H2)const
{


	if (this->sign != H2.sign)
		return 0;
	else if (this->size > H2.size)
		return 0;
	else if (this->size < H2.size)
		return 0;
	else if (this->size == H2.size)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->ds[i] != H2.ds[i])
				return 0;
		}
	}

	return 1;

}

bool HugeInt::operator!=(const HugeInt& H2)const
{

	if (this->sign != H2.sign)
		return 1;
	else if (this->size > H2.size)
		return 1;
	else if (this->size < H2.size)
		return 1;
	else if (this->size == H2.size)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->ds[i] != H2.ds[i])
				return 1;
		}
	}

	return 0;

}

bool HugeInt::operator<(const HugeInt& H2)const
{

	bool flag = 1;

	if (!this->sign == !H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] >= H2.ds[i])
				{
					flag = 0;
					break;
				}
				
			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size > H2.size)
			return 0;
		else
			return 1;
	}

	else if ((!this->sign && H2.sign) && (this->ds[0] != 0))
		return 0;

	else if (this->sign == H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] >= H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size > H2.size)
			return 1;
		else
			return 0;
	}

	else
		return 1;

}

bool HugeInt::operator<=(const HugeInt& H2)const
{

	bool flag = 1;

	if (!this->sign == !H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] > H2.ds[i])
				{
					flag = 0;
					break;
				}
				return 1;

			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size > H2.size)
			return 0;
		else
			return 1;
	}

	else if (!this->sign && H2.sign)
		return 0;

	else if ((this->sign && !H2.sign) && (this->ds[0] != 0))
		return 0;

	else if (this->sign == H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] > H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size > H2.size)
			return 1;
		else
			return 0;
	}

	else
		return 1;

}

bool HugeInt::operator>(const HugeInt& H2)const
{

	bool flag = 1;

	if (!this->sign == !H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] < H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 1;

			return 0;
		}
		else if (this->size < H2.size)
			return 0;
		else
			return 1;
	}

	else if ((!this->sign && H2.sign) && (this->ds[0] != 0))
		return 1;

	else if ((this->sign && !H2.sign) && (this->ds[0] != 0))
		return 0;

	else if (this->sign == H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] <= H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size < H2.size)
			return 1;
		else
			return 0;
	}

	else
		return 1;

}

bool HugeInt::operator>=(const HugeInt& H2)const
{

	bool flag = 1;

	if (!this->sign == !H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] >= H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 1;

			return 0;
		}
		else if (this->size < H2.size)
			return 0;
		else
			return 1;
	}

	else if ((!this->sign && H2.sign) && (this->ds[0] != 0))
		return 0;

	else if (this->sign == H2.sign)
	{
		if (this->size == H2.size)
		{
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (this->ds[i] >= H2.ds[i])
				{
					flag = 0;
					break;
				}

			}
			if (!flag)
				return 0;

			return 1;
		}
		else if (this->size < H2.size)
			return 1;
		else
			return 0;
	}

	else
		return 1;

}

HugeInt& HugeInt::operator++()
{

	this->ds[0] += 1;
	int carry = this->ds[0] / 10;
	this->ds[0] = this->ds[0] % 10;

	for (int i = 1; i < this->size; i++)
	{
		if (carry == 1)
		{
			this->ds[i] += 1;
			carry = this->ds[i] / 10;
			this->ds[i] = this->ds[i] % 10;
		}
	}
	if (carry == 1)
	{
		this->ds[this->size] = 1;
		this->size++;
		this->ds[this->size] = '\0';
	}

	return *this;

}

const HugeInt HugeInt::operator++(int)
{

	this->ds[0] += 1;
	int carry = this->ds[0] / 10;
	this->ds[0] = this->ds[0] % 10;

	for (int i = 1; i < this->size; i++)
	{
		if (carry == 1)
		{
			this->ds[i] += 1;
			carry = this->ds[i] / 10;
			this->ds[i] = this->ds[i] % 10;
		}
	}
	if (carry == 1)
	{
		this->ds[this->size] = 1;
		this->size++;
		this->ds[this->size] = '\0';
	}

	return *this;

}

HugeInt& HugeInt::operator--()
{

	this->ds[0] -= 1;
	int borrow = this->ds[0] / 10;
	this->ds[0] = this->ds[0] % 10;

	for (int i = 1; i < this->size; i++)
	{
		if (borrow == 1)
		{
			this->ds[i] -= 1;
			borrow = this->ds[i] / 10;
			this->ds[i] = this->ds[i] % 10;
		}
	}
	if (borrow == 1)
	{
		this->ds[this->size] = 1;
		this->size++;
		this->ds[this->size] = '\0';
	}

	return *this;

}

const HugeInt HugeInt::operator--(int)
{

	this->ds[0] -= 1;
	int borrow = this->ds[0] / 10;
	this->ds[0] = this->ds[0] % 10;

	for (int i = 1; i < this->size; i++)
	{
		if (borrow == 1)
		{
			this->ds[i] -= 1;
			borrow = this->ds[i] / 10;
			this->ds[i] = this->ds[i] % 10;
		}
	}
	if (borrow == 1)
	{
		this->ds[this->size] = 1;
		this->size++;
		this->ds[this->size] = '\0';
	}

	return *this;

}

void HugeInt::AssignPositive()
{
	for (int i = 0; i < this->size; i++)
		this->ds[i] *= -1;
}

void HugeInt::AssignNegative()
{
	for (int i = 0; i < this->size; i++)
		this->ds[i] *= -1;
}

void HugeInt::CheckIfZero()
{

	for (int i = 0; i < this->size; i++)
	{
		if (this->ds[i] != 0 && this->ds[i + 1] != 0)
		{
			return;
		}
	}

	this->sign = false;
	this->size = 1;
	this->ds[1] = '\0';
}

void HugeInt::Trim()
{

	while (this->ds[this->size - 1] == 0)
	{
		this->size--;
	}

	this->ds[this->size] = '\0';

}

int HugeInt::getSize()
{

	return this->size;

}

HugeInt HugeInt::Add(const HugeInt& H2)const
{

	int zero = 0;

	if (*this == zero && H2 == zero)
		return zero;
	else if (*this == H2 && !this->sign && H2.sign)
		return zero;
	else if (*this == H2 && this->sign && !H2.sign)
		return zero;

	HugeInt Sum;

	int carry = 0;

	if (this->sign && H2.sign)
		Sum.size = this->size + 1;
	else
		Sum.size = H2.size + 1;

	Sum.ds = new int[Sum.size];
	Sum.Initialize();

	for (int i = 0; i < Sum.size; i++)
	{
		Sum.ds[i] = ((*this)[i] + H2[i] + carry) % 10;
		carry = ((*this)[i] + H2[i] + carry) / 10;
		/*cout << "num1: " << num1[i] << endl;
		cout << "num2: " << num2[i] << endl;
		cout << "sum: " << Sum[i] << endl;*/
	}
	Sum.ds[Sum.size] = carry;
	Sum.size++;

	if (this->sign && H2.sign)
	{
		Sum.sign = true;
	}

	Sum.Trim();

	return Sum;
}

HugeInt HugeInt::operator+(const HugeInt& H2)const
{
	HugeInt H3, num1, num2;

	if ((*this > H2) && (!this->sign && !H2.sign))
	{
		num1 = *this;
		num2 = H2;
	}
	else if ((*this < H2) && (!this->sign && !H2.sign))
	{
		num1 = H2;
		num2 = *this;
	}
	else if ((*this > H2) && (!this->sign && H2.sign))
	{
		num1 = *this;
		num2 = H2;
		H3 = num1.Sub(num2);
		return H3;
	}
	else if ((*this < H2) && (this->sign && !H2.sign))
	{
		num1 = *this;
		num2 = H2;
		H3 = num1.Sub(num2);
		H3.sign = true;
		return H3;
	}
	else if ((*this > H2) && (this->sign && H2.sign))
	{
		num1 = H2;
		num2 = *this;
	}
	else
	{
		num1 = *this;
		num2 = H2;
	}
	
	int zero = 0;

	if (*this == zero && H2 == zero)
		return zero;
	else if (*this == H2 && !this->sign && H2.sign)
		return zero;
	else if (*this == H2 && this->sign && !H2.sign)
		return zero;

	HugeInt Sum;

	int carry = 0;

	Sum.size = num1.size + 1; 
	Sum.ds = new int[Sum.size];
	Sum.Initialize();

	for (int i = 0; i < Sum.size; i++)
	{
		Sum.ds[i] = (num1[i] + num2[i] + carry) % 10;
		carry = (num1[i] + num2[i] + carry) / 10;
		/*cout << "num1: " << num1[i] << endl;
		cout << "num2: " << num2[i] << endl;
		cout << "sum: " << Sum[i] << endl;*/
	}
	Sum.ds[Sum.size] = carry;

	if (this->sign && H2.sign)
	{
		Sum.sign = true;
	}

	Sum.Trim();

	return Sum;

}

HugeInt HugeInt::Sub(const HugeInt& H2)const
{

	int zero = 0;

	if (*this == zero && H2 == zero)
		return zero;
	else if (*this == H2 && !this->sign && !H2.sign)
		return zero;

	HugeInt Sub;
	int carry = 0;

	Sub.size = this->size + 1;
	Sub.ds = new int[Sub.size];
	Sub.Initialize();

	for (int i = 0; i < Sub.size; i++)
	{
		Sub.ds[i] = ((*this)[i] - H2[i] - carry);
		if (Sub.ds[i] < 0)
		{
			Sub.ds[i] += 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	Sub.ds[Sub.size] = carry;

	if (this->sign && H2.sign)
	{
		Sub.sign = true;
	}

	Sub.Trim();

	return Sub;

}

HugeInt HugeInt::operator-(const HugeInt& H2)const
{

	HugeInt H3, num1, num2;

	if ((*this > H2) && (!this->sign && !H2.sign))
	{
		num1 = *this;
		num2 = H2;
	}
	else if ((*this > H2) && (!this->sign && H2.sign))
	{
		num1 = *this;
		num2 = H2;
		H3 = num1.Add(num2);
		return H3;
	}
	else if ((*this < H2) && (this->sign && !H2.sign))
	{
		num1 = *this;
		num2 = H2;
		H3 = num1.Add(num2);
		H3.sign = true;
		return H3;
	}
	else if ((*this > H2) && (this->sign && H2.sign))
	{
		num1 = *this;
		num2 = H2;
	}
	else
	{
		num1 = *this;
		num2 = H2;
	}

	int zero = 0;

	if (num1 == zero && num2 == zero)
		return zero;
	else if (num1 == num2 && !this->sign && !this->sign)
		return zero;

	HugeInt Sub;
	int carry = 0;

	Sub.size = num1.size + 1;
	Sub.ds = new int[Sub.size];
	Sub.Initialize();

	for (int i = 0; i < Sub.size; i++)
	{
		Sub.ds[i] = (num1[i] - num2[i] - carry);
		if (Sub.ds[i] < 0)
		{
			Sub.ds[i] += 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	Sub.ds[Sub.size] = carry;

	if (this->sign && H2.sign)
	{
		Sub.sign = true;
	}

	Sub.Trim();

	return Sub;

}

HugeInt HugeInt::operator*(const HugeInt& H2)const
{

	HugeInt num1, num2;

	if (*this > H2)
	{
		num1 = H2;
		num2 = *this;
	}
	else
	{
		num1 = *this;
		num2 = H2;
	}

	if (num1.sign)
	{
		num1.sign = false;
	}
	if (num2.sign)
	{
		num2.sign = false;
	}

	int zero = 0;

	HugeInt Mul = zero;
	HugeInt TH = num1;
	HugeInt Res = zero;
	HugeInt count = zero;

	while (TH != zero)
	{
		Res = num2;
		count = 1;
		while (count + count <= TH)
		{
			Res += Res;
			count += count;
		}

		Mul += Res;
		Res = zero;
		TH = TH - count;
	}

	if (this->sign && H2.sign)
		Mul.sign = false;
	else if (this->sign || H2.sign)
		Mul.sign = true;

	return Mul;

}

HugeInt HugeInt::operator/(const HugeInt& H2)const
{

	HugeInt num1, num2;

	if (*this > H2)
	{
		num1 = *this;
		num2 = H2;
	}
	else
	{
		num1 = H2;
		num2 = *this;
	}

	if (num1.sign)
	{
		num1.sign = false;
	}
	if (num2.sign)
	{
		num2.sign = false;
	}

	int zero = 0;

	HugeInt Mul = zero;
	HugeInt TH = num1;
	HugeInt Res = zero;
	HugeInt count = zero;

	while (TH != zero)
	{
		Res = num2;
		count = 1;
		while (Res + Res <= TH)
		{
			Res += Res;
			count += count;
		}

		Mul += count;
		TH = TH - Res;
	}

	if (this->sign && H2.sign)
		Mul.sign = false;
	else if (this->sign || H2.sign)
		Mul.sign = true;
	
	return Mul;

}

const HugeInt HugeInt::operator+=(const HugeInt& H2)
{

	*this = *this + H2;
	return *this;

}

const HugeInt HugeInt::operator-=(const HugeInt& H2)
{

	*this = *this - H2;
	return *this;

}

const HugeInt HugeInt::operator*=(const HugeInt& H2)
{

	*this = *this * H2;
	return *this;

}

const HugeInt HugeInt::operator/=(const HugeInt& H2)
{

	*this = *this / H2;
	return *this;

}

int HugeInt::operator[](int i)const
{
	if (i >= this->size)
	{
		return 0;
	}

	return ds[i];
}

void HugeInt::Print()
{

	if (this->sign)
		cout << '-';

	for (int i = this->size - 1; i >= 0; i--)
	{
		if (i == decimal)
			cout << '.';
		else
			cout << (*this)[i];
	}

	cout << endl;

}

HugeInt::~HugeInt()
{

}