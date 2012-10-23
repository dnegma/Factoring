
#define CUT_OFF_LIMIT_UPPER 250000
#define CUT_OFF_LIMIT_LOWER 1000

struct timer{
	
	clock_t times;
	clock_t limit;

	void set_limit(clock_t l){
		if(l > CUT_OFF_LIMIT_UPPER){
			limit = CUT_OFF_LIMIT_UPPER;
		}else if(l < CUT_OFF_LIMIT_LOWER){
			limit = CUT_OFF_LIMIT_LOWER;
		}else{
			limit = l;
		}
	}

	timer(int t):limit(t){
		times = clock();
	}

	bool should_break(clock_t val2){
		clock_t ret = val2- times;
		// times = val2;
		// std::cout << ret << " " << (times) << std::endl;
		return ret >= limit;
	}

	clock_t breaked_at(clock_t val2){
		clock_t ret = val2- times;
		// times = val2;
		// std::cout << ret << " " << (times) << std::endl;
		return ret;
	}
};
