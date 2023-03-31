// --------------------------------------------------------------------------
// (c)2023, Jeff Nye
// https://github.com/jeffnye-gh/jnutils, performance-modeling
// ---------------------------------------------------------------------------
#include "tage.h"
#include "options.h"
#include "msg.h"
#include "utils.h"
#include <iomanip>
#include <iostream>
using namespace std;

Options *Options::instance = 0;
std::shared_ptr<Options> opts(Options::getInstance());

Msg *Msg::instance = 0;
std::unique_ptr<Msg> msg(Msg::getInstance());

int main(int ac,char **av)
{
  msg->setWho("tage");
  opts->setup_options(ac,av);

//  Tage tage("../traces/kaggle/input");
  Tage tage;

  srand(0x1234);
  
  for(UINT32 i=0; i<1024;++i) {
    UINT32 addr = (UINT32) rand();
    tage.GetPrediction(addr);
    cout<<"addr "<<hex<<setw(8)<<setfill('0')<<addr<<endl;
  }

  return 0;
}
