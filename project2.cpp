#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class DataFrame : public exception
{
protected:
	string** data;
	string* headers;
	int noRows, noCols;
public:
	//Constructors
	DataFrame();

	DataFrame(int rows, int cols);

	//File reading Method
	void readCSV(string filename, string headerPresence);

	//Output Method
	void display(); 

	void display1();
	
	//Search Record
	string* searchRecord(string name);
	
	//Getters
	int getNumberRows();

	int getNumberCols(); // returns the number of columns

	DataFrame* getColumns(int* columns, int cLen); // returns a dataframe with a set of columns

	DataFrame* getRows(int* rows, int rLen); // returns a data frame with a set of rows

	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen); // returns a data frame given a set of row numbersand column numbers

	string getHeader(int i); // returns the header name given a column index position

		//Find info of a given column
	double findAverage(int colNumber); // returns the average of the given column

	double findMax(int colNumber); // returns the max of the given column

	double findMin(int colNumber); // returns the min of the given column

	double frequency(int colNumber); // returns frequency of unique value of the given column

	//Destructor
	~DataFrame();
}
;

class MyException : public invalid_argument {
	const char* what() const throw () {
		return "C++ Exception";
	}
};

DataFrame::DataFrame()
{
	data = {};
	headers = {};
	noRows = 0;
	noCols = 0;
}

DataFrame::DataFrame(int rows, int cols)
{
	noRows = rows;
	noCols = cols;
	data = new string*[rows];
	headers = new string[cols];

	for (int i = 0; i < rows; i++)
	{
		string* temp = new string[cols];
		data[i] = temp;
	}
}

void DataFrame::readCSV(string filename, string headerPresence)
{
	ifstream ip(filename);

	if (!ip.is_open())
	{
		cout << " Error file open " << '\n';
	}
	int i = 0;
	while (ip.good())
	{
		string input;
		if (headerPresence == "false")
		{
			for (int i = 0; i < noRows; i++)
			{
				for ( int j = 0 ; j < noCols ; j++)
				{
					if (j != noCols - 1)
					{
						getline(ip, input, ',');
						data[i][j] = input;
					}
					else
					{
						getline(ip, input, '\n');
						data[i][j] = input;
					}
				}
			}
		}

		if (headerPresence == "true") 
		{
			for (int i = 0; i < noCols; i++)
			{
				if (i != noCols - 1)
				{
					getline(ip, input, ',');
					headers[i] = input;
				}
				else
				{
					getline(ip, input, '\n');
					headers[i] = input;
				}
			}
			headerPresence = "false";
		}
		

	}

}

void DataFrame::display()
{
	
	for (int i = 0; i < noRows; i++)
	{
		cout << "\n";
		for (int j = 0; j < noCols; j++)
		{
			
			cout << data[i][j] + "    " ;
		}
		cout << endl;
		
	}
}

void DataFrame::display1()
{
	cout << "\n";
	for (int i = 0; i < noRows; i++)
	{
		for (int j = 0; j < noCols; j++)
		{
			cout << data[i][j] + "	";
		}
		cout << endl;
	}
	
}

string* DataFrame::searchRecord(string name)
{
	string* rowArray = new string[noCols];
	bool found = false;
	for (int i = 0; i < noRows; i++)
	{
		if (data[i][0] == name)
		{			
			cout << "Record found:" << endl;
			found = true;
			for (int j = 0; j < noCols; j++)
			{
				rowArray[j]= data[i][j];
				cout << "	" + data[i][j];
			}
			cout << endl;
			cout << "\n";
		}
				
		
	}
	if (found == false)
	{
		cout << "Record not found" << endl;
	}
	return rowArray;
}

int DataFrame::getNumberRows()
{
	return noRows;
}

int DataFrame::getNumberCols()
{
	return noCols;
}

DataFrame* DataFrame::getColumns(int* columns, int cLen)
{

	DataFrame* dataframe = new DataFrame(noRows , cLen);
	int k = 0;

	for (int i = 0; i < noRows; i++)
	{
		for (int j = 0; j < cLen; j++)
		{
			k = columns[j];
			dataframe->data[i][j] = data[i][k];
		}
	}
	return dataframe;
}

