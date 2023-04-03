// --------------------------------------------------------------------------
// (c)2023, Jeff Nye
// https://github.com/jeffnye-gh/jnutils, performance-modeling
// ---------------------------------------------------------------------------
#include "bp.h"
//#include "tage.h"
#include "options.h"
#include "msg.h"
#include "utils.h"

#include <boost/algorithm/string.hpp>

#include <bitset>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost;

Options *Options::instance = 0;
std::shared_ptr<Options> opts(Options::getInstance());

Msg *Msg::instance = 0;
std::unique_ptr<Msg> msg(Msg::getInstance());

// -------------------------------------------------------------------
// -------------------------------------------------------------------
int main(int ac,char **av)
{
  msg->setWho("bp");
  opts->setup_options(ac,av);

  Bp bp;

//  srand(0x1234);

//  string traceFile   = "../traces/kaggle/input/I04.csv";
//  string summaryFile = "./simple.csv";

//  ifstream in(traceFile);
//
//  if(!in.is_open()) {
//    msg->emsg("Could not open trace file '"+traceFile+"'");
//    return(1);
//  }
//
//  ofstream out(summaryFile);
//  if(!out.is_open()) {
//    msg->emsg("Could not open summary file '"+summaryFile+"'");
//    return(1);
//  }
//
//
  vector<Branch> branches;

  if(opts->convert_full_trace) {
    if(!bp.convertFile(opts->full_trace_fn,opts->simple_trace_fn)) return 1;
  } else if(opts->run_prediction) {
    if(!bp.loadSimpleTraceFile(opts->simple_trace_fn,branches)) return 1;
    if(!bp.runPrediction(opts->results_fn,branches)) return 1;
  }

//  if(opts->load_full_trace) {
//
//    if(!bp.loadFullTraceFile(opts->full_trace_fn,branches))
//      return 1;
//
//  } else if(opts->convert_full_trace) {
//
//    if(!bp.loadFullTraceFile(opts->full_trace_fn,branches))
//      return 1;
//
//    if(!bp.writeSimpleTraceFile(opts->simple_trace_fn,branches))
//      return 1;
//
//  } else if(opts->run_prediction) {
//
//    if(!bp.loadSimpleTraceFile(opts->simple_trace_fn,branches))
//      return 1;
//
//    if(!bp.runPrediction(opts->results_fn,branches))
//      return 1;
//  }

//  string line;
//  //vector<string>::const_iterator p,q,r;
//  uint32_t lineNum=0;
//  uint32_t brId=0;
//
//  bool rptT=false,rptNT=false;
//  msg->imsg("Reading file");
//  while(getline(in,line)) {
//    ++lineNum;
//    if(lineNum == 1) continue;
//    vector<string> sv;
//    boost::split(sv,line,boost::is_any_of(" ,\t"),boost::token_compress_on);
//
//    //grab the T/NT value
//    float    ftaken = stof(sv[481]);
//    uint32_t taken  = (uint32_t) ftaken;
//
//    //pull off the address cols 1-33;
//    stringstream ss;
//    for (auto r = sv.begin()+1;r<sv.begin()+33;++r) {
//      float rf = stof(*r);
//      int ri   = (int) rf;
//      ss<<ri;
//    }
//
//    string binvalue = ss.str();
//    reverse(binvalue.begin(),binvalue.end());
//    uint32_t ri;
//    try {
//      ri = stol(binvalue,nullptr,2);
//    } catch(std::exception&) {
//      cout<<"Exception: binvalue "<<binvalue<<" "<<binvalue.length()<<endl;
//      return 1;
//    }
//
//    uint32_t target  = getTarget(ri);
//    uint32_t predict = NOT_TAKEN;
//
//    Branch b(brId++,ri,target,taken,predict);
//    branches.push_back(b);
////    uint32_t brPc     = b.address;
////    uint32_t brTarget = b.target;
////    bool     brTaken  = b.taken == 1;
////    bool predTaken = tage.GetPrediction(brPc);
////    if(predTaken) b.predTaken = 1;
////    else          b.predTaken = 0;
////
////    bool predDir = b.predTaken == 1;
////    if(!rptT  &&  predDir) { cout<<"Got T  "<<endl; rptT = true; }
////    if(!rptNT && !predDir) { cout<<"Got NT "<<endl; rptNT = true; }
////
////    tage.UpdatePredictor(brPc,brTaken,predDir,brTarget);
//
//    if(lineNum ==  10000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum ==  50000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum == 100000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum == 150000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum == 200000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum == 300000) cout<<"Line num "<<lineNum<<endl;
//    if(lineNum == 350000) cout<<"Line num "<<lineNum<<endl;
//  } 

//  in.close();
//
//  
//  for(size_t i=0;i<branches.size();++i) {
//    branches[i].info();
//  }
//
//  out.close();

//  msg->imsg("Prediction");
////  for(size_t j=0;j<500000;++j) {
//    for(size_t i=0;i<branches.size();++i) {
//      //branches[i].info();
//      uint32_t brPc     = branches[i].address;
//      uint32_t brTarget = branches[i].target;
//      bool     brTaken  = branches[i].taken == 1;
//
//      bool predTaken = tage.GetPrediction(brPc);
//      if(predTaken) branches[i].predTaken = 1;
//      else          branches[i].predTaken = 0;
//
//      bool predDir = branches[i].predTaken == 1;
//
//if(!rptT  &&  predDir) { cout<<"Got T  "<<endl; rptT = true; }
//if(!rptNT && !predDir) { cout<<"Got NT "<<endl; rptNT = true; }
//      tage.UpdatePredictor(brPc,brTaken,predDir,brTarget);
//    }
////  }
//
//  cout<<endl;
//  for(size_t i=0;i<16;++i) { branches[i].info(); }
////  for(size_t i=0;i<branches.size();++i) {
////  }

  return 0;
}
