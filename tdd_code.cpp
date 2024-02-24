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
    maxNode = 0;
    maxEdge = 0;
}

Graph::~Graph(){
    for (size_t i = 0; i < graph_nodes.size(); i++)
    {
        free(graph_nodes[i]);
    }
    for(size_t i = 0; i < graph_edges.size(); i++)
    {
        free(graph_edges[i]);
    }
    
}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes = graph_nodes;
    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;
    for (size_t i = 0; i < graph_edges.size(); i++)
    {
        edges.push_back(*graph_edges[i]);
    }
    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        if(graph_nodes[i]->id == nodeId)
        {
            return nullptr;
        }
    }
    Node* node = new Node();
    node->id = nodeId;
    node->color = 0;
    node->edges = std::vector<Edge*>();
    graph_nodes.push_back(node);
    maxNode++;
    return node;
    
}

bool Graph::addEdge(const Edge& edge){
    if(edge.a == edge.b) //  Ignoring self loops
    {
        return false;
    }
    if (this->containsEdge(edge)) { // Checks if the edge already exists
		return false;
	}
	if (!this->getNode(edge.a)) {
		return false;
	}
	if (!this->getNode(edge.b)) {
		return false;
	}
    Node* first_node = this->getNode(edge.a);
    Node* second_node = this->getNode(edge.b);
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    if(new_edge == nullptr)
    {
        return false;
    }
    new_edge->a = first_node->id;
    new_edge->b = second_node->id;
    first_node->edges.push_back(new_edge);
    second_node->edges.push_back(new_edge);
    graph_edges.push_back(new_edge);
    maxEdge++;
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

    return false;
}

void Graph::removeNode(size_t nodeId){
}

void Graph::removeEdge(const Edge& edge){
}

size_t Graph::nodeCount() const{
    return 42;
}

size_t Graph::edgeCount() const{
    return 42;
}

size_t Graph::nodeDegree(size_t nodeId) const{
    return 42;
}

size_t Graph::graphDegree() const{
    return 42;
}

void Graph::coloring(){
}

void Graph::clear() {
}

/*** Konec souboru tdd_code.cpp ***/
