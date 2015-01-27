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

void PacketManager::registrierePacket(PacketServer *paket) {
	delete PacketManager::paketListe[paket->gebePacketId()];
	PacketManager::paketListe[paket->gebePacketId()] = paket;
}

void PacketManager::initializePacketListe() {
	PacketManager::paketListe = (PacketServer **) malloc(
			sizeof(PacketServer *) * 256);

	for (short i = 0; i < 256; i++) {
		PacketManager::paketListe[i] = new PacketDummy();
	}

	Packet00KeepAlive::registierePacket();
	Packet01LoginRequest::registierePacket();
	Packet02Handshake::registierePacket();
	Packet03ChatMessage::registierePacket();
	Packet04TimeUpdate::registierePacket();
	Packet05EntityEquipment::registierePacket();
	Packet06SpawnPosition::registierePacket();
	Packet08UpdateHealth::registierePacket();
	Packet09Respawn::registierePacket();
	Packet0DPlayerPositionLook::registierePacket();
	Packet11UseBed::registierePacket();
	Packet12Animation::registierePacket();
	Packet14NamedEntitySpawn::registierePacket();
	Packet15PickupSpawn::registierePacket();
	Packet16CollectItem::registierePacket();
	Packet17AddObjectVehicle::registierePacket();
	Packet18MobSpawn::registierePacket();
	Packet19EntityPainting::registierePacket();
	Packet1AExperienceOrb::registierePacket();
	Packet1CEntityVelocity::registierePacket();
	Packet1DDestroyEntity::registierePacket();
	Packet1EEntity::registierePacket();
	Packet1FEntityRelativeMove::registierePacket();
	Packet20EntityLook::registierePacket();
	Packet21EntityLookAndRelativeMove::registierePacket();
	Packet22EntityTeleport::registierePacket();
	Packet23EntityHeadLook::registierePacket();
	Packet26EntityStatus::registierePacket();
	Packet27AttachEntity::registierePacket();
	Packet28EntityMetadata::registierePacket();
	Packet29EntityEffect::registierePacket();
	Packet2ARemoveEntityEffect::registierePacket();
	Packet2BExperience::registierePacket();
	Packet32PreChunk::registierePacket();
	Packet33MapChunk::registierePacket();
	Packet34MultiBlockChange::registierePacket();
	Packet35BlockChange::registierePacket();
	Packet36BlockAction::registierePacket();
	Packet3CExplosion::registierePacket();
	Packet3DSoundParticleEffect::registierePacket();
	Packet46NewInvalidState::registierePacket();
	Packet47Thunderbolt::registierePacket();
	Packet64OpenWindow::registierePacket();
	Packet65CloseWindow::registierePacket();
	Packet67SetSlot::registierePacket();
	Packet68WindowItems::registierePacket();
	Packet69UpdateWindowProperty::registierePacket();
	Packet6ATransaction::registierePacket();
	Packet6BCreativeInventoryAction::registierePacket();
	Packet82UpdateSign::registierePacket();
	Packet83ItemData::registierePacket();
	Packet84UpdateTileEntity::registierePacket();
	PacketC8IncrementStatistic::registierePacket();
	PacketC9PlayerListItem::registierePacket();
	PacketCAPlayerAbilities::registierePacket();
	PacketFAPluginmessage::registierePacket();
	PacketFFDisconnectKick::registierePacket();
}

PacketServer *PacketManager::getInstanz(byte byte) {
	PacketDummy *paketServer =
			dynamic_cast<PacketDummy *>(PacketManager::paketListe[byte]);
	if (paketServer != 0) {
		throw ExcPacketUnknownPacket(byte);
	}

	return PacketManager::paketListe[byte]->gebeInstanz();
}
