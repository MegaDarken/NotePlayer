#include <stdio.h>
#include <math.h>

//Constants
#define proportionBetweenNotes 1.0594630943592953;//result of 2^(1/12)
#define lowestCFrequency 16.35f;//C0

#define squareWave 0
#define sawtoothWave 5
#define triangleWave 10

//Notes
float * calcNotes()
{
    static float notes[12 << 3];//* 8

    

    notes[0] = lowestCFrequency;
    
    for (int i = 1; i < 12 << 3; i++)//sizeof(notes)/sizeof(float)
    {
        notes[i] = notes[i - 1] * proportionBetweenNotes;
    }
    
    return notes;
    //48 should be middle C
    //57 should be A4
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
    int output = (int)(time * (pitch / 8000) * volume) % (volume << 1);
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

void outputLoop()
{
    float * notes = calcNotes();

    //Music Loop
    for(int i = 0; ;i++)
    {
    
        int outputValue = 0;
        
        for (size_t channel = 0; channel < 3; channel++)
        {
            outputValue += wave(i, notes[57], 30, channel*5);
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
