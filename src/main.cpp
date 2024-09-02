#include<iostream>

int main(){
    VirtualDRAM dram(1024);
    PIMController controller(dram);

    //Writing some data to DRAM
    for(size_t i=0; i<10; ++i){
        dram.write(i,i+1);
    }

    controller.queueOperation(std::make_unique<BitWiseAND>(0,10));
    
    //Executing all the queue operations
    controller.executeAll();

    for(size_t i=0; i< 10; i+=2){
        std::cout<<"Result at "<< i << " : " << static_cast<int>(dram.read(i)) << std::endl;
    }
    return 0;
}