#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <filesystem>
#include "Reader.h"
#include "Graph.h"

using namespace std;

/**
 * Функция для прочтения графа, задаваемого в виде матрицы смежности.
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param flag проверка, на то нужно ли читать информацию из файла.
 * @param oriented ориентированность графа.
 */
void ReadAdjacencyMatrix(size_t& verts, bool& flag, bool& oriented)  {
    string input; int value;
    if(!std::filesystem::exists("input.txt") && flag)  {
        return;
    }
    ifstream fin("input.txt");
    vector<vector<int>>matrix = vector<vector<int>>(verts, vector<int>(verts, 0));
    if (!flag)  {
        cout << "Enter the adjacency matrix:\n";
    }  else  {
        fin >> input;
    }
    for (int i = 0; i < verts; ++i)  {
        // Переменная нужна для правильной обработки ввода. Правильный ввод описан в README.txt.
        bool decrement = false;
        for (int j = 0; j < verts; ++j)  {
            if (flag)  {
                fin >> input;
            }  else  {
                cin >> input;
            }
            try  {
                value = stoi(input);
                // Проверка, что данные корректны для ориентированного и неориентированного графа и не образуется петля.
                if ((value != 0 && value != 1) || (value == 1 && i == j) || (!oriented && i > j &&
                value != matrix[j][i]))  {
                    throw invalid_argument("");
                }  else  {
                    matrix[i][j] = value;
                }
            }  catch(exception&)  {
                cout << "Error: invalid number at pos (" << (i+1) << ", " << (j+1) << "), try again!\n";
                if (flag)  {
                    return;
                }
                decrement = true;
            }
        }
        if (decrement)  {
            --i;
        }
    }
    new Graph(matrix, 1);
}

/**
 * Функция для удаления некорректных столбцов и дубликатов.
 * Она удаляет столбцы с петлями, дубликатами, при этом дубликат стоит после оригинала, и просто некорректные столбцы.
 * Пример дубликата:
 * 1 1        1 1
 * -1 1       1 1
 * При этом будет оставлен первый столбец в обоих случаях, т.к. был введен первым.
 * @param matrix заданный граф.
 */
void RemoveInvalidEdges(vector<vector<int>>& matrix)  {
    // Нахождение некорректных столбцов.
    for (size_t i = 0; i < matrix[0].size(); ++i)  {
        int counter = 0;
        bool flag = false;
        for (auto & row : matrix)  {
            if (row[i] == -1 && flag)  {
                counter = 0;
                break;
                // Столбец из двух -1 некорректен.
            }  else if (row[i] == -1 && !flag)  {
                ++counter;
                flag = true;
            }  else if (row[i] != 0)  {
                ++counter;
            }
        }
        // В столбце должно быть либо две 1, либо 1 и -1.
        if (counter != 2)  {
            for (auto & row : matrix)  {
                row.erase(next(row.begin(), static_cast<int>(i)));
            }
            --i;
        }
    }
    // Нахождение дубликатов.
    for (size_t i = 0; i < matrix[0].size(); ++i)  {
        for (size_t j = i + 1; j < matrix[0].size(); ++j)  {
            bool flag = true;
            bool similar = false;
            for (auto & row : matrix)  {
                // Может быть только в случае, если один из элементов - 0 => не дубликат.
                if (abs(row[i] + row[j]) == 1)  {
                    flag = false;
                    break;
                    // Единственный случай не дубликата, когда у нас элементы ненулевые расположены на одних строках,
                    // это когда в одной строке 1 -1, а в другой -1 1.
                }  else  if (abs(row[i]) == 1 && row[i] + row[j] == 0 && !similar)  {
                    flag = false;
                }  else  if (abs(row[i]) == 1 && row[i] + row[j] != 0)  {
                    similar = true;
                }
            }
            if (flag)  {
                for (auto & row : matrix)  {
                    row.erase(next(row.begin(), static_cast<int>(j)));
                }
                --j;
            }
        }
    }
}

/**
 * Функция для прочтения графа, задаваемого в виде матрицы инцидентности.
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param edges количество ребер/дуг графа.
 * @param flag проверка, на то нужно ли читать информацию из файла.
 * @param oriented ориентированность графа.
 */
void ReadIncidenceMatrix(size_t& verts, size_t& edges, bool& flag, bool& oriented)  {
    string input; int value;
    if(!std::filesystem::exists("input.txt") && flag)  {
        return;
    }
    ifstream fin("input.txt");
    vector<vector<int>>matrix = vector<vector<int>>(verts, vector<int>(edges, 0));
    if (!flag)  {
        cout << "Enter the incidence matrix:\n";
    }  else  {
        fin >> input;
        fin >> input;
    }
    for (int i = 0; i < verts; ++i)  {
        // Переменная нужна для правильной обработки ввода. Правильный ввод описан в README.txt.
        bool decrement = false;
        for (int j = 0; j < edges; ++j)  {
            if (flag)  {
                fin >> input;
            }  else  {
                cin >> input;
            }
            try  {
                value = stoi(input);
                // Проверка на то, что число является корректным для ориентированного и неориентированного графа.
                if (value != 0 && value != 1 && value != -1 || (!oriented && value == -1))  {
                    throw invalid_argument("");
                }  else  {
                    matrix[i][j] = value;
                }
            }  catch(exception&)  {
                cout << "Error: invalid number at pos (" << (i+1) << ", " << (j+1) << "), try again!\n";
                if (flag)  {
                    return;
                }
                decrement = true;
            }
        }
        if (decrement)  {
            --i;
        }
    }
    RemoveInvalidEdges(matrix);
    new Graph(matrix, 2);
}

