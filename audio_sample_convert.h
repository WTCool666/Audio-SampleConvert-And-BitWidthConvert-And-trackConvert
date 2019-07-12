#ifndef  _AUDIO_SAMPLE_H_
#define _AUDIO_SAMPLE_H_
typedef signed char k_sint8; //注意编译把char认为是有符号还是无符号。
typedef char k_int8; //注意编译把char认为是有符号还是无符号。
typedef unsigned char k_uint8;
typedef signed short int  k_int16;
typedef unsigned short int k_uint16;
typedef signed int k_int32;
typedef unsigned int k_uint32;
typedef signed long k_intL32;
typedef unsigned long k_uintL32;
typedef signed long long k_intLL64;
typedef unsigned long long k_uintLL64;
typedef float k_float32;
typedef double k_double64;

void insert8_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert8_16k(k_int16 *psi_buff, k_int16* psi_outbuf,k_uint32 ui_samples);
void convert24_12k(k_int16 *psi_buff,k_int16* psi_outbuf,k_uint32 ui_samples);
void convert24_8k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples);
void convert12_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert12_48k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert48_16k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples);
void setpresample(k_int16 sampe);

#endif