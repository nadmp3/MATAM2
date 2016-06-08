#ifndef MTM_EX1_H_
#define MTM_EX1_H_

#include <stdio.h> // For FILE*, you should avoid including unnecessary header files

/*
 * Maximal input line length
 */
#define MAX_LEN 120 // Maximum command line length

/*
 * This type defines all errors for the system.
 * These codes should be used for calling mtmPrintErrorMessage to report
 * error messages.
 */
typedef enum {
	MTM_OUT_OF_MEMORY,
	MTM_NULL_ARG,
	MTM_INVALID_LINE_TYPE,
	MTM_INVALID_LINE_NUMBER,
	MTM_INVALID_PRICE,
	MTM_INVALID_TRAIN_TYPE,
	MTM_LINE_ALREADY_EXIST,
	MTM_LINE_DOESNT_EXIST,
	MTM_STATION_ALREADY_EXIST,
	MTM_STATION_DOESNT_EXIST,
	MTM_STATION_IS_USED,
	MTM_INVALID_TIME,
	MTM_INVALID_STATION_INDEX,
	MTM_NO_LINES,
	MTM_NO_STATIONS,
} MtmErrorCode;

typedef enum {
    MTM_LINE_BUS,
    MTM_LINE_TRAIN,
    MTM_LINE_ALL
} MtmLineType;


/*
 * Type to define all possible train types.
 */
typedef enum {
	MTM_TRAIN_DIRECT,
	MTM_TRAIN_INTERCITY,
	MTM_TRAIN_SUBURBAN,
	MTM_TRAIN_INVALID
} MtmTrainType;

/*
 * mtmPrintErrorMessage: Prints an error message
 *
 * errorChannel - A file descriptor for the used error channel, in this
 * 	exercise it should be stderr.
 * code - The code for the error to report
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int mtmPrintErrorMessage(FILE* errorChannel, MtmErrorCode code);

/*
 * mtmPrintBusLine: Prints a line describing a bus
 *
 * outputChannel - file descriptor to print to.
 * number - Line number
 * company - The company running the line
 * firstStation - First station of the line, NULL if it does not exist.
 * lastStation - Last station of the line, NULL if it does not exist.
 * price - Fair price for the line
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int mtmPrintBusLine(FILE* outputChannel,
		int number,
		const char* company,
		const char* firstStation,
		const char* lastStation,
		double price);

/*
 * mtmPrintTrainLine: Prints a line describing a train
 *
 * outputChannel - file descriptor to print to.
 * number - Line number
 * type - type of the train (TRAIN_DIRECT, etc...)
 * firstStation - First station of the line, NULL if it does not exist.
 * lastStation - Last station of the line, NULL if it does not exist.
 * price - Fair price for the line
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int mtmPrintTrainLine(FILE* outputChannel,
		int number,
		MtmTrainType type,
		const char* firstStation,
		const char* lastStation,
		double price);

/*
 * mtmPrintLineStation: Prints a line describing a line's station
 *
 * outputChannel - file descriptor to print to.
 * station - Station's name.
 * time - Time of arrival to the station in minutes. The time will be
 * 	printed in HH:MM format automatically.
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int mtmPrintLineStation(FILE* outputChannel,
		const char* station,
		int time);

/*
 * mtmPrintStationName: Prints the name of a given station.
 *
 * station - Station's name.
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int mtmPrintStationName(FILE* output, const char* station);

#endif /* MTM_EX1_H_ */
