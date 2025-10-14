#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Convierte texto normal a cadena binaria 
string textoABinario(const string &texto) {
    string binario = "";
    for (unsigned char c : texto) {
        for (int i = 7; i >= 0; i--) {
            binario += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return binario;
}

// Convierte una cadena binaria a texto ASCII
string binarioATexto(const string &binario) {
    string texto = "";
    for (size_t i = 0; i + 7 < binario.size(); i += 8) {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++) {
            if (binario[i + j] == '1')
                c |= (1 << (7 - j));
        }
        texto += c;
    }
    return texto;
}

// Invierte bits (1-0)
string invertirBits(const string &s) {
    string r = s;
    for (size_t i = 0; i < s.size(); i++)
        r[i] = (s[i] == '1') ? '0' : '1';
    return r;
}

// Invierte cada k bits del bloque (para método 1)
string invertirCadaK(const string &s, int k) {
    string r = s;
    for (size_t i = 0; i < s.size(); i += k)
        for (int j = 0; j < k && (i + j) < s.size(); j++)
            r[i + j] = (s[i + j] == '1') ? '0' : '1';
    return r;
}

// Rota bits a la derecha 
string rotarDerecha(const string &s) {
    if (s.empty()) return s;
    string r = s;
    char ultimo = s[s.size() - 1];
    for (int i = (int)s.size() - 1; i > 0; i--)
        r[i] = r[i - 1];
    r[0] = ultimo;
    return r;
}

// Rota bits a la izquierda
string rotarIzquierda(const string &s) {
    if (s.empty()) return s;
    string r = s;
    char primero = s[0];
    for (size_t i = 0; i + 1 < s.size(); i++)
        r[i] = s[i + 1];
    r[s.size() - 1] = primero;
    return r;
}

// Cuenta número de unos y ceros
void contarBits(const string &bloque, int &unos, int &ceros) {
    unos = ceros = 0;
    for (char b : bloque)
        (b == '1') ? unos++ : ceros++;
}
// MÉTODO 1 DE CODIFICACIÓN Y DECODIFICACIÓN
string metodo1Codificar(const string &bits, int n) {
    string resultado = "";
    string anterior = "";

    for (size_t i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        while (bloque.size() < (size_t)n) bloque += '0';

        string codificado;
        if (i == 0) {
            codificado = invertirBits(bloque);
        } else {
            int unos, ceros;
            contarBits(anterior, unos, ceros);
            if (unos == ceros) codificado = invertirBits(bloque);
            else if (ceros > unos) codificado = invertirCadaK(bloque, 2);
            else codificado = invertirCadaK(bloque, 3);
        }
        resultado += codificado;
        anterior = bloque;
    }
    return resultado;
}

string metodo1Decodificar(const string &bits, int n) {
    string resultado = "";
    string anterior = "";

    for (size_t i = 0; i < bits.size(); i += n) {
        string bloqueCod = bits.substr(i, n);
        while (bloqueCod.size() < (size_t)n) bloqueCod += '0';

        string bloqueDec;
        if (i == 0) {
            bloqueDec = invertirBits(bloqueCod);
        } else {
            int unos, ceros;
            contarBits(anterior, unos, ceros);
            if (unos == ceros) bloqueDec = invertirBits(bloqueCod);
            else if (ceros > unos) bloqueDec = invertirCadaK(bloqueCod, 2);
            else bloqueDec = invertirCadaK(bloqueCod, 3);
        }
        resultado += bloqueDec;
        anterior = bloqueDec;
    }
    return resultado;
}

// MÉTODO 2 DE CODIFICACIÓN Y DECODIFICACIÓN
string metodo2Codificar(const string &bits, int n) {
    string resultado = "";
    for (size_t i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        while (bloque.size() < (size_t)n) bloque += '0';
        resultado += rotarDerecha(bloque);
    }
    return resultado;
}

string metodo2Decodificar(const string &bits, int n) {
    string resultado = "";
    for (size_t i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        while (bloque.size() < (size_t)n) bloque += '0';
        resultado += rotarIzquierda(bloque);
    }
    return resultado;
}

void codificarArchivo() {
    string entrada, salida;
    int metodo, n;

    cout << "Nombre del archivo de entrada (texto): ";
    cin >> entrada;
    cout << "Nombre del archivo de salida (bits): ";
    cin >> salida;
    cout << "Semilla n: ";
    cin >> n;
    cout << "Metodo (1 o 2): ";
    cin >> metodo;

    ifstream in(entrada);
    if (!in.is_open()) {
        cout << "Error: No se puede abrir el archivo.\n";
        return;
    }

    string texto((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string bits = textoABinario(texto);
    string codificado = (metodo == 1) ? metodo1Codificar(bits, n) : metodo2Codificar(bits, n);

    ofstream out(salida);
    out << codificado;
    out.close();
    cout << "Archivo codificado correctamente.\n";
}

void decodificarArchivo() {
    string entrada, salida;
    int metodo, n;

    cout << "Archivo codificado (bits): ";
    cin >> entrada;
    cout << "Archivo de salida (texto): ";
    cin >> salida;
    cout << "Semilla n: ";
    cin >> n;
    cout << "Metodo (1 o 2): ";
    cin >> metodo;

    ifstream in(entrada);
    if (!in.is_open()) {
        cout << "Error: No se puede abrir el archivo.\n";
        return;
    }

    string bits((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string decodificado = (metodo == 1) ? metodo1Decodificar(bits, n) : metodo2Decodificar(bits, n);
    string texto = binarioATexto(decodificado);

    ofstream out(salida, ios::binary);
    out << texto;
    out.close();
    cout << "Archivo decodificado correctamente.\n";
}


