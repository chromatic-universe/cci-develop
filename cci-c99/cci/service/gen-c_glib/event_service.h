/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef EVENT_SERVICE_H
#define EVENT_SERVICE_H

#include <thrift/c_glib/processor/thrift_dispatch_processor.h>

#include "curator_types.h"

/* EventService service interface */
typedef struct _EventServiceIf EventServiceIf;  /* dummy object */

struct _EventServiceIfInterface
{
  GTypeInterface parent;

  gboolean (*get_next_event) (EventServiceIf *iface, CuratorEvent ** _return, const CuratorProjection * projection, CuratorException ** ex1, GError **error);
};
typedef struct _EventServiceIfInterface EventServiceIfInterface;

GType event_service_if_get_type (void);
#define TYPE_EVENT_SERVICE_IF (event_service_if_get_type())
#define EVENT_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EVENT_SERVICE_IF, EventServiceIf))
#define IS_EVENT_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EVENT_SERVICE_IF))
#define EVENT_SERVICE_IF_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), TYPE_EVENT_SERVICE_IF, EventServiceIfInterface))

gboolean event_service_if_get_next_event (EventServiceIf *iface, CuratorEvent ** _return, const CuratorProjection * projection, CuratorException ** ex1, GError **error);

/* EventService service client */
struct _EventServiceClient
{
  GObject parent;

  ThriftProtocol *input_protocol;
  ThriftProtocol *output_protocol;
};
typedef struct _EventServiceClient EventServiceClient;

struct _EventServiceClientClass
{
  GObjectClass parent;
};
typedef struct _EventServiceClientClass EventServiceClientClass;

GType event_service_client_get_type (void);
#define TYPE_EVENT_SERVICE_CLIENT (event_service_client_get_type())
#define EVENT_SERVICE_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EVENT_SERVICE_CLIENT, EventServiceClient))
#define EVENT_SERVICE_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_EVENT_SERVICE_CLIENT, EventServiceClientClass))
#define EVENT_SERVICE_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EVENT_SERVICE_CLIENT))
#define EVENT_SERVICE_IS_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_EVENT_SERVICE_CLIENT))
#define EVENT_SERVICE_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EVENT_SERVICE_CLIENT, EventServiceClientClass))

gboolean event_service_client_get_next_event (EventServiceIf * iface, CuratorEvent ** _return, const CuratorProjection * projection, CuratorException ** ex1, GError ** error);
gboolean event_service_client_send_get_next_event (EventServiceIf * iface, const CuratorProjection * projection, GError ** error);
gboolean event_service_client_recv_get_next_event (EventServiceIf * iface, CuratorEvent ** _return, CuratorException ** ex1, GError ** error);
void event_service_client_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
void event_service_client_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);

/* EventService handler (abstract base class) */
struct _EventServiceHandler
{
  GObject parent;
};
typedef struct _EventServiceHandler EventServiceHandler;

struct _EventServiceHandlerClass
{
  GObjectClass parent;

  gboolean (*get_next_event) (EventServiceIf *iface, CuratorEvent ** _return, const CuratorProjection * projection, CuratorException ** ex1, GError **error);
};
typedef struct _EventServiceHandlerClass EventServiceHandlerClass;

GType event_service_handler_get_type (void);
#define TYPE_EVENT_SERVICE_HANDLER (event_service_handler_get_type())
#define EVENT_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EVENT_SERVICE_HANDLER, EventServiceHandler))
#define IS_EVENT_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EVENT_SERVICE_HANDLER))
#define EVENT_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_EVENT_SERVICE_HANDLER, EventServiceHandlerClass))
#define IS_EVENT_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_EVENT_SERVICE_HANDLER))
#define EVENT_SERVICE_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EVENT_SERVICE_HANDLER, EventServiceHandlerClass))

gboolean event_service_handler_get_next_event (EventServiceIf *iface, CuratorEvent ** _return, const CuratorProjection * projection, CuratorException ** ex1, GError **error);

/* EventService processor */
struct _EventServiceProcessor
{
  ThriftDispatchProcessor parent;

  /* protected */
  EventServiceHandler *handler;
  GHashTable *process_map;
};
typedef struct _EventServiceProcessor EventServiceProcessor;

struct _EventServiceProcessorClass
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
typedef struct _EventServiceProcessorClass EventServiceProcessorClass;

GType event_service_processor_get_type (void);
#define TYPE_EVENT_SERVICE_PROCESSOR (event_service_processor_get_type())
#define EVENT_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EVENT_SERVICE_PROCESSOR, EventServiceProcessor))
#define IS_EVENT_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EVENT_SERVICE_PROCESSOR))
#define EVENT_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_EVENT_SERVICE_PROCESSOR, EventServiceProcessorClass))
#define IS_EVENT_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_EVENT_SERVICE_PROCESSOR))
#define EVENT_SERVICE_PROCESSOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EVENT_SERVICE_PROCESSOR, EventServiceProcessorClass))

#endif /* EVENT_SERVICE_H */
