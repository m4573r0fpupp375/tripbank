#include <string>
#include <math.h>

using namespace std;

class Client
{
public:
    string id;
    float balance;
    float fixed;

    Client(string name, float bal)
    {
        id=name;
        balance=bal;
        fixed=bal;
    }

    Client(string name)
    {
        id=name;
        balance=0;
        fixed=0;
    }

    void fixBalance()
    {
        fixed=balance*100;
        if(fixed>0) fixed=ceil(fixed);
        if(fixed<0) fixed=floor(fixed);
        fixed/=100;
    }
};
