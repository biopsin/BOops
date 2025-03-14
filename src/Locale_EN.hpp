#ifndef BOOPS_LOCALE
#define BOOPS_LOCALE

// Plugin core
#define BOOPS_LABEL_JACK_OFF "Msg: Jack transport off or halted. Plugin halted."
#define BOOPS_LABEL_CANT_OPEN_SAMPLE "Msg: Can't open sample file."
#define BOOPS_LABEL_MSG "Msg:"
#define BOOPS_LABEL_SELECT_CUT "Select & cut"
#define BOOPS_LABEL_SELECT_COPY "Select & copy"
#define BOOPS_LABEL_SELECT_XFLIP "Select & X flip"
#define BOOPS_LABEL_SELECT_YFLIP "Select & Y flip"
#define BOOPS_LABEL_PASTE "Paste"
#define BOOPS_LABEL_RESET "Reset"
#define BOOPS_LABEL_UNDO "Undo"
#define BOOPS_LABEL_REDO "Redo"
#define BOOPS_LABEL_LOAD "Load"
#define BOOPS_LABEL_SAVE "Save"
#define BOOPS_LABEL_MIDI_PAGE "MIDI control pattern"
#define BOOPS_LABEL_MIDI_STATUS "MIDI status"
#define BOOPS_LABEL_NONE "None"
#define BOOPS_LABEL_NOTE_ON "Note on"
#define BOOPS_LABEL_NOTE_OFF "Note off"
#define BOOPS_LABEL_CC "Control change"
#define BOOPS_LABEL_CHANNEL "Channel"
#define BOOPS_LABEL_ALL "All"
#define BOOPS_LABEL_NOTE "Note"
#define BOOPS_LABEL_VALUE "Value"
#define BOOPS_LABEL_LEARN "Learn"
#define BOOPS_LABEL_CANCEL "Cancel"
#define BOOPS_LABEL_OK "OK"
#define BOOPS_LABEL_STREAM "Stream"
#define BOOPS_LABEL_SAMPLE "Sample"
#define BOOPS_LABEL_AMP "Amp"
#define BOOPS_LABEL_AUTOPLAY "Autoplay"
#define BOOPS_LABEL_HOST_CONTROLLED "Host-controlled"
#define BOOPS_LABEL_MIDI_CONTROLLED "MIDI-controlled"
#define BOOPS_LABEL_RESTART "Restart"
#define BOOPS_LABEL_RESTART_SYNC "Restart & sync"
#define BOOPS_LABEL_CONTINUE "Continue"
#define BOOPS_LABEL_SOURCE "Source"
#define BOOPS_LABEL_MODE "Mode"
#define BOOPS_LABEL_BPM "bpm"
#define BOOPS_LABEL_BPBAR "bpBar"
#define BOOPS_LABEL_ADJUST_POSITION "Adjust position"
#define BOOPS_LABEL_PATTERN_SIZE "Pattern size"
#define BOOPS_LABEL_PLAY "Play"
#define BOOPS_LABEL_BYPASS "Bypass"
#define BOOPS_LABEL_STOP "Stop"
#define BOOPS_LABEL_SECONDS "Seconds"
#define BOOPS_LABEL_BEATS "Beats"
#define BOOPS_LABEL_BARS "Bars"
#define BOOPS_LABEL_STEPS "Steps"
#define BOOPS_LABEL_SELECT_KEYS "Progression control: Select keys"
#define BOOPS_LABEL_PROGRESSION_KEYS_TOOLTIP \
        "This option is intended for the control of the pattern progression (white vertical bar).\n" \
        "For MIDI-controlled pattern selection click on the piano keys symbol of the respective pattern tab. " \
        "For direct effect control click on the symbol left to the respective pattern row."
