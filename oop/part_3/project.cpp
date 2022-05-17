#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class masina{
protected:
    static int contor;
    const int id;
    int an_productie;
    string nume,producator;
public:
    masina (int, string, string);
    masina (masina&);
    virtual ~masina();

    int getcontor(){return contor;}
    int getid()const {return id;}
    int getan(){return an_productie;}
    string getnume(){return nume;}
    string getproducator(){return producator;}

    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    masina &operator=(masina&);
    friend istream& operator>>(istream&, masina&);
    friend ostream& operator<<(ostream&, masina&);

};
int masina::contor=0;

masina::masina(int ap=1900, string n="", string p="") : id(++contor), an_productie(ap), nume(n), producator(p){
    try{
        if (ap<0)
            throw 0;
        else if (ap<1900)
            throw 1;
        else if (ap>2021)
            throw 2;
    }
    catch (int x){
        if(x==0)
            cout<<"Eroare constructor: anul de productie nu poate fi negativ.\n";
        else if (x==1)
            cout<<"Eroare constructor: anul de productie nu poate fi mai mic de 1900.\n";
        else
            cout<<"Eroare constructor: anul de productie nu poate fi mai mare decat anul curent.\n";
        exit(EXIT_FAILURE);
    }
}
masina::masina(masina &m): id(m.id), an_productie(m.an_productie), nume(m.nume), producator(m.producator){
}
masina::~masina(){
    an_productie=0;
    nume="";
    producator="";
    contor--;
}

masina& masina::operator=(masina &m){
    an_productie=m.an_productie;
    nume=m.nume;
    producator=m.producator;
}

void masina::citire(istream &in){
    in.get();
    cout<<"Nume:";
    string n;
    getline(in,n);
    nume=n;
    cout<<"An productie:";
    int ap;
    in>>ap;
        try{
        if (ap<0)
            throw 0;
        else if (ap<1900)
            throw 1;
        else if (ap>2021)
            throw 2;
        }
    catch (int x){
        if(x==0)
            cout<<"Eroare citire: anul de productie nu poate fi negativ.\n";
        else if (x==1)
            cout<<"Eroare citire: anul de productie nu poate fi mai mic de 1900.\n";
        else
            cout<<"Eroare citire: anul de productie nu poate fi mai mare decat anul curent.\n";
        exit(EXIT_FAILURE);
        }
    an_productie=ap;
    in.get();
    cout<<"Producator:";
    string p;
    getline(in,p);
    producator=p;
}
istream& operator>>(istream& in,masina& m){
    m.citire(in);
    return in;
}

void masina::afisare(ostream &out){
    out<<"ID: "<<id<<";\n";
    out<<"Nume: "<<nume<<";\n";
    out<<"An productie: "<<an_productie<<";\n";
    out<<"Producator: "<<producator<<";\n";
}
ostream& operator<<(ostream& out, masina& m){
    m.afisare(out);
    return out;
}

class coupe: public masina{
private:

public:
    coupe (int, string, string);
    coupe (coupe&);
    ~coupe();

    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    coupe &operator=(coupe&);
    friend istream& operator>>(istream&, coupe&);
    friend ostream& operator<<(ostream&, coupe&);
};

coupe::coupe(int ap=1900, string n="", string p="") : masina(ap,n,p){
}
coupe::coupe(coupe &c): masina(c.an_productie, c.nume, c.producator){
}
coupe::~coupe(){
}

coupe& coupe::operator=(coupe &c){
    an_productie=c.an_productie;
    nume=c.nume;
    producator=c.producator;
}

void coupe::citire(istream &in){
    masina::citire(in);
}
istream& operator>>(istream& in,coupe& c){
    c.citire(in);
    return in;
}

void coupe::afisare(ostream &out){
    masina::afisare(out);
}
ostream& operator<<(ostream& out, coupe& c){
    c.afisare(out);
    return out;
}

