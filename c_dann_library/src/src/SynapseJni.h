/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class syncleus_dann_Synapse */

#ifndef _Included_syncleus_dann_Synapse
#define _Included_syncleus_dann_Synapse
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     syncleus_dann_Synapse
 * Method:    nativeConstructor
 * Signature: (Lsyncleus_dann/Neuron;Lsyncleus_dann/Neuron;D)I
 */
JNIEXPORT jint JNICALL Java_syncleus_dann_Synapse_nativeConstructor
  (JNIEnv *, jobject, jobject, jobject, jdouble);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    nativeDestructor
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_syncleus_dann_Synapse_nativeDestructor
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    getCurrentWeight
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_syncleus_dann_Synapse_getCurrentWeight
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    getDestinationNeuron
 * Signature: ()Lsyncleus_dann/Neuron;
 */
JNIEXPORT jobject JNICALL Java_syncleus_dann_Synapse_getDestinationNeuron
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    getSourceNeuron
 * Signature: ()Lsyncleus_dann/Neuron;
 */
JNIEXPORT jobject JNICALL Java_syncleus_dann_Synapse_getSourceNeuron
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    calculateOutput
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_syncleus_dann_Synapse_calculateOutput
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    learnWeight
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_syncleus_dann_Synapse_learnWeight
  (JNIEnv *, jobject);

/*
 * Class:     syncleus_dann_Synapse
 * Method:    calculateDifferential
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_syncleus_dann_Synapse_calculateDifferential
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
