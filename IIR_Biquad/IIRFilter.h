//
//  IIRFilter.h
//  IIR_Biquad
//
//  Created by Matthew Hosack on 8/8/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//

#ifndef IIR_Biquad_IIRFilter_h
#define IIR_Biquad_IIRFilter_h

#define NUM_COEFFS 5

/*
y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]
a0 = 0.00460399444634034
a1 = 0.00920798889268068
a2 = 0.00460399444634034
b1 = -1.7990948352036205
b2 = 0.8175108129889816
//GAVE ERRORS
b0 =  0.00704967
b1 =  0.00000
b2 = -0.00704967
a1 = -1.96578
a2 =  0.985901
*/

typedef float SAMPLE;
struct BIQUAD{
    SAMPLE outsample1; //y[n-1]
    SAMPLE outsample2; //y[n-2]
    SAMPLE insample1;  //x[n-1]
    SAMPLE insample2;  //x[n-2]
    float b0;
    float b1;
    float b2;
    float a1;
    float a2;
};

typedef struct BIQUAD * BIQUADREF;

BIQUADREF bq_new(float ab_coeffs[NUM_COEFFS]);
void bq_tick(BIQUADREF bq, SAMPLE *input, SAMPLE *output, unsigned long length);

#endif
