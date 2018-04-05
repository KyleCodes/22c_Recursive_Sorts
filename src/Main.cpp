////////////////////////////////////////////
//				Kyle Muldoon
//				Jasraj Dhudwal
//					LAB 5
////////////////////////////////////////////
//		MAIN FILE
////////////////////////////////////////////

// THIS PROGRAM DEMONSTRATES 3 TYPES OF SORTING DATA

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// FUNCTION PROTOTYPES
void PrintArray(int*, int);
void insertionSort(int*, int);
void MergeSort(int*, int, int, int);
void Merge(int*, int, int, int, int);
void swap(int*, int*);
int partition(int*, int, int, int);
void quickSort(int*, int, int, int);
void saveLine(string);
void deleteContents();

// ARRAY SIZE LIMITER
const int MAX_SIZE = 32;
//FileStorage<int> FIO;
//ofstream OUT;

int main()
{
	int chooseSize;
	int sortSelect;
	deleteContents();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

mainMenu:
	cout << " NOTICE: All operations will be saved to SortedData.txt " << endl;
	cout << "////////////////////////////////////////////////////////" << endl;
	cout << "      Please select the size of your array " << endl;
	cout << "         ARRAY SIZE CANNOT EXCEED 32 " << endl;
	cout << "                      ";

	cin >> chooseSize;
	if (cin.fail())
	{
		cout << "Invalid" << endl;
		goto mainMenu;
	}


	int* Array = new int[chooseSize];

	cin.ignore();

	cout << endl;
	cout << "////////////////////////////////////////////////////////" << endl;
	cout << "          Filling Array with " << chooseSize << " numbers" << endl;

	for (int x = 0; x < chooseSize; x++)
	{
		cout << "	";
		cin >> Array[x];
	}

SortPick:
	cout << "////////////////////////////////////////////////////////" << endl;
	cout << "            Pick a Sorting Type: " << endl << endl;
	cout << "     1. Insertion Sort " << endl;
	cout << "     2. Merge Sort " << endl;
	cout << "     3. Quick Sort " << endl;
	cout << "     4. Exit" << endl << endl;
	cout << "          ";

	cin >> sortSelect;
	if (cin.fail() || sortSelect < 0 || sortSelect > 4)
	{
		cout << "invalid" << endl;
		goto SortPick;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	switch (sortSelect)
	{
	case 1:
	{
		cout << "////////////////////////////////////////////////////////" << endl;
		cout << "       Displaying Insertion Sort Steps Recursively" << endl << endl;

		int* newArr = new int[chooseSize];
		for (int i = 0; i < chooseSize; i++)
			newArr[i] = Array[i];

//		PrintArray(newArr, chooseSize);
		insertionSort(newArr, chooseSize);
		PrintArray(newArr, chooseSize);
		saveLine("^^INSERTION SORT");
		cout << endl;

		goto SortPick;
	}
	case 2:
	{
		cout << "////////////////////////////////////////////////////////" << endl;
		cout << "        Displaying Merge Sort Steps Recursively" << endl << endl;

		int* newArr = new int[chooseSize];
		for (int i = 0; i < chooseSize; i++)
			newArr[i] = Array[i];

		PrintArray(newArr, chooseSize);
		MergeSort(newArr, 0, (chooseSize - 1), chooseSize);
		saveLine("^^MERGE SORT");
		cout << endl;

		goto SortPick;
	}
	case 3:
	{
		cout << "////////////////////////////////////////////////////////" << endl;
		cout << "       Displaying Quick Sort Steps Recursively" << endl << endl;

		int* newArr = new int[chooseSize];
		for (int i = 0; i < chooseSize; i++)
			newArr[i] = Array[i];

		PrintArray(newArr, chooseSize);
		quickSort(newArr, 0, (chooseSize - 1), chooseSize);
		PrintArray(newArr, chooseSize);
		saveLine("^^QUICK SORT");
		cout << endl;

		goto SortPick;
	}
	case 4:
		cout << "////////////////////////////////////////////////////////" << endl;
		char quit;
		cout << "Are you sure you want to Quit? (Y/N)" << endl;
		cout << "             ";
		cin >> quit;

		if (quit == 'Y' || quit == 'y')
			exit(0);
		else if (quit == 'N' || quit == 'n')
			goto mainMenu;
		break;
	}

	system("pause");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		FUNCTION DEFINITIONS
////////////////////////////////////////////


void PrintArray(int Array[], int Size)
{
	ofstream out;
	out.open("SortedData.txt", ios::out | ios::app);
	for (int i = 0; i < Size; i++)
	{
		cout << Array[i] << " ";
		out << Array[i] << " ";
	}
	cout << endl;
	out << endl;
	out.close();
}

void insertionSort(int Array[], int Size)
{
	if (Size <= 1)
	{
		return;
	}
	
	insertionSort(Array, Size - 1);

	int last = Array[Size - 1];
	int j = Size - 2;

	while (j >= 0 && Array[j] > last)
	{
		Array[j + 1] = Array[j];
		PrintArray(Array, Size-1);
		j--;
	}
	Array[j + 1] = last;
}

void MergeSort(int Array[], int first, int last, int ChooseSize)
{
	if (first < last)
	{
		int mid = first + (last - first) / 2;

		MergeSort(Array, first, mid, ChooseSize);

		MergeSort(Array, mid + 1, last, ChooseSize);

		Merge(Array, first, mid, last, ChooseSize);

	}

}

void Merge(int Array[], int first, int mid, int last, int ChooseSize)
{
	int tempArray[MAX_SIZE];

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;

	while ((first1 <= last1) && (first2 <= last2))
	{
		if (Array[first1] <= Array[first2])
		{
			tempArray[index] = Array[first1];
			first1++;
		}
		else
		{
			tempArray[index] = Array[first2];
			first2++;
		}
		index++;
	}

	while (first1 <= last1)
	{
		tempArray[index] = Array[first1];
		first1++;
		index++;
	}

	while (first2 <= last2)
	{
		tempArray[index] = Array[first2];
		first2++;
		index++;

	}

	for (index = first; index <= last; index++)
	{
		Array[index] = tempArray[index];
	}

	PrintArray(Array, ChooseSize);

}

void swap(int* a, int* b)
{
	//cout << "swapping" << endl;
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int Array[], int first, int last, int Size)
{
	//cout << "inside partition fn" << endl;
	int pivot = Array[last];
	int i = (first-1);

	for (int j = first; j <= (last-1); j++)
	{
		if (Array[j] <= pivot)
		{
			i++;
			swap(&Array[i], &Array[j]);
		}
	}
	swap(&Array[i + 1], &Array[last]);
	PrintArray(Array, Size);
	return (i + 1);
}

void quickSort(int Array[], int first, int last, int Size)
{
	if (first < last)
	{
		int index = partition(Array, first, last, Size);
		quickSort(Array, first, index - 1, Size);
		quickSort(Array, index + 1, last, Size);
	}
}

void deleteContents()
{
	ofstream del;
	del.open("SortedData.txt", ios::out | ios::trunc);
	del.close();
}

void saveLine(string addThis)
{
	ofstream out;
	out.open("SortedData.txt", ios::out | ios::app);
	out << addThis << endl;
	out << endl;
	out.close();
}