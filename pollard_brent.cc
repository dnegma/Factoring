#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>
#include <time.h>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::endl;

#define DEBUG 0
#define TEST_CASE 0

#if DEBUG
#define DEBUGPRINT(...)	gmp_printf( __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif

#define CUT_OFF_LIMIT 10000

gmp_randstate_t state;

mpz_class mod(mpz_class a, mpz_class b) {
	mpz_class ret;
	mpz_mod(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
	return ret;
}

void print_vector(const std::vector<mpz_class>& v) {
	for(size_t i = 0; i < v.size() ; i++){
		std::cout << v[i] << "\n";
	}
}

mpz_class gcd(mpz_class a, mpz_class b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

bool is_power (int i) {
	int pow = 1;
	while (pow <= i) {
		if (pow == i)
			return true;
		pow = pow * 2;
	}
	return false;
}
mpz_class brent(mpz_class N){
	gmp_randseed_ui(state, time(NULL));
	mpz_class power_two = 1;
	int lap_number = 1;
	mpz_class xi = 2; //random(N);
	mpz_class xm = 2;

	int i = 1;
	int c = 1;

	while (true){
		xi = mod((xi * xi + c), N);
		mpz_class a = xi-xm;
		mpz_class d = gcd(N, abs(a));
		DEBUGPRINT("N = %Zd, xi = %Zd, xm = %Zd, d = %Zd, c = %d\n", N.get_mpz_t(), xi.get_mpz_t(), xm.get_mpz_t(), d.get_mpz_t(), c);

		if (d > 1 && d < N)
			return d;

		if(is_power(lap_number)){
			xm = xi;
		}

		lap_number +=1;
		if(i >= CUT_OFF_LIMIT) break;
		i++;
	}

	return 0;
}

void factor(mpz_class N) {
	queue<mpz_class> q;
	q.push(N);
	std::vector<mpz_class> v;
	mpz_class factor=9;
	if(TEST_CASE == 1){
		cout << "Value: " << N.get_mpz_t() << endl;
	}

	while (!q.empty()) {
		mpz_class value = q.front();

		int is_prime = mpz_probab_prime_p(value.get_mpz_t(), 10);
		DEBUGPRINT("Prime function returned %d\n", is_prime);

		if (is_prime >= 1) {
			v.push_back(value);
		} else {
			factor = brent(value);
			if(factor == 0){
				cout << "fail" << "\n";
				break;
			}else{
				q.push(factor);
				q.push(value/factor);
			}
		}
		DEBUGPRINT("Ending factor...\n");
		q.pop();
	}

	if(factor!=0){
		print_vector(v);
	}
	cout << endl;
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

