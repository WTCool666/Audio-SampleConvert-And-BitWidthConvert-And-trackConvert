//
// Created by Administrator on 2018/12/18.
//
#include "RecordManager.h"
#include "com_kehwin_recorder_utils_AudioUtils.h"
#include "AudioHandle.h"
JNIEXPORT void JNICALL Java_com_kehwin_recorder_utils_AudioUtils_resampler
        (JNIEnv *env, jclass cls, jbyteArray srcData, jint srcSampleRate, jint srcSize, jbyteArray desData, jint desSampleRate,jint desSize){
    const int16_t * tempSrcData = (const int16_t *)env->GetByteArrayElements(srcData, 0);
    int16_t * tempDesData = (int16_t *)env->GetByteArrayElements(desData,0);
    AudioHandle::resampleData(tempSrcData,srcSampleRate,srcSize,tempDesData,desSampleRate,desSize);
    env->ReleaseByteArrayElements(srcData,(jbyte*)tempSrcData,0);
    env->ReleaseByteArrayElements(desData,(jbyte*)tempDesData,0);
}

JNIEXPORT jbyteArray JNICALL Java_com_kehwin_recorder_utils_AudioUtils_doubleChannel2SingleChannel
        (JNIEnv *env, jclass cls, jbyteArray doubleChannelData, jint size, jint nPerSampleBytesPerChannle){
    unsigned char * tempSrcData = (unsigned char *)env->GetByteArrayElements(doubleChannelData,0);
    unsigned char * tempDesData = AudioHandle::getSingleChannelAudio(tempSrcData,size,nPerSampleBytesPerChannle);
    env->ReleaseByteArrayElements(doubleChannelData,(jbyte*)tempSrcData,0);
    jbyteArray jbarray = env->NewByteArray(size/2);
    env->SetByteArrayRegion(jbarray,0,size/2,(jbyte*)tempDesData);
    return jbarray;
}

JNIEXPORT jbyteArray JNICALL Java_com_kehwin_recorder_utils_AudioUtils_bitWidthConvert
        (JNIEnv *env, jclass cls, jbyteArray data, jint size, jint oldBitWidth, jint newBitWidth){
    if(oldBitWidth==newBitWidth){
        return data;
    }
    //位宽转换之后，需要改变的数据大小
    int changeSize=0;
    //位宽转换之后，目标数据的大小
    int targetSize=0;
    //源数据的采样点
    int samplerRate = (size% (oldBitWidth/8)) ==0 ? ( size/ (oldBitWidth/8) ) : (int)( (float)(size/(oldBitWidth/8)) +1 );
    if(oldBitWidth > newBitWidth){
        changeSize = ( (oldBitWidth-newBitWidth) /8 ) *samplerRate;
        targetSize = size-changeSize;
    }else{//oldBitWidth < newBitWidth
        changeSize = ( (newBitWidth-oldBitWidth) /8 ) *samplerRate;
        targetSize = size+changeSize;
    }

    unsigned char * tempSrcData = (unsigned char *)env->GetByteArrayElements(data,0);
    unsigned char * tempDesData = AudioHandle::bitWidthConvert(tempSrcData,size,oldBitWidth, newBitWidth,targetSize ,samplerRate);
    env->ReleaseByteArrayElements(data,(jbyte*)tempSrcData,0);
    jbyteArray jbarray = env->NewByteArray(targetSize);//samplerRate *(oldBitWidth/8)
    env->SetByteArrayRegion(jbarray,0,targetSize,(jbyte*)tempDesData);
    return jbarray;
}

JNIEXPORT jintArray JNICALL Java_com_kehwin_recorder_utils_AudioUtils_byteArray2SamplerArray
        (JNIEnv *env, jclass cls , jbyteArray orgPcmBuf, jint size,jint bitWidth){
    int byteCountPreSampler = (bitWidth /8);
    if (orgPcmBuf==NULL || size==0){
        return NULL;
    }
    int samplerCount=0;
    if (size% byteCountPreSampler==0){
        samplerCount =  size/byteCountPreSampler;
    }else{
        samplerCount =  size/byteCountPreSampler+1;
    }
    if (samplerCount==0){
        return NULL;
    }
    int tempData =0;
    int* tempSamplerData=new int[samplerCount];
    LOGDV("samplerCount=%d byteCountPreSampler=%d",samplerCount,byteCountPreSampler);
    signed char *data =(signed char *)env->GetByteArrayElements(orgPcmBuf, 0);
    int j=0;
    for(int i=0;i<samplerCount;i++){
        tempData=0;
        for(int k=0;k<byteCountPreSampler;k++){
            signed int tempBuf =0;
            if ((j+k)<size){
                tempBuf = ( data[j+k] << (k*8) );
            }
            tempData = (tempData | tempBuf);
            /*if(i>300 && i<400){
                LOGDV("tempBuf=%d,k=%d,tempData=%d,i=%d",tempBuf,k,tempData,i);
            }*/
        }
//        LOGDV("tempData=%d i=%d",tempData,i);
        tempSamplerData[i]=tempData;
//			LogUtils.v("i="+i+" tempSamplerData.len="+tempSamplerData.length);
        j+=byteCountPreSampler;
    }
    jintArray tempBufs = env->NewIntArray(samplerCount);//samplerRate *(oldBitWidth/8)
    env->SetIntArrayRegion(tempBufs, 0, samplerCount,(jint*)(tempSamplerData));
    env->ReleaseByteArrayElements(orgPcmBuf,(jbyte*)data,0);
//		LogUtils.v("samplerCount="+samplerCount+" byteCountPreSampler="+byteCountPreSampler);
    return tempBufs;
}
