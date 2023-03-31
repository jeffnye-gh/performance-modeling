[Back to README](./README.md)

# Glossary

-------------------------------------------

Terminology is not always precise or used consistently across papers and 
discussion. This tries to help


# Branches


  - Target 
    - address the next pc if the branch is taken 
  - TAKEN (T)
    - next pc is the target of the branch
  - NOTTAKEN (NT)
    - next pc is the instruction following the branch instruction
  - Conditional branch
    - boolean selector, if(COND) then ACTION else ALT_ACTION
  - Unconditional branch
    - branch is always taken, JUMP or goto
  - Direct
    - target is encoded in the instruction
  - Indirect
    - instruction specifies where the target is to be found
  - Biased branch
    - branch history shows the branch is predominately TAKEN(NOTTAKEN)
  - Predictor Aliasing
    - when multiple unrelated branches share the same predictor information
    - aka Predictor Interference
    - neutral  - interference has no impact on prediction accuracy
    - positive - interference improves overall accuracy
    - negative - interference increases misprediction
    - negative interference is most common
  - Side predictor
    - secondary predictor along side the main predictor
    - defined to handle special cases
  - Local history
    - branch can be predicted using only it's T/NT pattern
    - e.g. for loop branches
  - Global history
    - branch can be predicted using other related branches 
      (along w/ local history)
  - Correlated branches
    - when 1 or more branch history provides hints to T/NT hv of the others
    - e.g. knowing the outcome of 1 branch help prediction with another
  - Basic block
    - a section of branch-free code.
