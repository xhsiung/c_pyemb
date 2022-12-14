#include <stdio.h>
#include <stdlib.h>
#include <python3.10/Python.h>

static PyObject* callback(PyObject* self, PyObject* args)
{
    long c;
    PyArg_ParseTuple(args, "l", &c);
    printf("Result of call: %ld\n", c);

    Py_RETURN_NONE;
}

int main(int argc, char* argv[])
{
    Py_Initialize();
    PyObject* sysPath = PySys_GetObject((char*) "path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    printf("Input two integers separated by space:\n");
    int a, b;
    scanf("%d %d", &a, &b);

    PyObject *pModule = NULL, *pFunc = NULL, *pArgs = NULL, *funcMod = NULL ;
    do
    {
        PyMethodDef CFunctions[] =
        {
            {"callback", callback, METH_VARARGS, ""},            
            { NULL, NULL, 0, NULL}
        };

        struct PyModuleDef funcmodule =
        {
            PyModuleDef_HEAD_INIT,
            "cmodule", /* name of module */
            "function module", /* Doc string (may be NULL) */
            -1, /* Size of per-interpreter state or -1 */
            CFunctions /* Method table */
        };

        funcMod = PyModule_Create(&funcmodule);
        PyObject* sys_modules = PyImport_GetModuleDict();
        PyDict_SetItemString(sys_modules, "cmodule", funcMod);
        //Py_DECREF(funcMod);

        pModule = PyImport_ImportModule("func-module");
        if (pModule == NULL) break;

        pFunc = PyObject_GetAttrString(pModule, "multiply");
        if (pFunc == NULL) break;

        pArgs = Py_BuildValue("ii", a, b);
        if (pArgs == NULL) break;

        PyObject_Call(pFunc, pArgs, NULL);
    } while (0);
    
    Py_XDECREF(pArgs);
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
    Py_XDECREF(funcMod);
    
    Py_Finalize();
    return 0;
}