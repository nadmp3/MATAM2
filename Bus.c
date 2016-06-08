#include "Bus.h"
#include "linked_list.h"
#include "Track.h"
#include "Track_utilities.h"
#include "Station.h"
#include "Station_utilities.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct Bus_t {
    int line_number;
	double Price;
	char* company_name;
	LinkedList Station_first;
	Track *Station_last;
};

BusResult Bus_create(Bus* bus, double Price,int line_number, const char* company_name) {//create bus

    Bus new_bus = NULL;
    BusResult status;

    if(bus == NULL || company_name==NULL){//check if arguments or ok
        return Bus_BAD_ARGUMENTS;//error
    }

	new_bus = 
		(Bus) malloc(sizeof(struct Bus_t));

	if(new_bus == NULL){
		return Bus_SUCCESS;
	}
	
	new_bus->company_name = NULL;
    status = Bus_set_company_name(new_bus,company_name);//set company name
    if(status != Bus_SUCCESS){
		free(new_bus);
        return status;
	}
    linkedListCreate(&(new_bus->Station_first) /* out */, copy_track,//////add succses check
							 free_track, print_track);
	new_bus->line_number = line_number;
    new_bus->Price = Price;
    new_bus->Station_last=NULL;

	*bus = new_bus;
	return Bus_SUCCESS;
}

BusResult Bus_destroy(Bus bus){
    if(bus == NULL){
        return Bus_SUCCESS;
    }
    linkedListDestroy(bus->Station_first);
	free(bus->Station_last);
	free(bus);
	return Bus_SUCCESS;
}

BusResult Bus_get_line_number(Bus bus,/*output*/int* line_number){//get line number
    if(bus == NULL || line_number == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    *line_number = bus->line_number;
    return Bus_SUCCESS;
}

BusResult Bus_get_price(Bus bus,/*output/input*/double* Price){//get price
    if(bus == NULL || Price == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    *Price = bus->Price;
    return Bus_SUCCESS;
}

BusResult Bus_get_company_name(Bus bus,/*output/input*/char* company_name){//get company name
    if(bus == NULL || company_name == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    strcpy(company_name,bus->company_name);//get company name
    return Bus_SUCCESS;
}

BusResult Bus_get_Station(Bus bus, /*output*/elem* station){//get station track

    if(bus == NULL || station == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

   linkedListGetCurrent(bus->Station_first, (ListElement*)&station /*out*/);//get station track
    return Bus_SUCCESS;
}

BusResult Bus_get_last_Station(Bus bus, /*output*/elem* station_last){//get last station track
    if(bus == NULL || station_last == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    *station_last =*((Track*)bus->Station_last);//get last station track
    return Bus_SUCCESS;
}

BusResult move_next_station_bus(Bus bus){//move next station in track
    if(bus == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    linkedListGoToNext(bus->Station_first);//move next station in track
    return Bus_SUCCESS;
}
BusResult Bus_set_company_name(Bus bus,const char* company_name){//set company name
    int name_length = 0;

    if(bus == NULL || company_name == NULL) {
        return Bus_BAD_ARGUMENTS;
    }
    
    if(company_name != bus->company_name){
        free(bus->company_name);
    }

    name_length = strlen(company_name);
    assert(name_length + 1 < MAX_LEN);
    
    bus->company_name = (char *)malloc(sizeof(char)*(name_length+1));
	if(bus->company_name == NULL) {
        return Bus_OUT_OF_MEMORY;
	}
    strcpy(bus->company_name,company_name); //set company name
    return Bus_SUCCESS;
}

BusResult move_to_head_station_bus(Bus bus){//move to head in list track
    if(bus == NULL) {
        return Bus_BAD_ARGUMENTS;
    }

    linkedListGoToHead(bus->Station_first);
    return Bus_SUCCESS;
}

BusResult add_station_bus(Bus bus, elem station,int time)//add new station to line
{
            Track *temp;
            int use;
            if(bus == NULL) {
                     return Bus_BAD_ARGUMENTS;
            }
            if (Track_create(temp,&station, time)==Track_OUT_OF_MEMORY)//create new track
            {  
               return Bus_OUT_OF_MEMORY;//check "maloc"
            }
            if (linkedListInsertLast(bus->Station_first, (ListElement) temp)==LIST_OUT_OF_MEMORY)//add new link to list
               {
                  Track_destroy(*temp); //make space faild free memory                                       
                  return LIST_OUT_OF_MEMORY;
               }
            Station_get_use((Station)station,&use);//inc station use
            use++;
            Station_set_use((Station)station,use); 
            bus->Station_last=temp;//last track is the new last
            return Bus_SUCCESS;
}

BusResult remove_station_bus(Bus bus,int index){//remove station 
     Track temp;
     Station to_dec;
     int use;
     int index_t=index;
     ListResult status;
     if (index==-1)//if we should delete the last
     {
             while (linkedListGoToNext(bus->Station_first)!=LIST_FAIL)//move until last link
             {}
             
             status=LIST_FAIL;   //set status and index_t as end and good
             index_t=0;
     }  
     else
     {
           while ((status!=LIST_FAIL) && (index_t!=0) )//move until last link or index_t!=0 
           {
                 index_t--;
                 status=linkedListGoToNext(bus->Station_first);        
           }
           
                       
     }
     if (index_t!=0)//valid index_t <=number of elements in list
        return Bus_FAIL;
     linkedListGetCurrent(bus->Station_first, (ListElement*)temp /*out*/);//get track
     Track_get_Station(temp,&to_dec);//get station
     Station_get_use(to_dec,&use);//dec line use
     use--;
     Station_set_use(to_dec,use);
     linkedListRemoveCurrent(bus->Station_first);//remove link
     if (status==LIST_FAIL)//if remove link was the last one
       { 
       while (linkedListGoToNext(bus->Station_first)!=LIST_FAIL)//move until last link
       {}
       linkedListGetCurrent(bus->Station_first, (ListElement*)temp /*out*/);   //get track
       bus->Station_last=&temp;//set the new last station 
       }
      return Bus_SUCCESS;
}
BusResult check_bus_station(Bus bus, elem station) {
          LinkedList station_list = bus->Station_first;
          ListResult status;
          char* station_name;
          Station_get_Station_name((Station)station,station_name);
          status = linkedListFind(station_list,&station_name,match_by_Station_name);
          if (status == LIST_SUCCESS) {return Bus_SUCCESS;}
          return Bus_FAIL;
}
BusResult Bus_get_station_list(Bus bus, elem* list) {
          if(bus == NULL || list == NULL) {
                 return Bus_BAD_ARGUMENTS;
          }
          *list = bus->Station_first;
          return Bus_SUCCESS;
}               
          
          
