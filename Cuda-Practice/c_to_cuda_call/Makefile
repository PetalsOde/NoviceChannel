CUDA_INSTALL_PATH:=/usr/local/cuda

CXX:=g++
CC:=gcc
LINK:=g++ -fPIC
NVCC:=nvcc

#includes
INCLUDES=-I.-I$(CUDA_INSTALL_PATH)/include

#Common Flags
COMMONFLAGS+=$(INCLUDES)
NVCCFLAGS+=$(COMMONFLAGS)
CXXFLAGS+=$(COMMONFLAGS)

LIB_CUDA:=-L$(CUDA_INSTALL_PATH)/lib -lcudart
OBJS = test.cu.o main.cpp.o
TARGET = exec
LINKLINE = $(LINK) -o $(TARGET) $(OBJS) $(LIB_CUDA)

.SUFFIXES:.c .cu .cpp .o

%.c.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.cu.o:%.cu 
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

%.cpp.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET):$(OBJS) Makefile
	$(LINKLINE)