#define BOOPS_LABEL_HELP "Help"
#define BOOPS_LABEL_TUTORIAL "Introduction"
#define BOOPS_LABEL_ROW "Row"
#define BOOPS_LABEL_STEP "Step"
#define BOOPS_LABEL_SIZE "Size"
#define BOOPS_LABEL_CLICK_TO_EDIT "Click to edit"
#define BOOPS_LABEL_ALL_FILES "All files"
#define BOOPS_LABEL_AUDIO_FILES "Audio files"
#define BOOPS_LABEL_OPEN "Open"
#define BOOPS_LABEL_PLAY_AS_LOOP "Play selection as loop"
#define BOOPS_LABEL_FILE "File"
#define BOOPS_LABEL_SELECTION_START "Selection start"
#define BOOPS_LABEL_SELECTION_END "Selection end"
#define BOOPS_LABEL_FRAMES "frames"
#define BOOPS_LABEL_NO_FILE_SELECTED "No audio file selected"
#define BOOPS_LABEL_FILE_EXISTS "File already exists. Overwrite?"
#define BOOPS_LABEL_NEW_FOLDER "Create new folder:"
#define BOOPS_LABEL_CANT_CREATE_NEW_FOLDER "Error: Can't create new folder"
#define BOOPS_LABEL_PATTERN_FILES "Pattern files"
#define BOOPS_LABEL_ADD "Add"
#define BOOPS_LABEL_DELETE "Delete"
#define BOOPS_LABEL_MOVE_FORWARD "Move forward"
#define BOOPS_LABEL_MOVE_BACKWARD "Move backward"
#define BOOPS_LABEL_MOVE_UP "Move up"
#define BOOPS_LABEL_MOVE_DOWN "Move down"
#define BOOPS_LABEL_MIDI "MIDI"
#define BOOPS_LABEL_SHAPE_PATTERN "Shape / pattern"
#define BOOPS_LABEL_MENU "Menu"
#define BOOPS_LABEL_PROBABILITY "Probability"
#define BOOPS_LABEL_PROBABILITY_TOOLTIP \
        "Probability\n" \
        " \n" \
        "Set the probability for\n" \
        "pads to be played or not.\n" \
        "This will be applied\n" \
        "when you draw new pads."
#define BOOPS_LABEL_MIX "Mix"
#define BOOPS_LABEL_MIX_TOOLTIP \
        "Mix\n" \
        " \n" \
        "Dry / wet mixing value\n" \
        "of an effect pad.\n" \
        "This will be applied\n" \
        "when you draw new pads."
#define BOOPS_LABEL_GETTING_STARTED "Getting started\n" \
        " \n" \
        "1) Add an effect by clicking on the [+] symbol below \"Fx\".\n" \
        "2) Click on the menu symbol left to the effect name to change the effect\n" \
        "3) Set a pattern right to the effect name to define the timepoint(s) to apply the effect on the incoming audio signal.\n" \
        "4) Continue with point 1 to add another effects. Change the order of the effects by dragging the effect or by clicking on the respective symbol."
#define BOOPS_LABEL_PAN "Pan"
#define BOOPS_LABEL_ADSR_A "A"
#define BOOPS_LABEL_ADSR_D "D"
#define BOOPS_LABEL_ADSR_S "S"
#define BOOPS_LABEL_ADSR_R "R"

