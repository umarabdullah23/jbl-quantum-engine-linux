#!/usr/bin/env python3
"""Minimal USBPcap pcapng parser: extract HID control (SET/GET_REPORT) traffic per file."""
import struct, sys, glob

def parse(path):
    out = []
    data = open(path, 'rb').read()
    # walk pcapng blocks
    off = 0
    endian = '<'
    while off < len(data) - 12:
        btype, blen = struct.unpack_from(endian + 'II', data, off)
        if blen < 12 or off + blen > len(data):
            break
        if btype == 0x0A0D0D0A:
            bom = data[off+8:off+12]
            endian = '<' if bom == b'\x4d\x3c\x2b\x1a' else '>'
        elif btype == 6:  # Enhanced Packet Block
            iface, ts_h, ts_l, caplen, origlen = struct.unpack_from(endian + 'IIIII', data, off + 8)
            pkt = data[off+28:off+28+caplen]
            out.append(pkt)
        off += blen
    return out

def usbpcap_headers(pkt):
    if len(pkt) < 27:
        return None
    headerLen, irpId, status, function, info, bus, dev, endpoint, transfer, dataLen = \
        struct.unpack_from('<HQIHBHHBBI', pkt, 0)
    return dict(headerLen=headerLen, irpId=irpId, function=function, info=info,
                bus=bus, dev=dev, endpoint=endpoint, transfer=transfer, dataLen=dataLen)

def main():
    for f in sorted(glob.glob(sys.argv[1] if len(sys.argv) > 1 else '*.pcapng')):
        pkts = parse(f)
        events = []
        for p in pkts:
            h = usbpcap_headers(p)
            if not h:
                continue
            if h['transfer'] != 2:  # control
                continue
            body = p[h['headerLen']:]
            if h['function'] == 0x0005 and len(body) >= 8:  # submit: setup packet present
                bmRequestType, bRequest, wValue, wIndex, wLength = struct.unpack_from('<BBHHH', body, 0)
                payload = body[8:]
                # HID class requests: 0x21 = host->device class interface
                if (bmRequestType & 0x60) == 0x20 and len(payload):
                    events.append(('SETUP', f'bmReq={bmRequestType:02x} bReq={bRequest:02x} wVal={wValue:04x} wIdx={wIndex:04x}',
                                   payload.hex()))
            elif h['function'] == 0x0006 and len(body) > 0:
                pass
        # dedupe consecutive
        seen = []
        for e in events:
            if e not in seen:
                seen.append(e)
        print(f'== {f}: {len(pkts)} pkts, {len(events)} HID class transfers, {len(seen)} unique')
        for e in seen[:12]:
            print('   ', e[0], e[1], 'data:', e[2][:64])

if __name__ == '__main__':
    main()
