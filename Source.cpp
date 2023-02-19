#include <wx/wx.h>
#include <wx/dir.h>

class FileExplorer : public wxFrame
{
public:
    FileExplorer(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnSelect(wxCommandEvent& event);
    void OnExit(wxCloseEvent& event);

    wxListBox* m_listBox;
    wxStaticText* m_staticText;
};

FileExplorer::FileExplorer(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Create a panel to hold the controls
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a horizontal sizer to layout the controls
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    // Create a vertical sizer to layout the list box and static text
    wxBoxSizer* vbox1 = new wxBoxSizer(wxVERTICAL);

    // Create a static text control to display the selected file
    m_staticText = new wxStaticText(panel, wxID_ANY, wxT("No file selected."));

    // Add the static text control to the vertical sizer
    vbox1->Add(m_staticText, 0, wxALIGN_CENTER | wxALL, 5);

    // Create a list box control to display the files
    m_listBox = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE);

    // Add the list box control to the vertical sizer
    vbox1->Add(m_listBox, 1, wxEXPAND | wxALL, 5);

    // Add the vertical sizer to the horizontal sizer
    hbox->Add(vbox1, 1, wxEXPAND | wxALL, 5);

    // Create a button to select the file
    wxButton* selectButton = new wxButton(panel, wxID_ANY, wxT("Select"));

    // Add the select button to the horizontal sizer
    hbox->Add(selectButton, 0, wxALIGN_CENTER | wxALL, 5);

    // Set the panel's sizer to the horizontal sizer
    panel->SetSizer(hbox);

    // Bind the select button to the OnSelect method
    selectButton->Bind(wxEVT_BUTTON, &FileExplorer::OnSelect, this);

    // Bind the exit event to the OnExit method
    Bind(wxEVT_CLOSE_WINDOW, &FileExplorer::OnExit, this);

    // Set the status bar
    CreateStatusBar();
    SetStatusText(wxT("Ready"));

    // Show the frame
    Centre();
    Show(true);
}

void FileExplorer::OnSelect(wxCommandEvent& event)
{
    wxString wildcard = wxT("*.*");
    wxString defaultDir = wxGetHomeDir();

    wxFileDialog dialog(this, wxT("Select a file"), defaultDir, wxEmptyString, wildcard, wxFD_OPEN);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();
        m_staticText->SetLabel(path);
    }
}

void FileExplorer::OnExit(wxCloseEvent& event)
{
    Close(true);
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    FileExplorer* frame = new FileExplorer(wxT("File Explorer"), wxPoint(50, 50), wxSize(450, 350));
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);