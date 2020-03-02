#include <wiringPi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <limits.h>
#include <bitlib.h>
#include "MinTDriver_bitscope.h"

#define MY_DEVICES 1 /* open one device only */
#define MY_PROBE_FILE "" /* default probe file if unspecified */

#define MY_DEVICE 0
#define MY_CHANNEL 0
#define MY_MODE BL_MODE_FAST
#define MY_RATE 1000000 /* capture sample rate */
#define MY_SIZE 4 /* number of samples to capture */

void free_BITSCOPE();

void init_BITSCOPE()
{
    printf("BitScope init...\n");
    
    if (wiringPiSetup() == -1) 
    {
        printf("wiringPiSetup ERROR\n");
        exit(1); 
    }
    
     /* 
    * Open and select the first channel on the first device.
    */
    printf("\nStarting: Attempting to open %d device%s...\n",MY_DEVICES,MY_DEVICES!=1?"s":"");
    if ( ! BL_Open(MY_PROBE_FILE,MY_DEVICE) ) {
        printf("Failed to find a devices.\n");
        free_BITSCOPE();
        exit(1); 
    }
    if ( BL_Select(BL_SELECT_DEVICE,MY_DEVICE) != MY_DEVICE ) {
        printf("Failed to select device %d.\n",MY_DEVICE);
        free_BITSCOPE();
        exit(1); 
    }
    if ( BL_Select(BL_SELECT_CHANNEL,MY_CHANNEL) != MY_CHANNEL ) {
        printf("Failed to select channel %d.\n",MY_CHANNEL);
        free_BITSCOPE();
        exit(1); 
    }   
   /* 
    * Prepare to capture one channel...
    */
    if ( BL_Mode(MY_MODE) != MY_MODE ) {
        printf("Failed to select mode %d.\n",MY_MODE);
        exit(1); 
    }
    BL_Intro(BL_ZERO); /* optional, default BL_ZERO */
    BL_Delay(BL_ZERO); /* optional, default BL_ZERO */
    BL_Rate(MY_RATE); /* optional, default BL_MAX_RATE */
    BL_Size(MY_SIZE); /* optional, default BL_MAX_SIZE */
    BL_Select(BL_SELECT_CHANNEL,MY_CHANNEL); /* choose the channel */
    BL_Trigger(BL_ZERO,BL_TRIG_RISE); /* optional when untriggered */
    BL_Select(BL_SELECT_SOURCE,BL_SOURCE_POD); /* use the POD input */
    BL_Range(BL_Count(BL_COUNT_RANGE)); /* maximum range */
    BL_Offset(BL_ZERO); /* optional, default 0 */
    BL_Enable(TRUE); /* at least one channel must be initialised */
}

void read_BITSCOPE(double (*vibration)) 
{ 
//    printf("   Trace: %d samples @ %.0fHz = %fs\n",BL_Size(BL_ASK),BL_Rate(BL_ASK), BL_Time(BL_ASK));
    if ( BL_Trace(BL_TRACE_FORCED,BL_SYNCHRONOUS) ) { /* capture data (without a trigger) */
        int i, n = MY_SIZE; 
//        double d[n]; /* let's get 5 samples */
        BL_Select(BL_SELECT_CHANNEL,MY_CHANNEL); /* optional if only one channel */
        if ( BL_Acquire(n, vibration)  == n ) { /* acquire (i.e. dump) the capture data */
//            printf("N : %d\n", n);
//            for (i = 0; i < n; i++)
//            {
//                printf("i : %d\t ", i);
//                printf("data : %f\n", vibration[i]);
//            }
//            printf("\n");
        }
        else
            printf("Fail to get data");
    }
//    printf("Data acquisition complete. Dump Log...\n");
//    printf("%s\n",BL_Log());
} 

void free_BITSCOPE()
{
    BL_Close(); /* call this to release library resources */
}

JNIEXPORT void JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_initSensor
  (JNIEnv *env, jobject obj) {
    init_BITSCOPE();
}

JNIEXPORT jdoubleArray JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_getVibrationData
  (JNIEnv *env, jobject obj) {
    double *vibrationArray = (double*) malloc(sizeof(double) * MY_SIZE);
    
    read_BITSCOPE(vibrationArray);
    
    jdoubleArray jdoubleArr = (*env)->NewDoubleArray(env, MY_SIZE);
    (*env)->SetDoubleArrayRegion( env, jdoubleArr, 0, MY_SIZE, (const jdouble*) vibrationArray );
   
    free(vibrationArray);
    
    return jdoubleArr;
}

/* * Class: MinT_ExternalDevice_Sensing_TempHumi_MinTDriver_1dht11 * Method: freeSensor * Signature: ()V */
JNIEXPORT void JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_freeSensor
  (JNIEnv *env, jobject obj) {
    free_BITSCOPE();
}
