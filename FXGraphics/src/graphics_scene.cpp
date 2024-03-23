#include "graphics_scene.h"

namespace FX {

    GraphicsScene::GraphicsScene()
    {
        m_pDiverter = new GraphicsDiverter(this);

        m_pDiverter->m_pEntityVGroup = &m_entityVGroup;
        m_pDiverter->m_pEntityVIGroup = &m_entityVIGroup;
        m_pDiverter->m_pEntityVNGroup = &m_entityVNGroup;
        m_pDiverter->m_pEntityVNIGroup = &m_entityVNIGroup;
    }

    GraphicsScene::~GraphicsScene()
    {
        delete m_pDiverter;
    }

    void GraphicsScene::draw()
    {
        m_entityVGroup.ensure();
        m_entityVIGroup.ensure();
        m_entityVNGroup.ensure();
        m_entityVNIGroup.ensure();

        // TODO
    }

} // namespace FX
