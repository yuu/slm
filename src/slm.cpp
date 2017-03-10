#include "slm.h"

static const uint32_t camera = 20000;
static const uint32_t remo   = 20001;
static const uint32_t black  = 20002;
static const uint32_t map    = 2147483649;

void slm::start()
{
    ilmErrorTypes err = ilm_init();
    if (ILM_SUCCESS != err) {
        qDebug("[%s] Failed ilm init", Q_FUNC_INFO);
        exit(EXIT_FAILURE);
    }

    ilm_getScreenResolution(screen_id_, &screen_width_, &screen_height_);
    qDebug("screen property");
    qDebug("    id=%d, w=%d, h=%d", screen_id_, screen_width_, screen_height_);

    create_layer(camera);
    create_layer(remo);
    create_layer(black);
    create_layer(map);

    t_ilm_layer renderOrder[] = {camera, remo, black, map};
    ilm_displaySetRenderOrder(screen_id_, renderOrder, 1);
    ilm_commitChanges();

    ilm_registerNotification(slm::notifyed, this);
}

void slm::notifyed(ilmObjectType object,
                   t_ilm_uint id,
                   t_ilm_bool created,
                   void *user_data)
{
    qDebug("[%s] id=%d created?=%d", Q_FUNC_INFO, id, created);

    auto my = static_cast<slm*>(user_data);
    if (!my)
        return;

    switch (object) {
    case ILM_SURFACE:
        emit my->notify_surface(id, created);
        break;
    case ILM_LAYER:
        emit my->notify_layer(id, created);
        break;
    }
}

void slm::create_layer(t_ilm_layer id)
{
    ilm_layerCreateWithDimension(&id,
                                 screen_width_,
                                 screen_height_);
    ilm_commitChanges();
    ilm_layerSetSourceRectangle(id,
                                0,
                                0,
                                screen_width_,
                                screen_height_);
    ilm_layerSetDestinationRectangle(id,
                                     0,
                                     0,
                                     screen_width_,
                                     screen_height_);
    ilm_commitChanges();
    ilm_layerSetOpacity(id, 1.0);
    ilm_layerSetVisibility(id, ILM_TRUE);
    ilm_commitChanges();
}

void slm::change_layout(t_ilm_uint id, t_ilm_bool created)
{
    qDebug("[%s]", Q_FUNC_INFO);
    qDebug("    id=%d, created?=%d", id, created);

    switch (id) {
    case camera:
    {
        ilm_surfaceSetSourceRectangle(camera, 0, 0, 640, 480);
        ilm_surfaceSetDestinationRectangle(camera, 695, 300, 535, 485);

        t_ilm_surface order[] = {camera};
        ilm_layerSetRenderOrder(camera, order, 1);
        ilm_commitChanges();
        break;
    }
    case remo:
    {
        ilm_surfaceSetVisibility(remo, true);

        t_ilm_surface order[] = {remo};
        ilm_layerSetRenderOrder(remo, order, 1);
        ilm_commitChanges();
        break;
    }
    case black:
    {
        ilm_surfaceSetVisibility(black, true);

        t_ilm_surface order[] = {black};
        ilm_layerSetRenderOrder(black, order, 1);
        ilm_commitChanges();
        break;
    }
    case map:
    {
        ilm_surfaceSetSourceRectangle(map, 0, 0, 384, 368);
        ilm_surfaceSetDestinationRectangle(map, 695, 300, 535, 485);
        ilm_surfaceSetVisibility(map, true);

        t_ilm_surface order[] = {map};
        ilm_layerSetRenderOrder(map, order, 1);
        ilm_commitChanges();
        break;
    }
    }
}
