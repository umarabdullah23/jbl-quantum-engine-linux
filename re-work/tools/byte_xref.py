#!/usr/bin/env python3
"""Byte-pattern scan for rip-relative references to a VA (robust to desync)."""
import sys, re, pefile

def load(path):
    pe = pefile.PE(path)
    ib = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    return pe, ib, img

def main():
    path = sys.argv[1]
    target_va = int(sys.argv[2], 16)
    pe, ib, img = load(path)
    hits = []
    # any instruction ending with disp32 rip-relative: last 4 bytes before end = disp
    # scan for lea: 48 8D /r  and mov: 48 8B /r and 4C 8D etc.
    for i in range(len(img) - 7):
        b0, b1, b2 = img[i], img[i+1], img[i+2]
        # REX.W (0x48-0x4f) + 0x8D/0x8B + modrm with mod=00 rm=101 (rip-relative)
        if 0x48 <= b0 <= 0x4f and b1 in (0x8D, 0x8B) and (b2 & 0xC7) == 0x05:
            disp = int.from_bytes(img[i+3:i+7], 'little', signed=True)
            va = ib + i
            target = va + 7 + disp
            if target == target_va:
                hits.append(va)
    print('refs to', hex(target_va), ':', [hex(h) for h in hits])

if __name__ == '__main__':
    main()
