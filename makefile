CXX = gcc

INCS = -I.  -I"." 
OBJS = $(SRC:.c=.o)

SRC = ratp.c  main.c cmocka.o


all: $(OBJS)
	$(CXX)  $(INCS) -o testAll  $(OBJS)

	
exec : all
	testAll.exe
%.o: %.c
	$(CXX)  -c  $< -o $@ $(INCS)
	
clean:
	rm $(OBJS) 


mrproper: clean
	rm testAll
	rm result.xml