class hothatch: public masina{
private:
    string sasiu_baza;
    int extra_acceleratie;
public:
    hothatch(int, string, string, string, int);
    hothatch(hothatch&);
    ~hothatch();

    string getsasiu(){return sasiu_baza;};
    int getacc(){return extra_acceleratie;};

    void citire(istream &in);
    void afisare(ostream &out);
    hothatch &operator=(hothatch&);
    friend istream& operator>>(istream&, hothatch&);
    friend ostream& operator<<(ostream&, hothatch&);

};

hothatch::hothatch(int ap=1900, string n="", string p="",string s="",int e=1): masina(ap, n, p),sasiu_baza(s),extra_acceleratie(e){
    try{
        if (e<0)
            throw 0;
        else if (e==0)
                throw 1;
    }
    catch (int x){
        if(x==0)
            cout<<"Eroare constructor: acceleratia nu poate fi negativa.\n";
        else if (x==1)
            cout<<"Eroare constructor: acceleratia nu poate fi nula.\n";
        exit(EXIT_FAILURE);
    }
}
hothatch::hothatch(hothatch& h):masina(h.an_productie, h.nume, h.producator),sasiu_baza(h.sasiu_baza),extra_acceleratie(h.extra_acceleratie){
}
hothatch::~hothatch(){
}

hothatch& hothatch::operator=(hothatch &h){
    an_productie=h.an_productie;
    nume=h.nume;
    producator=h.producator;
    sasiu_baza=h.sasiu_baza;
    extra_acceleratie=h.extra_acceleratie;
}

void hothatch::citire(istream &in){
    masina::citire(in);
    cout<<"Sasiu baza: ";
    string s;
    getline(in,s);
    sasiu_baza=s;
    cout<<"Acceleratie extra: ";
    int e;
    in>>e;
    try{
        if (e<0)
            throw 0;
        else if (e==0)
            throw 1;
    }
    catch (int x){
        if(x==0)
            cout<<"Eroare citire: acceleratia nu poate fi negativa.\n";
        else if (x==1)
            cout<<"Eroare citire: acceleratia nu poate fi nula.\n";
        exit(EXIT_FAILURE);
    }
    extra_acceleratie=e;
}
istream& operator>>(istream& in,hothatch &h){
    h.citire(in);
    return in;
}

void hothatch::afisare(ostream &out){
    masina::afisare(out);
    out<<"Sasiu baza: "<<sasiu_baza<<";\n";
    out<<"Acceleratie extra: "<<extra_acceleratie<<".\n";
}
ostream& operator<<(ostream& out, hothatch& h){
    h.afisare(out);
    return out;
}

class cabrio: public masina{
private:
    string material_acoperis;
    int nr_locuri;
public:
    cabrio(int, string, string, string, int);
    cabrio(cabrio&);
    ~cabrio();

    string getmateriala(){return material_acoperis;};
    int getnrl(){return nr_locuri;};

    void citire(istream &in);
    void afisare(ostream &out);
    cabrio &operator=(cabrio&);
    friend istream& operator>>(istream&, cabrio&);
    friend ostream& operator<<(ostream&, cabrio&);

};

cabrio::cabrio(int ap=1900, string n="", string p="",string m="metal",int nr=2): masina(ap, n, p),material_acoperis(m),nr_locuri(nr){
    try{
        if (nr<0)
            throw 0;
        else if(nr!=2&&nr!=4)
            throw 1;
        if (m!="metal"&&m!="textil")
            throw 2;
    }
    catch (int x){
        if (x==0)
            cout<<"Eroare constructor: numarul de locuri nu poate fi negativ.\n";
        else if(x==1)
            cout<<"Eroare constructor: numarul de locuri nu poate fi diferit de 2 sau 4.\n";
        else if (x==2)
            cout<<"Eroare constructor: materialul acoperisului poate fi doar metal sau textil.\n";
        exit(EXIT_FAILURE);
    }
}
cabrio::cabrio(cabrio& c):masina(c.an_productie, c.nume, c.producator),material_acoperis(c.material_acoperis),nr_locuri(c.nr_locuri){
}
cabrio::~cabrio(){
}

