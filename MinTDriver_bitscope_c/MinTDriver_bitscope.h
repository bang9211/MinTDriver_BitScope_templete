#include <jni.h>

#ifndef _Included_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_bitscope
#define _Included_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_bitscope
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_initSensor
  (JNIEnv *, jobject);

JNIEXPORT jdoubleArray JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_getVibrationData
  (JNIEnv *, jobject);


JNIEXPORT void JNICALL Java_MinT_ExternalDevice_Sensing_Vibration_MinTDriver_1bitscope_freeSensor
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif

#endif /* MINTDRIVER_BITSCOPE_H */

