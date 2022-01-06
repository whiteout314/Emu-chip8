#include <iostream>
#include "chip8.hpp"
void Chip::loadMemory(const char *FileName)
{
    FILE * stream;
    stream = fopen(FileName, "rb");
    if(stream == NULL)
    {
        std::cerr << "File did not load on the disk" << std::endl;
       
    }
    fseek(stream, 0, SEEK_END);
    long disk_size = ftell(stream);
    rewind(stream);

    char * buffer = (char*)malloc(sizeof(char) * disk_size);
    if(buffer == NULL)
    {
        std::cerr << "File did not load on the disk" << std::endl;
        
    }
    fread(buffer, sizeof(char), disk_size, stream);
    for(int i = 0; i < disk_size; i++)
    {
      
        memory[i + 512] = (uint8_t)buffer[i];
       
    }
    fclose(stream);
    free(buffer);   
}

void Chip::runEmulator()
{
    
    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
   
    //variables used in the opcodes
    nnn = opcode & 0x0FFF;
    n = opcode & 0x000F;
    x = (opcode & 0x0F00) >> 8;
    y = (opcode & 0x00F0) >> 4;
    kk = opcode & 0x00FF;
    printf("OPCODE: %x \n", opcode);
    std::cout << "PC: " << pc << std::endl;

    switch(opcode &  0xF000)
    {
        case 0x0000:
            switch(opcode & 0x000F)
            {
                case 0x0000:
                    for(int i = 0; i < 64 *32; i++)
                    {
                        gfx[i] = 0;
                    }
                    pc+= 2;
                    break;
                case 0x000E:
                    pc = stack[sp];
                    sp--;
                    break;
            }
       
            break;
        case 0x1000:
            pc = nnn;
            break;
        case 0x2000: 
            stack[sp++] = pc;
            pc = nnn;
            break;
        case 0x3000:
            if(v[x] == kk)
            {
                pc += 2;
            }
            pc += 2;
            break;
        case 0x4000:
            if(v[x] != kk)
            {
                pc+=2;
            }
            pc+=2;
            break;
        case 0x5000:
            if(v[x] == v[y])
            {
                pc+=2;
            }
            pc += 2;
            break;
        case 0x6000:
            v[x] = kk;
            pc+=2;
            break;
        case 0x7000:
            v[x] += kk;
            pc+=2;
            break;
        case 0x8000:
            switch(opcode & 0x000F)
            {
                case 0x0000:
                    v[x] = v[y];
                    pc += 2;
                    break;
                case 0x0001:
                    v[x] |= v[y];
                    pc += 2;
                    break;
                case 0x0002: 
                    v[x] &= v[y];
                    pc += 2;
                    break;
                case 0x0003:
                    v[x] ^= v[y];
                    pc += 2;
                    break;
                case 0x0004: 
                    if(v[x] + v[y] > 255) {v[0xF] = 1;}
                    else{v[0xF] = 0;}
                    v[x] += v[y];
                    pc += 2;
                    break;
                case 0x0005:
                    if(v[x] > v[y]){v[0xF] = 1;}
                    else{v[0xF] = 0;}
                    pc +=2;
                    break;
                case 0x0006:
                    if((v[x] & 0x000F) == 1){v[0xF] = 1;}
                    else{v[0xF] = 0;}
                    v[x] /= 2;
                    break;
                case 0x0007:
                    if(v[y] > v[x]){v[0xF] = 1;}
                    else{v[0xF] = 0;}
                    v[x] = v[y] - v[x];
                    pc += 2;
                    break;
                case 0x000E:
                    if((v[x] &  0xF000) == 1){v[0xf] = 1;}
                    else{v[0xf] = 0;}
                    v[x] *= 2;
                    pc += 2;
                    break;
            }
            break;
        case 0x9000:
            if(v[x] != v[y]){pc += 2;}
            pc +=2;
            break;
        case 0xA000:
            I = nnn;
            pc += 2;
            break;
        case 0xB000:
            pc = nnn + v[0];
            break;
        case 0xC000:
            break;
        case 0xD000:
            {
                unsigned short x_coord = v[x];
                unsigned short y_coord = v[y];
                unsigned short height = n;
                unsigned short pixel;
                for(int yline = 0; yline < height; yline++)
                {
                    pixel = memory[I + yline];
                    for(int xline = 0; xline < 8; xline++)
                    {
                        if((pixel & (0x80 >> xline)) != 0)
                        {
                            if(gfx[(x + xline + ((y + yline) * 64))] == 1)
                            {
                                v[0xF] = 1;

                            }
                            gfx[x + xline + ((y + yline) * 64)] ^= 1;
                        }
                    }
                
                }
                drawFlag = true;
                pc += 2;

            }
            pc += 2;
    } 

    
}
