#include "TextureManager.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/ForStatement.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"

void TextureManager::generate() const
{
	generateHeader();
	generateSource();
}

void TextureManager::generateHeader() const
{
	File("include/BE/" + m_className + ".h", {
		"#pragma once",
		"",
		"#include <unordered_map>",
		"#include <string>"
	}, {
		"struct SDL_Texture;",
		"struct SDL_Renderer;",
		"",
		Namespace("BE", {
			Class(m_className, {
				"static TextureManager &getInstance();",
				"",
				"static SDL_Texture *loadOrGet(std::string path);"
			}, {}, {
				"template<typename T>",
				"friend class Game;",
				"",
				"TextureManager() = default;",
				"~TextureManager() = default;",
				"",
				"void init(SDL_Renderer *renderer);",
				"void clear();",
				"",
				"SDL_Texture *loadOrGetTexture(std::string path);",
				"",
				"std::unordered_map<std::string, SDL_Texture*> m_textures { };",
				"SDL_Renderer *m_renderer { nullptr };"
			})
		})
	}).write();
}

void TextureManager::generateSource() const
{
	File("src/BE/" + m_className + ".cpp", {
		"#include \"BE/" + m_className + ".h\"",
		"",
		"#include <SDL2/SDL.h>",
		"#include <SDL2/SDL_image.h>",
	}, {
		Namespace("BE", {
			Function("", "TextureManager &TextureManager::getInstance()", {
				"static TextureManager instance;",
				"return instance;"
			}),
			"",
			Function("", "SDL_Texture *TextureManager::loadOrGet(std::string path)", { "return getInstance().loadOrGetTexture(std::move(path));" }),
			"",
			Function("", "SDL_Texture *TextureManager::loadOrGetTexture(std::string path)", {
				"auto ptr = m_textures.find(path);",
				IfStatement("ptr == m_textures.end()", {
					"SDL_Surface *surface = IMG_Load(path.c_str());",
					IfStatement("!surface", { "return nullptr;" }),
					"",
					"SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);",
					"",
					"m_textures[path] = texture;",
					"",
					"return texture;"
				}),
				"",
				"return ptr->second;"
			}),
			"",
			Function("", "void TextureManager::init(SDL_Renderer *renderer)", { "m_renderer = renderer;" }),
			"",
			Function("", "void TextureManager::clear()", {
				ForStatement("auto &pair : m_textures", {
					"SDL_DestroyTexture(pair.second); "
				}),
				"",
				"m_textures.clear();"
			})
		})
	}).write();
}

