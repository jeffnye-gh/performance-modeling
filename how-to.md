# How-To Instructions

Much of this information is found in the README's distributed with the source packages. But in a number of cases it was necessary to work around issues in the distributions. Those work arounds are documented here.

In the ideal these are recipes that can be cut/pasted into a session without any trial and error.

At present everything assumes installation on Ubuntu 22 with sudo rights.


------
# TOC

The TOC attempts to list the steps in the required order up to riscv-perf-model. The docker instructions are extra.

1. [Local environment variables](#local-environment-variables)

    1. wget tmp directory

    1. Sparcians/Map env var

    1. riscv-perf-model env var

1. [Install Miniconda on Ubuntu 22](#install-miniconda-on-ubuntu-22)

1. [Install Map/Sparta on Ubuntu 22](#install-map-sparta-on-ubuntu-22)

    1. Pre-req

    1. Install the collateral for Ubuntu 22

    1. Clone the repo

    1. Edit the source files (for Olympia)

    1. Build Sparta

1. [Install Map/Argos on Ubuntu 22](#install-map-argos-on-ubuntu-22)

    1. Pre-req

    1. Install the collateral for Ubuntu 22

    1. Install the conda packages for Ubuntu 22

    1. Build PipeView

1. [Install riscv-perf-model on Ubuntu 22](#install-riscv-perf-model-on-ubuntu-22)

    1. Pre-reqs

    1. Clone the repo

    1. Patch/modify the repo

    1. Build the simulator

1. [Using pipeline data views](#using-pipeline-data-views)

1. [Install docker on Ubuntu 22](#install-docker-on-ubuntu-22)

    1. [Remove previous install](##remove-previous-install)

    1. [Update and install collateral](##update-and-install-collateral)

    1. [Install latest docker](##install-latest-docker)

    1. [Hello world test](##hello-world-test)

------

# Local environment variables

A few bash environment variables is defined to reduce typing in these instructions.

These do not need to be a permanent part of your environment.

## wget tmp directory

Some packages require manual download using wget. This a temporary directory for that purpose.

- example: export WGETTMP=/home/jeff/Downloads

## Sparcians/Map env var

The var that points to where Sparcians/Map was cloned

- example: export MAP=/home/jeff/Development/map

It is a little confusing, Map is under Sparcians on github, Map contains a submodule Sparta.

Similarly the pipeline viewer commonly known as Argos, is under Sparcians/Map/Helios/PipeViewer/pipe_view/argos.py. 

## riscv-perf-model env var

The var that points to where riscv-perf-model (aka Olympia) was cloned.

- example: export OLYMPIA=/home/jeff/Development/riscv-perf-model

------

# Install Miniconda on Ubuntu 22

- cd $WGETTMP
- wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
- sh ./Minconda3-latest-Linux-x86_64.sh
- follow the instructions for license, etc. 
    - I am using the default install location
    - I am allowing the installer to run conda init
    - The text instructions tell you how to disable miniconda activation at startup
        - conda config --set auto_activate_base false
    - I am not executing this command
- open a new termimal or reload your environment

---------

# Install Map/Sparta on Ubuntu 22

## Pre-reqs

- Install Miniconda - see above
- Open a new terminal

## Install the collateral for Ubuntu 22

There might be bugs in this. I do not have a virgin Ubuntu, there might be missing packages not listed in the documentation, some of these packages may not be needed or have the wrong names.

- sudo apt install cmake sqlite doxygen (no equiv: hdf5 yaml-cpp rapidJson xz)
- The names change for Unbuntu (from Centos) so:
    - sudo apt install hdf5-tools h5utils
    - sudo apt install libyaml-cpp-dev
    - sudo apt install rapidjson-dev
    - sudo apt install xz-utils

## Clone the repo

- cd $MAP/..
- git clone https://github.com/sparcians/map.git
- cd map/sparta

## Edit the source files (for Olympia)

If you are building Olympia (riscv-perf-model) make these changes to these files:

- Edit:
    - Change $MAP/sparta/src/TreeNodeExtensions.cpp
    - Roughly line 72, comment out the destructor
        - //ExtensionsParamsOnly::~ExtensionsParamsOnly()
        - //{
        - //}
- Edit:
    - Change $MAP/sparta/simulation/TreeNodeExtensions.hpp
    - Roughly line 27, define the destructor, (add the braces)
        - virtual ~ExtensionsParamsOnly() {}

## Build Sparta

 See the apt install for support packages above in Pre-reqs

- cd $MAP/sparta
- mkdir release; cd release
- cmake .. -DCMAKE_BUILD_TYPE=Release
- make -j4   (idk-why, -j16 crashes my gnome terminal, weird)

---------

# Install Map/Argos on Ubuntu 22

Argos is a python pipe viewer for trace based performance models. It is variously named, even within the repo, as Helio, Argos, pipeViewer, or pipe_view. The python script is argos.py

The build directory is $MAP/helios/pipeViewer.


## Pre-reqs

There is likely cleanup possible in this list, but this is what I did. I'll simplify this once I have a fresh environment.

- Install Miniconda - see above
- Install Map/Sparta - see above

## Install the Map/Argos collateral for Ubuntu 22

This tool has a stupidly long dependency chain. 

- sudo apt install wxpython-tools (was called python-wxtools)
- sudo apt install libgtk-3-dev

- pip3 install attrdict3  (or maybe just attrdict)
- pip3 install wxPython
- pip3 install pyyaml

## Install the Map/Argos conda packages for Ubuntu 22

- Start a terminal with miniconda activated. See above. Prompt will look like:
    - (base) jeff@reynaldo:~/Development:

- cd $MAP   (cd to the root of the Sparcians/Map install)

- conda install -c conda-forge jq
- conda install -c conda-forge yq
- ./scripts/create_conda_env.sh sparta dev
    - This creates a conda dev environment script
- conda activate sparta
    - This activates the conda dev environment
- cd $(git rev-parse --show-toplevel); mkdir release; cd release


## Build Map/Argos/PipeView (Helios)

Your terminal should have an active sparta/conda dev environment. See above. You should be in the map/release directory. See the command in the previous section, cd $MAP/release

- cmake -DCMAKE_BUILD_TYPE=Release ..
- make -j4


---------

# Using Map/Argos/PipeView pipeline data views

## Prereqs

This assumes you have followed the instructions above for these steps. 

- Install Miniconda on Ubuntu 22
- Install Map/Sparta on Ubuntu 22
- Install Map/Argos on Ubuntu 22
- FIXME: it's possible you also need: 
    - Install riscv-perf-model on Ubuntu 22

## Create example core model

- cd to core model dir under sparta release
    - cd $MAP/sparta/release/example/CoreModel
- make
 

## Generate pipeline database

- cd $MAP/sparta/release/example/CoreModel
- ./sparta_core_example -i 1000 -z pipeout_

## View pipe output

### Pipeline data in single cycle view

- python3 ${MAP}/helios/pipeViewer/pipe_view/argos.py --database pipeout_ --layout-file cpu_layout.alf


### Pipeline data in multi-cycle view

- python3 ${MAP}/helios/pipeViewer/pipe_view/argos.py --database pipeout_ --layout-file cpu_layout.alf

---------

# Install docker on Ubuntu 22

## Remove previous install

Remove any test docker support or images as necessary.

- sudo apt remove docker-desktop
- rm -r $HOME/.docker/desktop
- sudo rm /usr/local/bin/com.docker.cli
- sudo apt purge docker-desktop
- sudo apt update
- sudo apt upgrade
## Update and install collateral

Install the support packages as needed. There is one step below that is not in list form (echo "deb...). 

- sudo apt install ca-certificates curl gnupg lsb-release
- sudo mkdir -m 0755 -p /etc/apt/keyrings
- curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
<br />
- The following is unformated due to control characters
<pre>
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
</pre>
- sudo apt-get update

If you get an GPG error with apt update:

- sudo chmod a+r /etc/apt/keyrings/docker.gpg
- sudo apt-get update

---------

# Install riscv-perf-model on Ubuntu 22

riscv-perf-model aka Olympia. Olympia is a trace driven OOO performance model. 

It appears to be incomplete, there is an advisory that renaming does not work. It does have some interesting capabilities in terms of trace input formats in [STF](https://github.com/sparcians/stf_spec) and [JSON](https://github.com/riscv-software-src/riscv-perf-model/tree/master/traces#json-inputs).

## Pre-reqs

- Install Miniconda - see above
- Install Sparta - see above

## Clone the repo

This needs the absolute path to the map/sparta directory.

There are errors in map/Sparta, make the source file changes described above.

There is an error in Dispatch.hpp, see below.

- cd to/some/where
- git clone --recursive git@github.com:riscv-software-src/riscv-perf-model.git

## Patch/modify the repo

- cd to/some/where/riscv-perf-model
- Edit core/Dispatch.hpp
    - change: #include "test/ContextCounter/WeightedContextCounter.hpp"
    - to: #include "sparta/statistics/WeightedContextCounter.hpp"

sparta/simulation/TreeNodeExtensions.hpp

## Build the simulator

- cd to/some/where/riscv-perf-model
- mkdir release; cd release
- cmake .. -DCMAKE_BUILD_TYPE=Release -DSPARTA_BASE=$MAP/sparta

### Select build level

- make -j4     # build everything
- make olympia # build the simulator only
- make regress 

--------

## Install latest docker

Actual docker installation

- sudo apt install docker-ce docker-ce-cli containerd.io 
- sudo apt docker-buildx-plugin docker-compose-plugin

## Hello world test

Run the install check

- sudo docker run hello-world

You should see this in the console:

> > Hello from Docker!

> > This message shows that your installation appears to be working correctly.

