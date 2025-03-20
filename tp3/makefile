CXX = gcc
LDFLAGS =   --coverage
LDLIBS_CMOCKA = -llibcmocka
OPTION = -Wall -fexceptions  -fprofile-arcs -ftest-coverage
INCS = -I.  -I"." 
OBJS = $(SRC:.c=.o)

SRC = compute.c  main.c cmocka.o

all: $(OBJS)
	$(CXX)  $(LDFLAGS) $(INCS)  -o testAll  $(OBJS)
exec : all
	./testAll
%.o: %.c
	$(CXX) $(OPTION) -c  $< -o $@ $(INCS)	
clean:
	rm $(OBJS) 
mrproper: clean
	rm testAll
	rm *.gcda
	rm *.gcno
	rm *.gcov

