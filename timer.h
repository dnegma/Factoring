
#define CUT_OFF_LIMIT_UPPER 1000
#define CUT_OFF_LIMIT_LOWER 20

class timer{
	public:
	clock_t times;
	clock_t limit;

	timer(int t):limit(t){
		times = clock();
	}

	timer(){
		times = clock();
	}

	double diffclock(clock_t clock1,clock_t clock2){
		clock_t diffticks = clock1 - clock2;
		//std::cout <<"Diff: "<< diffticks << " CLOCKS_PER_SEC: "<< CLOCKS_PER_SEC <<std::endl;
		double diffms=(double)(diffticks*1000)/CLOCKS_PER_SEC;
		return diffms;
	}

	void set_limit(clock_t l){
		// l = diffclock(l, times);
		limit = l;
	}

	void reset(){
		times = clock();
	}

	bool should_break(){
		clock_t ret = diffclock(clock(),times);
		return ret >= limit;
	}

	/*DEPRECATED REMOVE WHEN NOT USED ANYMORE*/
	bool should_break(clock_t val2){
		clock_t ret = diffclock(clock(),times);
		return ret >= limit;
	}

	clock_t time_taken_in_ms(){
		clock_t ret = diffclock(clock(),times);
		std::cout << "It took " << ret << std::endl;
		return ret;
	}

	/*DEPRECATED REMOVE WHEN NOT USED ANYMORE*/
	clock_t time_taken_in_ms(clock_t val2){
		clock_t ret = diffclock(clock(),times);
		std::cout << "It took " << ret << std::endl;
		return ret;
	}
};
