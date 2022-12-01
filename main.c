#include <stdio.h>
#include <stdlib.h>
#include <python3.10/Python.h>

int main(int argc,char* argv[]){

	Py_Initialize();
	//code here
	Py_Finalize();
	return 0;
}
