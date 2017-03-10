#pragma once

#include <QObject>

#include <ilm/ilm_control.h>

class slm : public QObject {
Q_OBJECT

public:
    void start();
    void create_layer(t_ilm_layer id);

signals:
    void notify_surface(t_ilm_uint id, t_ilm_bool created);
    void notify_layer(t_ilm_uint id, t_ilm_bool created);

public slots:
    void change_layout(t_ilm_uint id, t_ilm_bool created);

private:
    static void notifyed(ilmObjectType object,
                         t_ilm_uint id,
                         t_ilm_bool created,
                         void *user_data);

private:
    uint32_t screen_id_ = 0;
    uint32_t screen_width_ = 0;
    uint32_t screen_height_ = 0;
};
