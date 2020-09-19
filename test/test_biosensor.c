#include "unity.h"
#include "biosensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}
int t[100];//Global array to store parameter from file
int number;
int iter;//Global iterative variable
void test_BioSensor(void)
{
  TEST_ASSERT_EQUAL(1, biosensor(6,t[0],t[1],t[2],t[3],t[4]));
}
void test_BaudRateBelow9600(void)               //Test case for Baud rate  LL-02
{
  TEST_ASSERT_EQUAL(0, biosensor(5,t[5],t[6],t[7],t[8],t[9]));
}
void test_BaudRateAbove9600(void)               //Test case for Baud rate  LL-02
{
  TEST_ASSERT_EQUAL(0, biosensor(4,t[10],t[11],t[12],t[13]));
}
void test_SupplyBelow5volts(void)               //Test case for Supply  LL-01
{
  TEST_ASSERT_EQUAL(0, biosensor(4));
  TEST_ASSERT_EQUAL(0, biosensor(2));
}
void test_SupplyGreater16(void)
{
  TEST_ASSERT_EQUAL(0, biosensor(17));
  TEST_ASSERT_EQUAL(0, biosensor(18));
}
void test_NegativeSupply(void)
{
  TEST_ASSERT_EQUAL(0, biosensor(-4));
  TEST_ASSERT_EQUAL(0, biosensor(-2));
}
void test_ExternalSuply(void)               //Test case for memory size check LL-06
{
    TEST_ASSERT_EQUAL(0, biosensor(5));
    TEST_ASSERT_EQUAL(0, biosensor(6));
}
void test_MemoryCheck(void)                 //Test case for memory size check LL-07
{
    TEST_ASSERT_EQUAL(60, biosensorMem());
}
void test_WireLength(void)                  //Test case for Wire length LL-05
{
    TEST_ASSERT_EQUAL(2, WireLength());

}
int test_main(void)
{
void getBioData()                           // Function to read data from file
{
    char *token;
    char help[256];
    FILE *myFile;
    myFile=fopen("re.txt","r");
    fscanf(myFile, "%s",help);
    token=strtok(help,",");
    iter=0;
    while(token !=NULL)
    {
        t[iter]=atoi(token);
        token=strtok(NULL,",");
        iter++;
    }
    number=iter;
}
getBioData();
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();
/* Run Test functions */
  RUN_TEST(test_SupplyBelow5volts);
  RUN_TEST(test_NegativeSupply);
  RUN_TEST(test_SupplyGreater16);
  RUN_TEST(test_BioSensor);
  RUN_TEST(test_BaudRateBelow9600);
  RUN_TEST(test_BaudRateAbove9600);
  RUN_TEST(test_ExternalSuply);
  RUN_TEST(test_MemoryCheck);
  RUN_TEST(test_WireLength);/* Close the Unity Test Framework */
  return UNITY_END();
}
