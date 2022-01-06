#include <iostream>
#include "chip8.cpp"
#include <inttypes.h>
#include <stdio.h>






int main()
{
    Chip chip = Chip();
    chip.loadMemory("maze.ch8");
    for(int i = 0; i < 100; i++)
    {
        chip.runEmulator();
    }
    
    
    return 0;
}

