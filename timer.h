
struct timer{
	
	int times;
	int limit;
	timer(int t):limit(t){
		times = clock();
	}

	bool should_break(clock_t val2){
		clock_t ret = val2- times;
		times = val2;

		return ret >= limit;
	}
};
