
#if !defined( NET_APIH )
#define NET_APIH
#ifdef _WIN32
#pragma once
#endif

#if !defined ( NETADRH )
#include "netadr.h"
#endif

#define NETAPI_REQUEST_SERVERLIST	( 0 )
#define NETAPI_REQUEST_PING			( 1 )
#define NETAPI_REQUEST_RULES		( 2 )
#define NETAPI_REQUEST_PLAYERS		( 3 )
#define NETAPI_REQUEST_DETAILS		( 4 )

#define FNETAPI_MULTIPLE_RESPONSE ( 1<<0 )

typedef void ( *net_api_response_func_t ) ( struct net_response_s *response );

#define NET_SUCCESS						( 0 )
#define NET_ERROR_TIMEOUT				( 1<<0 )
#define NET_ERROR_PROTO_UNSUPPORTED		( 1<<1 )
#define NET_ERROR_UNDEFINED				( 1<<2 )

typedef struct net_adrlist_s
{
	struct net_adrlist_s	*next;
	netadr_t				remote_address;
} net_adrlist_t;

typedef struct net_response_s
{
	int			error;

	int			context;
	int			type;

	netadr_t	remote_address;

	double		ping;
	void		*response;
} net_response_t;

typedef struct net_status_s
{
	int			connected; 
	netadr_t	local_address;
	netadr_t	remote_address;
	int			packet_loss;
	double		latency;
	double		connection_time;
	double		rate;
} net_status_t;

typedef struct net_api_s
{
	void		( *InitNetworking )( void );
	void		( *Status ) ( struct net_status_s *status );
	void		( *SendRequest) ( int context, int request, int flags, double timeout, struct netadr_s *remote_address, net_api_response_func_t response );
	void		( *CancelRequest ) ( int context );
	void		( *CancelAllRequests ) ( void );
	char		*( *AdrToString ) ( struct netadr_s *a );
	int			( *CompareAdr ) ( struct netadr_s *a, struct netadr_s *b );
	int			( *StringToAdr ) ( char *s, struct netadr_s *a );
	const char *( *ValueForKey ) ( const char *s, const char *key );
	void		( *RemoveKey ) ( char *s, const char *key );
	void		( *SetValueForKey ) (char *s, const char *key, const char *value, int maxsize );
} net_api_t;

extern net_api_t netapi;

#endif