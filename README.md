 
Valid Port Range:
1. Dst Port: 0x0400-0xFFFF (1024-65536)
2. Src Port: 0x8000-0xFFFF (when system choses for user), user can force bind to full range of 0x0400-0xFFFF

In order to match the Src * DSt ports of RDMA_CM into the GRH/IPv6 flow_label field we checked the following hash funciton:
1. hash = Src * Dst
2. hash = Src * Dst; hash >>= 16; hash >>=8;
3. hash = Src * 31 + Dst

flow_label = hash * 0xFFFFFF;

below we present the flow_label spreading graph results for the 3 hash's: