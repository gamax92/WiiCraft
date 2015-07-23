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

#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <string>
#include "../util/Datentypes.h"
#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#else
#include "../util/pthread.h"
#endif

namespace std {

class Chunk;
class ChunkCacheManager;
class CompressedChunkData;
class BlockChange;

class World {
public:
	static void calculateChunkPosition(int x, int z, int &chunkX, int &chunkZ);
	static void initializeWorld(int dimension, string levelTyp,
			byte schwierigkeitsGrad, int serverModus, unsigned short worldHeight);
	static World *getWorld();

	void initializeChunk(int x, int z);
	void loescheChunk(int x, int z);
	void ergaenzeKomprimierteDaten(int chunkX, int chunkZ,
			CompressedChunkData *komprimierteDaten);
	void ergaenzeBlockChange(int chunkX, int chunkZ,
			BlockChange *blockAenderung);
	void setTime(short _uhrzeit);
	void setzeKompassPosition(int _x, int _y, int _z);
	void setzeServerModus(byte _serverModus);
	void setzeRegen(bool _regen);
	void setzeChunkGeladen(int x, int z, bool laden);
	bool istChunkGeladen(int x, int z);
	void getChunkPos(int x, int y, int z, byte &xP, byte &yP, byte &zP);
	unsigned short berechneIndex(int x, int y, int z);
	void berechnePosAusIndex(unsigned short index, int &x, int &y, int &z);
	void berechneIndex(unsigned short index, int &x, int &y, int &z);
	int getNumberLoadedChunks();
	int getNumberChunks();
	void zeichne();
	unsigned short getWorldHeight();
	short getTime();
	string getTimeString();
private:
	static World *world;

	bool regen;
	map<int, map<int, Chunk *> > geladeneChunks;
	map<int, map<int, Chunk *> > chunks;
	short time;
	int dimension;
	unsigned short worldHeight;
	string levelTyp;
	byte schwierigkeitsGrad;
	int serverModus;
	ChunkCacheManager *chunkCacheManager;
	pthread_mutex_t mutexChunks;
	pthread_mutex_t mutexLoadedChunks;
	pthread_mutex_t mutexTime;
	pthread_mutex_t mutexWorldhoehe;

	struct KompassPosition {
		int x;
		int y;
		int z;
	};
	KompassPosition kompassPosition;

	World(int _dimension, string _levelTyp, byte _schwierigkeitsGrad,
			int _serverModus, unsigned short _worldHeight);
	~World();
};

}
#endif /* WORLD_H_ */
