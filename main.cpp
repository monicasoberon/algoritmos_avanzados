#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Función para leer un archivo y devolver su contenido como un vector de chars
vector<char> readFile(const string& filename) {
    ifstream file(filename);

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open()) {
        cout << "main.cpp" << ": File \"" << filename << "\" not found\n";
        exit(-1);  // Salir del programa con un código de error
    }

    vector<char> content;
    char ch;
    while (file.get(ch)) {
        content.push_back(ch);
    }

    if (content.empty()) {
        cerr << "Error: File \"" << filename << "\" is empty.\n";
        exit(EXIT_FAILURE);  // Exit if the file is empty
    }

    file.close();  // Cerrar el archivo después de leerlo
    return content;
}

// Función similar a LCS que verifica si una secuencia está contenida en otra usando chars
void containsSequence(const vector<char>& transmission, const vector<char>& mcode) {
    // Check if the mcode is longer than the transmission right at the start of the function
    if (mcode.size() > transmission.size()) {
        cout << "false" << endl;  // Output false immediately if mcode is longer
        return;  // Exit the function early
    }
    int m = transmission.size();
    int n = mcode.size();

    // Tabla DP para guardar coincidencias
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int maxLen = 0;  // Máxima longitud encontrada
    int endPos = -1; // Posición final en transmission donde termina la coincidencia

    // Rellenar la tabla dp
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (transmission[i - 1] == mcode[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                // Verificar si toda la secuencia de mcode ha coincidido
                if (dp[i][j] == n) {  // Coincide con la longitud completa de mcode
                    endPos = i;
                    maxLen = n;
                }
            }
        }
    }

    if (maxLen == n) {
        cout << "true " << (endPos - n + 1) << endl;  // Posición base 1
    } else {
        cout << "false" << endl;
    }
}

// Función para encontrar el palíndromo más largo en una cadena de texto
pair<pair<int, int>, string> findLongestPalindrome(const string &content) {
    int start = 0, maxLength = 1; // Variables para la posición de inicio y la longitud del palíndromo más largo
    int n = content.size();       // Longitud del contenido

    string longestPal;

    for (int i = 0; i < n; ++i) {
        // Palíndromo impar
        int low = i, high = i;
        while (low >= 0 && high < n && content[low] == content[high]) {
            if (high - low + 1 > maxLength) {
                start = low;
                maxLength = high - low + 1;
                longestPal = content.substr(low, maxLength);
            }
            --low;
            ++high;
        }

        // Palíndromo par
        low = i, high = i + 1;
        while (low >= 0 && high < n && content[low] == content[high]) {
            if (high - low + 1 > maxLength) {
                start = low;
                maxLength = high - low + 1;
                longestPal = content.substr(low, maxLength);
            }
            --low;
            ++high;
        }
    }

    return {{start + 1, start + maxLength}, longestPal}; // Ajustar a base 1 y devolver también el palíndromo
}

// Función para encontrar el substring común más largo entre dos vectores de chars
void lcs(const vector<char>& t1, const vector<char>& t2) {
    int n = t1.size();
    int m = t2.size();
    vector<vector<int>> mlargo(n + 1, vector<int>(m + 1, 0)); // Matriz para almacenar longitudes
    int len = 0;  // Guardar la longitud de la substring común más larga
    int row = 0, col = 0;  // Guardar la posición de fin de la substring más larga

    // Llenar la matriz de longitud de substring común más larga
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (t1[i - 1] == t2[j - 1]) {
                mlargo[i][j] = mlargo[i - 1][j - 1] + 1;
                if (mlargo[i][j] > len) {
                    len = mlargo[i][j];
                    row = i;
                    col = j;
                }
            }
        }
    }

    // Si no hay substring común
    if (len == 0) {
        cout << "No hay substring común" << endl;
        return;
    }

    // Mostrar la posición inicial y final de la substring en el primer archivo
    cout << (row - len + 1) << " " << row << " ";
    for (int i = row - len; i < row; i++) {
        cout << t1[i];
    }
}

int main() {
    // Leer el contenido de los archivos usando la función readFile
    vector<char> mcode1_content = readFile("./mcode/mcode1.txt");
    vector<char> mcode2_content = readFile("./mcode/mcode2.txt");
    vector<char> mcode3_content = readFile("./mcode/mcode3.txt");
    vector<char> transmission1_content = readFile("./transmission/transmission1.txt");
    vector<char> transmission2_content = readFile("./transmission/transmission2.txt");

    // Parte 1: Verificar si los archivos mcode están contenidos en transmission1
    cout << "Parte 1:\n\n";
    containsSequence(transmission1_content, mcode1_content);
    containsSequence(transmission1_content, mcode2_content);
    containsSequence(transmission1_content, mcode3_content);

    // Verificar si los archivos mcode están contenidos en transmission2
    containsSequence(transmission2_content, mcode1_content);
    containsSequence(transmission2_content, mcode2_content);
    containsSequence(transmission2_content, mcode3_content);

    cout << endl;

    // Parte 2: Encontrar el palíndromo más largo en los archivos de transmisión
    cout << "Parte 2:\n\n";
    string transmission1_str(transmission1_content.begin(), transmission1_content.end());
    string transmission2_str(transmission2_content.begin(), transmission2_content.end());

    // Actualizar las variables para que coincidan con el nuevo tipo devuelto
    auto result1 = findLongestPalindrome(transmission1_str);
    auto result2 = findLongestPalindrome(transmission2_str);

    cout << result1.first.first << " " << (result1.first.second) << " " << result1.second << endl; // Posición inicial y final ajustada para inclusión
    cout << result2.first.first << " " << (result2.first.second) << " " << result2.second << endl;

    // Parte 3: Encontrar la substring común más larga entre transmission1 y transmission2
    cout << "\nParte 3:\n\n";
    lcs(transmission1_content, transmission2_content);

    return 0;
}
