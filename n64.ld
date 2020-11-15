
OUTPUT_ARCH(mips)

#define START_SEGMENT(segmentName, ramAddr) \
    _##segmentName##SegmentStart = ADDR(.segmentName); \
    _##segmentName##SegmentRomStart = romPos; \
    .segmentName ramAddr : AT(romPos)

#define START_NOLOAD(segmentName, ramAddr) \
    _##segmentName##SegmentBssStart = ADDR(.segmentName.noload); \
    .segmentName.noload ramAddr (NOLOAD) :

#define START_SEGMENT_AFTER(segmentName, previousSegment) \
    _##segmentName##SegmentStart = ADDR(.segmentName); \
    _##segmentName##SegmentRomStart = romPos; \
    .segmentName ADDR(.previousSegment) + SIZEOF(.previousSegment) : AT(romPos)

#define START_NOLOAD_AFTER(segmentName, previousSegment) \
    _##segmentName##SegmentBssStart = ADDR(.segmentName.noload); \
    .segmentName.noload ADDR(.previousSegment) + SIZEOF(.previousSegment) (NOLOAD) :

#define END_SEGMENT(segmentName) \
    _##segmentName##SegmentEnd = ADDR(.segmentName) + SIZEOF(.segmentName); \
    romPos += SIZEOF(.segmentName); \
    _##segmentName##SegmentSize = SIZEOF(.segmentName); \
    _##segmentName##SegmentRomEnd = romPos

#define END_NOLOAD(segmentName) \
    _##segmentName##SegmentBssEnd = ADDR(.segmentName.noload) + SIZEOF(.segmentName.noload); \
    _##segmentName##SegmentBssSize = SIZEOF(.segmentName)

#define START_TEXT(segmentName) \
    _##segmentName##SegmentTextStart = .

#define END_TEXT(segmentName) \
    _##segmentName##SegmentTextEnd = .

#define START_DATA(segmentName) \
    _##segmentName##SegmentDataStart = .

#define END_DATA(segmentName) \
    _##segmentName##SegmentDataEnd = .

SECTIONS
{
    romPos = 0;

    START_SEGMENT(header, 0xA4000000)
    {
        BUILD_ROOT/src/header/header.o(.data);
        BUILD_ROOT/boot/boot.6102.o;
    }
    END_SEGMENT(header);

    romPos = 0x1000;

    START_SEGMENT(main, 0x80000400)
    {
        BUILD_ROOT/src/entry/entry.o(.text*);
        BUILD_ROOT/src/main/main.o(.text*);
        BUILD_ROOT/src/main/mem.o(.text*);
        BUILD_ROOT/src/main/init.o(.text*);
        BUILD_ROOT/src/main/task_sched.o(.text*);
        BUILD_ROOT/src/math/asmmath.o(.text*);
        /* BUILD_ROOT/src/usb/usb.o(.text*); */
        BUILD_ROOT/src/main/main.o(.data*);
        BUILD_ROOT/src/main/main.o(.rodata*);
        BUILD_ROOT/src/main/mem.o(.data*);
        BUILD_ROOT/src/main/mem.o(.rodata*);
        BUILD_ROOT/src/main/init.o(.data*);
        BUILD_ROOT/src/main/init.o(.rodata*);
        BUILD_ROOT/src/main/task_sched.o(.data*);
        BUILD_ROOT/src/main/task_sched.o(.rodata*);
        /* BUILD_ROOT/src/usb/usb.o(.data*);
        BUILD_ROOT/src/usb/usb.o(.rodata*); */
        . = ALIGN(16);
    }
    END_SEGMENT(main);

    START_SEGMENT_AFTER(gfx, main)
    {
        BUILD_ROOT/src/gfx/gfx.o(.text*);
        BUILD_ROOT/src/gfx/gfx.o(.data*);
        BUILD_ROOT/src/gfx/gfx.o(.rodata*);
        . = ALIGN(16);
    }
    END_SEGMENT(gfx);

    START_SEGMENT_AFTER(audio, gfx)
    {
        BUILD_ROOT/src/audio/audio.o(.text*);
        lib/libopus.a(.text*);
        BUILD_ROOT/src/audio/audio.o(.data*);
        BUILD_ROOT/src/audio/audio.o(.rodata*);
        lib/libopus.a(.data*);
        lib/libopus.a(.rodata*);
        . = ALIGN(16);
    }
    END_SEGMENT(audio);

    START_SEGMENT_AFTER(libgcc, audio)
    {
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.text*);
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.data*);
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.rodata*);
        . = ALIGN(16);
    }
    END_SEGMENT(libgcc);

    START_SEGMENT_AFTER(libnustd, libgcc)
    {
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.text*);
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.data*);
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.rodata*);
        . = ALIGN(16);
    }
    END_SEGMENT(libnustd);

    START_SEGMENT_AFTER(libultra, libnustd)
    {
        SDK/ultra/usr/lib/libgultra_rom.a(.text*);
        SDK/ultra/usr/lib/libgultra_rom.a(.data*);
        SDK/ultra/usr/lib/libgultra_rom.a(.rodata*);
        SDK/ultra/usr/lib/libgultra_rom.a(.scommon*);
        SDK/ultra/usr/lib/libgultra_rom.a(COMMON*);
        . = ALIGN(16);
    }
    END_SEGMENT(libultra);

    START_SEGMENT_AFTER(ucode, libultra)
    {
        SDK/ultra/usr/lib/PR/rspboot.o(.text*);
        SDK/ultra/usr/lib/PR/gspF3DEX2.fifo.o(.text*);
        SDK/ultra/usr/lib/PR/gspL3DEX2.fifo.o(.text*);
        SDK/ultra/usr/lib/PR/rspboot.o(.data*);
        SDK/ultra/usr/lib/PR/gspF3DEX2.fifo.o(.data*);
        SDK/ultra/usr/lib/PR/gspL3DEX2.fifo.o(.data*);
        . = ALIGN(16);
    }
    END_SEGMENT(ucode);

    START_NOLOAD_AFTER(main, ucode)
    {
        BUILD_ROOT/src/main/main.o(.bss*);
        BUILD_ROOT/src/main/mem.o(.bss*);
        BUILD_ROOT/src/main/init.o(.bss*);
        BUILD_ROOT/src/main/task_sched.o(.bss*);
        /* BUILD_ROOT/src/usb/usb.o(.bss*); */
        . = ALIGN(16);
    }
    END_NOLOAD(main);

    START_NOLOAD_AFTER(libultra, main.noload)
    {
        SDK/ultra/usr/lib/libgultra_rom.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(libultra);

    START_NOLOAD_AFTER(gfx, libultra.noload)
    {
        BUILD_ROOT/src/gfx/gfx.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(gfx);

    START_NOLOAD_AFTER(audio, gfx.noload)
    {
        BUILD_ROOT/src/audio/audio.o(.bss*);
        lib/libopus.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(audio);

    START_NOLOAD_AFTER(libgcc, audio.noload)
    {
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(libgcc);

    START_NOLOAD_AFTER(libnustd, libgcc.noload)
    {
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(libnustd);

    memPoolStart = .;

    START_SEGMENT(intro, 0x04000000)
    {
        BUILD_ROOT/src/segments/intro.o(.data*);
        BUILD_ROOT/src/segments/intro.o(.rodata*);
        . = ALIGN(16);
    }
    END_SEGMENT(intro);

    START_SEGMENT(song, 0x04000000)
    {
        . = ALIGN(16);
    }
    END_SEGMENT(song);

    /DISCARD/ :
    {
        *(*);
    }
}