cabrio& cabrio::operator=(cabrio &c){
    an_productie=c.an_productie;
    nume=c.nume;
    producator=c.producator;
    material_acoperis=c.material_acoperis;
    nr_locuri=c.nr_locuri;
}

void cabrio::citire(istream &in){
    masina::citire(in);
    cout<<"Material acoperis(metal/textil): ";
    string m;
    getline(in,m);
    cout<<"Numar de locuri(2/4): ";
    int nr;
    in>>nr;
    try{
        if (nr<0)
            throw 0;
        else if(nr!=2&&nr!=4)
            throw 1;
        if (m!="metal"&&m!="textil")
            throw 2;
    }
    catch (int x){
        if (x==0)
            cout<<"Eroare citire: numarul de locuri nu poate fi negativ.\n";
        else if(x==1)
            cout<<"Eroare citire: numarul de locuri nu poate fi diferit de 2 sau 4.\n";
        else if (x==2)
            cout<<"Eroare citire: materialul acoperisului poate fi doar metal sau textil.\n";
        exit(EXIT_FAILURE);
    }
    material_acoperis=m;
    nr_locuri=nr;
}
istream& operator>>(istream& in,cabrio &c){
    c.citire(in);
    return in;
}

void cabrio::afisare(ostream &out){
    masina::afisare(out);
    out<<"Material acoperis: "<<material_acoperis<<";\n";
    out<<"Numar de locuri: "<<nr_locuri<<".\n";
}
ostream& operator<<(ostream& out, cabrio& c){
    c.afisare(out);
    return out;
}

class supersport: public masina{
private:
    string material_sasiu;
    int nr_cilindri;
public:
    supersport(int, string, string, string, int);
    supersport(supersport&);
    ~supersport();

    string getmaterials(){return material_sasiu;};
    int getnrc(){return nr_cilindri;};

    void citire(istream &in);
    void afisare(ostream &out);
    supersport &operator=(supersport&);
    friend istream& operator>>(istream&, supersport&);
    friend ostream& operator<<(ostream&, supersport&);

};

supersport::supersport(int ap=1900, string n="", string p="",string ma="",int nr=1): masina(ap, n, p),material_sasiu(ma),nr_cilindri(nr){
    try{
        if(nr<0)
            throw 0;
        if(nr==0)
            throw 1;
        if (nr>16)
            throw 2;
    }
    catch (int x){
        if(x==0)
            cout<<"Eroare constructor: numarul cilindrilor nu poate fi negativ.\n";
        else if (x==1)
            cout<<"Eroare constructor: numarul cilindrilor nu poate fi nul.\n";
        else if(x==2)
            cout<<"Eroare constructor: numarul cilindrilor nu poate fi mai mare de 16.\n";
        exit(EXIT_FAILURE);
    }
}
supersport::supersport(supersport& s):masina(s.an_productie, s.nume, s.producator),material_sasiu(s.material_sasiu),nr_cilindri(s.nr_cilindri){
}
supersport::~supersport(){
}

supersport& supersport::operator=(supersport &s){
    an_productie=s.an_productie;
    nume=s.nume;
    producator=s.producator;
    material_sasiu=s.material_sasiu;
    nr_cilindri=s.nr_cilindri;
}

