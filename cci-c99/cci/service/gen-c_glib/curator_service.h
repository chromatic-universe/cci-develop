/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef CURATOR_SERVICE_H
#define CURATOR_SERVICE_H

#include <thrift/c_glib/processor/thrift_dispatch_processor.h>

#include "curator_types.h"

/* CuratorService service interface */
typedef struct _CuratorServiceIf CuratorServiceIf;  /* dummy object */

struct _CuratorServiceIfInterface
{
  GTypeInterface parent;

  gboolean (*acquire_lock) (CuratorServiceIf *iface, OptionalLockProjection ** _return, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, CuratorException ** ex1, GError **error);
  gboolean (*acquire_semaphore) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, CuratorException ** ex1, GError **error);
  gboolean (*close_curator_projection) (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
  gboolean (*close_generic_projection) (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const gchar * id, CuratorException ** ex1, GError **error);
  gboolean (*create_node) (CuratorServiceIf *iface, OptionalPath ** _return, const CuratorProjection * projection, const CreateSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*delete_node) (CuratorServiceIf *iface, const CuratorProjection * projection, const DeleteSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*exists) (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const ExistsSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_children) (CuratorServiceIf *iface, OptionalChildrenList ** _return, const CuratorProjection * projection, const GetChildrenSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_data) (CuratorServiceIf *iface, OptionalData ** _return, const CuratorProjection * projection, const GetDataSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_leader_participants) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_node_cache_data) (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_path_children_cache_data) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_path_children_cache_data_for_path) (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, CuratorException ** ex1, GError **error);
  gboolean (*is_leader) (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
  gboolean (*new_curator_projection) (CuratorServiceIf *iface, CuratorProjection ** _return, const gchar * connectionName, CuratorException ** ex1, GError **error);
  gboolean (*ping_curator_projection) (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
  gboolean (*set_data) (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const SetDataSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*start_leader_selector) (CuratorServiceIf *iface, LeaderResult ** _return, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, CuratorException ** ex1, GError **error);
  gboolean (*start_node_cache) (CuratorServiceIf *iface, NodeCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, CuratorException ** ex1, GError **error);
  gboolean (*start_path_children_cache) (CuratorServiceIf *iface, PathChildrenCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, CuratorException ** ex1, GError **error);
  gboolean (*start_persistent_ephemeral_node) (CuratorServiceIf *iface, PersistentEphemeralNodeProjection ** _return, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, CuratorException ** ex1, GError **error);
  gboolean (*sync) (CuratorServiceIf *iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, CuratorException ** ex1, GError **error);
};
typedef struct _CuratorServiceIfInterface CuratorServiceIfInterface;

GType curator_service_if_get_type (void);
#define TYPE_CURATOR_SERVICE_IF (curator_service_if_get_type())
#define CURATOR_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CURATOR_SERVICE_IF, CuratorServiceIf))
#define IS_CURATOR_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CURATOR_SERVICE_IF))
#define CURATOR_SERVICE_IF_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), TYPE_CURATOR_SERVICE_IF, CuratorServiceIfInterface))

gboolean curator_service_if_acquire_lock (CuratorServiceIf *iface, OptionalLockProjection ** _return, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, CuratorException ** ex1, GError **error);
gboolean curator_service_if_acquire_semaphore (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, CuratorException ** ex1, GError **error);
gboolean curator_service_if_close_curator_projection (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
gboolean curator_service_if_close_generic_projection (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const gchar * id, CuratorException ** ex1, GError **error);
gboolean curator_service_if_create_node (CuratorServiceIf *iface, OptionalPath ** _return, const CuratorProjection * projection, const CreateSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_delete_node (CuratorServiceIf *iface, const CuratorProjection * projection, const DeleteSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_exists (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const ExistsSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_children (CuratorServiceIf *iface, OptionalChildrenList ** _return, const CuratorProjection * projection, const GetChildrenSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_data (CuratorServiceIf *iface, OptionalData ** _return, const CuratorProjection * projection, const GetDataSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_leader_participants (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_node_cache_data (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_path_children_cache_data (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_if_get_path_children_cache_data_for_path (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, CuratorException ** ex1, GError **error);
gboolean curator_service_if_is_leader (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_if_new_curator_projection (CuratorServiceIf *iface, CuratorProjection ** _return, const gchar * connectionName, CuratorException ** ex1, GError **error);
gboolean curator_service_if_ping_curator_projection (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
gboolean curator_service_if_set_data (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const SetDataSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_if_start_leader_selector (CuratorServiceIf *iface, LeaderResult ** _return, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, CuratorException ** ex1, GError **error);
gboolean curator_service_if_start_node_cache (CuratorServiceIf *iface, NodeCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, CuratorException ** ex1, GError **error);
gboolean curator_service_if_start_path_children_cache (CuratorServiceIf *iface, PathChildrenCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, CuratorException ** ex1, GError **error);
gboolean curator_service_if_start_persistent_ephemeral_node (CuratorServiceIf *iface, PersistentEphemeralNodeProjection ** _return, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, CuratorException ** ex1, GError **error);
gboolean curator_service_if_sync (CuratorServiceIf *iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, CuratorException ** ex1, GError **error);

/* CuratorService service client */
struct _CuratorServiceClient
{
  GObject parent;

  ThriftProtocol *input_protocol;
  ThriftProtocol *output_protocol;
};
typedef struct _CuratorServiceClient CuratorServiceClient;

struct _CuratorServiceClientClass
{
  GObjectClass parent;
};
typedef struct _CuratorServiceClientClass CuratorServiceClientClass;

GType curator_service_client_get_type (void);
#define TYPE_CURATOR_SERVICE_CLIENT (curator_service_client_get_type())
#define CURATOR_SERVICE_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CURATOR_SERVICE_CLIENT, CuratorServiceClient))
#define CURATOR_SERVICE_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_CURATOR_SERVICE_CLIENT, CuratorServiceClientClass))
#define CURATOR_SERVICE_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CURATOR_SERVICE_CLIENT))
#define CURATOR_SERVICE_IS_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_CURATOR_SERVICE_CLIENT))
#define CURATOR_SERVICE_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CURATOR_SERVICE_CLIENT, CuratorServiceClientClass))

gboolean curator_service_client_acquire_lock (CuratorServiceIf * iface, OptionalLockProjection ** _return, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_acquire_lock (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, GError ** error);
gboolean curator_service_client_recv_acquire_lock (CuratorServiceIf * iface, OptionalLockProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_acquire_semaphore (CuratorServiceIf * iface, GPtrArray ** _return, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_acquire_semaphore (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, GError ** error);
gboolean curator_service_client_recv_acquire_semaphore (CuratorServiceIf * iface, GPtrArray ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_close_curator_projection (CuratorServiceIf * iface, const CuratorProjection * projection, GError ** error);
gboolean curator_service_client_send_close_curator_projection (CuratorServiceIf * iface, const CuratorProjection * projection, GError ** error);
gboolean curator_service_client_recv_close_curator_projection (CuratorServiceIf * iface, GError ** error);
gboolean curator_service_client_close_generic_projection (CuratorServiceIf * iface, gboolean* _return, const CuratorProjection * projection, const gchar * id, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_close_generic_projection (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * id, GError ** error);
gboolean curator_service_client_recv_close_generic_projection (CuratorServiceIf * iface, gboolean* _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_create_node (CuratorServiceIf * iface, OptionalPath ** _return, const CuratorProjection * projection, const CreateSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_create_node (CuratorServiceIf * iface, const CuratorProjection * projection, const CreateSpec * spec, GError ** error);
gboolean curator_service_client_recv_create_node (CuratorServiceIf * iface, OptionalPath ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_delete_node (CuratorServiceIf * iface, const CuratorProjection * projection, const DeleteSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_delete_node (CuratorServiceIf * iface, const CuratorProjection * projection, const DeleteSpec * spec, GError ** error);
gboolean curator_service_client_recv_delete_node (CuratorServiceIf * iface, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_exists (CuratorServiceIf * iface, OptionalStat ** _return, const CuratorProjection * projection, const ExistsSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_exists (CuratorServiceIf * iface, const CuratorProjection * projection, const ExistsSpec * spec, GError ** error);
gboolean curator_service_client_recv_exists (CuratorServiceIf * iface, OptionalStat ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_children (CuratorServiceIf * iface, OptionalChildrenList ** _return, const CuratorProjection * projection, const GetChildrenSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_children (CuratorServiceIf * iface, const CuratorProjection * projection, const GetChildrenSpec * spec, GError ** error);
gboolean curator_service_client_recv_get_children (CuratorServiceIf * iface, OptionalChildrenList ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_data (CuratorServiceIf * iface, OptionalData ** _return, const CuratorProjection * projection, const GetDataSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_data (CuratorServiceIf * iface, const CuratorProjection * projection, const GetDataSpec * spec, GError ** error);
gboolean curator_service_client_recv_get_data (CuratorServiceIf * iface, OptionalData ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_leader_participants (CuratorServiceIf * iface, GPtrArray ** _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_leader_participants (CuratorServiceIf * iface, const CuratorProjection * projection, const LeaderProjection * leaderProjection, GError ** error);
gboolean curator_service_client_recv_get_leader_participants (CuratorServiceIf * iface, GPtrArray ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_node_cache_data (CuratorServiceIf * iface, ChildData ** _return, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_node_cache_data (CuratorServiceIf * iface, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, GError ** error);
gboolean curator_service_client_recv_get_node_cache_data (CuratorServiceIf * iface, ChildData ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_path_children_cache_data (CuratorServiceIf * iface, GPtrArray ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_path_children_cache_data (CuratorServiceIf * iface, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, GError ** error);
gboolean curator_service_client_recv_get_path_children_cache_data (CuratorServiceIf * iface, GPtrArray ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_get_path_children_cache_data_for_path (CuratorServiceIf * iface, ChildData ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_get_path_children_cache_data_for_path (CuratorServiceIf * iface, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, GError ** error);
gboolean curator_service_client_recv_get_path_children_cache_data_for_path (CuratorServiceIf * iface, ChildData ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_is_leader (CuratorServiceIf * iface, gboolean* _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_is_leader (CuratorServiceIf * iface, const CuratorProjection * projection, const LeaderProjection * leaderProjection, GError ** error);
gboolean curator_service_client_recv_is_leader (CuratorServiceIf * iface, gboolean* _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_new_curator_projection (CuratorServiceIf * iface, CuratorProjection ** _return, const gchar * connectionName, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_new_curator_projection (CuratorServiceIf * iface, const gchar * connectionName, GError ** error);
gboolean curator_service_client_recv_new_curator_projection (CuratorServiceIf * iface, CuratorProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_ping_curator_projection (CuratorServiceIf * iface, const CuratorProjection * projection, GError ** error);
gboolean curator_service_client_send_ping_curator_projection (CuratorServiceIf * iface, const CuratorProjection * projection, GError ** error);
gboolean curator_service_client_set_data (CuratorServiceIf * iface, OptionalStat ** _return, const CuratorProjection * projection, const SetDataSpec * spec, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_set_data (CuratorServiceIf * iface, const CuratorProjection * projection, const SetDataSpec * spec, GError ** error);
gboolean curator_service_client_recv_set_data (CuratorServiceIf * iface, OptionalStat ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_start_leader_selector (CuratorServiceIf * iface, LeaderResult ** _return, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_start_leader_selector (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, GError ** error);
gboolean curator_service_client_recv_start_leader_selector (CuratorServiceIf * iface, LeaderResult ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_start_node_cache (CuratorServiceIf * iface, NodeCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_start_node_cache (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, GError ** error);
gboolean curator_service_client_recv_start_node_cache (CuratorServiceIf * iface, NodeCacheProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_start_path_children_cache (CuratorServiceIf * iface, PathChildrenCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_start_path_children_cache (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, GError ** error);
gboolean curator_service_client_recv_start_path_children_cache (CuratorServiceIf * iface, PathChildrenCacheProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_start_persistent_ephemeral_node (CuratorServiceIf * iface, PersistentEphemeralNodeProjection ** _return, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_start_persistent_ephemeral_node (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, GError ** error);
gboolean curator_service_client_recv_start_persistent_ephemeral_node (CuratorServiceIf * iface, PersistentEphemeralNodeProjection ** _return, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_sync (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, CuratorException ** ex1, GError ** error);
gboolean curator_service_client_send_sync (CuratorServiceIf * iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, GError ** error);
gboolean curator_service_client_recv_sync (CuratorServiceIf * iface, CuratorException ** ex1, GError ** error);
void curator_service_client_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
void curator_service_client_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);

/* CuratorService handler (abstract base class) */
struct _CuratorServiceHandler
{
  GObject parent;
};
typedef struct _CuratorServiceHandler CuratorServiceHandler;

struct _CuratorServiceHandlerClass
{
  GObjectClass parent;

  gboolean (*acquire_lock) (CuratorServiceIf *iface, OptionalLockProjection ** _return, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, CuratorException ** ex1, GError **error);
  gboolean (*acquire_semaphore) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, CuratorException ** ex1, GError **error);
  gboolean (*close_curator_projection) (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
  gboolean (*close_generic_projection) (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const gchar * id, CuratorException ** ex1, GError **error);
  gboolean (*create_node) (CuratorServiceIf *iface, OptionalPath ** _return, const CuratorProjection * projection, const CreateSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*delete_node) (CuratorServiceIf *iface, const CuratorProjection * projection, const DeleteSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*exists) (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const ExistsSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_children) (CuratorServiceIf *iface, OptionalChildrenList ** _return, const CuratorProjection * projection, const GetChildrenSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_data) (CuratorServiceIf *iface, OptionalData ** _return, const CuratorProjection * projection, const GetDataSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*get_leader_participants) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_node_cache_data) (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_path_children_cache_data) (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
  gboolean (*get_path_children_cache_data_for_path) (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, CuratorException ** ex1, GError **error);
  gboolean (*is_leader) (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
  gboolean (*new_curator_projection) (CuratorServiceIf *iface, CuratorProjection ** _return, const gchar * connectionName, CuratorException ** ex1, GError **error);
  gboolean (*ping_curator_projection) (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
  gboolean (*set_data) (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const SetDataSpec * spec, CuratorException ** ex1, GError **error);
  gboolean (*start_leader_selector) (CuratorServiceIf *iface, LeaderResult ** _return, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, CuratorException ** ex1, GError **error);
  gboolean (*start_node_cache) (CuratorServiceIf *iface, NodeCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, CuratorException ** ex1, GError **error);
  gboolean (*start_path_children_cache) (CuratorServiceIf *iface, PathChildrenCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, CuratorException ** ex1, GError **error);
  gboolean (*start_persistent_ephemeral_node) (CuratorServiceIf *iface, PersistentEphemeralNodeProjection ** _return, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, CuratorException ** ex1, GError **error);
  gboolean (*sync) (CuratorServiceIf *iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, CuratorException ** ex1, GError **error);
};
typedef struct _CuratorServiceHandlerClass CuratorServiceHandlerClass;

GType curator_service_handler_get_type (void);
#define TYPE_CURATOR_SERVICE_HANDLER (curator_service_handler_get_type())
#define CURATOR_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CURATOR_SERVICE_HANDLER, CuratorServiceHandler))
#define IS_CURATOR_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CURATOR_SERVICE_HANDLER))
#define CURATOR_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_CURATOR_SERVICE_HANDLER, CuratorServiceHandlerClass))
#define IS_CURATOR_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_CURATOR_SERVICE_HANDLER))
#define CURATOR_SERVICE_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CURATOR_SERVICE_HANDLER, CuratorServiceHandlerClass))

gboolean curator_service_handler_acquire_lock (CuratorServiceIf *iface, OptionalLockProjection ** _return, const CuratorProjection * projection, const gchar * path, const gint32 maxWaitMs, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_acquire_semaphore (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const gchar * path, const gint32 acquireQty, const gint32 maxWaitMs, const gint32 maxLeases, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_close_curator_projection (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
gboolean curator_service_handler_close_generic_projection (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const gchar * id, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_create_node (CuratorServiceIf *iface, OptionalPath ** _return, const CuratorProjection * projection, const CreateSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_delete_node (CuratorServiceIf *iface, const CuratorProjection * projection, const DeleteSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_exists (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const ExistsSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_children (CuratorServiceIf *iface, OptionalChildrenList ** _return, const CuratorProjection * projection, const GetChildrenSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_data (CuratorServiceIf *iface, OptionalData ** _return, const CuratorProjection * projection, const GetDataSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_leader_participants (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_node_cache_data (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const NodeCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_path_children_cache_data (CuratorServiceIf *iface, GPtrArray ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_get_path_children_cache_data_for_path (CuratorServiceIf *iface, ChildData ** _return, const CuratorProjection * projection, const PathChildrenCacheProjection * cacheProjection, const gchar * path, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_is_leader (CuratorServiceIf *iface, gboolean* _return, const CuratorProjection * projection, const LeaderProjection * leaderProjection, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_new_curator_projection (CuratorServiceIf *iface, CuratorProjection ** _return, const gchar * connectionName, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_ping_curator_projection (CuratorServiceIf *iface, const CuratorProjection * projection, GError **error);
gboolean curator_service_handler_set_data (CuratorServiceIf *iface, OptionalStat ** _return, const CuratorProjection * projection, const SetDataSpec * spec, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_start_leader_selector (CuratorServiceIf *iface, LeaderResult ** _return, const CuratorProjection * projection, const gchar * path, const gchar * participantId, const gint32 waitForLeadershipMs, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_start_node_cache (CuratorServiceIf *iface, NodeCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean dataIsCompressed, const gboolean buildInitial, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_start_path_children_cache (CuratorServiceIf *iface, PathChildrenCacheProjection ** _return, const CuratorProjection * projection, const gchar * path, const gboolean cacheData, const gboolean dataIsCompressed, const PathChildrenCacheStartMode startMode, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_start_persistent_ephemeral_node (CuratorServiceIf *iface, PersistentEphemeralNodeProjection ** _return, const CuratorProjection * projection, const gchar * path, const GByteArray * data, const PersistentEphemeralNodeMode mode, CuratorException ** ex1, GError **error);
gboolean curator_service_handler_sync (CuratorServiceIf *iface, const CuratorProjection * projection, const gchar * path, const gchar * asyncContext, CuratorException ** ex1, GError **error);

/* CuratorService processor */
struct _CuratorServiceProcessor
{
  ThriftDispatchProcessor parent;

  /* protected */
  CuratorServiceHandler *handler;
  GHashTable *process_map;
};
typedef struct _CuratorServiceProcessor CuratorServiceProcessor;

struct _CuratorServiceProcessorClass
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
typedef struct _CuratorServiceProcessorClass CuratorServiceProcessorClass;

GType curator_service_processor_get_type (void);
#define TYPE_CURATOR_SERVICE_PROCESSOR (curator_service_processor_get_type())
#define CURATOR_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CURATOR_SERVICE_PROCESSOR, CuratorServiceProcessor))
#define IS_CURATOR_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CURATOR_SERVICE_PROCESSOR))
#define CURATOR_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_CURATOR_SERVICE_PROCESSOR, CuratorServiceProcessorClass))
#define IS_CURATOR_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_CURATOR_SERVICE_PROCESSOR))
#define CURATOR_SERVICE_PROCESSOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CURATOR_SERVICE_PROCESSOR, CuratorServiceProcessorClass))

#endif /* CURATOR_SERVICE_H */