//C lib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

// deviewer C to Python module
// WRITTEN xx/11/20 by Kyle Christie
// Converted to Python Module 25/11/20

//This python module is aimed towards Linux OS and is tested on Ubuntu
//9/12/20 -- Removed the use of variables when opening files
//20/12/20 -- Fixed minor display issue with cpu name, added get_bios() 

//GET OS
static PyObject* get_os(PyObject* self){
    FILE* fs;
    char buf[40] = {};
    char* results;

    fs = fopen("/proc/version", "r");
    
    fgets(buf, 32, fs);
    results = buf;
    
    PyObject* os = Py_BuildValue("s", buf);
    return os;
}

//GET CPU
static PyObject* get_cpu(){
    FILE* fs;
    
    char buf[40] = {};
    char* results;

    fs = fopen("/proc/cpuinfo", "r");
    

    while(fgets(buf, 40, fs)){
		
	    if(results = strstr(buf, "model name")){
		    results = results + 13;
            break;
            
        }
	}

    PyObject* cpu = Py_BuildValue("s", results);
    return cpu;

}

//GET CPU CORES
static PyObject* get_cpucore(){
    FILE* fs;
    char buf[40] = {};
    char* res;

    fs = fopen("/proc/cpuinfo", "r");

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
	
	system("lshw -numeric -C display > gpu.txt");

	char buf[60] = {};
	char* results;
	
	fs = fopen("gpu.txt", "r");

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
    char buf[40] = {};
    char* results;

    fs = fopen("/proc/meminfo", "r");
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

static PyObject* get_bios(void){
    system("sudo dmidecode -t 0 > bios.txt");

    FILE* fs;
    char buf[60] = {};
    char get[30] = {};
    char* bname;
    char* bvers;

    fs = fopen("bios.txt", "r");

    while(fgets(buf, 60, fs)){
        if(bname = strstr(buf, "Vendor:")){
            bname = bname + 8;
            break;
        }
    }

   
    rewind(fs);
  
   while(fgets(get, 30, fs)){
   	if(bvers = strstr(get, "BIOS Revision:")){
            bvers = bvers + 15;
            break;
        }
    }

    strtok(bname, "\n");
    
    PyObject* bios = Py_BuildValue("s", strcat(bname, bvers));
    return bios;
}


static PyObject* version(PyObject* self){
    return Py_BuildValue("s", "Version 0.04");
}

static PyMethodDef methods[] = {
        {"get_os", get_os, METH_NOARGS,"Returns String containing OS version."},
        {"get_gpu", get_gpu, METH_NOARGS, "Returns String containing GPU name."},
        {"get_cpu", get_cpu, METH_NOARGS, "Return String containing CPU name."},
        {"get_cpucore", get_cpucore, METH_NOARGS, "Returns Int containing number of CPU cores."},
        {"get_mem", get_mem, METH_NOARGS, "Returns Int containing amount of RAM."},
        {"get_user", get_user, METH_NOARGS, "Returns String containing current users name."},
        {"get_bios", get_bios, METH_NOARGS, "Returns String containing BIOS name and version."},
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