HEADERS		= filter.h io_util.h parse.h
SRCS		= main.cpp $(HEADERS:.h=.cpp)
OBJS		= $(SRCS:.cpp=.o)
BIN			= parseRequirements
STD			= -std=c++11

$(BIN): $(OBJS)
	@echo "Linking..."
	g++ $(STD) $(OBJS) -o $(BIN)
	@echo "Done."

$(OBJS): $(SRCS) $(HEADERS)
	@echo "Compiling..."
	g++ $(STD) -c $(SRCS)
	@echo "Done"

clean:
	rm $(BIN) $(OBJS)