void supersport::citire(istream &in){
    masina::citire(in);
    cout<<"Material sasiu: ";
    string m;
    getline(in,m);
    material_sasiu=m;
    cout<<"Numar de cilindri: ";
    int nr;
    in>>nr;
        try{
        if(nr<0)
            throw 0;
        if(nr==0)
            throw 1;
        if (nr>16)
            throw 2;
    }
    catch (int x){
        if(x==0)
            cout<<"Eroare citire: numarul cilindrilor nu poate fi negativ.\n";
        else if (x==1)
            cout<<"Eroare citire: numarul cilindrilor nu poate fi nul.\n";
        else if(x==2)
            cout<<"Eroare citire: numarul cilindrilor nu poate fi mai mare de 16.\n";
        exit(EXIT_FAILURE);
    }
    nr_cilindri=nr;
}
istream& operator>>(istream& in,supersport &s){
    s.citire(in);
    return in;
}

void supersport::afisare(ostream &out){
    masina::afisare(out);
    out<<"Material sasiu: "<<material_sasiu<<";\n";
    out<<"Numar de cilindri: "<<nr_cilindri<<".\n";
}
ostream& operator<<(ostream& out, supersport& s){
    s.afisare(out);
    return out;
}

template <class T> class expozitie{
private:
    static int nr;
    T* expo;

public:
    expozitie(int n=0,T *e=NULL){
        nr=n;
        try{
            if(nr<0)
                throw 0;
        }
        catch(int x){
            cout<<"Eroare constructor. Numarul de masini expuse nu poate fi negativ.\n";
            exit(EXIT_FAILURE);
        }
        expo=new T[nr];
        for (int i=0;i<n;i++){
            expo[i]=e[i];
        }
    }
    expozitie(expozitie& e){
        nr=e.nr;
        expo=new T[nr];
        for (int i=0;i<nr;i++){
            expo[i]=e.expo[i];
        }
    }
    ~expozitie(){
        nr=0;
        delete []expo;
    }

    int getnr() {return nr;}
    T getelem(int i) {
        try{
            if (i<0)
                throw 0;
            else if (i==0)
                throw 1;
            else if (i>=this.getnr())
                throw 2;
        }
        catch(int x){
            if(x==0)
                cout<<"Eroare getter: numarul masinii nu poate fi negativ.\n";
            else if (x==1)
                cout<<"Eroare getter: numarul masinii nu poate fi nul.\n";
            else if (x==2)
                cout<<"Eroare getter: numarul masinii nu poate fi mai mare decat numarul total de elemente.\n";
            exit(EXIT_FAILURE);
        }
        return expo[i];}

    void citire(istream &in){
        cout<<"Introduceti numarul de masini expuse: ";
        in>>nr;
        try{
            if(nr<0)
                throw 0;
            else if(nr==0)
                throw 1;
        }
        catch(int x){
            if(x==0)
                cout<<"Eroare citire. Numarul de masini expuse nu poate fi negativ.\n";
            else if(x==1)
                cout<<"Eroare citire. Numarul de masini expuse nu poate fi nul.\n";
            exit(EXIT_FAILURE);
        }
        expo=new T[nr];
        cout<<"Introduceti masinile: \n";
        for(int i=0;i<nr;i++){
           in>>expo[i];
           cout<<"\n";
        }
    }
    void afisare(ostream &out){
    out<<"La expozitie se expun urmatoarele "<<nr<<" masini:"<<"\n";
    for(int i=0;i<nr;i++)
        out<<expo[i]<<"\n";
    }
    expozitie &operator=(expozitie<T> &e){
        nr=e.nr;
        expo=new T[nr];
        for (int i=0;i<nr;i++){
            expo[i]=e.expo[i];
        }
    }
    friend istream& operator>>(istream& in, expozitie<T> &e){
        e.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, expozitie<T> &e){
        e.afisare(out);
        return out;
    }
};
template<class T> int expozitie<T>::nr=0;

