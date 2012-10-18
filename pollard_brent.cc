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
 
#define CUT_OFF_LIMIT 2000
 
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

bool is_power (int  i) {
	int pow = 1;
	while (pow <= i) {
		if (pow == i)
			return true;
		pow *= 2;
	}
	return false;
}

mpz_class min(mpz_class a, mpz_class b){
	if(a<b){
		return a;
	}
	return b;
}

struct timer{
	int time;
	bool should_break(){return time >= CUT_OFF_LIMIT;}
	timer operator++(int){
		time++;
		return *this;
	}
};
timer t;

mpz_class pollard(mpz_class N){
	if (mod(N,2) == 0) return 2;
	gmp_randseed_ui(state, time(NULL));
	mpz_class y,m,c;
	m = random(N);
	c = random(N);
	y = random(N);
	mpz_class g=1, r=1, q=1;
	mpz_class x, ys;

	

	while (g == 1){
		x = y;
		for(mpz_class i =0 ; i <= r ; ++i){
			y = mod((y*y+c),N);
		}
		mpz_class k = 0;
		while (k<r && g==1){
			ys = y;
			mpz_class min_v = min(m,r-k);
			for(mpz_class j = 0 ; j <= min_v ; ++j){
				y =mod((mod(y*y,N)+c),N);
				q = q*mod((abs(x-y)),N);
				if(t.should_break()) return 0;
				t++;
			}
			g = gcd(q,N);
			k = k+m;

			// cout << "t1: "<<  t.time << " ";
		}
		r = r*2;

	}
	if(g==N){
		while (true){
			ys = mod(mod(ys*ys, N)+c, N);
			g = gcd(abs(x-ys), N);
			if (g>1) break;
			if(t.should_break()) return 0;
			t++;
			// cout << "t2: "<<  t.time << " ";
		}
	}
	return g;
}

mpz_class brute_force(mpz_class N) {
	if(N == 1) return 0;
	if(mod(N,2) == 0){return 2;}
 	long int n = mpz_get_ui(N.get_mpz_t());
	double root = ceil(sqrt(n));
//	cout << "N = " << N.get_mpz_t() << "n = " << n << " Root = " << root << "\n";
	for (int i = 3; i <= root; i++){
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
			cout << "Factoring value = " << value << "\n";
			factor = (value > 10) ? pollard(value) : brute_force(value);
			if(factor == 0){
				std::cout << "fail" << std::endl;
				// print_vector(v);
				break;
			}else{
				//DEBUGPRINT("Found factor 1: %Zd 2: %Zd\n",factor.get_mpz_t(), (value/factor).get_mpz_t());
				if(value != 1 || value != N){
					q.push(factor);
					q.push(value/factor);
				}
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
	while (std::cin >> N){
		t.time = 0;
		factor(N);
	}
 
	return 0;
}

