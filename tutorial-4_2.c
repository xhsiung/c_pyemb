#include <stdio.h>
#include <stdlib.h>
#include <python3.10/Python.h>

typedef struct _paras{
    char name[1024];
} paras;

void* runpy(void* arg){
    paras* data = (paras*)(arg);
    printf("-->%sXX", data->name);

    PyGILState_STATE state = PyGILState_Ensure();
    PyObject *pModule = NULL, *pFunc = NULL;
    do{
        pModule = PyImport_ImportModule("work");
        if (pModule == NULL) break;

        pFunc = PyObject_GetAttrString(pModule, "working");
        if (pFunc == NULL) break;
        
        //code hear
        PyObject_CallFunction(pFunc, "s",  data->name);
        
    } while (0);

    //release  
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
    PyGILState_Release(state);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char* argv[]){
    paras data;    
    strcpy( data.name , "alex3_alex1");
    
    Py_Initialize();
    PyObject* sysPath = PySys_GetObject((char*) "path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    PyThreadState* save = PyEval_SaveThread();
    pthread_t tid1 ;    
    pthread_create(&tid1, NULL, runpy, &data );        

    printf("main thread finish\n");
    //PyEval_RestoreThread(save);    
    //Py_Finalize();
    pthread_exit(NULL);

    sleep(5);
    return 0;
}
    