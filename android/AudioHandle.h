#ifndef AUDIOHANDLE_H
#define AUDIOHANDLE_H

#include<stdio.h>
#include<string.h>
#include "android_logcat.h"
#define BIT_8_WIDTH 8
#define BIT_16_WIDTH 16
#define BIT_24_WIDTH 24
#define BIT_32_WIDTH 32

class AudioHandle{
public:

	static unsigned char * getSingleChannelAudio(unsigned char * pDoubleChannelBuf, int nLen, int nPerSampleBytesPerChannle)
	{
		int nOneChannelLen = nLen / 2;
		unsigned char * pOneChannelBuf = new unsigned char[nOneChannelLen];
		for (int i = 0; i < nOneChannelLen / 2; i++)
		{
			memcpy((uint16_t*)pOneChannelBuf + i, ((uint32_t *)(pDoubleChannelBuf)) + i, nPerSampleBytesPerChannle);
		}
		return pOneChannelBuf;
	}
	
	static unsigned char * audioTrackConvert(unsigned char * srcTrackBuf, int srcTrackLen, int nPerSampleBytesPerTrack,bool isSingleConvertDoubleTrack)
	{
		int targetBuflLen=0;
		int offset=0;
		unsigned char * targetTrackBuf;
		if(isSingleConvertDoubleTrack){//单声道转双声道
			targetBuflLen== srcTrackLen * 2;
			targetTrackBuf= new unsigned char[targetBuflLen];
			for (int i = 0; i < srcTrackLen; i+=nPerSampleBytesPerTrack)
			{
				for (int j = 0; j < 2; j++)
				{	
					memcpy(targetTrackBuf + offset, 
					srcTrackBuf + (i*nPerSampleBytesPerTrack), nPerSampleBytesPerTrack);
					offset+=nPerSampleBytesPerTrack;
				}
			}
		}else{//双声道转单声道
			targetBuflLen== srcTrackLen  /2;
			targetTrackBuf= new unsigned char[targetBuflLen];
			for (int i = 0; i < targetBuflLen; i+=nPerSampleBytesPerTrack)
			{
				memcpy(targetTrackBuf + (i*nPerSampleBytesPerTrack), 
				srcTrackBuf + ((i+1)*nPerSampleBytesPerTrack), nPerSampleBytesPerTrack);
			}
		}
		return targetTrackBuf;
	}

	static unsigned char * bitWidthConvert(unsigned char * data, int nLen, int oldBitWidth,int newBitWidth,int targetSize,int samplerRate)
	{
		if(oldBitWidth==newBitWidth){
			return data;
		}
        //新的位宽的字节数
        int newBitWidthByteCount= newBitWidth/8;
		//旧的位宽的字节数
        int oldBitWidthByteCount= oldBitWidth/8;
		//目标数据
		unsigned char * targetBuf = new unsigned char[targetSize];
		//LOGDV("tempBitWidthTimes=%d,targetSize=%d,samplerRate=%d",tempBitWidthTimes,targetSize,samplerRate);

		//临时的源数据的每个采样点的数据
		uint32_t tempData;
		//目标数据偏移量
		int newBitWidthOffset=0;
		int oldBitWidthOffset=0;

       // uint32_t* data32bit=(uint32_t*)data;
        if (oldBitWidth < newBitWidth){
            for (int i = 0; i < samplerRate; ++i) {
				memcpy(&tempData,data+oldBitWidthOffset, oldBitWidthByteCount);
				oldBitWidthOffset+=oldBitWidthByteCount;
                memcpy(targetBuf+newBitWidthOffset,&tempData, newBitWidthByteCount);
                newBitWidthOffset+=newBitWidthByteCount;
            }
        }else{
            for (int i = 0; i < samplerRate; ++i) {
				memcpy(&tempData,data+oldBitWidthOffset, oldBitWidthByteCount);
				oldBitWidthOffset+=oldBitWidthByteCount;
                //去除低位
                tempData =  (tempData >> (oldBitWidth-newBitWidth) );
                memcpy(targetBuf+newBitWidthOffset,&tempData, newBitWidthByteCount);
                newBitWidthOffset+=newBitWidthByteCount;
            }
        }
       /* u_int8_t* data8bit;
        uint16_t* data16bit;
        uint32_t* data32bit;
        if (oldBitWidth < newBitWidth){
		    switch (oldBitWidth){
		        case BIT_8_WIDTH:
                    data8bit=(u_int8_t*)data;
                    for (int i = 0; i < samplerRate; ++i) {
                        tempData = *(data8bit+i) ;
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
		            break;
		        case BIT_16_WIDTH:
//                    data16bit=(uint16_t*)data;
                    for (int i = 0; i < nLen; ++i) {
                        tempData = *(data16bit+i) ;
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
		            break;
		        case BIT_24_WIDTH:
		        case BIT_32_WIDTH:
                    data32bit=(uint32_t*)data;
                    for (int i = 0; i < samplerRate; ++i) {
                        tempData = *(data32bit+i) ;
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
		            break;
		    }

		}else{
            switch (oldBitWidth){
                case BIT_8_WIDTH:
                    data8bit=(u_int8_t*)data;
                    for (int i = 0; i < samplerRate; ++i) {
                        //去除低位
                        tempData =  ((*(data8bit+i)) >> (oldBitWidth-newBitWidth) );
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
                    break;
                case BIT_16_WIDTH:
                    data16bit=(uint16_t*)data;
                    for (int i = 0; i < samplerRate; ++i) {
                        //去除低位
                        tempData =  ((*(data16bit+i)) >> (oldBitWidth-newBitWidth) );
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
                    break;
                case BIT_24_WIDTH:
                case BIT_32_WIDTH:
                    data32bit=(uint32_t*)data;
                    for (int i = 0; i < samplerRate; ++i) {
                        //去除低位
//                        tempData =  ((*(data32bit+i)) >> (oldBitWidth-newBitWidth) );
                        tempData =  ((*(data32bit+i)) );
                        memcpy(targetBuf+count,&tempData, newBitWidthByteCount);
                        count+=newBitWidthByteCount;
                    }
                    break;
            }
		}*/
		return targetBuf;
	}

	static void resampleData(const int16_t *sourceData, int32_t sampleRate, uint32_t srcSize, int16_t *destinationData, int32_t newSampleRate,uint32_t dstSize)
	{
		if (sampleRate == newSampleRate)
		{
			memcpy(destinationData, sourceData, srcSize * sizeof(int16_t));
			return;
		}
		uint32_t last_pos = srcSize - 1;
		//LOGDV("srcSize=%d,dstSize=%d",srcSize,dstSize);
		for (uint32_t idx = 0; idx < dstSize; idx++)
		{
			float index = ((float) idx * sampleRate) / (newSampleRate);
			uint32_t p1 = (uint32_t) index;
			float coef = index - p1;
			uint32_t p2 = (p1 == last_pos) ? last_pos : p1 + 1;
			destinationData[idx] = (int16_t) ((1.0f - coef) * sourceData[p1] + coef * sourceData[p2]);
		//	LOGDV("index=%f,p1=%d,coef=%f,p2=%d",index,p1,coef,p2);
		}
	}

};

#endif // AUDIOHANDLE_H
