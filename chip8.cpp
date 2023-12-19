


struct Chip8
{
    union
    {
        // 0x1000 bytes of RAM (4k)
        unsigned char mem[0x1000] = {0};

        // 0x200 bytes are reserved
        struct
        {

        }
    };

};