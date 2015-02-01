/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define MAX_DISTANCE 2

#include "ChunkLoader.h"

#include "../world/Chunk.h"

using namespace std;

ChunkLoader *ChunkLoader::chunkLoader = new ChunkLoader();

ChunkLoader::ChunkLoader() {
	pthread_mutex_init(&this->mutexChunk, NULL);
}

ChunkLoader::~ChunkLoader() {
	pthread_mutex_destroy(&this->mutexChunk);
}

void ChunkLoader::updateChunks(int x, int z) {
	pthread_mutex_lock(&this->mutexChunk);
	vector<Chunk *>::iterator it1;
	for (it1 = this->chunks.begin(); it1 < this->chunks.end(); it1++) {
		Chunk *_chunk = (*it1);

		if (x + MAX_DISTANCE >= _chunk->getX()
				&& x - MAX_DISTANCE <= _chunk->getX()
				&& z + MAX_DISTANCE >= _chunk->getZ()
				&& z - MAX_DISTANCE <= _chunk->getZ()) { // Player Chunk hat sich geaendert
			if (!_chunk->isLoaded()) { // Chunk load
				_chunk->loadChunk();
			}
		} else if (_chunk->isLoaded()) { // Chunk unload
			_chunk->saveChunk();
		}
	}
	pthread_mutex_unlock(&this->mutexChunk);
}

ChunkLoader *ChunkLoader::getChunkLoader() {
	return ChunkLoader::chunkLoader;
}

void ChunkLoader::fuegeChunkHinzu(Chunk *_chunk) {
	pthread_mutex_lock(&this->mutexChunk);
	this->chunks.push_back(_chunk);
	pthread_mutex_unlock(&this->mutexChunk);
}

void ChunkLoader::deleteChunk(Chunk *_chunk) {
	pthread_mutex_lock(&this->mutexChunk);
	vector<Chunk *>::iterator it;
	for (it = this->chunks.begin(); it < this->chunks.end(); it++) {
		Chunk *_chunkV = (*it);

		if (_chunk->getX() == _chunkV->getX()
				&& _chunk->getZ() == _chunkV->getZ()) {
			this->chunks.erase(it);
		}
	}
	pthread_mutex_unlock(&this->mutexChunk);
}

short ChunkLoader::getMaximumLoadedChunks() {
	return (MAX_DISTANCE * 4) + ((MAX_DISTANCE * MAX_DISTANCE) * 4) + 1;
}
