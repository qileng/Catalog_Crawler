HEADERS		= filter.h io_util.h parse.h
SRCS		= main.cpp $(HEADERS:.h=.cpp)
OBJS		= $(SRCS:.cpp=.o)
BIN			= ../bin/parseRequirements
STD			= -std=c++11
PATH		= ../headers
TEMP		= ../temp

$(BIN): $(OBJS)
	@echo "Linking..."
	g++ -I $(PATH) $(STD) $(OBJS) -o $(BIN)
	@echo "Done."

$(OBJS): $(SRCS)
	@echo "Compiling..."
	g++ -I $(PATH) $(STD) -c $(SRCS)
	@echo "Done"

clean:
	rm $(BIN) $(OBJS)
	rm -r $(TEMP)

