#include <string.h>
#include "schedule.h"
#include "linked_list.h"
#include "set.h"
#include "Station.h"
#include "Station_utilities.h"
#include "Track.h"

int check_line_number(int line_number) {
    if (line_number < 0 || line_number > 9999) {
                    return 0;
    }
    return 1;
}
int check_price(double price) {
    if (price < 0) return 0;
    return 1;
}
MtmTrainType change_to_mtm_train(const char* train_type) {
             if (strcmp(train_type,"direct") == 0) {
                                             return MTM_TRAIN_DIRECT;
             }
             if (strcmp(train_type,"intercity") == 0) {
                                                return MTM_TRAIN_INTERCITY;
             }
             if (strcmp(train_type,"suburban") == 0) {
                                               return MTM_TRAIN_SUBURBAN;
             }
             return MTM_TRAIN_INVALID;
}
ScheduleResult check_data(MtmLineType type, int number, MtmTrainType train_type, double price) {
               if (check_line_number(number) == 0) {
                                             return SCHEDULE_INVALID_LINE_NUMBER;
               }
               if (check_price(price) == 0) {
                                      return SCHEDULE_INVALID_PRICE;
               }
               if ((type == MTM_LINE_TRAIN) && (train_type == MTM_TRAIN_INVALID)) {
                              return SCHEDULE_INVALID_TRAIN_TYPE;
               }
               return SCHEDULE_SUCCESS;
}
ListResult check_track(LinkedList station_list, const char* from, const char* to) {
    ListResult status;
    LinkedList station_tmp = station_list;
    Station station;
    StationResult station_status;
    char station_name[MAX_LEN];
    int ok_to_run = 0;
    status = linkedListGoToHead(station_tmp);
    while ((status != LIST_FAIL) && (ok_to_run != 2)) {
          status = linkedListGetCurrent(station_tmp,(ListElement*)&station);
          if (ok_to_run == 0) {
                        station_status = Station_get_Station_name(station,station_name);
                        if (strcmp(station_name,from) == 0) {ok_to_run++;}
          }
          else {
               station_status = Station_get_Station_name(station,station_name);
               if (strcmp(station_name,to) == 0) {ok_to_run++;}
          }
          status = linkedListGoToNext(station_tmp);
    }
    if (ok_to_run == 2) {return LIST_SUCCESS;}
    else {return LIST_FAIL;}
}
SetResult check_station(Set set, const char* station) {
          Station station_tmp;
          SetResult set_status;
          SetResult set_status1;
          Station_create(&station_tmp,station);
          set_status = setIsIn(set, station_tmp);
          set_status1 = Station_destroy(station_tmp);
          return set_status;
}
                              
