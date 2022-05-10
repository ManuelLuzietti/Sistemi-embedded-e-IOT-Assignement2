#ifndef __MACHINEMODEL__
#define __MACHINEMODEL__
#define NPROD  3
#define NMAX 1
enum MachineStates
    {
        Idle,
        Working,
        Assistance
    } ;
String machineStatesString[NPROD] = {"Idle","Working","Assistance"};

class MachineModel{
    int nproducts = NPROD;
    int qty[NPROD];
    int maxQtyProd = NMAX;
    String productNames[NPROD] = {"Coffe","Tea","Chocolate"};
    int sugarLevel;
    MachineStates machineState;
    bool noProducts;
    int nTest;
    enum Products
    {
        Coffe,
        Tea,
        Chocolate
    } productSel;

    public:
    MachineModel(){
    }

    void init(){
        refill();
        sugarLevel = 0;
        productSel = Coffe;
        machineState = Idle;
        noProducts = false;
        nTest = 0;
    }

    void setWorkingState()
    {
        machineState = Working;
    }

    void setIdleState()
    {
        machineState = Idle;
    }

    void setAssistanceState()
    {
        machineState = Assistance;
    }

    void selectNextProduct(){
        
        for ( int i = 1;i <= NPROD;i++){
            int current = (productSel + i) % nproducts;
            if( qty[current]> 0){
                productSel = current;
                return;
            }
        }
        setAssistanceState();
    }

    void selectPrevProduct(){
        //productSel = (productSel-1 == -1) ? nproducts-1 : productSel - 1;
        int current = productSel;
        for ( int i = 1;i <= nproducts;i++){
            current = (current-1 == -1) ? nproducts-1 : current - 1;
            if( qty[current]> 0){
                productSel = current;
                return;
            }
        }
        setAssistanceState();
    }

    String getSelectedProduct(){
        return productNames[productSel];
    }
    int getNproducts(){
        int sum = 0;
        for(int i=0;i<nproducts;i++){
            sum += qty[i];
        }
        return sum;
    }
    int getNTest(){
        return nTest;
    }
    String getStatus(){
        return machineStatesString[machineState];
    }
    void incrementNTest(){
        nTest++;
    }
    int getSugarLevel(){
        return sugarLevel;
    }

    void setSugarLevel(int sugarLevel){
        this->sugarLevel = sugarLevel;
    }

    MachineStates getMachineState(){
        return machineState;
    }

    void selectCurrentProduct(){
        qty[productSel]--;
    }

    void refill(){
        for (int i = 0; i < nproducts; i++)
        {
            qty[i] = maxQtyProd;
        }
        setIdleState();
    }

    void recover(){
        setIdleState();
    }
};

#endif