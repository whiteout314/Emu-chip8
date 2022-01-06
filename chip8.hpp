#include <iostream>

/*
 * 
 *
 *
 *
 *
 *
 *
 */


class Chip {
    public:
       //VARIABLES 
        int gfx[64 * 32]; // graphics array representation
        bool drawFlag;
        uint8_t  memory[4095];

       //FUNCTIONS
        void loadMemory(const char *FileName);
        void runEmulator();
        uint16_t nnn;
        uint8_t n;
        uint8_t x;
        uint8_t y;
        uint8_t kk;

        
    private:
       //VARIABLES
        uint8_t v[0xF];
        uint16_t I;  //This is generally used to store memory adresses
        uint16_t pc; //program counter
        uint8_t  sp; // This is the stack pointer
        uint16_t stack[16];        
        uint8_t delayTimer;
        uint8_t soundTimer;
       //FUNCTIONS
       //NONE
       
};
