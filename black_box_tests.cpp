//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Maksim Kalutski <xkalut00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Maksim Kalutski
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

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode) {
    auto result = tree.InsertNode(1);
    EXPECT_TRUE(result.first);
    EXPECT_NE(nullptr, tree.FindNode(1));
    EXPECT_EQ(1, result.second->key);
}

TEST_F(EmptyTree, DeleteNode) {
    EXPECT_FALSE(tree.DeleteNode(1));
}

TEST_F(EmptyTree, FindNode) {
    EXPECT_EQ(nullptr, tree.FindNode(1));
    tree.InsertNode(1);
    EXPECT_NE(nullptr, tree.FindNode(1));
}

class NonEmptyTree : public ::testing::Test {
protected:
    BinaryTree tree;

    void SetUp() override {
        for (int value: {1, 2, 3, 4, 5, 6, 7, 8}) {
            tree.InsertNode(value);
        }
    }
};

TEST_F(NonEmptyTree, InsertNode) {
    auto existing = tree.InsertNode(2);
    EXPECT_FALSE(existing.first);
    EXPECT_EQ(tree.FindNode(2), existing.second);
    EXPECT_EQ(2, existing.second->key);

    auto newNode = tree.InsertNode(10);
    EXPECT_TRUE(newNode.first);
}

TEST_F(NonEmptyTree, DeleteNode) {
    EXPECT_TRUE(tree.DeleteNode(2));
    EXPECT_EQ(nullptr, tree.FindNode(2));
    EXPECT_FALSE(tree.DeleteNode(10));
}

TEST_F(NonEmptyTree, FindNode) {
    EXPECT_NE(nullptr, tree.FindNode(5));
    EXPECT_EQ(nullptr, tree.FindNode(10));
}

class TreeAxioms : public ::testing::Test {
protected:
    BinaryTree tree;

    void SetUp() override {
        for (int value : {1, 2, 3, 4, 5, 6, 7, 8}) {
            tree.InsertNode(value);
        }
    }
};

TEST_F(TreeAxioms, Axiom1) {
    std::vector<BinaryTree::Node_t *> allNodes;
    tree.GetLeafNodes(allNodes);
    for (auto *node : allNodes) {
        EXPECT_EQ(BLACK, node->color);
    }
}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<BinaryTree::Node_t *> nonLeafNodes;
    tree.GetNonLeafNodes(nonLeafNodes);
    for (auto *node : nonLeafNodes) {
        if (node->color == RED) {
            EXPECT_EQ(BLACK, node->pLeft->color);
            EXPECT_EQ(BLACK, node->pRight->color);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) {
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    int expectedBlackCount = -1;
    for (auto *leaf : leafNodes){
        int blackCount = 0;
        for (auto *node = leaf; node != nullptr; node = node->pParent){
            if (node->color == BLACK){
                blackCount++;
            }
        }
        if (expectedBlackCount == -1) {
            expectedBlackCount = blackCount;
        } else {
            EXPECT_EQ(expectedBlackCount, blackCount);
        }
    }
}

/*** Konec souboru black_box_tests.cpp ***/
