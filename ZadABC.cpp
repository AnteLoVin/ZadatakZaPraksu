#include <iostream>
#include <future>
#include <Windows.h>
#include <thread>



class cyclicPrint
{
    bool* aP, * bP, * cP;
    bool functionStop = false;


    public:void GetAddresses(bool** address)
    {
        aP = address[0];
        bP = address[1];
        cP = address[2];
    }

    public:void Start()
      {
          while (!functionStop)
          {
              printf("\nA %s\nB %s\nC %s\n-------\n", ((*aP) ? "upaljeno" : "ugaseno"), ((*bP) ? "upaljeno" : "ugaseno"), ((*cP) ? "upaljeno" : "ugaseno"));
              Sleep(5000);

          }
      }

    void stopSignal()
    {
        functionStop = true;
    }
};



class signalClass
{
    bool a = true, b = true, c = true;
    bool* pointerArray[3] = { &a, &b, &c };

    public:bool** GetArrayAddress() 
    {
        return &pointerArray[0];
    }

    public:void TurnOff(std::string input)
    {
        std::string temp = input.c_str();
        int i = 0;
        printf_s("Gasenje : %s", temp.c_str());
        if (temp._Equal("A"))
            i += 1;
        if (temp._Equal("B"))
            i += 2;
        if (temp._Equal("C"))
            i += 3;

        switch (i)
        {
        case 1:
            Sleep(2000);
            a = false;
        case 2:
            Sleep(2000);
            b = false;
        case 3:
            Sleep(2000);
            c = false;
        default:
            signalClass::TurnOn();
            break;
        }


    }

    void TurnOn()
    {
        int j = 3;
        if (a)
            j -= 1;
        if (b)
            j -= 1;
        if (c)
            j -= 1;

        switch (j)
        {
        case 3:
            Sleep(2000);
            a = true;
        case 2:
            Sleep(2000);
            b = true;
        case 1:
            Sleep(2000);
            c = true;
        default:
            break;
        }
    }

};




int main()
{
    std::string unos;
    signalClass setSignala;
    cyclicPrint printing;
    printing.GetAddresses(setSignala.GetArrayAddress());
    std::thread parallelPrint([&printing]() {printing.Start(); });
    
    std::cin >> unos;
    while (unos != "stop")
    {
        if (unos == "A" || unos == "B" || unos == "C")
            setSignala.TurnOff(unos);
        else
            std::cout << "Pogresan unos\n";
        std::cin >> unos;
    }
    printing.stopSignal();
    Sleep(5500);
    parallelPrint.join();
    return 0;
}

