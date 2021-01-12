## Describe
	**This version only verifies the Single line n301 radar**
	**The driver is developed with linux c++, and supports Four threads**


## Compile and package
```
g++ -o  main  main.cpp -L ./  -ltiger -lpthread
export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
```

## Run
```
./main
```



