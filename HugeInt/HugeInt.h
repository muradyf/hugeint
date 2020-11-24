#include <iostream>
#include <fstream>

using namespace std;

#pragma once

class HugeInt
{

private:
	int* ds;
	int size;
	int decimal;
	bool sign = false;

public:
	HugeInt();
	HugeInt(ifstream& fin);
	HugeInt(const HugeInt& H2);
	HugeInt(int num);
	HugeInt(const char* ptr);
	void Initialize();
	/*void InitializeIntPtr(int* ptr, int length);*/
	void InitializeCharPtr(char* ptr, int length);
	void SetHIs(string s);
	void RegrowIntArr(int* arr, int size);
	int getLengthInt(int num);
	char* CopyCharPtr(const char* ptr);
	void ShiftLeftChar(char* ptr);
	void ShiftLeftInt(int* ptr);
	void AssignPositive();
	void AssignNegative();
	void CheckIfZero();
	int Atoi();
	void Trim();
	int getSize();
	int getDec();

	const void operator=(const HugeInt& h2);
	const void operator=(int num);
	const void operator=(const char* ptr);

	int operator[](int i)const;
	/*int& operator[](int i);*/
	friend istream& operator>>(istream& CIN, HugeInt& H1);
	friend ostream& operator<<(ostream& COUT, HugeInt& H1);

	bool operator==(const HugeInt& H2)const;
	bool operator!=(const HugeInt& H2)const;
	bool operator<(const HugeInt& H2)const;
	bool operator>(const HugeInt& H2)const;
	bool operator<=(const HugeInt& H2)const;
	bool operator>=(const HugeInt& H2)const;
	HugeInt& operator++();
	const HugeInt operator++(int);
	HugeInt& operator--();
	const HugeInt operator--(int);

	HugeInt operator+(const HugeInt& H2)const;
	HugeInt Add(const HugeInt& H2)const;
	HugeInt operator-(const HugeInt& H2)const;
	HugeInt Sub(const HugeInt& H2)const;
	HugeInt operator*(const HugeInt& H2)const;
	HugeInt operator/(const HugeInt& H2)const;

	const HugeInt operator+=(const HugeInt& H2);
	const HugeInt operator-=(const HugeInt& H2);
	const HugeInt operator*=(const HugeInt& H2);
	const HugeInt operator/=(const HugeInt& H2);

	void Print();

	~HugeInt();

};
