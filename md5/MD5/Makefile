PROCESS_DIR=$(HOME)/GenMp4
INCLUDE_DIR=$(PROCESS_DIR)/inc
LIB_DIR=$(PROCESS_DIR)/lib
BIN_DIR=$(PROCESS_DIR)/bin

libmd5.so: md5.o
	g++ -std=c++11 -fPIC -o libmd5.so -shared -m64 md5.o
md5.o: md5.cpp md5.h
	g++ -m64 -std=c++11 -fPIC -g -fstack-protector-all -Wall -c $<  -I$(PROCESS_DIR)/inc
install:
	cp  libmd5.so  $(LIB_DIR)/
	cp md5.h $(INCLUDE_DIR)/
clean:
	rm -rf  libmd5.so md5.o
