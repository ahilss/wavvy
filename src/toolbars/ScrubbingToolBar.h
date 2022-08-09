/**********************************************************************

 Audacity: A Digital Audio Editor


 ScrubbingToolbar.h
 
 Paul Licameli

 **********************************************************************/

#ifndef __WAVVY_SCRUBBING_TOOLBAR__
#define __WAVVY_SCRUBBING_TOOLBAR__



#include <wx/defs.h>

#include "ToolBar.h"

class WavvyProject;

class wxCommandEvent;
class wxDC;
class wxImage;
class wxWindow;

class AButton;

enum {
   STBScrubID,
   STBSeekID,
   STBRulerID,

   STBNumButtons,
   STBFirstButton = STBScrubID
};

class ScrubbingToolBar final : public ToolBar {

public:

   ScrubbingToolBar( WavvyProject &project );
   virtual ~ScrubbingToolBar();

   static ScrubbingToolBar &Get( WavvyProject &project );
   static const ScrubbingToolBar &Get( const WavvyProject &project );

   void Create(wxWindow *parent) override;

   void OnButton(wxCommandEvent & event);

   void Populate() override;
   void Repaint(wxDC * WXUNUSED(dc)) override {};
   void EnableDisableButtons() override;
   void UpdatePrefs() override;

   void RegenerateTooltips() override;

private:

   static AButton *AddButton(
      ScrubbingToolBar *pBar,
      teBmps eEnabledUp, teBmps eEnabledDown, teBmps eDisabled,
      int id, const TranslatableString &label, bool toggle = false);

   void MakeButtons();

   AButton *mButtons[STBNumButtons];

   wxImage *upImage;
   wxImage *downImage;
   wxImage *hiliteImage;

   void OnIdle( wxIdleEvent &evt );

public:

   DECLARE_CLASS(ScrubbingToolBar)
   DECLARE_EVENT_TABLE()

private:
   void DoRegenerateTooltips( bool force );

   bool mLastScrub{ false };
   bool mLastSeek{ false };
   bool mLastRuler{ false };
};

#endif