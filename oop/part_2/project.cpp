#include <iostream>
#include <stdlib.h>

using namespace std;

class Locuinta;

class agentieImobiliara{
private:
    Locuinta **v;
    int n;
public:
    agentieImobiliara(Locuinta**, int);
    agentieImobiliara(agentieImobiliara&);
    ~agentieImobiliara();

    void citire(istream &in);
    void afisare(ostream &out);

    int getn(){return n;}
    void CalculChirieTotala(int, int);

    agentieImobiliara &operator=(agentieImobiliara&);
    friend istream& operator>>(istream&, agentieImobiliara&);
    friend ostream& operator<<(ostream&, agentieImobiliara&);
};

agentieImobiliara::agentieImobiliara(Locuinta **v=new Locuinta *[0], int n=0) : v(v), n(n){
}
agentieImobiliara::agentieImobiliara(agentieImobiliara &A) : v(A.v), n(A.n){
}

class Locuinta: public agentieImobiliara{
protected:
    string numeClient;
    int suprafataUtila;
    float discount;
    static int nrCase;
public:
    Locuinta (string, int, float);
    Locuinta (Locuinta&);
    virtual ~Locuinta();

    string getNume(){return numeClient;};
    int getSuprafata(){return suprafataUtila;};
    float getDiscount(){return discount;};

    virtual int CalculChirie(int x, int y)=0;
    static void numarLocuinte(){cout<<nrCase;}

    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    Locuinta &operator=(Locuinta&);
    friend istream& operator>>(istream&, Locuinta&);
    friend ostream& operator<<(ostream&, Locuinta&);
};
int Locuinta::nrCase;

Locuinta::Locuinta(string nc="", int su=0, float d=0) : numeClient(nc), suprafataUtila(su), discount(d){
    nrCase++;
}
Locuinta::Locuinta(Locuinta &L) : numeClient(L.numeClient), suprafataUtila(L.suprafataUtila), discount(L.discount){
    nrCase++;
}
Locuinta::~Locuinta(){
    numeClient="";
    suprafataUtila=0;
    discount=0;
}

Locuinta& Locuinta::operator=(Locuinta &L){
    numeClient=L.numeClient;
    suprafataUtila=L.suprafataUtila;
    discount=L.discount;
}

void Locuinta::citire(istream &in){
    cout<<"Nume Client:";
    in.get();
    string name;
    getline(in,name);
    numeClient=name;
    cout<<"Suprafata utila:";
    in>>suprafataUtila;
    cout<<"Discount:";
    in>>discount;
}
istream& operator>>(istream& in,Locuinta& L){
    L.citire(in);
    return in;
}

void Locuinta::afisare(ostream &out){
    out<<"Nume: "<<numeClient<<";\n";
    out<<"Suprafata utila: "<<suprafataUtila<<"mp;\n";
    out<<"Discount: "<<discount<<"%;\n";
}
ostream& operator<<(ostream& out, Locuinta& L){
    L.afisare(out);
    return out;
}

class Apartament:public Locuinta{
private:
    int etaj;
public:
    Apartament(string, int, float, int);
    Apartament(Apartament&);
    virtual ~Apartament();

    getEtaj(){return etaj;};

    int CalculChirie(int, int);

    void citire(istream &in);
    void afisare(ostream &out);
    Apartament &operator=(Apartament&);
    friend istream& operator>>(istream&, Apartament&);
    friend ostream& operator<<(ostream&, Apartament&);
};

Apartament::Apartament(string nc="", int su=0, float d=0, int e=0): Locuinta(nc, su, d),etaj(e){
}
Apartament::Apartament(Apartament& A):Locuinta(A.numeClient,A.suprafataUtila,A.discount),etaj(A.etaj){
}
Apartament::~Apartament(){
}

Apartament::CalculChirie(int x, int y){
    return x*suprafataUtila*(1-y*discount/100.0);
}

Apartament& Apartament::operator=(Apartament &A){
    numeClient=A.numeClient;
    suprafataUtila=A.suprafataUtila;
    discount=A.discount;
    etaj=A.etaj;
}

void Apartament::citire(istream &in){
    Locuinta::citire(in);
    cout<<"Etaj: ";
    in>>etaj;
}
istream& operator>>(istream& in,Apartament &A){
    A.citire(in);
    return in;
}

void Apartament::afisare(ostream &out){
    Locuinta::afisare(out);
    out<<"Etaj: "<<etaj<<".\n\n";
}
ostream& operator<<(ostream& out, Apartament& A){
    A.afisare(out);
    return out;
}

class Casa:public Locuinta{
private:
    int suprafataCurte;
public:
    Casa(string, int, float, int);
    Casa(Casa&);
    virtual ~Casa();

    getCurte(){return suprafataCurte;};

    int CalculChirie(int, int);

    void citire(istream &in);
    void afisare(ostream &out);
    Casa &operator=(Casa&);
    friend istream& operator>>(istream&, Casa&);
    friend ostream& operator<<(ostream&, Casa&);
};

Casa::Casa(string nc="", int su=0, float d=0, int sc=0): Locuinta(nc, su, d),suprafataCurte(sc){
}
Casa::Casa(Casa &C): Locuinta(C.numeClient,C.suprafataUtila,C.discount),suprafataCurte(C.suprafataCurte){
}
Casa::~Casa(){
}

Casa::CalculChirie(int x, int y){
    return x*(suprafataUtila+0.2*suprafataCurte)*(1-y*discount/100.0);
}

