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

#include "Entity.h"

#include "../world/World.h"

using namespace std;

pthread_mutex_t Entity::staticmutex;

map<int, Entity*> Entity::entities;

Entity::Entity(int _id) {
	this->id = _id;
}

Entity::Entity() {
}

void Entity::initialize() {
	pthread_mutex_init(&Entity::staticmutex, NULL);
}

void Entity::deinitialize() {
	pthread_mutex_destroy(&Entity::staticmutex);
}

Entity *Entity::getEntity(int _id) {
	Entity *foundEntity;
	pthread_mutex_lock(&Entity::staticmutex);
	if (Entity::entities.count(_id) == 0) {
		Entity::entities[_id] = new Entity(_id);
	}
	foundEntity = Entity::entities[_id];
	pthread_mutex_unlock(&Entity::staticmutex);

	return foundEntity;
}

void Entity::setEntity(Entity *entity) {
	pthread_mutex_lock(&Entity::staticmutex);
	Entity::entities[entity->getId()] = entity;
	pthread_mutex_unlock(&Entity::staticmutex);
}

void Entity::deleteEntity(int _id) {
	pthread_mutex_lock(&Entity::staticmutex);
	Entity::entities.erase(_id);
	pthread_mutex_unlock(&Entity::staticmutex);
}

void Entity::setId(int _id) {
	pthread_mutex_lock(&this->mutex);
	this->id = _id;
	pthread_mutex_unlock(&this->mutex);
}

int Entity::getId() {
	int _id;
	pthread_mutex_lock(&this->mutex);
	_id = this->id;
	pthread_mutex_unlock(&this->mutex);

	return _id;
}

void Entity::setCoordinates(double _x, double _y, double _z) {
	pthread_mutex_lock(&this->mutex);
	this->x = _x;
	this->y = _y;
	this->z = _z;

	World::calculateChunkPosition((int)this->x, (int)this->z, this->chunkX, this->chunkZ);

	pthread_mutex_unlock(&this->mutex);
}

double Entity::getX() {
	pthread_mutex_lock(&this->mutex);
	double _x = this->x;
	pthread_mutex_unlock(&this->mutex);

	return _x;

}

double Entity::getY() {
	pthread_mutex_lock(&this->mutex);
	double _y = this->y;
	pthread_mutex_unlock(&this->mutex);

	return _y;
}

double Entity::getZ() {
	pthread_mutex_lock(&this->mutex);
	double _z = this->z;
	pthread_mutex_unlock(&this->mutex);

	return _z;
}

int Entity::getChunkX() {
	pthread_mutex_lock(&this->mutex);
	int _x = this->chunkX;
	pthread_mutex_unlock(&this->mutex);

	return _x;

}

int Entity::getChunkZ() {
	pthread_mutex_lock(&this->mutex);
	int _z = this->chunkZ;
	pthread_mutex_unlock(&this->mutex);

	return _z;
}
