// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
// https://github.com/jeffnye-gh/jnutils
// ---------------------------------------------------------------------------
#include "msg.h"
#include "options.h"
#include <iostream>
using namespace std;
// --------------------------------------------------------------------
// Build the option set and check the options
// --------------------------------------------------------------------
void Options::setup_options(int ac,char **av)
{
  notify_error = false;

  po::options_description visibleOpts(
   "\nBoost Option Example\n "
   "Usage:: test [--help|-h|--version|-v] {[options] {positional_option}}");

  po::options_description allOpts("All options");
  po::options_description stdOpts("Standard options");
  po::options_description hiddenOpts("Hidden options");

  //not implemented  po::options_description iniOpts("Config file options");
  po::positional_options_description posOpts;

  build_options(stdOpts,hiddenOpts,posOpts);

  visibleOpts.add(stdOpts);
  allOpts.add(stdOpts).add(hiddenOpts);

  try {
    po::store(
      po::command_line_parser(ac, av)
          .options(allOpts).positional(posOpts).run(),vm
    );

    //Without positional option po::parse_command_line can be used
    //po::store(po::parse_command_line(ac, av, allOpts), vm);

  } catch(boost::program_options::error& e) {
    msg->msg("");
    msg->emsg("1st pass command line option parsing failed");
    msg->emsg("What: " + string(e.what()));
    usage(stdOpts,posOpts);
    exit(1);
  }

  po::notify(vm);
  if(!check_options(vm,allOpts,visibleOpts,posOpts,true)) exit(1);
}
// --------------------------------------------------------------------
// Construct the std, hidden and positional option descriptions
// --------------------------------------------------------------------
void Options::build_options(po::options_description &stdOpts,
                            po::options_description &hiddenOpts,
                            po::positional_options_description &posOpts)
{
  stdOpts.add_options()
    ("help,h", "...")

    ("version,v", "report version and exit")

    ("query_options",po::bool_switch(&_query_options)->default_value(false),
     "report option settings and exit")

    ("full_trace_fn",   po::value<string>(&full_trace_fn), 
     "Full trace file name")

    ("simple_trace_fn",   po::value<string>(&simple_trace_fn), 
     "Simple trace file name")

    ("results_fn",   po::value<string>(&results_fn), 
     "Prediction results file name")

    ("load_full_trace", po::bool_switch(&load_full_trace),
     "")

    ("convert_full_trace", po::bool_switch(&convert_full_trace),
     "requires full trace and simple trace file names")

    ("run_prediction", po::bool_switch(&run_prediction),
     "requires simple trace file and results file name")

  ;

//  hiddenOpts.add_options()
//    ("hidden_one", po::value<int>(&hidden_one),
//     "Hidden option #1, accepted but not listed in usage")
//
//    ("hidden_two", po::value<int>(&hidden_two),
//     "Hidden option #2, accepted but not listed in usage")
//
//    ("positional_option", po::value<string>(&positional_option),
//     "Positional option example")
//  ;
//
//  posOpts.add("positional_option",-1); 
}
// --------------------------------------------------------------------
// Check sanity on the options, handle --help, --version
// --------------------------------------------------------------------
bool Options::check_options(po::variables_map &vm,
                            po::options_description &allOpts,
                            po::options_description &visibleOpts,
                            po::positional_options_description &posOpts,
                            bool firstPass)
{
  if(firstPass) {
    if(vm.count("help"))    { usage(visibleOpts,posOpts); return false; }
    if(vm.count("version")) { version(); return false; }
  } else {
    //insert option checks for 2nd pass only, usually ini file
    //not implemented yet
  }

  if(_query_options) { query_options(); return true; }

//  if(!bool_flag) {
//    msg->emsg("bool_flag must be set");
//    return false;
//  }

  return true;
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Options::usage(po::options_description &opts,
                    po::positional_options_description &posOpts)
{
  msg->imsg("BEG Options::usage()");
  cout<<opts<<endl;
  //cout<<posOpts<<endl;
  msg->imsg("END Options::usage()");
}
// --------------------------------------------------------------------
void Options::version()
{
  msg->imsg("BEG Options::version()");
  msg->imsg("");
  msg->imsg("Boost program_option example");
  msg->imsg("Version: v"+std::string(VERSION));
  msg->imsg("Slack jeff w/any questions");
  msg->imsg("");
  msg->imsg("END Options::version()");
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Options::query_options()
{
//  msg->imsg("BEG Options::query_options()");
//  msg->imsg("full_trace_fn : "po::value<string>(&full_trace_fn),
//     "Full trace file name")
//
//  msg->imsg("simple_trace_fn",   po::value<string>(&simple_trace_fn),
//     "Simple trace file name")
//
//  msg->imsg("results_fn",   po::value<string>(&simple_trace_fn),
//     "Prediction results file name")
//
//  msg->imsg("load_full_trace", po::bool_switch(&load_full_trace),
//     "")
//
//  msg->imsg("convert_full_trace", po::bool_switch(&convert_full_trace),
//     "requires full trace and simple trace file names")
//
//  msg->imsg("run_prediction", po::bool_switch(&run_prediction),
//     "requires simple trace file and results file name")
//
//  msg->imsg("END Options::query_options()");
}
