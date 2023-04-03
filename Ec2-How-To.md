[Back to README](./README.md)

# EC2 Setup How-To Instructions

-------------------------------------------
# TOC

FIXME - COMMENTED OUT UNTIL VERIFIED

<!--

----------------------------------------------------------
# EC2 instance

## Create an AWS account

FIXME: point to web resource for this

## Open your EC2 dash board

FIXME: point to web resource for this

This uses rhel9_test1 as instance name, key/pair name, ppk file name 
and putty session name.

Default login name for Red Hat is ec2-user.

```
My dashboard is located:
    https://us-east-2.console.aws.amazon.com/ec2/home?region=us-east-2#Home:

```

## Start a RHEL9 instance

```
  go to url:$DASHBOARD
      select Instance  <left menu>
      click orange Launch instance, and launch instance

  In browser - Launch an instance page
      create name                          - rhel9_test1
      in Application and OS Images         - select Red Hat
      Instance type                        - keep defaults, t2.micro, etc

      select Create key pair key pair name - rhel9_test1
      Keypair type                         - RSA
      Private key file format              - .ppk
      Select create key pair, copy file
      copy downloaded file to known location - rhel9_test1.ppk

      Network settings - in Launch an instance page
        keep defaults
        Allow SSH traffic from  -  Anywhere
 
      Configure storage - in Launch an instance page
        Root volume - 1x 30  GiB gp2 
         
      Scroll down launch instance

      Page: Next steps - preview
        select -> create billing and free tier usage alerts
        check -> Receive Free Tier Usage Alerts
          enter email address: your address 

        go back to Next steps - preview

        select Connect to your instance

        From EC2 Instance Connect tab - copy instance information
          Instance ID       -   i-0904de081e9f67593 (rhel9_test1)
          Public IP address -   18.218.82.93
          User name         -   ec2-user
```
## Connect to instance with putty on windows

```
   start putty
   Left panel - select Connection
     Open +SSH
     Open +Auth
     Select credentials
        Private key file for authentication - browse to rhel9_test1.ppk

   Left panel - Session
     Host Name (or IP address) - 18.218.82.93
     Port                      - 22
     Connection type           - SSH
     Saved Sessions            - rhel9_test1
     Select save
   Select open
   Accept key <ok>
   login as: ec2-user

```

## Update instance OS

In console (putty) window:

```
  bash
  sudo yum update -y
  cat /etc/redhat-release
      should be at least: Red Hat Enterprise Linux release 9.1 (Plow)  
  sudo yum install -y gcc vim git wget

## Clone perf modeling how-to's

  cd; mkdir -p Development; cd Development
  git clone https://github.com/jeffnye-gh/performance-modeling.git

## Set how-to exported variables
  cd; cd Development
  mkdir -p Downloads

  export TOP=`pwd`
  export WGETTMP=$TOP/Downloads
  export PATCHES=$TOP/performance-modeling/patches
  export MAP=$TOP/map
  export OLYMPIA=$TOP/riscv-perf-model
  export RV_TOOLS_SRC=$TOP/riscv-gnu-toolchain
  export RV_GNU_TOOLS=$TOP/riscv-tools
  export DROMAJO=$TOP/riscv-perf-model/traces/stf_trace_gen/dromajo

## Install riscv gnu tool chain

### Pre-reqs
These are listed in the order I used, I will come back and optimize

```
  sudo yum install -y autoconf automake         <might be redundant>
  sudo yum group install -y "Development Tools"
  sudo yum install -y libmpc-devel 

  cd $WGETTEMP
  wget https://rpmfind.net/linux/openmandriva/cooker/repository/x86_64/main/release/texinfo-7.0.2-3-omv2390.x86_64.rpm

  sudo yum localinstall sudo yum localinstall texinfo-7.0.2-3-omv2390.x86_64.rpm

```

### Clone, configure, make and install

This takes a long time to download

```
  cd $TOP
  mkdir -p $RV_GNU_TOOLS
  git clone https://github.com/riscv-collab/riscv-gnu-toolchain
  cd $RV_TOOLS_SRC
  ./configure --prefix=$RV_GNU_TOOLS --enable-multilib
  make linux

```

# RPM help

```
    what dependencies
      rpm -qpR texinfo-7.0.2-3-omv2390.x86_64.rpm


texlive-dehyph
texlive-epsf
texlive-tex.bin
texlive-texinfo


```
 
redhad/ec2 enabling

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/9/html/deploying_red_hat_enterprise_linux_9_on_public_cloud_platforms/assembly_deploying-a-virtual-machine-on-aws_cloud-content
 

custeromer portal go here create account
https://access.redhat.com/?session_state=86ae0d13-5fa7-4693-9f79-be0af15eec48&code=b4571181-ba3d-426c-b453-4f33eb8a0aa9.86ae0d13-5fa7-4693-9f79-be0af15eec48.4473e33a-bfd4-4fd0-9ebf-82faab4c2f6c


go here to enable subscriptions:

https://access.redhat.com/public-cloud

-->

