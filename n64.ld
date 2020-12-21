
OUTPUT_ARCH(mips)

#define START_SEGMENT(segmentName, ramAddr) \
    _##segmentName##SegmentStart = ADDR(.segmentName); \
    _##segmentName##SegmentRomStart = romPos; \
    .segmentName ramAddr : AT(romPos) SUBALIGN(16)

#define START_NOLOAD(segmentName, ramAddr) \
    _##segmentName##SegmentBssStart = ADDR(.segmentName.noload); \
    .segmentName.noload ramAddr (NOLOAD) : SUBALIGN(16)

#define START_SEGMENT_AFTER(segmentName, previousSegment) \
    _##segmentName##SegmentStart = ADDR(.segmentName); \
    _##segmentName##SegmentRomStart = romPos; \
    .segmentName ADDR(.previousSegment) + SIZEOF(.previousSegment) : AT(romPos) SUBALIGN(16)

#define START_NOLOAD_AFTER(segmentName, previousSegment) \
    _##segmentName##SegmentBssStart = ADDR(.segmentName.noload); \
    .segmentName.noload ADDR(.previousSegment) + SIZEOF(.previousSegment) (NOLOAD) : SUBALIGN(16)

#define END_SEGMENT(segmentName) \
    _##segmentName##SegmentEnd = ADDR(.segmentName) + SIZEOF(.segmentName); \
    romPos += SIZEOF(.segmentName); \
    _##segmentName##SegmentSize = SIZEOF(.segmentName); \
    _##segmentName##SegmentRomEnd = romPos

#define END_NOLOAD(segmentName) \
    _##segmentName##SegmentBssEnd = ADDR(.segmentName.noload) + SIZEOF(.segmentName.noload); \
    _##segmentName##SegmentBssSize = SIZEOF(.segmentName.noload)

SECTIONS
{
    romPos = 0;

    START_SEGMENT(header, 0xA4000000)
    {
        KEEP(BUILD_ROOT/src/header/header.o(.*data));
        KEEP(BUILD_ROOT/boot/boot.6102.o);
    }
    END_SEGMENT(header);

    romPos = 0x1000;

    START_SEGMENT(main, 0x80000400)
    {
        BUILD_ROOT/boot/entry.o(.text*);
        BUILD_ROOT/codesegment.o(.text*);
        
        PR/rspboot.o(.text*);
        PR/gspF3DEX2.fifo.o(.text*);
        PR/gspL3DEX2.fifo.o(.text*);
        PR/gspS2DEX2.fifo.o(.text*);

        BUILD_ROOT/codesegment.o(.data*);
        BUILD_ROOT/codesegment.o(COMMON*);
        BUILD_ROOT/codesegment.o(.scommon*);

        PR/rspboot.o(.*data*);
        PR/gspF3DEX2.fifo.o(.*data*);
        PR/gspL3DEX2.fifo.o(.*data*);
        PR/gspS2DEX2.fifo.o(.*data*);
        BUILD_ROOT/codesegment.o(.rodata*);
    }
    END_SEGMENT(main);

    __popcountsi2 = numberOfSetBits;

    START_NOLOAD_AFTER(main, main)
    {
        BUILD_ROOT/codesegment.o(.bss*);
    }
    END_NOLOAD(main);

    memPoolStart = .;

    START_SEGMENT(intro, 0x04000000)
    {
        BUILD_ROOT/segments/intro.o(.*data*);
        BUILD_ROOT/segments/intro.o(.bss*);
    }
    END_SEGMENT(intro);

    START_SEGMENT(sounds, 0x0A000000)
    {
        rockstep_1_start = .;
        sounds/rockstep_1.o(.*data*);
        rockstep_1_end = .;
        rockstep_2_start = .;
        sounds/rockstep_2.o(.*data*);
        rockstep_2_end = .;
    }
    END_SEGMENT(sounds);

    START_SEGMENT(dma_water, 0x00000000)
    {
        dma_textures/water/water.o;
    }
    END_SEGMENT(dma_water);

    START_SEGMENT(credits, 0x04000000)
    {
        BUILD_ROOT/segments/credits.o(.*data*);
        BUILD_ROOT/segments/credits.o(.bss*);
    }
    END_SEGMENT(credits);

    /DISCARD/ :
    {
        *(*);
    }
}