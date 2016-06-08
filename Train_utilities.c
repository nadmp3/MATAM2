#include "mtm_ex2.h"
#include "linked_list.h"
#include "Train_utilities.h"
#include "Train.h"
#include "Station.h"
#include "Station_utilities.h"
#include "Track.h"
#include "Track_utilities.h"
#include <assert.h>

static TrainResult train_get_details(Train train, double* Price,int* line_number,//get train detials
MtmTrainType* type) {
    TrainResult status;

    assert(train != NULL && Price != NULL && line_number != NULL && type!=NULL);
    status = Train_get_line_number(train,line_number);//get line number
    if(status != Train_SUCCESS) {
        return Train_FAIL;
    }
    
    status = Train_get_price(train,Price);//get price
    if(status != Train_SUCCESS) {
        return Train_FAIL;
    }
    
    status = Train_get_type(train,type);//get type
    if(status != Train_SUCCESS) {
        return Train_FAIL;
    }
    return Train_SUCCESS;
}

void* copy_train(void* elm) {

    return elm;
}

void free_train(void* elm){
    Train_destroy((Train)elm);
}

void print_train(FILE* outstream,void* elm){
    Train train = (Train)elm;
    int line_number;
    double Price;
    MtmTrainType type;
    char first_station[MAX_LEN];
    char last_station[MAX_LEN];
    Track station_tmp;
    Station station_cp;
    TrainResult status;
    StationResult station_status;
    int print_status;
    
    assert(outstream != NULL && elm != NULL);
    status = train_get_details(train, &Price,&line_number,&type);
    status = Train_get_Station(train,(elemm)&station_tmp);
    status = Track_get_Station(station_tmp,station_cp);
    station_status = Station_get_Station_name(station_cp,first_station);
    status = Train_get_last_Station(train,(elemm)&station_tmp);
    status = Track_get_Station(station_tmp,station_cp);
    station_status = Station_get_Station_name(station_cp,last_station);
    assert(status == Station_SUCCESS);
    print_status = mtmPrintTrainLine(outstream,line_number,type,first_station,last_station,Price);
}

int compare_train_type(void* elm1, void* elm2){
    Train train1 = (Train)elm1;
    Train train2 = (Train)elm2;
    int Train_line1;
    int Train_line2;
    MtmTrainType train_type1;
    MtmTrainType train_type2;
    TrackResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Train_get_type(train1,&train_type1);//get train_type1
    status = Train_get_line_number(train1,&Train_line1);//get Train_line1
    assert(status == Track_SUCCESS);
    status = Train_get_type(train1,&train_type2);//get train_type2
    status = Train_get_line_number(train2,&Train_line2);//get Train_line2
    assert(status == Station_SUCCESS);
    if (train_type1<train_type2)//train_type1<train_type2
       return -1 ;
    else if ((train_type1==train_type2)&&(Train_line1<Train_line2))//train_type1==train_type2 Train_line1<Train_line2
       return -1;
       else
       return 1;//elm2>elm1
}

int compare_train_price(void* elm1, void* elm2){
    Train train1 = (Train)elm1;
    Train train2 = (Train)elm2;
    int Train_line1;
    int Train_line2;
    double train_price1;
    double train_price2;
    TrackResult status;

    assert(elm1 != NULL && elm2 != NULL);
    status = Train_get_price(train1,&train_price1);//get train_price1
    status = Train_get_line_number(train1,&Train_line1);//Train_line1
    assert(status == Track_SUCCESS);
    status = Train_get_price(train2,&train_price2);//train_price2
    status = Train_get_line_number(train2,&Train_line2);//get Train_line2
    assert(status == Station_SUCCESS);
    if (train_price1<train_price2)//elm1<elm2
       return -1 ;
    else if ((train_price1==train_price2)&&(Train_line1<Train_line2))//elm1<elm2
       return -1;
       else
       return 1;//elm2>elm1
}

int match_by_line_number_train(void* elm, void* key){//cheak if key = line number
    Train train1 = (Train)elm;
    int key_train_line;
    int train_line;
    TrackResult status;

    assert(elm != NULL && key != NULL);
    key_train_line = *(int*)key;
    status = Train_get_line_number(train1,&train_line);//get line number
    
    assert(status == Station_SUCCESS);
    if(train_line==key_train_line){//cheak if key = line number
        return 1;
    }
        return 0;
}
