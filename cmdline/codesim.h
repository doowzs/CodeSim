#ifndef CMDLINE_CODESIM_H
#define CMDLINE_CODESIM_H

#include "app/config.h"

void print_usage_and_exit [[noreturn]] ();
bool try_parse_cmdline_args(int argc, const char **argv, Config *config);

#endif//CMDLINE_CODESIM_H
