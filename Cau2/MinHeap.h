#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Minheap
{
	char Key;             // Ki tu luu tru
	int Frequency;             // tan suat cua ki tu
	Minheap *Left, *Right;
	Minheap(char Key, int Frequency)//khoi tao
	{
		this->Key = Key;
		this->Frequency = Frequency;
		Left = Right = NULL;
	}
};
