#ifndef  _AUDIO_SAMPLE_H_
#define _AUDIO_SAMPLE_H_
#include "KwDataType.h"

void insert8_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert8_16k(k_int16 *psi_buff, k_int16* psi_outbuf,k_uint32 ui_samples);
void convert24_12k(k_int16 *psi_buff,k_int16* psi_outbuf,k_uint32 ui_samples);
void convert24_8k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples);
void convert12_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert12_48k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples);
void convert48_16k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples);
void setpresample(k_int16 sampe);

#endif