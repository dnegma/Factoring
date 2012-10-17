/*
Pre-compiler functions related to debugging
*/

#if DEBUG
#define DEBUGPRINT2(...) gmp_printf(__VA_ARGS__)
#define DEBUGPRINT(...) DEBUGPRINT2("#" __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif
