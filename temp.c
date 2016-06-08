#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "schedule.h"
#include "mtm_ex2.h"

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

//
//=============================================================================
int test() {
        Schedule schedule = scheduleCreate();
        if(schedule == NULL)
            return ERROR_OUT_OF_MEMORY;

        printf("Check some reports with empty schedule, should output errors\n");
        if (handleError(scheduleReportRegisteredStations(schedule)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_BUS)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_TRAIN)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Register some stations\n");
        if (handleError(scheduleRegisterStation(schedule, "Station 1.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 1.1")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 1.2")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 1.3")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 1.4")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 11.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 11.1")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 11.2")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 11.3")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 11.4")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 2.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 2.1")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 2.2")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 2.3")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.1")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.2")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.3")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.4")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 3.5")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 0.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Here should be 3 errors about station already exists\n");
        if (handleError(scheduleRegisterStation(schedule, "Station 1.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 2.3")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRegisterStation(schedule, "Station 0.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Add lines\n");
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 901,
"Egged",         33))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 902,
"Egged",         34))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 101,
"Metropolin",    34))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 555,
"Metropolin",    30))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 9,
"A",             45))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 89,
"e",             54))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 75,
"z",             56))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1901,
"direct",     37))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1902,
"direct",     34))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1101,
"intercity",  34))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1555,
"direct",     30))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1009,
"suburban", 45))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1089,
"suburban",  54))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1075,
"intercity", 36))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}

        printf("Add illegal lines, check errors\n");
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 1,
"Egged",      10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 0,
"Egged",      10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 10000,
"Egged",      10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 0,
"direct",     10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 10000,
"direct",     10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 200,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1200,
"direct",     0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 200,
"Egged",     -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1200,
"direct",    -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1200,
"egged",      1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 901,
"E",          33))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1901,
"intercity",  37))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        /* Till now we checked simple errors, now let's check double errors
*/
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 0,
"Egged",      10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 9999,
"Egged",      10))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 200,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 0,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 9999,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 901,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_ALL, 1901,
"Egged",      0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 0,
"Egged",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS, 10000,
"Egged",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 0,
"direct",     0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 10000,
"direct",     0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 0,
"error",      1))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 10000,
"error",      1))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 0,
"error",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 10000,
"error",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1200,
"error",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1901,
"error",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 1901,
"error",      1))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS,   901,
"error",      0))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_BUS,   1901,
"error",      1))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddLine(schedule, MTM_LINE_TRAIN, 901,
"direct",     1))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}

        printf("Add stations all lines\n");
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.1", 12))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.2", 14))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.3", 20))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.4", 30))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
902,  "Station 1.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
902,  "Station 1.1", 6)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
902,  "Station 1.2", 13))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
902,  "Station 1.3", 22))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
902,  "Station 1.4", 31))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
555,  "Station 2.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
555,  "Station 2.1", 5)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
555,  "Station 2.2", 33))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
555,  "Station 2.3", 54))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.1", 23))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.2", 29))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.3", 57))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.4", 68))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
9,    "Station 3.5", 68))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.1", 12))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.2", 14))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.3", 20))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.4", 30))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1902, "Station 1.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1902, "Station 1.1", 6)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1902, "Station 1.2", 13))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1902, "Station 1.3", 22))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1902, "Station 1.4", 31))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1555, "Station 2.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1555, "Station 2.1", 5)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1555, "Station 2.2", 33))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1555, "Station 2.3", 54))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.0", 0)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.1", 23))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.2", 29))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.3", 57))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.4", 68))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1009, "Station 3.5", 68))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}

        printf("Add illegal stations (errors must be here)\n");
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
901,  "Station 0.0", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
0,    "Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
10000,"Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
0,    "Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
10000,"Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
111,  "Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1111, "Station 0.0", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 0.1", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 0.1", 900))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        /* Now test double and more errors */
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.0", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.0", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
1,    "Station 0.0", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
901,  "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
1901, "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
901,  "Station 1.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
1901, "Station 1.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
901,  "Station 1.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
1901, "Station 1.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
901,  "Station 1.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
1901, "Station 1.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
0,    "Station 0.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_ALL,
10000,"Station 0.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
0,    "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
10000,"Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
0,    "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
10000,"Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
0,    "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
10000,"Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
0,    "Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
10000,"Station 0.0", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
1,    "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1,    "Station 0.1", 90)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
1,    "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1,    "Station 0.0", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
1,    "Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1,    "Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 0.1", -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 0.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 0.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_BUS,
901,  "Station 1.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleAddStationToLine(schedule, MTM_LINE_TRAIN,
1901, "Station 1.1", 10)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}

        printf("Print some report, no errors here (except if no lines are passing 2 stations with price <= maxPrice)\n");
        if (handleError(scheduleReportRegisteredStations(schedule)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_BUS)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_TRAIN)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1.1", "Station 1.4",100))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1.1", "Station 1.4",30)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 3.1", "Station 3.4",30)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1.1", "Station 3.4",100))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1.1", "Station 1.4",0)))   {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 3.2", "Station 3.1",300))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 0.0", "Station 0.0",300))) {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}

        printf("Check reports errors\n");
        if (handleError(scheduleReportStationsForLine(schedule, 0)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 10000)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 71)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1.1", "Station 1.4",-1))) 
        {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1",   "Station 1",  0)))  
        {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1",   "Station 1",  -1)))  
        {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 0.0",   "Station 0.0",  -1)))  
        {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLinesBetweenStations(schedule, "Station 1",   "Station 1",  0)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Unregister station\n");
        if (handleError(scheduleUnregisterStation(schedule, "Station 0.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Now check errors of unregistering stations\n");
        if (handleError(scheduleUnregisterStation(schedule, "Station 0.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleUnregisterStation(schedule, "Station 1.0")))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Remove some stations from lines (stations report is printed between each change)\n");
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   555,  2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   555,  0)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   555,  -1)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 1555, 2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 1555, 0)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 1555, -1)))  {scheduleDestroy(schedule); return
ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Now let's check some errors in removing stations from lines \n");
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   555,   0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   0,     0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   10000, 0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 0,     0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 10000, 0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   7771,  0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   1901,  0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 7771,  0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 901,   0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   555,   -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 1555,  -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   555,   1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 1555,  1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   0,     0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   10000, 0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   7771,  0)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   555,   -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   555,   1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   0,     -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   10000, -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   0,     1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   10000, 1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   7771,  1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_ALL,   7771,  -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   0,     -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   10000, -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 0,     -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 10000, -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   0,     1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   10000, 1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 0,     1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 10000, 1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   2,     -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_BUS,   2,     -2)))  {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 2,     1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveStationFromLine(schedule, MTM_LINE_TRAIN, 2,     1)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Now let's remove some lines\n");
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS, 9)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 1009)))   {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Test remove line errors\n");
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_ALL,   555))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS,   0))) {scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS,   10000)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 0)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 10000)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS,   1901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_BUS,   2)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_TRAIN, 2)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_ALL,   0)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_ALL,   10000)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleRemoveLine(schedule, MTM_LINE_ALL,   2)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("And at last print all reports to check that everything is as should be\n");
        if (handleError(scheduleReportRegisteredStations(schedule)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportLines(schedule, MTM_LINE_ALL)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 902)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 101)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 9)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 89)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 75)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1901)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1902)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1101)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1555)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1009)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1089)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}
        if (handleError(scheduleReportStationsForLine(schedule, 1075)))
{scheduleDestroy(schedule); return ERROR_OUT_OF_MEMORY;}

        printf("Now destroy schedule and exit, valgrind should report that no memory leaks are possible\n");
        scheduleDestroy(schedule);
        return SUCCESS;

}

//
//=============================================================================
int main(int argc, char** argv) {
    return test();

}
