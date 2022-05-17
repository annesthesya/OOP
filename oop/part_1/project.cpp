#include <iostream>

using namespace std;



class multime {
private:
    int lungime;
    int elem[100];

public:

    multime ();
    multime (int*, int);
    multime (multime&);
    ~multime ();

    friend void input(multime [100], int);
    friend void output(multime [100], int);

    void setElement (int, int);
    void setLungime (int);

    int getElement (int i){
        if (i>this->lungime){
            cout<<"Elementul nu exista! Operatie esuata.";
            return -1;}
        else return this->elem[i];
        };
    int getLungime () {return lungime;};

    friend istream& operator>>(istream &in, multime& m);
    friend ostream& operator<<(ostream &out, multime& m);
    void citire(istream &in);
    void afisare(ostream &out);

    void transformare();

    friend multime& operator+(multime& m1, multime& m2);
    friend multime& operator*(multime& m1, multime& m2);
    friend multime& operator-(multime& m1, multime& m2);

};



multime::multime(){
    this->lungime = 0;
}
multime::multime(int elem[1000], int lungime){
    this->lungime = lungime;
    for (int i=0;i<lungime;i++)
        this->elem[i]=elem[i];
}
multime::multime(multime &m){
    this->lungime = m.lungime;
    for (int i=0;i<m.lungime;i++)
        this->elem[i]=m.elem[i];
}
multime::~multime(){
    this->lungime=0;
    //cout<<"Multimea a fost distrusa."<<endl;
}


void multime:: setElement(int i, int x){
    if (i>this->lungime)
        cout<<"Elementul este in afara multimii! Operatie esuata.";
    else this->elem[i]=x;
}
void multime:: setLungime(int lungime){
    this->lungime=lungime;
}


istream& operator>>(istream& in,multime& m){
    m.citire(in);
    return in;
}
ostream& operator<<(ostream& out, multime& m){
    m.afisare(out);
    return out;
}
void multime::citire(istream &in){
    int i;
    cout<<"Lungime: ";
    in>>lungime;
    for (i=0; i<lungime;i++){
        cout<<"\nElementul "<<i+1<<": ";
        in>>elem[i];
        cout<<endl;
        }
}
void multime::afisare(ostream &out){
    if (lungime==0) {
        out<<"Multimea este goala.\n"<<endl;
    }
    else
        {for(int i=0;i<lungime;i++)
            out<<elem[i]<<" ";
        cout<<endl<<"Lungime: "<<lungime<<endl;
        }
}


void multime::transformare(){
    int aux,i,j;
    for (i=0; i< this->lungime-1;i++)
        for (j=0; j<this->lungime-1-i;j++)
            if ((this->elem[j])>(this->elem[j+1])){
                aux = this->elem[j];
                this->elem[j] = this->elem[j+1];
                this->elem[j+1] = aux;
                }
    for (i = 0;i < this->lungime-1;i++)
            if (this->elem[i] == this->elem[i+1]){
                    for (int j = i; j < this->lungime-1; j++){
                        this->elem[j] = this->elem[j+1];
                        }
             this->lungime--;
             i--;
            }
}


inline multime& operator+(multime &m1, multime& m2){
multime *m = new multime;
int i=0,j=0,k=0;

    while (i < m1.lungime && j < m2.lungime)
        if (m1.elem[i] <= m2.elem[j]){
            m->elem[k] = m1.elem[i];
            k++;
            i++;
            m->lungime++;
            }
            else {
                m->elem[k] = m2.elem[j];
                k++;
                j++;
                m->lungime++;
                }

    while (i < m1.lungime){
        m->elem[k] = m1.elem[i];
        k++;
        i++;
        m->lungime++;
        }

    while (j < m2.lungime){
        m->elem[k] = m2.elem[j];
        k++;
        j++;
        m->lungime++;
        }

        for (i = 0;i < m->lungime-1;i++)
            if (m->elem[i] == m->elem[i+1]){
                    for (int j = i; j < m->lungime-1; j++){
                        m->elem[j] = m->elem[j+1];
                        }
             m->lungime--;
             i--;
            }
        return *m;
}
inline multime& operator*(multime &m1, multime& m2){
multime *m = new multime;
int i=0,j=0,k=0;

    while (i < m1.lungime && j < m2.lungime)
        if (m1.elem[i] <= m2.elem[j]){
            if (m1.elem[i] == m2.elem[j]){
                m->elem[k] = m1.elem[i];
                k++;
                m->lungime++;
                j++;}
            i++;
            }
            else {
                if (m1.elem[i] == m2.elem[j]){
                    m->elem[k] = m2.elem[j];
                    k++;
                    m->lungime++;
                    i++;}
                j++;
                }

        return *m;
}
inline multime& operator-(multime &m1, multime& m2){
multime *m =new multime;
int i=0,j=0,k=0;

    while (i < m1.lungime && j < m2.lungime)
        if (m1.elem[i] < m2.elem[j]){
            m->elem[k] = m1.elem[i];
            k++;
            m->lungime++;
            i++;
            }
                else if(m1.elem[i] > m2.elem[j])
                    j++;
                    else{
                        i++;
                        j++;
                    }
        while(i<m1.lungime){
            m->elem[k]=m1.elem[i];
            i++;
            k++;
            m->lungime++;
        }
        return *m;
}


