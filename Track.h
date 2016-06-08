#ifndef MAX_LEN
#define MAX_LEN 120 
#endif
typedef struct Track_t* Track;
typedef enum  {
    Track_SUCCESS,
    Track_FAIL,
    Track_BAD_ARGUMENTS,
    Track_OUT_OF_MEMORY
} TrackResult;

TrackResult Track_create(Track* track, void *station, int time_from_first);//create adt
TrackResult Track_destroy(Track track);//destroy adt

TrackResult Track_get_time_from_first(Track track,/*output*/int* time_from_first);//get time
TrackResult Track_set_time_from_first(Track track,/*input*/int time_from_first);//set time

TrackResult Track_get_Station(Track track, /*output*/void *station);//get station

 

TrackResult Track_set_Station(Track track,/*input*/void *station);
//change statin name