DataFrame* DataFrame::getRows(int* rows, int rLen)
{
	DataFrame* dataframe = new DataFrame(rLen, noCols);
	int k = 0;

	for (int i = rows[0]; i < rows[1]; i++)
	{
		for (int j = 0; j < noCols; j++)
		{
			dataframe->data[k][j] = data[i][j];
		}
		k = k + 1;
	}
	return dataframe;
}

DataFrame* DataFrame::getRowsCols(int* rows, int rLen, int* cols, int cLen)
{
	DataFrame* dataframe = new DataFrame(rLen, cLen);
	int k = 0; int r = 0; int c = 0;

	for (int i = rows[0] ; i < rows[1]; i++)
	{
		for (int j = 0; j < cLen; j++)
		{
			k = cols[j];
			dataframe->data[r][j] = data[i][k];
		}
		r = r + 1;
	}
	return dataframe;
}

string DataFrame::getHeader(int i)
{
	string name = "";
	name = headers[i];
	return name;
}

double DataFrame::findAverage(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	int avg = 0;
	int count = 0;
	string x = getHeader(colNumber);
	try
	{
		int c = stoi(data[0][colNumber]);
	}
	catch (invalid_argument e)
	{
		string message = "Average for " + x + " cannot be found since it is nan";
		cout << message << endl;
		return 0.0;

	}

	for (int i = 0; i < noRows; i++)
	{
		count = count + stoi(data[i][colNumber]);

	}
	avg = count / noRows;
	cout << "Average of " + x + " is " + to_string(avg) << endl;

	return 0.0;
}

double DataFrame::findMax(int colNumber)
{	
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string column_name = getHeader(colNumber);
	try
	{
		int c = stoi(data[0][colNumber]);
	}
	catch (invalid_argument e)
	{
		string message = "Max for " + column_name + " cannot be found since it is nan";
		cout << message << endl;
		return 0.0;
	}
	int i, j, min;
	string temp1;
	string* rows = new string[noRows];
	for (int i = 0; i < noRows; i++)
	{
		rows[i] = data[i][colNumber];
	}
	for (i = 0; i < noRows - 1; i++) {
		min = i;
		for (j = i + 1; j < noRows; j++)
		{
			if (stoi(rows[j]) > stoi(rows[i]))
			{
				min = j;
				temp1 = rows[i];
				rows[i] = rows[min];
				rows[min] = temp1;
			}
		}
	}
	cout << "Max of " + column_name + " is " + rows[0] << endl;
		
	return 0.0;
}

double DataFrame::findMin(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string column_name = getHeader(colNumber);
	try
	{
		int c = stoi(data[0][colNumber]);
	}
	catch (invalid_argument e)
	{
		string message = "Min for " + column_name + " cannot be found since it is nan";
		cout << message << endl;
		return 0.0;
	}
	string* rows = new string[noRows];
	for (int i = 0; i < noRows; i++)
	{
		rows[i] = data[i][colNumber];
	}
	int i, j, min;
	string temp1;
	for (i = 0; i < noRows - 1; i++) {
		min = i;
		for (j = i + 1; j < noRows; j++)
		{
			if (stoi(rows[j]) < stoi(rows[i]))
			{
				min = j;
				temp1 = rows[i];
				rows[i] = rows[min];
				rows[min] = temp1;
			}
		}
	}
	cout << "Min of " + column_name + " is " + rows[0] << endl;
	return 0.0;
}

double DataFrame::frequency(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string column_name = getHeader(colNumber);
	string* columnArray = new string[noRows];
	int res = 1;
	columnArray[0] = data[0][colNumber];
	for (int i = 1; i < noRows; i++) {
		int j = 0;
		for (j = 0; j < noRows; j++)
			if (data[i][colNumber] == data[j][colNumber])
				break;
		if (i == j)
		{
			columnArray[res] = data[i][colNumber];
			res++;
		}
	}
	for (int i = 0; i < res; i++)
	{
		int count = 0;
		for (int j = 0; j < noRows; j++)
		{
			if (data[j][colNumber] == columnArray[i])
			{
				count = count + 1;
			}
		}
		cout << columnArray[i] + ": " + to_string(count) << endl;
	}
	return 0.0;
}

