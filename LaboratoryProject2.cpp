// LaboratoryProject2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int gcd(int c,int mod)//Euclid
{
	if (mod == 0)
		return c;

	return gcd(mod, c%mod);
}

int noc(int c, int mod)//least common multiple
{
	return 2 * c / gcd(c, mod) * mod;
}

vector<int> prime_divisors(int mod)//function for finding mod`s dividers
{
	int div = 2;
	vector<int> divider;

	while (mod > 1)
	{
		while (mod % div == 0)
		{
			//cout << "*" << div;
			if ( !(std::find(divider.begin(), divider.end(), div) != divider.end()) )
				divider.push_back(div);

			mod /= div;
		}
		div++;
	}

	return divider;
}


bool del(int a,vector<int>v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if ((a - 1) % v[i] == 0)
			continue;
		else
			return false;
	}

	return true;
}

bool testing_theorem(int &a, int c, int mod,vector<int>v)
{
	//first condition: (c,m) = 1;
	if ( gcd(abs(c), abs(mod)) != 1)
		return false;

	//second condition: (a-1) divisible into all prime divisors of m
	if (del(a,v) == false)
		a = noc(v[1],v[2])+1;
	cout << "Now a:" << a << endl;

	//third condition: m%4==0 && (a-1)%4==0;
	if (mod % 4 == 0)
	{
		if ((a - 1) % 4 == 0)
			return true;
		else
			a *= 4;

	}
	else
		return true;

	return true;

}

void print(vector<int> v)//function for vector<int> printing( C++11 standart )
{
	for (auto &i : v)
		cout << i << " ";
}

void inFile(const char* path, int x)//function for write in file
{
	ofstream out(path,ios_base::app);
	out << x << endl;
}

void generator(int a, int b, int mod,int x0,const char* path,int count)
{
	int x = 0;
	for (int i = 0; i < count; i++)
	{
		///cout << "x0: " << x0 <<" :: ";
		int x = (a*x0%mod + b) % mod;
		///cout << ((x) / (4)) % 4096 << endl;// if you want to see in console let`s uncomment
		inFile(path, ((x) / (4)) % 4096);
		x0 = x;
	}
}

void work(int a,int b, int mod,int x0,const char *path,int count)
{
	vector<int> v = prime_divisors(mod); //write down mod`s dividers
	cout << "Your theorem test: " << testing_theorem(a, b, mod, v) << endl; //let`s check theorem: 1 = true; 0 = false;
	testing_theorem(a, b, mod, v);
	cout << a << ":" << b << ":" << mod << endl;//if theorem not performed in testing_theorem() we will change a, so now i want to see if something was change
	generator(a, b, mod, x0, path,count);//generator function
}


int main()
{
	int a = 5;
	int b = 22;
	int mod = pow(2,5);
	int x00 = 8;

	int a1 = 297;
	int b1 = 203;
	int mod1 = 131072;
	int x0 = 0;

	int a2 = 1013;
	int b2 = 857;
	int mod2 = pow(2, 20);
	int x01 = 0;

	const char* path0 = "C:\\Users\\Gennady\\Desktop\\file0.txt";
	const char* path1 = "C:\\Users\\Gennady\\Desktop\\file.txt";
	const char* path2 = "C:\\Users\\Gennady\\Desktop\\file2.txt";

	//4096 - count for calculation(how many numbers we will generate)
	work(a, b, mod, x00, path0, 4096);
	cout << endl;
	work(a1, b1, mod1, x0, path1,100);
	cout << endl;
	work(a2, b2, mod2, x01, path2,100);

	return 0;
}
