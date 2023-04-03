/*
#include "tage.h"
#include <algorithm>

// -------------------------------------------------------------------------
// Initialize TAGE predictor
//
// Capture the history length parameter
// Reset the table_index field for each table
// For each table
//   set the table size to 1 << history length;
// -------------------------------------------------------------------------
void SimpleTage::InitializeTAGEPredictor(SimpleTAGEPredictor* tage)
{
  // Set initial history length and table indices
  tage->history_length = kMaxHistoryLength;

  for (int i = 0; i < kNumTables; i++) {
    tage->table_index[i] = 0;
  }
  
  // Initialize each table
  for (int i = 0; i < kNumTables; i++) {
    tage->table[i].table_size = 1 << tage->history_length;
    tage->table[i].table = new SimpleTAGEEntry[tage->table[i].table_size];
    for (int j = 0; j < tage->table[i].table_size; j++) {
      tage->table[i].table[j].tag = 0;
      tage->table[i].table[j].ctr = 0;
    }
  }
  
  // Initialize geometric history length selector
  tage->geometric_history_length_selector = 0;

  for (int i = 0; i < kNumTables; i++) {
    tage->geometric_history_length[i] = kMaxHistoryLength;
  }

  tage->geometric_history_length[0] = kMinHistoryLength;
}

// -------------------------------------------------------------------------
// Update TAGE predictor
// -------------------------------------------------------------------------
void UpdateTAGEPredictor(SimpleTAGEPredictor* tage, int branch_address, bool actual_outcome) {
  // Calculate table indices and tags
  int index[kNumTables];
  int tag[kNumTables];
  for (int i = 0; i < kNumTables; i++) {
    index[i] = (branch_address >> i) % tage->table[i].table_size;
    tag[i] = (tage->global_history >> i) % tage->table[i].table_size;
  }
  
  // Make a prediction based on the tables
  bool prediction = false;
  for (int i = 0; i < kNumTables; i++) {
    SimpleTAGEEntry entry = tage->table[i].table[index[i]];
    if (entry.tag == tag[i]) {
      prediction = prediction || (entry.ctr >= 0);
    }
  }
  
  // Update the tables
  for (int i = 0; i < kNumTables; i++) {
    if (prediction == actual_outcome || tage->table[i].table[index[i]].tag != tag[i]) {
      // Update counter
      if (actual_outcome) {
        tage->table[i].table[index[i]].ctr = std::min(tage

//Jeff Nye
//please continue
//
//css

  ->table[i].table[index[i]].ctr + 1, 3);
  } else {
    tage->table[i].table[index[i]].ctr = std::max(tage->table[i].table[index[i]].ctr - 1, -4);
  }
  
  // Update tag
  tage->table[i].table[index[i]].tag = tag[i];
  
  // Update history length
  if (prediction != actual_outcome) {
    int index_delta = actual_outcome ? 1 : -1;
    int table_delta = (index_delta < 0) ? -1 : 1;
    int table_index = tage->table_index[i] + table_delta;
    if (table_index >= 0 && table_index < kNumTables) {
      tage->table_index[i] = table_index;
      tage->history_length += index_delta * tage->geometric_history_length_selector * kGeometricHistoryLengthStep;
      tage->history_length = std::max(std::min(tage->history_length, kMaxHistoryLength), kMinHistoryLength);
      tage->global_history = (tage->global_history << table_delta) | actual_outcome;
    }
  }
}

}

// Update geometric history length selector
if (actual_outcome) {
tage->geometric_history_length_selector = (tage->geometric_history_length_selector + 1) % kNumTables;
}
}

// -------------------------------------------------------------------------
// Make a prediction with the TAGE predictor
// -------------------------------------------------------------------------
bool PredictWithTAGEPredictor(SimpleTAGEPredictor* tage, int branch_address) {
// Calculate table indices and tags
int index[kNumTables];
int tag[kNumTables];
for (int i = 0; i < kNumTables; i++) {
index[i] = (branch_address >> i) % tage->table[i].table_size;
tag[i] = (tage->global_history >> i) % tage->table[i].table_size;
}

// -------------------------------------------------------------------------
// Make a prediction based on the tables
// -------------------------------------------------------------------------
bool prediction = false;
for (int i = 0; i < kNumTables; i++) {
SimpleTAGEEntry entry = tage->table[i].table[index[i]];
if (entry.tag == tag[i]) {
prediction = prediction || (entry.ctr >= 0);
}
}

return prediction;
}
*/

/*
This implementation defines the SimpleTAGE predictor parameters and data structures, 
including the SimpleTAGEEntry and SimpleTAGETable structs and the SimpleTAGEPredictor struct. 
It also defines functions to initialize the predictor, update it based on a 
branch outcome, and make a prediction for a given branch address.

The UpdateTAGEPredictor function performs the core TAGE predictor logic, 
which involves calculating table indices and tags, making a prediction based 
on the tables, updating the tables based on the actual outcome, and adjusting 
the history length if necessary. The PredictWithTAGEPredictor function simply 
calculates table indices and tags and makes a prediction based on the tables.

Note that this implementation is simplified and does not include all the 
features 
*/
