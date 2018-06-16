#include <iostream>
#include <cstring>

using namespace std;

class ArithmeticException
{
public:
    void message()
    {
        cout<<"Division by zero is not allowed" <<endl;
    }
};

class NumbersNotDivisibleException
{
private:
    int divider;
public:
    NumbersNotDivisibleException(int d)
    {
        divider=d;
    }
    void message()
    {
        cout<<"Division by "<<divider<<" is not supported"<<endl;
    }

};

class NumbersIsNotPositiveException
{
private:
    int num;
public:
    NumbersIsNotPositiveException(int n)
    {
        num=n;
    }
    void message()
    {
        cout<<"Number "<<num<<" is not positive integer"<<endl;
    }
};

class IndexOutOfBoundsException
{
private:
    int index;
public:
    IndexOutOfBoundsException(int i)
    {
        index=i;
    }
    void message()
    {
        cout<<"The index "<<index<<" is out of bounds"<<endl;
    }
};



class ArrayFullException
{
public:

    void message()
    {
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};



class PositiveIntegers
{
private:
    int *niza;
    int n;
    int maxcapacity;
public:
    PositiveIntegers(int maxc=0)
    {
        maxcapacity=maxc;
        niza=new int[maxc];
        int n=0;
    }

    PositiveIntegers(const PositiveIntegers &p)
    {
        niza=new int[p.maxcapacity];
        for(int i=0; i<p.n; i++)
        {
            niza[i]=p.niza[i];
        }
        n=p.n;
        maxcapacity=p.maxcapacity;
    }

    PositiveIntegers &operator=(const PositiveIntegers &p)
    {
        if(this!=&p)
        {
            delete [] niza;
            niza=new int[p.maxcapacity];
            for(int i=0; i<p.n; i++)
            {
                niza[i]=p.niza[i];
            }
            maxcapacity=p.maxcapacity;
            n=p.n;
        }
        return *this;
    }
    ~PositiveIntegers()
    {
        delete [] niza;
    }

    void increaseCapacity(int c)
    {
        int *tmp=new int[maxcapacity+c];
        for(int i=0; i<n; i++)
        {
            tmp[i]=niza[i];
        }
        delete [] niza;
        niza=tmp;
        maxcapacity+=c;
    }

    PositiveIntegers &operator+=(int x)
    {
        if(n==maxcapacity)
        {
            throw ArrayFullException();
        }
        if(x<=0)
        {
            throw NumbersIsNotPositiveException(x);
        }
        niza[n++]=x;
        return *this;
    }

    PositiveIntegers operator*(int x)
    {
        PositiveIntegers p(*this);
        for(int i=0; i<p.n; i++)
        {
            p.niza[i]*=x;
        }
        return p;
    }
    PositiveIntegers operator/(int x)
    {
        if(x==0)
        {
            throw ArithmeticException();
        }
        for(int i=0; i<n; i++)
        {
            if(niza[i]%x!=0)
            {
                throw NumbersNotDivisibleException(x);
            }
        }
        PositiveIntegers p(*this);
        for(int i=0; i<p.n; i++)
        {
            p.niza[i]/=x;
        }
        return p;
    }
    int &operator[](int i)
    {
        if(i<0 || i>n)
        {
            throw IndexOutOfBoundsException(i);
        }
        return niza[i];
    }
    void print()
    {
        cout<<"Size: "<<n<<" Capacity: "<<maxcapacity<<" Numbers: ";
        for(int i=0; i<n; i++)
        {
            cout<<niza[i]<< " " ;
        }
        cout<<endl;

    }

};

int main()
{

    int n,capacity;
    cin >> n >> capacity;
    PositiveIntegers pi (capacity);
    for (int i=0; i<n; i++)
    {
        int number;
        cin>>number;
        try
        {
            pi+=number;
        }
        catch(ArrayFullException &e)
        {
            e.message();
        }
        catch(NumbersIsNotPositiveException &e)
        {
            e.message();
        }
    }
    cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
    pi.print();
    int incCapacity;
    cin>>incCapacity;
    pi.increaseCapacity(incCapacity);
    cout<<"===INCREASING CAPACITY==="<<endl;
    pi.print();

    int n1;
    cin>>n1;
    for (int i=0; i<n1; i++)
    {
        int number;
        cin>>number;

        try
        {
            pi+=number;
        }
        catch(ArrayFullException &e)
        {
            e.message();
        }
        catch(NumbersIsNotPositiveException &e)
        {
            e.message();
        }

    }
    cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
    PositiveIntegers pi1;

    cout<<"===TESTING DIVISION==="<<endl;

    try
    {
        pi1 = pi/0;
    pi1.print();
    }
    catch(ArithmeticException &e)
    {
        e.message();
    }
    catch(NumbersNotDivisibleException &e)
    {
        e.message();
    }

    try
    {
        pi1 = pi/1;
        pi1.print();

    }
    catch(ArithmeticException &e)
    {
        e.message();
    }
    catch(NumbersNotDivisibleException &e)
    {
        e.message();
    }

    try
    {
        pi1 = pi/2;
        pi1.print();

    }
    catch(ArithmeticException &e)
    {
        e.message();
    }
    catch(NumbersNotDivisibleException &e)
    {
        e.message();
    }


    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();


    cout<<"===TESTING [] ==="<<endl;

    try
    {
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }


    try
    {
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }

    try
    {
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }

    try
    {
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }



    return 0;
}
