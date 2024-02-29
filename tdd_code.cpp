//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Rastislav Uhliar <xuhliar00@stud.fit.vutbr.cz>
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

Graph::Graph(){
}

Graph::~Graph(){
    clear();
}

std::vector<Node*> Graph::nodes() {
    return graph_nodes;
}

std::vector<Edge> Graph::edges() const{
    return graph_edges;
}

Node* Graph::addNode(size_t nodeId) {
    for(size_t i = 0; i < graph_nodes.size(); i++){
        if(graph_nodes[i]->id == nodeId){
                return nullptr;
        }
    } 
    Node *node = new Node();
    node->id = nodeId;
    graph_nodes.push_back(node);
    return node;
}

bool Graph::addEdge(const Edge& edge){
    if(edge.a == edge.b)
    {
        return false;
    }
    if (containsEdge(edge)) {
		return false;
	}
    addNode(edge.a);
    addNode(edge.b);
    graph_edges.push_back(edge);
    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(size_t i = 0; i < edges.size(); i++)
    {
        addEdge(edges[i]);
    }
}

Node* Graph::getNode(size_t nodeId){
   for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        if(graph_nodes[i]->id == nodeId)
        {
            return graph_nodes[i];
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    for(size_t i = 0; i < graph_edges.size(); i++)
    {
        if(graph_edges[i] == edge)
        {
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId){
    bool found=false;
    for(size_t i = 0; i < graph_nodes.size(); i++){
        if(graph_nodes[i]->id == nodeId){
            for(auto edge = graph_edges.begin(); edge != graph_edges.end();){
                if(edge->a == nodeId || edge->b == nodeId){
                    removeEdge(*edge);
                } else {
                    edge++;
                }
            }
            found=true;
            free(graph_nodes[i]);
            graph_nodes.erase(graph_nodes.begin() + i);
        }
    }
    if(!found){
        throw std::out_of_range("Node with id " + std::to_string(nodeId) + " does not exist.");
    }
}

void Graph::removeEdge(const Edge& edge){
    bool found=false;
    for(size_t i = 0; i < graph_edges.size(); i++)
    {
        if(graph_edges[i] == edge)
        {
            graph_edges.erase(graph_edges.begin() + i);
            found=true;
        }
    }
    if(!found){
        throw std::out_of_range("Edge {" + std::to_string(edge.a) + "," + std::to_string(edge.b) +"} does not exist.");
    }
}

size_t Graph::nodeCount() const{
    return graph_nodes.size();
}

size_t Graph::edgeCount() const{
    return graph_edges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    int counter=0;
    for(size_t i = 0; i < graph_nodes.size(); i++){
        if(graph_nodes[i]->id == nodeId){
            for(size_t j = 0; j < graph_edges.size(); j++){
                if(graph_edges[j].a == nodeId || graph_edges[j].b == nodeId){
                    counter++;
                }
            }
        }
    }
    if(counter){
        return counter;
    } else {
        throw std::out_of_range("Node with id " + std::to_string(nodeId) + " does not exist.");
    }
}

size_t Graph::graphDegree() const{
    int max = 0;
    for(size_t i = 0; i < graph_nodes.size(); i++){
        int value = nodeDegree(graph_nodes[i]->id);
        if(value > max){
            max = value;
        }
    }
    return max;
}

void Graph::coloring(){
}

void Graph::clear() {
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        delete graph_nodes[i];
    }
    graph_nodes.clear();
    graph_edges.clear();

}

/*** Konec souboru tdd_code.cpp ***/