void input(multime m[1000], int n){
    for (int i=0;i<n;i++){
        cout<<"\nMultimea "<<i+1<<":";
        cin>>m[i];
        m[i].transformare();
    }
}


void output(multime m[1000], int n){
    for (int i=0;i<n;i++){
        cout<<"Multimea "<<i+1<<":\n"<<m[i];
    }
}



int main(){
int selectie;
do{
    system("cls");
    cout<<"\n Neagu Anastasia Elena - 134 - Proiect - Multimi: \n";
    cout<<"\n=====-- MENIU PRINCIPAL --=====\n";
    cout<<"\n";
    cout<<"\t1. Operatii pe n multimi;\n";
    cout<<"\t2. Operatii pe o multime;\n";
    cout<<"\t0. Iesire.\n";
    cin>>selectie;

    if (selectie==1){
    multime M[100];
    int optiune;
    system("cls");
    int n;
    cout<<"\n=====-- OPERATII PE N MULTIMI --=====\n";
    cout<<"Selectati numarul de multimi pe care doriti sa le introduceti:";
    cout<<"\n\t(Tablourile vor fi transformate in multimi automat.)\n";
    do {
        cin>>n;
        if (n<=1) cout<<"Numarul multimilor trebuie sa fie mai mare decat 1! Mai incearca o data.\n";
        if (n>100) cout<<"Numarul multimilor trebuie sa fie mai mic sau egal cu 100! Mai incearca o data.\n";
    }while(n<=1 || n>100);
    input(M,n);
    do{
            system("cls");
            cout<<"\n=====-- MENIU OPERATII PE N MULTIMI --=====\n";
            cout<<"\n";
            cout<<"\t1. Afisare multimi;\n";
            cout<<"\t2. Reuniunea tuturor multimilor;\n";
            cout<<"\t3. Intersectia tuturor multimilor;\n";
            cout<<"\t0. Inapoi la meniul principal.\n";
            cin>>optiune;
            if (optiune == 1){
                output(M,n);
                system("pause");
            }
            if (optiune == 2){
                multime m;
                m = M[0];
                for (int i=1;i<n;i++)
                    m = m + M[i];
                cout<<"Multimea obtinuta este:"<<m;
                system("pause");
            }
            if (optiune == 3){
                multime m;
                m = M[0]*M[1];
                for (int i=2;i<n;i++)
                    m = m * M[i];
                cout<<"Multimea obtinuta este:"<<m;
                system("pause");
            }
            if (optiune < 0 || optiune > 3){
                cout<<"Tasta gresita! Mai incearca o data!\n";
                system("pause");
            }

        }while (optiune != 0);
        }
        if (selectie==2){
            int option,poz,val;
            multime l,k;
                system("cls");
                cout<<"\n=====-- OPERATII PE O MULTIME --=====\n";
                cout<<"\t(Tabloul va fi transformat intr-o multime automat.)\n";
                cin>>l;
                l.transformare();
                do{
                system("cls");
                cout<<"\n=====-- MENIU OPERATII PE O MULTIME --=====\n";
                cout<<"\n";
                cout<<"\t1. Afisare multime;\n";
                cout<<"\t2. Introducere element in multime;\n";
                cout<<"\t3. Afisare element din multime;\n";
                cout<<"\t4. Reuniune;\n";
                cout<<"\t5. Intersectie;\n";
                cout<<"\t6. Diferenta;\n";
                cout<<"\t0. Inapoi la meniul principal.\n";
                cin>>option;

                if (option == 1){
                    cout<<l;
                    system("pause");
                }
                if (option == 2){
                    cout<<"Alegeti pozitia elementului:";
                    cin>>poz;
                    cout<<"Alegeti valoarea noua a elementului de pe pozitia "<<poz<<":";
                    cin>>val;
                    l.setElement(poz,val);
                    l.transformare();
                    system("pause");
                }
                if (option == 3){
                    cout<<"Alegeti pozitia elementului cautat:";
                    cin>>poz;
                    cout<<"Valoarea elementului de pe pozitia "<<poz<<" este "<<l.getElement(poz)<<".\n";
                    system("pause");}
                if (option == 4){
                    cout<<"Pentru aceasta operatie este necesara inca o multime.\n";
                    cin>>k;
                    k.transformare();
                    cout<<"Reuniunea celor doua multimi:"<<l+k;
                    system("pause");}
                if (option == 5){
                    cout<<"Pentru aceasta operatie este necesara inca o multime.\n";
                    cin>>k;
                    k.transformare();
                    cout<<"Intersectia celor doua multimi:"<<l*k;
                    system("pause");}
                if (option == 6){
                    cout<<"Pentru aceasta operatie este necesara inca o multime.\n";
                    cin>>k;
                    k.transformare();
                    cout<<"Diferenta dintre cele doua multimi:"<<l-k;
                    system("pause");}
                if (option > 6 || option < 0){
                    cout<<"Tasta gresita! Mai incearca o data!\n";
                    system("pause");
                    }
                }while (option != 0);
            }
            if (selectie < 0 || selectie > 3){
                cout<<"Tasta gresita! Mai incearca o data!\n";
                system("pause");
                }
}while (selectie != 0);

    return 0;
}
