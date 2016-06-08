
int check_line_number(int line_number);
int check_price(double price);
MtmTrainType change_to_mtm_train(const char* train_type);
ScheduleResult check_data(MtmLineType type, int number, MtmTrainType train_type, double price);
ListResult check_track(LinkedList station_list, const char* from, const char* to);
SetResult check_station(Set set, const char* station);
                              
