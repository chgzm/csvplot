PROGRAM := csvplot
OBJS := Main.o CsvParser.o GnuplotPipe.o
CXX := g++
FLGS := -std=c++14
CXXFLAGS := -Wall -O2

.PHONY: all
$(PROGRAM): $(OBJS)
	$(CXX) $(FLGS) $(CXXFLAGS) -o $(PROGRAM) $(OBJS)

.cpp.o:
	$(CXX) $(FLGS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGRAM)
