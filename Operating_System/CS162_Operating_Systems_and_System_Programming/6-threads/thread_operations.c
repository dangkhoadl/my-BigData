
// Create a new thread to run func(arg)
thread_fork(func, arg);

// Given up processor for a while
thread_yield();

// In parent, wait for forked thread to exit
// then return
thread_join(thread);

// Quit thread and clean up
// wake up joiner if any
thread_exit();
