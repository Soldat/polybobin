#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "gl/displaysettings.hpp"
#include "gl/glcanvas.hpp"
#include "map/map.hpp"
#include "settings.hpp"

/**
 * \brief Represents a page inside our Notebook class.
 *  It contains OpenGL canvas in which we draw the map.
 */
class MainFrame;

class Workspace: public wxWindow
{
    public:
        Workspace(wxWindow *notebook, MainFrame& mainFrame, Settings settings, wxString mapPath);
        ~Workspace() = default;

        DisplaySettings GetDisplaySettings();
        void SetDisplaySetting(int setting, bool display);

        GLCanvas& GetGLCanvas() { return *m_glCanvas; }
        Map &GetMap() { return m_map; }
        wxPoint GetMousePositionOnMap();

        void GiveFocusToGLCanvas();

        void SaveMapAsPMS(const wxString& destinationPath);

        void SelectAll();
        void SetBackgroundColors(wxColor backgroundBottomColor, wxColor backgroundTopColor);
        void SetPolygonsTexture(const wxString& textureFilename);

    private:
        GLCanvas* m_glCanvas;
        Map m_map;
};

#endif
