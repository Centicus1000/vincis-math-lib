rem Use this batch file to build morf for Visual Studio
rmdir /s /q build
mkdir build
cd build
cmake ..
cmake --build .
start vml.sln
