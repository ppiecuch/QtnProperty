#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <QApplication>
#include <QString>

/* Don't translate any string defined in this header */

#define LITERAL(s) #s
#define STRINGIFY(s) LITERAL(s)
const QString PGM_VERSION(STRINGIFY(VERSION));

const QString BLD_DATE(__DATE__);
const QString BLD_TIME(__TIME__);
#if defined(Q_CC_GNU) || defined(Q_CC_GCCE)
const QString CMP_VERSION(__VERSION__);
#elif defined(Q_CC_MSVC)
const QString CMP_VERSION(QString::number(_MSC_VER/100.0,'g',2));
#else
const QString CMP_VERSION(QString());
#endif

const QString QSTR_WINDOW("Window");
const QString QSTR_GEOMETRY("Geometry");
const QString QSTR_STATE("State");
const QString QSTR_PREFERENCES("Preferences");
const QString QSTR_CHANNEL("Channel");
const QString QSTR_VELOCITY("Velocity");
const QString QSTR_BASEOCTAVE("BaseOctave");
const QString QSTR_TRANSPOSE("Transpose");
const QString QSTR_NUMOCTAVES("NumOctaves");
const QString QSTR_INSTRUMENTSDEFINITION("InstrumentsDefinition");
const QString QSTR_INSTRUMENTNAME("InstrumentName");
const QString QSTR_CONNECTIONS("Connections");
const QString QSTR_INENABLED("InEnabled");
const QString QSTR_THRUENABLED("ThruEnabled");
const QString QSTR_OMNIENABLED("OmniEnabled");
const QString QSTR_INPORT("InPort");
const QString QSTR_OUTPORT("OutPort");
const QString QSTR_KEYBOARD("Keyboard");
const QString QSTR_MAPFILE("MapFile");
const QString QSTR_RAWMAPFILE("RawMapFile");
const QString QSTR_DEFAULT("default");
const QString QSTR_CONTROLLERS("Controllers");
const QString QSTR_INSTRUMENT("Instrument");
const QString QSTR_BANK("Bank");
const QString QSTR_PROGRAM("Program");
const QString QSTR_CONTROLLER("Controller");
const QString QSTR_GRABKB("GrabKeyboard");
const QString QSTR_STYLEDKNOBS("StyledKnobs");
const QString QSTR_ALWAYSONTOP("AlwaysOnTop");
const QString QSTR_SHOWNOTENAMES("ShowNoteNames");
const QString QSTR_SHOWSTATUSBAR("ShowStatusBar");
const QString QSTR_RAWKEYBOARDMODE("RawKeyboardMode");
const QString QSTR_EXTRACONTROLLERS("ExtraControllers");
const QString QSTR_EXTRACTLPREFIX("ExtraCtl_");
const QString QSTR_VMPK("VMPK");
const QString QSTR_VMPKINPUT("VMPK Input");
const QString QSTR_VMPKOUTPUT("VMPK Output");
const QString QSTR_DEFAULTINS("gmgsxg.ins");
const QString QSTR_DRUMSCHANNEL("DrumsChannel");
const QString QSTR_SHORTCUTS("Shortcuts");
const QString QSTR_LANGUAGE("Language");
const QString QSTR_VELOCITYCOLOR("VelocityColor");
const QString QSTR_NETWORKPORT("NetworkPort");
const QString QSTR_NETWORKIFACE("NetworkInterface");
const QString QSTR_ENFORCECHANSTATE("EnforceChannelState");
const QString QSTR_ENABLEKEYBOARDINPUT("EnableKeyboardInput");
const QString QSTR_ENABLEMOUSEINPUT("EnableMouseInput");
const QString QSTR_ENABLETOUCHINPUT("EnableTouchInput");

const QString QSTR_MIDIDRIVER("MIDIDriver");
const QString QSTR_DRIVERNAMEALSA("ALSA Sequencer");
const QString QSTR_DRIVERNAMEJACK("Jack MIDI");
const QString QSTR_DRIVERNAMEMACOSX("Mac OSX CoreMIDI");
const QString QSTR_DRIVERNAMEIRIX("SGI Irix MD");
const QString QSTR_DRIVERNAMEWINMM("Windows MM");
const QString QSTR_DRIVERNAMENET("Network UDP (IpMIDI)");
const QString QSTR_MULTICAST_ADDRESS("225.0.0.37");
const QString QSTR_PALETTEPREFIX("Palette_");
const QString QSTR_CURRENTPALETTE("CurrentPalette");
const QString QSTR_SHOWCOLORSCALE("ShowColorScale");

#if defined(Q_OS_LINUX)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEALSA);
#elif defined(Q_OS_MAC)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEMACOSX);
#elif defined(Q_OS_IRIX)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEIRIX);
#elif defined(Q_OS_WIN)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEWINMM);
#else
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMENET);
#endif

const char MIDICTLNUMBER[] = "MIDICTLNUMBER\0";
const char MIDICTLONVALUE[] = "MIDICTLONVAL\0";
const char MIDICTLOFFVALUE[] = "MIDICTLOFFVAL\0";
const char SYSEXFILENAME[] = "SYSEXFILENAME\0";
const char SYSEXFILEDATA[] = "SYSEXFILEDATA\0";

const int MIDIGMDRUMSCHANNEL = 9;
const int MIDICHANNELS = 16;
const int MIDIVELOCITY = 100;
const int MIDIPAN = 64;
const int MIDIVOLUME = 100;
const int MIDIEXPRESSION = 127;

const int NETWORKPORTNUMBER = 21928;

const int PAL_SINGLE = 0;
const int PAL_DOUBLE = 1;
const int PAL_CHANNELS = 2;
const int PAL_SCALE = 3;

#endif /*CONSTANTS_H_*/
