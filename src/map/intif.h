/****************************************************************************!
*                _           _   _   _                                       *
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *
*                                                                            *
*                            www.brathena.org                                *
******************************************************************************
* src/map/intif.h                                                            *
******************************************************************************
* Copyright (c) brAthena Dev Team                                            *
* Copyright (c) Hercules Dev Team                                            *
* Copyright (c) Athena Dev Teams                                             *
*                                                                            *
* Licenciado sob a licen�a GNU GPL                                           *
* Para mais informa��es leia o arquivo LICENSE na ra�z do emulador           *
*****************************************************************************/

#ifndef MAP_INTIF_H
#define MAP_INTIF_H

#include "common/cbasetypes.h"

/**
 * Declarations
 **/
struct auction_data;
struct guild_member;
struct guild_position;
struct guild_storage;
struct mail_message;
struct map_session_data;
struct party_member;
struct s_elemental;
struct s_homunculus;
struct s_mercenary;
struct s_pet;

/**
 * Defines
 **/
#define intif_rename_pc(sd, name)  (intif->rename((sd), 0, (name)))
#define intif_rename_pet(sd, name) (intif->rename((sd), 1, (name)))
#define intif_rename_hom(sd, name) (intif->rename((sd), 2, (name)))
#define INTIF_PACKET_LEN_TABLE_SIZE 161


/**
 * intif.c Interface
 **/
