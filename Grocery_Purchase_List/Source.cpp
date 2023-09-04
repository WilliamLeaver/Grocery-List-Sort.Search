#include <Python.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

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
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
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
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
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
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
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

void DailyHisto() {
	string line;
	ifstream file;
	file.open("frequency.dat");
	while (getline(file, line)) {
		string item;
		int num;
		stringstream ss(line);
		ss >> item;
		ss >> num;
		cout << setw(15) << left << item << "|";
		for (int i = 0; i < num; i++) {
			cout << "+";
		}
		cout << endl;
	}
	file.close();
}

void Menu() {
	int selection;
	string item;
	int num;
	cout << "      Please make a selection      " << endl;
	cout << "===================================" << endl;
	cout << "|1: Display Daily Purchases       |" << endl;
	cout << "|2: Specific Daily Purchases      |" << endl;
	cout << "|3: Display Daily Histogram       |" << endl;
	cout << "|4: Exit                          |" << endl;
	cout << "===================================" << endl;
	cin >> selection;
	cout << endl;
	switch (selection) {
	case 1:
		CallProcedure("DailyList");
		cout << endl;
		Menu();
		break;
	case 2:
		cout << "What item would you like to search for?" << endl;
		cin >> item;
		cout << endl;
		num = callIntFunc("DailyItem", item);
		if (num > 0) {
			cout << item << " were purchased " << num << " time(s) today." << endl << endl;
		}
		else {
			cout << item << " was not found on the list today. Please confirm spelling and remember that capitals matter." << endl << endl;
		}
		Menu();
		break;
	case 3:
		CallProcedure("DailyHisto");
		DailyHisto();
		cout << endl;
		Menu();
		break;
		break;
	case 4:
		cout << "Thank you. Please come again!" << endl;
		break;
	default:
		cout << "Incorrect input. Please try again." << endl << endl;
		cin.clear();
		cin.ignore();
		Menu();
		break;
	}
}


int main()
{
	Menu();
	return 0;
}