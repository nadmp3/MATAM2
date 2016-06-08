#include <stdio.h>
#include <string.h>#include "schedule.h"
#include "linked_list.h"
#include "set.h"
#include "mtm_ex2.h"
#include "Station.h"
#include "Station_utilities.h"
#include "Track.h"
#include "Track_utilities.h"
#include "Bus.h"
#include "Bus_utilities.h"
#include "Train.h"
#include "Train_utilities.h"
#include "functions.h"


#define EMPTY_BUS_LIST(bus) linkedListCreate(bus,copy_bus,free_bus,print_bus)
#define EMPTY_TRAIN_LIST(train) linkedListCreate(train,copy_train,free_train,print_train)
#define EMPTY_STATION_LIST(station) setCreate(station,compare_station,copy_station,free_station,print_station)
#define MAX_NUM 9999

struct schedule_t {
    LinkedList bus_l;
    LinkedList train_l;
    Set station_set;
};

ScheduleResult check_line_exist(LinkedList bus_l,LinkedList train_l, int line_number) {
               ListResult list_status;
               list_status = linkedListFind(bus_l,&line_number,match_by_line_bus);
               if (list_status == LIST_SUCCESS) {return SCHEDULE_LINE_ALREADY_EXISTS;}
               list_status = linkedListFind(train_l,&line_number,match_by_line_number_train);
               if (list_status == LIST_SUCCESS) {return SCHEDULE_LINE_ALREADY_EXISTS;}
               return SCHEDULE_LINE_DOESNT_EXIST;
}
Schedule scheduleCreate() {
         Schedule new_schedule = NULL;
         ListResult list_status;
         SetResult set_status;
         
         new_schedule = (Schedule) malloc(sizeof(struct schedule_t));
         if(new_schedule == NULL){
                       return NULL;
         }
         list_status = EMPTY_BUS_LIST(&(new_schedule->bus_l));
         if (list_status != LIST_SUCCESS) { return NULL;}
         list_status = EMPTY_TRAIN_LIST(&(new_schedule->train_l));
         if (list_status != LIST_SUCCESS) { return NULL;}
         set_status = EMPTY_STATION_LIST(&(new_schedule->station_set));
         if (set_status != SET_SUCCESS) {return NULL;}
         return new_schedule;
}
void scheduleDestroy(Schedule schedule) {    
     SetResult set_status;
     ListResult list_status;
     if (schedule == NULL) {return;}
     list_status = linkedListDestroy(schedule->bus_l);
     list_status = linkedListDestroy(schedule->train_l);
     set_status = setDestroy(schedule->station_set);
     free(schedule);
}
ScheduleResult scheduleRegisterStation(Schedule schedule, const char* stationName) {
               SetResult set_status;
               Station station_tmp;
               printf("test");
               Station_create(&station_tmp,stationName);

               set_status = setIsIn(schedule->station_set, station_tmp);
               if (set_status == SET_ELEMENT_EXISTS) {
                              Station_destroy(station_tmp);
                              return SCHEDULE_STATION_ALREADY_EXIST;
               }
               set_status = setAdd(schedule->station_set, station_tmp);
               if (set_status != SET_SUCCESS) {return SCHEDULE_NULL_ARG;}
               return SCHEDULE_SUCCESS;
}
ScheduleResult scheduleUnregisterStation(Schedule schedule, const char* stationName) {
               SetResult set_status;
               char station_name[MAX_LEN];
               int use;
               Station tmp_station = NULL;
               strcpy(station_name,stationName);
               set_status = setFind(schedule->station_set,(SetElement*)&tmp_station,&station_name,match_by_Station_name);
               if (set_status != SET_SUCCESS) {return SCHEDULE_STATION_DOESNT_EXIST;}
               if (Station_get_use(tmp_station,&use) != Station_SUCCESS) {return SCHEDULE_STATION_DOESNT_EXIST;}
               if (use > 0) { 
                       return SCHEDULE_STATION_IS_USED;
               }
               set_status = setRemove(schedule->station_set, tmp_station);
               if (set_status != SET_SUCCESS) {return SCHEDULE_STATION_DOESNT_EXIST;} //here prob
               return SCHEDULE_SUCCESS;
}
ScheduleResult
scheduleAddLine(Schedule schedule, MtmLineType type, int number,
							   const char* description, double price) {
                         ListResult list_status;
                         ScheduleResult status;
                         LinkedList bus_tmp = schedule->bus_l;
                         LinkedList train_tmp = schedule->train_l;
                         if (type == MTM_LINE_BUS) {
                                  status = check_data(type,number,MTM_TRAIN_INVALID,price);
                                  if (status == SCHEDULE_SUCCESS) {
                                     status = check_line_exist(bus_tmp,train_tmp,number);
                                     if (status != SCHEDULE_LINE_DOESNT_EXIST) { return status;}
                                     Bus new_bus = NULL;
                                     BusResult bus_status;
                                     bus_status = Bus_create(&new_bus,price,number,description);
                                     if (bus_status == Bus_SUCCESS) {
                                        list_status = linkedListInsertLast(schedule->bus_l,new_bus);
                                     }
                                  }
                                  return status;
                         }
                         if (type == MTM_LINE_TRAIN) {
                                  MtmTrainType train_type = change_to_mtm_train(description);
                                  status = check_data(type,number,train_type,price);
                                  if (status == SCHEDULE_SUCCESS) {
                                             status = check_line_exist(bus_tmp,train_tmp,number);
                                             if (status != SCHEDULE_LINE_DOESNT_EXIST) { return status;}
                                             Train new_train = NULL;
                                             TrainResult train_status;
                                             train_status = Train_create(&new_train,price,number,train_type);
                                             if (train_status == Train_SUCCESS) {
                                                              list_status = linkedListInsertLast(schedule->train_l,new_train);
                                             }
                                  }
                                  return status;
                         }
                         return SCHEDULE_INVALID_TRAIN_TYPE;
}
ScheduleResult scheduleRemoveLine(Schedule schedule, MtmLineType type, int number) {
                 ListResult list_status;
                 ScheduleResult status;
                 LinkedList bus_tmp = schedule->bus_l;
                 LinkedList train_tmp = schedule->train_l;
                 if (check_line_number(number) == 0) {return SCHEDULE_INVALID_LINE_NUMBER;}
                 status = check_line_exist(bus_tmp,train_tmp,number);
                 if (status == SCHEDULE_LINE_DOESNT_EXIST) {return status;}
                 if (type == MTM_LINE_BUS) {
                          list_status = linkedListRemoveCurrent(bus_tmp);
                          return SCHEDULE_SUCCESS;
                 }
                 if (type == MTM_LINE_TRAIN) {
                          list_status = linkedListRemoveCurrent(train_tmp);
                          return SCHEDULE_SUCCESS;
                 }
                 return SCHEDULE_INVALID_TRAIN_TYPE;
}
ScheduleResult scheduleAddStationToLine(Schedule schedule, MtmLineType type, int number, 
						 const char* station, int time) {
                 ListResult list_status;
                 ScheduleResult status;
                 SetResult set_status;
                 Set station_list = schedule->station_set;
                 LinkedList bus_tmp = schedule->bus_l;
                 LinkedList train_tmp = schedule->train_l;
                 Station station_tmp;
                 if (check_line_number(number) == 0) {return SCHEDULE_INVALID_LINE_NUMBER;}
                 status = check_line_exist(bus_tmp,train_tmp,number);
                 if (status == SCHEDULE_LINE_DOESNT_EXIST) {return status;}
                 set_status = setFind(station_list,(SetElement*)&station_tmp,&station,match_by_Station_name);
                 if (set_status != SET_SUCCESS) {return SCHEDULE_STATION_DOESNT_EXIST;}
                 if (type == MTM_LINE_BUS) {
                          Bus line_bus = NULL;
                          BusResult bus_status;
                          list_status = linkedListFind(bus_tmp,&number,match_by_line_bus);
                          list_status = linkedListGetCurrent(bus_tmp,(ListElement*)&line_bus);
                          bus_status = check_bus_station(line_bus,station_tmp);
                          if (bus_status == Bus_SUCCESS) {return SCHEDULE_STATION_ALREADY_EXIST;}
                          bus_status = add_station_bus(line_bus,station_tmp,time);
                          if (bus_status != Bus_SUCCESS) {return SCHEDULE_INVALID_TIME;}
                          return SCHEDULE_SUCCESS;
                 }
                 if (type == MTM_LINE_TRAIN) {
                          Train line_train = NULL;
                          TrainResult train_status;
                          list_status = linkedListFind(train_tmp,&number,match_by_line_number_train);
                          list_status = linkedListGetCurrent(train_tmp,(ListElement*)&line_train);
                          train_status = check_train_station(line_train,station_tmp);
                          if (train_status != Train_SUCCESS) {return SCHEDULE_INVALID_TIME;}
                          return SCHEDULE_SUCCESS;
                 }
                 return SCHEDULE_INVALID_TRAIN_TYPE;
}     
ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, MtmLineType type, int number, int index) {
               ListResult list_status;
               ScheduleResult status;
               LinkedList bus_tmp = schedule->bus_l;
               LinkedList train_tmp = schedule->train_l;
               if (check_line_number(number) == 0) {return SCHEDULE_INVALID_LINE_NUMBER;}
               status = check_line_exist(bus_tmp,train_tmp,number);
               if (status == SCHEDULE_LINE_DOESNT_EXIST) {return status;}
               if (type == MTM_LINE_BUS) {
                        Bus line_bus = NULL;
                        BusResult bus_status;
                        list_status = linkedListFind(bus_tmp,&number,match_by_line_bus);
                        list_status = linkedListGetCurrent(bus_tmp,(ListElement*)&line_bus);
                        bus_status = remove_station_bus(line_bus,index);
                        if (bus_status != Bus_SUCCESS) {return SCHEDULE_INVALID_STATION_INDEX;}
                        return SCHEDULE_SUCCESS;
               }
               if (type == MTM_LINE_TRAIN) {
                          Train line_train = NULL;
                          TrainResult train_status;
                          list_status = linkedListFind(train_tmp,&number,match_by_line_number_train);
                          list_status = linkedListGetCurrent(train_tmp,(ListElement*)&line_train);
                          train_status = remove_station_train(line_train,index);
                          if (train_status != Train_SUCCESS) {return SCHEDULE_INVALID_STATION_INDEX;}
                          return SCHEDULE_SUCCESS;
               }
               return SCHEDULE_INVALID_TRAIN_TYPE;
}
ScheduleResult scheduleReportRegisteredStations(Schedule schedule) {
               SetResult set_status;
               Set station_list = schedule->station_set;
               if (station_list = NULL) {return SCHEDULE_NO_STATIONS;}
               set_status = setPrint(station_list,stdout,MAX_NUM);
               return SCHEDULE_SUCCESS;
}
ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number) {
               ListResult list_status;
               LinkedList list_tmp = schedule->bus_l;
               if (check_line_number(number) == 0) {return SCHEDULE_INVALID_LINE_NUMBER;}
               list_status = linkedListFind(list_tmp,&number,match_by_line_bus);
               if (list_status =  LIST_SUCCESS) {
                  linkedListPrint(list_tmp,stdout,1);
                  return SCHEDULE_SUCCESS;
               }
               list_tmp = schedule->train_l;
               list_status = linkedListFind(list_tmp,&number,match_by_line_number_train);
               if (list_status =  LIST_SUCCESS) {
                  linkedListPrint(list_tmp,stdout,1);
                  return SCHEDULE_SUCCESS;
               }
               return  SCHEDULE_LINE_DOESNT_EXIST;
}               
ScheduleResult scheduleReportLines(Schedule schedule, MtmLineType type) {
               ListResult list_status;
               LinkedList list_tmp = NULL;
               int count = 0;
               if ((type == MTM_LINE_TRAIN) || (type == MTM_LINE_ALL)) {
                         list_tmp = schedule->train_l;
                         list_status = linkedListSortElements(list_tmp,compare_train_type);
                         list_status = linkedListSortElements(list_tmp,match_by_line_number_train);
                         list_status = linkedListPrint(list_tmp,stdout,MAX_NUM);
                         count++;    
               } 
               if ((type == MTM_LINE_BUS) || (type == MTM_LINE_ALL)) {
                        list_tmp = schedule->bus_l;
                        list_status = linkedListSortElements(list_tmp,compare_bus_company_name);
                        list_status = linkedListSortElements(list_tmp,match_by_line_bus);
                        list_status = linkedListPrint(list_tmp,stdout,MAX_NUM);
                        count++;
               }
               if (count > 0) {return SCHEDULE_SUCCESS;}
               return SCHEDULE_NO_LINES;
}
ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule, const char* from, const char* to, double maximumPrice) {
               ListResult list_status;
               ListResult list_status_bus,list_status_train;
               SetResult set_status;
               Bus bus_tmp;
               Train train_tmp;
               LinkedList list_tmp = NULL;
               LinkedList list_train = schedule->train_l;
               LinkedList list_bus = schedule->bus_l;
               int print_ok =0;
               double price_bus = 0,price_train = 0;
               if (check_price(maximumPrice) == 0) {return SCHEDULE_INVALID_PRICE;}
               set_status = check_station(schedule->station_set,from);
               if (set_status == SET_ELEMENT_DOES_NOT_EXIST) {return SCHEDULE_STATION_DOESNT_EXIST;}
               set_status = check_station(schedule->station_set,to);
               if (set_status == SET_ELEMENT_DOES_NOT_EXIST) {return SCHEDULE_STATION_DOESNT_EXIST;}
               if ((linkedListGetNumElements(list_bus) == 0) && (linkedListGetNumElements(list_train) == 0)) {
                                                       return SCHEDULE_NO_LINES;
               }
               list_status = linkedListSortElements(list_train,match_by_line_number_train);
               list_status = linkedListSortElements(list_bus,match_by_line_bus);
               list_status = linkedListSortElements(list_train,compare_train_price);
               list_status = linkedListSortElements(list_bus,compare_bus_price);
               list_status_train = linkedListGoToHead(list_train);
               list_status_bus = linkedListGoToHead(list_bus);
               while ((list_status != LIST_FAIL) && (print_ok != 2)) {    
                     list_status_bus = linkedListGetCurrent(list_bus,(ListElement*)&bus_tmp);
                     if (list_status_bus != LIST_FAIL) {Bus_get_price(bus_tmp,&price_bus);}
                     list_status_train = linkedListGetCurrent(list_train,(ListElement*)&train_tmp);
                     if (list_status_train != LIST_FAIL) {Train_get_price(train_tmp,&price_train);}
                     if ((price_bus <= price_train) && (list_status_bus != LIST_FAIL)) {
                                   list_status = Bus_get_station_list(bus_tmp,(elem)&list_tmp);
                                   list_status = check_track(list_tmp,from,to);
                                   if (list_status == LIST_SUCCESS) {
                                                   print_bus(stdout,bus_tmp);
                                   }
                                   list_status_bus = linkedListGoToNext(list_bus);
                                   if (list_status_bus == LIST_FAIL) {print_ok++;}
                     }
                     else {
                          list_status = Train_get_station_list(train_tmp,(elemm)&list_tmp);
                          list_status = check_track(list_tmp,from,to);
                          if (list_status == LIST_SUCCESS) {
                                          print_train(stdout,train_tmp);
                          }
                          list_status_train = linkedListGoToNext(list_train);
                          if (list_status_train == LIST_FAIL) {print_ok++;}
                     }
                     if ((list_status_train == LIST_FAIL) && (list_status_bus == LIST_FAIL)) {list_status = LIST_FAIL;}
                     else {list_status = LIST_SUCCESS;}
               }
               return SCHEDULE_SUCCESS;
}
                                   
