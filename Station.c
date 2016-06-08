#include "Station.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct Station_t {
    int line_use;//how many station use this line
	char* Station_name;
};



StationResult Station_create(Station* station,  const char* Station_name) {//add new station

    Station new_Station = NULL;
    StationResult status;

    if(station == NULL || Station_name == NULL){//check if arguments are ok
        return Station_BAD_ARGUMENTS;//error
    }

	new_Station =                           //set space for new sation
		(Station) malloc(sizeof(struct Station_t));

	if(new_Station == NULL){           //check succses for set spaces 
	
		return Station_OUT_OF_MEMORY;
	}
	
	new_Station->Station_name = NULL;  
    status = Station_set_Station_name(new_Station,Station_name);//set station name 
    if(status != Station_SUCCESS){//check sucsess for set station name
		free(new_Station); //realse space
        return status;
	}

	
    new_Station->line_use = 0;//no line use this station yet

	*station = new_Station;
	return Station_SUCCESS;
}

StationResult Station_destroy(Station station) {//delete station
    if(station == NULL){//check if station is allready empty
        return Station_SUCCESS;
    } 
    free(station->Station_name);//realse station name
	free(station);//realse station
	return Station_SUCCESS;
}

StationResult Station_get_use(Station station,/*output*/int* use){
    if(station == NULL || use == NULL) {
        return Station_BAD_ARGUMENTS;
    }

    *use = station->line_use;//point to line use
    return Station_SUCCESS;
}

StationResult Station_set_use(Station station,/*input*/int use){
    if(station == NULL ) {
        return Station_BAD_ARGUMENTS;
    }

    station->line_use=use;//point to line use
    return Station_SUCCESS;
}

StationResult Station_get_Station_name(Station station, /*output*/char* Station_name){
    if(station == NULL || Station_name == NULL) {
        return Station_BAD_ARGUMENTS;
    }

    strcpy(Station_name,station->Station_name);//"return" station name
    return Station_SUCCESS;
}



StationResult Station_set_Station_name(Station station, const /*input*/char* Station_name){
    int name_length = 0;

    if(station == NULL ) {
        return Station_BAD_ARGUMENTS;
    }
    
    if(Station_name != station->Station_name){
        free(station->Station_name);
    }

    name_length = strlen(Station_name);
    assert(name_length + 1 < MAX_LEN);
    
    station->Station_name = (char *)malloc(sizeof(char)*(name_length+1));//make space
	if(station->Station_name == NULL) {//check make space
        return Station_OUT_OF_MEMORY;
	}
    strcpy(station->Station_name,Station_name);//"return" station name 
    return Station_SUCCESS;
}


