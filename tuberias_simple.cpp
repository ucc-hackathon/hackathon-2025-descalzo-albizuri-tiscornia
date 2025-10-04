#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

// Estructura para las conexiones de cada pieza
struct Conexiones {
    bool norte, sur, este, oeste;
};

// Mapa global: símbolo -> conexiones (más eficiente que vector con búsqueda, podríamos haber hecho un vector pero la búsqueda tarda más y me hace el codigo más largo)
map<string, Conexiones> PIEZAS_CONEXIONES;


/*Un std::map es un contenedor asociativo que almacena datos en pares clave-valor (como un diccionario en la vida real).
Función: Te permite buscar un valor de forma muy rápida y eficiente usando su llave (clave).
--> es lo que me va a ayudar en el void de abajo*/

// --- INICIALIZACIÓN ---
void inicializar_piezas() {
    PIEZAS_CONEXIONES["╣"] = {true, true, false, true};   // N, S, O
    PIEZAS_CONEXIONES["║"] = {true, true, false, false};  // N, S
    PIEZAS_CONEXIONES["╗"] = {false, true, false, true};  // S, O
    PIEZAS_CONEXIONES["╝"] = {true, false, false, true};  // N, O
    PIEZAS_CONEXIONES["╚"] = {true, false, true, false};  // N, E
    PIEZAS_CONEXIONES["╔"] = {false, true, true, false};  // S, E
    PIEZAS_CONEXIONES["╩"] = {true, false, true, true};   // N, E, O
    PIEZAS_CONEXIONES["╦"] = {false, true, true, true};   // S, E, O
    PIEZAS_CONEXIONES["╠"] = {true, true, true, false};   // N, S, E
    PIEZAS_CONEXIONES["═"] = {false, false, true, true};  // E, O
    PIEZAS_CONEXIONES["╬"] = {true, true, true, true};    // N, S, E, O
}

// --- VALIDACIÓN DE CONEXIONES ---
bool es_conexion_valida(const string& origen, int dr, int dc, const string& destino) {
    //hacemos el paso por referencia para trabajar directamente con el string de destino que le pasemos y no se cree una copia en la memoria
    //usamos el const por las dudas ya que solo vamos a leer la string
    if (origen == " " || destino == " ") return false;
    
    Conexiones c1 = PIEZAS_CONEXIONES[origen];
    Conexiones c2 = PIEZAS_CONEXIONES[destino];

    //Aquí, el map busca el string origen o destino y devuelve la estructura Conexiones asociada a esa pieza (es decir, si tiene salida Norte, Sur, Este u Oeste). El resultado se guarda en c1.

    if (dr == -1) return c1.norte && c2.sur;      // Norte
    if (dr == 1)  return c1.sur && c2.norte;      // Sur
    if (dc == 1)  return c1.este && c2.oeste;     // Este
    if (dc == -1) return c1.oeste && c2.este;     // Oeste
    


    /* El valor de dr (cambio de fila) y dc (cambio de columna) en la función es_conexion_valida no se pasan desde el exterior, sino que se generan y pasan dentro de la función dfs (Búsqueda en Profundidad).*/
    return false;
}

// --- DFS PARA CALCULAR PUNTUACIÓN , se usa para explorar un grafo---

//Depth First Search o Búsqueda en Profundidad

void dfs(const vector<vector<string>>& tablero, int N, int r, int c, 
         vector<vector<bool>>& visitado, int& longitud, int& conexiones) {
    
    // 1. Condición de Parada (Base Case): Fuera de límites, ya visitado, o celda vacía.
    if (r < 0 || r >= N || c < 0 || c >= N || visitado[r][c] || tablero[r][c] == " ") 
        return;
    
    visitado[r][c] = true;
    longitud++;
    
    // Direcciones: Norte, Sur, Este, Oeste
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && tablero[nr][nc] != " ") {
            if (es_conexion_valida(tablero[r][c], dr[i], dc[i], tablero[nr][nc])) {
                conexiones++;
                if (!visitado[nr][nc]) {
                    dfs(tablero, N, nr, nc, visitado, longitud, conexiones);
                }
            }
        }
    }
}

long long calcular_puntuacion(const vector<vector<string>>& tablero, int N) {
    long long puntuacion = 0;
    vector<vector<bool>> visitado(N, vector<bool>(N, false));
    
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (tablero[r][c] != " " && !visitado[r][c]) {
                int longitud = 0, conexiones = 0;
                dfs(tablero, N, r, c, visitado, longitud, conexiones);
                if (longitud > 0) {
                    puntuacion += (long long)(conexiones / 2) * longitud;
                }
            }
        }
    }
    return puntuacion;
}