struct intif_interface {
	/* */
	int packet_len_table[INTIF_PACKET_LEN_TABLE_SIZE];
	/* funcs */
	int (*parse) (int fd);
	int (*create_pet)(int account_id, int char_id, short pet_type, short pet_lv, short pet_egg_id,
	                  short pet_equip, short intimate, short hungry, char rename_flag, char incubate, char *pet_name);
	int (*broadcast) (const char* mes, int len, int type);
	int (*broadcast2) (const char* mes, int len, unsigned int fontColor, short fontType, short fontSize, short fontAlign, short fontY);
	int (*main_message) (struct map_session_data* sd, const char* message);
	int (*wis_message) (struct map_session_data *sd,char *nick,char *mes,int mes_len);
	int (*wis_message_to_gm) (char *Wisp_name, int permission, char *mes);
	int (*saveregistry) (struct map_session_data *sd);
	int (*request_registry) (struct map_session_data *sd, int flag);
	int (*request_guild_storage) (int account_id, int guild_id);
	int (*send_guild_storage) (int account_id, struct guild_storage *gstor);
	int (*create_party) (struct party_member *member,char *name,int item,int item2);
	int (*request_partyinfo) (int party_id, int char_id);
	int (*party_addmember) (int party_id,struct party_member *member);
	int (*party_changeoption) (int party_id, int account_id, int exp, int item);
	int (*party_leave) (int party_id,int account_id, int char_id);
	int (*party_changemap) (struct map_session_data *sd, int online);
	int (*break_party) (int party_id);
	int (*party_message) (int party_id, int account_id, const char *mes,int len);
	int (*party_leaderchange) (int party_id,int account_id,int char_id);
	int (*guild_create) (const char *name, const struct guild_member *master);
	int (*guild_request_info) (int guild_id);
	int (*guild_addmember) (int guild_id, struct guild_member *m);
	int (*guild_leave) (int guild_id, int account_id, int char_id, int flag, const char *mes);
	int (*guild_memberinfoshort) (int guild_id, int account_id, int char_id, int online, int lv, int class_);
	int (*guild_break) (int guild_id);
	int (*guild_message) (int guild_id, int account_id, const char *mes, int len);
	int (*guild_change_gm) (int guild_id, const char* name, int len);
	int (*guild_change_basicinfo) (int guild_id, int type, const void *data, int len);
	int (*guild_change_memberinfo) (int guild_id, int account_id, int char_id, int type, const void *data, int len);
	int (*guild_position) (int guild_id, int idx, struct guild_position *p);
	int (*guild_skillup) (int guild_id, uint16 skill_id, int account_id, int max);
	int (*guild_alliance) (int guild_id1, int guild_id2, int account_id1, int account_id2, int flag);
	int (*guild_notice) (int guild_id, const char *mes1, const char *mes2);
	int (*guild_emblem) (int guild_id, int len, const char *data);
	int (*guild_castle_dataload) (int num, int *castle_ids);
	int (*guild_castle_datasave) (int castle_id, int index, int value);
	void (*itembound_req) (int char_id, int aid, int guild_id);
	int (*request_petdata) (int account_id, int char_id, int pet_id);
	int (*save_petdata) (int account_id, struct s_pet *p);
	int (*delete_petdata) (int pet_id);
	int (*rename) (struct map_session_data *sd, int type, char *name);
	int (*homunculus_create) (int account_id, struct s_homunculus *sh);
	bool (*homunculus_requestload) (int account_id, int homun_id);
	int (*homunculus_requestsave) (int account_id, struct s_homunculus* sh);
	int (*homunculus_requestdelete) (int homun_id);
	/******QUEST SYTEM*******/
	void (*request_questlog) (struct map_session_data * sd);
	int (*quest_save) (struct map_session_data * sd);
	// MERCENARY SYSTEM
	int (*mercenary_create) (struct s_mercenary *merc);
	int (*mercenary_request) (int merc_id, int char_id);
	int (*mercenary_delete) (int merc_id);
	int (*mercenary_save) (struct s_mercenary *merc);
	// MAIL SYSTEM
	int (*Mail_requestinbox) (int char_id, unsigned char flag);
	int (*Mail_read) (int mail_id);
	int (*Mail_getattach) (int char_id, int mail_id);
	int (*Mail_delete) (int char_id, int mail_id);
	int (*Mail_return) (int char_id, int mail_id);
	int (*Mail_send) (int account_id, struct mail_message *msg);
	// AUCTION SYSTEM
	int (*Auction_requestlist) (int char_id, short type, int price, const char* searchtext, short page);
	int (*Auction_register) (struct auction_data *auction);
	int (*Auction_cancel) (int char_id, unsigned int auction_id);
	int (*Auction_close) (int char_id, unsigned int auction_id);
	int (*Auction_bid) (int char_id, const char* name, unsigned int auction_id, int bid);
	// ELEMENTAL SYSTEM
	int (*elemental_create) (struct s_elemental *ele);
	int (*elemental_request) (int ele_id, int char_id);
	int (*elemental_delete) (int ele_id);
	int (*elemental_save) (struct s_elemental *ele);
	/* @accinfo */
	void (*request_accinfo) (int u_fd, int aid, int group_lv, char* query);
	/* */
	int (*CheckForCharServer) (void);
	/* */
	void (*pWisMessage) (int fd);
	void (*pWisEnd) (int fd);
	int (*pWisToGM_sub) (struct map_session_data* sd,va_list va);
	void (*pWisToGM) (int fd);
	void (*pRegisters) (int fd);
	void (*pChangeNameOk) (int fd);
	void (*pMessageToFD) (int fd);
	void (*pLoadGuildStorage) (int fd);
	void (*pSaveGuildStorage) (int fd);
	void (*pPartyCreated) (int fd);
	void (*pPartyInfo) (int fd);
	void (*pPartyMemberAdded) (int fd);
	void (*pPartyOptionChanged) (int fd);
	void (*pPartyMemberWithdraw) (int fd);
	void (*pPartyMove) (int fd);
	void (*pPartyBroken) (int fd);
	void (*pPartyMessage) (int fd);
	void (*pGuildCreated) (int fd);
	void (*pGuildInfo) (int fd);
	void (*pGuildMemberAdded) (int fd);
	void (*pGuildMemberWithdraw) (int fd);
	void (*pGuildMemberInfoShort) (int fd);
	void (*pGuildBroken) (int fd);
	void (*pGuildMessage) (int fd);
	void (*pGuildBasicInfoChanged) (int fd);
	void (*pGuildMemberInfoChanged) (int fd);
	void (*pGuildPosition) (int fd);
	void (*pGuildSkillUp) (int fd);
	void (*pGuildAlliance) (int fd);
	void (*pGuildNotice) (int fd);
	void (*pGuildEmblem) (int fd);
	void (*pGuildCastleDataLoad) (int fd);
	void (*pGuildMasterChanged) (int fd);
	void (*pQuestLog) (int fd);
	void (*pQuestSave) (int fd);
	void (*pMailInboxReceived) (int fd);
	void (*pMailNew) (int fd);
	void (*pMailGetAttach) (int fd);
	void (*pMailDelete) (int fd);
	void (*pMailReturn) (int fd);
	void (*pMailSend) (int fd);
	void (*pAuctionResults) (int fd);
	void (*pAuctionRegister) (int fd);
	void (*pAuctionCancel) (int fd);
	void (*pAuctionClose) (int fd);
	void (*pAuctionMessage) (int fd);
	void (*pAuctionBid) (int fd);
	void (*pItembound_ack) (int fd);
	void (*pMercenaryReceived) (int fd);
	void (*pMercenaryDeleted) (int fd);
	void (*pMercenarySaved) (int fd);
	void (*pElementalReceived) (int fd);
	void (*pElementalDeleted) (int fd);
	void (*pElementalSaved) (int fd);
	void (*pCreatePet) (int fd);
	void (*pRecvPetData) (int fd);
	void (*pSavePetOk) (int fd);
	void (*pDeletePetOk) (int fd);
	void (*pCreateHomunculus) (int fd);
	void (*pRecvHomunculusData) (int fd);
	void (*pSaveHomunculusOk) (int fd);
	void (*pDeleteHomunculusOk) (int fd);
};

struct intif_interface *intif;

#ifdef BRATHENA_CORE
void intif_defaults(void);
#endif // BRATHENA_CORE

#endif /* MAP_INTIF_H */
