#include <iostream>
#include <gmpxx.h>

#define DEBUG 0

#if DEBUG
#define DEBUGPRINT(...)	gmp_printf( __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif

void factor(mpz_class N){

}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	DEBUGPRINT("Starting Program\n");

	//gmp_randinit_default(state);
	mpz_class N;
	DEBUGPRINT("Waiting for input...\n");
	while (std::cin >> N)
		factor(N);

	return 0;
}
