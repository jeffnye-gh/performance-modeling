// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
// https://github.com/jeffnye-gh/jnutils
// ---------------------------------------------------------------------------
#pragma once
#include "options.h"
#include "utils.h"
//#include "tracer.h"
#include <string>
#include <bitset>
#include <vector>

#define NUMTAGTABLES 4

#define BIMODAL_CTR_MAX   3
#define BIMODAL_CTR_INIT  2
#define TAGPRED_CTR_MAX   7
#define TAGPRED_CTR_INIT  0
#define BIMODALLOG       14
#define NUMTAGTABLES      4
#define TAGPREDLOG       12

using namespace std; //FIXME

// =====================================================================
// Each entry in the tag Pred Table
// =====================================================================
struct TagEntry 
{
  INT32  ctr;
  UINT32 tag;
  INT32  usefulBits;
};

// =====================================================================
// Folded History implementation ... 
// from ghr (geometric length) -> compressed(target)
// =====================================================================
struct CompressedHist
{
  // Objective is to convert geomLengt of GHR into tagPredLog 
  // which is of length equal to the index of the corresponding bank

  // It can be also used for tag when the final length would be the Tag
  UINT32 geomLength;
  UINT32 targetLength;
  UINT32 compHist;
      
  void updateCompHist(bitset<131> ghr) {

/*
    bitset<131> temp;;
    int numFolds = geomLength / targetLength;
    //int remainder = (ghr.size()) % compLength;
    int mask = (1 << targetLength) - 1;
    int geometricMask = (1 << geomLength) - 1;
    temp = ghr;
        
    temp = temp & geometricMask;
    UINT32 remainder = 0;
    UINT32 comphistfolds[numFolds];
        
    for(int i=0; i < numFolds; i++)
    {    
            comphistfolds[i] = temp & mask;
            temp = temp >> targetLength;
            
    }
    remainder = temp & mask;
        
    for(int i = 0; i< numFolds; i++)
    {
            compHist ^= comphistfolds[i];
    }
    compHist ^= remainder;
*/

    // easier way below... see PPM paper Figure 2
    // creating important masks

    int mask = (1 << targetLength) - 1;
    int mask1 = ghr[geomLength] << (geomLength % targetLength);
    int mask2 = (1 << targetLength);
    compHist  = (compHist << 1) + ghr[0];
    compHist ^= ((compHist & mask2) >> targetLength);
    compHist ^= mask1;
    compHist &= mask;  
         
  }    
};



