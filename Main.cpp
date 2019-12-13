#include <iostream>
#include <direct.h>
#include <limits>
#include <algorithm>
#include <string>
#include <queue>
#include<fstream>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include<Bits.h>
#include<bitset>
#include<Windows.h>
#define MAX_TREE_HT 256 
#include"DuyetFolder.h"
#include"MinHeap.h"
using namespace std;
constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits;
using bits_in_byte = std::bitset<BITS_PER_BYTE>;

// Tao bang chua gia tri ma huffman cho tung ki tu
unordered_map<char, string> Codes;
//Tao bang tan so xuat hien cua tung ki tu
unordered_map<char, int> Frequency;
//Cay Huffman

//Ham luu tru vao cay Huffman danh cho cac ki tu
void storeCodes(struct Minheap* root, string str)
{
	if (root == NULL)
	{
		return;
	}
	if (root->Key != '#')
	{
		Codes[root->Key] = str;
	}
	storeCodes(root->Left, str + "0");
	storeCodes(root->Right, str + "1");
}

// De dung cho hang doi MinHeap
struct Compare
{
	bool operator()(Minheap* l, Minheap* r)
	{
		return (l->Frequency > r->Frequency);
	}
};
//Hang doi uu tien luu tru cay Heap
priority_queue<Minheap*, vector<Minheap*>, Compare> MinHeap;

//Ham xay cay Huffman va luu tru vao MinHeap
void HuffmanCodes(int size)
{
	struct Minheap *Left, *Right, *Top;
	for (unordered_map<char, int>::iterator v = Frequency.begin(); v != Frequency.end(); v++)
		MinHeap.push(new Minheap(v->first, v->second));
	while (MinHeap.size() != 1)
	{
		Left = MinHeap.top();
		MinHeap.pop();
		Right = MinHeap.top();
		MinHeap.pop();
		Top = new Minheap('#', Left->Frequency + Right->Frequency);
		Top->Left = Left;
		Top->Right = Right;
		MinHeap.push(Top);
	}
	storeCodes(MinHeap.top(), "");
}

//Ham tinh tan suat voi moi ki tu cho bien Frequency duoc khai bao o dau
void calcFrequency(string str, int n)
{
	for (int i = 0; i < str.size(); i++)
	{
		Frequency[str[i]]++;
	}
}

// Ham lap qua chuoi da Encode # Neu s[i]=='0' thi duy qua trai # '1' thi qua phai # neu la nut la thi tra ve ki tu tai do
string Decode(struct Minheap* root, string s)
{
	string rs = "";
	struct Minheap* pos = root;
	for (int i = 0;i<s.size();i++)
	{
		if (s[i] == '0')
		{
			pos = pos->Left;
		}
		else
		{
			pos = pos->Right;
		}
		if (pos->Left == NULL && pos->Right == NULL)
		{
			rs += pos->Key;
			pos = root;
		}
	}
	return rs + '\0';
}
int main()
{
	vector<string> list = DuyetFolder("Go");
	vector<priority_queue<Minheap*, vector<Minheap*>, Compare>> List_MinHeap;
	vector<string>List_EncodedString;
	while (true) 
	{
		cout << "---------------------------------------" << endl;
		cout << "1. Nen file" << endl;
		cout << "2. Giai nen file" << endl;
		cout << "3. Thoat" << endl;
		cout << "---------------------------------------" << endl;
		int luachon;
		cin >> luachon;
		if (luachon == 1)
		{
			std::clock_t start;
			start = std::clock();
			for (int i = 0;i < list.size();i++)
			{
				std::clock_t start;
				double duration;
				start = std::clock();
				ifstream infile;
				string k = list.at(i);
				ifstream ifs("Go/" + k);
				string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
				string encodedString, decodedString;
				calcFrequency(content, content.length());
				HuffmanCodes(content.length());
				duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				std::cout << "printf: " << duration << '\n';
				ofstream fileout;
				fileout.open("FileNen.txt", ios::app);
				fileout << list.at(i) << endl;
				for (auto v = Codes.begin(); v != Codes.end(); v++)
				{
					cout << v->first << ' ' << v->second << endl;
				}
				for (auto i : content)
				{
					encodedString += Codes[i];
				}
				for (std::size_t i = 0; i < encodedString.size(); i += BITS_PER_BYTE)
				{
					byte b = bits_in_byte(encodedString.substr(i, BITS_PER_BYTE)).to_ulong();
					fileout << b;
				}
				List_MinHeap.push_back(MinHeap);
				List_EncodedString.push_back(encodedString);
				fileout << endl;
			}
			double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\nNen hoan tat (" << duration << "s)" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 2)
		{
			std::clock_t start;
			start = std::clock();
			string filename = "FileGiaiNen_";
			for (int i = 0;i < list.size();i++)
			{
				ostringstream ss;
				string DecodedString;
				cout << "\nNen hoan tat\n" << endl;
				system("cls");
				cout << "Giai Nen file..." << endl;
				ss << filename << i << ".txt";
				ofstream out2(ss.str().c_str(), ios::out);
				DecodedString = Decode(List_MinHeap.at(i).top(), List_EncodedString.at(i));
				out2 << DecodedString;
				out2.close();
				system("cls");
			}
			double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\nGiai nen hoan tat (" << duration << "s)" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			break;
		}
	}
}

