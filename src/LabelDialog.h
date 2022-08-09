/**********************************************************************

  Audacity: A Digital Audio Editor

  LabelDialog.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVVY_LABELDIALOG__
#define __WAVVY_LABELDIALOG__

#include <vector>
#include <wx/defs.h>

#include "widgets/wxPanelWrapper.h" // to inherit
#include "wavvy/ComponentInterface.h" // member variable

class wxArrayString;
class wxGridEvent;
class WavvyProject;
class ChoiceEditor;
class Grid;
class NumericEditor;
class TrackList;
class RowData;
class EmptyLabelRenderer;
class LabelTrack;
class ViewInfo;
class ShuttleGui;

typedef std::vector<RowData> RowDataArray;

class LabelDialog final : public wxDialogWrapper
{
 public:

   LabelDialog(wxWindow *parent,
               WavvyProject &project,
               TrackList *tracks,

               // if NULL edit all tracks, else this one only:
               LabelTrack *selectedTrack,

               // This is nonnegative only if selectedTrack is not NULL
               // and is the unique label to edit
               int index,

               ViewInfo &viewinfo,
               double rate,
               const NumericFormatSymbol & format,
               const NumericFormatSymbol &freqFormat);
   ~LabelDialog();

    bool Show(bool show = true) override;

 private:

   void Populate();
   void PopulateOrExchange( ShuttleGui & S );
   void PopulateLabels();
   virtual void OnHelp(wxCommandEvent & event);
   virtual wxString GetHelpPageName() {return "Labels_Editor";};

   bool TransferDataToWindow() override;
   bool TransferDataFromWindow() override;
   bool Validate() override;
   void FindAllLabels();
   void AddLabels(const LabelTrack *t);
   void FindInitialRow();
   wxString TrackName(int & index, const wxString &dflt = _("Label Track"));

   void OnUpdate(wxCommandEvent &event);
   void OnFreqUpdate(wxCommandEvent &event);
   void OnInsert(wxCommandEvent &event);
   void OnRemove(wxCommandEvent &event);
   void OnImport(wxCommandEvent &event);
   void OnExport(wxCommandEvent &event);
   void OnSelectCell(wxGridEvent &event);
   void OnCellChange(wxGridEvent &event);
   void OnChangeTrack(wxGridEvent &event, int row, RowData *rd);
   void OnChangeLabel(wxGridEvent &event, int row, RowData *rd);
   void OnChangeStime(wxGridEvent &event, int row, RowData *rd);
   void OnChangeEtime(wxGridEvent &event, int row, RowData *rd);
   void OnChangeLfreq(wxGridEvent &event, int row, RowData *rd);
   void OnChangeHfreq(wxGridEvent &event, int row, RowData *rd);
   void OnOK(wxCommandEvent &event);
   void OnCancel(wxCommandEvent &event);

   void ReadSize();
   void WriteSize();

 private:

   WavvyProject &mProject;

   Grid *mGrid;
   ChoiceEditor *mChoiceEditor;
   NumericEditor *mTimeEditor;
   NumericEditor *mFrequencyEditor;

   RowDataArray mData;

   TrackList *mTracks;
   LabelTrack *mSelectedTrack {};
   int mIndex { -1 };
   ViewInfo *mViewInfo;
   wxArrayString mTrackNames;
   double mRate;
   NumericFormatSymbol mFormat, mFreqFormat;

   int mInitialRow;

   DECLARE_EVENT_TABLE()
};

#endif