//// =====================================================================
//// Initialize predictor tables
////for i = 0 to kNumTables - 1
////  table[i]
////    = new TAGETable(1 << (i + kLogMinTableSize),
////                         kTagWidths[i], 
////                         kTagCompBits[i],
////                         kCtrBits,
////                         kHistLengths[i],
////                         kUseAltPred,
////                         kUseBiModal,
////                         kUseExtraBits,
////                         kUseLoopPred,
////                         kUseUpdateThreshold);
////
////  stat_corr_table = new StatisticalCorrector(kStatCorrSize,
////                                             kStatCorrHistLength,
////                                             kUseUpdateThreshold);
////
////  local_history_table = new LocalHistoryTable(kLocalHistTableSize,
////                                              kLocalHistLength);
////
////  global_history = 0;
////
////  // Update predictor on each branch instruction
////  for each branch instruction:
////  // Calculate table index and tag
////    tage_index = CalculateTAGEIndex(pc, global_history,
////                                    local_history_table.local_history,
////                                    table_index,
////                                    table[table_index].table_size);
////    tag = CalculateTag(pc,
////                       table[table_index].tag_width,
////                       table[table_index].tag_comp_bits);
////  
////    // Lookup entry in TAGE table
////    entry = table[table_index].table[tage_index];
////  
////    // Predict using TAGE table
////    pred = entry.prediction;
////    if (entry.alt_pred != 0 && entry.use_alt_pred) {
////      alt_tage_index = CalculateAltTAGEIndex(pc, global_history, local_history_table.local_history, table_index, table[table_index].table_size);
////      alt_entry = table[table_index].table[alt_tage_index];
////      pred = (entry.alt_ctr >= 0) ? entry.alt_pred : alt_entry.prediction;
////    }
////  
////    // Update statistical corrector
////    stat_corr_index = CalculateStatCorrIndex(pc, global_history, local_history_table.local_history, stat_corr_table.size);
////    stat_corr_entry = stat_corr_table.table[stat_corr_index];
////    sc_pred = (entry.sc_ctr >= 0) ? pred : stat_corr_entry.prediction;
////    stat_corr_table.Update(pc, sc_pred, resolve_dir);
////    
////    // Update local history table
////    local_history_table.Update(pc, resolve_dir);
////  
////    // Update TAGE table
////    tage_pred_dir = (entry.ctr >= 0);
////    if (tage_pred_dir != resolve_dir || abs(entry.ctr) < kThreshold[tage_index]) {
////      tage_pred_dir = (entry.alt_ctr >= 0) ? entry.alt_pred_dir : tage_pred_dir;
////    }
////    table[table_index].table[tage_index].Update(resolve_dir, tage_pred_dir, tag, table[table_index].tag_comp_bits);
////    
////    // Update global history
////    global_history = ((global_history << 1) | resolve_dir) & ((1 << kGlobalHistLength) - 1);
////    
////    // Update branch history and table index
////    local_history_table.Update(pc, resolve_dir);
////    table_index = CalculateTableIndex(pc, global_history);
////  end for
//// =====================================================================
//// =====================================================================
//// Define SimpleTAGE predictor parameters
//const int kNumTables        = 10;          // number of tables
//const int kMaxHistoryLength = 200;         // maximum history length
//const int kMinHistoryLength = 5;           // minimum history length
//const int kGeometricHistoryLengthStep = 2; // geometric history length step
//
//struct SimpleTAGEEntry {
//  int tag;
//  int ctr;
//};
//
//struct SimpleTAGETable {
//  int table_size;
//  SimpleTAGEEntry* table;
//};
//
//struct SimpleTAGEPredictor {
//  int history_length;
//  int table_index[kNumTables];
//  SimpleTAGETable table[kNumTables];
//  int geometric_history_length[kNumTables];
//  int geometric_history_length_selector;
//  int global_history;
//};
//
//struct SimpleTage
//{
//  void InitializeTAGEPredictor(SimpleTAGEPredictor*);
//  void UpdateTAGEPredictor(SimpleTAGEPredictor*,int,bool);
//  
//};
// =====================================================================
//
// Total storage budget: 32KB (PHT) + 17 bits (GHR)a
//
// PHT:
// Total PHT counters: 2^17, 2 bits
// Total PHT size = 2^17 * 2 = 32KB
//
// GHR:
// GHR size: 17 bits
//
// =====================================================================
struct Tage
{
  // The interface to the four functions below CAN NOT be changed
  Tage(void);

  bool GetPrediction(UINT32 PC);  

  void UpdatePredictor(UINT32 PC, bool resolveDir, 
                       bool predDir, UINT32 branchTarget);

  void TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget);
  // Contestants can define their own functions below
 
  UINT32 HASH(UINT32 PC,UINT32 N,UINT32 compHist,int PHRTerm)
  {
    return PC ^ (PC >> (TAGPREDLOG - N)) ^ compHist ^ PHRTerm;
  }
 
  // end Contestants can define their own functions below

  // --------------------------------------------------------------------
  // The state is defined for Gshare, change for your design
  bitset<131> GHR;           // global history register

  // 16 bit path history
  int PHR;

  // Bimodal
  std::vector<UINT32> bimodal;
//  UINT32  *bimodal;          // pattern history table
  UINT32  historyLength;     // history length
  UINT32  numBimodalEntries; // entries in pht 
  UINT32  bimodalLog;

  //Tagged Predictors
  TagEntry *tagPred[NUMTAGTABLES];
  UINT32    numTagPredEntries;
  UINT32    tagPredLog;
  UINT32    geometric[NUMTAGTABLES];

  //Compressed Buffers
  CompressedHist indexComp[NUMTAGTABLES];
  CompressedHist tagComp[2][NUMTAGTABLES]; 
 
  // Predictions need to be global ?? recheck
  bool primePred;
  bool altPred;
  int primeBank;
  int altBank;

  // index had to be made global else recalculate for update
  UINT32 indexTagPred[NUMTAGTABLES];
  UINT32 tag[NUMTAGTABLES];
  UINT32 clock;
  int    clock_flip;
  INT32  altBetterCount;


};
