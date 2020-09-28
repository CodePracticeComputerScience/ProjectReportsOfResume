#include "my_malloc.hpp"
#include "header.hpp"

int main()
{
	int test_pid = 6;
	long long int *some_ticks;
	generate_processes();
	//initialize_dynamic_memory();
	
	process testproc;
	testproc.pid = 0;
	testproc.cycles = 575;
	testproc.memory_size = 346832;

	process *process_ptr = &testproc;
	
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "***********************************************TESTING MY MALLOC DYNAMIC PARTITIONED*******************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	cout << "*******************************************************************************************************************************"<<endl;
	
	//generate_processes();
	printElement("PROCESS ID ", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES", 3 + nameWidth);
	printElement("  ", nameWidth);
	printElement("BLOCKS", (2*nameWidth) + 10 );
	printElement("  ", nameWidth);
	printElement("MEMORY SIZE", nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR OUR MALLOC" , nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES FOR OUR MyFree" , nameWidth);
	//printElement("  ", nameWidth);
	//printElement("CYCLES FOR OUR FREE" , nameWidth);
	cout << endl;
	for (int i=0; i < 50; i++)
	{
		//cout <<"Blocks needed "<< ceil(float(process_ready_queue[i].memory_size / 10240)) << endl;
		process_ready_queue[i].blocks = floor( float(process_ready_queue[i].memory_size) / float(10240)); //Optimize this with macros
		process_ready_queue[i].leftover = (process_ready_queue[i].memory_size - (process_ready_queue[i].blocks) * 10240);
		printElement(process_ready_queue[i].pid, nameWidth);
		printElement("           ", nameWidth);
		printElement(process_ready_queue[i].cycles, nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].blocks, 0);
		printElement(" + ", 0);
		printElement(process_ready_queue[i].leftover, 2);
		printElement(" extra bytes", nameWidth);
		printElement("         ", nameWidth);
		printElement(process_ready_queue[i].memory_size, nameWidth);
		printElement("         ", nameWidth);
		//printElement(process_ready_queue[i].leftover, nameWidth);
		//printElement("         ", nameWidth);
		mymalloc2(&process_ready_queue[i]);
		
		
		//while((proc_tick_end - proc_tick_begin) <process_ready_queue[i].cycles)
		int j{0}, k{0};
		auto proc_tick_end = 0; 
		auto proc_tick_begin = rdtsc();
		//cout<<"Running Process with PID ["<<process_ready_queue[i].pid <<"]" << endl;
		for (auto i=0; i< process_ready_queue[i].cycles; i++)
		{	
				;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		}
		myfree2(process_ready_queue[i]);
		for(auto i=0; i < 50; i++)
		{
			;;//cout << "Fake Context Switch\n";
		}
		//while(k < 50)
		//{
		//	k++;
		//	proc_tick_end = rdtsc();
		//}

	}
	//cout << Dynamic_Partitioned_Memory.size() << endl;
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
		test_malloc_2.push_back(end_time_malloc - start_time_malloc);
		auto start_free = rdtsc();
		free(thisprocess);
		auto end_free = rdtsc();
		printElement(end_free - start_free  , nameWidth);
		test_free_2.push_back(end_free - start_free);
		cout << endl;
		//cout << "Malloc = " << end_time_malloc - start_time_malloc << endl;
	}

	cout << "************memory sizes*****************************"<<endl;
	for (auto& i : process_ready_queue)
	{
		cout << i.memory_size <<",";
	}
	cout << endl;
	cout << "***************************************************"<<endl;
	cout << "***********************Malloc static times ***************"<<endl;
	for (auto& i : test_malloc_dynamic)
	{
		cout << i <<",";
	}
	cout << "************************************************************"<<endl;
	cout <<"************************free*************************"<<endl;
	for (auto& i : test_free_dynamic)
	{
		cout << i <<",";
	}
	cout << endl;
	cout << "************************************************************"<<endl;
	cout << "****************gnu malloc***************************"<<endl;
	for (auto& i : test_malloc_2)
	{
		cout << i <<",";
	}
	cout << endl;
	cout << "************************************************************"<<endl;
	cout << "****************gnu free***************************"<<endl;
	for (auto& i : test_free_2)
	{
		cout << i <<",";
	}
	cout << endl;
	return 0;
}
