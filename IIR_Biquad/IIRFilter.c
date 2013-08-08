//
//  IIRFilter.c
//  IIR_Biquad
//
//  Created by Matthew Hosack on 8/8/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "IIRFilter.h"

BIQUADREF bq_new(float ab_coeffs[NUM_COEFFS])
{
    BIQUADREF tmp = (BIQUADREF)malloc(sizeof(struct BIQUAD));
    tmp->b0 = ab_coeffs[0];
    tmp->b1 = ab_coeffs[1];
    tmp->b2 = ab_coeffs[2];
    tmp->a1 = ab_coeffs[3];
    tmp->a2 = ab_coeffs[4];
    tmp->insample1 = 0.0;
    tmp->insample2 = 0.0;
    tmp->outsample1 = 0.0;
    tmp->outsample2 = 0.0;
    return tmp;
}

void bq_tick(BIQUADREF bq, SAMPLE *input, SAMPLE *output, unsigned long length){
    unsigned long i;
    for (i = 0; i < length; i++) {
        /*
         y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]
        */
        *output =   (bq->b0 * (*input)) +
                    (bq->b1 * (bq->insample1)) +
                    (bq->b2 * (bq->insample2)) -
                    (bq->a1 * bq->outsample1) -
                    (bq->a2 * (bq->outsample2));
        //update biquad values
        bq->outsample2 = bq->outsample1;
        bq->outsample1 = *output++;
        bq->insample2 = bq->insample1;
        bq->insample1 = *input++;
    }
}