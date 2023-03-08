# FOSS modeling tools

## Sparcians 

[Sparcians](https://github.com/sparcians)

These are the packages I'm interested in. Not sure why they have a copy of spike, this is not the official repo for riscv-isa-sim.

The organization and naming is inconsistent.

The interesting tools are Olympia, STF and the pipeview known variously as Helios/PipeViewer/pipe_view and argos.py

<ul>
  <li>Map  - modeling architecture platform
    <ul> <li> This is the umbrella </ul>
  <li> STF - simulation tracing format
    <ul> <li> There is a library and tools </ul>
  <li>Olympia
    <ul><li>OOO trace driven perf model</ul>
  <li>riscv-isa-sim
    <ul>
        <li>This is spike et al
        <li>I do not know why they have their own copy
    </ul>
  <li>Helios/PipeViewer/pipe_view/argos.py
    <ul><li> A pipeline viewer using STF</ul>
  <li> MAP/Docker</li>
    <ul>
      <li>This may be the way to go for MAP. 
      <li> Installing MAP has been a larger chore than expected
    </ul>
</ul>

## BOOM/CHIPS Alliance/Chip Yard

I'm grouping these together, but structure and separation isnt always clear. 

[ChipsAlliance](https://github.com/chipsalliance)

[RISCV-BOOM](https://github.com/riscv-boom)

[ChipYard](https://github.com/ucb-bar/chipyard)

Dromajo and BOOM are interesting.

<ul>
  <li> Dromajo
    <ul>
      <li> A model suitable for co-simulation with RTL.
      <li> Supports RV64VGC, unclear
      <li> With a patch provided by Sparcians this cooperates with
      <li> Co-operates with Olympia and the Sparcians/Map tools
    </ul>
  <li> BOOM aka riscv-boom
    <ul>
      <li> OOO machine, implemented in Chisel
      <li> renders to Verilog thru <b>firrtl</b>
    </ul>
</ul>

## RISC-V Software

[RISC-V Intnl Repos](https://github.com/riscv-software-src)

[Spike](https://github.com/riscv-software-src/riscv-isa-sim)

[ProxyKernel](https://github.com/riscv-software-src/riscv-pk)

These are well known, here for reference.


# Install Docker on Ubuntu

The MAP tools are problematic even on Ubuntu. Argos' log file parser uses wx widgets which has a painful set of pre-reqs.

Docker may be the way to go if we use these tools.

I'll remove the advisory when I'm happy with the install. I'll add a RHEL version when I have an RHEL instance to play with.

<b> This has not been tested, if in doubt about your ability to recover from this, dont do it at all.</b>

## Remove previous installations of docker, if any

<ul>
  <li> sudo apt remove docker-desktop
  <li> rm -r $HOME/.docker/desktop
  <li> sudo rm /usr/local/bin/com.docker.cli
  <li> sudo apt purge docker-desktop
  <li> sudo apt update
  <li> sudo apt upgrade
</ul>

### Update/install collateral
<ul>
  <li> sudo apt install ca-certificates curl gnupg lsb-release
  <li> sudo mkdir -m 0755 -p /etc/apt/keyrings
  <li> curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
  <li> echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
  <li> sudo apt-get update
    <ul>
      <li> If you get an GPG error with apt update do this:
        <ul>
          <li> sudo chmod a+r /etc/apt/keyrings/docker.gpg
          <li> sudo apt-get update
        </ul>
    </ul>
 </ul>

### Install latest docker
<ul>
  <li> sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  <li> sudo docker run hello-world
</ul>

### Test docker
<ul>
  <li> sudo docker run hello-world
</ul>

You should see these lines

...snip...

Hello from Docker!

This message shows that your installation appears to be working correctly.

...snip...

<!--
# Build Dromajo

### FIXME 

## 1.2 Build bootable image

### 1.2.1 Download buildroot image

cd /home/jeff/Development/riscv-perf-model

mkdir buildroot; cd buildroot

wget https://github.com/buildroot/buildroot/archive/2020.05.1.tar.gz

## 1.3 Instrument test case
Add START_TRACE/STOP_TRACE to source

See /home/jeff/Development/riscv-perf-model/traces/stf_trace_gen/qsort

make

## 1.4 

## 1.1 Location

/home/jeff/Development/riscv-perf-model/traces/stf_trace_gen/dromajo/build

# 100. Example instrumented App - Requires Bootimg

```
qsort.c
    #include "trace_macros.h"
    #include <stdio.h>
    #include <stdlib.h>

    int compare (const void * a, const void * b)
    {
      int data1 = *(int *)a, data2 = *(int *)b;
      if(data1 < data2) // a < b
        return -1;
      else if(data1 == data2) // a == b
        return 0;
      else
        return 1;  // a > b
    }

    main ()
    {
      START_TRACE;
      int i = 0, numbers = 5;
      int data[] = {3, 40, 2, 1, 10};
      qsort (data, numbers, sizeof(int), compare);
      for (i=0; i < numbers; i++)
         printf ("%d ", data[i]);
      STOP_TRACE;

      return 0;
    }

Makefile

.PHONY: default clean
CC = /mnt/usr/local/riscv64-unknown-elf/bin/riscv64-unknown-elf-gcc
ARCH=-march=rv64g -mabi=lp64d
OPT = -O0

TGT = qsort
SRC = qsort.c
OBJ = qsort.o
DEP = qsort.d
LIBS=
INC = -I..

CFLAGS = -MMD -MP $(ARCH) $(OPT) $(INC)
LFLAGS =
default: $(TGT)
%.o: %.c
  $(CC) -c $(CFLAGS) -o $@ $<
$(TGT): $(OBJ)
  $(CC) -o $@ $^ $(LIBS)
clean:
  -rm -f *.o *.d $(TGT)


```

mkdir myapp; cd myapp
cat myapp.c << "/home/jeff/Development/riscv-perf-model

## Boot linux

-->
