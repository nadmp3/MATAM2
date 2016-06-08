typedef void* elem;
typedef struct Bus_t* Bus;
typedef enum  {
    Bus_SUCCESS,
    Bus_FAIL,
    Bus_BAD_ARGUMENTS,
    Bus_OUT_OF_MEMORY
} BusResult;

BusResult Bus_create(Bus* bus, double Price,int line_number, const char* company_name);//create adt
BusResult Bus_destroy(Bus bus);//destroy adt

BusResult Bus_get_line_number(Bus bus,/*output*/int* line_number);//get line number


BusResult Bus_get_price(Bus bus,/*output*/double* Price);//get price

BusResult Bus_get_company_name(Bus bus,/*output/input*/char* company_name);//get company name

BusResult Bus_get_Station(Bus bus, /*output*/elem* station);//get station track

BusResult Bus_get_last_Station(Bus bus, /*output*/elem* station_last);//get last station track

BusResult move_next_station_bus(Bus bus);//move to next station in track

BusResult Bus_set_company_name(Bus bus,const char* company_name);//set company name

BusResult move_to_head_station_bus(Bus bus);//move to head track
BusResult add_station_bus(Bus bus,elem station,int time);//add new station
BusResult remove_station_bus(Bus bus,int index);//remove station
BusResult check_bus_station(Bus bus, elem station);
BusResult Bus_get_station_list(Bus bus, elem* list);

