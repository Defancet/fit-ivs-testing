//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Maksim Kalutski <xkalut00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph() {}

Graph::~Graph() {
    clear();
}

std::vector<Node *> Graph::nodes() {
    std::vector<Node*> nodes;
    nodes = nodes_;
    return nodes;
}

std::vector <Edge> Graph::edges() const {
    std::vector<Edge> edges;
    edges = edges_;
    return edges;
}

Node *Graph::addNode(size_t nodeId) {
    if (getNode(nodeId) != nullptr) {
        return nullptr;
    }

    Node *newNode = new Node{nodeId, 0};
    nodes_.push_back(newNode);
    return newNode;
}

bool Graph::addEdge(const Edge &edge) {
    if (edge.a == edge.b || containsEdge(edge)) {
        return false;
    }

    if (getNode(edge.a) == nullptr) {
        addNode(edge.a);
    }
    if (getNode(edge.b) == nullptr) {
        addNode(edge.b);
    }

    edges_.push_back(edge);
    return true;
}

void Graph::addMultipleEdges(const std::vector <Edge> &edges) {
    for (const auto &edge: edges) {
        addEdge(edge);
    }
}

Node *Graph::getNode(size_t nodeId) {
    for (auto node: nodes_) {
        if (node->id == nodeId) {
            return node;
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge &edge) const {
    for (const auto &e: edges_) {
        if (e == edge) {
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId) {
    Node *node = getNode(nodeId);
    if (node == nullptr) {
        throw std::out_of_range("Node not found");
    }

    for (int i = 0; i < nodes_.size(); i++) {
        if (nodes_[i]->id == nodeId) {
            delete nodes_[i];
            nodes_.erase(nodes_.begin() + i);
            for (int j = 0; j < edges_.size(); j++) {
                if (edges_[j].a == nodeId || edges_[j].b == nodeId) {
                    edges_.erase(edges_.begin() + j);
                    j--;
                }
            }
            return;
        }
    }
}

void Graph::removeEdge(const Edge &edge) {
    if (!containsEdge(edge)) {
        throw std::out_of_range("Index out of range");
    }

    for (int i = 0; i < edges_.size(); i++) {
        if (edges_[i] == edge) {
            edges_.erase(edges_.begin() + i);
            return;
        }
    }
}

size_t Graph::nodeCount() const {
    return nodes_.size();
}

size_t Graph::edgeCount() const {
    return edges_.size();
}

size_t Graph::nodeDegree(size_t nodeId) const {
    size_t degree = 0;
    for (const auto &edge: edges_) {
        if (edge.a == nodeId || edge.b == nodeId) {
            degree++;
        }
    }
    if (degree == 0) {
        throw std::out_of_range("Index out of range");
    }
    return degree;
}

size_t Graph::graphDegree() const {
    size_t maxDegree = 0;
    for (const auto &node: nodes_) {
        size_t degree = nodeDegree(node->id);
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}

void Graph::coloring() {
    for (auto &node: nodes_) {
        node->color = 0;
    }

    std::vector<bool> availableColors(nodes_.size(), false);

    for (auto &node: nodes_) {
        std::fill(availableColors.begin(), availableColors.end(), false);

        for (const auto &edge: edges_) {
            if (edge.a == node->id) {
                Node *adjacent = getNode(edge.b);
                if (adjacent->color != 0) {
                    availableColors[adjacent->color - 1] = true;
                }
            } else if (edge.b == node->id) {
                Node *adjacent = getNode(edge.a);
                if (adjacent->color != 0) {
                    availableColors[adjacent->color - 1] = true;
                }
            }
        }

        for (int colorIdx = 0; colorIdx < availableColors.size(); colorIdx++) {
            if (!availableColors[colorIdx]) {
                node->color = colorIdx + 1;
                break;
            }
        }
    }
}

void Graph::clear() {
    for (auto& node: nodes_) {
        delete node;
    }
    nodes_.clear();
    edges_.clear();
}

/*** Konec souboru tdd_code.cpp ***/
