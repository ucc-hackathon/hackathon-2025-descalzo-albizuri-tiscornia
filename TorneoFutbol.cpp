#include <iostream>
using namespace std;

// clases equipo

class Equipo
{
private:
    string nombre;

public:
    Equipo();
    Equipo(string n);
    string getNombre();
    void setNombre(string);
    ~Equipo();
};

// Metodos clases equipo

Equipo::Equipo()
{
    nombre = "";
}
Equipo::Equipo(string n)
{
    nombre = n;
}
string Equipo::getNombre()
{
    return nombre;
}
void Equipo::setNombre(string n)
{
    nombre = n;
}
Equipo::~Equipo(){}

// clase partido

class Partido
{
private:
    Equipo Equipo1;
    Equipo Equipo2;
    int golesEquipo1;
    int golesEquipo2;

public:
    Partido();
    Partido(int g1, int g2);
    Partido(Equipo eq1, Equipo eq2, int g1, int g2);
    Equipo getEquipo1();
    Equipo getEquipo2();
    int getgolesEquipo1();
    int getgolesEquipo2();
    void setEquipo1(Equipo);
    void setEquipo2(Equipo);
    void setgolesEquipo1(int);
    void setgolesEquipo2(int);
    ~Partido();
};

// metodos clase partido

Partido::Partido()
{
    golesEquipo1 = 0;
    golesEquipo2 = 0;
}

Partido::Partido(int g1, int g2)
{
    golesEquipo1 = g1;
    golesEquipo2 = g2;
}

Partido::Partido(Equipo eq1, Equipo eq2, int g1, int g2)
{
    Equipo1 = eq1;
    Equipo2 = eq2;
    golesEquipo1 = g1;
    golesEquipo2 = g2;
}

Equipo Partido::getEquipo1()
{
    return Equipo1;
}

Equipo Partido::getEquipo2()
{
    return Equipo2;
}

int Partido::getgolesEquipo1()
{
    return golesEquipo1;
}

int Partido::getgolesEquipo2()
{
    return golesEquipo2;
}

void Partido::setEquipo1(Equipo eq)
{
    Equipo1 = eq;
}

void Partido::setEquipo2(Equipo eq)
{
    Equipo2 = eq;
}

void Partido::setgolesEquipo1(int g)
{
    golesEquipo1 = g;
}

void Partido::setgolesEquipo2(int g)
{
    golesEquipo2 = g;
}

Partido::~Partido() {}

int main()
{

    Equipo ucc("UCC");
    Equipo unc("UNC");
    Equipo utn("UTN");
    Equipo unrc("UNRC");
    Equipo ubp("UBP");
    Equipo ues21("UES21");

    string nombresEquipos[6] = {"UCC", "UNC", "UTN", "UNRC", "UBP", "UES21"};
    int puntajesEquipos[6] = {0, 0, 0, 0, 0, 0};
    Partido Partidos[15] = {
        Partido(unrc, ubp, 0, 0),
        Partido(ucc, unrc, 3, 0),
        Partido(utn, ubp, 2, 2),
        Partido(unc, ues21, 3, 1),
        Partido(ubp, ues21, 2, 1),
        Partido(ucc, utn, 4, 1),
        Partido(unc, unrc, 2, 2),
        Partido(ucc, ubp, 0, 2),
        Partido(unc, utn, 0, 1),
        Partido(ucc, unc, 2, 1),
        Partido(unrc, ubp, 2, 1),
        Partido(unc, ubp, 1, 3),
        Partido(utn, ues21, 1, 0),
        Partido(utn, unrc, 0, 1),
        Partido(unrc, ues21, 2, 3)};

    int n = 15;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j) // n-i-1 no compara los elementos
                                            // que ya estan en su lugar
        {
            int goles1 = Partidos[j].getgolesEquipo1() + Partidos[j].getgolesEquipo2();
            int goles2 = Partidos[j + 1].getgolesEquipo1() + Partidos[j + 1].getgolesEquipo2();

            if (goles1 < goles2)
            {
                Partido temp = Partidos[j];
                Partidos[j] = Partidos[j + 1];
                Partidos[j + 1] = temp;
            }
        }
    }

    cout << "--- Partidos Ordenados por Goles (de Mayor a Menor) ---" << endl;
    for (int i = 0; i < 15; ++i)
    {
        int totalGoles = Partidos[i].getgolesEquipo1() + Partidos[i].getgolesEquipo2();
        cout << Partidos[i].getEquipo1().getNombre() << " (" << Partidos[i].getgolesEquipo1() << ") vs "
             << Partidos[i].getEquipo2().getNombre() << " (" << Partidos[i].getgolesEquipo2() << ") - Total: "
             << totalGoles << endl;
    }
    cout << endl;

    for (int i = 0; i < 15; ++i)
    {
        string nombreEq1 = Partidos[i].getEquipo1().getNombre();
        string nombreEq2 = Partidos[i].getEquipo2().getNombre();

        int pos1 = -1, pos2 = -1;
        for (int j = 0; j < 6; ++j)
        {
            if (nombresEquipos[j] == nombreEq1)
                pos1 = j;
            if (nombresEquipos[j] == nombreEq2)
                pos2 = j;
        }

        if (Partidos[i].getgolesEquipo1() > Partidos[i].getgolesEquipo2())
        {
            puntajesEquipos[pos1] += 3;
        }
        else if (Partidos[i].getgolesEquipo2() > Partidos[i].getgolesEquipo1())
        {
            puntajesEquipos[pos2] += 3;
        }
        else
        {
            puntajesEquipos[pos1] += 1;
            puntajesEquipos[pos2] += 1;
        }
    }

    string primerLugar = "", segundoLugar = "", tercerLugar = "";
    int maxPuntos = -1, segundoMaxPuntos = -1, tercerMaxPuntos = -1;
    int pos1 = -1, pos2 = -1, pos3 = -1;

    for (int i = 0; i < 6; ++i)
    {
        if (puntajesEquipos[i] > maxPuntos)
        {
            maxPuntos = puntajesEquipos[i];
            primerLugar = nombresEquipos[i];
            pos1 = i;
        }
    }

    for (int i = 0; i < 6; ++i)
    {
        if (i != pos1 && puntajesEquipos[i] > segundoMaxPuntos)
        {
            segundoMaxPuntos = puntajesEquipos[i];
            segundoLugar = nombresEquipos[i];
            pos2 = i;
        }
    }

    for (int i = 0; i < 6; ++i)
    {
        if (i != pos1 && i != pos2 && puntajesEquipos[i] > tercerMaxPuntos)
        {
            tercerMaxPuntos = puntajesEquipos[i];
            tercerLugar = nombresEquipos[i];
            pos3 = i;
        }
    }

    cout << "--- Tabla de Posiciones Final ---" << endl;
    cout << "1er Lugar: " << primerLugar << " con " << maxPuntos << " puntos." << endl;
    cout << "2do Lugar: " << segundoLugar << " con " << segundoMaxPuntos << " puntos." << endl;
    cout << "3er Lugar: " << tercerLugar << " con " << tercerMaxPuntos << " puntos." << endl;

    return 0;
}
