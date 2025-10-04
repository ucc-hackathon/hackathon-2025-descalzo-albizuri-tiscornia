#include <iostream>
using namespace std;

class Libro{
private:
long codigo;
string titulo;
string autor;
int añoPublicacion;
string categoria;
bool prestado = 0;
int vecesPrestado = 0;
public:
Libro();
Libro(long, string, string, int, string, bool);
void setCodigo(long);
long getCodigo();
void setTitulo(string);
string getTitulo();
void setAutor(string);
string getAutor();
void setAñoPublicacion(int);
int getAñoPublicacion();
void setCategoria(string);
string getCategoria();
bool getPrestado();
void prestar(string);
void devolver(string);
void listarDisponibles(Libro[], int);
void listarPrestados(Libro[], int);
int getVecesPrestado();
};

Libro::Libro(){
}
Libro::Libro(long _codigo, string _titulo, string _autor, int _año, string _categoria, bool _prestado) {
    codigo = _codigo;
    titulo = _titulo;
    autor = _autor;
    añoPublicacion = _año;
    categoria = _categoria;
    prestado = _prestado;
}
long Libro::getCodigo(){
    return codigo;
}

void Libro::setCodigo(long _codigo){
    codigo = _codigo;
}

string Libro::getTitulo(){
    return titulo;
}

void Libro::setTitulo(string _titulo){
    titulo = _titulo;
}

string Libro::getAutor(){
    return autor;
}

void Libro::setAutor(string _autor){
    autor = _autor;
}

int Libro::getAñoPublicacion(){
    return añoPublicacion;
}

void Libro::setAñoPublicacion(int _añoPublicacion){
    añoPublicacion = _añoPublicacion;
}

string Libro::getCategoria(){
    return categoria;
}

void Libro::setCategoria(string _categoria){
    categoria = _categoria;
}

bool Libro::getPrestado(){
    return prestado;
}

void Libro::prestar(string _titulo){
   if(titulo == _titulo && prestado == 0){
        prestado = 1;
        vecesPrestado ++;
    }
}

void Libro::devolver(string _titulo){
     if(titulo == _titulo && prestado == 1){
        prestado = 0;
    }
}
void Libro::listarDisponibles(Libro v[], int cantidad){
    cout << "Libros disponibles:" << endl;
    for(int i = 0; i < cantidad; i++){
        if(v[i].getPrestado() == 0){
            cout << "- " << v[i].getTitulo() << endl;
        }
    }
}

