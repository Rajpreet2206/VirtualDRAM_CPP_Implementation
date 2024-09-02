#include<vector>
#include<cstdint>

class VirtualDRAM{
    private:
        std::vector<uint8_t> memory;
        size_t size;
    
    public:
        VirtualDRAM(size_t size_in_bytes): size(size_in_bytes), memory(size_in_bytes,0){}
        void write(size_t address, uint8_t values){
            if(address< size) memory[address]=value;
        }

        uint8_t read(size_t address) const {
            return (address < size) ? memory[address] : 0;
        }
};

class PIMOperation{
    public:
        virtual void execute(VirtualDRAM& dram) = 0;
        virtual ~PIMOperation()=default;
};

class BitWiseAND: public PIMOperation{
    private:
        size_t start_address;
        size_t end_address;

    public:
        BitWiseAND(size_t start, size_t end): start_address(start), end_address(end){}

        void execute(VirtualDRAM& dram) override{
            for(size_t i=start_address; i<end_address; i+=2){
                uint_8 result= dram.read(i) & dram.read(i+1);
                dram.write(i, result);
            }
        }
};


