/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef DISCOVERY_SERVICE_H
#define DISCOVERY_SERVICE_H

#include <thrift/c_glib/processor/thrift_dispatch_processor.h>

#include "curator_types.h"

/* DiscoveryService service interface */
typedef struct _DiscoveryServiceIf DiscoveryServiceIf;  /* dummy object */

struct _DiscoveryServiceIfInterface
{
  GTypeInterface parent;

  gboolean (*get_all_instances) (DiscoveryServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_instance) (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
  gboolean (*make_discovery_instance) (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const gchar * name, const GByteArray * payload, const gint32 port, CuratorException ** ex1, GError **error);
  gboolean (*note_error) (DiscoveryServiceIf *iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, CuratorException ** ex1, GError **error);
  gboolean (*start_discovery) (DiscoveryServiceIf *iface, DiscoveryProjection ** _return, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, CuratorException ** ex1, GError **error);
  gboolean (*start_provider) (DiscoveryServiceIf *iface, DiscoveryProviderProjection ** _return, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, CuratorException ** ex1, GError **error);
};
typedef struct _DiscoveryServiceIfInterface DiscoveryServiceIfInterface;

GType discovery_service_if_get_type (void);
#define TYPE_DISCOVERY_SERVICE_IF (discovery_service_if_get_type())
#define DISCOVERY_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DISCOVERY_SERVICE_IF, DiscoveryServiceIf))
#define IS_DISCOVERY_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DISCOVERY_SERVICE_IF))
#define DISCOVERY_SERVICE_IF_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), TYPE_DISCOVERY_SERVICE_IF, DiscoveryServiceIfInterface))

gboolean discovery_service_if_get_all_instances (DiscoveryServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
gboolean discovery_service_if_get_instance (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
gboolean discovery_service_if_make_discovery_instance (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const gchar * name, const GByteArray * payload, const gint32 port, CuratorException ** ex1, GError **error);
gboolean discovery_service_if_note_error (DiscoveryServiceIf *iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, CuratorException ** ex1, GError **error);
gboolean discovery_service_if_start_discovery (DiscoveryServiceIf *iface, DiscoveryProjection ** _return, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, CuratorException ** ex1, GError **error);
gboolean discovery_service_if_start_provider (DiscoveryServiceIf *iface, DiscoveryProviderProjection ** _return, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, CuratorException ** ex1, GError **error);

/* DiscoveryService service client */
struct _DiscoveryServiceClient
{
  GObject parent;

  ThriftProtocol *input_protocol;
  ThriftProtocol *output_protocol;
};
typedef struct _DiscoveryServiceClient DiscoveryServiceClient;

struct _DiscoveryServiceClientClass
{
  GObjectClass parent;
};
typedef struct _DiscoveryServiceClientClass DiscoveryServiceClientClass;

GType discovery_service_client_get_type (void);
#define TYPE_DISCOVERY_SERVICE_CLIENT (discovery_service_client_get_type())
#define DISCOVERY_SERVICE_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DISCOVERY_SERVICE_CLIENT, DiscoveryServiceClient))
#define DISCOVERY_SERVICE_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_DISCOVERY_SERVICE_CLIENT, DiscoveryServiceClientClass))
#define DISCOVERY_SERVICE_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DISCOVERY_SERVICE_CLIENT))
#define DISCOVERY_SERVICE_IS_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_DISCOVERY_SERVICE_CLIENT))
#define DISCOVERY_SERVICE_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DISCOVERY_SERVICE_CLIENT, DiscoveryServiceClientClass))

gboolean discovery_service_client_get_all_instances (DiscoveryServiceIf * iface, GPtrArray ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_get_all_instances (DiscoveryServiceIf * iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, GError ** error);
gboolean discovery_service_client_recv_get_all_instances (DiscoveryServiceIf * iface, GPtrArray ** _return, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_get_instance (DiscoveryServiceIf * iface, DiscoveryInstance ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_get_instance (DiscoveryServiceIf * iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, GError ** error);
gboolean discovery_service_client_recv_get_instance (DiscoveryServiceIf * iface, DiscoveryInstance ** _return, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_make_discovery_instance (DiscoveryServiceIf * iface, DiscoveryInstance ** _return, const gchar * name, const GByteArray * payload, const gint32 port, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_make_discovery_instance (DiscoveryServiceIf * iface, const gchar * name, const GByteArray * payload, const gint32 port, GError ** error);
gboolean discovery_service_client_recv_make_discovery_instance (DiscoveryServiceIf * iface, DiscoveryInstance ** _return, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_note_error (DiscoveryServiceIf * iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_note_error (DiscoveryServiceIf * iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, GError ** error);
gboolean discovery_service_client_recv_note_error (DiscoveryServiceIf * iface, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_start_discovery (DiscoveryServiceIf * iface, DiscoveryProjection ** _return, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_start_discovery (DiscoveryServiceIf * iface, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, GError ** error);
gboolean discovery_service_client_recv_start_discovery (DiscoveryServiceIf * iface, DiscoveryProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_start_provider (DiscoveryServiceIf * iface, DiscoveryProviderProjection ** _return, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, CuratorException ** ex1, GError ** error);
gboolean discovery_service_client_send_start_provider (DiscoveryServiceIf * iface, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, GError ** error);
gboolean discovery_service_client_recv_start_provider (DiscoveryServiceIf * iface, DiscoveryProviderProjection ** _return, CuratorException ** ex1, GError ** error);
void discovery_service_client_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
void discovery_service_client_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);

/* DiscoveryService handler (abstract base class) */
struct _DiscoveryServiceHandler
{
  GObject parent;
};
typedef struct _DiscoveryServiceHandler DiscoveryServiceHandler;

struct _DiscoveryServiceHandlerClass
{
  GObjectClass parent;

  gboolean (*get_all_instances) (DiscoveryServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_instance) (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
  gboolean (*make_discovery_instance) (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const gchar * name, const GByteArray * payload, const gint32 port, CuratorException ** ex1, GError **error);
  gboolean (*note_error) (DiscoveryServiceIf *iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, CuratorException ** ex1, GError **error);
  gboolean (*start_discovery) (DiscoveryServiceIf *iface, DiscoveryProjection ** _return, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, CuratorException ** ex1, GError **error);
  gboolean (*start_provider) (DiscoveryServiceIf *iface, DiscoveryProviderProjection ** _return, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, CuratorException ** ex1, GError **error);
};
typedef struct _DiscoveryServiceHandlerClass DiscoveryServiceHandlerClass;

GType discovery_service_handler_get_type (void);
#define TYPE_DISCOVERY_SERVICE_HANDLER (discovery_service_handler_get_type())
#define DISCOVERY_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DISCOVERY_SERVICE_HANDLER, DiscoveryServiceHandler))
#define IS_DISCOVERY_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DISCOVERY_SERVICE_HANDLER))
#define DISCOVERY_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_DISCOVERY_SERVICE_HANDLER, DiscoveryServiceHandlerClass))
#define IS_DISCOVERY_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_DISCOVERY_SERVICE_HANDLER))
#define DISCOVERY_SERVICE_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DISCOVERY_SERVICE_HANDLER, DiscoveryServiceHandlerClass))

gboolean discovery_service_handler_get_all_instances (DiscoveryServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
gboolean discovery_service_handler_get_instance (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, CuratorException ** ex1, GError **error);
gboolean discovery_service_handler_make_discovery_instance (DiscoveryServiceIf *iface, DiscoveryInstance ** _return, const gchar * name, const GByteArray * payload, const gint32 port, CuratorException ** ex1, GError **error);
gboolean discovery_service_handler_note_error (DiscoveryServiceIf *iface, const CuratorProjection * projection, const DiscoveryProviderProjection * providerProjection, const gchar * instanceId, CuratorException ** ex1, GError **error);
gboolean discovery_service_handler_start_discovery (DiscoveryServiceIf *iface, DiscoveryProjection ** _return, const CuratorProjection * projection, const gchar * basePath, const DiscoveryInstance * yourInstance, CuratorException ** ex1, GError **error);
gboolean discovery_service_handler_start_provider (DiscoveryServiceIf *iface, DiscoveryProviderProjection ** _return, const CuratorProjection * projection, const DiscoveryProjection * discoveryProjection, const gchar * serviceName, const ProviderStrategyType providerStrategy, const gint32 downTimeoutMs, const gint32 downErrorThreshold, CuratorException ** ex1, GError **error);

/* DiscoveryService processor */
struct _DiscoveryServiceProcessor
{
  ThriftDispatchProcessor parent;

  /* protected */
  DiscoveryServiceHandler *handler;
  GHashTable *process_map;
};
typedef struct _DiscoveryServiceProcessor DiscoveryServiceProcessor;

struct _DiscoveryServiceProcessorClass
{
  ThriftDispatchProcessorClass parent;

  /* protected */
  gboolean (*dispatch_call) (ThriftDispatchProcessor *processor,
                             ThriftProtocol *in,
                             ThriftProtocol *out,
                             gchar *fname,
                             gint32 seqid,
                             GError **error);
};
typedef struct _DiscoveryServiceProcessorClass DiscoveryServiceProcessorClass;

GType discovery_service_processor_get_type (void);
#define TYPE_DISCOVERY_SERVICE_PROCESSOR (discovery_service_processor_get_type())
#define DISCOVERY_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DISCOVERY_SERVICE_PROCESSOR, DiscoveryServiceProcessor))
#define IS_DISCOVERY_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DISCOVERY_SERVICE_PROCESSOR))
#define DISCOVERY_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_DISCOVERY_SERVICE_PROCESSOR, DiscoveryServiceProcessorClass))
#define IS_DISCOVERY_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_DISCOVERY_SERVICE_PROCESSOR))
#define DISCOVERY_SERVICE_PROCESSOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DISCOVERY_SERVICE_PROCESSOR, DiscoveryServiceProcessorClass))

#endif /* DISCOVERY_SERVICE_H */
