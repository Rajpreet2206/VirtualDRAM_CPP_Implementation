#include<memory>
#include<queue>

class PIMController{
    private:
        VirtualDRAM& dram;
        std::queue<std::unique_ptr<PIMOperation>> operation_queue;
    
    public:
        PIMController(VirtualDRAM& dram_ref) : dram(dram_ref){}

        void queueOperation(std::unique_ptr<PIMOperation> op){
            operation_queue.push(std::move(op));
        }

        void executeAll(){
            while(!operation_queue.empty()){
                operation_queue.front() -> execute(dram);
                operatoin_queue.pop();
            }
        }
};

