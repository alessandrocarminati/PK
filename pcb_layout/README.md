#Password keeper PCB
The current repository implements the following schema

![NET](/res/net.png)

Because it is printed by hand, an effort is made to keep it single face.

Here the routed PCB

![LAYOUT](/res/pcb.png)

# BOM
| ID | Name     | Package      | Qty | Designation
|----|----------|--------------|-----|-------------
|  1 | IC1      | DIL16        |   1 | 74HC595N
|  2 | IC2      | DIL08        |   1 | ATtiny85-20PU
|  3 | IC3      | DIL14        |   1 | CD40106BCN
|  4 | R1, R2   | 0207/10      |   2 | 68 $\Omega$
|  5 | R3       | 0207/10      |   1 | 33k $\Omega$
|  6 | R4       | 0207/10      |   1 | 220k $\Omega$
|  7 | R5       | 0207/10      |   1 | 560 $\Omega$ 
|  8 | R6, R7   | 0207/10      |   2 | 10k $\Omega$
|  9 | R10      | 0207/10      |   1 | 1.5k $\Omega$ 
| 10 | R11      | 0207/10      |   1 | 470 $\Omega$ 
| 11 | D1       | DO35         |   1 | 1N581
| 12 | D2, D3   | DO35         |   2 | 1N5227B-TR
| 13 | LED1     | LED5MM       |   1 | Power
| 14 | LED2     | LED5MM       |   1 | ACT
| 15 | C1       | E2-5         |   1 | 10$\mu$F
| 16 | C2, C3   | C050-024X044 |   2 | 2.2nF
| 17 | J1       | 2X07_LOCK    |   1 | Display Connector
| 18 | JP3      | USB-B-PTH    |   1 | USB-B
| 19 | JP2      | 1X02_LOCK    |   1 | Reset
| 20 | JP4      | 1X02_LOCK    |   1 | Button1
| 21 | JP5      | 1X02_LOCK    |   1 | Button2
| 22 | DISPLAY  | NA           |   1 | LM16211

