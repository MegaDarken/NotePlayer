#include <stdio.h>
#include <math.h>

#include "noteChannel.h"
#include "randomTable.h"

//Constants
#define proportionBetweenNotes 1.0594630943592953;//result of 2^(1/12)
#define lowestCFrequency 16.35f;//C0

#define squareWave 0
#define sawtoothWave 5
#define triangleWave 10
#define sineWave 15
#define noiseWave 20

//Notes
float * calcFrequencies()
{
    static float notes[12 << 3];//* 8

    
    //The first note is C0
    notes[0] = lowestCFrequency;
    
    for (size_t i = 1; i <= sizeof(notes) / sizeof(float); i++)//sizeof(notes)/sizeof(float)
    {
        //Every note is relitive to the previous one, with a proportion of 2^(1/12).
        notes[i] = notes[i - 1] * proportionBetweenNotes;
    }
    
    return notes;
    //48 should be middle C
    //57 should be A4
}

//Waves
int sawtooth(int time, float pitch, int volume)
{
    //Gradual increment to Volume before setting back to 0, the simplest wave to generate.
    int output = (int)(time * (pitch / 16000) * volume) % volume;

    return output;
}



int square(int time, float pitch, int volume)
{
    //Value is switches between 0 and Volume for half of the times
    int output = (int)(time * (pitch / 16000) * volume) % volume;
    output = (output < (volume / 2) ? 0 : volume);
    
    return output;
}

int triangle(int time, float pitch, int volume)
{
    //Deincrement linearly to 0 then up to Volume, Mathematically simple form of sine wave.
    int output = (int)(time * (pitch / 8000) * volume) % (volume << 1);
    output = output < volume ? volume - output : output - volume; 
    
    return output;
}

int noise(int time, float pitch, int volume)
{
    return getRandomUInt() % volume;
}


int wave(int time, float pitch, int volume, int waveType)
{

    switch (waveType)
    {
    case squareWave:
        return square(time, pitch, volume);
        break;

    case sawtoothWave:
        return sawtooth(time, pitch, volume);
        break;
    
    case triangleWave:
        return triangle(time, pitch, volume);
        break;

    case noiseWave:
        return noise(time, pitch, volume);
        break;

    default:
        break;
    }
}

void outputLoop()
{
    //Scale of notes from C0 to B8
    float * notes = calcFrequencies();

    //Load channel data
    int channelCount = 1;

    //Channel Array
    struct noteChannel channels[channelCount];

    channels[0].note = 40;
    channels[0].volume = 50;
    channels[0].waveType = 20;

    channels[1].note = 60;
    channels[1].volume = 30;
    channels[1].waveType = 20;

    //Music Loop
    for(int i = 0; ;i++)
    {
        //Change channel values if needed


        //Output starts at 0 for each loop
        int outputValue = 0;
        
        //For each sound channel
        for (size_t channel = 0; channel <= sizeof(channels) / sizeof(channel); channel++)
        {
            //Add this channel's wave to the output value.
            outputValue += wave(i, notes[channels[channel].note], channels[channel].volume, channels[channel].waveType);
        }
         

        //Send value to output
        putchar(
        //printf(" %d",//Print output value for testing
        outputValue    
        );
    }
}

int main(int argc, char *argv[])
{
    outputLoop(); 
}