/**
 * Функция для прочтения графа, задаваемого в виде списка смежности. (получилась большая, объяснил в README.txt)
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param flag проверка, на то нужно ли читать информацию из файла.
 * @param oriented ориентированность графа.
 */
void ReadAdjacencyList(size_t& verts, bool& flag, bool& oriented)  {
    string input; int value, edges;
    if(!std::filesystem::exists("input.txt") && flag)  {
        return;
    }
    ifstream fin("input.txt");
    vector<vector<int>>matrix = vector<vector<int>>(verts);
    // Необходимо добавление в множество и последующее копирование, для избегания дубликатов.
    vector<set<int>> filtered = vector<set<int>>(verts);
    if (!flag)  {
        cout << "Enter the adjacency list:\n";
    }  else  {
        fin >> input;
    }
    for (int i = 0; i < verts; ++i)  {
        if (flag)  {
            fin >> input;
        }  else  {
            cin >> input;
        }
        try  {
            edges = stoi(input);
            if (edges < 1)  {
                throw invalid_argument("");
            }
        }  catch(exception&)  {
            cout << "Error: invalid number at pos (" << (i+1) << "), try again!\n";
            if (flag)  {
                return;
            }
            --i;
            continue;
        }
        // Переменная нужна для правильной обработки ввода. Правильный ввод описан в README.txt.
        bool decrement = false;
        for (int j = 0; j < edges; ++j)  {
            if (flag)  {
                fin >> input;
            }  else  {
                cin >> input;
            }
            try  {
                value = stoi(input);
                // Проверка на то, что числа лежат в правильном диапазоне и что не образует петля.
                if (value < 1 || verts < value || value == (i+1))  {
                    throw invalid_argument("");
                }  else  {
                    filtered[i].insert(value);
                    if (!oriented) {
                        filtered[value-1].insert(i+1);
                    }
                }
            }  catch(exception&)  {
                cout << "Error: invalid number at pos (" << (i+1) << ", " << (j+1) << "), try again!\n";
                if (flag)  {
                    return;
                }
                decrement = true;
            }
        }
        if (decrement)  {
            --i;
        }
    }
    // Копирование данных из множеств в векторы.
    for (int i = 0; i < filtered.size(); ++i)  {
        for (int j = 0; j < filtered[i].size(); ++j)  {
            auto number = *next(filtered[i].begin(), j);
            matrix[i].push_back(number);
        }
    }
    new Graph(matrix, 3);
}

/**
 * Функция для удаления идентичных дуг.
 * Все ограничения в этом методе описаны в README.txt.
 * @param matrix заданный граф.
 */
void DeleteSimilarArcs(vector<vector<int>>& matrix)  {
    for (size_t i = 0; i < matrix.size(); ++i)  {
        for (size_t j = i + 1; j < matrix.size(); ++j)  {
            if (matrix[i][0] == matrix[j][0] && matrix[i][1] == matrix[j][1])  {
                matrix.erase(next(matrix.begin(), static_cast<int>(j)));
            }
        }
    }
}

/**
 * Функция для добавления обратных дуг. Нужно для неориентированного графа.
 * Все ограничения в этом методе описаны в README.txt.
 * @param matrix заданный граф.
 */
void MakeMirrorArcs(vector<vector<int>>& matrix)  {
    size_t size = matrix.size();
    for (size_t i = 0; i < size; ++i)  {
        auto vec = vector<int> {matrix[i][1], matrix[i][0]};
        matrix.emplace_back(vec);
    }
}

/**
 * Функция для прочтения графа, задаваемого в виде списка ребер.
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param edges количество ребер/дуг графа.
 * @param flag проверка, на то нужно ли читать информацию из файла.
 * @param oriented ориентированность графа.
 */
