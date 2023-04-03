#pragma once
#include "tage.h"
#include "msg.h"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// ========================================================================
// ========================================================================
struct Branch {
  Branch(uint32_t _id,uint32_t _a,uint32_t _trg,
         uint32_t _tkn,uint32_t _pred=NOT_TAKEN)
    : id(_id),
      address(  _a&0xFFFFFFFF),
      target (_trg&0xFFFFFFFF),
      taken  (_tkn&0x1),
      predTaken(_pred)
  { }

  // -----------------------------------------------------------------
  // -----------------------------------------------------------------
  void emit(std::ofstream &out) {
    std::stringstream pcss,tgss;
    pcss<<"0x"<<std::hex<<std::setw(8)<<std::setfill('0')<<address;
    tgss<<"0x"<<std::hex<<std::setw(8)<<std::setfill('0')<<target;
    out<<id
       <<","<<pcss.str()
       <<","<<tgss.str()
       <<","<<taken
       <<","<<predTaken<<endl;
  }
  // -----------------------------------------------------------------
  // -----------------------------------------------------------------
  void info() {
    std::stringstream ssid,ssaddr,sstarg,sstake,sspred,ssdiff;
    ssid    <<     std::setw(2)<<id;
    ssaddr  <<std::hex<<std::setw(8)<<std::setfill('0')<<address;
    sstarg  <<std::hex<<std::setw(8)<<std::setfill('0')<<target;
    sstake  <<     std::setw(1)<<taken;
    sspred  <<     std::setw(1)<<predTaken;

    int diff = (int) target - (int)address;
    ssdiff << setw(8)<<diff;
    msg->imsg("br: "+ssid.str()
                +" addr:"+ssaddr.str()
                +" targ:"+sstarg.str()
                +" take:"+sstake.str()
                +" pred:"+sspred.str()
                +" diff:"+ssdiff.str());
  }

  uint32_t id;
  uint32_t address;
  uint32_t target;
  uint32_t taken;
  uint32_t predTaken; //0 = not taken, 1 = taken
};
// ========================================================================
// ========================================================================
struct Bp
{
  Bp() {}

  bool convertFile(std::string,std::string);
  bool loadSimpleTraceFile(std::string,std::vector<Branch>&);
  bool runPrediction(std::string,std::vector<Branch>&);

  void tee(std::ofstream&,std::string,uint32_t);

  uint32_t getTarget(uint32_t br);
  Tage tage;

};
