typedef void* elemm;
typedef struct Train_t* Train;
typedef enum  {
    Train_SUCCESS,
    Train_FAIL,
    Train_BAD_ARGUMENTS,
    Train_OUT_OF_MEMORY
} TrainResult;

TrainResult Train_create(Train* train, double Price,int line_number, int type);//create adt
TrainResult Train_destroy(Train train);//destroy adt

TrainResult Train_get_line_number(Train train,/*output*/int* line_number);


TrainResult Train_get_price(Train train,/*output*/double* Price);


TrainResult Train_get_type(Train train,/*output/input*/elemm type);


TrainResult Train_get_Station(Train train, /*output*/elemm* station);//return station name 


TrainResult Train_get_last_Station(Train train, /*output*/elemm* station_last);//return station name 


TrainResult move_next_station_train(Train train);//move to next station in track
TrainResult move_to_head_station_train(Train train);//move to head track
TrainResult add_station_train(Train train,elemm station,int time);//add new station
TrainResult remove_station_train(Train train,int index);//remove station
TrainResult check_train_station(Train train, elemm station);
TrainResult Train_get_station_list(Train train, elemm* list);




