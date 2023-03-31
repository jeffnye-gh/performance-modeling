[Back to README](./README.md)

# Branch Prediction

-------------------------------------------
# TOC

1. [Chapter One](#chapter-one)
1. [Benchmark Suites](#xxx-yyy-zzz)

-------------------------------------------

# A survey of techniques for dynamic branch prediction

## Citation

- Mittal, Sparsh. "A survey of techniques for dynamic branch prediction." Concurrency and Computation: Practice and Experience 31.1 (2019): e4666.
    - https://arxiv.org/pdf/1804.00261

## Outline

See also section 1 of the citation.

1. [Branch predictor designs](#branch-predictor-designs)

    1. Two-level BPs
    1. Using both global history and branch address
    1. Using multiple indexing functions
    1. Leveraging biased branches
    1. Geometric history length BPs
    1. TAGE operation

1. [Branch predictors for hard to predict branches](#branch-predictors-for-hard-to-predict-branches)

    1. Predicting loop-exit branches 
    1. Predicting branches inside nested loops
    1. Predicting branches with long period
    1. Predicting based on data correlation
    1. Predicting based on address correlation

1. [Hybrid branch predictors](#hybrid-branch-predictors)

    1. Tagged hybrid BPs 
    1. Selection-based hybrid BPs
    1. Fusion-based hybrid BPs
    1. Multi-hybrid BP designs
    1. Prophet-critic hybrid BP

1. Techniques for Improving BP accuracy

    1. Adapting history-length and path-length 
    1. Filtering branch history 
    1. Reducing aliasing with kernel-mode instructions
    1. Using conflict-reducing indexing functions
    1. Handling multithreading and short threads
    1. Utilizing information from wrong-path execution

1. Neural BPs and implementation techniques

    1. Neural BPs
    1. Optimizing Neural BPs 
    1. Analog implementations of neural BPs
    
1. Techniques for reducing BP latency and energy

    1. BP pipelining 
    1. BP caching and overriding
    1. BP virtualization 
    1. Predicting multiple branches in each cycle
    1. Reducing PHT size by BHR partitioning
    1. Leveraging branch locality
    1. Avoiding redundant reads and updates

----------------------------------------------------------------
### Branch predictor designs

#### Two-level BPs
#### Using both global history and branch address
#### Using multiple indexing functions
#### Leveraging biased branches
#### Geometric history length BPs
#### TAGE operation

Modulo of the PC is calculated against the number of entries in the bimodal 
table creating an index into that table. This is the counter value, 
bimodalCounter, if bimodalCounter > 1 is the biased value the basePrediction is 
TAKEN. (SNT=0,NT=1,T=2,ST=3). 

Note state machine order is SNT->NT->ST->T.  The strong/weak and T/NT bits are 
separated to enable single port RAM implementations of the bimodal counter
arrays.

For each bank in the tage predictor a tag is formed

----------------------------------------------------------------
# Branch predictors for hard to predict branches

### Predicting loop-exit branches
### Predicting branches inside nested loops
### Predicting branches with long period
### Predicting based on data correlation
### Predicting based on address correlation
#
----------------------------------------------------------------
# Hybrid branch predictors

### Tagged hybrid BPs 
### Selection-based hybrid BPs
### Fusion-based hybrid BPs
### Multi-hybrid BP designs
### Prophet-critic hybrid BP

----------------------------------------------------------------
# Techniques for Improving BP accuracy

## Adapting history-length and path-length
## Filtering branch history 
## Reducing aliasing with kernel-mode instructions
## Using conflict-reducing indexing functions
## Handling multithreading and short threads
## Utilizing information from wrong-path execution

----------------------------------------------------------------
# Neural BPs and implementation techniques

## Neural BPs
## Optimizing Neural BPs
## Analog implementations of neural BPs

----------------------------------------------------------------
# Techniques for reducing BP latency and energy

## BP pipelining
## BP caching and overriding
## BP virtualization
## Predicting multiple branches in each cycle
## Reducing PHT size by BHR partitioning
## Leveraging branch locality
## Avoiding redundant reads and updates


------------------------------------------------------------
# Benchmark suites
https://openbenchmarking.org/
https://www.phoronix-test-suite.com/
https://github.com/phoronix-test-suite/phoronix-test-suite/


LTTng: LTTng is a low-overhead tracing framework for Linux. It can generate raw trace files in a format called "ctf" using the "lttng" command-line tool. The trace files can be viewed and analyzed using the LTTng viewer.

https://lttng.org/

https://lttng.org/docs/v2.12/#doc-tracing-your-own-user-application

