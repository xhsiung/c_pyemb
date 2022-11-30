#include <python3.10/Python.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    Py_Initialize();
    PyObject* sysPath = PySys_GetObject((char*) "path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    printf("Input two integers separated by space:\n");
    int a, b;
    scanf("%d %d", &a, &b);

    PyObject *pModule = NULL, *pFunc = NULL, *pArgs = NULL, *pValue = NULL;
    do
    {
        pModule = PyImport_ImportModule("func");
        if (pModule == NULL) break;

        pFunc = PyObject_GetAttrString(pModule, "multiply");
        if (pFunc == NULL) break;

        pArgs = Py_BuildValue("ii", a, b);
        if (pArgs == NULL) break;

        pValue = PyObject_Call(pFunc, pArgs, NULL);
	//pValue = PyObject_CallFunction(pFunc, "ii", 22,33);
        if (pValue == NULL) break;
        printf("Result of call: %ld\n", PyLong_AsLong(pValue));
    } while (0);

    Py_XDECREF(pValue);
    Py_XDECREF(pArgs);
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);

    Py_Finalize();
    return 0;
}
