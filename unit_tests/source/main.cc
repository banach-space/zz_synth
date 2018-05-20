//========================================================================
// FILE:
//    unit_tests/main.cc
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Testbench for the Enve
//
// License: GNU GPL v2.0
//========================================================================
#include <gtest/gtest.h>

//========================================================================
// UTILITIES
//========================================================================
bool is_opt(const char *const argv, const char *const opt) {
  return 0 == strncmp(opt, argv, strlen(opt));
}

struct ArgumentParser {
  ArgumentParser(const int *const argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
      if ((0 == strcmp("-h", argv[i])) || (0 == strcmp("--help", argv[i]))) {
        fprintf(stdout, "\nUnitSynth - additional information;\n\n");
        fprintf(stdout, "Command Line Options:\n");
        // fprintf(stdout, "  --option_name\n      Option description\n")
      // } else if (is_opt(argv[i], "--option_name=")) {
        // option_val = argv[i] + strlen("--option_name=");
      } else {
        fprintf(stdout,
                "WARNING: Unknown command line argument '%s' ignored!\n",
                argv[i]);
      }
    }
  }

  std::string option_val = "";
};

//========================================================================
// MAIN
//========================================================================
GTEST_API_ int main(int argc, char *argv[]) {
  // Let Google Test parse the arguments first
  ::testing::InitGoogleTest(&argc, argv);

  // Then, UnitSynth can handle any that are left
  ArgumentParser parser(&argc, argv);

  return RUN_ALL_TESTS();
}

//========================================================================
// End of file
//========================================================================
