#!/usr/bin/env python3
"""Static RE helper: find string xrefs + function disassembly in a PE (x64).
Usage:
  find_xrefs.py <dll> --strings            # list interesting string VAs
  find_xrefs.py <dll> --xref <substring>   # find code refs to strings containing substring
  find_xrefs.py <dll> --dis <va_hex> <n>   # disassemble n instrs at VA
"""
import sys, re, pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

def load(path):
    pe = pefile.PE(path)
    ib = pe.OPTIONAL_HEADER.ImageBase
    data = {s.Name.decode().rstrip('\0'): (s.VirtualAddress + ib, s.get_data())
            for s in pe.sections}
    return pe, ib, data

def find_strings(pe, ib, minlen=6):
    img = pe.get_memory_mapped_image()
    base = ib + pe.OPTIONAL_HEADER.BaseOfCode  # not exact start of image; use ib
    base = ib
    out = []
    # ascii
    for m in re.finditer(rb'[\x20-\x7e]{%d,}' % minlen, img):
        out.append((ib + m.start(), m.group().decode()))
    return out

def disasm_at(data, va, n=120):
    for name, (start, raw) in data.items():
        if start <= va < start + len(raw):
            off = va - start
            md = Cs(CS_ARCH_X86, CS_MODE_64)
            return list(md.disasm(raw[off:off+4096], va))[:n]
    return []

def main():
    path = sys.argv[1]
    pe, ib, data = load(path)
    mode = sys.argv[2] if len(sys.argv) > 2 else '--strings'
    if mode == '--strings':
        strs = find_strings(pe, ib)
        kw = sys.argv[3] if len(sys.argv) > 3 else ''
        for va, s in strs:
            if kw.lower() in s.lower():
                print(hex(va), repr(s[:120]))
    elif mode == '--xref':
        pat = sys.argv[3].encode()
        img = pe.get_memory_mapped_image()
        # locate string VAs
        vas = []
        for m in re.finditer(re.escape(pat), img, re.IGNORECASE):
            vas.append(ib + m.start())
        print('string VAs:', [hex(v) for v in vas])
        # linear sweep for rip-relative leas pointing at those VAs
        text_start, text_raw = data['.text']
        md = Cs(CS_ARCH_X86, CS_MODE_64)
        md.detail = False
        hits = []
        for ins in md.disasm(text_raw, text_start):
            if ins.mnemonic in ('lea', 'mov') and 'rip' in ins.op_str:
                m = re.search(r'\[rip \+ (0x[0-9a-f]+)\]|\[rip - (0x[0-9a-f]+)\]', ins.op_str)
                if m:
                    d = int(m.group(1), 16) if m.group(1) else -int(m.group(2), 16)
                    target = ins.address + ins.size + d
                    if any(abs(target - v) < 64 for v in vas):
                        hits.append((ins.address, ins.mnemonic, ins.op_str, hex(target)))
        for h in hits[:20]:
            print(h)

if __name__ == '__main__':
    main()
