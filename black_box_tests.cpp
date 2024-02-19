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

TEST(EmptyTree, InsertNode_42)
{
    BinaryTree tree;
    tree.InsertNode(42); // Inserts node with key 42
    Node_t *node = tree.FindNode(42); // Finds node with key 42
    ASSERT_NE(node, nullptr); // Checks if node with key 42 exists
    EXPECT_EQ(node->key, 42); // Checks if key of the node is 42
    EXPECT_EQ(node->color, BLACK); // Checks if the color of the node is black
}
TEST(EmptyTree, DeleteNode_42)
{
    BinaryTree tree;
    tree.DeleteNode(42); // Deletes node with key 42
    Node_t *node = tree.FindNode(42); // Finds node with key 42
    EXPECT_EQ(node, nullptr); // Checks if node with key 42 does not exist
}
TEST(EmptyTree, FindNode_42)
{
    BinaryTree tree;
    Node_t *node = tree.FindNode(42); // Finds node with key 42
    EXPECT_EQ(node, nullptr); // Checks if node with key 42 does not exist
}
TEST(NonEmptyTree, InsertNodes_30_40)
{
    BinaryTree tree;
    tree.InsertNode(30); // Inserts node with key 30 so the tree is not empty
    tree.InsertNode(40); // Inserts node with key 40
    Node_t *node = tree.FindNode(40); // Finds node with key 40
    ASSERT_NE(node, nullptr); // Checks if node with key 40 exists
    EXPECT_EQ(node->key, 40); // Checks if key of the node is 40
    EXPECT_EQ(node->color, RED); // Checks if the color of the node is red
}
TEST(NonEmptyTree, InsertNodes_15_15)
{
    BinaryTree tree;
    tree.InsertNode(15); // Inserts node with key 15 so the tree is not empty
    tree.InsertNode(15); // Inserts node with key 15
    Node_t *node = tree.FindNode(15); // Finds node with key 15
    ASSERT_NE(node, nullptr); // Checks if node with key 15 exists
    EXPECT_EQ(node->key, 15); // Checks if key of the node is 15
    EXPECT_EQ(node->color, BLACK); // Checks if the color of the node is black
}
TEST(NonEmptyTree, DeleteNode_12)
{
    BinaryTree tree;
    tree.InsertNode(10); // Inserts node with key 10 so the tree is not empty
    tree.InsertNode(12); // Inserts node with key 12
    tree.DeleteNode(12); // Deletes node with key 12
    Node_t *node = tree.FindNode(12); // Finds node with key 12
    EXPECT_EQ(node, nullptr); // Checks if node with key 12 exists
}
TEST(NonEmptyTree, DeleteNodes_22_22)
{
    BinaryTree tree;
    tree.InsertNode(22); // Inserts node with key 22
    tree.InsertNode(22); // Inserts node with key 22
    tree.DeleteNode(22); // Deletes node with key 22
    Node_t *node = tree.FindNode(22); // Finds node with key 22
    EXPECT_EQ(node, nullptr); // Checks if node with key 22 exists
}
TEST(NonEmptyTree, DeleteNode_That_Doesnt_Exist)
{
    BinaryTree tree;
    tree.InsertNode(5); // Inserts node with key 5 so the tree is not empty
    tree.DeleteNode(6); // Deletes node with key 6
    Node_t *node = tree.FindNode(2); // Tries to find node with key 2
    EXPECT_EQ(node, nullptr); // Checks if node with key 2 does not exist
}
TEST(NonEmptyTree, FindNode_7)
{
    BinaryTree tree;
    tree.InsertNode(5); // Inserts node with key 5 so the tree is not empty
    tree.InsertNode(7); // Inserts node with key 7
    Node_t *node = tree.FindNode(7); // Finds node with key 7
    ASSERT_NE(node, nullptr); // Checks if node with key 7 exists
    EXPECT_EQ(node->key, 7); // Checks if key of the node is 7
    EXPECT_EQ(node->color, RED); // Checks if the color of the node is red
}
TEST(NonEmptyTree, FindNode_That_Doesnt_Exist)
{
    BinaryTree tree;
    tree.InsertNode(5); // Inserts node with key 5 so the tree is not empty
    tree.InsertNode(7); // Inserts node with key 7
    tree.InsertNode(3); // Inserts node with key 3
    Node_t *node = tree.FindNode(6); // Tries to find node with key 6
    EXPECT_EQ(node, nullptr); // Checks if node with key 6 does not exist
}
TEST(TreeAxioms, Axiom1)
{
    BinaryTree tree;
    for (int i = 0; i < 50; i++) {
        tree.InsertNode(i); // Creates a tree with 50 nodes
    }
    std::vector<Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes); // Gets all leaf nodes
    for (auto leaf : leafNodes) {
        EXPECT_EQ(leaf->color, BLACK); // Checks if all leaf nodes are black
    }
}
TEST(TreeAxioms, Axiom2)
{
    BinaryTree tree;
    for (int i = 0; i < 50; i++) {
        tree.InsertNode(i); // Creates a tree with 50 nodes
    }
    std::vector<Node_t *> redNodes;
    tree.GetAllNodes(redNodes); // Gets all leaf nodes
    for (auto parentNode : redNodes) {
        if(parentNode->color == RED) {
            EXPECT_EQ(parentNode->pLeft->color, BLACK); // Checks if parentNode has black left child
            EXPECT_EQ(parentNode->pRight->color, BLACK); // Checks if parentNode has black right child
        }
    }   
}
TEST(TreeAxioms, Axiom3)
{
    BinaryTree tree;
    for (int i = 0; i < 50; i++) {
        tree.InsertNode(i); // Creates a tree with 50 nodes
    }
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