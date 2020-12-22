CC=g++
KNN_ROOT := $(PWD)

INCLUDE_DIR := -I$(KNN_ROOT)/inc
INCLUDE_DIR += -I$(KNN_ROOT)/../MNISTDataset/inc

LIB_DIR := -L$(KNN_ROOT)/../MNISTDataset/lib/

SRC := $(KNN_ROOT)/src
CFLAGS := -std=c++11 -g

TARGET := Knn_Alg

all : $(TARGET)

$(TARGET) : bindir objdir obj/knn.o obj/main.o
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(LIB_DIR) obj/*.o -ldata
	#rm -r $(KNN_ROOT)/obj

bindir: 
	mkdir -p $(KNN_ROOT)/bin

objdir: 
	mkdir -p $(KNN_ROOT)/obj

obj/knn.o: $(SRC)/knn.cc 
	$(CC) $(CFLAGS) -o obj/data_handler.o $(INCLUDE_DIR) -c $(SRC)/knn.cc

obj/main.o: $(SRC)/main.cc 
	$(CC) $(CFLAGS) -o obj/main.o $(INCLUDE_DIR) -c $(SRC)/main.cc

clean:
	rm -r $(KNN_ROOT)/bin
	rm -r $(KNN_ROOT)/obj
