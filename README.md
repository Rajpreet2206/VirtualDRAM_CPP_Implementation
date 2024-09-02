## Virutal DRAM-Processing-In-Memory

#### The code demonstrates the use of a Virtual DRAM (Dynamic Random Access Memory) and a PIM (Processing-in-Memory) Controller. The breakdown of the code is given below:
``` cpp
VirtualDRAM dram(1024);
PIMController controller(dram);
```
This creates a **VirtualDRAM** object with a size of **1024 bytes**.
And the second line creates a **PIMController** object and associates it with the VirtualDRAM object. Some data is written to the DRAM using  
```cpp
    for(size_t i=0; i<10; ++i){
        dram.write(i,i+1);
    }
    controller.queueOperation(std::make_unique<BitWiseAND>(0,10));
    controller.executeAll();
```
A **unique pointer** is created to a **BitWiseAND** operation and it is added to the queue of operations in the PIMController. The last line executes all the queued operations.  

The main program sets up a **VirtualDRAM** and a **PIMController** to simulate a Processing-in-Memory system. It writes some data to the DRAM, then queues a **BitWiseAND** operation on the data. The **executeAll()** function executes the queued operation, which likely performs a bitwise AND operation on the DRAM contents. Finally, the program reads and prints every other element from the DRAM to show the results of the bitwise AND operation.
Overall, the project demonstrates a basic usage of a Virtual DRAM and a PIM Controller, where a bitwise operation is performed on the data stored in the DRAM. This type of architecture can be useful for certain types of data-intensive computations, as it can potentially reduce the amount of data movement between the memory and the processor.