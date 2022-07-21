#include <stdio.h>
#include <math.h>

//Constants
const int squareWave = 0;
const int sawtoothWave = 5;
const int triangleWave = 10;

//Notes
float * calcNotes()
{
    static float notes[8 * 12];

    double proportionBetweenNotes = 1.0594630943592953;//result of 2^(1/12)

    float lowestCFrequency = 16.35f;//C0

    notes[0] = lowestCFrequency;
    
    for (int i = 1; i < 8 * 12; i++)//sizeof(notes)/sizeof(float)
    {
        notes[i] = notes[i - 1] * proportionBetweenNotes;
    }
    
    return notes;
    //48 should be middle C
    //57 should be 
}

//Waves
int sawtooth(int time, float pitch, int volume)
{
    int output = (int)(time * (pitch / 16000) * volume) % volume;

    return output;
}



int square(int time, float pitch, int volume)
{
    int output = (int)(time * (pitch / 16000) * volume) % volume;
    output = (output < (volume / 2) ? 0 : volume);
    
    return output;
}

int triangle(int time, float pitch, int volume)
{
    int output = (int)(time * (pitch / 8000) * volume) % (volume * 2);
    output = output < volume ? volume - output : output - volume; 
    
    return output;
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

    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    float * notes = calcNotes();

    //Music Loop
    for(int i = 0; ;i++)
    {
    	int n=i>>14;
    	int s=i>>17;
    
        //Send value to output
        putchar(
        //printf(" %d",//Print output value for testing
            
            sawtooth(i,notes[46], 20) +
            square(i,notes[57], 50) +
            triangle(i,notes[48], 20)
            
        );
    }
}
