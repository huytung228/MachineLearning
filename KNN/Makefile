CC=g++
KNN_ROOT := $(PWD)

INCLUDE_DIR := $(KNN_ROOT)/inc
INCLUDE_DIR += $(KNN_ROOT)/../MNISTDataset/inc

SRC := $(KNN_ROOT)/src
CFLAGS := -std=c++11 -g

TARGET := Knn_Alg

all : $(TARGET)

$(TARGET) : bindir objdir obj/knn.o obj/main.o
	$(CC) $(CFLAGS) -o bin/$(TARGET) obj/*.o
	#rm -r $(KNN_ROOT)/obj

bindir: 
	mkdir -p $(KNN_ROOT)/bin

objdir: 
	mkdir -p $(KNN_ROOT)/obj

obj/knn.o: $(SRC)/knn.cc 
	$(CC) $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC)/knn.cc

obj/main.o: $(SRC)/main.cc 
	$(CC) $(CFLAGS) -o obj/main.o -I$(INCLUDE_DIR) -c $(SRC)/main.cc

clean:
	rm -r $(KNN_ROOT)/bin
	rm -r $(KNN_ROOT)/obj
