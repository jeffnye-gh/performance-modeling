[Back to README](./README.md)

# Trace generation

--------
# TOC

1. [Patching Dromajo for trace generation](#patching-dromajo-for-trace-generation)

--------
# Patching Dromajo for trace generation

This info is found in ./riscv-perf-model/traces/README.md.

A patch is supplied to modify Dromajo to generate STF traces.


```
    cd $OLYMPIA
    git clone https:://github.com/chipsalliance/dromajo
    cd dromajo
    git checkout 86125b31
    git apply ../dromajo_stf_lib.patch
    ln -s ../../../stf_lib
    mkdir build; cd build
    cmake ..
    make
```

Check if patch worked, should have the --stf_trace option

```
    ./dromajo
    usage ./dromajo {options} [config|elf-file]
        ...snip...
        --stf_trace <filename>  Dump an STF trace
        ...snip...
```
