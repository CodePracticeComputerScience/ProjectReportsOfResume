#include "header.hpp"

#define MAX_MEM_SIZE 100000000  //Maximum size of entire memory 2MB
#define MAX_PROCESS 50 //Maximum number of processes


#define MIN_PROCESS_SIZE 10240  //Minimum size of entire memory  10kB
#define MAX_PROCESS_SIZE 2048000 //Maximum size of process 2MB

#define MAX_CYCLES 2500
#define MIN_CYCLES 200


#define NUMBER_OF_BASIC_BLOCKS 102400 //This is 100MB
#define NUMBER_OF_BYTES (1024 * 102400) //104857600 10kB for each block so 102400 blocks
//char memory[10000000]; //Testing 10bytes
char main_memory[NUMBER_OF_BASIC_BLOCKS]; //Just using 8bytes for now
const char separator = ' ';
const int nameWidth     = 6;
const int numWidth      = 8;
auto num_free_blocks(0);
auto num_allocated_blocks(0);
long long int start_time, end_time;

vector<long long int> test_malloc_static;
vector<long long int> test_malloc_dynamic;
vector<long long int> test_free_static;
vector<long long int> test_free_dynamic;
vector<long long int> test_malloc_1;
vector<long long int> test_free_1;

vector<long long int> test_malloc_2;
vector<long long int> test_free_2;


template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
}



inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (
      "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx");
    return (uint64_t)hi << 32 | lo;
}


template <class ForwardIterator>
   ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last)
{
  if (first != last)
  {
    ForwardIterator next=first; ++next;
    while (next != last) {
      if (*first == *next)     // or: if (pred(*first,*next)), for version (2)
        return first;
      ++first; ++next;
    }
  }
  return last;
}


typedef struct basic_block
{
	int basic_block_size;
	int pid;
	int unique_id;
	bool free;
	//struct basic_block* next;
}basic_block;

typedef struct dynamic_block
{
	int basic_block_size;
	int pid;
	int unique_id;
	bool free;
}dynamic_block;


typedef struct process
{
	int pid; 
	int cycles;
	int memory_size;
	int blocks;
	int leftover;
	//int blocks = ceil(float(memory_size)/ float(10240));
	void process_func(){
		printElement(pid , nameWidth);
		printElement("      ", nameWidth);
		printElement(cycles, nameWidth);
		printElement("      ", nameWidth);
		printElement(memory_size, nameWidth);
		cout << endl;
		cout << "------------------------------------------------------|"<< endl;
	}
}process;
//typedef struct process_block;

//process_block FreeList just 1 
//vector<basic_block> freelist; 
vector<basic_block> MainMemory; //Initialize freelist
//vector<vector<basic_block>> Allocated_list; //
vector<process> process_ready_queue;
vector<process> active_processes;


vector<dynamic_block> Dynamic_Partitioned_Memory;
void initialize_dynamic_memory(int num_of_blocks, int pid, int leftover)
{
	//for (int i = 0; i < num_of_blocks; i++)//1024000000; i++)
	//{
		dynamic_block current_block;
		current_block.basic_block_size = (num_of_blocks * 10240);//size of process m m ;
		current_block.pid = pid;
		current_block.free = false;
		Dynamic_Partitioned_Memory.push_back(current_block);

	//}
	if (leftover >0)
	{	dynamic_block leftover_block;
		leftover_block.basic_block_size = leftover;
		leftover_block.pid = pid;
		leftover_block.free = false;
		Dynamic_Partitioned_Memory.push_back(leftover_block);
	}
}

void initialize_left_over_dynamic()
{

}
void initialize_main_memory()
{
	for (int i=0; i < NUMBER_OF_BASIC_BLOCKS; i++) //16 blocks 
	{
		basic_block current_block;
		current_block.free = true;
		current_block.pid = -1;
		current_block.basic_block_size = 10240;// * sizeof(char); //(sizeof(char) / 4);
		MainMemory.push_back(current_block);
		//freelist.push_back(true);
	}
	//Allocated_list.clear();
} 

void generate_processes()
{
	srand((unsigned) time(0));
	for(int i=0; i < 50; i++) //Generate 50 proceses
	{
		
		process thisprocess;
		thisprocess.pid = i;
		thisprocess.cycles = rand() % (MAX_CYCLES-MIN_CYCLES) + MIN_CYCLES; //random number from 200 to 2500
		thisprocess.memory_size = rand() % (MAX_PROCESS_SIZE - MIN_PROCESS_SIZE) + MIN_PROCESS_SIZE;
		process_ready_queue.push_back(thisprocess);
	}
}

