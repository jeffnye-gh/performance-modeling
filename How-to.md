[Back to README](./README.md)

# How-To Instructions

WORK IN PROGRESS. THIS IS A CHECKPOINT OF ACTIVE WORK.

I made corrections to the source package files to get these to compile
and run Ubuntu 22, GCC-11. You need sudo for this.

<i>
If you are evaluating a design environment most if not all issues will be
exposed upto, and  including the Boot linux step. The boot linux step, in
particular the buildroot sub-steps will expose permissions issues.
</i>
<p><p>
<i>
From 'Install Docker' on, the instructions are important but it's unlikely 
they will expose more issues in the design environment.
</i>

-------------------------------------------
# TOC

1. [Assumed local environment variables](#assumed-local-environment-variables)

1. [Paths to original README files (incomplete)](#paths-to-original-readme-files-incomplete)

1. [Install riscv gnu tool chain](#install-riscv-gnu-tool-chain)

1. [Install Miniconda](#install-miniconda)

1. [Install Map Sparta](#install-map-sparta)

1. [Install Map Argos](#install-map-argos)

1. [Install riscv-perf-model](#install-riscv-perf-model)

1. [Using pipeline data views](#using-pipeline-data-views)

1. [Setup Dromajo for tracing](#setup-dromajo-for-tracing)

1. [Boot linux on Dromajo](#boot-linux-on-dromajo)

1. [Install docker](#install-docker)

1. [Install Si-Five Tools](#install-si-five-tools)

<!--
1. [Install Si-Five Freedom sdk](#install-si-five-freedom-sdk)
-->
-------------------------------------------

# Assumed local environment variables

Bash environment variables defined for clarity. Not all need to be in your
env.

Except: I assume $RV_GNU_TOOLS/bin is in your path for these instructions.


# Prep

Create a directory for the source root of these packages. Example

- TOP
    - This var points to where all repo's will live, cd/mkdir where you want the root of the tree to be, in this case /home/$USER/Development. Also create a temp directory for wget (if needed).
        - cd; mkdir -p Development
        - cd Development
        - mkdir -p Downloads
    - <b>export TOP=\`pwd\`</b>
     
- WGETTMP
    - Some packages require manual download using wget.
    - This a temporary directory for that purpose.
    - <b>export WGETTMP=$TOP/Downloads</b>

- PATCHES
    - A directory with pre-modified source and patch files
    - <b>export PATCHES=$TOP/performance-modeling/patches</b>
<!--    - <b>export PATCHES=/home/jeff/Development/gitbox/github/performance-modeling/patches</b> -->

- MAP
    - This var points to the Sparcians/Map repo copy
    - <b>export MAP=$TOP/map</b>

- OLYMPIA
    - This var points to the riscv-perf-model (aka Olympia) repo copy
    - <b>export OLYMPIA=$TOP/riscv-perf-model</b>

- RV_TOOLS_SRC
    - This var points to the tool chain source directory
    - <b>export RV_TOOLS_SRC=$TOP/riscv-gnu-toolchain</b>
 
- RV_GNU_TOOLS
    - This var points to the GNU tool chain install directory. 
    - <b>export RV_GNU_TOOLS=$TOP/riscv-tools</b>

- DROMAJO
    - This var points to the dromajo under riscv-perf-model 
    - <b>export DROMAJO=$TOP/riscv-perf-model/traces/stf_trace_gen/dromajo</b>

----------------------------------------------------------
# Paths to original README files (incomplete)

FIXME: this will hold the URL's of the original README.md files

----------------------------------------------------------
# Install riscv gnu tool chain

They say you need 6.65GB of space.

## Pre-req and clone

```
  sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build

  git clone https://github.com/riscv/riscv-gnu-toolchain
  cd riscv-gnu-toolchain   (aka cd $RV_TOOLS_SRC)
  mkdir -p $RV_GNU_TOOLS   (the install path)
```

## Configure, make and install

Install path will be $RV_GNU_TOOLS.

```
  cd $RV_TOOLS_SRC
  ./configure --prefix=$RV_GNU_TOOLS --enable-multilib
  make -j4 linux

```
  

----------------------------------------------------------
# Install Miniconda

Miniconda package manager is used by Sparcians.

In accepting the license:

- I am using the default install location

- I am allowing the installer to run conda init


The license instructions tell you how to disable miniconda activation at startup

- conda config --set auto_activate_base false

- I am not executing this command


```
cd $WGETTMP
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh ./Minconda3-latest-Linux-x86_64.sh
```
<i>open new terminal or reload your environment</i>

----------------------------------------------------------
# Install Map Sparta

## Pre-reqs

- Install Miniconda - see above
- Open a new terminal

## Install the collateral for Ubuntu 22

There might be bugs in this. I do not have a virgin Ubuntu, there might be missing packages not listed in the documentation, some of these packages may not be needed or have the wrong names.

```
    sudo apt install cmake sqlite doxygen (no equiv: hdf5 yaml-cpp rapidJson xz)
```

- The names change for Unbuntu (from Centos) so:

```
    sudo apt install hdf5-tools h5utils
    sudo apt install libyaml-cpp-dev
    sudo apt install rapidjson-dev
    sudo apt install xz-utils
```

## Clone the repo

```
    cd $TOP
    git clone https://github.com/sparcians/map.git
    cd $MAP/sparta
```

## Edit the source files (for Olympia)


<b>FIXME: Create actual patch files, for now copy the pre-edited files</b>

If you are building Olympia (riscv-perf-model) you copy over two files.

```
    cp $PATCHES/TreeNodeExtensions.cpp $MAP/sparta/src/TreeNodeExtensions.cpp
    cp $PATCHES/TreeNodeExtensions.hpp $MAP/sparta/sparta/simulation/TreeNodeExtensions.hpp
```

<!-- old instructions
- Edit:
    - Change $MAP/sparta/src/TreeNodeExtensions.cpp
    - Roughly line 72, comment out the destructor

```
    //ExtensionsParamsOnly::~ExtensionsParamsOnly()
    //{
    //}
```
- Edit:
    - Change $MAP/sparta/sparta/simulation/TreeNodeExtensions.hpp
    - Roughly line 27, define the destructor, (add the braces)

```
    virtual ~ExtensionsParamsOnly() {}
```
-->

## Build Sparta

 See the apt install for support packages above in Pre-reqs

```
    cd $MAP/sparta
    mkdir release; cd release
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j4
```

TODO: idk-why, make -j16 actually crashes my gnome terminal under NoMachine.

---------

# Install Map Argos

Argos is a python pipe viewer for trace based performance models. It is variously named, even within the repo, as Helio, Argos, pipeViewer, or pipe_view. The python script is argos.py

The build directory is $MAP/helios/pipeViewer.


## Pre-reqs

There is likely cleanup possible in this list, but this is what I did. I'll simplify this once I have a fresh environment.

- Install Miniconda - see above
- Install Map/Sparta - see above

## Install the Map Argos collateral

This tool has a stupidly long dependency chain. wxpython-tools was called python-wxtools. attrdict3 replaces attrdict.

```
    sudo apt install wxpython-tools
    sudo apt install libgtk-3-dev
    pip3 install attrdict3
    pip3 install wxPython
    pip3 install pyyaml
```

## Install the Map Argos conda packages

- Start a terminal with miniconda activated. See above.    
    - The prompt will look like (base):
```
   (base) jeff@reynaldo:~/Development:
```

- Install the conda packages, activate the environment

```
    cd $MAP
    conda install -c conda-forge jq
    conda install -c conda-forge yq
    ./scripts/create_conda_env.sh sparta dev
    conda activate sparta
    cd $(git rev-parse --show-toplevel);
    mkdir -p release; cd release
```


## Build Map/Argos/PipeView (Helios)

Your terminal should have an active sparta/conda dev environment. See above.

```
    cd $MAP
    mkdir -p release; cd release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4
```


---------

# Install riscv-perf-model

riscv-perf-model aka Olympia. Olympia is a trace driven OOO performance model. 

It appears to be incomplete, there is an advisory that renaming does not work. It does have some interesting capabilities in terms of trace input formats in [STF](https://github.com/sparcians/stf_spec) and [JSON](https://github.com/riscv-software-src/riscv-perf-model/tree/master/traces#json-inputs).

## Pre-reqs

- Install Miniconda - see above
- Install Sparta - see above

## Clone the repo

There are errors in map/Sparta source files when compiling for Olympia. Make the source file changes described above (TreeNodeExtensions.hpp/cpp).

There is also an error in Dispatch.hpp, see below.

```
    cd $TOP
    git clone --recursive git@github.com:riscv-software-src/riscv-perf-model.git
```

## Patch/modify the repo

Dispatch.hpp has an error. Copy the edited file from the $PATCHES directory.

FIXME: Create actual patch files, for now copy the pre-edited file over.

```
    cd $OLYMPIA
    cp $PATCHES/Dispatch.hpp core/Dispatch.hpp
```


<!--
- Edit core/Dispatch.hpp
- change:

```
    #include "test/ContextCounter/WeightedContextCounter.hpp"
```
- to: 

```
    #include "sparta/statistics/WeightedContextCounter.hpp"
```
-->

## Build the simulator

```
    cd $OLYMPIA
    mkdir -p release; cd release
    cmake .. -DCMAKE_BUILD_TYPE=Release -DSPARTA_BASE=$MAP/sparta
```

### Select build level

Choose what to build. I chose just olympia.

```
    cd $OLYMPIA
    mkdir -p release; cd release
    make -j4     # build everything
    make olympia # build the simulator only
    make regress 
```

---------

# Using pipeline data views

## Prereqs

This assumes you have followed the instructions above for these steps.

- Install Miniconda on Ubuntu 22
- Install Map/Sparta on Ubuntu 22
- Install Map/Argos on Ubuntu 22
- FIXME: it's possible you also need: 
    - Install riscv-perf-model on Ubuntu 22

## Create example core model

```
    cd $MAP/sparta/release/example/CoreModel
    make
```

## Generate pipeline database

```
    cd $MAP/sparta/release/example/CoreModel
    ./sparta_core_example -i 1000 -z pipeout_
```

## View pipe output

### Pipeline data in single cycle view

```
    python3 ${MAP}/helios/pipeViewer/pipe_view/argos.py --database pipeout_ --layout-file cpu_layout.alf
```

### Pipeline data in multi-cycle view

```
    python3 ${MAP}/helios/pipeViewer/pipe_view/argos.py --database pipeout_ --layout-file cpu_layout.alf
```

------------------------------------------------------------------------
# Setup Dromajo for tracing


## Clone and patch dromajo

FIXME: I need to re-create the patch, there was a fix for console io performance in dromajo, so the checksum below is no longer used, and I need to verify that the patch still works

A patch is supplied to modify Dromajo to generate STF traces. These steps clone the repo, checkout the known compatible commit and patch the source.

```
    cd $OLYMPIA/traces/stf_trace_gen
    git clone https://github.com/chipsalliance/dromajo
    cd dromajo
    <FIXME:> git checkout 86125b31
    <FIXME:> git apply ../dromajo_stf_lib.patch
    ln -s ../../../stf_lib
```

## Correct cmake files 

stf_lib/stf-config.cmake and Dromajo CMakeLists must be edited for correct compile. 


```
    cd $DROMAJO
    vi $OLYMPIA/stf_lib/cmake/stf-config.cmake
    change line ~14 to (remove _GLOBAL):
        set_target_properties(Threads::Threads PROPERTIES IMPORTED TRUE)

    vi ./CMakeLists.txt
    change line ~53 to (change std to ++17)
        -std=c++17
```

## Build dromajo

```
    cd $DROMAJO
    mkdir -p build; cd build
    cmake ..
    make -j4
```

## Verify patch

Check if patch worked, dromajo should have the --stf_trace option

```
    cd $DROMAJO/build
    ./dromajo | grep stf_trace
    console:
        --stf_trace <filename>  Dump an STF trace
```

------------------------------------------------------------------------
# Boot Linux on Dromajo

## Create buildroot image

The make of build root downloads some files. Some of these files need
a patch so make is called multiple times.

Prepatched files are provided to copy over the files with issues.
FIXME: ADD THESE FILES TO REPO AND INSTRUCTIONS TO RETRIEVE THEM.

```
    cd $DROMAJO
    wget https://github.com/buildroot/buildroot/archive/2020.05.1.tar.gz
    tar xf 2020.05.1.tar.gz
    cp run/config-buildroot-2020.05.1 buildroot-2020.05.1/.config
    make -C buildroot-2020.05.1
    (this will fail)
    cp $PATCHES/c-stack.c ./buildroot-2020.05.1/output/build/host-m4-1.4.18/lib/c-stack.c
    make -C buildroot-2020.05.1
    (this will fail)
    cp $PATCHES/libfakeroot.c ./buildroot-2020.05.1/output/build/host-fakeroot-1.20.2/libfakeroot.c
    sudo make -C buildroot-2020.05.1
    (this is expected to finish without error)
```

## Download and compile kernel

You must have previously installed the riscv tool chain.
See [Install riscv gnu tool Chain](#install-riscv-gnu-tool-chain)

```
    cd $DROMAJO
    export CROSS_COMPILE=riscv64-unknown-linux-gnu-
    wget -nc https://git.kernel.org/torvalds/t/linux-5.8-rc4.tar.gz
    tar -xf linux-5.8-rc4.tar.gz
    make -C linux-5.8-rc4 ARCH=riscv defconfig
    make -C linux-5.8-rc4 ARCH=riscv -j16
```

## Download and compile OpenSBI

```
    cd $DROMAJO
    export CROSS_COMPILE=riscv64-unknown-linux-gnu-
    git clone https://github.com/riscv/opensbi.git
    cd opensbi
    git checkout tags/v0.8 -b temp2
    # works too: git checkout 7be75f519f7705367030258c4410d9ff9ea24a6f -b temp
    make PLATFORM=generic
    cd ..
```

## Boot linux

```
    cd $DROMAJO
    cp buildroot-2020.05.1/output/images/rootfs.cpio ./run
    cp linux-5.8-rc4/arch/riscv/boot/Image ./run
    cp opensbi/build/platform/generic/firmware/fw_jump.bin ./run
    cd run
    ../build/dromajo boot.cfg
```

------------------------------------------------------------------------
# Install docker

## Remove previous install

Remove any test docker support or images as necessary.

```
    sudo apt remove docker-desktop
    rm -r $HOME/.docker/desktop
    sudo rm /usr/local/bin/com.docker.cli
    sudo apt purge docker-desktop
    sudo apt update
    sudo apt upgrade
```

## Update and install collateral

Install the support packages as needed.

```
    sudo apt install ca-certificates curl gnupg lsb-release
    sudo mkdir -m 0755 -p /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    sudo apt-get update
```

If you get an GPG error with apt update:

```
    sudo chmod a+r /etc/apt/keyrings/docker.gpg
    sudo apt-get update
```

## Install latest docker

Actual docker installation

```
    sudo apt install docker-ce docker-ce-cli containerd.io 
    sudo apt docker-buildx-plugin docker-compose-plugin
```

## Hello world test

Run the install check
```
    sudo docker run hello-world
```

You should see this in the console:
```
    Hello from Docker!

    This message shows that your installation appears to be working correctly.
```

<!--
------------------------------------------------------------------------
# Install Si-Five Tools
FIXME: 2023.03.21 this is broken under Ubuntu with some obscure tex2div problem.  Moving on to other repos

# Instructions for installing/building these Si-Five tools:

- SiFive Freedom RISC-V Tools for Embedded Development
  - "At SiFive we've been distributing binary release packages of the embedded development tools that target our Freedom RISC-V platforms. This repository contains the scripts we use to build these tools."


## SiFive Freedom RISC-V Tools for Embedded Development

So far these instructions are the same as what is [here](https://github.com/sifive/freedom-tools). I'm duplicating for now because I expect to have to modify the instructions for our design environment. If that turns out to be the case I'll just point to the known good instructions on github.

This package contains:

    - riscv64-unknown-elf-*
    - riscv-openocd-*)
    - riscv-qemu-*
    - sdk-utilities-*
    - trace-decoder-*
    - xc3sprog-*


### Pre-reqs - Ubuntu

The pre-reqs listed, I have not tried to filter this huge list. The minqw step
reports 1GB of disk required.

FIXME: Why does this need mingw? Try this again without.

```
    sudo apt install cmake autoconf automake autotools-dev curl 
    sudo apt install libmpc-dev libmpfr-dev libgmp-dev gawk build-essential
    sudo apt install bison flex texinfo gperf patchutils bc zlib1g-dev
    sudo apt install libexpat-dev libtool pkg-config mingw-w64
    sudo apt install mingw-w64-tools texlive zip python-dev gettext
    sudo apt install libglib2.0-dev libpixman-1-dev swig ninja-build python3
    sudo pip3 install meson
```

### Pre-reqs - Centos/RHEL 7

```
    sudo yum install autoconf automake libtool pkg-config
    sudo yum install cmake libmpc-devel mpfr-devel gmp-devel gawk bison flex 
    sudo yum install texinfo patchutils gcc gcc-c++ zlib-devel expat-devel
    sudo yum install swig rh-python35 ninja-build
    sudo pip3 install meson
```

### Clone the repo


```
  cd $TOP
  git clone git@github.com:sifive/freedom-tools.git
```

### Download and build the packages

This is a lengthy build. Pick only the package you need.

```
  cd $TOP/freedom-tools
  make binutils-metal
  make gcc-metal
  make gdb-metal
  make openocd
  make qemu
  make sdk-utilities
  make toolchain-metal
  make trace-decoder
  make xc3sprog
```

-->
