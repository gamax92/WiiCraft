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
#include "../exception/ExcPacketUnbekanntesPacket.h"
#include "paket/Packet00KeepAlive.h"
#include "paket/Packet01LoginRequest.h"
#include "paket/Packet02Handshake.h"
#include "paket/Packet03ChatMessage.h"
#include "paket/Packet04TimeUpdate.h"
#include "paket/Packet05EntityEquipment.h"
#include "paket/Packet06SpawnPosition.h"
#include "paket/Packet08UpdateHealth.h"
#include "paket/Packet09Respawn.h"
#include "paket/Packet0DPlayerPositionLook.h"
#include "paket/Packet11UseBed.h"
#include "paket/Packet12Animation.h"
#include "paket/Packet14NamedEntitySpawn.h"
#include "paket/Packet15PickupSpawn.h"
#include "paket/Packet16CollectItem.h"
#include "paket/Packet17AddObjectVehicle.h"
#include "paket/Packet18MobSpawn.h"
#include "paket/Packet19EntityPainting.h"
#include "paket/Packet1AExperienceOrb.h"
#include "paket/Packet1CEntityVelocity.h"
#include "paket/Packet1DDestroyEntity.h"
#include "paket/Packet1EEntity.h"
#include "paket/Packet1FEntityRelativeMove.h"
#include "paket/Packet20EntityLook.h"
#include "paket/Packet21EntityLookAndRelativeMove.h"
#include "paket/Packet22EntityTeleport.h"
#include "paket/Packet23EntityHeadLook.h"
#include "paket/Packet26EntityStatus.h"
#include "paket/Packet27AttachEntity.h"
#include "paket/Packet28EntityMetadata.h"
#include "paket/Packet29EntityEffect.h"
#include "paket/Packet2ARemoveEntityEffect.h"
#include "paket/Packet2BExperience.h"
#include "paket/Packet32PreChunk.h"
#include "paket/Packet33MapChunk.h"
#include "paket/Packet34MultiBlockChange.h"
#include "paket/Packet35BlockChange.h"
#include "paket/Packet36BlockAction.h"
#include "paket/Packet3CExplosion.h"
#include "paket/Packet3DSoundParticleEffect.h"
#include "paket/Packet46NewInvalidState.h"
#include "paket/Packet47Thunderbolt.h"
#include "paket/Packet64OpenWindow.h"
#include "paket/Packet65CloseWindow.h"
#include "paket/Packet67SetSlot.h"
#include "paket/Packet68WindowItems.h"
#include "paket/Packet69UpdateWindowProperty.h"
#include "paket/Packet6ATransaction.h"
#include "paket/Packet6BCreativeInventoryAction.h"
#include "paket/Packet82UpdateSign.h"
#include "paket/Packet83ItemData.h"
#include "paket/Packet84UpdateTileEntity.h"
#include "paket/PacketC8IncrementStatistic.h"
#include "paket/PacketC9PlayerListItem.h"
#include "paket/PacketCAPlayerAbilities.h"
#include "paket/PacketFAPluginmessage.h"
#include "paket/PacketFFDisconnectKick.h"
#include "paket/PacketDummy.h"

using namespace std;

PacketServer **PacketManager::paketListe = NULL;

void PacketManager::registrierePacket(PacketServer *paket) {
	delete PacketManager::paketListe[paket->gebePacketId()];
	PacketManager::paketListe[paket->gebePacketId()] = paket;
}

void PacketManager::initialisierePacketListe() {
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
		throw ExcPacketUnbekanntesPacket(byte);
	}

	return PacketManager::paketListe[byte]->gebeInstanz();
}
