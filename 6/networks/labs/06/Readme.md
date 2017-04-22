![1.png](images/1.png)

```
Router#show ip protocols 
Routing Protocol is "rip"
Sending updates every 30 seconds, next due in 13 seconds
Invalid after 180 seconds, hold down 180, flushed after 240
Outgoing update filter list for all interfaces is not set
Incoming update filter list for all interfaces is not set
Redistributing: rip
Default version control: send version 2, receive 2
  Interface             Send  Recv  Triggered RIP  Key-chain
  FastEthernet0/0       2     2     
  Serial0/0             2     2     
  Serial0/1             2     2     
Automatic network summarization is in effect
Maximum path: 4
Routing for Networks:
	15.0.0.0
Passive Interface(s):
Routing Information Sources:
	Gateway         Distance      Last Update
	15.154.0.1           120      00:00:01
	15.155.0.2           120      00:00:07
Distance: (default is 120)

Router#show ip route
Codes: C - connected, S - static, I - IGRP, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2, E - EGP
       i - IS-IS, L1 - IS-IS level-1, L2 - IS-IS level-2, ia - IS-IS inter area
       * - candidate default, U - per-user static route, o - ODR
       P - periodic downloaded static route

Gateway of last resort is not set

     15.0.0.0/16 is subnetted, 6 subnets
R       15.151.0.0 [120/1] via 15.156.0.1, 00:00:19, Serial0/0
R       15.152.0.0 [120/1] via 15.155.0.1, 00:00:03, Serial0/1
C       15.153.0.0 is directly connected, FastEthernet0/0
R       15.154.0.0 [120/1] via 15.156.0.1, 00:00:19, Serial0/0
                   [120/1] via 15.155.0.1, 00:00:03, Serial0/1
C       15.155.0.0 is directly connected, Serial0/1
C       15.156.0.0 is directly connected, Serial0/0
```