template <> class expozitie <supersport>{
private:
    static int nrs,nrv;
    supersport *s, *v;
public:
    expozitie(int ns=0,int nv=0,supersport *ps=NULL, supersport *pv=NULL){
        nrs=ns;
        nrv=nv;
        s=new supersport[nrs];
        v=new supersport[nrv];
        for (int i=0;i<ns;i++)
            s[i]=ps[i];
        for (int i=0;i<nv;i++)
            v[i]=pv[i];
    }
    expozitie(expozitie &e){
        nrs=e.nrs;
        nrv=e.nrv;
        s=new supersport[nrs];
        v=new supersport[nrv];
        for (int i=0;i<nrs;i++)
            s[i]=e.s[i];
        for (int i=0;i<nrv;i++)
            v[i]=e.v[i];
    }
    ~expozitie(){
        nrs=0;
        nrv=0;
        delete[]s;
        delete[]v;
    }

    int getnrs() {return nrs;};
    supersport getelems(int i) {
        try{
            if (i<0)
                throw 0;
            else if (i==0)
                throw 1;
            else if (i>=this->getnrs())
                throw 2;
        }
        catch(int x){
            if(x==0)
                cout<<"Eroare getter: numarul masinii nu poate fi negativ.\n";
            else if (x==1)
                cout<<"Eroare getter: numarul masinii nu poate fi nul.\n";
            else if (x==2)
                cout<<"Eroare getter: numarul masinii nu poate fi mai mare decat numarul total de elemente expuse.\n";
            exit(EXIT_FAILURE);
        }
        return s[i];}
        int getnrv() {return nrv;}
        supersport getelemv(int i){
        try{
            if (i<0)
                throw 0;
            else if (i==0)
                throw 1;
            else if (i>=this->getnrv())
                throw 2;
        }
        catch(int x){
            if(x==0)
                cout<<"Eroare getter: numarul masinii nu poate fi negativ.\n";
            else if (x==1)
                cout<<"Eroare getter: numarul masinii nu poate fi nul.\n";
            else if (x==2)
                cout<<"Eroare getter: numarul masinii nu poate fi mai mare decat numarul total de elemente vandute.\n";
            exit(EXIT_FAILURE);
        }
        return v[i];}

    void citire(istream &in){
        cout<<"Introduceti numarul de masini supersport din stoc: ";
        in>>nrs;
        try{
            if(nrs<0)
                throw 0;
        }
        catch(int x){
                cout<<"Eroare citire. Numarul de masini expuse nu poate fi negativ.\n";
            exit(EXIT_FAILURE);
        }
        s=new supersport[nrs];
        cout<<"Introduceti masinile: \n";
        for(int i=0;i<nrs;i++){
           in>>s[i];
           cout<<"\n";
        }
        cout<<"Introduceti numarul de masini supersport vandute: ";
        in>>nrv;
        try{
            if(nrv<0)
                throw 0;
        }
        catch(int x){
                cout<<"Eroare citire. Numarul de masini vandute nu poate fi negativ.\n";
            exit(EXIT_FAILURE);
        }
        v=new supersport[nrv];
        cout<<"Introduceti masinile: \n";
        for(int i=0;i<nrv;i++){
           in>>v[i];
           cout<<"\n";
        }
    }
    void afisare(ostream &out){
        out<<"Expozitia are in stoc urmatoarele "<<nrs<<" masini supersport:"<<"\n";
        for(int i=0;i<nrs;i++)
            out<<s[i]<<"\n";
        if (nrv==0){
            out<<"Si nu s-a vandut nicio masina.\n";
        }
        else{
            out<<"Iar urmatoarele "<<nrv<<" masini supersport au fost vandute:"<<"\n";
            for(int i=0;i<nrv;i++)
                out<<v[i]<<"\n";
        }
    }
    expozitie &operator=(expozitie<supersport> &e){
        nrs=e.nrs;
        nrv=e.nrv;
        s=new supersport[nrs];
        v=new supersport[nrv];
        for (int i=0;i<nrs;i++)
            s[i]=e.s[i];
        for (int i=0;i<nrv;i++)
            v[i]=e.v[i];
    }
    expozitie &operator-=(int x){
        try{
            if (x<0)
                throw 0;
            else if (x==0)
                throw 1;
            else if(x>nrs)
                throw 2;
        }
        catch(int z){
            if(z==0)
                cout<<"Eroare: indicele nu poate fi negativ.\n";
            else if(z==1)
                cout<<"Eroare: indicele nu poate fi nul.\n";
            else if(z==2)
                cout<<"Eroare: indicele nu poate fi mai mare ca numarul de masini din stoc.\n";
            exit(EXIT_FAILURE);
        }
        v[++nrv]=s[x-1];
        for (int i=x-1;i<nrs;i++)
            s[i]=s[i+1];
        ///delete s[nrs];
        nrs--;
    }
    friend istream& operator>>(istream& in, expozitie<supersport> &e){
        e.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, expozitie<supersport> &e){
        e.afisare(out);
        return out;
    }
};
int expozitie<supersport>::nrs=0;
int expozitie<supersport>::nrv=0;

