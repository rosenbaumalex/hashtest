 
**Valid port range in this test resutls:**
1. Dst Port: 0x0400-0xFFFF (1024-65536)
2. Src Port: 0x8000-0xFFFF (when system choses for user), user could force bind to full range of 0x0400-0xFFFF

In order to match the <Src, DSt> ports of RDMA_CM into the GRH/IPv6 flow_label field (20 bits) we for loop on SrcPort range 0x0400-0xFFFF (~64000 values), and DsrPort range 0x8000-0xFFFF (~32000 values), and for each we checked the following hash funciton:
```
1. hash = Src * Dst
2. hash = Src * Dst; hash >>= 16; hash >>=8;
3. hash = Src * 31 + Dst

flow_label = hash * 0xFFFFFF;
```

We get 2G samples results, sorted into 2M buckets. An avarge bucket should hold 2K entries.

Below we present the flow_label spreading graph results for the 3 hash's:

**hash #1**

Non-Fold Multi(Src*Dst)  
In the graph below, highs are around 24K, which much higher then the expexted 2K entries per bucket.  

![Non-Fold Multi](https://github.com/rosenbaumalex/hashtest/blob/master/hash1_full_range.PNG)

**hash #2**

Folding Multi(Src*Dst)  
In the graph below, highs are around 20K, which higher then the expexted 2K entries per bucket.  

![Folding Multi](https://github.com/rosenbaumalex/hashtest/blob/master/hash2_full_range.PNG)


**hash #3**

Src*31 + Dst  
In the graph below, high is 4K, which not too far then the expexted 2K entries per bucket.  

![Non-Simetric](https://github.com/rosenbaumalex/hashtest/blob/master/hash3_full_range.PNG)
