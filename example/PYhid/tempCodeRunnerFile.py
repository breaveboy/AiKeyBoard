while True:
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[255,0,0])
    dev.write(packet)
    time.sleep(1)
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[0,255,0])
    dev.write(packet)
    time.sleep(1)
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[0,0,255])
    dev.write(packet)