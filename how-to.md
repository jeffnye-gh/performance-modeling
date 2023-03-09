# How-To Instructions

At present everything assumes installation on Ubuntu 22 with sudo rights.

The TOC attempts to list the steps in the required order up to riscv-perf-model. The docker instructions are extra.

## TOC

1. [Install Miniconda on Ubuntu 22](#install-miniconda-on-ubuntu-22)

1. [Install Map/Sparta on Ubuntu 22](#install-map-sparta-on-ubuntu-22)
    2. Pre-req
    3. Install the collateral for Ubuntu 22
    3. Clone the repo

1. [Install riscv-perf-model on Ubuntu 22](#install-riscv-perf-model-on-ubuntu-22)
    2. Pre-reqs
    3. Clone the repo
    3. Install the conda environment


1. [Install docker on Ubuntu 22](#install-docker-on-ubuntu-22)

    1. [Remove previous install](##remove-previous-install)
    1. [Update and install collateral](##update-and-install-collateral)
    1. [Install latest docker](##install-latest-docker)
    1. [Hello world test](##hello-world-test)

# Install Miniconda on Ubuntu 22

- cd to/some/where
- wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
- sh ./Minconda3-latest-Linux-x86_64.sh
- follow the instructions for license, etc. 
    - I am using the default install location
    - I am allowing the installer to run conda init
    - The text instructions tell you how to disable miniconda activation at startup
        - conda config --set auto_activate_base false
    - I am not executing this command
- open a new termimal or reload your environment

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

- cd to/some/where
- git clone https://github.com/sparcians/map.git
- cd map/sparta

## Build Sparta
 See the apt install for support packages above in  Pre-reqs

- cd .../map/sparta
- mkdir release; cd release
- cmake .. -DCMAKE_BUILD_TYPE=Release
- make -j4   (idk-why, -j16 crashes my gnome terminal, weird)

<br/>
# Install riscv-perf-model on Ubuntu 22

riscv-perf-model aka Olympia. Olympia is a trace driven OOO performance model. It appears to be incomplete, there is an advisory that renaming does not work. It does have some interesting capabilities in terms of trace input formats in [STF](https://github.com/sparcians/stf_spec) and [JSON](https://github.com/riscv-software-src/riscv-perf-model/tree/master/traces#json-inputs).

## Pre-reqs

- Install Miniconda - see above
- Install Sparta - see above

## Clone the repo

- cd to/some/where
- git clone https://github.com/riscv-software-src/riscv-perf-model.git


## Install the conda environment

Original instructions are [HERE](https://github.com/riscv-software-src/riscv-perf-model/tree/master/conda)

- cd riscv-perf-model
- 

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




