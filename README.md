# Perceptron_cpp
Programm for a project in CS. Comments are on french.

> The objectif of this programm is to learn manuscrite writing from the mnist database.

It is Cmake based.

Compiling
-
For compiling just do: 
- cd build/
- cmake ../ && make

Running
-
- cd build/
- ./perceptron++ [numofCycles]

NumOfcycle of learning of on the traning dataset
when all the cycles are done we run on the test dataset

Dependencies
-
- Cmake 3.9
- OpenCV
- The Boost library for ublas
- C++11

 all this dependecies are installable on linux with the command line
 --
 > Archlinux
- pacman -S opencv boost cmake gtkgltext hdf5


> Debian/Ubuntu
base-devel might be necessary
- sudo apt-get install cmake libopencv-dev libboost-dev