inline bool IsAllocated(basic_block p) { return (p.free==false);}

void binary_rotate()
{
	//int i=0;
	std::vector<basic_block>::iterator bound;
	bound = std::partition(MainMemory.begin(), MainMemory.end(), IsAllocated);  //Partition MainMemory with allocated and not allocated
	auto i(0), j(0);
}
inline bool IsAllocated2(dynamic_block p) { return (p.free==false);}
void binary_rotate2()
{
	vector<dynamic_block> :: iterator bound;
	bound = std::partition(Dynamic_Partitioned_Memory.begin(), Dynamic_Partitioned_Memory.end(), IsAllocated2);
	;;;;
}
void flip2()
{
	binary_rotate();
}
void flip()
{
	binary_rotate();
}
void mymalloc2(process *thisprocess)
{
	auto j(0);
	long long int diff;
	long long int start;
	long long int end;

	start = rdtsc();
	initialize_dynamic_memory(thisprocess->blocks, thisprocess->pid, thisprocess->leftover);
	end = rdtsc();
	printElement(end-start, nameWidth);
	test_malloc_dynamic.push_back(end-start);
	printElement("                  ", nameWidth);
	//cout << endl;

}

void myfree2(process thisprocess)
{
		auto j(0);
		long long int diff;
		long long int end; 
		long long int start = rdtsc();
		for(auto& i : Dynamic_Partitioned_Memory)
		{
			if((i.free != true) && (i.pid == thisprocess.pid)) //I could have just deleted the whole memory but that is not necessary because we are just assigning a pointer
			{
				i.free = true;
				i.pid = -1; 
				i.basic_block_size = 10240;
			}
			end = rdtsc();
			printElement(end -start, nameWidth);
			test_free_dynamic.push_back(end-start);
			cout << endl;
			break;	
		}
	
}

void mymalloc(process *thisprocess)//, process active_process)
{
	auto j(0);
	long long int diff; 
	start_time = rdtsc();
	for(auto& i : MainMemory)
	{
		j++;
		i.free = false;
		i.pid = thisprocess->pid;
		//iter_alloc.push_back(i);
		if (j == thisprocess->blocks) 
		{
			end_time =rdtsc();
			printElement(end_time - start_time  , nameWidth);
			test_malloc_static.push_back(end_time-start_time);
			printElement("                  ", nameWidth);
			//cout << endl;
			break;
		}
	}//Allocated_list.push_back(iter_alloc);
}


void myfree(process thisprocess)
{
		auto j(0);
		long long int diff;
		long long int end; 
		long long int start = rdtsc();
		for(auto& i : MainMemory)
		{
			if((i.free != true) && (i.pid == thisprocess.pid))
			{
				i.free = true;
				i.pid = -1;
				j++;

			}
			if(j == thisprocess.blocks)
			{
				end = rdtsc();
				printElement(end -start, nameWidth);
				test_free_static.push_back(end-start);
				cout << endl;
				break;
			}
		}
}

void test_process_initialization()
{
	printElement("PROCESS NUMBER", nameWidth);
	printElement("  ", nameWidth);
	printElement("ID" , nameWidth);
	printElement("  ", nameWidth);
	printElement("CYCLES", nameWidth);
	printElement("  ", nameWidth);
	printElement("MEMORY SIZE", nameWidth);
	cout << endl;
	cout << "------------------------------------------------------|"<< endl;
	for(int i=0; i < 50; i++)
	{
		//cout << "process_ready_queue[" << i << "]" <<"--"<<process_ready_queue[i].pid << "--" <<process_ready_queue[i].cycles <<"--"<<process_ready_queue[i].memory_size << endl;
		printElement(i, nameWidth);
		printElement("              ", nameWidth);
		printElement(process_ready_queue[i].pid , nameWidth);
		printElement("      ", nameWidth);
		printElement(process_ready_queue[i].cycles, nameWidth);
		printElement("      ", nameWidth);
		printElement(process_ready_queue[i].memory_size, nameWidth);
		cout << endl;
		cout << "------------------------------------------------------|"<< endl;
	}
}


void test_memory_initialization()
{

	cout << endl;
	cout << "------------------------------------------------------|"<< endl;
	for(int i=0; i < 102400; i++)
	{
		if( (i % 32) != 0)//320)
		{
			printElement("|", 1);
			printElement(MainMemory[i].free, 1);
			printElement("|", 1);
		}
		else
		{ 
			cout << endl;
		}
	}
	cout << endl;
}
void print_memory()
{

}
