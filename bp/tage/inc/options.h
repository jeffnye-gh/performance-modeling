// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
// https://github.com/jeffnye-gh/jnutils
// ---------------------------------------------------------------------------
#pragma once
#include <boost/program_options.hpp>
namespace po = boost::program_options;

struct Options
{ 
  // ----------------------------------------------------------------
  // singleton 
  // ----------------------------------------------------------------
  static Options* getInstance() {
    if(!instance) instance = new Options();
    return instance;
  }
  // ----------------------------------------------------------------
  // support methods
  // ----------------------------------------------------------------
  void build_options(po::options_description&,
                     po::options_description&,
                     po::positional_options_description&);

  bool check_options(po::variables_map&,
                     po::options_description&,
                     po::options_description&,
                     po::positional_options_description&,
                     bool);

  void setup_options(int,char**);

  void usage(po::options_description&,
             po::positional_options_description&);

  void version();
  void query_options();
  // ----------------------------------------------------------------
  // example options
  // ----------------------------------------------------------------
  bool _query_options;
  bool load_full_trace;
  bool convert_full_trace;

  bool load_simple_trace;
  bool run_prediction;

  std::string full_trace_fn;
  std::string simple_trace_fn;
  std::string results_fn;
  // ----------------------------------------------------------------
  // ----------------------------------------------------------------
  bool notify_error;
  po::variables_map vm;

  // more singleton 
  static Options *instance;
private:
  // ----------------------------------------------------------------
  // more singleton 
  // ----------------------------------------------------------------
  Options() {} //default
  Options(const Options&) = delete; //copy
  Options(Options&&)      = delete; //move
  Options& operator=(const Options&) = delete; //assignment
};

extern std::shared_ptr<Options> opts;