void ReadEdgeList(size_t& verts, size_t& edges, bool& flag, bool& oriented)  {
    string input; int value;
    if(!std::filesystem::exists("input.txt") && flag)  {
        return;
    }
    ifstream fin("input.txt");
    vector<vector<int>>matrix = vector<vector<int>>(edges, vector<int>(2, 0));
    Graph::sVerts = verts;
    if (!flag)  {
        cout << "Enter the edge list:\n";
    }  else  {
        fin >> input;
        fin >> input;
    }
    for (int i = 0; i < edges; ++i)  {
        // Переменная нужна для правильной обработки ввода. Правильный ввод описан в README.txt.
        bool decrement = false;
        for (int j = 0; j < 2; ++j)  {
            if (flag)  {
                fin >> input;
            }  else  {
                cin >> input;
            }
            try  {
                value = stoi(input);
                // Проверка, что числа лежат в нужном диапазоне и что не образуется петля.
                if (value < 1 || verts < value || (j == 1 && matrix[i][0] == value))  {
                    throw invalid_argument("");
                }  else  {
                    matrix[i][j] = value;
                }
            }  catch(exception&)  {
                if (flag)  {
                }
                cout << "Error: invalid number at pos (" << (i+1) << ", " << (j+1) << "), try again!\n";
                if (flag)  {
                    return;
                }
                decrement = true;
            }
        }
        if (decrement)  {
            --i;
        }
    }
    if  (!oriented)  {
        MakeMirrorArcs(matrix);
    }
    DeleteSimilarArcs(matrix);
    new Graph(matrix, 4);
}


/**
 * Функция для получения размера графа из консоли.
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param edges количество ребер/дуг графа.
 * @param graphMode способ задания графа (матрица смежности и т.д.).
 * @param oriented ориентированность графа.
 */
void GetSizeFromConsole(size_t& verts, size_t& edges, int& graphMode, bool& oriented)  {
    string input;
    do  {
        cout << "Input number of vertices:";
        cin >> input;
        try  {
            verts = stoi(input);
        }  catch(exception&)  {
            cout << "Error: invalid number of vertices, try again!";
            continue;
        }
    }  while (verts < 1 || 30 < verts);
    if  (graphMode == 2 || (graphMode == 4 && !oriented))  {
        do  {
            cout << "Input number of edges:";
            cin >> input;
            try  {
                edges = stoi(input);
            }  catch(exception&)  {
                cout << "Error: invalid number of edges, try again!";
                continue;
            }
        }  while (edges < 0 || 435 < edges);
    }
    if  (graphMode == 4 && oriented)  {
        do  {
            cout << "Input number of arcs:";
            cin >> input;
            try  {
                edges = stoi(input);
            }  catch(exception&)  {
                cout << "Error: invalid number of arcs, try again!";
                continue;
            }
        }  while (edges < 0 || 870 < edges);
    }
}

/**
 * Функция для получения размера графа из файла.
 * Все ограничения в этом методе описаны в README.txt.
 * @param verts количество вершин графа.
 * @param edges количество ребер/дуг графа.
 * @param graphMode способ задания графа (матрица смежности и т.д.).
 * @param oriented ориентированность графа.
 */
void GetSizeFromFile(size_t& verts, size_t& edges, int& graphMode, bool& oriented)  {
    string input;
    if(!std::filesystem::exists("input.txt"))  {
        return;
    }
    ifstream fin("input.txt");
    fin >> input;
    try  {
        verts = stoi(input);
        if (verts < 1 || 30 < verts)  {
            throw invalid_argument("");
        }
    }  catch(exception&)  {
        cout << "Error: invalid number of vertices, try again!";
        return;
    }
    if  (graphMode == 2 || (graphMode == 4 && !oriented))  {
        fin >> input;
        try  {
            edges = stoi(input);
            if (edges < 0 || 435 < edges) {
                throw invalid_argument("");
            }
        }  catch(exception&)  {
            cout << "Error: invalid number of edges, try again!";
            return;
        }
    }
    if  (graphMode == 4 && oriented)  {
        fin >> input;
        try  {
            edges = stoi(input);
            if (edges < 0 || 870 < edges) {
                throw invalid_argument("");
            }
        }  catch(exception&)  {
            cout << "Error: invalid number of arcs, try again!";
            return;
        }
    }
}

/**
 * Распределяющая функция, вызывает функции для чтения графа в разных представлениях.
 * @param verts количество вершин графа.
 * @param edges количество ребер/дуг графа.
 * @param graphMode способ задания графа (матрица смежности и т.д.).
 * @param flag проверка, на то нужно ли читать информацию из файла.
 * @param oriented ориентированность графа.
 */
void Read(size_t verts, size_t edges, int& graphMode, bool flag, bool& oriented)  {
    switch (graphMode) {
        case 1:
            ReadAdjacencyMatrix(verts, flag, oriented);
            break;
        case 2:
            ReadIncidenceMatrix(verts, edges, flag, oriented);
            break;
        case 3:
            ReadAdjacencyList(verts, flag, oriented);
            break;
        case 4:
            ReadEdgeList(verts, edges, flag, oriented);
            break;
        default:
            break;
    }
}

/**
 * Распределяющая функция, вызывает функции для получения размера и прочтения графа в разных представлениях.
 * @param readMode способ чтения: из файла/ из консоли.
 * @param graphMode способ задания графа (матрица смежности и т.д.).
 * @param oriented ориентированность графа.
 */
void ReadGraph(int readMode, int graphMode, bool oriented)  {
    size_t verts, edges;
    if (readMode == 1)  {
        GetSizeFromConsole(verts, edges, graphMode, oriented);
        Read(verts, edges, graphMode, false, oriented);
    }  else  {
        GetSizeFromFile(verts, edges, graphMode, oriented);
        Read(verts, edges, graphMode, true, oriented);
    }
}