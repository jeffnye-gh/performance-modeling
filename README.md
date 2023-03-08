
 <!DOCTYPE html>
<html>
<head>
<title>Title of the document</title>
</head>

<body>
<H1> Modeling resources
mostly text files on modeling, some papers to share, etc

# RISCV Simulators and their properties

Terminology in the literature isnt very consistent, this is what I am using here. If this varies from accepted usage I'll update this.

I obtained some information below from this URL [wiki.riscv.org1](https://wiki.riscv.org/display/HOME/Emulators+and+Simulators)

Uarch terms:

* (FUNC) Functional Model:
    * correctness only, aka instruction set simulator

* (AT) Approximately Timed:
    * SystemC TLM term, fine grain transaction phases, not cycle accurate

* (LT) Loosely Timed:
    * SystemC TLM term, coarse grain transaction phases, not cycle accurate

* (CA) Cycle Accurate
    * Matches RTL without statistical estimation
    * In some cases some state is abstracted to improve simulation speed but cycle counts are accurate
* (CAX) Cycle Approximate :
    * Approximates RTL cycle counts
    * Gains speed through statistical or abstraction methods of modeling predicted cycle counts there is not always a sharp distinction between cycle approximate and accurate
* (IO)  In order, single issue
* (IOn)  In order, n-scalar
* (OO)  Out of order, always n-scalar

<table>
<tr><th>label<th>detail<th>uarch<th>impl<th>comment<th>url<th>license
<tr><td class="label">  spike
   <td class="uarch">   FUNC(ISS), IO
   <td class="impl">    c/c++
   <td class="comment"> ISS only, some memory, instrumentation vehicle
   <td class="url"> <a href="https://github.com/riscv/riscv-isa-sim">Spike</a>
   <td class="license"> <a href="https://github.com/riscv-software-src/riscv-isa-sim/blob/master/LICENSE">UC Regents</a>
<tr><td>QEMU
   <td class="uarch">   FUNC
   <td class="impl">    c/c++
   <td class="comment"> co-sim with non-std extensions, boots o/s
   <td class="url"> 
   <td class="license"> 
<tr><td>GEM5
   <td class="uarch">   FUNC or CAX, ISS, IO, OOO
   <td class="impl">    c/c++
   <td class="comment"> 
   <td class="url"> 
   <td class="license"> 
<tr><td>MARSS
   <td class="uarch">   
   <td class="impl">    
   <td class="comment"> 
   <td class="url"> 
   <td class="license"> 
</table>

# Tools for modeling

<table>
<tr><th>label<th>comment
<tr><td class="label">  SESC
   <td class="comment"> 
<tr><td class="label">  Sparts
   <td class="comment"> 
</table>

| label  | detail | uarch | impl  | comment                            | See |
| ------ | ------ | ----- | ----- | ---------------------------------- | --- | 
| Spike  | FUNC   | IO    | c/c++ | code is rough                      |  1  | 
| QEMU   | FUNC   | OO/IO | c/c++ | some experience w/   ARM           |  2  | 
| GEM5   | CAX    | OO/IO | c/c++ | supports cycle counts              |  3  | 
| MARSS  | CA     | IO    | c     | based on TinyEMU RiscV             |  4  | 
| SESC   | CA     | ?     | c++   | tool for arch exploration          |  5  |
| sparta | CA     | ?     | c++   | tool for arch explor. alt to SysC  |  6  |

</body>
</html> 
