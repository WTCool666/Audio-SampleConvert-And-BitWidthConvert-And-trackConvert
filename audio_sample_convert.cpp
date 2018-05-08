#include "audio_sample_convert.h"
/*****************************************************************************
 name        : insert8_24k
 description : none
 Arguments   : none 
 Returns     : none 
 designer    : commemt by syf
*****************************************************************************/
void insert8_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 
ui_samples)
{
    static k_int16 s_sample_prev = 0;
    k_uint32 i; 
    k_uint32 j = 3;
    k_uint16 us_step = 0;

    us_step = ((psi_input[0] - s_sample_prev)) / 3; //
        
    psi_output[0] = s_sample_prev + us_step;
    psi_output[1] = s_sample_prev + (us_step*2);
    psi_output[2] = psi_input[0]; //us_data_pre + (us_step*3)

	for(i = 1;i < ui_samples;i++)
	{
            us_step = (psi_input[i] - psi_input[i-1]) / 3;
            psi_output[j] = psi_input[i-1] + us_step;
            psi_output[j+1] = psi_input[i-1] + (us_step*2);
            psi_output[j+2] = psi_input[i]; //psi_input[i-1] + (us_step*3)
            j += 3;
	}
    s_sample_prev = psi_input[i-1];
}

/*****************************************************************************
 name        : convert12_8k
 description : none
 Arguments   : none 
 Returns     : none 
 designer    : commemt by syf
*****************************************************************************/
static k_int16 s_sample_prev = 0;
void setpresample(k_int16 sampe)
{
	s_sample_prev = sampe;
}
void convert8_16k(k_int16 *psi_buff, k_int16* psi_outbuf,k_uint32 ui_samples){

    k_uint32 i,j = 2;
    k_uint16 us_step = 0;
    us_step = ((psi_buff[0] - s_sample_prev)) / 2; //
    psi_outbuf[0] = s_sample_prev + us_step;
    psi_outbuf[1] = psi_buff[0]; //us_data_pre + (us_step*3)

    for(i=1;i<ui_samples;i++){
        us_step = (psi_buff[i] - psi_buff[i-1]) / 2;
        psi_outbuf[j] =  psi_buff[i-1]+us_step;
        psi_outbuf[j+1] =  psi_buff[i];
        j+=2;
    }
    s_sample_prev = psi_buff[i-1];
}

void convert24_12k(k_int16 *psi_buff,k_int16* psi_outbuf,k_uint32 ui_samples)
{
        k_uint32 i;
        k_uint32 j;
        for(i = 0, j = 0; i < ui_samples; i += 2)
       {
	    psi_outbuf[j++] = psi_buff[i];
       }
}

void convert24_8k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples)
{
	k_uint32 i;
       k_uint32 j;

	for(i = 0, j = 0; i < ui_samples; i += 3)
	{
	    psi_output[j++] = psi_buff[i];
	}
}

/*****************************************************************************
 name        : insert12_48k
 description : none
 Arguments   : none 
 Returns     : none 
 designer    : commemt by syf
*****************************************************************************/
void convert12_24k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples)
{
    static k_int16 us_data_pre = 0;
	k_uint32 i; 
    k_uint32 j = 2;
    
    psi_output[0] = (us_data_pre+psi_input[0]) >> 1;
    psi_output[1] = psi_input[0];

	for(i = 1;i < ui_samples;i++)
	{
        psi_output[j] = (psi_input[i-1]+psi_input[i]) >> 1;
        psi_output[j+1] = psi_input[i];
        j += 2;
	}
    us_data_pre = psi_input[i-1];
}

void convert12_48k(k_int16 *psi_input, k_int16 *psi_output,k_uint32 ui_samples)
{
    static k_int16 us_data_pre = 0;
    k_uint32 i; 
    k_uint32 j = 4;
    k_uint16 us_step = 0;
    
    us_step = (psi_input[0]-us_data_pre) /4;
    psi_output[0] = us_data_pre+us_step;
    psi_output[1] = us_data_pre+us_step*2;
    psi_output[2] = us_data_pre+us_step*3;
    psi_output[3] = psi_input[0];

    for(i = 1;i < ui_samples;i++)
    {
            us_step = (psi_input[i]-psi_input[i-1]) /4;
            psi_output[j] = psi_input[i-1]+us_step;
            psi_output[j+1] = psi_input[i-1]+us_step*2;
            psi_output[j+2] = psi_input[i-1]+us_step*3;
            psi_output[j+3] = psi_input[i];
            j += 4;
    }
    us_data_pre = psi_input[i-1];
}


void convert48_16k(k_int16 *psi_buff,k_int16 *psi_output,k_uint32 ui_samples)
{
	k_uint32 i;
       k_uint32 j;

	for(i = 0, j = 0; i < ui_samples; i += 3)
	{
	    psi_output[j++] = psi_buff[i];
	}
}