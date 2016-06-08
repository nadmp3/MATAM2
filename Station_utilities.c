#include "Station_utilities.h"
#include "Station.h"
#include <assert.h>
#include <string.h>

/* a helper function - retrieves all the person details in one stroke.
   returns Station_utilities if all the details were retrieved successfully,
           Station_FAIL otherwise
 */
static StationResult station_get_details(Station station, int* line_use,char* Station_name) {//"return" detials
    StationResult status;

    assert(station != NULL && line_use != NULL && Station_name != NULL);
    status = Station_get_use(station,line_use);//get use
    if(status != Station_SUCCESS) {
        return Station_FAIL;
    }
    
    status = Station_get_Station_name(station,Station_name);//get station name
    if(status != Station_SUCCESS) {
        return Station_FAIL;
    }

    return Station_SUCCESS;
}

void* copy_station(void* elm) {//return element

    return elm;
}

void free_station(void* elm){//free element
    Station_destroy((Station)elm);
}

void print_station(FILE* outstream,void* elm){
    Station station = (Station)elm;
    int line_use;
    char Station_name[MAX_LEN];
    StationResult status;
    int print_status;
    
    assert(outstream != NULL && elm != NULL);
    status = station_get_details(station,&line_use,Station_name);
    assert(status == Station_SUCCESS);

    print_status = mtmPrintStationName(outstream,Station_name);
}

int compare_station(void* elm1, void* elm2){//return int>0 if elm1 > elm2
    Station station1 = (Station)elm1;
    Station station2 = (Station)elm2;
    char* Station_name1;
    char* Station_name2;
    StationResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Station_get_Station_name(station1,Station_name1);//get Station_name1
    assert(status == Station_SUCCESS);

    status = Station_get_Station_name(station2,Station_name2);//get Station_name2
    assert(status == Station_SUCCESS);

       return strcmp(Station_name1, Station_name2) ;//return "//get Station_name1"-"//get Station_name2"
    
}

int match_by_Station_name(void* elm, void* key){//return 1 when elm=key
    Station station = (Station)elm;
    char* key_Station_name = (char*)key;//turn key to string
    char Station_name[MAX_LEN];
    StationResult status;

    assert(elm != NULL && key != NULL);
    status = Station_get_Station_name(station,Station_name);//get station name
    assert(status == Station_SUCCESS);
    if(strcmp(Station_name,key_Station_name) == 0){//return "station name"-"key"
        return 1;
    }
        return 0;
}
