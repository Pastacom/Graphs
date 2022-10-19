#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_set>

/**
 * Класс, представляющий собой граф и операции доступные с ним.
 */
class Graph  {
private:
    // Заданный граф.
    inline static std::vector<std::vector<int>> sGraph;
    // Текущее представление графа.
    inline static int sCurrentMode = 0;
public:
    inline static size_t sVerts;
    // Универсальный конструктор для графа в любом представлении.
    explicit Graph (std::vector<std::vector<int>> matrix, int mode);
    // Конвертер из матрицы смежности в матрицу инцидентности.
    static void FromAdjacencyToIncidenceMatrix();
    // Конвертер из матрицы смежности в список смежности.
    static void FromAdjacencyMatrixToList();
    // Конвертер из матрицы смежности в список ребер.
    static void FromAdjacencyMatrixToEdgeList();
    // Конвертер из матрицы инцидентности в матрицу смежности.
    static void FromIncidenceToAdjacencyMatrix();
    // Конвертер из списка смежности в матрицу смежности.
    static void FromAdjacencyListToMatrix();
    // Конвертер из списка ребер в матрицу смежности.
    static void FromEdgeListToAdjacencyMatrix();
    // Конвертирует граф в другое представление, либо ничего не делает,
    // если выбрано представление, совпадающее с текущим.
    static void Convert(int outputMode);
    // Проверка пустой ли граф.
    static bool IsEmpty();
    // Подсчет степеней/полустепеней вершин.
    static void VerticesDegree(bool oriented, std::ostream& stream);
    // Подсчет суммарного количества ребер/дуг.
    static void CountArcEdges(bool oriented, std::ostream& stream);
    // Вызов конвертера и вывод графа в полученном представлении в поток.
    static void Print(int outputMode, std::ostream& stream);
    // Рекурсивный обход в глубину.
    static void RecursiveDFS(int start, std::unordered_set<int>& visited, std::ostream& stream, bool flag);
    // Вспомогательная функция для нерекурсивного обхода графа в глубину.
    static void DFS(int& start, std::unordered_set<int> &visited, std::stack<int>& stack, std::ostream& stream);
    // Нерекурсивный обход в глубину.
    static void NonRecursiveDFS(int start, std::unordered_set<int>& visited, std::ostream& stream);
    // Вспомогательная функция для нерекурсивного обхода графа в ширину.
    static void BFS(int& start, std::unordered_set<int> &visited, std::queue<int>& queue, std::ostream& stream);
    // Рекурсивный обход в ширину.
    static void NonRecursiveBFS(int start, std::unordered_set<int>& visited, std::ostream& stream);
    // Функция для проверки корректности стартовой точки и запуска нужной функции обхода графа.
    static void GraphSearch(int start, int searchMode, std::ostream& stream);
};

#endif //GRAPHS_GRAPH_H
