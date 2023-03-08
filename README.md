# Performance modeling resources

## [How-to pages](./how-to.md)

Notes, arcane instructions, build/install recipes 

## [Simulators](XYZ) <!-- (./simulators.md) -->

More or less alphabetical

- [Dromajo](https://github.com/chipsalliance/dromajo)
    - "It is a RISC-V RV64GC emulator designed for RTL co-simulation."
    - This can be patched for instrumented execution of user mode software
    - See the Sparcians resource page under Modeling Tools

- [GEM5](https://github.com/gem5/gem5)
    - As of 2023.03.07 site claims priv instruction set is work in progress
    - Configurable system and processor uarch simulation
    - Inorder and out of order processor models
    - [Full system resources](http://resources.gem5.org/resources/riscv-fs) can boot busybox linux, time to boot {?}
    - Various levels of accuracy including functional and trace based
    - Claims co-simulation with SystemC 
        - (I tried briefly but never got this to work)

- [MARSS-RISCV](https://github.com/bucaps/marss-riscv)
    - cycle level models, in order, ooo
    - system level, incl. TLBs, cache, memory
    - Claims full system, linux kernel, boot, real time IO

- [Olympia](https://github.com/riscv-software-src/riscv-perf-model)
    - OOO RISC-V performance model - renaming not implemented
    - Trace based modeling - functional backend "in progress"
    - Requires Sparta/Sparcians tool set

- [QEMU](https://github.com/qemu/qemu)
    - Board level simulation platform
    - [Docs](https://www.qemu.org/docs/master/system/target-riscv.html)

- [riscv-ovpsim](https://github.com/riscv-admin/riscv-ovpsim)
    - Open source from Imperas, has commerical option
    - Virtual platform style model, boots linux

- [Sail-RISC-V](https://github.com/riscv/sail-riscv)
    - according to RISC-V Intl. this is now the RISCV reference model
        - [See RISC-V org page](https://wiki.riscv.org/display/HOME/Emulators+and+Simulators)
    - Functional simulator (ISS)
    - Claims to boot BSD linux in 2 mins (300KIPS)

- [Spike](https://github.com/riscv/riscv-isa-sim)
    - canonical reference model, superceeded by a Sail implementation
    - Functional simulator (ISS)
    - SMP capable, in order



## Resources <!-- (./modelingtools.md) -->

- [Map](XYZ)
    - FIXME
    - Docker files: 

- [BOOM](XYZ)
    - FIXME

- [ChipYard](XYZ)
    - FIXME

- [ChipsAlliance](XYZ)
    - FIXME

- [Embercosm](XYZ)
    - FIXME

- [STF](XYZ)
    - FIXME

- [Sparta](XYZ)
    - FIXME

- [Mavis](https://github.com/sparcians/mavis)
    - disassembler, etc
    - FIXME

- [Verilator](https://www.veripool.org/verilator/)
    - FIXME

- [Ripes](https://github.com/mortbopet/Ripes/tree/master/src)
    - FIXME

- [riscvp](https://github.com/agra-uni-bremen/riscv-vp)
    - FIXME

- [Helios/Argos](XYZ)
    - FIXME

- [SystemC](https://www.accellera.org/downloads/standards/systemc)
    - 2.3.4 is current version