Casa& Casa::operator=(Casa &C){
    numeClient=C.numeClient;
    suprafataUtila=C.suprafataUtila;
    discount=C.discount;
    suprafataCurte=C.suprafataCurte;
}

void Casa::citire(istream &in){
    Locuinta::citire(in);
    cout<<"Suprafata curte: ";
    in>>suprafataCurte;
}
istream& operator>>(istream& in,Casa &C){
    C.citire(in);
    return in;
}

void Casa::afisare(ostream &out){
    Locuinta::afisare(out);
    out<<"Suprafata curte: "<<suprafataCurte<<".\n\n";
}
ostream& operator<<(ostream& out,Casa &C){
    C.afisare(out);
    return out;
}

agentieImobiliara &agentieImobiliara::operator=(agentieImobiliara &A){
    n=A.n;
    v = new Locuinta *[n];
    for (int i=0;i<n;i++)
        v[i]=A.v[i];
}

void agentieImobiliara::citire(istream &in){
    string l;
    int ok;
    cout<<"Introduceti numarul de locuinte din agentie: ";
    cin>>n;
    v=new Locuinta*[n];
    for(int i=0;i<n;i++){
        do {
            cout<<"Alege tipul locuintei "<<i+1<<":\n";
            cin>>l;
            ok=1;
            if(l=="apartament"){
                    v[i]=new Apartament;
                    cin>>*v[i];
                }
            else
                if(l=="casa"){
                    v[i]=new Casa;
                    cin>>*v[i];
                }
                    else{
                        cout<<"Nu ati introdus un tip valid de locuinta. Incercati inca o data!\n ";
                        ok=0;
                    }
            }while(ok==0);
            }
}
istream& operator>>(istream& in,agentieImobiliara &A){
    A.citire(in);
    return in;
}

void agentieImobiliara::afisare(ostream &out){
    cout<<"\nAgentia imobiliara contine urmatoarele locuinte:\n";
    for(int i=0;i<n;i++){
            cout<<"Locuinta "<<i+1<<" :\n";
        cout<<"\n"<<*v[i];
        cout<<"\n";
        }
}
ostream& operator<<(ostream& out,agentieImobiliara &A){
    A.afisare(out);
    return out;
}

void agentieImobiliara::CalculChirieTotala(int x, int y){
    for (int i=0;i<n;i++){
        cout<<"Chiria pentru locuinta "<<i+1<<":";
        cout<<this->v[i]->CalculChirie(x,y);
        cout<<"\n";
        }
}

agentieImobiliara::~agentieImobiliara(){
    for (int i=0;i<n;i++)
        delete v[i];
}

int main(){
agentieImobiliara *a;
int selectie,n,optiune,m,x,y;

cout<<"Neagu Anastasia Elena - 134 - Proiect - Agentie Imobiliara: \n";
cout<<"\n";
do{cout<<"Inserati numarul de agentii: ";
   cin>>n;
   cin.get();
   if (n>0){
        a=new agentieImobiliara[n];
        for (int i=0;i<n;i++){
            cout<<"Agentia "<<i+1<<":\n";
            cin>>a[i];cin.get();}
   }
   else
    cout<<"Valoarea n trebuie sa fie pozitiva";
    }while(n<=0);
do{
    system("cls");
    cout<<"\n=====-- MENIU --=====\n";
    cout<<"\n";
    cout<<"\t1. Afisare agentii;\n";
    cout<<"\t2. Afisare o agentie;\n";
    cout<<"\t3. Afisare numar total locuinte;\n";
    cout<<"\t4. Afisare plata chirie a tuturor locuintelor;\n";
    cout<<"\t5. Afisare plata chirie agentie;\n";
    cout<<"\t0. Iesire.\n";
    cin>>optiune;

    if (optiune == 1){
        system("cls");
        for (int i=0;i<n;i++)
            cout<<"Agentia "<<i+1<<":\n"<<a[i];
        system("pause");
    }
    if (optiune == 2){
        do{cout<<"Alegeti agentia: ";
        cin>>m;
        if (m<0||m>n)
            cout<<"Numar gresit! Mai incearca o data.";
        }while (m<0||m>n);
        cout<<a[m];
        system("pause");
    }
    if (optiune == 3){
        cout<<"Agentiile au in total ";
        Locuinta::numarLocuinte();
        cout<<" locuinte.\n";
        system("pause");
    }
    if (optiune == 4){
        cout<<"Alegeti valoarea standard chirie/mp: ";
        cin>>x;
        do{cout<<"Se tine cont de discount?\n\t1 - Da;\n\t0 - Nu. ";
        cin>>y;
        if (y>1||y<0) cout<<"Numar gresit! Mai incearca o data.";
        }while(y>1||y<0);
        system("cls");
        for (int i=0;i<n;i++){
            a[i].CalculChirieTotala(x,y);
        }
        system("pause");
    }
    if (optiune == 5){
        do{cout<<"Alegeti agentia: ";
        cin>>m;
        if (m<0||m>n)
            cout<<"Numar gresit! Mai incearca o data.";
        }while (m<0||m>n);
        cout<<"Alegeti valoarea standard chirie/mp: ";
        cin>>x;
        do{cout<<"Se tine cont de discount?\n\t1 - Da;\n\t0 - Nu. ";
        cin>>y;
        if (y>1||y<0) cout<<"Numar gresit! Mai incearca o data.";
        }while(y>1||y<0);
        a[m].CalculChirieTotala(x,y);
        system("pause");
    }
    if (optiune < 0 || optiune > 5){
        cout<<"Tasta gresita! Mai incearca o data!\n";
        system("pause");
    }
}while (optiune != 0);

    return 0;
}
