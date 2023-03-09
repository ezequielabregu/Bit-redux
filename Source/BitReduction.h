/*
  ==============================================================================

    BitReduction.h
    Created: 26 Jul 2022 1:21:15pm
    Author:  Ezequiel Abregu

  ==============================================================================
*/

#pragma once

//*** 1) creo la CLASS
class BitReduction
{
// siempre debe ser public para poder acceder al contenido de la clase
public:
    //*** 2) Constructor / Destructor
    BitReduction();
    ~BitReduction();
    //*** 3) Method (audio input, audio output, slider (integer), nsamples)
    // ver el detalle que para el audio in/out usa un pointer (float*)
    void bitReducProcess(float* inAudio, float* outAudio, int inBitReduction, int inNumSamples);
};
