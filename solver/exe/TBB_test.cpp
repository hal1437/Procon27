#include <iostream>
#include <tbb/tbb.h>

int main(){
	
	std::cout << "start" << std::endl;
	tbb::tick_count begin = tbb::tick_count::now();

	for(int i=0;i<1e5;i++){
		for(int j = 0;j<1e5;j++){

		}
	}

	std::cout << (tbb::tick_count::now()-begin).seconds() << std::endl;
	begin = tbb::tick_count::now();
	
	tbb::parallel_for( tbb::blocked_range<size_t>(0,1e5), 
		[=](const tbb::blocked_range<size_t>& r) {
			for(size_t i=r.begin(); i!=r.end(); ++i){
				for(int j=0;j<1e5;j++){
				}
			}
		}
	);
	std::cout << (tbb::tick_count::now()-begin).seconds() << std::endl;
	std::cout << "end" << std::endl;
}
