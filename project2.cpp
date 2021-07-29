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
		cout << " Error file open " <<'\n';
	}

	string name;
	string sex;
	string age;
	string height;
	string weight;
	string city;
	
	int i = 0;
	while ( ip.good())
	{
		getline(ip, name, ',');
		getline(ip, sex, ',');
		getline(ip, age, ',');
		getline(ip, height, ',');
		getline(ip, weight, ',');
		getline(ip, city, '\n');

		int j = 0;
		if (headerPresence == "false") 
		{
			data[i][0] = name;
			data[i][1] = sex;
			data[i][2] = age;
			data[i][3] = height;
			data[i][4] = weight;
			data[i][5] = city;
			i = i + 1;
		}

		if (headerPresence == "true")
		{
			headers[0] = name;
			headers[1] = sex;
			headers[2] = age;
			headers[3] = height;
			headers[4] = weight;
			headers[5] = city;

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
	/*cout << "\n" ;*/
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
	try {
		string x = getHeader(colNumber);
		if (x != "Name" && x != "Sex" && x != "City")
		{
			for (int i = 0; i < noRows; i++)
			{
				count = count + stoi (data[i][colNumber]);
			}

			avg = count / noRows;
			cout << "Average of " + x + " is " + to_string(avg) << endl;
		}
		else 
		{
			string message = "Average for " + x + " cannot be found since it is nan";
			throw message ;
		}
	}
	catch ( const string msg)
	{
		cerr << msg << endl;
	}
	return 0.0;
}

double DataFrame::findMax(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string* rows = new string[noRows];
	for (int i = 0; i < noRows; i++)
	{
		rows[i] = data[i][colNumber];
	}
	try {
		string columnName = getHeader(colNumber);
		if (columnName != "Name" && columnName != "Sex" && columnName != "City")
		{
			int i, j, min;
			string temp1;
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
			cout << "Max of " + columnName + " is " + rows[0] << endl;
		}
		else
		{
			string message = "Max for " + columnName + " cannot be found since it is nan";
			throw message;
		}
	}
	catch (const string msg)
	{
		cerr << msg << endl;
	}
	return 0.0;
}

double DataFrame::findMin(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string* rows = new string[noRows];
	for (int i = 0; i < noRows; i++)
	{
		rows[i] = data[i][colNumber];
	}
	try {
		string columnName = getHeader(colNumber);
		if (columnName != "Name" && columnName != "Sex" && columnName != "City")
		{
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
			cout << "Min of " + columnName + " is " + rows[0] << endl;
		}
		else
		{
			string message = "Min for " + columnName + " cannot be found since it is nan";
			throw message;
		}
	}
	catch (const string msg)
	{
		cerr << msg << endl;
	}
	return 0.0;

}

double DataFrame::frequency(int colNumber)
{
	if (colNumber == -1)
	{
		cout << "Header not found" << endl;
		return 0.0;
	}
	string columnName = getHeader(colNumber);
	try {
		if (columnName != "Name" && columnName != "Sex" && columnName != "Height(in)")
		{
			string message = "Frequency for " + columnName + " cannot be found since it is non categorical";
			throw message;
		}
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
	}
	catch (const string msg) 
	{
		cerr << msg << endl;
	}
	return 0.0;
}

DataFrame::~DataFrame()
{
}




int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	char option; // used to store the option(F or D) from the input file // get the following information from the redirected input
	option = ' ';
	cin >> numRows >> numCols >> headerBool >> fileName;
	// create an object of the data frame class using the non default constructor
	DataFrame* df = new DataFrame(numRows, numCols);

	// call the readCSV method with the file name and the header presence information
	bool var = true;
	df->readCSV(fileName, headerBool);
	char c;
	cin.get(c);
	while (!cin.eof())
	{
		string read_input = "";
		while (c == '\n')
		{
			cin.get(c);			
		}
		
		if (c != '\n')
		{
			option = c;
			while (c != '\n')
			{
				read_input = read_input + c;
				cin.get(c);
			}
		}

		if (option == 'D')
		{
			for (int j = 0; j < numCols; j++)
			{
				string x = df->getHeader(j);
				cout << x + "    ";
			}
			cout << endl;				
		
			df->display();
		}
		if (option == 'F')
		{
			string searchName;
			for (int i = 2; i < read_input.length(); i++)
			{
				searchName = searchName + read_input[i];
			}
			df->searchRecord(searchName);
		}
		if (option == 'C')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while ( j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}									
				}
				j = j + 1;								
			}
			int columnLength = stoi(substrings[1]);
			int* columnArray = new int[columnLength];
			for ( int j = 2 ; j < columnLength + 2  ; j++)
			{
				read_input = substrings[j];

				for (int i = 0; i < numCols; i++)
				{
					if (df->getHeader(i)== read_input)
					{
						columnArray[j - 2] = i; 
						break;
					}
				}
			}
			DataFrame* dataframe = new DataFrame(numRows, columnLength);
			dataframe = df->getColumns(columnArray, columnLength);
			dataframe->display1();
		}
		if (option == 'Q')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int column = 0;
			bool found = false;
			for (int i = 0; i < numCols; i++)
			{
				if (df->getHeader(i) == substrings[1])
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
		}
		if (option == 'A')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int column = 0;
			bool found = false;
			for (int i = 0; i < numCols; i++)
			{
				if (df->getHeader(i) == substrings[1])
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
		}
		if (option == 'X')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int column = 0;
			bool found = false;
			for (int i = 0; i < numCols; i++)
			{
				if (df->getHeader(i) == substrings[1])
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
		}
		if (option == 'I')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int column = 0;
			bool found = false;
			for (int i = 0; i < numCols; i++)
			{
				if (df->getHeader(i) == substrings[1])
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
		}
		if (option == 'R')
		{
			int Length = read_input.length();
			string* substrings = new string[5];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int rowStart = stoi(substrings[1]);
			int rowEnd = stoi(substrings[2]);
			int len = rowEnd - rowStart;
			int* rowArray = new int[2];
			rowArray[0] = rowStart;
			rowArray[1] = rowEnd;
			DataFrame* dataframe = new DataFrame(len, numCols);
			dataframe = df->getRows(rowArray, len);
			dataframe->display();		
			cout << "\n";
		}
		if (option == 'S')
		{
			int Length = read_input.length();
			string* substrings = new string[8];
			int k = 0;
			bool v = false;
			string substring = "";
			int j = 0;
			while (j < Length)
			{
				if (read_input[j] != ' ')
				{
					substring = substring + read_input[j];
				}
				if (read_input[j] == ' ' || j == Length - 1)
				{
					if (substring != "")
					{
						substrings[k] = substring;
						k = k + 1;
						substring = "";
					}
				}
				j = j + 1;
			}
			int columnLength = stoi(substrings[1]);
			int* columnsArray = new int[columnLength];
			int rowStart = stoi(substrings[columnLength + 2]);
			int rowEnd = stoi(substrings[columnLength + 3]);
			int rowLen = rowEnd - rowStart;
			int* rowsArray = new int[2];
			rowsArray[0] = rowStart;
			rowsArray[1] = rowEnd;
			for (int i = 2; i < columnLength + 2; i++)
			{
				for (j = 0; j < numCols; j++)
				{
					if (df->getHeader(j) == substrings[i]) 
					{
						columnsArray[i - 2] = j;
						break;
					}
				}
			}
			DataFrame* dataframe = new DataFrame(rowLen,columnLength);
			dataframe = df->getRowsCols(rowsArray, rowLen, columnsArray, columnLength);
			dataframe->display1();
		}
		cin.get(c);
	}
	
}

