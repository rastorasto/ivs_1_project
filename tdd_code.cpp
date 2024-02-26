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
    //std::vector<Node*> nodes = graph_nodes;
    return graph_nodes;
}

std::vector<Edge> Graph::edges() const{
    /*std::vector<Edge> edges;
    for (size_t i = 0; i < graph_edges.size(); i++)
    {
        edges.push_back(graph_edges[i]);
    }*/
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
    if(edge.a == edge.b) //  Ignoring self loops
    {
        return false;
    }
    if (containsEdge(edge)) { // Checks if the edge already exists
		return false;
	}
    /*
	if (getNode(edge.a)) {
		return false;
	}
	if (!getNode(edge.b)) {
		return false;
	}*/
    //Node* first_node = getNode(edge.a);
    //Node* second_node = getNode(edge.b);
    addNode(edge.a);
    addNode(edge.b);
    /*Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    if(new_edge == nullptr)
    {
        return false;
    }
    new_edge->a = first_node->id;
    new_edge->b = second_node->id;
    first_node->edges.push_back(new_edge);
    second_node->edges.push_back(new_edge);
    graph_edges.push_back(new_edge);
    return true;
    */
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
       // if(graph_edges[i].a == edge.a && graph_edges[i].b == edge.b || graph_edges[i].b == edge.a && graph_edges[i].a == edge.b)
        if(graph_edges[i] == edge)
        {
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId){
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        if(graph_nodes[i]->id == nodeId)
        {
            delete graph_nodes[i];
            graph_nodes.erase(graph_nodes.begin() + i);
        }
    }
    throw std::out_of_range("Node with id " + std::to_string(nodeId) + " does not exist.");
}

void Graph::removeEdge(const Edge& edge){
    for(size_t i = 0; i < graph_edges.size(); i++)
    {
        if(graph_edges[i] == edge)
        {
            graph_edges.erase(graph_edges.begin() + i);
        }
    }
    throw std::out_of_range("Edge {" + std::to_string(edge.a) + "," + std::to_string(edge.b) +"} does not exist.");
}

size_t Graph::nodeCount() const{
    return graph_nodes.size();
}

size_t Graph::edgeCount() const{
    return graph_edges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        if(graph_nodes[i]->id == nodeId)
        {
            return graph_nodes[i]->edges.size();
        }
    }
    throw std::out_of_range("Node with id " + std::to_string(nodeId) + " does not exist.");
}

size_t Graph::graphDegree() const{
    size_t max = 0;
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        if(graph_nodes[i]->edges.size() > max)
        {
            max = graph_nodes[i]->edges.size();
        }
    }
    return max;
}

void Graph::coloring(){
    for(size_t i = 0; i < graph_nodes.size(); i++)
    {
        //todo
        if(i>graphDegree()+1){
            break;
        }
        graph_nodes[i]->color = i;
    }

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
