#include "bp.h"
#include "options.h"
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
bool Bp::convertFile(std::string infn,std::string outfn)
{
  string line;
  uint32_t lineNum=0;

  //do this early the full trace files are big
  ifstream in(infn);
  ofstream out(outfn);
  
  if(!in.is_open()) {
    msg->emsg("Could not open full trace file '"+infn+"'");
    return false;
  }

  if(!out.is_open()) {
    msg->emsg("Could not open output file '"+outfn+"'");
    return false;
  }

  //output header
  out<<"ID,PC,TGT,T,PT"<<endl;

  msg->imsg("Starting conversion");

  uint32_t brId=0;
  while(getline(in,line)) {
    ++lineNum;
    if(lineNum == 1) continue;
    vector<string> sv;
    boost::split(sv,line,boost::is_any_of(" ,\t"),boost::token_compress_on);

    if(sv.size() != 482) {
      msg->emsg("Could not parse full trace file");
      msg->emsg("line#:"+::to_string(lineNum));
      msg->emsg("line : '"+line+"'");
      return false;
    }

    //grab the T/NT value
    float    ftaken = stof(sv[481]);
    uint32_t taken  = (uint32_t) ftaken;

    //pull off the address cols 1-33;
    stringstream ss;
    for (auto r = sv.begin()+1;r<sv.begin()+33;++r) {
      float rf = stof(*r);
      int ri   = (int) rf;
      ss<<ri;
    }

    string binvalue = ss.str();
    reverse(binvalue.begin(),binvalue.end());
    uint32_t ri;
    try {
      ri = stol(binvalue,nullptr,2);
    } catch(std::exception&) {
      cout<<"Exception: binvalue "<<binvalue<<" "<<binvalue.length()<<endl;
      return false;
    }

    uint32_t target  = getTarget(ri);
    uint32_t predict = NOT_TAKEN;

    stringstream pcss,tgss;
    pcss<<"0x"<<hex<<setw(8)<<setfill('0')<<ri;
    tgss<<"0x"<<hex<<setw(8)<<setfill('0')<<target;
    out<<brId++<<","<<pcss.str()<<","<<tgss.str()
               <<","<<taken<<","<<predict<<endl;

    if(lineNum ==  10000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum ==  50000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum == 100000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum == 150000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum == 200000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum == 300000) cout<<"Line num "<<lineNum<<endl;
    if(lineNum == 350000) cout<<"Line num "<<lineNum<<endl;
  }

  in.close();
  return true;
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
bool Bp::loadSimpleTraceFile(std::string infn,vector<Branch>&v)
{
  ifstream in(infn);
  
  if(!in.is_open()) {
    msg->emsg("Could not open full trace file '"+infn+"'");
    return false;
  }

  msg->imsg("Loading simple trace file");
  string line;
  uint32_t lineNum=0;
  while(getline(in,line)) {
    ++lineNum;
    if(lineNum == 1) continue;
    vector<string> sv;
    boost::split(sv,line,boost::is_any_of(" ,\t"),boost::token_compress_on);

    if(sv.size() != 5) {
      msg->emsg("Could not parse simple trace file");
      msg->emsg("line#:"+::to_string(lineNum));
      msg->emsg("line : '"+line+"'");
      return false;
    }

    uint32_t id,pc,target,taken,predict;

    try {
      id      = stoi(sv[0]);
      pc      = stoul(sv[1],nullptr,16);
      target  = stoul(sv[2],nullptr,16);
      taken   = stoi(sv[3]);
      predict = stoi(sv[4]);
    } catch(std::exception&) {

      msg->emsg("Conversion error");
      msg->emsg("s0 '"+sv[0]+"'");
      msg->emsg("s1 '"+sv[1]+"'");
      msg->emsg("s2 '"+sv[2]+"'");
      msg->emsg("s3 '"+sv[3]+"'");
      msg->emsg("s4 '"+sv[4]+"'");

    }

    Branch b(id,pc,target,taken,predict);
    v.push_back(b);
  }

  return true;
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
bool Bp::runPrediction(std::string rfn,vector<Branch> &branches)
{
  msg->imsg("Running prediction on "
            +::to_string(branches.size())+" branches");

  ofstream out(rfn);

  if(!out.is_open()) {
    msg->emsg("Could not open results file '"+rfn+"'");
    return false;
  }

  uint32_t recirculate = 1;
  uint32_t limit = branches.size();
  uint32_t curLimit = 0;
  bool rptT=false,rptNT=false;
  for(uint32_t i=0;i<recirculate;++i) {

    curLimit = 0;

    for(size_t j=0;j<branches.size();++j) {
      uint32_t brPc     = branches[j].address;
      uint32_t brTarget = branches[j].target;
      bool     brTaken  = branches[j].taken == 1;
  
      bool predTaken = tage.GetPrediction(brPc);

      if(predTaken) branches[j].predTaken = 1;
      else          branches[j].predTaken = 0;

      bool predDir = branches[j].predTaken == 1;

      if(!rptT  &&  predDir) {
        cout<<"Got T  "<<j<<endl; rptT  = true;
      }

      if(!rptNT && !predDir) {
        cout<<"Got NT "<<j<<endl; rptNT = true;
      }

      tage.UpdatePredictor(brPc,brTaken,predDir,brTarget);
  
      ++curLimit;
      if(curLimit > limit) {
        msg->imsg("Early exit 1");
        break;
      }
    }

//    msg->imsg("Round "+::to_string(i));

  }

  uint64_t total=0;
  uint64_t taken=0;
  uint64_t nottaken=0;
  uint64_t predtaken=0;
  uint64_t prednottaken=0;
  uint64_t correct=0;
  uint64_t incorrect=0;

  curLimit = 0;
  for(auto &b : branches) {

    b.emit(out); 

    ++total;

    if(b.taken) ++taken;
    else        ++nottaken;

    if(b.predTaken) ++predtaken;
    else            ++prednottaken;

    if(b.predTaken == b.taken) ++correct;
    if(b.predTaken != b.taken) ++incorrect;

    ++curLimit;
    if(curLimit > limit) {
      msg->imsg("Early exit 2");
      break;
    }
  }

  out<<"Final"<<endl;
  cout<<"Final"<<endl;

  tee(out,"unique    ",branches.size());
  tee(out,"total     ",total);
  tee(out,"actual T  ",taken);
  tee(out,"pred T    ",predtaken);
  tee(out,"actual NT ",nottaken);
  tee(out,"pred NT   ",prednottaken);
  tee(out,"correct   ",correct);
  tee(out,"incorrect ",incorrect);

  stringstream pct;

  double p = (double) incorrect / (double) total;
  pct<<fixed<<setprecision(6)<<p<<endl;

   out<<"misp %    "<<pct.str()<<endl;
  cout<<"misp %    "<<pct.str()<<endl;

  out.close();
  return true;

}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Bp::tee(ofstream &out,string m,uint32_t d)
{
  out<<m<<d<<endl;
  cout<<m<<d<<endl;
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
uint32_t Bp::getTarget(uint32_t br)
{
  uint32_t RANGE = 1024*1024;
  uint32_t offset = RANGE * (rand() / (RAND_MAX + 1.0));
  uint32_t sign   = 2     * (rand() / (RAND_MAX + 1.0));

  sign &= 0x1;
  uint32_t target = br + ((sign*-1)*offset);

  if(sign) target = br + offset;
  else     target = br - offset;

  return target;
}