void Libro::listarPrestados(Libro v[], int cantidad){
    cout << "Libros prestados:" << endl;
    for(int i = 0; i < cantidad; i++){
        if(v[i].getPrestado() == 1){
            cout << "- " << v[i].getTitulo() << endl;
        }
    }
}
/*
Cada método recorre el arreglo de libros.

listarDisponibles() imprime solo los que tienen prestado == 0.

listarPrestados() imprime solo los que tienen prestado == 1.
*/
int Libro::getVecesPrestado(){
    return vecesPrestado;
}

    class Usuario{
    private:
    long legajo;
    int librosPrestados = 0;
    Libro l1;
    public:
    Usuario();
    Usuario(long, int);
    Usuario(long, int, Libro);
    void prestarLibro(Libro);
    void devolverLibro(Libro);
    string listarLibros();
    long getLegajo();
    void setLegajo(long);
    int getlibrosPrestados();
    void setLibro(Libro);
    Libro getLibro();
    void prestarLibro(Libro*);
    void devolverLibro(Libro*);
    };

    Usuario::Usuario(){
    }
    Usuario::Usuario(long _legajo, int _librosPrestados){
    legajo = _legajo;
    librosPrestados = _librosPrestados;
    }
    Usuario::Usuario(long _legajo, int _librosPrestados, Libro _l1){
    legajo = _legajo;
    librosPrestados = _librosPrestados;
    l1 = _l1;
    }
    
    long Usuario::getLegajo(){
    return legajo;
    }

    void Usuario::setLegajo(long _legajo){
    legajo = _legajo;
    }

    int Usuario::getlibrosPrestados(){
    return librosPrestados;
    }

    Libro Usuario::getLibro(){
    return l1;
    }

    void Usuario::setLibro(Libro _l1){
    l1 = _l1;
    }
   void Usuario::prestarLibro(Libro* libro){
    if(libro->getPrestado() == 0){
        libro->prestar(libro->getTitulo());  // usamos -> porque es puntero
        librosPrestados++;
    }
    }
   void Usuario::devolverLibro(Libro* libro){
    if(libro->getPrestado() == 1){
        libro->devolver(libro->getTitulo()); 
        if(librosPrestados > 0){
            librosPrestados--;
        }
    }
    }
    
   class Alumno : public Usuario{
    private:
    int año;
    public:
    Alumno();
    Alumno(long, int, int);
    Alumno(long, int, int, Libro);
    int getAño();
    void setAño(int);
    };
   Alumno::Alumno(){
    }

    Alumno::Alumno(long _legajo, int _librosPrestados, int _año) : Usuario(_legajo, _librosPrestados){
    año = _año;
    }

    Alumno::Alumno(long _legajo, int _librosPrestados, int _año, Libro _l1)
    : Usuario(_legajo, _librosPrestados, _l1){
    año = _año;
    }

    int Alumno::getAño(){
    return año;
    }

    void Alumno::setAño(int _año){
    año = _año;
    }

   class Profesor : public Usuario{
    private:
    string areaEspecializacion;
    public:
    Profesor();
    Profesor(long, int, string);
    Profesor(long, int, string, Libro);
    string getAreaEspecializacion();
    void setAreaEspecializacion(string);
    };

    Profesor::Profesor(){
    }

    Profesor::Profesor(long _legajo, int _librosPrestados, string _area)
    : Usuario(_legajo, _librosPrestados){
    areaEspecializacion = _area;
    }

    Profesor::Profesor(long _legajo, int _librosPrestados, string _area, Libro _l1)
    : Usuario(_legajo, _librosPrestados, _l1){
    areaEspecializacion = _area;
    }

    string Profesor::getAreaEspecializacion(){
    return areaEspecializacion;
    }

    void Profesor::setAreaEspecializacion(string _area){
    areaEspecializacion = _area;
    }

    //CONSULTAS AVANZADAS

    void buscarPorCategoria(Libro v[], int n, string cat){
    cout << "Categoria: " << cat << endl;
    for(int i=0;i<n;i++){
        if(v[i].getCategoria()==cat){
            cout << "- " << v[i].getTitulo() << endl;
             }
        }
    }

    void buscarPorAutor(Libro v[], int n, string au){
    cout << "Autor: " << au << endl;
    for(int i=0;i<n;i++){
        if(v[i].getAutor()==au){
            cout << "- " << v[i].getTitulo() << endl;
         }
     }
    }

    void top3MasPrestados(Libro v[], int n){
    int i1=-1,c1=-1, i2=-1,c2=-1, i3=-1,c3=-1;

    for(int i=0; i<n; i++){
        int c = v[i].getVecesPrestado();

        if(c > c1){
            i3=i2; c3=c2;
            i2=i1; c2=c1;
            i1=i;  c1=c;
        } else if(c > c2){
            i3=i2; c3=c2;
            i2=i;  c2=c;
        } else if(c > c3){
            i3=i;  c3=c;
        }
    }

    cout << "Top 3 mas prestados:" << endl;
    if(i1!=-1 && c1>0) cout << "1. " << v[i1].getTitulo() << " (" << c1 << ")" << endl;
    if(i2!=-1 && c2>0) cout << "2. " << v[i2].getTitulo() << " (" << c2 << ")" << endl;
    if(i3!=-1 && c3>0) cout << "3. " << v[i3].getTitulo() << " (" << c3 << ")" << endl;
    
    }


    int main(){
    // Libros (categorías: programacion, matematica, fisica)
    Libro a(1, "C++ Basico", "Autor A", 2015, "programacion", 0);
    Libro b(2, "Algebra I", "Autor B", 2012, "matematica",   0);
    Libro c(3, "Fisica I",  "Autor C", 2010, "fisica",       0);
    Libro d(4, "POO en C++","Autor D", 2018, "programacion", 0);

    Libro lista[4] = {a,b,c,d};

    // Usuarios
    Alumno   alu(1001, 0, 1);                 // legajo, librosPrestados, año
    Profesor prof(2001, 0, "programacion");   // legajo, librosPrestados, area

    // Listado inicial
    cout << "=== INICIAL ===" <<endl;
    lista[0].listarDisponibles(lista, 4);
    lista[0].listarPrestados(lista, 4);

    // Préstamos
    alu.prestarLibro(&lista[0]);   // C++ Basico
    prof.prestarLibro(&lista[2]);  // Fisica I

    cout << "=== TRAS PRESTAMOS ===" <<endl;
    lista[0].listarDisponibles(lista, 4);
    lista[0].listarPrestados(lista, 4);

    // Devoluciones
    alu.devolverLibro(&lista[0]);
    prof.devolverLibro(&lista[2]);

    cout << "=== TRAS DEVOLUCIONES ===" <<endl;
    lista[0].listarDisponibles(lista, 4);
    lista[0].listarPrestados(lista, 4);

    // Datos específicos
    cout << "Alumno anio: " << alu.getAño() << endl;
    cout << "Profesor area: " << prof.getAreaEspecializacion() << endl;

    // === Consultas avanzadas ===
    cout << "=== CONSULTAS ===" <<endl;
    buscarPorCategoria(lista, 4, "programacion");
    buscarPorAutor(lista, 4, "Autor C");
    top3MasPrestados(lista, 4);
    }