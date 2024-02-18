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

TEST(EmptyTree, InsertNode)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    BinaryTree::Node_t *node = tree.FindNode(1); // Finds node with key 1
    ASSERT_NE(node, nullptr); // Checks if node with key 1 exists
    EXPECT_EQ(node->key, 1); // Checks if key of the node is 1
    EXPECT_EQ(node->color, 1); // Checks if the color of the node is black
}
TEST(EmptyTree, DeleteNode)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.DeleteNode(1); // Deletes node with key 1
    BinaryTree::Node_t *node = tree.FindNode(1); // Finds node with key 1
    EXPECT_EQ(node, nullptr); // Checks if node with key 1 exists
}
TEST(EmptyTree, FindNode)
{
    BinaryTree tree;
    BinaryTree::Node_t *node = tree.FindNode(1); // Finds node with key 1
    EXPECT_EQ(node, nullptr); // Checks if node with key 1 exists
}
TEST(NonEmptyTree, InsertNode_DifferentKeys)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.InsertNode(2); // Inserts node with key 2
    BinaryTree::Node_t *node = tree.FindNode(2); // Finds node with key 2
    ASSERT_NE(node, nullptr); // Checks if node with key 2 exists
    EXPECT_EQ(node->key, 2); // Checks if key of the node is 2
    EXPECT_EQ(node->color, 0); // Checks if the color of the node is red
}
TEST(NonEmptyTree, InsertNode_SameKeys)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.InsertNode(1); // Inserts node with key 1
    BinaryTree::Node_t *node = tree.FindNode(1); // Finds node with key 1
    ASSERT_NE(node, nullptr); // Checks if node with key 1 exists
    EXPECT_EQ(node->key, 1); // Checks if key of the node is 1
    EXPECT_EQ(node->color, 1); // Checks if the color of the node is black
}
TEST(NonEmptyTree, DeleteNode)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.InsertNode(2); // Inserts node with key 2
    tree.DeleteNode(2); // Deletes node with key 2
    BinaryTree::Node_t *node = tree.FindNode(2); // Finds node with key 2
    EXPECT_EQ(node, nullptr); // Checks if node with key 2 exists
}
TEST(NonEmptyTree, DeleteNodesWithSameKeys)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.InsertNode(1); // Inserts node with key 1
    tree.DeleteNode(1); // Deletes node with key 1
    BinaryTree::Node_t *node = tree.FindNode(1); // Finds node with key 1
    EXPECT_EQ(node, nullptr); // Checks if node with key 1 exists
}
TEST(NonEmptyTree, DeleteNodeThatDoesntExist)
{
    BinaryTree tree;
    tree.InsertNode(1); // Inserts node with key 1
    tree.DeleteNode(2); // Deletes node with key 2
    BinaryTree::Node_t *node = tree.FindNode(2); // Finds node with key 2
    EXPECT_EQ(node, nullptr); // Checks if node with key 2 exists
}