#include "glmanager.hpp"
#include "glfunctions.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "../constants.hpp"

GLManager::GLManager(Map map) : m_glOutlineScenerySelection(PMSColor(129, 23, 23, 255),
                                                            PMSColor(176, 31, 31, 255),
                                                            PMSColor(255, 44, 44, 255)),
                                m_glOutlineSceneryWireframe(PMSColor(129, 129, 129, 255),
                                                            PMSColor(168, 168, 168, 255),
                                                            PMSColor(210, 210, 210, 255))
{
    m_glReady = false;

    m_map = map;
}

void GLManager::Init()
{
    m_glReady = InitGLPointers();

    if (!m_glReady)
    {
        throw (wxString) wxT("Could not retrieve OpenGL functions' addresses.");
    }
}

bool GLManager::IsGLReady()
{
    return m_glReady;
}

void GLManager::Render(Camera camera, wxSize canvasSize, DisplaySettings displaySettings,
                       Selection selectedPolygons, Selection selectedScenery)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 transform = glm::ortho(camera.GetX(),
                                     camera.GetX() + camera.GetWidth(canvasSize),
                                     camera.GetY() + camera.GetHeight(canvasSize),
                                     camera.GetY());

    if (displaySettings.ShouldDisplay(DISPLAY_BACKGROUND))
    {
        m_glBackground.Render(transform);
    }

    if (displaySettings.ShouldDisplay(DISPLAY_SCENERY))
    {
        m_glScenery.Render(transform, lBEHIND_ALL);
        m_glScenery.Render(transform, lBEHIND_MAP);
    }

    if (displaySettings.ShouldDisplay(DISPLAY_POLYGONS))
    {
        m_glPolygons.Render(transform);
    }

    if (displaySettings.ShouldDisplay(DISPLAY_SCENERY))
    {
        m_glScenery.Render(transform, lBEHIND_NONE);
    }

    if (displaySettings.ShouldDisplay(DISPLAY_SPAWNPOINTS))
    {
        m_glSpawnPoints.Render(transform);
    }

    if (displaySettings.ShouldDisplay(DISPLAY_WIREFRAME))
    {
        m_glOutlinePolygons.RenderAll(transform);
        m_glOutlineSceneryWireframe.RenderAll(transform);
    }

    wxVector<unsigned int> selectedPolygonsIds = selectedPolygons.GetSelectedIds();
    if (selectedPolygonsIds.size() > 0)
    {
        m_glOutlinePolygons.RenderSelected(transform, selectedPolygonsIds);
        m_glSelectionPolygons.RenderSelected(transform, selectedPolygonsIds);
    }

    wxVector<unsigned int> selectedSceneryIds = selectedScenery.GetSelectedIds();
    if (selectedSceneryIds.size() > 0)
    {
        m_glOutlineScenerySelection.RenderSelected(transform, selectedSceneryIds);
    }
}

void GLManager::SetupShaders()
{
    m_glBackground.SetupShaderProgram();
    m_glPolygons.SetupShaderProgram();
    m_glScenery.SetupShaderProgram();
    m_glSpawnPoints.SetupShaderProgram();

    m_glOutlinePolygons.SetupShaderProgram();
    m_glOutlineScenerySelection.SetupShaderProgram();
    m_glOutlineSceneryWireframe.SetupShaderProgram();

    m_glSelectionPolygons.SetupShaderProgram();
}

void GLManager::SetupTextures()
{
    m_glPolygons.SetupTexture(PATH_SOLDAT + "textures/" + m_map.GetTextureName());
    m_glScenery.SetupTextures(m_map.GetSceneryTypes());
    m_glSpawnPoints.SetupTextures();

    m_glSelectionPolygons.SetupTexture();
}

void GLManager::SetupVertices()
{
    m_glBackground.SetupVAO(m_map.GetBackgroundTopColor(),
                            m_map.GetBackgroundBottomColor(),
                            m_map.GetBoundaries());
    m_glPolygons.SetupVAO(m_map.GetPolygons());
    m_glScenery.SetupVAO(m_map.GetSceneryInstances());
    m_glSpawnPoints.SetupVAO(m_map.GetSpawnPoints());

    m_glOutlinePolygons.SetupVAO(m_map.GetPolygons());
    m_glOutlineScenerySelection.SetupVAO(m_map.GetSceneryInstances());
    m_glOutlineSceneryWireframe.SetupVAO(m_map.GetSceneryInstances());

    m_glSelectionPolygons.SetupVAO(m_map.GetPolygons());
}