// --- MOSTRAR TABLERO ---
void mostrar_tablero(const vector<vector<string>>& tablero, int N) {
    cout << "\n  ";
    for (int j = 1; j <= N; j++) cout << " " << j << " ";
    cout << endl;
    
    for (int i = 0; i < N; i++) {
        cout << (i + 1 < 10 ? " " : "") << i + 1;
        for (int j = 0; j < N; j++) {
            cout << "|" << (tablero[i][j] == " " ? " " : tablero[i][j]) << " ";
        }
        cout << "|" << endl;
    }
}

// --- MAIN ---
int main() {
    srand(time(0));
    inicializar_piezas();
    
    // Configuración con validación obligatoria
    int N;
    cout << "JUEGO DE TUBERIAS (UTF-8)\n";
    cout << "--------------------------\n";
    
    do {
        cout << "Ingrese el tamano del tablero (N*N), min (8x8) max (20x20): ";
        cin >> N;
        
        if (cin.fail()) {
            cout << "Error: Debe ingresar un numero valido." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            N = 0; // Forzar que continue el bucle
        } else if (N < 8 || N > 20) {
            cout << "Error: El tamano debe estar entre 8 y 20. Intente nuevamente." << endl;
        }
    } while (N < 8 || N > 20);
    
    // Crear lista de piezas disponibles
    vector<string> piezas;
    for (const auto& p : PIEZAS_CONEXIONES) {
        piezas.push_back(p.first);
    }
    
    // Inicializar tablero y piezas del usuario
    vector<vector<string>> tablero(N, vector<string>(N, " "));
    int tamanio_user = (N * N) / 2;
    vector<string> user_piezas(tamanio_user);
    vector<bool> user_piezas_usadas(tamanio_user, false);
    
    for (int i = 0; i < tamanio_user; i++) {
        user_piezas[i] = piezas[rand() % piezas.size()];
    }
    
    cout << "\n***** PIEZAS ASIGNADAS AL USUARIO *****" << endl;
    for (int i = 0; i < tamanio_user; i++) {
        cout << i + 1 << ": " << user_piezas[i] << "  ";
    }
    cout << endl;
    
    mostrar_tablero(tablero, N);
    
    // --- JUEGO ---
    int total_piezas = 0, max_piezas = N * N;
    int row = 0, col = 0;
    int user_pieces_used = 0;
    
    cout << "\n--- INICIO DEL JUEGO ---" << endl;
    
    while (total_piezas < max_piezas) {
        // TURNO JUGADOR
        if (user_pieces_used < tamanio_user && total_piezas < max_piezas) {
            cout << "\nTurno JUGADOR. Posicion: (" << row + 1 << ", " << col + 1 << ")" << endl;
            cout << "Disponibles: ";
            for (int i = 0; i < tamanio_user; i++) {
                if (!user_piezas_usadas[i]) {
                    cout << i + 1 << "-" << user_piezas[i] << "  ";
                }
            }
            cout << "\nElige indice (1-" << tamanio_user << "): ";
            
            int idx;
            if (!(cin >> idx) || idx < 1 || idx > tamanio_user || user_piezas_usadas[idx - 1]) {
                cout << "Invalido. Pierdes turno." << endl;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            } else {
                tablero[row][col] = user_piezas[idx - 1];
                user_piezas_usadas[idx - 1] = true;
                user_pieces_used++;
                total_piezas++;
                
                cout << "Puntuacion: " << calcular_puntuacion(tablero, N) << endl;
                
                if (total_piezas >= max_piezas) {
                    mostrar_tablero(tablero, N);
                    break;
                }
            }
            
            mostrar_tablero(tablero, N);
            if (++col >= N) { col = 0; row++; }
        }
        
        // TURNO COMPUTADORA
        if (total_piezas < max_piezas) {
            string pieza_pc = piezas[rand() % piezas.size()];
            cout << "\nTurno COMPUTADORA. Coloca '" << pieza_pc << "' en (" 
                 << row + 1 << ", " << col + 1 << ")" << endl;
            
            tablero[row][col] = pieza_pc;
            total_piezas++;
            
            cout << "Puntuacion: " << calcular_puntuacion(tablero, N) << endl;
            
            if (total_piezas >= max_piezas) {
                mostrar_tablero(tablero, N);
                break;
            }
            
            mostrar_tablero(tablero, N);
            if (++col >= N) { col = 0; row++; }
        }
    }
    
    cout << "\n--- JUEGO TERMINADO ---" << endl;
    cout << "Puntuacion final: " << calcular_puntuacion(tablero, N) << endl;
    
    return 0;
}

