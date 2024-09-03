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

The class **VirtualDRAM** represents a virtual DRAM (Dynamic Random Access Memory) using **std::vector<uint_8>** to simulate memory storage. The constructor initializes the memory with a given size. It provides **write** and **read** methods to interact with the memory. In the main file, **VirtualDRAM dram(1024)** creates an instance of this class with 1024 bytes of memory. The main file uses **dram.write()** to store data and **dram.read()** to retrieve data. The **PIMOperation** class is an abstract base class for Processing-in-Memory operations. It declares a pure virtual **execute** method that subclass must implement. This is a base class for **BitWiseAND**. 

The **BitWiseAND** class inherits from **PIMOperation**. It implements a bitwise AND operation on a range of memory addresses. The **execute** method performs the AND operation on pairs of adjacent memory locations. In the main file, **std::make_unique<BitWiseAND>(0,10) creates an instance of this class. This operation is queued in the PIMController and later executed. 

The **PIMOperation** class is a crucial component in the Processing-in-Memory (PIM) system. The class manages a queue of PIM operations and executes them on a **VirtualDRAM** instance. It has a reference to a **VirtualDRAM** object and a queue of **PIMOperation** pointers. The constructor **PIMController(VirtualDRAM& dram_ref) : dram(dram_ref){}** takes to reference to a **VirtualDRAM** object, which it will use to execute operations. The method **queueOperation(std::unique_ptr<PIMOperation> op)** adds a new PIM operation to the queue. It takes ownership of the passed operation using a unique pointer. The method **executeAll()** executes all queued operations on the DRAM. It processes the queue until it's empty, executing each operation and then removing it fromt the queue. 

## Relationship between these classes and the main file:
1. The main file creates a **VirtualDRAM** object and uses it to store and retrieve data.
2. It also creates a **PIMController** that manages PIM operations on the **VirtualDRAM**.
3. The main file queues a **BitWiseAND** operation, which is a specific type of **PIMOperation**.
4. When **controller.executeAll()** is called in the main file, it triggers the **execute** method of the queued **BitWiseAND** operation, which performs the bitwise AND on the data in the **VirtualDRAM**.
5. Finally, the main file reads and prints the results of this operation from the **VirtualDRAM**.  

## Code Description
```cpp
class VirtualDRAM {
private:
    std::vector<uint8_t> memory;
    size_t size;
```

### This class simulates a Dynamic Random Access Memory (DRAM) using a vector of 8-bit unsigned integers (uint8_t). 
- **memory**: A vector of uint8_t, representing the actual storage.
- **size**: Stores the total size of the memory in bytes.

```cpp
public:
    VirtualDRAM(size_t size_in_bytes): size(size_in_bytes), memory(size_in_bytes,0){}
```

The constructor initializes the memory with a specified size, filling it with zeroes.

```cpp
void write(size_t address, uint8_t values){
        if(address < size) memory[address] = value;
    }
```
- **write** method: Writes a byte value to a specific address if the address is within bounds.

```cpp
uint8_t read(size_t address) const {
        return (address < size) ? memory[address] : 0;
    }
```
- **read** method: Reads a byte from a specific address and returns 0 if the address is out of bounds.

```cpp
class PIMOperation {
public:
    virtual void execute(VirtualDRAM& dram) = 0;
    virtual ~PIMOperation() = default;
};
```
The PIMOperation class is shown above for Processing-in-Memory operations.
- **execute**: A pure virtual function that subclasses must implement to define their operation.
- Virtual destructor: Allows proper cleanup of derived classes through base class pointer.

The BitWiseAND class below inherits from PIMOperation and implements a bitwise AND operation.
```cpp
class BitWiseAND: public PIMOperation {
private:
    size_t start_address;
    size_t end_address;
public:
    BitWiseAND(size_t start, size_t end): start_address(start), end_address(end){}
```
- **start_address** and **end_address**: Define the range of memory addresses to operate on. The constructor initializes the start and end addresses for the operation.

### This design allows for easy extension of the system with new types of PIM operations by creating new classes that inherit from **PIMOperation**. The separation of the memory interface **(VirtualDRAM)** from the operations **(PIMOperation and its subclasses)** provides flexibility and modularity in the system design. 