#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <cmath>


/*
This is the version where we got most points(39)
uploaded as future reference
*/
 
using std::cin;
using std::cout;
using std::queue;
using std::endl;
 
#define DEBUG 0
 
#if DEBUG
#define DEBUGPRINT(...) gmp_printf( __VA_ARGS__)
#else
#define DEBUGPRINT(...)
#endif
 
#define CUT_OFF_LIMIT 12500
 
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
	int c = 1;
	mpz_class a = 1;
	mpz_class d;
	while (N >= 0) {
 
			x = mod((x * x + c), N);
			y = mod((y * y + c), N);
			y = mod((y * y + c), N);
			DEBUGPRINT("preinit a ::: x: %Zd a: %Zd y: %Zd\n", x.get_mpz_t(), a.get_mpz_t(), y.get_mpz_t());
			
			if ((x - y) != 0){
				a = mod(a*(x - y), N);
				d = gcd(N, abs(a));
 			}

			DEBUGPRINT("N = %Zd\n", N.get_mpz_t());
			DEBUGPRINT("gcd=%Zd d>1 && d<N -> %d\n", d.get_mpz_t(), (d > 1 && d < N));
			if (d > 1 && d < N)
				return d;
 
			if(i >= CUT_OFF_LIMIT) break;
			i++;
	}
return 0;
}
mpz_class brute_force(mpz_class N) {
 	long int n = mpz_get_ui(N.get_mpz_t());
	double root = ceil(sqrt(n));
//	cout << "N = " << N.get_mpz_t() << "n = " << n << " Root = " << root << "\n";
	for (int i = 2; i <= root; i++){
		if (n % i == 0)
			return i;
	}
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
			factor = (value > 100) ? pollard(value) : brute_force(value);
			if(factor == 0){
				std::cout << "fail" << std::endl;
				break;
			}else{
				DEBUGPRINT("Found factor 1: %Zd 2: %Zd\n",factor.get_mpz_t(), (value/factor).get_mpz_t);
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

