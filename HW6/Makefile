CXXFLAGS = -g -Wall -c -fpic
CLINK = $(CXX)
CXX = g++
RM = rm -rf *.o *.exe
CPPS = ip.cpp  port.cpp string.cpp
OBJ = ip.o port.o string.o
LIB = libfirewall.so



firewall.exe: $(LIB) $(OBJ) $(CPPS) main.o
	$(CXX)  -g -Wall $(OBJ) main.o -o firewall.exe -L. -lfirewall -L. -linput

libfirewall.so: $(OBJ)
	$(CLINK) -shared $(OBJ) -o $(LIB)

main.o: main.cpp string.h ip.h input.h port.h generic-field.h
		$(CXX) -g -Wall -c -c -fpic main.cpp

ip.o:  ip.h ip.cpp generic-field.h
	$(CXX) $(CXXFLAGS) ip.cpp
	
port.o: port.cpp port.h generic-field.h
	$(CXX) $(CXXFLAGS) port.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) string.cpp



clean:
	$(RM) $(LIB)
