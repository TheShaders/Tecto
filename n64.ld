
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
        KEEP(BUILD_ROOT/src/header/header.o(.*data));
        KEEP(BUILD_ROOT/boot/boot.6102.o);
    }
    END_SEGMENT(header);

    romPos = 0x1000;

    START_SEGMENT(main, 0x80000400)
    {
        BUILD_ROOT/src/entry/entry.o(.text*);
        KEEP(BUILD_ROOT/src/main/main.o(.text*));
        BUILD_ROOT/src/main/mem.o(.text*);
        BUILD_ROOT/src/main/init.o(.text*);
        BUILD_ROOT/src/main/input.o(.text*);
        BUILD_ROOT/src/main/task_sched.o(.text*);
        BUILD_ROOT/src/main/multiarraylist.o(.text*);
        BUILD_ROOT/src/math/asmmath.o(.text*);
        BUILD_ROOT/src/math/mathutils.o(.text*);
        BUILD_ROOT/src/usb/usb.o(.text*);
        BUILD_ROOT/src/usb/debug.o(.text*);
        BUILD_ROOT/src/main/main.o(.*data*);
        BUILD_ROOT/src/main/mem.o(.*data*);
        BUILD_ROOT/src/main/init.o(.*data*);
        BUILD_ROOT/src/main/input.o(.*data*);
        BUILD_ROOT/src/main/task_sched.o(.*data*);
        BUILD_ROOT/src/main/multiarraylist.o(.*data*);
        BUILD_ROOT/src/math/mathutils.o(.*data*);
        BUILD_ROOT/src/usb/usb.o(.*data*);
        BUILD_ROOT/src/usb/debug.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(main);

    START_SEGMENT_AFTER(gfx, main)
    {
        BUILD_ROOT/src/gfx/gfx.o(.text*);
        BUILD_ROOT/src/gfx/gfx.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(gfx);

    START_SEGMENT_AFTER(ecs, gfx)
    {
        BUILD_ROOT/src/ecs/ecs.o(.text*);
        BUILD_ROOT/src/ecs/ecs.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(ecs);

    START_SEGMENT_AFTER(physics, ecs)
    {
        BUILD_ROOT/src/physics/collision.o(.text*);
        BUILD_ROOT/src/physics/traversal.o(.text*);
        BUILD_ROOT/src/physics/collision.o(.*data*);
        BUILD_ROOT/src/physics/traversal.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(physics);

    START_SEGMENT_AFTER(audio, physics)
    {
        BUILD_ROOT/src/audio/audio.o(.text*);
        BUILD_ROOT/src/audio/audio.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(audio);

    START_SEGMENT_AFTER(libgcc, audio)
    {
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.text*);
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(libgcc);

    START_SEGMENT_AFTER(libultra, libgcc)
    {
        SDK/ultra/usr/lib/LIBULTRA.a(.text*);
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.text*);
        SDK/ultra/usr/lib/LIBULTRA.a(.*data*);
        SDK/ultra/usr/lib/LIBULTRA.a(.scommon*);
        SDK/ultra/usr/lib/LIBULTRA.a(COMMON*);
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(libultra);

    START_SEGMENT_AFTER(ucode, libultra)
    {
        SDK/ultra/usr/lib/PR/rspboot.o(.text*);
        SDK/ultra/usr/lib/PR/gspF3DEX2.fifo.o(.text*);
        SDK/ultra/usr/lib/PR/gspL3DEX2.fifo.o(.text*);
        SDK/ultra/usr/lib/PR/gspS2DEX2.fifo.o(.text*);
        SDK/ultra/usr/lib/PR/rspboot.o(.*data*);
        SDK/ultra/usr/lib/PR/gspF3DEX2.fifo.o(.*data*);
        SDK/ultra/usr/lib/PR/gspL3DEX2.fifo.o(.*data*);
        SDK/ultra/usr/lib/PR/gspS2DEX2.fifo.o(.*data*);
        . = ALIGN(16);
    }
    END_SEGMENT(ucode);

    START_NOLOAD_AFTER(main, ucode)
    {
        BUILD_ROOT/src/main/main.o(.bss*);
        BUILD_ROOT/src/main/mem.o(.bss*);
        BUILD_ROOT/src/main/init.o(.bss*);
        BUILD_ROOT/src/main/input.o(.bss*);
        BUILD_ROOT/src/main/task_sched.o(.bss*);
        BUILD_ROOT/src/main/multiarraylist.o(.bss*);
        BUILD_ROOT/src/math/mathutils.o(.bss*);
        BUILD_ROOT/src/usb/usb.o(.bss*);
        BUILD_ROOT/src/usb/debug.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(main);

    START_NOLOAD_AFTER(gfx, main.noload)
    {
        BUILD_ROOT/src/gfx/gfx.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(gfx);

    START_NOLOAD_AFTER(ecs, gfx.noload)
    {
        BUILD_ROOT/src/ecs/ecs.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(ecs);

    START_NOLOAD_AFTER(physics, ecs.noload)
    {
        BUILD_ROOT/src/physics/collision.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(physics);

    START_NOLOAD_AFTER(audio, physics.noload)
    {
        BUILD_ROOT/src/audio/audio.o(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(audio);

    START_NOLOAD_AFTER(libgcc, audio.noload)
    {
        CHAIN/lib/gcc/mips64-elf/10.1.0/libgcc.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(libgcc);

    START_NOLOAD_AFTER(libultra, libgcc.noload)
    {
        SDK/ultra/usr/lib/LIBULTRA.a(.bss*);
        SDK/nintendo/n64kit/nustd/lib/libnustd.a(.bss*);
        . = ALIGN(16);
    }
    END_NOLOAD(libultra);

    memPoolStart = .;

    START_SEGMENT(intro, 0x04000000)
    {
        BUILD_ROOT/src/segments/intro.o(.*data*);
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