// TODO Fx modules
#define BOOPS_LABEL_BALANCE "Balance"
#define BOOPS_LABEL_LIMIT "Limit"
#define BOOPS_LABEL_BITS "Bits"
#define BOOPS_LABEL_NR_CHOPS "Nr chops"
#define BOOPS_LABEL_SMOOTH "Smooth"
#define BOOPS_LABEL_CHOPS "Chops"
#define BOOPS_LABEL_RANDOM "Random"
#define BOOPS_LABEL_REACH "Reach"
#define BOOPS_LABEL_LEVEL "Level"
#define BOOPS_LABEL_RATE "Rate"
#define BOOPS_LABEL_MAX_SIZE "Max. size"
#define BOOPS_LABEL_DISTRIBUTION "Distribution"
#define BOOPS_LABEL_DB "db"
#define BOOPS_LABEL_RESOLUTION "Resolution"
#define BOOPS_LABEL_RANGE "Range"
#define BOOPS_LABEL_DELAY "Delay"
#define BOOPS_LABEL_FEEDBACK "Feedback"
#define BOOPS_LABEL_DRIVE "Drive"
#define BOOPS_LABEL_HARDCLIP "Hardclip"
#define BOOPS_LABEL_SOFTCLIP "Softclip"
#define BOOPS_LABEL_FOLDBACK "Foldback"
#define BOOPS_LABEL_OVERDRIVE "Overdrive"
#define BOOPS_LABEL_FUZZ "Fuzz"
#define BOOPS_LABEL_HIGHPASS "High pass"
#define BOOPS_LABEL_LOWPASS "Low pass"
#define BOOPS_LABEL_ROLL_OFF "Roll off"
#define BOOPS_LABEL_HZ "Hz"
#define BOOPS_LABEL_MINUS_DB_PER_OCTAVE "-db/o"
#define BOOPS_LABEL_AMOUNT "Amount"
#define BOOPS_LABEL_MODULATION "Modulation"
#define BOOPS_LABEL_STEREO_PHASE "Stereo phase"
#define BOOPS_LABEL_MS "ms"
#define BOOPS_LABEL_PITCH "Pitch"
#define BOOPS_LABEL_OFFSET "Offset"
#define BOOPS_LABEL_SEMI "semi"
#define BOOPS_LABEL_LOW_FREQ "Low freq."
#define BOOPS_LABEL_HIGH_FREQ "High freq."
#define BOOPS_LABEL_RATIO "Ratio"
#define BOOPS_LABEL_FREQUENCY "Frequency"
#define BOOPS_LABEL_WAVEFORM "Waveform"
#define BOOPS_LABEL_DEPTH "Depth"
#define BOOPS_LABEL_SELECT "Select"
#define BOOPS_LABEL_POINT_NODE "Point node"
#define BOOPS_LABEL_AUTO_BEZIER_NODE "Auto Bezier node"
#define BOOPS_LABEL_SYMMETRIC_BEZIER_NODE "Symmetric Bezier node"
#define BOOPS_LABEL_ASYMMETRIC_BEZIER_NODE "Asymmetric Bezier node"
#define BOOPS_LABEL_CUT "Cut"
#define BOOPS_LABEL_COPY "Copy"
#define BOOPS_LABEL_SHOW_GRID "Show grid"
#define BOOPS_LABEL_SNAP_TO_GRID "Snap to grid"
#define BOOPS_LABEL_STUTTERS "Stutters"
#define BOOPS_LABEL_NONE "None"
#define BOOPS_LABEL_SLOT "Slot"
#define BOOPS_LABEL_SPEED "Speed"
#define BOOPS_LABEL_DECELERATION "Deceleration"
#define BOOPS_LABEL_CENTER "Center"
#define BOOPS_LABEL_WIDTH "Width"
#define BOOPS_LABEL_WOW "Wow"
#define BOOPS_LABEL_FLUTTER "Flutter"
#define BOOPS_LABEL_ROOMSIZE "Room size"
#define BOOPS_LABEL_REPLACE "Replace"
#define BOOPS_LABEL_BRIGHTNESS "Brightness"
#define BOOPS_LABEL_DETUNE "Detune"
#define BOOPS_LABEL_BIGNESS "Bigness"
#define BOOPS_LABEL_FILTER "Filter"
#define BOOPS_LABEL_DAMP "Damp"
#define BOOPS_LABEL_ALLPASS "Allpass"
#define BOOPS_LABEL_GAIN "Gain"
#define BOOPS_LABEL_FIRST "First"
#define BOOPS_LABEL_LAST "Last"
#define BOOPS_LABEL_NUKE "Nuke"
#define BOOPS_LABEL_SPIN "Spin"
#define BOOPS_LABEL_SUB "Sub"
#define BOOPS_LABEL_BOOM "Boom"
#define BOOPS_LABEL_WARMTH "Warmth"
#define BOOPS_LABEL_CLARITY "Clarity"
#define BOOPS_LABEL_PRESENCE "Presence"
#define BOOPS_LABEL_AIR "Air"
#define BOOPS_LABEL_SHAPE "Shape"

#endif
