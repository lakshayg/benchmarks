#pragma once

// Common initialization routine. This does not include the
// headers deliberately so that we do not add dependencies to
// the user's code. The user is expected to include all the
// necessary dependecies for the function they are using.

#define LG_INIT_GLOG(_argc, _argv)                                             \
  do {                                                                         \
    FLAGS_logtostderr = 1;                                                     \
    google::InitGoogleLogging(_argv[0]);                                       \
    google::InstallFailureSignalHandler();                                     \
  } while (false)
