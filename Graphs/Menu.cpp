#include "Menu.h"
#include "Reader.h"
#include "Graph.h"
#include <iostream>
#include <fstream>

using  namespace  std;

/**
 * Функция для считывания ориентированности графа.
 * @param oriented ориентированность графа.
 */
void OrientedMode(bool& oriented)  {
    string result;
    do  {
        cout << "Is graph oriented?(y/n)\n";
        cin >> result;
        if (result == "y")  {
            oriented = true;
        }  else if (result == "n")  {
            oriented = false;
        }
    } while (result != "y" && result !="n");
}

/**
 * Функция для определения откуда/куда будет записываться информация.
 * @param readMode Источник считывания информации: консоль/файл.
 */
void ReadWriteMode(int& readMode)  {
    string input;
    do  {
        cout << "Graph read/write modes:\n1) From/to a console\n2) From/to a file\n";
        cin >> input;
        try  {
            readMode = stoi(input);
        }  catch(exception&)  {
            cout << "Error: invalid number, try again!\n";
            continue;
        }
    } while (readMode < 1 || 2 < readMode);
}

/**
 * Функция для определения формата введения графа.
 * @param graphMode способ задания графа (матрица смежности и т.д.).
 */
void GraphMode(int& graphMode)  {
    string input;
    do  {
        cout << "Graph representation:\n1) Adjacency matrix\n2) Incidence matrix\n"
                "3) Adjacency list\n4) Edge list\n";
        cin >> input;
        try  {
            graphMode = stoi(input);
        }  catch(exception&)  {
            cout << "Error: invalid number, try again!\n";
            continue;
        }
    } while (graphMode < 1 || 4 < graphMode);
}

/**
 * Функция для зацикливания программы.
 * @param loop продолжить работу или прервать.
 */
void Loop(string& loop)  {
    do  {
        cout << "Continue?(y/n)\n";
        cin >> loop;
    }  while (loop != "n" && loop != "y");
}

/**
 * Функция для определения действия, которое необходимо совершить над графом.
 * В случае конвертации и вывода графа в новом представлении, также определяется это представление.
 * @param action действие, которое необходимо выполнить с графом.
 * @param mode способ задания графа (матрица смежности и т.д.).
 */
void GetAction(int& action, int& mode)  {
    string input;
    do  {
        cout << "Actions with graph:\n1) Vertices degree\n2) Total number of edges/arcs\n"
                "3) Convert and output graph <1/2/3/4>\n4) Recursive DFS <start_point>\n"
                "5) Non-recursive DFS <start_point>\n6) Recursive BFS <start_point>\n"
                "Where:\n1 - Adjacency matrix\n2 - Incidence matrix\n"
                "3 - Adjacency list\n4 - Edge list\n";
        cin >> input;
        try  {
            action = stoi(input);
        }  catch(exception&)  {
            cout << "Error: invalid number, try again!\n";
            continue;
        }
        if (action == 3 || (3 < action && action < 7))  {
            cin >> input;
            try  {
                mode = stoi(input);
            }  catch(exception&)  {
                cout << "Error: invalid number, try again!\n";
                continue;
            }
        }
    } while (action < 1 || 6 < action || (action == 3 && (mode < 1 || 4 < mode)));
}

/**
 * Распределяющая функция, вызывает функции класса Graph, для выполнения соответствующих действий.
 * @param writeMode куда будет записываться информация: консоль/файл.
 * @param oriented ориентированность графа.
 * @param fileStream поток, в который будет писаться информация.
 */
void Action(int& writeMode, bool& oriented, ostream& fileStream)  {
    string loop;
    int action, mode = 0;
    do  {
        GetAction(action, mode);
        switch (action) {
            case 1:
                if (writeMode == 1)  {
                    Graph::VerticesDegree(oriented, std::cout);
                }  else  {
                    Graph::VerticesDegree(oriented, fileStream);
                }
                break;
            case 2:
                if (writeMode == 1)  {
                    Graph::CountArcEdges(oriented, std::cout);
                }  else  {
                    Graph::CountArcEdges(oriented, fileStream);
                }
                break;
            case 3:
                if (writeMode == 1)  {
                    Graph::Print(mode, std::cout);
                }  else  {
                    Graph::Print(mode, fileStream);
                }
                break;
            case 4: case 5: case 6:
                if (writeMode == 1)  {
                    Graph::GraphSearch(mode, action, std::cout);
                }  else  {
                    Graph::GraphSearch(mode, action, fileStream);
                }
                break;
            default:
                break;
        }
        Loop(loop);
    }  while (loop != "n");
}

/**
 * Главная функция программы, входная точка в меню.
 */
void Menu()  {
    int readWriteMode, graphMode;
    bool oriented;
    std::ofstream fileStream("output.txt");
    string loop;
    do  {
        OrientedMode(oriented);
        ReadWriteMode(readWriteMode);
        GraphMode(graphMode);
        ReadGraph(readWriteMode, graphMode, oriented);
        if (Graph::IsEmpty())  {
            continue;
        }
        ReadWriteMode(readWriteMode);
        Action(readWriteMode, oriented, fileStream);
        Loop(loop);
    }  while (loop != "n");
}