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

#include "PacketManager.h"

#include <stddef.h>
#include <stdlib.h>
#include "PacketServer.h"
#include "../exception/ExcPacketUnknownPacket.h"
#include "packet/Packet00KeepAlive.h"
#include "packet/Packet01LoginRequest.h"
#include "packet/Packet02Handshake.h"
#include "packet/Packet03ChatMessage.h"
#include "packet/Packet04TimeUpdate.h"
#include "packet/Packet05EntityEquipment.h"
#include "packet/Packet06SpawnPosition.h"
#include "packet/Packet08UpdateHealth.h"
#include "packet/Packet09Respawn.h"
#include "packet/Packet0DPlayerPositionLook.h"
#include "packet/Packet11UseBed.h"
#include "packet/Packet12Animation.h"
#include "packet/Packet14NamedEntitySpawn.h"
#include "packet/Packet15PickupSpawn.h"
#include "packet/Packet16CollectItem.h"
#include "packet/Packet17AddObjectVehicle.h"
#include "packet/Packet18MobSpawn.h"
#include "packet/Packet19EntityPainting.h"
#include "packet/Packet1AExperienceOrb.h"
#include "packet/Packet1CEntityVelocity.h"
#include "packet/Packet1DDestroyEntity.h"
#include "packet/Packet1EEntity.h"
#include "packet/Packet1FEntityRelativeMove.h"
#include "packet/Packet20EntityLook.h"
#include "packet/Packet21EntityLookAndRelativeMove.h"
#include "packet/Packet22EntityTeleport.h"
#include "packet/Packet23EntityHeadLook.h"
#include "packet/Packet26EntityStatus.h"
#include "packet/Packet27AttachEntity.h"
#include "packet/Packet28EntityMetadata.h"
#include "packet/Packet29EntityEffect.h"
#include "packet/Packet2ARemoveEntityEffect.h"
#include "packet/Packet2BExperience.h"
#include "packet/Packet32PreChunk.h"
#include "packet/Packet33MapChunk.h"
#include "packet/Packet34MultiBlockChange.h"
#include "packet/Packet35BlockChange.h"
#include "packet/Packet36BlockAction.h"
#include "packet/Packet3CExplosion.h"
#include "packet/Packet3DSoundParticleEffect.h"
#include "packet/Packet46NewInvalidState.h"
#include "packet/Packet47Thunderbolt.h"
#include "packet/Packet64OpenWindow.h"
#include "packet/Packet65CloseWindow.h"
#include "packet/Packet67SetSlot.h"
#include "packet/Packet68WindowItems.h"
#include "packet/Packet69UpdateWindowProperty.h"
#include "packet/Packet6ATransaction.h"
#include "packet/Packet6BCreativeInventoryAction.h"
#include "packet/Packet82UpdateSign.h"
#include "packet/Packet83ItemData.h"
#include "packet/Packet84UpdateTileEntity.h"
#include "packet/PacketC8IncrementStatistic.h"
#include "packet/PacketC9PlayerListItem.h"
#include "packet/PacketCAPlayerAbilities.h"
#include "packet/PacketFAPluginmessage.h"
#include "packet/PacketFFDisconnectKick.h"
#include "packet/PacketDummy.h"

using namespace std;

PacketServer **PacketManager::paketListe = NULL;

void PacketManager::registerPacket(PacketServer *paket) {
	delete PacketManager::paketListe[paket->getPacketId()];
	PacketManager::paketListe[paket->getPacketId()] = paket;
}

void PacketManager::initializePacketListe() {
	PacketManager::paketListe = (PacketServer **) malloc(
			sizeof(PacketServer *) * 256);

	for (short i = 0; i < 256; i++) {
		PacketManager::paketListe[i] = new PacketDummy();
	}

	Packet00KeepAlive::registerPacket();
	Packet01LoginRequest::registerPacket();
	Packet02Handshake::registerPacket();
	Packet03ChatMessage::registerPacket();
	Packet04TimeUpdate::registerPacket();
	Packet05EntityEquipment::registerPacket();
	Packet06SpawnPosition::registerPacket();
	Packet08UpdateHealth::registerPacket();
	Packet09Respawn::registerPacket();
	Packet0DPlayerPositionLook::registerPacket();
	Packet11UseBed::registerPacket();
	Packet12Animation::registerPacket();
	Packet14NamedEntitySpawn::registerPacket();
	Packet15PickupSpawn::registerPacket();
	Packet16CollectItem::registerPacket();
	Packet17AddObjectVehicle::registerPacket();
	Packet18MobSpawn::registerPacket();
	Packet19EntityPainting::registerPacket();
	Packet1AExperienceOrb::registerPacket();
	Packet1CEntityVelocity::registerPacket();
	Packet1DDestroyEntity::registerPacket();
	Packet1EEntity::registerPacket();
	Packet1FEntityRelativeMove::registerPacket();
	Packet20EntityLook::registerPacket();
	Packet21EntityLookAndRelativeMove::registerPacket();
	Packet22EntityTeleport::registerPacket();
	Packet23EntityHeadLook::registerPacket();
	Packet26EntityStatus::registerPacket();
	Packet27AttachEntity::registerPacket();
	Packet28EntityMetadata::registerPacket();
	Packet29EntityEffect::registerPacket();
	Packet2ARemoveEntityEffect::registerPacket();
	Packet2BExperience::registerPacket();
	Packet32PreChunk::registerPacket();
	Packet33MapChunk::registerPacket();
	Packet34MultiBlockChange::registerPacket();
	Packet35BlockChange::registerPacket();
	Packet36BlockAction::registerPacket();
	Packet3CExplosion::registerPacket();
	Packet3DSoundParticleEffect::registerPacket();
	Packet46NewInvalidState::registerPacket();
	Packet47Thunderbolt::registerPacket();
	Packet64OpenWindow::registerPacket();
	Packet65CloseWindow::registerPacket();
	Packet67SetSlot::registerPacket();
	Packet68WindowItems::registerPacket();
	Packet69UpdateWindowProperty::registerPacket();
	Packet6ATransaction::registerPacket();
	Packet6BCreativeInventoryAction::registerPacket();
	Packet82UpdateSign::registerPacket();
	Packet83ItemData::registerPacket();
	Packet84UpdateTileEntity::registerPacket();
	PacketC8IncrementStatistic::registerPacket();
	PacketC9PlayerListItem::registerPacket();
	PacketCAPlayerAbilities::registerPacket();
	PacketFAPluginmessage::registerPacket();
	PacketFFDisconnectKick::registerPacket();
}

PacketServer *PacketManager::getInstanz(byte byte) {
	PacketDummy *paketServer =
			dynamic_cast<PacketDummy *>(PacketManager::paketListe[byte]);
	if (paketServer != 0) {
		throw ExcPacketUnknownPacket(byte);
	}

	return PacketManager::paketListe[byte]->getInstance();
}
