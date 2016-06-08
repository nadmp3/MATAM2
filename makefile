#macro

CC = gcc
EXEC = mtm_schedule
OBJS =  Station.o Station_utilities.o Track.o Track_utilities.o\
Bus.o Bus_utilities.o Train.o Train_utilities.o functions.o schedule.o main.o
FLAG = -std=c99 -Wall -pedantic-errors -DNDEBUG 

#Main program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(FLAG) $(OBJS) -L. libmtm.a -o $@
	
#Objects 


Station.o: Station.c mtm_ex2.h schedule.h set.h \
linked_list.h Station.h
	$(CC) $(FLAG) -c $*.c  -o $@
	
Station_utilities.o: Station_utilities.c Station_utilities.h Station.h
	$(CC) $(FLAG) -c $*.c  -o $@
  
Track.o: Track.c mtm_ex2.h linked_list.h functions.h \
  Track.h Station.h
	$(CC) $(FLAG) -c $*.c  -o $@

Track_utilities.o: Track_utilities.c mtm_ex2.h Station.h Track.h
	$(CC) $(FLAG) -c $*.c  -o $@

Bus.o: Bus.c mtm_ex2.h schedule.h set.h linked_list.h \
  functions.h Track.h Bus.h Station.h
	$(CC) $(FLAG) -c $*.c -o $@

Bus_utilities.o: Bus_utilities.c mtm_ex2.h schedule.h set.h linked_list.h \
Bus.h Bus_utilities.h Station.h Track.h
	$(CC) $(FLAG) -c $*.c -o $@

Train.o: Train.c mtm_ex2.h schedule.h set.h linked_list.h \
  functions.h Station.h Track.h Train.h
	$(CC) $(FLAG) -c $*.c -o $@

Train_utilities.o: Train_utilities.c mtm_ex2.h schedule.h set.h linked_list.h \
  functions.h Station.h Track.h Train.h Train_utilities.h
	$(CC) $(FLAG) -c $*.c -o $@

functions.o: functions.c Station_utilities.h Station.h Track.h \
  schedule.h mtm_ex2.h
	$(CC) $(FLAG) -c $*.c -o $@
  	
schedule.o: schedule.c mtm_ex2.h schedule.h set.h linked_list.h \
  functions.h Station.h Station_utilities.h Track.h Bus.h Bus_utilities.h \
  Track_utilities.h Train.h Train_utilities.h
	$(CC) $(FLAG) -c $*.c -o $@

main.o: main.c schedule.h mtm_ex2.h
	$(CC) $(FLAG) -c $*.c -o $@

#clean

clean:
	rm -f $(OBJS) $(EXEC)
	


