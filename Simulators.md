[Back to README](./README.md)

# RISC-V Simulators

I have not vetted all of these.

- [Dromajo](https://github.com/chipsalliance/dromajo)
    - "It is a RISC-V RV64GC emulator designed for RTL co-simulation."
    - This can be patched for instrumented execution of user mode software
    - See [link to progress how-to](./How-to.md). 

- [GEM5](https://github.com/gem5/gem5)
    - As of 2023.03.07 site claims priv instruction set is work in progress
    - Configurable system and processor uarch simulation
    - Inorder and out of order processor models
    - [Full system resources](http://resources.gem5.org/resources/riscv-fs) can boot busybox linux, time to boot {?}
    - Various levels of accuracy including functional and trace based
    - Claims co-simulation with SystemC 
        - (I tried briefly but never got this to work)
    - I have used GEM5 for ARM V8 no issues 
    - I have used this for RISC-V, 
        - As of 4Q22/1Q23 I found the RV32 support spotty. 
        - FIXME: revisit this for RV32I/G.

- [MARSS-RISCV](https://github.com/bucaps/marss-riscv)
    - cycle level models, in order, ooo
    - system level, incl. TLBs, cache, memory
    - Claims full system, linux kernel, boot, real time IO

- [Olympia](https://github.com/riscv-software-src/riscv-perf-model)
    - OOO RISC-V performance model - framework only
    - Trace based modeling - functional backend "in progress"
    - Requires Sparta/Sparcians tool set
    - 2/3/8 wide machines
    - [Presentation](https://www.youtube.com/watch?v=739lNpMWpQI)
    - [Issues/Status](https://github.com/riscv-software-src/riscv-perf-model/issues)

- [QEMU](https://github.com/qemu/qemu)
    - Board level simulation platform
    - [Docs](https://www.qemu.org/docs/master/system/target-riscv.html)
    - I have used this for ARM V7/V8 no issues within the intended purpose.

- [riscv-ovpsim](https://github.com/riscv-admin/riscv-ovpsim)
    - Open source from Imperas, has commerical option
    - Virtual platform style model, boots linux
    - [Github](https:://github.com/riscv-ovpsim)
    - ["Enhanced Version"](https://www.ovpworld.org/riscvOVPsimPlus)

- [Sail-RISC-V](https://github.com/riscv/sail-riscv)
    - according to RISC-V Intl. this is now the RISCV reference model
        - [See RISC-V org page](https://wiki.riscv.org/display/HOME/Emulators+and+Simulators)
    - Functional simulator (ISS)
    - Claims to boot BSD linux in 2 mins (300KIPS)

- [Sparta](https://github.com/sparcians/map)
    - This is not a simulator, but here because it is the basis of simulators.
    - Docs: https://sparcians/github.io/map/index.html
    - Api: https://sparcians/github.io/map/modeling.html

- [Spike](https://github.com/riscv/riscv-isa-sim)
    - canonical reference model, superceeded by a Sail implementation
    - Functional simulator (ISS)
    - SMP capable, in order
    - I have used this, for bare metal apps and with PK. 

