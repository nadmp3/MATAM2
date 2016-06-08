#include "Train.h"
#include "mtm_ex2.h"
#include "Track.h"
#include "Track_utilities.h"
#include "linked_list.h"
#include "Station.h"
#include "Station_utilities.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct Train_t {
    int line_number;
	double Price;
	MtmTrainType type;
	LinkedList Station_first;
	Track *Station_last;
};

TrainResult Train_create(Train* train, double Price,int line_number,int type) {

    Train new_Train = NULL;

    if(train == NULL){//che(Track*)ck if arguments or ok
        return Train_BAD_ARGUMENTS;//error
    }

	new_Train =                           //make space
		(Train) malloc(sizeof(struct Train_t));

	if(new_Train == NULL){//check space
		return Train_OUT_OF_MEMORY;
	}
	//create list of tracks
    linkedListCreate(&(new_Train->Station_first) /* out */, copy_track,/////add succses check
							 free_track, print_track);
    new_Train->Station_last = NULL;
    new_Train->Price = Price;
    new_Train->type = (MtmTrainType) type;
    new_Train->line_number = line_number;


	*train = new_Train;
	return Train_SUCCESS;
}

TrainResult Train_destroy(Train train){//free train
    if(train == NULL){//if train is allready null
        return Train_SUCCESS;
    }
    linkedListDestroy(train->Station_first);//realse list
	Track_destroy(*train->Station_last);//realease last station
	free(train);
	return Train_SUCCESS;
}

TrainResult Train_get_line_number(Train train,/*output*/int* line_number){//"return" line number
    if(train == NULL || line_number == NULL) {
        return Train_BAD_ARGUMENTS;
    }

    *line_number = train->line_number;
    return Train_SUCCESS;
}


TrainResult Train_get_price(Train train,/*output*/double* Price){//"return: price
    if(train == NULL || Price == NULL) {
        return Train_BAD_ARGUMENTS;
    }

    *Price = train->Price;
    return Train_SUCCESS;
}

TrainResult Train_get_type(Train train,/*output*/elemm type){//"return" type
    MtmTrainType type_tmp;
    if(train == NULL || type == NULL) {
        return Train_BAD_ARGUMENTS;
    }
    type_tmp = (train->type);
    type = &type_tmp;
    return Train_SUCCESS;
}

TrainResult Train_get_Station(Train train, /*output*/elemm* station){//"return" track station
    if(train == NULL || station == NULL) {
        return Train_BAD_ARGUMENTS;
    }

   linkedListGetCurrent(train->Station_first, (ListElement*)&station /*out*/);
    return Train_SUCCESS;
}

TrainResult Train_get_last_Station(Train train, /*output*/elemm* station_last){//"return" last station track
    if(train == NULL || station_last == NULL) {
        return Train_BAD_ARGUMENTS;
    }

    *station_last =*((Track*)train->Station_last);
    return Train_SUCCESS;
}

TrainResult move_next_station_train(Train train){//move to next track station in list
    if(train == NULL) {
        return Train_BAD_ARGUMENTS;
    }

    linkedListGoToNext(train->Station_first);
    return Train_SUCCESS;
}
TrainResult move_to_head_station_train(Train train){//move to head in list track
    if(train == NULL) {
        return Train_BAD_ARGUMENTS;
    }

    linkedListGoToHead(train->Station_first);
    return Train_SUCCESS;
}

TrainResult add_station_train(Train train,elemm station,int time)//add new station to line
{
            Track *temp;
            int use;
            if(train == NULL) {
                     return Train_BAD_ARGUMENTS;
            }
            if (Track_create(temp,&station, time)==Track_OUT_OF_MEMORY)//create new track
            {  
               return Train_OUT_OF_MEMORY;//check "maloc"
            }
            if (linkedListInsertLast(train->Station_first, (ListElement) temp)==LIST_OUT_OF_MEMORY)//add new link to list
               {
                  Track_destroy(*temp); //make space faild free memory                                       
                  return LIST_OUT_OF_MEMORY;
               }
            Station_get_use((Station)station,&use);//inc station use
            use++;
            Station_set_use((Station)station,use); 
            train->Station_last=temp;//last track is the new last
            return Train_SUCCESS;
}

TrainResult remove_station_train(Train train,int index){//remove station 
     Track temp;
     Station to_dec;
     int use;
     int index_t=index;
     ListResult status;
     if (index==-1)//if we should delete the last
     {
             while (linkedListGoToNext(train->Station_first)!=LIST_FAIL)//move until last link
             {}
             
             status=LIST_FAIL;   //set status and index_t as end and good
             index_t=0;
     }  
     else
     {
           while ((status!=LIST_FAIL) && (index_t!=0) )//move until last link or index_t!=0 
           {
                 index_t--;
                 status=linkedListGoToNext(train->Station_first);        
           }
           
                       
     }
     if (index_t!=0)//valid index_t <=number of elements in list
        return Train_FAIL;
     linkedListGetCurrent(train->Station_first, (ListElement*)temp /*out*/);//get track
     Track_get_Station(temp,&to_dec);//get station
     Station_get_use(to_dec,&use);//dec line use
     use--;
     Station_set_use(to_dec,use);
     linkedListRemoveCurrent(train->Station_first);//remove link
     if (status==LIST_FAIL)//if remove link was the last one
       { 
       while (linkedListGoToNext(train->Station_first)!=LIST_FAIL)//move until last link
       {}
       linkedListGetCurrent(train->Station_first, (ListElement*)temp /*out*/);   //get track
       train->Station_last=&temp;//set the new last station 
       }
      return Train_SUCCESS;
}
TrainResult check_train_station(Train train, elemm station) {
          LinkedList station_list = train->Station_first;
          ListResult status;
          char* station_name;
          Station_get_Station_name((Station)station,station_name);
          status = linkedListFind(station_list,&station_name,match_by_Station_name);
          if (status == LIST_SUCCESS) {return Train_SUCCESS;}
          return Train_FAIL;
}
TrainResult Train_get_station_list(Train train, elemm* list) {
          if (train == NULL || list == NULL) {
                 return Train_BAD_ARGUMENTS;
          }
          *list = train->Station_first;
          return Train_SUCCESS;
}               
