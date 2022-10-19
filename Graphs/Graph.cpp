#include <utility>
#include "Graph.h"

/**
 * Универсальный конструктор для графа в любом представлении.
 * @param matrix заданный граф.
 * @param mode способ представления графа (матрица смежности и т.д.).
 */
Graph::Graph(std::vector<std::vector<int>> matrix, int mode) {
    sGraph = std::move(matrix);
    sCurrentMode = mode;
}

/**
 * Конвертер из матрицы смежности в матрицу инцидентности.
 */
void Graph::FromAdjacencyToIncidenceMatrix()  {
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(sGraph.size());
    for (int i = 0; i < sGraph.size(); ++i)  {
        for (int j = 0; j < sGraph.size(); ++j)  {
            // Случай, если у нас дуга.
            if (sGraph[i][j] == 1 && sGraph[j][i] == 0)  {
                for (int row = 0; row < matrix.size(); ++row)  {
                    if (row == i)  {
                        matrix[row].emplace_back(1);
                    }  else if (row == j)  {
                        matrix[row].emplace_back(-1);
                    }  else  {
                        matrix[row].emplace_back(0);
                    }
                }
                // Случай, если у нас ребро.
            }  else  if (sGraph[i][j] == 1 && sGraph[j][i] == 1 && i < j)  {
                for (int row = 0; row < matrix.size(); ++row)  {
                    if (row == i || row == j)  {
                        matrix[row].emplace_back(1);
                    }  else  {
                        matrix[row].emplace_back(0);
                    }
                }
            }
        }
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертер из матрицы смежности в список смежности.
 */
void Graph::FromAdjacencyMatrixToList()  {
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(sGraph.size());
    for (int i = 0; i < sGraph.size(); ++i)  {
        for (int j = 0; j < sGraph.size(); ++j)  {
            if (sGraph[i][j] == 1)  {
                matrix[i].emplace_back(j+1);
            }
        }
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертер из матрицы смежности в список ребер.
 */
void Graph::FromAdjacencyMatrixToEdgeList()  {
    std::vector<std::vector<int>> matrix;
    sVerts = sGraph.size();
    for (int i = 0; i < sGraph.size(); ++i)  {
        for (int j = 0; j < sGraph.size(); ++j)  {
            if (sGraph[i][j] == 1)  {
                matrix.emplace_back(std::vector<int>{(i+1), (j+1)});
            }
        }
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертер из матрицы инцидентности в матрицу смежности.
 */
void Graph::FromIncidenceToAdjacencyMatrix()  {
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>
            (sGraph.size(), std::vector<int>(sGraph.size(), 0));
    for (int i = 0; i < sGraph[0].size(); ++i)  {
        // Пары чисел, где первое число в каждой паре - число из матрицы,
        // а второе - индекс строки матрицы, в которой он находится. В каждом столбце есть ровно 2 ненулевых числа,
        // поэтому нужны две пары.
        std::pair<int, int> x, y;
        for (int j = 0; j < sGraph.size(); ++j)  {
            if (abs(sGraph[j][i]) == 1)  {
                if (x.first == 0)  {
                    x = {sGraph[j][i], j};
                }  else  {
                    y = {sGraph[j][i], j} ;
                }
            }
        }
        if (x.first == 1 && y.first == 1)  {
            matrix[x.second][y.second] = 1;
            matrix[y.second][x.second] = 1;
        }  else  if (x.first == 1 && y.first == -1)  {
            matrix[x.second][y.second] = 1;
        }  else  {
            matrix[y.second][x.second] = 1;
        }
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертер из списка смежности в матрицу смежности.
 */
void Graph::FromAdjacencyListToMatrix()  {
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>
            (sGraph.size(), std::vector<int>(sGraph.size(), 0));
    for (int i = 0; i < sGraph.size(); ++i)  {
        for (int j = 0; j < sGraph[i].size(); ++j)  {
            matrix[i][sGraph[i][j]-1] = 1;
        }
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертер из списка ребер в матрицу смежности.
 */
void Graph::FromEdgeListToAdjacencyMatrix()  {
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>
            (sVerts, std::vector<int>(sVerts, 0));
    for (auto& row : sGraph) {
        matrix[row[0]-1][row[1]-1] = 1;
    }
    sGraph = std::move(matrix);
}

/**
 * Конвертирует граф в другое представление, либо ничего не делает,
 * если выбрано представление, совпадающее с текущим.
 * @param outputMode представление, в которое необходимо сконвертировать граф.
 */
void Graph::Convert(int outputMode)  {
    if (sCurrentMode == outputMode)  {
        return;
    }
    if (sCurrentMode == 1 && outputMode == 2)  {
        FromAdjacencyToIncidenceMatrix();
    }  else if (sCurrentMode == 1 && outputMode == 3)  {
        FromAdjacencyMatrixToList();
    }  else if (sCurrentMode == 1 && outputMode == 4)  {
        FromAdjacencyMatrixToEdgeList();
    }  else if (sCurrentMode == 2 && outputMode == 1)  {
        FromIncidenceToAdjacencyMatrix();
    }  else if (sCurrentMode == 2 && outputMode == 3)  {
        FromIncidenceToAdjacencyMatrix();
        FromAdjacencyMatrixToList();
    }  else if (sCurrentMode == 2 && outputMode == 4)  {
        FromIncidenceToAdjacencyMatrix();
        FromAdjacencyMatrixToEdgeList();
    }  else if (sCurrentMode == 3 && outputMode == 1)  {
        FromAdjacencyListToMatrix();
    }  else if (sCurrentMode == 3 && outputMode == 2)  {
        FromAdjacencyListToMatrix();
        FromAdjacencyToIncidenceMatrix();
    }  else if (sCurrentMode == 3 && outputMode == 4)  {
        FromAdjacencyListToMatrix();
        FromAdjacencyMatrixToEdgeList();
    }  else if (sCurrentMode == 4 && outputMode == 1)  {
        FromEdgeListToAdjacencyMatrix();
    }  else if (sCurrentMode == 4 && outputMode == 2)  {
        FromEdgeListToAdjacencyMatrix();
        FromAdjacencyToIncidenceMatrix();
    }  else if (sCurrentMode == 4 && outputMode == 3)  {
        FromEdgeListToAdjacencyMatrix();
        FromAdjacencyMatrixToList();
    }
    sCurrentMode = outputMode;
}

/**
 *  Проверка пустой ли граф.
 * @return true, если пустой, иначе false.
 */
bool Graph::IsEmpty() {
    return sGraph.empty() && sCurrentMode == 0;
}

/**
 * Функция производит подсчет степеней/полустепеней вершин и выводит их в поток.
 * @param oriented ориентированность графа.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::VerticesDegree(bool oriented, std::ostream &stream) {
    // Произвожу подсчет в матрице смежности, поэтому конвертирую в нее, подсчитываю и после конвертирую обратно.
    int mode = sCurrentMode;
    Convert(1);
    if (oriented)  {
        for (int i = 0; i < sGraph.size(); ++i)  {
            int inDegree = 0, outDegree = 0;
            stream << (i+1) << '\t';
            for (int j = 0; j < sGraph.size(); ++j)  {
                outDegree += sGraph[i][j];
            }
            for (auto& col : sGraph)  {
                inDegree += col[i];
            }
            stream << "In-degree: " << inDegree << '\t' << "Out-degree: " << outDegree << '\n';
        }
    }  else  {
        for (int i = 0; i < sGraph.size(); ++i)  {
            int degree = 0;
            stream << (i+1) << '\t';
            for (int j = 0; j < sGraph.size(); ++j)  {
                degree += sGraph[i][j];
            }
            stream << "Degree: " << degree << '\n';
        }
    }
    Convert(mode);
}

/**
 * Функция производит подсчет суммарного количества ребер/дуг и выводит его в поток.
 * @param oriented ориентированность графа.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::CountArcEdges(bool oriented, std::ostream& stream) {
    // Произвожу подсчет в списке ребер, поэтому конвертирую в него, подсчитываю и после конвертирую обратно.
    int mode = sCurrentMode;
    Convert(4);
    if (oriented)  {
        stream << "Arcs: " << sGraph.size() << '\n';
    }  else  {
        stream << "Edges: " << sGraph.size() / 2 << '\n';
    }
    Convert(mode);
}

/**
 * Функция, вызывающая конвертер и позже выводящая в полученном представлении граф в поток.
 * @param outputMode представление, в которое необходимо сконвертировать граф.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::Print(int outputMode, std::ostream& stream) {
    Convert(outputMode);
    if (outputMode == 1 || outputMode == 2)  {
        for (size_t i = 0; i < sGraph[0].size(); ++i)  {
            stream << '\t' << (i+1);
        }
        stream << '\n';
    }
    for (size_t i = 0; i < sGraph.size(); ++i)  {
        stream << (i+1) << '\t';
        for (int j : sGraph[i])  {
            stream << j << '\t';
        }
        stream << '\n';
    }
}

/**
 * Рекурсивный обходи графа в глубину.
 * @param start точка из которой начинаем обход.
 * @param visited множество, в котором содержатся посещенные вершины.
 * @param stream поток, в который нужно выводить информацию.
 * @param flag индикатор, что мы находимся у корня компоненты связности.
 */
void Graph::RecursiveDFS(int start, std::unordered_set<int>& visited, std::ostream& stream, bool flag) {
    visited.insert(start);
    stream << start << " ";
    for (int & i : sGraph[start-1])  {
        if  (!visited.contains(i))  {
            RecursiveDFS(i, visited, stream, false);
        }
    }
    // В случае, если у нас больше 1 компоненты связности, то далее они будут обходиться по мере возрастания чисел.
    if (flag)  {
        if (visited.size() != sGraph.size())  {
            for (int i = 1; i < sGraph.size(); ++i)  {
                if  (!visited.contains(i))  {
                    RecursiveDFS(i, visited, stream, false);
                }
            }
        }
        stream << '\n';
    }
}
/**
 * Функция для декомпозиции функции нерекурсивного обхода в глубину.
 * @param start точка из которой начинаем обход.
 * @param visited множество, в котором содержатся посещенные вершины.
 * @param stack стэк с вершинами, которые нужно обойти.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::DFS(int& start, std::unordered_set<int> &visited, std::stack<int>& stack, std::ostream& stream)  {
    while (!stack.empty())  {
        if (!visited.contains(stack.top()))  {
            visited.insert(stack.top());
            stream << stack.top() << " ";
        }
        // Удаляем из стэка верхнюю вершину, перед этим добавив ее в посещенные.
        // Далее добавляем в верхушку стека все вершины, смежные с удаленной.
        // Дубликаты допустимы, т.к. выше идет проверка на то, была ли эта вершина уже посещена.
        start = stack.top();
        stack.pop();
        for (int i = int(sGraph[start-1].size())-1; i >= 0; --i)  {
            if  (!visited.contains(sGraph[start-1][i]))  {
                stack.push(sGraph[start-1][i]);
            }
        }
    }
}

/**
 * Функция для нерекурсивного обхода графа в глубину.
 * @param start точка из которой начинаем обход.
 * @param visited множество, в котором содержатся посещенные вершины.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::NonRecursiveDFS(int start, std::unordered_set<int> &visited, std::ostream& stream) {
    visited.insert(start);
    std::stack<int> stack;
    stream << start << " ";
    for (int i = int(sGraph[start-1].size())-1; i >= 0; --i)  {
        stack.push(sGraph[start-1][i]);
    }
    DFS(start, visited, stack, stream);
    // В случае, если у нас больше 1 компоненты связности, то далее они будут обходиться по мере возрастания чисел.
    if (visited.size() != sGraph.size())  {
        for (int i = 1; i < sGraph.size(); ++i)  {
            if  (!visited.contains(i))  {
                visited.insert(i);
                stream << i << " ";
                for (int j = int(sGraph[i-1].size())-1; j >= 0; --j)  {
                    stack.push(sGraph[i-1][j]);
                }
                DFS(start, visited, stack, stream);
            }
        }
    }
    stream << '\n';
}

/**
 * Функция для декомпозиции функции нерекурсивного обхода в ширину.
 * @param start точка из которой начинаем обход.
 * @param visited множество, в котором содержатся посещенные вершины.
 * @param queue очередь с вершинами, которые нужно обойти.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::BFS(int &start, std::unordered_set<int> &visited, std::queue<int> &queue, std::ostream &stream) {
    while (!queue.empty())  {
        if (!visited.contains(queue.front()))  {
            visited.insert(queue.front());
            stream << queue.front() << " ";
        }
        // Удаляем из очереди вершину, стоящую спереди, перед этим добавив ее в посещенные.
        // Далее добавляем ставим в очередь все вершины, смежные с удаленной.
        // Дубликаты допустимы, т.к. выше идет проверка на то, была ли эта вершина уже посещена.
        start = queue.front();
        queue.pop();
        for (int & i : sGraph[start-1])  {
            if  (!visited.contains(i))  {
                queue.push(i);
            }
        }
    }
}

/**
 * Функция для нерекурсивного обхода графа в ширину.
 * @param start точка из которой начинаем обход.
 * @param visited множество, в котором содержатся посещенные вершины.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::NonRecursiveBFS(int start, std::unordered_set<int> &visited, std::ostream& stream) {
    visited.insert(start);
    std::queue<int> queue;
    stream << start << " ";
    for (int & i : sGraph[start-1])  {
        queue.push(i);
    }
    BFS(start, visited, queue, stream);
    // В случае, если у нас больше 1 компоненты связности, то далее они будут обходиться по мере возрастания чисел.
    if (visited.size() != sGraph.size())  {
        for (int i = 1; i < sGraph.size(); ++i)  {
            if  (!visited.contains(i))  {
                visited.insert(i);
                stream << i << " ";
                for (int j = int(sGraph[i-1].size())-1; j >= 0; --j)  {
                    queue.push(sGraph[i-1][j]);
                }
                BFS(start, visited, queue, stream);
            }
        }
    }
    stream << '\n';
}

/**
 * Функция для проверки корректности стартовой точки и запуска нужной функции обхода графа.
 * @param start точка из которой начинаем обход.
 * @param searchMode способ обхода графа.
 * @param stream поток, в который нужно выводить информацию.
 */
void Graph::GraphSearch(int start, int searchMode, std::ostream& stream)  {
    int mode = sCurrentMode;
    Convert(3);
    std::unordered_set<int> visited = {};
    try  {
        if (start < 1 || sGraph.size() < start)  {
            throw std::invalid_argument("");
        }
    }  catch(std::exception&)  {
        std::cout << "Error: invalid start point, try again!\n";
        Convert(mode);
        return;
    }
    switch (searchMode) {
        case 4:
            RecursiveDFS(start, visited, stream, true);
            break;
        case 5:
            NonRecursiveDFS(start, visited, stream);
            break;
        case 6:
            NonRecursiveBFS(start, visited, stream);
            break;
        default:
            break;
    }
    Convert(mode);
}