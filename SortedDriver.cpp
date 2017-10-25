// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

// James Fantin
// 10/23/17

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
    double difference = 0, isolated = 0, temp, temp2;
    if(number.size() == 1) {
        return number[0];
    }
	for(int i = 0; i < number.size() - 1; i++)
    {
        if(i == 0) // First item of the list
        {
            temp = -1*(number[i] - number[i+1]);
            if(temp > difference)
            {
                difference = temp;
                isolated = number[i];
            }
        }
        else if(i == number.size() - 2) // Last item of the list
        {
            temp = (number[i] - number[i-1]);
            if(temp > difference)
            {
                difference = temp;
                isolated = number[i];
            }
        }
        else // Middle items of the list
        {
            temp = -1*(number[i] - number[i+1]);
            temp2 = (number[i] - number[i-1]);
            if(temp < temp2 && temp > difference)
            {
                difference = temp;
                isolated = number[i];
            }
            else if(temp2 < temp && temp2 > difference)
            {
                difference = temp2;
                isolated = number[i];
            }
        }
	}
	return isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
    int count = 0;
    list<string>::iterator itA = A.begin();
	list<string>::iterator itB = B.begin();
    while(next(itA, 1) != A.end() || next(itB, 1) != B.end())
    {
        if(*itA == *itB) // If they are equal then we increment A
        {
			if (next(itA,1) != A.end())
			{
				itA++;
			}
			else
			{
				break; // Break because there are no more values in A, so we can stop
			}
        }
        else if(*itA < *itB) // If A < B then we count the value and increment A to next value
        {
			if (next(itA, 1) != A.end())
			{
				itA++;
			}
			count++;
        }
        else // If A > B then we increment B to the next value
        {
			if (next(itB, 1) != B.end())
			{
				itB++;
			}
        }
    }
	if (*itA < *itB) // We need to check the final values and see if A is still less than B, if it is count it
	{
		count++;
	}
    return count;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