DataFrame::~DataFrame()
{
	for (int i = 0; i < noRows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	delete[] headers;
}


int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	char option; // used to store the option(F or D) from the input file // get the following information from the redirected input
	cin >> numRows >> numCols >> headerBool >> fileName;
	// create an object of the data frame class using the non default constructor
	DataFrame* df = new DataFrame(numRows, numCols);

	// call the readCSV method with the file name and the header presence information
	df->readCSV(fileName, headerBool);
	string findName;
	while (cin >> option)
	{
		switch (option)
		{
			cin >> findName;
			case 'D':
			{

				for (int j = 0; j < numCols; j++)
				{
					string x = df->getHeader(j);
					if (x == "")
					{
						break;
					}
					cout << x + "   ";
					if (j == numCols-1)
					{
						cout << endl;
					}				
				}
				df->display();
				break;
			}
			case'F':
			{
				cin >> findName;
				df->searchRecord(findName);
				break;
			}
			case 'C':
			{
				cin >> findName;
				int length = stoi(findName);
				string* substrings = new string[length];
				int j = 0;
				for (int i = 0; i < length; i++)
				{
					cin >> findName;
					substrings[i] = findName;
				}			
				int* columnArray = new int[length];
				int k = 0;
				for (int i = 0; i < length ; i++)
				{
					for (int j = 0; j < numCols; j++)
					{
						if (df->getHeader(j) == substrings[i])
						{
							columnArray[k] = j;
							k = k + 1;
							break;
						}
					}
				}
				DataFrame* dataframe = new DataFrame(numRows, length);
				dataframe = df->getColumns(columnArray, length);
				dataframe->display1();
				break;
			}
			case 'Q':
			{
				cin >> findName;
				int column = 0;
				bool found = false;
				for (int i = 0; i < numCols; i++)
				{
					if (df->getHeader(i) == findName)
					{
						column = i;
						found = true;
						break;
					}
				}
				if (found == false)
				{
					column = -1;
				}
				df->frequency(column);
				break;
			}
			case('A'):
			{
				cin >> findName;
				int column = 0;
				bool found = false;
				for (int i = 0; i < numCols; i++)
				{
					if (df->getHeader(i) == findName)
					{
						column = i;
						found = true;
						break;
					}
				}
				if (found == false)
				{
					column = -1;
				}
				df->findAverage(column);
				break;
			}
			case('X'):
			{
				cin >> findName;
				int column = 0;
				bool found = false;
				for (int i = 0; i < numCols; i++)
				{
					if (df->getHeader(i) == findName)
					{
						column = i;
						found = true;
						break;
					}
				}
				if (found == false)
				{
					column = -1;
				}
				df->findMax(column);
				break;
			}
			case'I':
			{
				cin >> findName;
				int column = 0;
				bool found = false;
				for (int i = 0; i < numCols; i++)
				{
					if (df->getHeader(i) == findName)
					{
						column = i;
						found = true;
						break;
					}
				}
				if (found == false)
				{
					column = -1;
				}
				df->findMin(column);
				break;
			}
			case'R':
			{
				cin >> findName;
				int rowStart = stoi(findName);
				cin >> findName;
				int rowEnd = stoi(findName);
				int len = rowEnd - rowStart;
				int* rowArray = new int[2];
				rowArray[0] = rowStart;
				rowArray[1] = rowEnd;
				DataFrame* dataframe = new DataFrame(len, numCols);
				dataframe = df->getRows(rowArray, len);
				dataframe->display();
				cout << "\n";
				break;
			}
			case'S':
			{
				cin >> findName;
				int length = stoi(findName);
				int* rowsArray = new int[2];
				int* columnArray = new int[length];
				string* substrings = new string[length];
				int j = 0;
				for (int i = 0; i < length; i++)
				{
					cin >> findName;
					substrings[i] = findName;
				}
				int rowlen = 0;
				for (int i = 0; i < 2; i++)
				{
					cin >> findName;
					rowsArray[i] = stoi(findName);
					rowlen = stoi(findName) - rowlen;
				}
				int k = 0;
				for (int i = 0; i < length; i++)
				{
					for (int j = 0; j < numCols; j++)
					{
						if (df->getHeader(j) == substrings[i])
						{
							columnArray[k] = j;
							k = k + 1;
							break;
						}
					}
				}
				DataFrame* dataframe = new DataFrame(rowlen, length);
				dataframe = df->getRowsCols(rowsArray, rowlen, columnArray, length);
				dataframe->display1();
				break;
			}

		}
				
	}
	df->~DataFrame();
}
	
