#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "timer.h"

#define DEBUG 0
#if DEBUG
#define DEBUGPRINT2(...) gmp_printf(__VA_ARGS__)
#define DEBUGPRINT(...) DEBUGPRINT2("#" __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif
/*
This is the version where we got most points(39)
uploaded as future reference
*/
 
using std::cin;
using std::cout;
using std::queue;
using std::endl;
 
#define CUT_OFF_LIMIT_HIGH 10500
#define CUT_OFF_LIMIT_LOW 9500
#define PRIMES 22
 
timer t(180);
int cut_off_limit;
gmp_randstate_t state;
int primes[22];
 
void init_primes() {
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	primes[3] = 7;
	primes[4] = 11;
	primes[5] = 13;
	primes[6] = 17;
	primes[7] = 19;
	primes[8] = 23;
	primes[9] = 29;
	primes[10] = 31;
	primes[11] = 37;
	primes[12] = 41;
	primes[13] = 43;
	primes[14] = 47;
	primes[15] = 53;
	primes[16] = 59;
	primes[17] = 61;
	primes[18] = 67;
	primes[19] = 71;
	primes[20] = 73;
	primes[21] = 79;
}

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
 
void print_vector(const std::vector<mpz_class>& v) {
	for(size_t i = 0; i < v.size() ; i++){
		std::cout << v[i] << "\n";
	}
}
 
mpz_class pollard (mpz_class N) {
	gmp_randseed_ui(state, time(NULL));
	mpz_class x = random(N);
	mpz_class y = x;
	
	int i = 1;
	mpz_class a = 1;
	mpz_class ab;
	while (N >= 0) {
 
			x = mod((x * x + 1), N);
			y = mod((y * y + 1), N);
			y = mod((y * y + 1), N);
			DEBUGPRINT("preinit a ::: x: %Zd a: %Zd y: %Zd\n", x.get_mpz_t(), a.get_mpz_t(), y.get_mpz_t());
			a = mod(a*(x - y), N);
			if(a==0) a=2;
			mpz_class d = gcd(N, abs(a));
 
			DEBUGPRINT("N = %Zd\n", N.get_mpz_t());
			DEBUGPRINT("gcd=%Zd d>1 && d<N -> %d\n", d.get_mpz_t(), (d > 1 && d < N));
			if (d > 1 && d < N)
				return d;
 
			if(t.should_break(clock())){
				//cout << "Breaking with time " << clock() << endl;
			 break;
			}
	}
return 0;
}
 
mpz_class brute_force(mpz_class N) {
	for (int i = 0; i < PRIMES; i++) {
		if (mod(N, primes[i]) == 0)
			return primes[i];
	}
	mpz_class root;
	mpz_sqrt(root.get_mpz_t(), N.get_mpz_t());
	if (root == N)
		return root;
	return 0;
}

void factor(mpz_class N) {
	queue<mpz_class> q;
	q.push(N);
	std::vector<mpz_class> v;
	mpz_class factor=9;
 
	while (!q.empty()) {
		mpz_class value = q.front();
 
		int is_prime = mpz_probab_prime_p(value.get_mpz_t(), 10);
		DEBUGPRINT("Prime function returned %d\n", is_prime);
 
		if (is_prime >= 1) {
			//cout << value << endl;
			v.push_back(value);
		} else {
			factor = brute_force(value);
			if (factor == 0)
				factor = pollard(value);
			if(factor == 0){
				std::cout << "fail" << std::endl;
				break;
			}else{
				// DEBUGPRINT("Found factor 1: %Zd 2: %Zd\n",factor.get_mpz_t(), (value/factor).get_mpz_t);
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
	int i = 1;
	cut_off_limit = CUT_OFF_LIMIT_HIGH;
	init_primes();
	t.set_limit(200);
	while (std::cin >> N) {

		if (i >= 50)
			t.set_limit(200);
		
		factor(N);
		t.times = clock();		
		i++;
	}
	return 0;
}
