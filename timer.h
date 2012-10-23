
#define CUT_OFF_LIMIT_UPPER 1000
#define CUT_OFF_LIMIT_LOWER 20

struct timer{
	
	clock_t times;
	clock_t limit;

	double diffclock(clock_t clock1,clock_t clock2){
		clock_t diffticks=clock1-clock2;
		// std::cout <<"Diff: "<< diffticks << " CLOCKS_PER_SEC: "<< CLOCKS_PER_SEC <<std::endl;
		double diffms=(double)(diffticks*1000)/CLOCKS_PER_SEC;
		return diffms;
	}

	void set_limit(clock_t l){
		// l = diffclock(l, times);
		limit = l;
	}

	timer(int t):limit(t){
		times = clock();
	}

	bool should_break(clock_t val2){
		clock_t ret = diffclock(val2,times);
		// times = val2;
		// std::cout << ret << " " << (limit) << std::endl;
		return ret >= limit;
	}

	clock_t breaked_at(clock_t val2){
		clock_t ret = val2- times;
		// times = val2;
		// std::cout << ret << " " << (times) << std::endl;
		return ret;
	}
};
