//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Maksim Kalutski <xkalut00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Maksim Kalutski
 *
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v
//       indexu
//============================================================================//

class HashMapTest : public ::testing::Test {
protected:
    hash_map_t *map = nullptr;

    void SetUp() override {
        map = hash_map_ctor();
    }

    void TearDown() override {
        hash_map_dtor(map);
    }

    void putAndGetTest(const std::string& key, int value) {
        hash_map_put(map, key.c_str(), value);
        int retrievedValue = 0;
        EXPECT_EQ(hash_map_get(map, key.c_str(), &retrievedValue), OK);
        EXPECT_EQ(retrievedValue, value);
    }
};

TEST_F(HashMapTest, ConstructorDestructorValidity) {
    ASSERT_NE(map, nullptr);
}

TEST_F(HashMapTest, InitialEmptyCheck) {
    EXPECT_EQ(hash_map_size(map), 0);
}

TEST_F(HashMapTest, InsertAndRetrieveSingleValue) {
    putAndGetTest("key1", 10);
}

TEST_F(HashMapTest, UpdateValueForKey) {
    hash_map_put(map, "key1", 10);
    putAndGetTest("key1", 20);
}

TEST_F(HashMapTest, RemoveKeyAndCheckAbsence) {
    hash_map_put(map, "key1", 10);
    EXPECT_EQ(hash_map_remove(map, "key1"), OK);
    EXPECT_FALSE(hash_map_contains(map, "key1"));
}

TEST_F(HashMapTest, PopValueForKey) {
    hash_map_put(map, "key1", 10);
    int value = 0;
    EXPECT_EQ(hash_map_pop(map, "key1", &value), OK);
    EXPECT_EQ(value, 10);
    EXPECT_FALSE(hash_map_contains(map, "key1"));
}

TEST_F(HashMapTest, KeyNotPresent) {
    int value = 0;
    EXPECT_EQ(hash_map_get(map, "missingKey", &value), KEY_ERROR);
}

TEST_F(HashMapTest, HandleCollisions) {
    hash_map_put(map, "key1", 10);
    hash_map_put(map, "key2", 20);
    EXPECT_EQ(hash_map_size(map), 2);
}

TEST_F(HashMapTest, MapResizeOnMultipleInsertions) {
    for (int i = 0; i < 10; ++i) {
        hash_map_put(map, ("key" + std::to_string(i)).c_str(), i);
    }
    EXPECT_GT(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
    EXPECT_EQ(hash_map_size(map), 10);
}

TEST_F(HashMapTest, RemoveNonexistentKey) {
    EXPECT_EQ(hash_map_remove(map, "nonexistent"), KEY_ERROR);
}

TEST_F(HashMapTest, PopNonexistentKey) {
    int value = 0;
    EXPECT_EQ(hash_map_pop(map, "nonexistent", &value), KEY_ERROR);
}

TEST_F(HashMapTest, VerifyRemovalEffectOnContains) {
    hash_map_put(map, "key1", 10);
    hash_map_remove(map, "key1");
    EXPECT_FALSE(hash_map_contains(map, "key1"));
}

TEST_F(HashMapTest, HandleEmptyKey) {
    putAndGetTest("", 1);
}

TEST_F(HashMapTest, SequenceOfRemoveAndAdd) {
    hash_map_put(map, "key1", 10);
    hash_map_remove(map, "key1");
    putAndGetTest("key2", 20);
}

/*** Konec souboru white_box_tests.cpp ***/
