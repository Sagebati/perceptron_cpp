# Perceptron_cpp
Programm for a project in CS. Commentaries are on french, but i will try to change that on the future.

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
- Ex: pacman -S opencv boost cmake gtkgltext hdf5

base-devel might be necessary
> Arhclinux
- Ex: sudo apt-get install cmake libopencv-dev libboost-dev
>Debian/Ubuntu







