CXX:=g++



LIB_CUDA:=-L$(CUDA_INSTALL_PATH)/lib -lcudart
OBJS = main.o  data_interface.o  printdata.o
TARGET = exec
LINKLINE = $(CXX) -o $(TARGET) $(OBJS) 




.SUFFIXES:.cpp .o




%.cpp.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@




$(TARGET):$(OBJS) Makefile
	$(LINKLINE)

