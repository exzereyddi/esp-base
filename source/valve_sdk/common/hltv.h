
#ifndef HLTV_H
#define HLTV_H

#define TYPE_CLIENT				0
#define TYPE_PROXY				1
#define TYPE_COMMENTATOR		3
#define TYPE_DEMO				4

#define HLTV_ACTIVE				0
#define HLTV_STATUS				1
#define HLTV_LISTEN				2

#define DRC_CMD_NONE				0
#define DRC_CMD_START				1
#define DRC_CMD_EVENT				2
#define DRC_CMD_MODE				3
#define DRC_CMD_CAMERA				4
#define DRC_CMD_TIMESCALE			5
#define DRC_CMD_MESSAGE				6
#define DRC_CMD_SOUND				7
#define DRC_CMD_STATUS				8
#define DRC_CMD_BANNER				9
#define DRC_CMD_STUFFTEXT			10
#define DRC_CMD_CHASE				11
#define DRC_CMD_INEYE				12
#define DRC_CMD_MAP					13
#define DRC_CMD_CAMPATH				14
#define DRC_CMD_WAYPOINTS			15

#define DRC_CMD_LAST				15


#define DRC_FLAG_PRIO_MASK		0x0F
#define DRC_FLAG_SIDE			(1<<4)
#define DRC_FLAG_DRAMATIC		(1<<5)
#define DRC_FLAG_SLOWMOTION		(1<<6)
#define DRC_FLAG_FACEPLAYER		(1<<7)
#define DRC_FLAG_INTRO			(1<<8)
#define DRC_FLAG_FINAL			(1<<9)
#define DRC_FLAG_NO_RANDOM		(1<<10)


#define DRC_FLAG_STARTPATH		1
#define DRC_FLAG_SLOWSTART		2
#define DRC_FLAG_SLOWEND		4

#endif