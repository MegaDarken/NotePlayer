

char * noteWithinOctave(int index)
{
    //return (char)('C' + index);
    switch (index)
    {
    //C
    case 0:
        return "C";
        break;
    
    //C#
    case 1:
        return "C#";
        break;
    
    //D
    case 2:
        return "D";
        break;
    
    //D#
    case 3:
        return "D#";
        break;
    

    //E
    case 4:
        return "E";
        break;
    
    //F
    case 5:
        return "F";
        break;
    
    //F#
    case 6:
        return "F#";
        break;
    

    //G
    case 7:
        return "G";
        break;
    
    //G#
    case 8:
        return "G#";
        break;
    
    //A
    case 9:
        return "A";
        break;
    
    //A#
    case 10:
        return "A#";
        break;
    
    //B
    case 11:
        return "B";
        break;
    
    default:
        return "Invalid Note!";
        break;
    }
    
}

char * note(int index)
{
    char noteString[2];//Letter, sharp/flat, Octave

    //Note within octave
    noteString[0] = noteWithinOctave(index % 12);

    //Which Octave
    noteString[2] = (char)('0' + (int)(index / 12));

    return noteString;
}