

#define DRC_ACTIVE				0
#define DRC_STATUS				1
#define DRC_CAMERA				2
#define DRC_EVENT				3


#define DRC_FLAG_PRIO_MASK		0x0F
#define DRC_FLAG_SIDE			(1<<4)	
#define DRC_FLAG_DRAMATIC		(1<<5)




#define DRCAPI_NOP					0
#define DRCAPI_ACTIVE				1
#define DRCAPI_STATUS				2
#define DRCAPI_SETCAM				3
#define DRCAPI_GETCAM				4
#define DRCAPI_DIRPLAY				5
#define DRCAPI_DIRFREEZE			6
#define DRCAPI_SETVIEWMODE			7
#define DRCAPI_SETOVERVIEWPARAMS	8
#define DRCAPI_SETFOCUS				9
#define DRCAPI_GETTARGETS			10
#define DRCAPI_SETVIEWPOINTS		11