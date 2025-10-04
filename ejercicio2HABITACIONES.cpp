#include <iostream>
#include <string>
using namespace std;

// ===== Habitacion =====
class Habitacion{
private:
    int id;
    string nombre;
    int norte; // -1 = sin sala
    int sur;
    int este;
    int oeste;
    int item;  // 0=nada, 1=alimento, 2=arma
public:
    Habitacion();
    Habitacion(int, string, int, int, int, int, int);
    int getNorte();
    int getSur();
    int getEste();
    int getOeste();
    string getNombre();
    int getItem();
    void setItem(int);
};

Habitacion::Habitacion(){
    id = -1;
    nombre = "";
    norte = -1;
    sur = -1;
    este = -1;
    oeste = -1;
    item = 0;
}

Habitacion::Habitacion(int _id, string _nombre, int _n, int _s, int _e, int _o, int _item){
    id = _id;
    nombre = _nombre;
    norte = _n;
    sur = _s;
    este = _e;
    oeste = _o;
    item = _item;
}

int Habitacion::getNorte(){
    return norte;
}

int Habitacion::getSur(){
    return sur;
}

int Habitacion::getEste(){
    return este;
}

int Habitacion::getOeste(){
    return oeste;
}

string Habitacion::getNombre(){
    return nombre;
}

int Habitacion::getItem(){
    return item;
}

void Habitacion::setItem(int _item){
    item = _item;
}

// ===== Prototipo helper usado por Jugador =====
int vecino(Habitacion v[], int pos, string dir);

// ===== Jugador =====
class Jugador{
private:
    int pos;       // indice en el arreglo de habitaciones
    int alimentos; // cantidad
    int armas;     // cantidad
public:
    Jugador();
    Jugador(int);
    int getPos();
    void setPos(int);
    int tomar(Habitacion&); // 0 nada, 1 alimento, 2 arma
    int getAlimentos();
    int getArmas();
    void mover(string, Habitacion[]);
    void tomarActual(Habitacion[]);
    void mostrarInventario();
};

Jugador::Jugador(){
    pos = 0;
    alimentos = 0;
    armas = 0;
}

Jugador::Jugador(int _pos){
    pos = _pos;
    alimentos = 0;
    armas = 0;
}

int Jugador::getPos(){
    return pos;
}

void Jugador::setPos(int _pos){
    pos = _pos;
}

int Jugador::tomar(Habitacion& h){
    int it = h.getItem();
    if(it == 1){
        alimentos++;
        h.setItem(0);
        return 1;
    }
    if(it == 2){
        armas++;
        h.setItem(0);
        return 2;
    }
    return 0;
}

int Jugador::getAlimentos(){
    return alimentos;
}

int Jugador::getArmas(){
    return armas;
}

void Jugador::mover(string dir, Habitacion v[]){
    int dest = vecino(v, getPos(), dir);
    if(dest == -1){
        cout << "No se puede avanzar en esa direccion" << endl;
    } else {
        setPos(dest);
        cout << "Ahora estas en " << v[getPos()].getNombre() << endl;
    }
}

void Jugador::tomarActual(Habitacion v[]){
    int r = tomar(v[getPos()]);
    if(r == 1) cout << "Tomaste alimento" << endl;
    else if(r == 2) cout << "Tomaste un arma" << endl;
    else cout << "Aqui no hay elemento" << endl;
}

void Jugador::mostrarInventario(){
    cout << "Alimentos: " << getAlimentos() << "  Armas: " << getArmas() << endl;
}

// ===== Helpers =====
void inicializarMapa(Habitacion v[], int& inicio){
    // indices 0..6 = Hab1..Hab7
    v[0] = Habitacion(1, "Hab 1", -1, 2, -1, -1, 1);
    v[1] = Habitacion(2, "Hab 2", -1, 3, -1, -1, 2);
    v[2] = Habitacion(3, "Hab 3",  0, 5,  3, -1, 0);
    v[3] = Habitacion(4, "Hab 4",  1, 5,  4,  2, 2);
    v[4] = Habitacion(5, "Hab 5", -1, 6, -1,  3, 0);
    v[5] = Habitacion(6, "Hab 6",  3, -1,  6, -1, 1);
    v[6] = Habitacion(7, "Hab 7",  4, -1, -1,  5, 0);
    inicio = 0; // arranca en Hab 1
}

int vecino(Habitacion v[], int pos, string dir){
    if(dir == "norte"){
        return v[pos].getNorte();
    }
    if(dir == "sur"){
        return v[pos].getSur();
    }
    if(dir == "este"){
        return v[pos].getEste();
    }
    if(dir == "oeste"){
        return v[pos].getOeste();
    }
    return -1;
}

// ===== main =====
int main(){
    Habitacion mapa[7];
    int inicio = 0;
    inicializarMapa(mapa, inicio);
    Jugador pj(inicio);

    cout << "Estas en " << mapa[pj.getPos()].getNombre() << endl;
    cout << "Comandos: norte, sur, este, oeste, tomar, inventario, salir" << endl;

    string cmd;
    while(true){
        cout << "> ";
        getline(cin, cmd);

        if(cmd=="salir"){
            break;
        } else if(cmd=="norte"){
            pj.mover("norte", mapa);
        } else if(cmd=="sur"){
            pj.mover("sur", mapa);
        } else if(cmd=="este"){
            pj.mover("este", mapa);
        } else if(cmd=="oeste"){
            pj.mover("oeste", mapa);
        } else if(cmd=="tomar"){
            pj.tomarActual(mapa);
        } else if(cmd=="inventario"){
            pj.mostrarInventario();
        } else {
            cout << "Comando invalido" << endl;
        }
    }
}
