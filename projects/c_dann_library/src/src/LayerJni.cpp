#include "LayerJni.h"
#include "JniHelpers.h"
#include <jni.h>


JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_nativeConstructor(JNIEnv *Application, jobject SrcObject, jobject OwnedNeuralNetToSet, jobject OwnedDNAToSet, jobject DestinationLayerToSet, jobject SourceLayerToSet)
{
	//if the class already has been constructed then just return the already established native id.
	Layer *NativeThis = GetNativeLayer(Application, SrcObject);
	if( NativeThis != 0 )
		return (jint) NativeThis;
	
	//this is truely a new class, generate a global reference
	NativeThis = new Layer(GetNativeNeuralNet(Application, OwnedNeuralNetToSet), GetNativeDNA(Application, OwnedDNAToSet), GetNativeLayer(Application, DestinationLayerToSet), GetNativeLayer(Application, SourceLayerToSet));
	return (jint) NativeThis;
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_nativeDestructor(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	delete NativeThis;
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Layer_getSourceLayer(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	Layer* NewLayer = NativeThis->SourceLayer;

	jclass JavaLayerClass = Application->FindClass("syncleus/dann/Layer");
	jmethodID JavaLayerConstructor = Application->GetMethodID(JavaLayerClass, "<init>", "(I)V");
	return Application->NewObject(JavaLayerClass, JavaLayerConstructor, (jint)NewLayer);
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Layer_getDestinationLayer(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	Layer* NewLayer = NativeThis->DestinationLayer;

	jclass JavaLayerClass = Application->FindClass("syncleus/dann/Layer");
	jmethodID JavaLayerConstructor = Application->GetMethodID(JavaLayerClass, "<init>", "(I)V");
	return Application->NewObject(JavaLayerClass, JavaLayerConstructor, (jint)NewLayer);
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Layer_GetNeuralNet(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NeuralNet* NewNeuralNet = NativeThis->GetNeuralNet();

	jclass JavaNeuralNetClass = Application->FindClass("syncleus/dann/NeuralNet");
	jmethodID JavaNeuralNetConstructor = Application->GetMethodID(JavaNeuralNetClass, "<init>", "(I)V");
	return Application->NewObject(JavaNeuralNetClass, JavaNeuralNetConstructor, (jint)NewNeuralNet);
}


JNIEXPORT void JNICALL Java_syncleus_dann_Layer_AddNeurons(JNIEnv *Application, jobject SrcObject, jint NeuronCount)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->AddNeurons(NeuronCount);
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_AddNeuron(JNIEnv *Application, jobject SrcObject, jobject NeuronToAdd)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->AddNeuron(GetNativeNeuron(Application, NeuronToAdd));
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_ConnectAllToLayer(JNIEnv *Application, jobject SrcObject, jobject LayerToConnectTo)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->ConnectAllToLayer(GetNativeLayer(Application, LayerToConnectTo));
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_ConnectAllToNextLayer(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->ConnectAllToNextLayer();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_ConnectAllToForwardLayers(JNIEnv *Application, jobject SrcObject, jobject LastLayerToConnectTo)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->ConnectAllToLayer(GetNativeLayer(Application, LastLayerToConnectTo));
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Layer_GetRandomNeuron(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	Neuron* NewNeuron = NativeThis->GetRandomNeuron();

	jclass JavaNeuronClass = Application->FindClass("syncleus/dann/Neuron");
	jmethodID JavaNeuronConstructor = Application->GetMethodID(JavaNeuronClass, "<init>", "(I)V");
	return Application->NewObject(JavaNeuronClass, JavaNeuronConstructor, (jint)NewNeuron);
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Layer_GetNeuronByUid(JNIEnv *Application, jobject SrcObject, jint UidToGet)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	Neuron* NewNeuron = NativeThis->GetNeuronByUid(UidToGet);

	jclass JavaNeuronClass = Application->FindClass("syncleus/dann/Neuron");
	jmethodID JavaNeuronConstructor = Application->GetMethodID(JavaNeuronClass, "<init>", "(I)V");
	return Application->NewObject(JavaNeuronClass, JavaNeuronConstructor, (jint)NewNeuron);
}

JNIEXPORT jboolean JNICALL Java_syncleus_dann_Layer_ContainsNeuronByUid(JNIEnv *Application, jobject SrcObject, jint UidToCheck)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->ContainsNeuronByUid(UidToCheck);
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_NeuronCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->NeuronCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_OutgoingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->OutgoingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_IncommingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->IncommingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_MaximumOutgoingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->MaximumOutgoingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_MinimumOutgoingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->MinimumOutgoingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_MaximumIncommingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->MaximumIncommingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Layer_MinimumIncommingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->MinimumIncommingConnectionCount();
}

JNIEXPORT jdoubleArray JNICALL Java_syncleus_dann_Layer_GetOutput(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	double* AllOutputs = NativeThis->GetOutput();
	int OutputCount = NativeThis->NeuronCount();

	jdoubleArray JavaOutputs = Application->NewDoubleArray(OutputCount);
	jdouble* LocalJavaOutputs = Application->GetDoubleArrayElements(JavaOutputs, 0);
	for(int OutputIndex = 0; OutputIndex < OutputCount; OutputIndex++)
	{
		LocalJavaOutputs[OutputIndex] = AllOutputs[OutputIndex];
	}
	Application->ReleaseDoubleArrayElements(JavaOutputs, LocalJavaOutputs, 0);

	return JavaOutputs;
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_PropogateAll(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->PropogateAll();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_SetInput(JNIEnv *Application, jobject SrcObject, jdoubleArray InputToSet)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;
	
	int InputCount = Application->GetArrayLength(InputToSet);
	jdouble* LocalInputsToSet = Application->GetDoubleArrayElements(InputToSet, 0);

	NativeThis->SetInput(LocalInputsToSet);

	Application->ReleaseDoubleArrayElements(InputToSet, LocalInputsToSet, JNI_ABORT);
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_SetTrainData(JNIEnv *Application, jobject SrcObject, jdoubleArray TrainingToSet)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;
	
	int TrainingCount = Application->GetArrayLength(TrainingToSet);
	jdouble* LocalTrainingToSet = Application->GetDoubleArrayElements(TrainingToSet, 0);

	NativeThis->SetTrainData(LocalTrainingToSet);

	Application->ReleaseDoubleArrayElements(TrainingToSet, LocalTrainingToSet, JNI_ABORT);
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_BackPropogateWeightAll(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->BackPropogateWeightAll();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Layer_BackPropogateStructureAll(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Layer* NativeThis = GetNativeLayer(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->BackPropogateStructureAll();
}
