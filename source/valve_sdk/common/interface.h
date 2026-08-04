


#ifndef INTERFACE_H
#define INTERFACE_H

#ifdef __cplusplus

class IBaseInterface
{
public:

	virtual			~IBaseInterface() {}
};


#define CREATEINTERFACE_PROCNAME	"CreateInterface"
typedef IBaseInterface* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);


typedef IBaseInterface* (*InstantiateInterfaceFn)();


class InterfaceReg
{
public:
				InterfaceReg(InstantiateInterfaceFn fn, const char *pName);

public:

	InstantiateInterfaceFn	m_CreateFn;
	const char				*m_pName;

	InterfaceReg			*m_pNext;
	static InterfaceReg		*s_pInterfaceRegs;
};


#define EXPOSE_INTERFACE_FN(functionName, interfaceName, versionName) \
	static InterfaceReg __g_Create##className##_reg(functionName, versionName);

#define EXPOSE_INTERFACE(className, interfaceName, versionName) \
	static IBaseInterface* __Create##className##_interface() {return (interfaceName *)new className;}\
	static InterfaceReg __g_Create##className##_reg(__Create##className##_interface, versionName );

#define EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, globalVarName) \
	static IBaseInterface* __Create##className##interfaceName##_interface() {return (interfaceName *)&globalVarName;}\
	static InterfaceReg __g_Create##className##interfaceName##_reg(__Create##className##interfaceName##_interface, versionName);

#define EXPOSE_SINGLE_INTERFACE(className, interfaceName, versionName) \
	static className __g_##className##_singleton;\
	EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, __g_##className##_singleton)


#ifdef WIN32
	#define EXPORT_FUNCTION __declspec(dllexport)
#else
	#define EXPORT_FUNCTION
#endif


enum 
{
	IFACE_OK = 0,
	IFACE_FAILED
};


extern "C"
{
	EXPORT_FUNCTION IBaseInterface* CreateInterface(const char *pName, int *pReturnCode);
};


typedef struct HInterfaceModule_t* HINTERFACEMODULE;


extern HINTERFACEMODULE		Sys_LoadModule(const char *pModuleName);
extern void					Sys_FreeModule(HINTERFACEMODULE hModule);

extern CreateInterfaceFn	Sys_GetFactory( HINTERFACEMODULE hModule );
extern CreateInterfaceFn	Sys_GetFactoryThis( void );

#endif

#endif