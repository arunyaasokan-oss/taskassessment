/* student.h - supporting function for students */

#ifndef __INCstudenth
#define __INCstudenth

#include <stdint.h>

/* defines */
#define MAX_STUDENT_COUNT   100U
#define MAX_STUDENT_NAME    50U
#define NO_OF_SUBJECT       10U

/* typedef */
typedef struct 
    {
    uint8_t ucStudentName[MAX_STUDENT_NAME];
    uint32_t ulRollNumber;
    float fMarkInfo[NO_OF_SUBJECT];
    float fSum;
    float fAverage;
    int8_t ucDeleted;
    }student;

/* function declaration */
extern uint32_t ulRecordCount;
extern student studentInfo[MAX_STUDENT_COUNT];
extern bool studentAdd(student* pstInfo);
extern bool studentGetCount(uint32_t* pulCount);
extern bool studentGetAvgMarksOfSubjects(uint32_t* pucAvgMarks);
extern bool studentSearchByName(uint8_t *pcName);
extern void studentSortByName(void);
extern void studentSortByRank(void);
extern void studentSortByRollNumber(void);
extern bool studentDeleteByName(uint8_t* pucName);
extern bool studentDeleteByRollNumber(uint32_t ulRoll);
#endif                                                         /*__INCstudenth*/
