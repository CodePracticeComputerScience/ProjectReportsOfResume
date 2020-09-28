#include "my_malloc.hpp"
#include "header.hpp"




int main()
{
	int test_noOfBytes = 60910;
	int test_pid = 6;
	long long int *some_ticks;
	initialize_main_memory();
	generate_processes();
	flip();

	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "***********************************************TESTING MY MALLOC STATIC PARTITIONED*******************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	printElement("PROCESS ID ", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES", nameWidth);
	printElement("  ", nameWidth);
	printElement("BLOCKS", nameWidth);
	printElement("  ", nameWidth);
	printElement("MEMORY SIZE", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR OUR MALLOC" , nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR OUR FREE" , nameWidth);
	cout << endl;
	for (int i=0; i < 50; i++)
	{
		//cout <<"Blocks needed "<< ceil(float(process_ready_queue[i].memory_size / 10240)) << endl;
		process_ready_queue[i].blocks = ceil( float(process_ready_queue[i].memory_size) / float(10240)); //Optimize this with macros
		printElement(process_ready_queue[i].pid, nameWidth);
		printElement("           ", nameWidth);
		printElement(process_ready_queue[i].cycles, nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].blocks, nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].memory_size, nameWidth);
		printElement("         ", nameWidth);
		//cout << endl;
		mymalloc(&process_ready_queue[i]);//, some_ticks);
		for (auto i=0; i< process_ready_queue[i].cycles; i++)
		{	
				;;;;;;;
		}
		flip();
		for(auto i=0; i < 50; i++)
		{
			;;//cout << "Fake Context Switch\n";
		}
		myfree(process_ready_queue[i]);
		/*This is where we wait for 50 cycles before the next process */
		flip();
	}
	
	

	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "***********************************************TESTING GNU MALLOC**************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	printElement("PROCESS ID ", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES", nameWidth);
	printElement("  ", nameWidth);
	printElement("BLOCKS", nameWidth);
	printElement("  ", nameWidth);
	printElement("MEMORY SIZE", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR  MALLOC" , nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR FREE" , nameWidth);
	cout << endl;

	for (int i=0; i < 50; i++)
	{
		process *thisprocess = &process_ready_queue[i];
		printElement(process_ready_queue[i].pid, nameWidth);
		printElement("           ", nameWidth);
		printElement(process_ready_queue[i].cycles, nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].blocks, nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].memory_size, nameWidth);
		printElement("         ", nameWidth);

		auto start_time_malloc = rdtsc();
		thisprocess = (process*) malloc(process_ready_queue[i].memory_size * sizeof(process));
		//thisprocess = (process) malloc(sizeof(process));
		auto end_time_malloc = rdtsc();


		printElement(end_time_malloc - start_time_malloc  , nameWidth);
		printElement("                    "  , nameWidth);
		test_malloc_1.push_back(end_time_malloc - start_time_malloc);
		auto start_free = rdtsc();
		free(thisprocess);
		auto end_free = rdtsc();
		printElement(end_free - start_free  , nameWidth);
		test_free_1.push_back(end_free - start_free);

		cout << endl;
		//cout << "Malloc = " << end_time_malloc - start_time_malloc << endl;
	}


	
	/*Creating matlab script to plot */
	//cout << "legend('my malloc', 'my free', 'system malloc', 'system free');"<< endl;
	//cout << "title("Dynamic Partition Results");" <<endl;
	//cout << "xlabel("Memory Size");"<<endl;
	//cout << "ylabel("Ticks or CPU Cycles");"<<endl;
	// cout << "************memory sizes*****************************"<<endl;
	// for (auto& i : process_ready_queue)
	// {
	// 	cout << i.memory_size <<",";
	// }
	// cout << endl;
	// cout << "***************************************************"<<endl;
	// cout << "***********************Malloc static times ***************"<<endl;
	// for (auto& i : test_malloc_static)
	// {
	// 	cout << i <<",";
	// }
	// cout << "************************************************************"<<endl;
	// cout <<"************************free*************************"<<endl;
	// for (auto& i : test_free_static)
	// {
	// 	cout << i <<",";
	// }
	// cout << endl;
	// cout << "************************************************************"<<endl;
	// cout << "****************gnu malloc***************************"<<endl;
	// for (auto& i : test_malloc_1)
	// {
	// 	cout << i <<",";
	// }
	// cout << endl;
	// cout << "************************************************************"<<endl;
	// cout << "****************gnu free***************************"<<endl;
	// for (auto& i : test_free_1)
	// {
	// 	cout << i <<",";
	// }
	// cout << endl;
	return 0;
}
