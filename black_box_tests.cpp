//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Rastislav Uhliar <xuhliar00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Rastislav Uhliar
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"


//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
using namespace::testing;

class EmptyTree : public Test{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public Test{
    void SetUp(){
        for(int i = 0; i<50; i++){
            tree.InsertNode(i);
        }
    }
protected:
    BinaryTree tree;
};

class TreeAxioms : public Test{
    void SetUp(){
        for(int i = 0; i<50; i++){
            tree.InsertNode(i);
        }
    }
protected:
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode_62)
{
    tree.InsertNode(62); // Inserts node with key 62
    Node_t *node = tree.FindNode(62); // Finds node with key 62
    ASSERT_NE(node, nullptr); // Checks if node with key 62 exists
    EXPECT_EQ(node->key, 62); // Checks if key of the node is 62
    EXPECT_EQ(node->color, BLACK); // Checks if the color of the node is black
}
TEST_F(EmptyTree, DeleteNode_62)
{
    tree.DeleteNode(62); // Deletes node with key 62
    Node_t *node = tree.FindNode(62); // Finds node with key 62
    EXPECT_EQ(node, nullptr); // Checks if node with key 62 does not exist
}
TEST_F(EmptyTree, DeleteNode_15_Doesnt_Exist)
{
    auto result = tree.DeleteNode(15); // Tries to delete node with key 15
    EXPECT_EQ(result, false); // Checks if node was deleted
}
TEST_F(EmptyTree, FindNode_42)
{
    auto result = tree.FindNode(42); // Finds node with key 42
    EXPECT_EQ(result, nullptr); // Checks if node with key 42 does not exist
}
TEST_F(NonEmptyTree, DeleteNode_12)
{
    tree.DeleteNode(12); // Deletes node with key 12
    Node_t *node = tree.FindNode(12); // Finds node with key 12
    EXPECT_EQ(node, nullptr); // Checks if node with key 12 exists
}
TEST_F(NonEmptyTree, DeleteNodes_60_Doesnt_Exist)
{
    Node_t *node = tree.FindNode(60); // Finds node with key 60
    EXPECT_EQ(node, nullptr); // Checks if node with key 60 exists
}
TEST_F(NonEmptyTree, FindNode_7)
{
    Node_t *node = tree.FindNode(7); // Finds node with key 7
    ASSERT_NE(node, nullptr); // Checks if node with key 7 exists
    EXPECT_EQ(node->key, 7); // Checks if key of the node is 7
    EXPECT_EQ(node->color, BLACK); // Checks if the color of the node is black
}
TEST_F(NonEmptyTree, FindNode_120_Doesnt_Exist)
{
    Node_t *node = tree.FindNode(120); // Tries to find node with key 120
    EXPECT_EQ(node, nullptr); // Checks if node with key 120 does not exist
}
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes); // Gets all leaf nodes
    for (auto leaf : leafNodes) {
        EXPECT_EQ(leaf->color, BLACK); // Checks if all leaf nodes are black
    }
}
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<Node_t *> redNodes;
    tree.GetAllNodes(redNodes); // Gets all leaf nodes
    for (auto parentNode : redNodes) {
        if(parentNode->color == RED) {
            EXPECT_EQ(parentNode->pLeft->color, BLACK); // Checks if parentNode has black left child
            EXPECT_EQ(parentNode->pRight->color, BLACK); // Checks if parentNode has black right child
        }
    }   
}
TEST_F(TreeAxioms, Axiom3)
{
    std::vector<Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes); // Gets all leaf nodes
    std::vector<int> blackNodesCount; // Array to store numbers of black nodes
    for (auto leaf : leafNodes) {
        int blackNodes = 0; // Sets the number of black nodes to 0
        while(leaf != nullptr) { // Goes from leaf higher if the node has parent
            if(leaf->color == BLACK) {
                blackNodes++;
            }
            leaf = leaf->pParent; // Moves to node higher up
        }
        blackNodesCount.push_back(blackNodes); // Adds the number of black nodes to the array
    }
    for (int i = 0; i < blackNodesCount.size(); i++) {
        EXPECT_EQ(blackNodesCount[0], blackNodesCount[i]); // Checks if all paths from leaf nodes to root have the same number of black nodes
    }
}