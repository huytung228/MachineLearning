CC=g++
ML_ROOT := $(PWD)
INCLUDE_DIR := $(ML_ROOT)/inc
SRC := $(ML_ROOT)/src
CFLAGS := -shared -std=c++11 -g

LIB_DATA := libdata.so

all : $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o lib/$(LIB_DATA) obj/*.o

libdir: 
	mkdir -p $(ML_ROOT)/lib

objdir: 
	mkdir -p $(ML_ROOT)/obj

obj/data_handler.o: $(SRC)/data_handler.cc 
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC)/data_handler.cc

obj/data.o: $(SRC)/data.cc 
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cc

clean:
	rm -r $(ML_ROOT)/lib
	rm -r $(ML_ROOT)/obj
