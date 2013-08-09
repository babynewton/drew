ARCHIVE=libdml.a
OBJS=dml_parser.o

CXXFLAGS=-g -O2 -Wall -I../engine

all: $(OBJS)
	$(AR) rcu $(ARCHIVE) $(OBJS)

install:

clean:
	rm -f $(ARCHIVE) $(OBJS)