void tip(masina *&m, int i, vector<pair<masina*,int>> &v) {
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul masinii "<<i+1<<": ";
    cin>>s;
    try{
        if(s=="coupe"){
                m=new coupe;
                cin>>*m;
                v.push_back(std::make_pair(*&m,-1));
        }
        else if(s=="hothatch"){
                m=new hothatch;
                cin>>*m;
                v.push_back(std::make_pair(*&m,-1));
            }
        else if(s=="cabrio"){
                m=new cabrio;
                cin>>*m;
                v.push_back(std::make_pair(*&m,-1));
            }
        else if(s=="supersport"){
                m=new supersport;
                cin>>*m;
                v.push_back(std::make_pair(*&m,-1));
            }
            else
                throw 10;
    }
    catch(int x){
        cout<<"Nu ati introdus un tip valid de masina. Optiuni: coupe, hothatch, cabrio, supersport.\n ";
    }
}

bool comp(const pair<masina*,int>& a, pair<masina*,int>& b){
    return a.second>b.second;
}

int main(){
    int option=0,n=0;
    masina **m;
    vector <pair<masina*,int>> v;
    do{
        cout<<"\nEXPOZITIE MASINI SPORT-Neagu Anastasia Elena-134-Tema 5\n\n";
        cout<<"1. Citeste masinile expuse;\n";
        cout<<"2. Afiseaza masinile expuse;\n";
        cout<<"3. Vinde o masina supersport;\n";
        cout<<"4. Afisaza masinile vandute dupa pretul de vanzare;\n";
        cout<<"5. Expozitie de masini coupe;\n";
        cout<<"6. Expozitie de masini hothatch;\n";
        cout<<"7. Expozitie de masini cabrio;\n";
        cout<<"8. Expozitie si vanzare de masini supersport;\n";
        cout<<"9. Contorizare masini;\n";
        cout<<"0. Iesire.\n";
        cin>>option;
        if (option==1){
            cout<<"Introduceti numarul de masini expuse: ";
            cin>>n;
            try{
                if(n<0)
                    throw 0;
                else if (n==0)
                    throw 1;
            }
            catch(int x){
                if(x==0)
                    cout<<"Eroare: numarul de masini expuse nu poate fi negativ.\n";
                else if(x==1)
                    cout<<"Eroare: numarul de masini expuse nu poate fi nul.\n";
                exit(EXIT_FAILURE);
            }
            m=new masina*[n];
            for(int i=0;i<n;i++)
                tip(m[i],i,v);
        }
        if (option==2){
            if(!v.empty()){
                vector <pair<masina*,int>>::iterator i;
                for (i=v.begin();i!=v.end();i++){
                    cout<<(*i->first)<<"\n";
                }
            }
            else cout<<"Nu s-au citit masini. Reveniti la actiunea 1.\n";
        }
        if(option==3){
            int nr,pret;
            cout<<"Selectati ID-ul masinii pe care doriti sa o vindeti: ";
            cin>>nr;
            try{
                if (n==0)
                    throw 0;
                else if(nr<0)
                    throw 1;
                else if(nr==0)
                    throw 2;
                else if(nr>n)
                    throw 3;
                supersport *s=dynamic_cast<supersport*>(m[nr-1]);
                if(!s)
                    throw 4;
            }
            catch(int x){
                if(x==0)
                    cout<<"Eroare: nu ati citit lista de masini expuse. Incercati mai intai optiunea 1.\n";
                else if(x==1)
                    cout<<"Eroare: ID-ul masinii expuse nu poate fi negativ.\n";
                else if(x==2)
                    cout<<"Eroare: ID-ul masinii expuse nu poate fi nul.\n";
                else if(x==3)
                    cout<<"Eroare: ID-ul masinii expuse nu poate fi mai mare decat numarul masinilor expuse.\n";
                else if(x==4)
                    cout<<"Eroare: ID-ul ales nu apartine unei masini supersport.\n";
                exit(EXIT_FAILURE);
            }
            for (int i=0;i<n;i++){
                    if(v[i].first->getid()==nr)
                        if (v[i].second!=-1)
                            cout<<"Masina cu ID-ul "<<nr<<" a fost deja vanduta cu pretul de "<<v[i].second<<" euro! Selectati o alta masina.\n";
                    else {
                        cout<<"Selectati pretul de vanzare: ";
                        cin>>pret;
                        v[i].second=pret;
                    }
            }
        }
        if (option==4){
            vector <pair<masina*,int>>::iterator i;
            sort(v.begin(),v.end(),comp);
            try{
                if(n==0)
                    throw 0;
                i=v.begin();
                if(i->second==-1)
                    throw 1;
            }
            catch(int x){
                if(x==0){
                    cout<<"Eroare: nu ati citit lista de masini expuse. Incercati mai intai optiunea 1.\n";
                    exit(EXIT_FAILURE);
                    }
                else if(x==1) cout<<"Nicio masina nu a fost vanduta! Incercati mai intai optiunea 2.\n";
            }
            for (i=v.begin();i!=v.end()&&i->second!=-1;i++){
                cout<<(*i->first);
                cout<<"Pret vanzare:"<<i->second<<".\n";
            }
        }
        if (option==5){
            expozitie <coupe> c;
            cin>>c;
            cout<<c;
        }
        if (option==6){
            expozitie <hothatch> h;
            cin>>h;
            cout<<h;
        }
        if (option==7){
            expozitie <cabrio> c;
            cin>>c;
            cout<<c;
        }
        if (option==8){
            expozitie <supersport> s;
            cin>>s;
            cout<<s;
        }
        if (option==9){
            int nrc=0,nrh=0,nrca=0,nrs=0;
            if (n>0){
            for(int i=0;i<n;i++){
                coupe *m1=dynamic_cast<coupe*>(m[i]);
                hothatch *m2=dynamic_cast<hothatch*>(m[i]);
                cabrio *m3=dynamic_cast<cabrio*>(m[i]);
                supersport *m4=dynamic_cast<supersport*>(m[i]);
                if (m1) nrc++;
                if (m2) nrh++;
                if (m3) nrca++;
                if (m4) nrs++;
                }
            cout<<"Numarul de masini coupe: "<<nrc<<";\n";
            cout<<"Numarul de masini hothatch: "<<nrh<<";\n";
            cout<<"Numarul de masini cabrio: "<<nrca<<";\n";
            cout<<"Numarul de masini supersport: "<<nrs<<";\n";
            }
            else{
                cout<<"Nu s-au citit masini. Reveniti la actiunea 1.\n";
            }
        }
        if (option<0||option>9){
            cout<<"\nSelectie invalida. Mai incearca o data!\n";
        }
        system("pause");
        system("cls");
    }while(option!=0);
    return 0;
}
