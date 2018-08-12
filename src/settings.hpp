#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

/**
 * \brief Represents settings INI file.
 */
class Settings
{
    public:
        wxString GetSoldatPath() const
        {
            return m_soldatPath;
        }
        void SetSoldatPath(wxString path)
        {
            m_soldatPath = path;
        }

        void LoadSettingsFromFile();
        void SaveSettingsToFile();

    private:
        const wxString GetSettingsPath() const;

        wxString m_soldatPath;

        void LoadDefaultSettings();
};

#endif
