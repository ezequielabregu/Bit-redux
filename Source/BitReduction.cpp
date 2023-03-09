/*
  ==============================================================================

    BitReduction.cpp
    Created: 26 Jul 2022 1:21:15pm
    Author:  Ezequiel Abregu

  ==============================================================================
*/

#include "BitReduction.h"

//*** 4) desarrollo de la CLASS BitReduction
// primero se invoca la clase y luego el method (class::method)
// Constructor
BitReduction::BitReduction()
{
// destructor
}
BitReduction::~BitReduction()
{
//*** 5) Desarrollo del procesamiento de audio (bit reduction en este caso)

}
void BitReduction::bitReducProcess(float* inAudio, float* outAudio, int inBitReduction, int inNumSamples)
{       //si el slider inBitReduction es > 1 procesa, sino inAudio == outAudio
        if(inBitReduction > 1)
        {   // iteración x cada uno de los samples alojados en el buffer (inNumsamples)
            for(int i = 0; i < inNumSamples; i++)
            {   // si la división entre el valor del sample y inBiReduction no es 0
                if (i % inBitReduction != 0)
                {   //cada sample [i] del out = (entrada[i - módulo entre i y inBitreduction] * 2 )
                    outAudio[i] = (inAudio[i - i % inBitReduction]) * 2;
                }
            }
        }
}
