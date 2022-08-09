#include <iostream>
#include <fstream>
using namespace std;
class FloatArray
{
protected:
	int sizee;
	float* arr;
	int cnt;
public:
	FloatArray(int sizee)
	{
		cnt = 0;
        this->sizee = sizee;
        arr = new float[sizee];
	}
	virtual void add(float num)
	{
	    arr[cnt++] = num;
	}
	friend ofstream& operator<<(ofstream& readToFile, const FloatArray&  ob)
	{
		readToFile << ob.cnt <<"|";
		for (int i = 0; i < ob.cnt; i++)
			readToFile <<"\t"<<ob.arr[i];

		readToFile << endl;
		return readToFile;
	}
	friend ifstream& operator>>(ifstream& writeFromFile, FloatArray& ob)
	{
		float x;
		for (int i =0; i < ob.sizee; i++)
		{
				writeFromFile >> x;
				ob.add(x);
		}
		return writeFromFile;
	}
	~FloatArray()
	{
		delete [] arr;
	}

};
class SortedArray:public FloatArray
{
public:
	SortedArray(int sizee ):FloatArray(sizee){}
	void add(float num)
	{
		if (cnt == 0)
			{arr[cnt++] = num;}
		else if (num >= arr[cnt-1])
		{
			arr[cnt++] = num;
		}
		else
		{
			int i=0;
			for (; i < cnt; i++)
			{
				if (num < arr[i])
                    break;
			}
			for (int j = cnt; j > i; j--)
				    arr[j] = arr[j-1];
            arr[i++] = num;
            cnt++;
		}
	}

};
class FrontArray :public FloatArray
{
public:
	FrontArray(int sizee) :FloatArray(sizee) {}
	void add(float num)
	{
		for (int i = cnt-1; i>=0 ; i--)
			arr[i+1] = arr[i];
		arr[0] = num;
		cnt++;
	}
};
class PositiveArray:public SortedArray
{
public:
	PositiveArray(int sizee):SortedArray(sizee){}
	void add(float num)
	{
		if (num > 0)
		{
			SortedArray::add(num);
		}
	}
};
class NegativeArray :public SortedArray
{
public:
	NegativeArray(int sizee) :SortedArray(sizee) {}
	void add(float num)
	{
		if (num < 0)
		{
			SortedArray::add(num);
		}
	}
};
int main()
{
	string nameOfTheInputFile, nameOfTheOutputFile;
	cout << "Enter the name of the input file: ";
	cin >> nameOfTheInputFile;
	cout << "Enter the name of the output file: ";
	cin >> nameOfTheOutputFile;

	ifstream inFile; ofstream outFile;
	inFile.open(nameOfTheInputFile);
	outFile.open(nameOfTheOutputFile);

	FloatArray* arr[10];
	for (int i = 0; i < 10; i++)
	{
		string type;
		int sizee;
		inFile >> type >> sizee;
		if (type == "Array")
			arr[i] = new FloatArray(sizee);

		else if (type == "Sorted")
			arr[i] = new SortedArray(sizee);

		else if (type == "Front")
			arr[i] = new FrontArray(sizee);

		else if (type == "Positive")
			arr[i] = new PositiveArray(sizee);

		else if (type == "Negative")
			arr[i] = new NegativeArray(sizee);

		inFile >> *arr[i];
		outFile << *arr[i];
	}
	return 0;
}
