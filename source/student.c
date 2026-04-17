/* 
* student.c  - include all student operations , add, average calculation, sum,  
* grade calculation, update rank,average mark of subjects  
*/

/*
DESCRIPTION 
This will be responsible for adding students, List student, Delete Student,
Search by name - roll number and rank, Delete by name -roll number - all.
 */

 /* includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "studentinc.h"

/* defines */
student studentInfo[MAX_STUDENT_COUNT];
/* typedef */

/* globals */
uint32_t ulRecordCount = 0;

/* locals */

/* forward declaration */
bool studentAdd(student* pstInfo);
bool studentGetCount(uint32_t* pulCount);
bool studentGetAvgMarksOfSubjects(uint32_t* pucAvgMarks);
/*******************************************************************************
*
* studentAdd - function to add student info.
*
* DESCRIPTION
* The function is used to add student information such as name, roll number,
* mark .
* mark
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : True - whe data save successfully , false when error
*
* ERRNO     : N/A
*/
bool studentAdd(student* pstInfo)
    {
    bool blSaveStatus = false;
    uint8_t ucIndex = 0;
    if(pstInfo != NULL)
        {
        strncpy(studentInfo[ulRecordCount].ucStudentName, 
        pstInfo->ucStudentName,
        sizeof(pstInfo->ucStudentName));
        studentInfo[ulRecordCount].ulRollNumber = pstInfo->ulRollNumber;

        for(ucIndex = 0; ucIndex < NO_OF_SUBJECT; ucIndex++)
            {
            studentInfo[ulRecordCount].fMarkInfo[ucIndex] = 
                pstInfo->fMarkInfo[ucIndex];

            }
        for(ucIndex = 0; ucIndex < NO_OF_SUBJECT; ucIndex++)
            {
            studentInfo[ulRecordCount].fSum +=   pstInfo->fMarkInfo[ucIndex]; 
            }
        
        studentInfo[ulRecordCount].fAverage =  studentInfo[ulRecordCount].fSum 
                                        / NO_OF_SUBJECT;
        studentInfo[ulRecordCount].ucDeleted = 0;
        ulRecordCount++;
        blSaveStatus = true;
        }
        return blSaveStatus;
    
    }
/*******************************************************************************
*
* studentGetCount - To get record count
* DESCRIPTION
* The function is used to get record count.
* 
* PARAMETER : record count
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/    
bool studentGetCount(uint32_t* pulCount)
    {
    bool ulReturnStatus = false;
    if(NULL!= pulCount)
        {
        pulCount = ulRecordCount;
        ulReturnStatus = true;
        }
        return ulReturnStatus;
    }
/*******************************************************************************
*
* studentGetAvgMarksOfSubjects - To get average mark
* DESCRIPTION
* The function is used to get average mark
* 
* PARAMETER : average mark
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/   
bool studentGetAvgMarksOfSubjects(uint32_t* pucAvgMarks)
    {
    bool blReturnStatus = false;
    uint32_t ulIndex = 0;
    float fAverageMark = 0.00;
    float fTotalMark = 0.00;
    if(NULL != pucAvgMarks)
        {
        for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
            {
            fTotalMark += studentInfo[ulIndex].fAverage;
            }
        fAverageMark = fTotalMark / ulRecordCount; 
        pucAvgMarks = (uint32_t)fAverageMark;
        blReturnStatus = true;         
        }
        return blReturnStatus;
    }
    
    