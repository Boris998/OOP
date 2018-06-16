#include <iostream>
#include <cstring>

using namespace std;

class Vozac
{
protected:
    char ime[100];
    int vozrast;
    int brojtrki;
    bool veteran;
public:
    Vozac(char *i,int v,int b,bool ve)
    {
        strcpy(ime,i);
        vozrast=v;
        brojtrki=b;
        veteran=ve;
    }
    bool operator==(Vozac &v)
    {
        return (zarabotuvacka()==v.zarabotuvacka());
    }

    virtual int zarabotuvacka()=0;
    virtual int danok()=0;

    friend ostream &operator<<(ostream &out,const Vozac &v)
    {
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.brojtrki<<endl;
        if(v.veteran)
        {
            out<<"VETERAN"<<endl;
        }
        return out;
    }
};

class Avtomobilist:public Vozac
{
private:
    double cena;
public:
    Avtomobilist(char *i,int v,int b,bool ve,double c):Vozac(i,v,b,ve)
    {
        cena=c;
    }
    int zarabotuvacka()
    {
        return (cena/5)*brojtrki;
    }
    int danok()
    {
        if(brojtrki>10)
        {
            return zarabotuvacka()*0.15;
        }
        else
        {
            return zarabotuvacka()*0.1;
        }
    }
};

class Motociklist:public Vozac
{
private:
    int moknost;
public:
    Motociklist(char *i,int v,int b,bool ve,int m):Vozac(i,v,b,ve)
    {
        moknost=m;
    }
    int zarabotuvacka()
    {
        return moknost*20*brojtrki;
    }
    int danok()
    {
        if(veteran)
        {
            return zarabotuvacka()*0.25;
        }
        else
        {
            return zarabotuvacka()*0.2;
        }
    }
};

int soIstaZarabotuvachka(Vozac **v,int n,Vozac *vx)
{
    int c=0;
    for(int i=0;i<n;i++)
    {
        if(*vx==*v[i])
        {
            c++;
        }
    }
    return c;
}


int main()
{
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i)
    {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x)
        {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        }
        else
        {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i)
    {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i)
    {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
