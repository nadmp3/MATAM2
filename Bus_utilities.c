#include "mtm_ex2.h"
#include "Track.h"
#include "Station.h"
#include "Bus_utilities.h"
#include "Bus.h"
#include <string.h>
#include <assert.h>
static BusResult bus_get_details(Bus bus, double* Price,int* line_number,char* company_name) {
    BusResult status;

    assert(bus != NULL && Price != NULL && line_number != NULL && company_name!=NULL);
    status = Bus_get_line_number(bus,line_number);
    if(status != Bus_SUCCESS) {
        return Bus_FAIL;
    }
    
    status = Bus_get_price(bus,Price);
    if(status != Bus_SUCCESS) {
        return Bus_FAIL;
    }
    
    status = Bus_get_company_name(bus,company_name);
    if(status != Bus_SUCCESS) {
        return Bus_FAIL;
    }
    return Bus_SUCCESS;
}

void* copy_bus(void* elm) {

    return elm;
}

void free_bus(void* elm){
    Bus_destroy((Bus)elm);
}

void print_bus(FILE* outstream,void* elm){
    Bus bus = (Bus)elm;
    int line_number;
    double Price;
    char company_name[MAX_LEN];
    char first_station[MAX_LEN];
    char last_station[MAX_LEN];
    BusResult status;
    int print_status;
    Track station_tmp;
    Station station_cp;
    StationResult station_status;
    assert(outstream != NULL && elm != NULL);
    status = bus_get_details(bus,&Price,&line_number,company_name);
    status = Bus_get_Station(bus,(elem)&station_tmp);
    status = Track_get_Station(station_tmp,station_cp);
    station_status = Station_get_Station_name(station_cp,first_station);
    status = Bus_get_last_Station(bus,(elem)&station_tmp);
    status = Track_get_Station(station_tmp,station_cp);
    station_status = Station_get_Station_name(station_cp,last_station);
    assert(status == Bus_SUCCESS);
    print_status = mtmPrintBusLine(outstream,line_number,company_name,first_station,last_station,Price);
}

int compare_bus_company_name(void* elm1, void* elm2){
    Bus bus1 = (Bus)elm1;
    Bus bus2 = (Bus)elm2;
    char* company_name1;
    char* company_name2;
    int line1;
    int line2;
    BusResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Bus_get_company_name(bus1,company_name1);
    status = Bus_get_line_number(bus1,&line1);
    assert(status == Bus_SUCCESS);

    status = Bus_get_company_name(bus2,company_name2);
    status = Bus_get_line_number(bus2,&line2);
    assert(status == Bus_SUCCESS);
    if (strcmp(company_name1, company_name2) < 0)
       {return -1 ;}
    else if ((strcmp(company_name1, company_name2)==0) && (line1<line2)) {return -1;}
         else {return 1;}
}

int compare_bus_price(void* elm1, void* elm2){//1 if first is equel or biger
    Bus bus1 = (Bus)elm1;
    Bus bus2 = (Bus)elm2;
    int Bus_line1;
    int Bus_line2;
    double Bus_price1;
    double Bus_price2;
    BusResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Bus_get_price(bus1,&Bus_price1);
    status = Bus_get_line_number(bus1,&Bus_line1);
    assert(status == Bus_SUCCESS);
    status = Bus_get_price(bus2,&Bus_price2);
    status = Bus_get_line_number(bus2,&Bus_line2);
    assert(status == Bus_SUCCESS);
    if (Bus_price1<Bus_price2)
       return -1 ;
    else if ((Bus_price1==Bus_price2)&&(Bus_line1<Bus_line2))
       return -1;
       else
       return 1;
}

int match_by_line_bus(void* elm, void* key){
    Bus bus = (Bus)elm;
    int key_line;
    int line;
    BusResult status;

    assert(elm != NULL && key != NULL);
    key_line = *(int*)key;
    status = Bus_get_line_number(bus,&line);
    assert(status == Bus_SUCCESS);
    if(line==key_line){
        return 1;
    }
        return 0;
}

int match_by_price_bus(void* elm, void* key){
    Bus bus1 = (Bus)elm;
    double *key_price;
    double bus_price;
    TrackResult status;
    key_price = (double*)key;
    assert(elm != NULL && key != NULL);
    status = Bus_get_price(bus1,&bus_price);
    assert(status == Bus_SUCCESS);
    if(bus_price==*key_price){
        return 1;
    }
        return 0;
}
