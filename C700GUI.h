/*
 *  C700GUI.h
 *  C700
 *
 *  Created by osoumen on 12/10/01.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include <map>
#include "vstgui.h"
#include "C700defines.h"
#include "GUIUtils.h"
#include "EfxAccess.h"

#include "DummyCntl.h"
#include "MyKnob.h"
#include "MySlider.h"
#include "LabelOnOffButton.h"
#include "WaveView.h"
#include "SeparatorLine.h"
#include "MyParamDisplay.h"
#include "MyTextEdit.h"
#include "RecordingSettingsGUI.h"

#include "SPCFile.h"
#include "RawBRRFile.h"
#include "AudioFile.h"
#include "XIFile.h"

class C700GUI : public CViewContainer, public CControlListener
{
public:
	C700GUI(const CRect &size, CFrame *pParent, CBitmap *pBackground = 0);
	~C700GUI();
	
	CControl*	FindControlByTag( long tag );
	void		SetEfxAccess(EfxAccess* efxacc) {
        efxAcc = efxacc;
        if (recordWindow) {
            recordWindow->SetEfxAccess(efxacc);
        }
    }
	
	// CView���
	virtual void	valueChanged(CControl* control);
	bool			attached(CView* view);
	bool			removed(CView* parent);
	CMessageResult	notify(CBaseObject* sender, const char* message);
	
	bool			loadToCurrentProgram( const char *path );
	
	CLASS_METHODS(C700GUI, CViewContainer)
private:
	void			copyFIRParamToClipBoard();
    bool            loadToCurrentProgramFromKhaos();
	bool			loadToCurrentProgramFromBRR( RawBRRFile *file );
	bool			loadToCurrentProgramFromPlistBRR( PlistBRRFile *file );
	bool			loadToCurrentProgramFromAudioFile( AudioFile *file );
	bool			loadToCurrentProgramFromSPC( SPCFile *file );
	bool			getLoadFile( char *path, int maxLen, const char *title );
	bool			getSaveFile( char *path, int maxLen, const char *defaultName, const char *title );
	void			saveFromCurrentProgram(const char *path);
	void			saveFromCurrentProgramToXI(const char *path);
	void			autocalcCurrentProgramSampleRate();
	void			autocalcCurrentProgramBaseKey();
	bool			IsPreemphasisOn();
	
    std::map<long, CControl*> mCntl;
    RecordingSettingsGUI    *recordWindow;
	
	EfxAccess				*efxAcc;
};
