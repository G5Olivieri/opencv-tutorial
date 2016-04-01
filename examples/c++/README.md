# Examples

## Env

- Qt Creator 3.6.1
- Qt 5.6
- MSVC 2013
- OpenCV 3.1

### **Dir Tree**
```
c++
├── qt_hello_world
├── qt_skin_detection
├── qt_edge_detection
│
├── lib
│   └── opencv
│       └── x64
│           └── vc12
│               └── bin
│               └── include
│               └── lib
```

### **Build Dlib**
```bat
cd examples
mkdir build
cd build
cmake -G "Visual Studio 12 2013" ..
cmake --build . --config Release
```

### **Build OpenCV**
```bat
cmake -G "Visual Studio 12 2013" .. -DOPENCV_EXTRA_MODULES_PATH=...\opencv\sources\modules\contrib\modules ...\opencv\sources
cmake --build . --config Release
```