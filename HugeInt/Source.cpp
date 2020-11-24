#include <iostream>
#include <fstream>
#include <string>
#include "HugeInt.h"

using namespace std;

int main()
{

	// INITIIALIZING AND READING

	ifstream fin;
	fin.open("HIs.txt");

	int size = 0;

	fin >> size;
	HugeInt** HIs = nullptr;

	for (int i = 0; i < size; i++)
		HIs = new HugeInt * [size];

	for (int i = 0; i < size; i++)
		HIs[i] = new HugeInt(fin);

	fin.close();

	for (int i = 0; i < size; i++)
		cout << "HIs[" << i << "] = " << *HIs[i] << endl;

	HugeInt H1("18");
	HugeInt H2("2");
	HugeInt num1, num2;

	/*HugeInt H3 = num1 + num2;
	HugeInt H3 = num1 - num2;*/

	if (H1.getSize() > H2.getSize())
	{
		num1 = H1;
		num2 = H2;
	}
	else
	{
		num1 = H2;
		num2 = H1;
	}

	HugeInt H3;
		
	H3 = num1 + num2;

	cout << endl << H3;

	 H3 = num1 - num2;

	cout << endl << H3;

	 H3 = num1 * num2;

	cout << endl << H3;

	 H3 = num1 / num2;

	cout << endl << H3;

	H1 += H2;

	cout << endl << H1;

	H1 -= H2;

	cout << endl << H1;

	H1 *= H2;

	cout << endl << H1;

	H1 /= H2;

	cout << endl << H1;

	//DONE

}