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
#include <stdlib.h>
#include "studentinc.h"

/* defines */
student studentInfo[MAX_STUDENT_COUNT];
/* typedef */

/* globals */
uint32_t ulRecordCount = 0;

/* locals */
static int studentCompareByName(const void *pInputA, const void *pInputB);
static int studentCompareByRank(const void *pInputA, const void *pInputB);
static int studentCompareByRollNumber(const void *pInputA, const void *pInputB);

/* forward declaration */
bool studentAdd(student* pstInfo);
bool studentGetCount(uint32_t* pulCount);
bool studentGetAvgMarksOfSubjects(uint32_t* pucAvgMarks);
bool studentSearchByName(const uint8_t *pcName);
void studentSortByName(void);
void studentSortByRank(void);
void studentSortByRollNumber(void);
bool studentDeleteByName(const uint8_t* pucName);
bool studentDeleteByRollNumber(uint32_t ulRoll);
void studentDeleteAll(void);
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
        strncpy((char*)studentInfo[ulRecordCount].ucStudentName, 
        (char*)pstInfo->ucStudentName,
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
        *pulCount = ulRecordCount;
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
    uint32_t ulMarks = 0;
    if(NULL != pucAvgMarks)
        {
        for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
            {
            fTotalMark += studentInfo[ulIndex].fAverage;
            }
        fAverageMark = fTotalMark / ulRecordCount;
        ulMarks =  (uint32_t)fAverageMark;
        *pucAvgMarks = ulMarks;
        blReturnStatus = true;         
        }
        return blReturnStatus;
    }
    
/*******************************************************************************
*
* studentSearchByName - search the name on the list
* DESCRIPTION
* The function is used to search a name from the list
* 
* PARAMETER : pcName - input name
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/ 
bool studentSearchByName(const uint8_t *pcName)
    {
    uint32_t ulIndex = 0;
    uint8_t ucIndex = 0;
    
    bool blReturnStatus = false;
    if(NULL != pcName)
        {
        for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
            {
            if(strncmp((char *)studentInfo[ulIndex].ucStudentName, 
             (char *)pcName, strlen((char *)pcName)))
                {
                ucIndex = 0;
                printf("|%d|%s|%02f|%.02f\n",
                studentInfo[ulIndex].ulRollNumber,
                studentInfo[ulIndex].ucStudentName,
                studentInfo[ulIndex].fSum,
                studentInfo[ulIndex].fAverage);
                for(ucIndex = 0 ; ucIndex< NO_OF_SUBJECT; ucIndex++)
                    {
                    printf("%.02f|",
                    studentInfo[ulIndex].fMarkInfo[ucIndex]);
                    }

                blReturnStatus = true;
                }

            }
        }
        return blReturnStatus;
    }
/*******************************************************************************
*
* studentCompareByName - compare the student name
* DESCRIPTION
* The supportive function used to compare student name in the list.
* 
* PARAMETER : pInputA - void pointer
*             pInputB - void pointer
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/ 
static int studentCompareByName(const void *pInputA, const void *pInputB)
    {
    const struct student *psStudentA = (const struct student *)pInputA;
    const struct student *psStudentB = (const struct student *)pInputB;
    return strcmp((const char *)psStudentA->ucStudentName, 
    (const char *)psStudentB->ucStudentName); 
    }
/*******************************************************************************
*
* studentSortByName - sort the array by name
* DESCRIPTION
* The function is used to sort the student list by using name
* 
* PARAMETER : pcName - input name
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/
void studentSortByName(void)
    {
    uint32_t ulIndex =0;
    qsort(studentInfo, ulRecordCount, sizeof(student), studentCompareByName);
    printf("Sorted By Name \n");
    for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
        {
         printf("Roll Number %d Name : %s",
            studentInfo[ulIndex].ulRollNumber,
            studentInfo[ulIndex].ucStudentName);
        }
    } 
/*******************************************************************************
*
* studentCompareByRollNumber - compare the student rollnumber
* DESCRIPTION
* The supportive function used to compare student rol number in the list.
* 
* PARAMETER : pInputA - void pointer
*             pInputB - void pointer
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/ 
static int studentCompareByRollNumber(const void *pInputA, const void *pInputB)
    {
    const struct student *psStudentA = (const struct student *)pInputA;
    const struct student *psStudentB = (const struct student *)pInputB;
    return (psStudentA ->ulRollNumber - psStudentB ->ulRollNumber);
    }
/*******************************************************************************
*
* studentSortByName - sort the array by name
* DESCRIPTION
* The function is used to sort the student list by using name
* 
* PARAMETER : pcName - input name
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/
void studentSortByRollNumber(void)
    {
    uint32_t ulIndex =0;
    qsort(studentInfo, ulRecordCount, sizeof(student), 
    studentCompareByRollNumber);
    printf("Sorted By RollNumber \n");
    for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
        {
         printf("Roll Number %d Name : %s",
            studentInfo[ulIndex].ulRollNumber,
            studentInfo[ulIndex].ucStudentName);
        }
    } 
    /*******************************************************************************
*
* studentCompareByRank - compare the student rank
* DESCRIPTION
* The supportive function used to compare student rank in the list.
* 
* PARAMETER : pInputA - void pointer
*             pInputB - void pointer
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/ 
static int studentCompareByRank(const void *pInputA, const void *pInputB)
    {
    const student *psStudentA = (const struct student *)pInputA;
    const student *psStudentB = (const struct student *)pInputB;
    return (psStudentA ->fSum - psStudentB ->fSum);
    }
/*******************************************************************************
*
* studentSortByName - sort the array by name
* DESCRIPTION
* The function is used to sort the student list by using name
* 
* PARAMETER : pcName - input name
*
* GLOBALS   : N/A
*
* RETURNS   : True - on success , false - on failure
*
* ERRNO     : N/A
*/
void studentSortByRank(void)
    {
    uint32_t ulIndex =0;
    qsort(studentInfo, ulRecordCount, sizeof(student), studentCompareByRank);
    printf("Sorted By Name \n");
    for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++)
        {
         printf("Roll Number %d Name : %s mark: %.02f",
            studentInfo[ulIndex].ulRollNumber,
            studentInfo[ulIndex].ucStudentName,
            studentInfo[ulIndex].fSum
        );
        }
    }
