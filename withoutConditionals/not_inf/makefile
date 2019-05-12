CXX       = g++
CXXFLAGS  = --std=c++17 
LIBS      = -lgtest -lpthread 
SRCS      = $(wildcard *.cpp) 
OBJS      = $(filter %.o,$(SRCS:.cpp=.o) $(SRCS:.cc=.o))

logger: $(OBJS)
	$(CXX) -g $(OBJS) -o $@ $(LIBS)  

valgrind_logger : $(OBJS)
	$(CXX) -g $(OBJS) -o $@ $(LIBS)  

%.o: %.cc 
	$(CXX) -g $(CXXFLAGS) -c $< -O0 -o $@

clean:
	@rm -f *.o
	@rm -f logger

.PHONY: clean valgrind
