#include "keymanager.h"

#include <fstream>

void generateHeader()
{
	std::ofstream header("include/KeyManager.h");

	header << "#pragma once\n\n";
	header << "using Key = unsigned int;\n\n";
	header << "class KeyManager\n{\n";
	header << "public:\n";
	header << "\tstatic KeyManager &getInstance();\n\n";
	header << "\tbool isKeyPressed(Key key) const;\n";
	header << "\tbool isKeyDown(Key key) const;\n";
	header << "\tbool isKeyReleased(Key key) const;\n";
	header << "private:\n";
	header << "\tfriend class Game;\n\n";
	header << "\tclass KeyMap\n\t{\n";
	header << "\tpublic:\n";
	header << "\t\tstatic constexpr int CacheLineSize { 64 };\n";
	header << "\t\tstatic constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };\n\n";
	header << "\t\tvoid operator=(const KeyMap &other);\n\n";
	header << "\t\tvoid insert(Key key);\n";
	header << "\t\tbool contains(Key key) const;\n";
	header << "\t\tvoid remove(Key key);\n\n";
	header << "\tprivate:\n";
	header << "\t\tKey m_keys[ArraySize];\n";
	header << "\t\tunsigned char m_size { 0 };\n";
	header << "\t};\n\n";
	header << "\tKeyManager() = default;\n";
	header << "\t~KeyManager() = default;\n\n";
	header << "\tvoid update();\n\n";
	header << "\tvoid keyPressed(Key key);\n";
	header << "\tvoid keyReleased(Key key);\n\n";
	header << "\tstatic KeyManager m_instance;\n\n";
	header << "\tKeyMap m_currFrameKeys;\n";
	header << "\tKeyMap m_oldFrameKeys;\n";
	header << "};\n";

	header.close();
}

void generateSource()
{
	std::ofstream src("src/KeyManager.cpp");

	src << "#include \"KeyManager.h\"\n\n";
	src << "KeyManager KeyManager::m_instance;\n\n";
	src << "KeyManager &KeyManager::getInstance() { return m_instance; }\n\n";
	src << "bool KeyManager::isKeyPressed(Key key) const { return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key); }\n";
	src << "bool KeyManager::isKeyDown(Key key) const { return m_currFrameKeys.contains(key); }\n";
	src << "bool KeyManager::isKeyReleased(Key key) const { return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key); }\n\n";
	src << "void KeyManager::update() { m_oldFrameKeys = m_currFrameKeys; }\n\n";
	src << "void KeyManager::keyPressed(Key key) { m_currFrameKeys.insert(key); }\n";
	src << "void KeyManager::keyReleased(Key key) { m_currFrameKeys.remove(key); }\n\n";
	src << "void KeyManager::KeyMap::operator=(const KeyManager::KeyMap &other) \n{\n\tm_size = other.m_size;\n\tfor(unsigned char i = 0; i < m_size; ++i) m_keys[i] = other.m_keys[i];\n}\n\n";
	src << "void KeyManager::KeyMap::insert(Key key)\n{\n\tif(!contains(key) && m_size < KeyManager::KeyMap::ArraySize)\n\t\tm_keys[m_size++] = key;\n}\n\n";
	src << "void KeyManager::KeyMap::remove(Key key)\n{\n\tfor(unsigned char i = 0; i < m_size; ++i)\n\t\tif(m_keys[i] == key)\n\t\t{\n\t\t\tm_keys[i] = m_keys[--m_size];\n\t\t\treturn;\n\t\t}\n}\n\n";
	src << "bool KeyManager::KeyMap::contains(Key key) const\n{\n\tfor(unsigned char i = 0; i < m_size; ++i)\n\t\tif(m_keys[i] == key) return true;\n\treturn false;\n}\n\n";

	src.close();
}

void generateKeyManager()
{
	generateHeader();
	generateSource();
}
