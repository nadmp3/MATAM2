/*
 * main.c
 *
 *  Created on: 28/11/2008
 *      Author: Avishay Livne
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mtm_ex2.h"
#include "schedule.h"
#define SUCCESS 0
#define ERROR_OUT_OF_MEMORY -1

#define ERROR_STREAM stderr

static int handleError(ScheduleResult result) {
	switch (result) {
	case SCHEDULE_OUT_OF_MEMORY:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_OUT_OF_MEMORY);
		return ERROR_OUT_OF_MEMORY;
	case SCHEDULE_NULL_ARG:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_NULL_ARG);
		break;
	case SCHEDULE_INVALID_LINE_TYPE:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_LINE_TYPE);
		break;
	case SCHEDULE_INVALID_LINE_NUMBER:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_LINE_NUMBER);
		break;
	case SCHEDULE_INVALID_PRICE:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_PRICE);
		break;
	case SCHEDULE_INVALID_TRAIN_TYPE:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_TRAIN_TYPE);
		break;
	case SCHEDULE_LINE_ALREADY_EXISTS:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_LINE_ALREADY_EXIST);
		break;
	case SCHEDULE_LINE_DOESNT_EXIST:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_LINE_DOESNT_EXIST);
		break;
	case SCHEDULE_STATION_ALREADY_EXIST:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_STATION_ALREADY_EXIST);
		break;
	case SCHEDULE_STATION_DOESNT_EXIST:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_STATION_DOESNT_EXIST);
		break;
	case SCHEDULE_STATION_IS_USED:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_STATION_IS_USED);
		break;
	case SCHEDULE_INVALID_TIME:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_TIME);
		break;
	case SCHEDULE_INVALID_STATION_INDEX:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_INVALID_STATION_INDEX);
		break;
	case SCHEDULE_NO_LINES:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_NO_LINES);
		break;
	case SCHEDULE_NO_STATIONS:
		mtmPrintErrorMessage(ERROR_STREAM,MTM_NO_STATIONS);
		break;
	default:
		assert(result == SCHEDULE_SUCCESS);
		break;
	}
	return SUCCESS;
}
//=============================================================================
int test1() {
	Schedule schedule = scheduleCreate();

	printf("Register stations\n");
	if (handleError(scheduleRegisterStation(schedule, "Bay_Central"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Horev Center"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Haifa University"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Hadar"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Carmel_Beach"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Binyamina"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Tel-Aviv_University"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Beer-Sheva_North"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Old_Romema"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add lines\n");
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 37, "Egged", 5.4))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 4000, "direct", 20.7))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 24, "Egged", 5.6))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add stations to bus line #37...\n");
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 37, "Bay_Central", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 37, "Horev Center", 22))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 37, "Haifa University", 32))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 37, "Hadar", 15))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add stations to train line #4000\n");
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 4000, "Carmel_Beach", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 4000, "Binyamina", 22))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 4000, "Tel-Aviv_University", 48))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 4000, "Beer-Sheva_North", 148))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add stations to bus line #24\n");
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 24, "Bay_Central", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 24, "Old_Romema", 27))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 24, "Haifa University", 38))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Remove a station from the train.\n");
	if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 4000, 1))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Report registered stations...\n");
	if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report all lines...\n");
	if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report lines between certain stations...\n");
	if (handleError(scheduleReportLinesBetweenStations(schedule, "Bay_Central", "Haifa University", 0.00))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report stations for line\n");
	if (handleError(scheduleReportStationsForLine(schedule, 4000))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report stations for line\n");
	if (handleError(scheduleReportStationsForLine(schedule, 37))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report stations for line\n");
	if (handleError(scheduleReportStationsForLine(schedule, 24))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	scheduleDestroy(schedule);
	return SUCCESS;
}
//=============================================================================
int test2() {
	Schedule schedule = scheduleCreate();
	printf("Add bus line\n");
    if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 901, "E g  g   e    d", 22))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("register stations\n");
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Carmel Beach"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Tel Aviv Savidor"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Tel Aviv Central"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleRegisterStation(schedule, "Binyamina"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	
	printf("Add stations to bus line\n");
    if (handleError(scheduleReportStationsForLine(schedule, 901))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 901, "Carmel Beach", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 901, "Tel Aviv Savidor", 80))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 901, "Tel Aviv Central", 100))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 901))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add train line\n");
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 10200, "direct", 24.0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 8500, "intercity", 24.0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Add stations to train line\n");
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 8500, "Carmel Beach", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 8500, "Tel Aviv Savidor", 20))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 8500, -1))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 8500, "Binyamina", 22))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 8500, "Tel Aviv Savidor", 20))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN, 8500, "Tel Aviv Savidor", 58))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Report lines\n");
    if (handleError(scheduleReportLines(schedule, MTM_LINE_TRAIN))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportLines(schedule, MTM_LINE_BUS))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	printf("Report stations for line\n");
    if (handleError(scheduleReportStationsForLine(schedule, 4000))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Remove 1st line\n");
    if (handleError(scheduleRemoveLine(schedule, MTM_LINE_ALL, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 8500))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Unregister station\n");
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleUnregisterStation(schedule, "Carmel Beach"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}


	printf("Remove 2nd line\n");
    if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS, 901))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Unregister stations\n");
    if (handleError(scheduleUnregisterStation(schedule, "Carmel Beach"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleUnregisterStation(schedule, "Tel Aviv Savidor"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleUnregisterStation(schedule, "Tel Aviv Central"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Report stations\n");
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	scheduleDestroy(schedule);
	return SUCCESS;
}
//=============================================================================
int test3() {
	Schedule schedule = scheduleCreate();

	printf("Add bus lines\n");
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 58, "Egged", 9.2))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 58, "egged", 9.20))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 59, "egged", 9.20))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 60, "Metropolin", 9.0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 61, "Metropolin", 8.9))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 58, "Klavim", 11.5))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 54, "Klavim", 11.5))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	
	printf("Add train lines\n");
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 2000, "intercity", 33))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 3000, "unknown", 33))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 3000, "suburban", 33))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 4000, "direct", 33))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, -7, "intercity", 33))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

    printf("Report lines\n");
    if (handleError(scheduleReportLines(schedule, MTM_LINE_BUS))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportLines(schedule, MTM_LINE_TRAIN))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

    printf("Report stations for line\n");
    if (handleError(scheduleReportStationsForLine(schedule, 2000))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

    printf("register stations\n");
    if (handleError(scheduleRegisterStation(schedule, "Kiryat Eliezer"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRegisterStation(schedule, "Stellamaris"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRegisterStation(schedule, "Carmel Center"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRegisterStation(schedule, "Stellamaris"))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportRegisteredStations(schedule))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

    printf("Add stations to bus\n");
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 58, "Carmel Center", 1))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 58, "Stellamaris", 5))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 58, "Stellamaris", 4))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 58, "London", 7))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 58, "Kiryat Eliezer", 10))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS, 158, "Kiryat Eliezer", 10))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 58))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Report lines between stations\n");
	if (handleError(scheduleReportLinesBetweenStations(schedule, "Kiryat Eliezer", "Carmel Center", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
	if (handleError(scheduleReportLinesBetweenStations(schedule, "Carmel Center", "Kiryat Eliezer", 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	printf("Remove stations from line\n");
    if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS, 58, 1))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 58))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS, 58, -1))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 58))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS, 58, 0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
    if (handleError(scheduleReportStationsForLine(schedule, 58))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

	scheduleDestroy(schedule);
	return SUCCESS;
}
//=============================================================================
int main(int argc, char** argv) {
	int test;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <test_number>\n", argv[0]);
		return !SUCCESS;
	}
	test = atoi(argv[1]);
	switch(test) {
		case 1: return test1();
		case 2: return test2();
		case 3: return test3();
		default: break;
	}
	return SUCCESS;
}
