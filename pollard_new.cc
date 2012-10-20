#include <iostream>
#include <queue>
#include <gmpxx.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <cmath>
#include "timer.h"

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
 
#define CUT_OFF_LIMIT 10000
timer t(CUT_OFF_LIMIT);
 
gmp_randstate_t state;
int prime_array[100];

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

bool is_power (int  i) {
	int pow = 1;
	while (pow <= i) {
		if (pow == i)
			return true;
		pow *= 2;
	}
	return false;
}

mpz_class modPow(mpz_class a, long b, mpz_class N) {
	mpz_class ans = 1;
	a = mod(a, N);
	long k = 1;	
	while (true){
		if (pow(2, k) > b)
			return ans;
		//long pow = pow(2,i);
		//cout << "before if " << endl;
		long pow_two = (long) pow(2, k);
		cout << "b = " << b << " pow_two = " << pow_two << " bool = " << ((b & pow_two) == 0) << endl;
		if (!((b & pow_two) == 0)) {
			cout << "ans = " << ans.get_mpz_t() << " a = " << a << " N = " << N << endl;
			ans = mod((ans * a), N);
		}
		a = mod(a*a, N);
		k++;
	}
}

mpz_class pollard (mpz_class N) {
	gmp_randseed_ui(state, time(NULL));
	
	if (mod(N, 2) == 0) 
		return 2;
	
	mpz_class two_k_fact = 2;
	mpz_class d;
	mpz_class k = 1;
	while (true) {
	//	cout << "Pollard while loop N = " << N << endl;
		mpz_powm(two_k_fact.get_mpz_t(), two_k_fact.get_mpz_t(), k.get_mpz_t(), N.get_mpz_t());
		d = gcd(two_k_fact-1, N);
		if ( d > 1 && d < N)
			return d;
		k++;
		if (t.should_break(clock())) 
			break;
	}
	return 0;
}
/*
mpz_class brent (mpz_class N) {
	gmp_randseed_ui(state, time(NULL));
	if (mod(2, N) == 0)
		return 2;
	mpz_class y = random(N);
	mpz_class c = random(N);
	mpz_class m = random(N);
	mpz_class d = 1;
	int r = 1;
	mpz_class q = 1;
	mpz_class ys, x;

	while (d == 1) {
		x = y;
		for (int i = 0; i < r; i++)
			y = mod(mod((y*y),(N+c)), N);
		int k = 0;
		while ( k < r && d == 1) {
			ys = y;
			for (int i = 0; i < min(m, r-k) {
				y = mod(mod((y*y),(N+c)), N);
				q = mod(q*(abs(x-y)), N);
			}
			d = gcd(q, N);
			k = k + m;
		}
		r = r*2;
	}
	if (d == N) {
		while (true) {
			y = mod(mod((y*y),(N+c)), N);
			d = gcd(abs(x-ys),N);
			if (d > 1)
				break;
	return d;
}
*/
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
			//cout << "Factoring value = " << value << "\n";
			factor = (value > 10000) ? pollard(value) : brute_force(value);
			if(factor == 0){
				std::cout << "fail" << std::endl;
				//print_vector(v);
				break;
			}else{
				//DEBUGPRINT("Found factor 1: %Zd 2: %Zd\n",factor.get_mpz_t(), (value/factor).get_mpz_t());
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
void init_prime_array(){
	
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);


	init_prime_array();
	DEBUGPRINT("Starting Program\n");
 
	gmp_randinit_default(state);
	mpz_class N;
	DEBUGPRINT("Waiting for input...\n");
	while (std::cin >> N)
		factor(N);
 
	return 0;
}

