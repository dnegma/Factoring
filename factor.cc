#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>

using std::cin;
using std::cout;
using std::queue;

gmp_randstate_t state;

mpz_class random(mpz_class N) {
	mpz_class random;
	mpz_urandomm(random.get_mpz_t(), state, N.get_mpz_t());
	return random;
}

mpz_class pollard (mpz_class N) {
	srand(2342);
	mpz_class x = random(N);
	mpz_class y = x;
	

	while (true) {
			mpz_class sum = y - x;
			mpz_class d;
			mpz_class absolute = abs(sum);
			mpz_gcd(d.get_mpz_t(), N.get_mpz_t(), absolute.get_mpz_t());
			
			if (d > 1 && d < N)
				return d;
	}
}

void factor(mpz_class N) {
	
	queue<mpz_class> q;
	q.push(N);

	while (!q.empty()) {
		
		mpz_class value = q.front();

		if (mpz_probab_prime_p(value.get_mpz_t(), 10) >= 1){
			std::cout << value << "\n"; 
		} else {
			mpz_class factor = pollard(value);
			q.push(factor);
			q.push(value / factor);
		}
		q.pop();
	}
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	gmp_randinit_default(state);
	mpz_class N;
	while (std::cin >> N)
		factor(N);
	return 0;
}
