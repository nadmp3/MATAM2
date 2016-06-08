#ifndef MAX_LEN
#define MAX_LEN 120 
#endif
typedef struct Station_t* Station;
typedef enum  {
    Station_SUCCESS,
    Station_FAIL,
    Station_BAD_ARGUMENTS,
    Station_OUT_OF_MEMORY
} StationResult;

StationResult Station_create(Station* station, const char* Station_name);//create adt
StationResult Station_destroy(Station station);//destroy adt

StationResult Station_get_use(Station station,/*output*/int* use);//get line uses

StationResult Station_set_use(Station station,/*input*/int use);//set line uses
StationResult Station_get_Station_name(Station station, /*output*/char* station_name);
//return station name 

StationResult Station_set_Station_name(Station station, const char* Station_name);
//change statin name
