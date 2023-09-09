#pragma once

auto TEXTUREMANAGER_H_TEMPLATE { R"(#pragma once

#include <unordered_map>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

namespace be {

class TextureManager {
public:
	static TextureManager &getInstance();
	
	static SDL_Texture *loadOrGet(std::string path);
private:
	template<typename T>
	friend class Game;
	
	TextureManager() = default;
	~TextureManager() = default;
	
	void init(SDL_Renderer *renderer);
	void clear();
	
	SDL_Texture *loadOrGetTexture(std::string path);
	
	std::unordered_map<std::string, SDL_Texture*> m_textures { };
	SDL_Renderer *m_renderer { nullptr };
};

} // namespace be
)" };

auto TEXTUREMANAGER_CPP_TEMPLATE { R"(#include "be/TextureManager.h"

#include <SDL.h>
#include <SDL_image.h>

namespace be {

TextureManager &TextureManager::getInstance() {
	static TextureManager instance;
	return instance;
}

SDL_Texture *TextureManager::loadOrGet(std::string path) {
	return getInstance().loadOrGetTexture(std::move(path));
}

SDL_Texture *TextureManager::loadOrGetTexture(std::string path) {
	auto ptr = m_textures.find(path);
	if(ptr == m_textures.end()) {
		SDL_Surface *surface = IMG_Load(path.c_str());
		if(!surface) {
			return nullptr;
		}
		
		SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		
		m_textures[path] = texture;
		
		return texture;
	}
	
	return ptr->second;
}

void TextureManager::init(SDL_Renderer *renderer) {
	m_renderer = renderer;
}

void TextureManager::clear() {
	for(auto &pair : m_textures) {
		SDL_DestroyTexture(pair.second); 
	}
	
	m_textures.clear();
}

} // namespace be
)" };