/*******************************************************************************
*
* studentDeleteAll - delete all student record
* DESCRIPTION
* The function is used to delete all student record
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
void studentDeleteAll(void)
    {
    ulRecordCount = 0;
    memset(&studentInfo, 0, sizeof(student));
    } 

/*******************************************************************************
*
* studentDeleteByName - delete student record by name
* DESCRIPTION
* The function is delete student by name
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
bool studentDeleteByName(const uint8_t* pucName)
    {
    uint32_t ulIndex = 0;
    uint32_t ulJindex = 0;
    uint8_t ucFound = 0;

    bool blReturnStatus = false;
    if(NULL != pucName)
        {
        for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++, ulJindex++)
            {
            if(0 == strncmp((char *)studentInfo[ulIndex].ucStudentName, 
             (char *)pucName, strlen((char *)pucName)))
                {
                  ucFound = 1 ;
                  ulIndex++;
                  ulRecordCount --;
                } 
                if(ucFound == 1)
                    {
                    memcpy(&studentInfo[ulJindex],&studentInfo[ulIndex],
                    sizeof(studentInfo));
                    }
                }
                if(ucFound == 1)
                blReturnStatus = true;
            }
            return  blReturnStatus;
    }

/*******************************************************************************
*
* studentDeleteByRollNumber - delete student record by ROLL NUMBER
* DESCRIPTION
* The function is delete student by ROLLNUMBER
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
bool studentDeleteByRollNumber(uint32_t ulRoll)
    {
    uint32_t ulIndex = 0;
    uint32_t ulJindex = 0;
    uint8_t ucFound = 0;

    bool blReturnStatus = false;
    if(0 != ulRoll)
        {
        for(ulIndex = 0; ulIndex < ulRecordCount; ulIndex++, ulJindex++)
            {
            if(ulRoll == studentInfo[ulIndex].ulRollNumber)
                {
                  ucFound = 1 ;
                  ulIndex++;
                  ulRecordCount --;
                } 
                if(ucFound == 1)
                    {
                    memcpy(&studentInfo[ulJindex],&studentInfo[ulIndex],
                    sizeof(studentInfo));
                    }
                }
                if(ucFound == 1)
                blReturnStatus = true;
            }
            return  blReturnStatus;
    }
    