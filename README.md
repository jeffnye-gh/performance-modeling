# Performance modeling resources

## [How-to pages](./how-to.md)

Notes, arcane instructions, build/install recipes 

## [RISC-V Simulators](XYZ) <!-- (./simulators.md) -->

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

## Resources <!-- (./modelingresourcess.md) -->

- [BOOM](XYZ)
    - Berkeley Out of Order Machine
    - FIXME

- [ChipsAlliance](XYZ)
    - FIXME

- [ChipYard](XYZ)
    - FIXME

- [Embercosm](XYZ)
    - FIXME

- [Ripes](https://github.com/mortbopet/Ripes/tree/master/src)
    - FIXME

- [riscvp](https://github.com/agra-uni-bremen/riscv-vp)
    - FIXME

- [(r-s-s) riscv-software-src](https://github.com/riscv-software-src)
    - Umbrella repo maintained by RISC-V International (RVI)
    - Olympia is now part of this
 
- [r-s-s/Olympia](https://github.com/riscv-software-src/riscv-perf-model)
    - Olympia was part of Sparcians, new repo location
    - C++ performance model for example Out-of-order RISC-V
    - Trace driven, uses JSON or STF input
    - STF input can be generated by patching Dromajo

- [r-s-s/riscv-isa-sim](https://github.com/riscv-software-src/riscv-isa-sim)
    - Spike: official repo
    - Functional model, previously the golden reference
    - RVI says now replaced by Sail version

- [r-s-s/pk](https://github.com/riscv-software-src/riscv-pk)
    - Pico-Kernel
    - Provides minimal kernel for executing user mode code

- [r-s-s/riscv-tests](https://github.com/riscv-software-src/riscv-tests)
    - RVI compliance tests, asm fragments

- [r-s-s/semihosting](https://github.com/riscv-software-src/riscv-semihosting)
    - Semi-hosting - simulator to host communication
    - C/C++ std library access to native code execution

- [Sparcians](https://github.com/sparcians)
    - UC-Berkeley umbrella repo
    - "organization of modeling/simulation software/frameworks"

- [Sparcians/Map](https://github.com/sparcians/map)
    - Sparcians/Modeling Architecture Platform
    - Includes sub-projects: Sparta, Helios, etc

- [Sparcians/Map-Docker](https://github.com/sparcians/map-docker)
    - Docker files/instructions for Sparcians/Map
    - This is used in the how-to section above

- [Sparcians/Mavis](https://github.com/sparcians/mavis)
    - RISC-V instruction decoding/disassembly
    - Custom instruction creation support

- Sparcians/STF
    - Sparcians/Simple Tracing Format Specification
    - Binary file format for instruction traces, ISA generalized
    - [STF Lib](https://github.com/sparcians/stf_lib)
    - [STF Spec](https://github.com/sparcians/stf_spec)
    - [STF Tools](https://github.com/sparcians/stf_tools)

- [SystemC](https://www.accellera.org/downloads/standards/systemc)
    - 2.3.4 is current version

- [Verilator](https://www.veripool.org/verilator/)
    - FOSS System Verilog simulator
    - Compiles Verilog to multi-threaded C++ or SystemC


