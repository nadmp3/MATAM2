#include "Track.h"
#include "Station.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
struct Track_t {
    int time_from_first;
	Station* station;
};

TrackResult Track_create(Track* track, void *station, int time_from_first) {

    Track new_track = NULL;
    TrackResult status;
    Station station_tmp = (Station) station;

    if(track == NULL || station == NULL){//check if arguments or ok
        return Track_BAD_ARGUMENTS;//error
    }

	new_track =                           //make space
		(Track) malloc(sizeof(struct Track_t));

	if(new_track == NULL){//check make space
		return Track_OUT_OF_MEMORY;
	}
	
	new_track->station = NULL;
    status = Track_set_Station(new_track,station_tmp);//set station
    if(status != Track_SUCCESS){//check set station
		free(new_track);//free space
        return status;
	}

	
    new_track->time_from_first = time_from_first;

	*track = new_track;
	return Track_SUCCESS;
}

TrackResult Track_destroy(Track track){
    if(track == NULL){//if track is empty
        return Track_SUCCESS;
    }
    free(track->station);//free station
	free(track);//free track
	return Track_SUCCESS;
}

TrackResult Track_get_time_from_first(Track track,/*output*/int* time_from_first){//"return" time
    if(track == NULL || time_from_first == NULL) {
        return Track_BAD_ARGUMENTS;
    }

    *time_from_first = track->time_from_first;//"return" time
    return Track_SUCCESS;
}

TrackResult Track_set_time_from_first(Track track,/*input*/int time_from_first){//set time
    if(track == NULL ) {
        return Track_BAD_ARGUMENTS;
    }

    track->time_from_first=time_from_first;//set time
    return Track_SUCCESS;
}

TrackResult Track_get_Station(Track track, /*output*/void *station){//"return" station
    Station station_tmp = (Station) station;
    if(track == NULL || station == NULL) {
        return Track_BAD_ARGUMENTS;
    }
    station_tmp = (Station)track->station;//"return" station
    return Track_SUCCESS;
}

TrackResult Track_set_Station(Track track,/*input*/void *station){//set station

    Station station_tmp = (Station) station;
    if(track == NULL || station_tmp == NULL) {
        return Track_BAD_ARGUMENTS;
    }
    
    if(station_tmp != *(track->station)){
        free(track->station);
    }

    
    track->station = &station_tmp;

    return Track_SUCCESS;
}
