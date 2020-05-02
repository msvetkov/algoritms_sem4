#include "pch.h"
#include "../algoritms_sem4_lab1/TreeMap.h"
#include "../algoritms_sem4_lab1/LinkedList.h"

TreeMap<std::string, int>* getTestingMap() {
	auto* map = new TreeMap<std::string, int>();
	map->insert("width", 10);
	map->insert("height", 25);
	map->insert("border", 80);
	map->insert("padding", 8);
	map->insert("margin", 4);
	return map;
}

TEST(tree_map, insert) {
	TreeMap<std::string, int>* map = getTestingMap();
	ASSERT_ANY_THROW(map->find("z-index"));
	map->insert("z-index", 10);
	ASSERT_EQ(map->find("z-index"), 10);
}

TEST(map, remove) {
	TreeMap<std::string, int>* map = getTestingMap();
	ASSERT_EQ(map->find("margin"), 4);
	map->remove("margin");
	ASSERT_ANY_THROW(map->find("margin"));
	ASSERT_ANY_THROW(map->remove("margin"));
}

TEST(map, find) {
	TreeMap<std::string, int>* map = getTestingMap();
	ASSERT_EQ(map->find("margin"), 4);
	ASSERT_ANY_THROW(map->find("margin-left"));
}

TEST(map, clear) {
	TreeMap<std::string, int>* map = getTestingMap();
	auto* list = new LinkedList<std::string>();
	ASSERT_FALSE(map->getKeys()->equals(list));
	map->clear();
	ASSERT_TRUE(map->getKeys()->equals(list));
}

TEST(map, getKeys) {
	TreeMap<std::string, int>* map = getTestingMap();
	auto* list = new LinkedList<std::string>();
	ASSERT_FALSE(map->getKeys()->equals(list));
	list->insert("width");
	list->insert("height");
	list->insert("border");
	list->insert("padding");
	list->insert("margin");
	ASSERT_TRUE(map->getKeys()->equals(list));
}

TEST(map, getValues) {
	TreeMap<std::string, int>* map = getTestingMap();
	auto* list = new LinkedList<int>();
	ASSERT_FALSE(map->getValues()->equals(list));
	list->insert(10);
	list->insert(25);
	list->insert(80);
	list->insert(8);
	list->insert(4);
	ASSERT_TRUE(map->getValues()->equals(list));
}