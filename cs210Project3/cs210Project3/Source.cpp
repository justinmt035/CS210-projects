#include <Python.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

//function declarations
void CallProcedure(string pName);
int CallIntFunc(string proc, string param);
int CallIntFunc(string proc, int param);
void Menu();
void PrintSales();
void SearchSales();
void PrintHistogram();

//main method
int main() {
	int userInput = -1;

	//loop the menu and link to functions
	while (userInput != 4) {
		Menu();

		cin >> userInput;

		//prints a list of daily sales
		if (userInput == 1) {
			PrintSales();
		}
		//allows user to search daily sales for item
		else if (userInput == 2) {
			SearchSales();
		}
		//prints a histogram of daily sales
		else if (userInput == 3) {
			PrintHistogram();
		}
		//handle invalid input
		else if (userInput > 4) {
			cout << "Not a valid input!" << endl;
		}
	}

	return  0;
}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int CallIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int CallIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
* Displays the menu
*/
void Menu() {
	cout << setfill('=') << setw(40) << "" << endl;
	cout << setfill(' ') << setw(15) << "" << setw(10) << left << "Main Menu" << endl;
	cout << setfill('-') << setw(40) << "" << endl;
	cout << "1 - List Today's Sales" << endl;
	cout << "2 - Search Today's Sales" << endl;
	cout << "3 - Print Histogram of Today's Sales" << endl;
	cout << "4 - Quit" << endl;
}

/*
* Calls Python function to display sales
*/
void PrintSales() {
	cout << setfill(' ') << setw(14) << "" << setw(10) << left << "Today's Sales" << endl;
	cout << setfill('-') << setw(40) << "" << endl;
	CallProcedure("PrintSales"); //calls python function
}

/*
* Calls Python function to search for user specified item
*/
void SearchSales() {
	string userInput;
	cout << setfill(' ') << setw(16) << "" << setw(10) << left << "Search" << endl;
	cout << setfill('-') << setw(40) << "" << endl;
	cout << endl;
	cout << "Enter an item to search for: ";
	cin >> userInput;
	cout << "# of " << userInput << " purchased --- " << CallIntFunc("SearchSales", userInput) << endl; //calls python function
	cout << endl;
}

/*
* Calls Python function to write data to file, then C++ displays a histogram
*/
void PrintHistogram() {
	CallProcedure("WriteFile"); //calls python function

	ifstream inFS;
	string sales;

	cout << setfill(' ') << setw(15) << " " << setw(10) << left << "Histogram" << endl;
	cout << setfill('-') << setw(40) << "" << endl;

	inFS.open("frequency.dat"); //opens the file that python just created
	if (!inFS.is_open()) { //did it open?
		cout << "Could not open file frequency.dat!" << endl;
	}

	inFS >> sales; //read first item
	while (!inFS.fail()) {	//until EOF, count the occurences and display histogram for item
		cout << left << setw(13) << setfill(' ') << sales << "|"; //print item
		inFS >> sales; //read quantity
		int numSales = stoi(sales); //convert quantity string to int
		for (int i = 0; i < numSales; ++i) //iterate over int
			cout << "*"; //printing the histogram
		inFS >> sales; //get the next item ready
		cout << endl;
	}

	if (!inFS.eof()) { //exit properly?
		cout << "Input failure before reaching end of file!" << endl;
	}

	cout << endl;
	inFS.close(); //close the file
}
