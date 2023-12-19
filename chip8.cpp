#define instruction(P) \
P(h==0&&x==0&&kk==0xE0, for(auto &i:disp) i = 0; )      00E0 - CLS
P(h==0&&x==0&&kk==0xEE, PC=stack[SP-- % 12];)           00EE - RET
P(h==1, PC=nnn;)                                        1nnn - JP addr
P(h==2, {stack[++SP]=PC,PC=nnn;})                       2nnn - CALL addr
P(h==3, if(Vx==kk){PC+=2;})                             3xkk - SE Vx, byte
P(h==4, if(Vx!=kk){PC+=2;})                             4xkk - SNE Vx, byte
P(h==5&&l==0, if(Vx==V7){PC+=2;})                       5xy0 - SE Vx, Vy
P(h==6, Vx=kk)                                          6xkk - LD Vx, byte
P(h==7, Vx=Vx+kk)                                       7xkk - ADD Vx, byte
P(h==8&&l==0, Vx=Vy)                                    8xy0 - LD Vx, Vy
P(h==8&&l==1, Vx=Vx|Vy)                                 8xy1 - OR Vx, Vy
P(h==8&&l==2, Vx=Vx&Vy)                                 8xy2 - AND Vx, Vy
P(h==8&&l==3, Vx=Vx^Vy)                                 8xy3 - XOR Vx, Vy
P(h==8&&l==4, {u=Vx+Vy;V[15]=u>>8;Vx=u;})               8xy4 - ADD Vx, Vy
P(h==8&&l==5, {u=Vx-Vy;V[15]=!(u>>8);Vx=u;})            8xy5 - SUB Vx, Vy
P(h==8&&l==6, {V[15]=Vx&1;Vx>>=1;})                     8xy6 - SHR Vx {, Vy}
P(h==8&&l==7, {u=Vy-Vx;V[15]=!(u>>8);Vx=u;})            8xy7 - SUBN Vx, Vy
P(h==8&&l==14, {V[15]=Vx&128;Vx<<=1;})                  8xyE - SHL Vx {, Vy}
P(h==9&&l==0, if(Vx!=Vy){PC+=2;}                        9xy0 - SNE Vx, Vy
P(h==10,                                                Annn - LD I, addr
P(h==11,                                                Bnnn - JP V0, addr
P(h==12,                                                Cxkk - RND Vx, byte
P(h==13,                                                Dxyn - DRW Vx, Vy, nibble
P(h==14&&kk==158,                                       Ex9E - SKP Vx
P(h==14&&kk==161,                                       ExA1 - SKNP Vx
P(h==15&&kk==7,                                         Fx07 - LD Vx, DT
P(h==15&&kk==10,                                        Fx0A - LD Vx, K
P(h==15&&kk==21,                                        Fx15 - LD DT, Vx
P(h==15&&kk==24,                                        Fx18 - LD ST, Vx
P(h==15&&kk==30,                                        Fx1E - ADD I, Vx
P(h==15&&kk==41,                                        Fx29 - LD F, Vx
P(h==15&&kk==51,                                        Fx33 - LD B, Vx
P(h==15&&kk==85,                                        Fx55 - LD [I], Vx
P(h==15&&kk==101,                                       Fx65 - LD Vx, [I]
P(h==0&&x==0&&y==12,                                    00Cn - SCD nibble
P(h==0&&x==0&&kk==251,                                  00FB - SCR
P(h==0&&x==0&&kk==252,                                  00FC - SCL
P(h==0&&x==0&&kk==253,                                  00FD - EXIT
P(h==0&&x==0&&kk==254,                                  00FE - LOW
P(h==0&&x==0&&kk==255,                                  00FF - HIGH
P(h==13&&l==0,                                          Dxy0 - DRW Vx, Vy, 0
P(h==15&&kk==48,                                        Fx30 - LD HF, Vx
P(h==15&&kk==117,                                       Fx75 - LD R, Vx
P(h==15&&kk==133,                                       Fx85 - LD Vx, R

struct Chip8
{
    union
    {
        // 0x1000 bytes of RAM (4k)
        unsigned char mem[0x1000] = {0};

        // 0x200 bytes are reserved for registers, stack, etc.
        struct
        {
            unsigned char V[0x10], delayTimer, soundTimer, SP;
            unsigned short stack[16], PC, I;
            unsigned char disp[64*32 / 8], sprite[16*5];
        };
    };

};