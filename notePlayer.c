#include <stdio.h>
#include <math.h>

#include "noteChannel.h"
#include "randomTable.h"

//Constants
#define proportionBetweenNotes 1.0594630943592953;//result of 2^(1/12)
#define lowestCFrequency 16.35f;//C0

#define squareWaveIndex 0
#define pulseWaveIndex 2
#define sawtoothWaveIndex 5
#define triangleWaveIndex 10
#define sineWaveIndex 15
#define noiseWaveIndex 20

//nightcracker's fast sine solution https://www.gamedev.net/forums/topic/621589-extremely-fast-sin-approximation/
double fast_sine(double x) {
int k;
double y;
double z;

z = x;
z *= 0.3183098861837907;
z += 6755399441055744.0;
k = *((int *) &z);
z = k;
z *= 3.1415926535897932;
x -= z;
y = x;
y *= x;
z = 0.0073524681968701;
z *= y;
z -= 0.1652891139701474;
z *= y;
z += 0.9996919862959676;
x *= z;
k &= 1;
k += k;
z = k;
z *= x;
x -= z;

return x;
}

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

int wrapToVolume(int magnitude, int volume)
{
    return magnitude <= 0 ? 0 : magnitude % volume;
}

//Waves
int sawtooth(int time, float pitch, int volume)
{
    //Gradual increment to Volume before setting back to 0, the simplest wave to generate.
    int output = wrapToVolume((int)(time * (pitch * 0000625) * volume), volume);

    return output;
}



int square(int time, float pitch, int volume)
{
    //Value is switches between 0 and Volume for half of the times
    int output = wrapToVolume((int)(time * (pitch * 0.0000625) * volume), volume);
    output = (output < (volume >> 1) ? 0 : volume);
    
    return output;
}

int triangle(int time, float pitch, int volume)
{
    //Deincrement linearly to 0 then up to Volume, Mathematically simple form of sine wave.
    int output = wrapToVolume((int)(time * (pitch * 0.000125) * volume), (volume << 1));
    output = output < volume ? volume - output : output - volume; 
    
    return output;
}

int sineWave(int time, float pitch, int volume)
{
    return wrapToVolume((int)(fast_sine(time * (pitch * 0.000392699081699)) * volume), volume);//2546.47908947 = 8000 / pi
}

int noise(int time, float pitch, int volume)
{
    return wrapToVolume(getRandomUInt(), volume);
}

int pulse(int time, float pitch, int volume, float proportion)
{
    int output = wrapToVolume((int)(time * (pitch * 0.0000625) * volume), volume);
    output = (output < (volume * proportion) ? 0 : volume);
    
    return output;
}

int wave(int time, float pitch, int volume, int waveType)
{

    switch (waveType)
    {
    case squareWaveIndex:
        return square(time, pitch, volume);
        break;

    case sawtoothWaveIndex:
        return sawtooth(time, pitch, volume);
        break;
    
    case triangleWaveIndex:
        return triangle(time, pitch, volume);
        break;

    case sineWaveIndex:
        return sineWave(time, pitch, volume);
        break;

    case noiseWaveIndex:
        return noise(time, pitch, volume);
        break;

    case pulseWaveIndex:
        return pulse(time, pitch, volume, 0.2f);
        break;

    default:
        return 0;
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
    channels[0].waveType = 2;

    channels[1].note = 60;
    channels[1].volume = 0;
    channels[1].waveType = 2;

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
