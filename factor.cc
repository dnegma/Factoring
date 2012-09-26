#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>
#include <time.h>

using std::cin;
using std::cout;
using std::queue;
using std::endl;

#define DEBUG 1

#if DEBUG
#define DEBUGPRINT(...)	gmp_printf( __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif

gmp_randstate_t state;

mpz_class mod(mpz_class a, mpz_class b) {
	mpz_class ret;
	mpz_mod(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
	return ret;
}

mpz_class random(mpz_class N) {
	mpz_class random;
	mpz_urandomm(random.get_mpz_t(), state, N.get_mpz_t());
	return random;
}

mpz_class gcd(mpz_class a, mpz_class b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

mpz_class pollard (mpz_class N) {
	srand(time(NULL));
	mpz_class x = random(N);
	mpz_class y = x;
	
	int i = 1, k = 2;
	mpz_class a = 1;
	while (N >= 0) {
			i++;
			x = mod((x * x + 1), N);
			y = mod((y * y + 1), N);
			y = mod((y * y + 1), N);

			a = a*(x - y);
			DEBUGPRINT("x: %Zd a: %Zd y: %Zd\n", x.get_mpz_t(), a.get_mpz_t(), y.get_mpz_t());
			mpz_class d = gcd(N, abs(a));

			DEBUGPRINT("N = %Zd\n", N.get_mpz_t());
			DEBUGPRINT("gcd=%Zd d>1 && d<N -> %d\n", d.get_mpz_t(), (d > 1 && d < N));
			if (d > 1 && d < N)
				return d;
	}
return 0;
}

void factor(mpz_class N) {
	queue<mpz_class> q;
	q.push(N);

	while (!q.empty()) {
		mpz_class value = q.front();

		int is_prime = mpz_probab_prime_p(value.get_mpz_t(), 10);
		DEBUGPRINT("Prime function returned %d\n", is_prime);

		if (is_prime >= 1) {
			cout << value << endl;
		} else {
			mpz_class factor = pollard(value);
			mpz_class factor2 = value / factor;
			DEBUGPRINT("Found factor 1: %Zd 2: %Zd\n",factor.get_mpz_t(), 
														factor2.get_mpz_t()	);
			q.push(factor);
			q.push(factor2);
		}
		DEBUGPRINT("Ending factor...\n");
		q.pop();
	}
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	DEBUGPRINT("Starting Program\n");

	gmp_randinit_default(state);
	mpz_class N;
	DEBUGPRINT("Waiting for input...\n");
	while (std::cin >> N)
		factor(N);

	return 0;
}
