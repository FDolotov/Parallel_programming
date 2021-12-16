#include <iostream>
#include <iomanip>


#include <immintrin.h>
#include <chrono>
#include <cmath>


static inline uint64_t rdtsc() 
{
	uint64_t tsc;

    	asm volatile (
		"rdtscp; "
		"shl $32,%%rdx; "
		"or %%rdx,%%rax"
		: "=a"(tsc) :
		: "%rcx", "%rdx", "memory");

    return tsc;
};

void print_head()
{
	std::cout << std::setw(18) << std::left << "Iterations" << std::setw(18) << std::left << "time" 
		<< std::setw(18) << std::left << "Operations / sec" << std::setw(18) << std::left << "Processor tacts"
		<< std::setw(18) << std::left << "Proc. tacts / sec\n"; 
}

int main() 
{
	std::cout << "Simple division\n";

	print_head();	

	double buff1, buff2, buff3;
        
	for (uint16_t i = 0; i < 9; ++i) 
	{
		buff1 = 120.36;
		buff2 =7.9;

		uint32_t rounds = pow(10, i);
        
	    	auto start = std::chrono::system_clock::now();
        
	    	uint64_t t1 = rdtsc();
        
	    	for (uint32_t j = 0; j < rounds; ++j) 
	    	{
                	buff3 = buff1 / buff2;
            	};
        
	    	uint64_t t2 = rdtsc();
        
	    	std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
        
	    	double seconds = duration.count();
            	double operations_per_second = rounds / seconds;
            	uint64_t processor_clocks = t2 - t1;
            	double processor_clocks_per_second = processor_clocks / seconds;
 
		std::cout << std::setw(18) << std::left << rounds << std::setw(18) << std::left <<  seconds << std::setw(18) 
		<< std::left << operations_per_second << std::setw(18) << std::left << processor_clocks << std::setw(18) << 
		std::left <<  processor_clocks_per_second << '\n';
        
	};
        
	std::cout << "\n\n";

	std::cout << "SSE2 division\n";

	print_head();

	const double arr1[2] = {120.38, 120.38};
	const double arr2[2] = {7.9, 7.9};

	__m128d buff11;
	__m128d buff22;
	__m128d buff33;
        
        for (uint16_t i = 0; i < 9; ++i) 
	{
		buff11 = _mm_setzero_pd();
		buff22 = _mm_setzero_pd();
		buff33 = _mm_setzero_pd();
	
		buff11 = _mm_load_pd(&arr1[0]);
        	buff22 = _mm_load_pd(&arr2[0]);
 
	    	uint32_t rounds = pow(10, i);
        
	    	auto start = std::chrono::system_clock::now();
        
	    	uint64_t  t1 = rdtsc();
        
	    	for (uint32_t j = 0; j < rounds / 2; ++j) 
	    	{
			buff33 = _mm_div_pd(buff11, buff22);
            	};
        
	    	uint64_t t2 = rdtsc();
        
	    	std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
        
	    	double seconds = duration.count();
            	double operations_per_second = rounds / seconds;
            	uint64_t processor_clocks = t2 - t1;
            	double processor_clocks_per_second = processor_clocks / seconds;
  
		std::cout << std::setw(18) << std::left << rounds << std::setw(18) << std::left <<  seconds << std::setw(18) 
		<< std::left << operations_per_second << std::setw(18) << std::left << processor_clocks << std::setw(18) << 
		std::left <<  processor_clocks_per_second << '\n';
        
        
        };
        
	std::cout << "\n\n";

	std::cout << "AVX2 division\n";

	print_head();

	alignas(32) const double arr11[4] = {120.36, 120.36, 120.36, 120.36};
	alignas(32) const double arr22[4] = {7.9, 7.9, 7.9, 7.9};

	__m256d buff111;
	__m256d buff222;
	__m256d buff333;

        for (uint16_t i = 0; i < 9; ++i) 
	{
            	buff111 = _mm256_load_pd(&arr11[0]);
            	buff222 = _mm256_load_pd(&arr22[0]);
            
	    	uint32_t rounds = pow(10, i);
            
	    	auto start = std::chrono::system_clock::now();
            
	    	uint64_t t1 = rdtsc();
            
	    	for (uint32_t j = 0; j < rounds / 4; ++j) 
	    	{
                	buff333 = _mm256_div_pd(buff111, buff222);
            	};
            
	    	uint64_t t2 = rdtsc();
            	
	    	std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
            
	    	double seconds = duration.count();
            	double operations_per_second = rounds / seconds;
            	uint64_t processor_clocks = t2 - t1;
            	double processor_clocks_per_second = processor_clocks / seconds;
  
		std::cout << std::setw(18) << std::left << rounds << std::setw(18) << std::left <<  seconds << std::setw(18) 
		<< std::left << operations_per_second << std::setw(18) << std::left << processor_clocks << std::setw(18) << 
		std::left <<  processor_clocks_per_second << '\n';
        
            
        };

	std::cout << '\n';

	return 0;
};
