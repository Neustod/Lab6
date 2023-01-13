#pragma once
#include <iostream>
#include <vector>
#include <time.h>

class Graph
{
public:
    Graph() {}

    Graph(int EdgesAmount) {
        Edges.assign(EdgesAmount, std::vector<int>(EdgesAmount, 0));

        for (int i = 0; i < EdgesAmount; i++) {
            for (int j = i + 1; j < EdgesAmount; j++) {
                Edges[i][j] = rand() % 2;
                Edges[j][i] = Edges[i][j];
            }
        }
    }

    std::vector<std::vector<int>> Edges;

    void Merge(int v, int u) {
        if (!(v >= 0 && v < Edges.size()) || !(u >= 0 && u < Edges.size()) || u == v) return;

        std::vector<int> q1;
        q1 = Edges[v];

        for (int i = 0; i < q1.size(); i++) q1[i] = q1[i] or Edges[u][i];

        if (v < u) {
            v = v xor u;
            u = v xor u;
            v = v xor u;
        }

        q1.erase(q1.begin() + v);
        q1.erase(q1.begin() + u);

        Edges.erase(Edges.begin() + v);
        Edges.erase(Edges.begin() + u);


        for (int i = 0; i < Edges.size(); i++) {
            Edges[i].erase(Edges[i].begin() + v);
            Edges[i].erase(Edges[i].begin() + u);

            Edges[i].push_back(q1[i]);
        }

        q1.push_back(0);
        Edges.push_back(q1);
    }

    void Break(int v) {
        int i = 0;
        Edges.push_back(Edges[v]);

        for (i; i < Edges.size() - 1; i++) {
            Edges[i].push_back(Edges[v][i]);
        }

        Edges[i].push_back(0);
    }

    void DeleteEdge(int n) {
        if (!(n >= 0 && n < Edges.size())) return;

        Edges.erase(Edges.begin() + n);
        for (int i = 0; i < Edges.size(); i++) Edges[i].erase(Edges[i].begin() + n);
    }

    Graph Union(Graph b) {
        Graph a = *this;

        if (a.Edges.size() < b.Edges.size()) {
            for (int i = 0; i < a.Edges.size(); i++) a.Edges[i].resize(b.Edges.size(), 0);
            a.Edges.resize(b.Edges.size(), std::vector<int>(b.Edges.size(), 0));
        }
        else if (a.Edges.size() > b.Edges.size()) {
            for (int i = 0; i < b.Edges.size(); i++) b.Edges[i].resize(a.Edges.size(), 0);
            b.Edges.resize(a.Edges.size(), std::vector<int>(a.Edges.size(), 0));
        }

        for (int i = 0; i < a.Edges.size(); i++) {
            for (int j = 0; j < a.Edges.size(); j++) {
                a.Edges[i][j] = a.Edges[i][j] or b.Edges[i][j];
            }
        }

        return a;
    }

    Graph Intersection(Graph b) {
        Graph a = *this;

        if (a.Edges.size() < b.Edges.size()) {
            b.Edges.resize(a.Edges.size());
            for (auto item : b.Edges) item.resize(a.Edges.size());
        }
        else if (a.Edges.size() > b.Edges.size()) {
            a.Edges.resize(b.Edges.size());
            for (auto item : a.Edges) item.resize(b.Edges.size());
        }

        for (int i = 0; i < a.Edges.size(); i++) {
            for (int j = 0; j < a.Edges.size(); j++) {
                a.Edges[i][j] = a.Edges[i][j] * b.Edges[i][j];
            }
        }

        return a;
    }

    Graph DecartMul(Graph b) {
        Graph c;
        c.Edges.assign(Edges.size() * b.Edges.size(), std::vector<int>(Edges.size() * b.Edges.size(), 0));

        for (int x1 = 0; x1 < Edges.size(); x1++) {
            for (int y1 = 0; y1 < b.Edges.size(); y1++) {
                for (int x2 = 0; x2 < Edges.size(); x2++) {
                    for (int y2 = 0; y2 < b.Edges.size(); y2++) {
                        if (x1 == x2)
                            c.Edges[x1 * b.Edges.size() + y1][x2 * b.Edges.size() + y2] = b.Edges[y1][y2];
                        else if (y1 == y2)
                            c.Edges[x1 * b.Edges.size() + y1][x2 * b.Edges.size() + y2] = Edges[x1][x2];
                        else
                            c.Edges[x1 * b.Edges.size() + y1][x2 * b.Edges.size() + y2] = 0;
                    }
                }
            }
        }

        return c;
    }

    Graph RingAdd(Graph b) {
        Graph a = *this;

        if (a.Edges.size() < b.Edges.size()) {
            for (int i = 0; i < a.Edges.size(); i++) a.Edges[i].resize(b.Edges.size(), 0);
            a.Edges.resize(b.Edges.size(), std::vector<int>(b.Edges.size(), 0));
        }
        else if (a.Edges.size() > b.Edges.size()) {
            for (int i = 0; i < b.Edges.size(); i++) b.Edges[i].resize(a.Edges.size(), 0);
            b.Edges.resize(a.Edges.size(), std::vector<int>(a.Edges.size(), 0));
        }

        for (int i = 0; i < a.Edges.size(); i++) {
            for (int j = 0; j < a.Edges.size(); j++) {
                a.Edges[i][j] = a.Edges[i][j] xor b.Edges[i][j];
            }
        }

        return a;
    }

    void Print() {
        for (int i = 0; i < Edges.size(); i++) {
            for (int j = 0; j < Edges.size(); j++) {
                std::cout << Edges[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    ~Graph() {
        Edges.clear();
    }
};