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
