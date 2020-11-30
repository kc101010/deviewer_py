//C lib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

// deviewer C to Python module
// WRITTEN xx/11/20 by Kyle Christie -- Converted to Python Module 25/11/20

//This python module is aimed towards Linux OS and is tested on Ubuntu

//GET OS
static PyObject* get_os(PyObject* self){
    FILE* fs;
    char* name = "/proc/version";

    char buf[40] = {};
    char* results;

    fs = fopen(name, "r");
    
    fgets(buf, 32, fs);
    results = buf;
    
    PyObject* os = Py_BuildValue("s", buf);
    return os;
}

//GET CPU
static PyObject* get_cpu(){
    FILE* fs;
    char* name = "/proc/cpuinfo";

    char buf[40] = {};
    char* results;

    fs = fopen(name, "r");
    

    while(fgets(buf, 40, fs)){
		
	    if(results = strstr(buf, "model name")){
		    results = results + 12;
            break;
            
        }
	}

    PyObject* cpu = Py_BuildValue("s", results);
    return cpu;

}

//GET CPU CORES
static PyObject* get_cpucore(){
    FILE* fs;
    char* name = "/proc/cpuinfo";

    char buf[40] = {};
    char* res;

    fs = fopen(name, "r");

    while(fgets(buf, 40, fs)){
		
         if(res = strstr(buf, "cpu cores")){
		    res = res + 12;
            break;
	    }
   }

   int out = atoi(res);
   //Return int for better use
   PyObject* core = Py_BuildValue("i", out);
   return core;
}

//GET GPU
static PyObject* get_gpu(){
    FILE* fs;
	char* sname = "gpu.txt";	

	system("lshw -numeric -C display > gpu.txt");

	char buf[60] = {};
	char* results;
	//char* out;

	fs = fopen(sname, "r");

	while(fgets(buf, 60, fs)){
		
	    if(results = strstr(buf, "product")){
		    results = results + 9;
		    break;
	    }	
	}
	
	remove("gpu.txt");

    PyObject* gpu = Py_BuildValue("s", results);
    return gpu;
}

//GET MEM
static PyObject* get_mem(){
    FILE* fs;
    char* name = "/proc/meminfo";

    char buf[40] = {};
    char* results;

    fs = fopen(name, "r");
    int retmem;    

    while(fgets(buf, 40, fs)){
		
	    if(results = strstr(buf, "MemTotal:")){
		    results = results + 15;
            fs = fopen("temp", "w");
            fprintf(fs, "%s" ,results);
            fclose(fs);

            break;
	    }
		
	}

    fs = fopen("temp", "r");
    rewind(fs);
    fscanf(fs, "%d", &retmem );
    fclose(fs);

    remove("temp");

    PyObject* mem = Py_BuildValue("i", retmem);
    return mem;
}

static PyObject* get_user(){
    system("who > user.txt");

    FILE* fs;

    char buf[10] = {};
    char* results;

    fs = fopen("user.txt", "r");

    fgets(buf, 10, fs);
    results = buf;

    remove("user.txt");

    PyObject* user = Py_BuildValue("s", results);
    return user;
}


static PyObject* version(PyObject* self){
    return Py_BuildValue("s", "Version 0.01");
}

static PyMethodDef methods[] = {
        {"get_os", get_os, METH_NOARGS,"Returns String containing OS version."},
        {"get_gpu", get_gpu, METH_NOARGS, "Returns String containing GPU name."},
        {"get_cpu", get_cpu, METH_NOARGS, "Return String containing CPU name."},
        {"get_cpucore", get_cpucore, METH_NOARGS, "Returns Int containing number of CPU cores."},
        {"get_mem", get_mem, METH_NOARGS, "Returns Int containing amount of RAM."},
        {"get_user", get_user, METH_NOARGS, "Returns String containing current users name."},
        {"version", (PyCFunction)version, METH_NOARGS,"Returns String containing module Version" },
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef deviewer = {
        PyModuleDef_HEAD_INIT,
        "deviewer",
        "Returns System Information for Linux OS",
        -1,
        methods
};

PyMODINIT_FUNC PyInit_deviewer(void){
    return PyModule_Create(&deviewer);
}