#include "mtm_ex2.h"
#include "Track_utilities.h"
#include "Track.h"
#include "Station.h"
#include <assert.h>
static TrackResult track_get_details(Track track, int* time_from_first,Station* station) {//get deteils
    TrackResult status;

    assert(track != NULL && time_from_first != NULL && station != NULL);
    status = Track_get_time_from_first(track,time_from_first);//get time
    if(status != Track_SUCCESS) {
        return Track_FAIL;
    }
    
    status = Track_get_Station(track,station);//get station
    if(status != Track_SUCCESS) {
        return Track_FAIL;
    }

    return Track_SUCCESS;
}

void* copy_track(void* elm) {

    return elm;
}

void free_track(void* elm){
    Track_destroy((Track)elm);
}

void print_track(FILE* outstream,void* elm){
    Track track = (Track)elm;
    int time_from_first;
    Station* station;
    char Station_name[MAX_LEN];
    TrackResult status;
    int print_status;
    
    assert(outstream != NULL && elm != NULL);
    status = track_get_details(track,&time_from_first,station);
    
    assert(status == Station_SUCCESS);
    Station_get_Station_name(*station,Station_name);
    print_status = mtmPrintLineStation(outstream,Station_name,time_from_first);
}

int compare_track(void* elm1, void* elm2){//copmre by station
    Track track1 = (Track)elm1;
    Track track2 = (Track)elm2;
    Station* track_ptr1;
    Station* track_ptr2;
    TrackResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Track_get_Station(track1,track_ptr1);//get station1
    assert(status == Station_SUCCESS);

    status = Track_get_Station(track2,track_ptr2);//get station2
    assert(status == Station_SUCCESS);
    if (track_ptr1==track_ptr2)//if station==1station2
       return 1 ;
    else
       return 0;
}

int match_by_time_from_first_from_start(void* elm, void* key){//match by time
    Track track1 = (Track)elm;
    int key_Station_time;//set key as int
    int Station_time;
    TrackResult status;

    assert(elm != NULL && key != NULL);
    key_Station_time = *(int*)key;
    status = Track_get_time_from_first(track1,&Station_time);//get time
    assert(status == Track_SUCCESS);
    if(Station_time==key_Station_time){//if time==key
        return 1;
    }
        return 0;
}
