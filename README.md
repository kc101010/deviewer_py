# deviewer_py
A Python Module written in C which returns system information

# About: deviewer
deviewer is a Python module which collects Linux system information.

# IMPORTANT NOTES
deviewer has only been tested on Ubuntu 20.04

# Getting Started

Please make sure the latest version of Python and the Python Developer Tools are installed to the machine.
These tools are necessary as they contain <Python.h>

In the Terminal, run; "sudo apt-get install python-dev" to install dev tools.

After downloading the source files run setup.py using; 
"python3 setup.py {build/install}"

At the end of the command please use either build or install without the brackets to either build a local version of the module or install it to your system. 

If you build the module please make sure to copy the contents of "/build/lib.linux-x86_64-3.8/" into the same directory as your projects in which you plan to use the module.

### Functions
- get_os      : Returns String of OS name/version
- get_cpu     : Returns String of CPU name
- get_cpucore : Returns String number of CPU cores
- get_gpu     : Returns String of GPU name
- get_mem     : Returns Int Amount of Memory (Kilobytes)
- get_user    : Returns String of Current user
- version     : Returns String of Module Version


# Built With

- C
- Python (for setup script)

# CONTACT 

If you have any issues or questions, please contact me at the following;

	kcTranslationServices@gmx.com
	https://kc101010.itch.io/passwiz-password-generator


# Authored by Project Developer - Kyle Christie (kc101010) ###

    https://github.com/kc101010
    https://kc101010.itch.io
    https://www.sololearn.com/Profile/4051735
    https://www.codecademy.com/profiles/blueboikc





