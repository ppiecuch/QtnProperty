/*-------------------------------------------------------------------------
	    Copyright 2013 Damage Control Engineering, LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*-------------------------------------------------------------------------*/
#ifndef QRtMidiIdent_h__
#define QRtMidiIdent_h__

#include <QHash>
#include <QString>
#include "QRtMidiData.h"

struct QRtMidiId_t 
{
    int id;
    const char* name;
};

// This list is not from any offical documentation
// It is probably wrong.
static QRtMidiId_t kMidiIdArray[] =\
{
    {0x01,"Sequential Circuits"},
    {0x02,"Big Briar"},
    {0x03,"Octave / Plateau"},
    {0x04,"Moog"},
    {0x05,"Passport Designs"},
    {0x06,"Lexicon"},
    {0x07,"Kurzweil"},
    {0x08,"Fender"},
    {0x09,"Gulbransen"},
    {0x0A,"Delta Labs"},
    {0x0B,"Sound Comp."},
    {0x0C,"General Electro"},
    {0x0D,"Techmar"},
    {0x0E,"Matthews Research"},
    {0x10,"Oberheim"},
    {0x11,"PAIA"},
    {0x12,"Simmons"},
    {0x13,"DigiDesign"},
    {0x14,"Fairlight"},
    {0x1B,"Peavey"},
    {0x15,"JL Cooper"},
    {0x16,"Lowery"},
    {0x17,"Lin"},
    {0x18,"Emu"},
    {0x20,"Bon Tempi"},
    {0x21,"S.I.E.L."},
    {0x23,"SyntheAxe"},
    {0x24,"Hohner"},
    {0x25,"Crumar"},
    {0x26,"Solton"},
    {0x27,"Jellinghaus Ms"},
    {0x28,"CTS"},
    {0x29,"PPG"},
    {0x2F,"Elka"},
    {0x36,"Cheetah"},
    {0x3E,"Waldorf"},
    {0x40,"Kawai"},
    {0x41,"Roland"},
    {0x42,"Korg"},
    {0x43,"Yamaha"},
    {0x44,"Casio"},
    {0x45,"Akai"},
    {0x40,"Kawai"},
    {0x41,"Roland"},
    {0x42,"Korg"},
    {0x43,"Yamaha"},
    {0x44,"Casio"},
    {0x46,"Kamiya"},
    {0x47,"Akai"},
    {0x48,"Victor"},
    {0x4B,"Fujitsu Limited"},
    {0x4C,"Sony"},
    {0x4E,"Teac"},
    {0x50,"Matsushita"},
    {0x51,"Fostex"},
    {0x52,"Zoom"},
    {0x54,"Matsushita"},
    {0x55,"Suzuki Musical Instruments"},
    {0x56,"Fuji Sound Corporation Ltd."},
    {0x57,"Acoustic Technical Laboratory, Inc."},
    {0x59,"Faith, Inc."},
    {0x5A,"Internet Corporation"},
    {0x5C,"Seekers Co. Ltd."},
    {0x5F,"SD Card Association"},
    {0x0074,"Ta Horng Musical Instrument"},
    {0x0075,"e-Tek Labs (Forte Tech)"},
    {0x0076,"Electro-Voice"},
    {0x0077,"Midisoft Corporation"},
    {0x0078,"QSound Labs"},
    {0x0079,"Westrex"},
    {0x007A,"Nvidia"},
    {0x007B,"ESS Technology"},
    {0x007C,"Media Trix Peripherals"},
    {0x007D,"Brooktree Corp"},
    {0x007E,"Otari Corp"},
    {0x007F,"Key Electronics, Inc."},
    {0x0100,"Shure incorporated"},
    {0x0101,"AuraSound"},
    {0x0102,"Crystal Semiconductor"},
    {0x0103,"Conexant (Rockwell)"},
    {0x0104,"Silicon Graphics"},
    {0x0105,"M-Audio (Midiman)"},
    {0x0106,"PreSonus"},
    {0x0108,"Topaz Enterprises"},
    {0x0109,"Cast Lighting"},
    {0x010A,"Microsoft"},
    {0x010B,"Sonic Foundry"},
    {0x010C,"Line 6 (Fast Forward)"},
    {0x010D,"Beatnik Inc"},
    {0x010E,"Van Koevering Company"},
    {0x010F,"Altech Systems"},
    {0x0110,"S & S Research"},
    {0x0111,"VLSI Technology"},
    {0x0112,"Chromatic Research"},
    {0x0113,"Sapphire"},
    {0x0114,"IDRC"},
    {0x0115,"Justonic Tuning"},
    {0x0116,"TorComp Research Inc."},
    {0x0117,"Newtek Inc."},
    {0x0118,"Sound Sculpture"},
    {0x0119,"Walker Technical"},
    {0x011A,"Digital Harmony (PAVO)"},
    {0x011B,"InVision Interactive"},
    {0x011C,"T-Square Design"},
    {0x011D,"Nemesys Music Technology"},
    {0x011E,"DBX Professional (Harman Intl)"},
    {0x011F,"Syndyne Corporation"},
    {0x0120,"Bitheadz"},
    {0x0121,"Cakewalk Music Software"},
    {0x0122,"Analog Devices"},
    {0x0123,"National Semiconductor"},
    {0x0124,"Boom Theory / Adinolfi Alternative Percussion"},
    {0x0125,"Virtual DSP Corporation"},
    {0x0126,"Antares Systems"},
    {0x0127,"Angel Software"},
    {0x0128,"St Louis Music"},
    {0x0129,"Lyrrus dba G-VOX"},
    {0x012A,"Ashley Audio Inc."},
    {0x012B,"Vari-Lite Inc."},
    {0x012C,"Summit Audio Inc."},
    {0x012D,"Aureal Semiconductor Inc."},
    {0x012E,"SeaSound LLC"},
    {0x012F,"U.S. Robotics"},
    {0x0130,"Aurisis Research"},
    {0x0131,"Nearfield Research"},
    {0x0132,"FM7 Inc"},
    {0x0133,"Swivel Systems"},
    {0x0134,"Hyperactive Audio Systems"},
    {0x0135,"MidiLite (Castle Studios Productions)"},
    {0x0136,"Radikal Technologies"},
    {0x0137,"Roger Linn Design"},
    {0x0138,"TC-Helicon Vocal Technologies"},
    {0x0139,"Event Electronics"},
    {0x013A,"Sonic Network Inc"},
    {0x013B,"Realtime Music Solutions"},
    {0x013C,"Apogee Digital"},
    {0x013D,"Classical Organs, Inc."},
    {0x013E,"Microtools Inc."},
    {0x013F,"Numark Industries"},
    {0x0140,"Frontier Design Group, LLC"},
    {0x0141,"Recordare LLC"},
    {0x0142,"Starr Labs"},
    {0x0143,"Voyager Sound Inc."},
    {0x0144,"Manifold Labs"},
    {0x0145,"Aviom Inc."},
    {0x0146,"Mixmeister Technology"},
    {0x0147,"Notation Software"},
    {0x0148,"Mercurial Communications"},
    {0x0149,"Wave Arts"},
    {0x014A,"Logic Sequencing Devices"},
    {0x014B,"Axess Electronics"},
    {0x014C,"Muse Research"},
    {0x014D,"Open Labs"},
    {0x014E,"Guillemot R&D Inc"},
    {0x014F,"Samson Technologies"},
    {0x0150,"Electronic Theatre Controls"},
    {0x0151,"Blackberry (RIM)"},
    {0x0152,"Mobileer"},
    {0x0153,"Synthogy"},
    {0x0154,"Lynx Studio Technology Inc."},
    {0x0155,"Strymon"},
    {0x0156,"Yost Engineering, Inc."},
    {0x0157,"Brooks & Forsman Designs LLC / DrumLite"},
    {0x0158,"Infinite Response"},
    {0x0159,"Garritan Corp"},
    {0x015A,"Plogue Art et Technologie, Inc"},
    {0x015B,"RJM Music Technology"},
    {0x015C	,"Custom Solutions Software"},
    {0x015D,"Sonarcana LLC"},
    {0x015E,"Centrance"},
    {0x015F,"Kesumo LLC"},
    {0x0160,"Stanton (Gibson)"},
    {0x0161,"Livid Instruments"},
    {0x0162,"First Act / 745 Media"},
    {0x0163,"Pygraphics, Inc."},
    {0x0164,"Panadigm Innovations Ltd"},
    {0x0165,"Avedis Zildjian Co"},
    {0x0166,"Auvital Music Corp"},
    {0x0167,"Inspired Instruments Inc"},
    {0x0168,"Chris Grigg Designs"},
    {0x0169,"Slate Digital LLC"},
    {0x016A,"Mixware"},
    {0x016B,"Social Entropy"},
    {0x016C,"Source Audio LLC"},
    {0x016D,"Ernie Ball / Music Man"},
    {0x016E,"Fishman Transducers"},
    {0x016F,"Custom Audio Electronics"},
    {0x0170,"American Audio/DJ"},
    {0x0171,"Mega Control Systems"},
    {0x0172,"Kilpatrick Audio"},
    {0x0173,"iConnectivity"},
    {0x0174,"Fractal Audio"},
    {0x0175,"NetLogic Microsystems"},
    {0x0176,"Music Computing"},
    {0x0177,"Nektar Technology Inc"},
    {0x0178,"Zenph Sound Innovations"},
    {0x0179,"DJTechTools.com"},
    {0x017A,"Rezonance Labs"},
    {0x017B,"Decibel Eleven"},
    {0x2008,"M-Audio"},
    {0x2029,"Focusrite/Novation"},
    {0x202A,"Samkyung Mechatronics"},
    {0x202B,"Medeli Electronics Co."},
    {0x202C,"Charlie Lab SRL"},
    {0x202D,"Blue Chip Music Technology"},
    {0x202E,"BEE OH Corp"},
    {0x202F,"LG Semicon America"},
    {0x2030,"TESI"},
    {0x2031,"EMAGIC"},
    {0x2032,"Behringer GmbH"},
    {0x2033,"Access Music Electronics"},
    {0x2034,"Synoptic"},
    {0x2035,"Hanmesoft"},
    {0x2036,"Terratec Electronic GmbH"},
    {0x2037,"Proel SpA"},
    {0x2038,"IBK MIDI"},
    {0x2039,"IRCAM"},
    {0x203A,"Propellerhead Software"},
    {0x203B,"Red Sound Systems Ltd"},
    {0x203C,"Elektron ESI AB"},
    {0x203D,"Sintefex Audio"},
    {0x203E,"MAM (Music and More)"},
    {0x203F,"Amsaro GmbH"},
    {0x2040,"CDS Advanced Technology BV"},
    {0x2041,"Touched By Sound GmbH"},
    {0x2042,"DSP Arts"},
    {0x2043,"Phil Rees Music Tech"},
    {0x2044,"Stamer Musikanlagen GmbH"},
    {0x2045,"Musical Muntaner S.A. dba Soundart"},
    {0x2046,"C-Mexx Software"},
    {0x2047,"Klavis Technologies"},
    {0x2048,"Noteheads AB"},
    {0x2049,"Algorithmix"},
    {0x204A,"Skrydstrup R&D"},
    {0x204B,"Professional Audio Company"},
    {0x204C,"NewWave Labs (MadWaves)"},
    {0x204D,"Vermona"},
    {0x204E,"Nokia"},
    {0x204F,"Wave Idea"},
    {0x2050,"Hartmann GmbH"},
    {0x2051,"Lion's Tracs"},
    {0x2052,"Analogue Systems"},
    {0x2053,"Focal-JMlab"},
    {0x2054,"Ringway Electronics (Chang-Zhou) Co Ltd"},
    {0x2055,"Faith Technologies (Digiplug)"},
    {0x2056,"Showworks"},
    {0x2057,"Manikin Electronic"},
    {0x2058,"1 Come Tech"},
    {0x2059,"Phonic Corp"},
    {0x205A,"Dolby Australia (Lake)"},
    {0x205B,"Silansys Technologies"},
    {0x205C,"Winbond Electronics"},
    {0x205D,"Cinetix Medien und Interface GmbH"},
    {0x205E,"A&G Soluzioni Digitali"},
    {0x205F,"Sequentix Music Systems"},
    {0x2060,"Oram Pro Audio"},
    {0x2061,"Be4 Ltd"},
    {0x2062,"Infection Music"},
    {0x2063,"Central Music Co. (CME)"},
    {0x2064,"genoQs Machines GmbH"},
    {0x2065,"Medialon"},
    {0x2066,"Waves Audio Ltd"},
    {0x2067,"Jerash Labs"},
    {0x2068,"Da Fact"},
    {0x2069,"Elby Designs"},
    {0x206A,"Spectral Audio"},
    {0x206B,"Arturia"},
    {0x206C,"Vixid"},
    {0x206D,"C-Thru Music"},
    {0x206E,"Ya Horng Electronic Co LTD"},
    {0x206F,"SM Pro Audio"},
    {0x2070,"OTO MACHINES"},
    {0x2071,"ELZAB S.A., G LAB"},
    {0x2072,"Blackstar Amplification Ltd"},
    {0x2073,"M3i Technologies GmbH"},
    {0x2074,"Gemalto (from Xiring)"},
    {0x2075,"Prostage SL"},
    {0x2076,"Teenage Engineering"},
    {0x2077,"Tobias Erichsen Consulting"},
    {0x2078,"Nixer Ltd"},
    {0x2079,"Hanpin Electron Co Ltd"},
    {0x207A,"MIDI-hardware R.Sowa"},
    {0x207B,"Beyond Music Industrial Ltd"},
    {0x207C,"Kiss Box B.V."},
    {0x207D,"Misa Digital Technologies Ltd"},
    {0x207E,"AI Musics Technology Inc"},
    {0x207F,"Serato Inc LP"},
    {0x2100,"Limex Music Handles GmbH"},
    {0x2101,"Kyodday/Tokai"},
    {0x2102,"Mutable Instruments"},
    {0x2103,"PreSonus Software Ltd"},
    {0x2104,"Xiring"},
    {0x2105,"Fairlight Instruments Pty Ltd"},
    {0x2106,"Musicom Lab"},
    {0x2107,"VacoLoco"},
    {0x2108,"RWA (Hong Kong) Limited"},
    {0x2109,"Native Instruments"},
    {0x210A,"Naonext"},
    {0x210B,"MFB"},
    {0x210C,"Teknel Research"},
    {0x210D,"Ploytec GmbH"},
    {0x4000,"Crimson Technology Inc."},
    {0x4001,"Softbank Mobile Corp"},
    {0x4003,"D&M Holdings Inc."}};


typedef QHash<int,QByteArray> QRtMidiIdHash_t;

class QRtMidiIdsHash : public QRtMidiIdHash_t
{

public:

    QRtMidiIdsHash()
    {
        int len = sizeof(kMidiIdArray)/sizeof(QRtMidiId_t);
        for (int idx = 0; idx < len ; idx++)
        {
            this->insert(kMidiIdArray[idx].id,kMidiIdArray[idx].name);
        }
    }

};

static QRtMidiIdsHash MidiNameToIds;


struct QRtMidiDevIdent
{
    QRtMidiDevIdent();

    
    QRtMidiDevIdent(const QRtMidiData &data);

    /*!
    	Initialize device identity from the given identify response data
    */
    void            fromIdentData( const QRtMidiData & data );
    
    /*!
    	Clear data
    */
    void            clear();

    /*!
    	Returns a QString with formatted identity 
    */
    QString         toString();
    
    /*!
    	Returns true if the structure is empty
    */
    bool            isEmpty();
    
    /*!
    	Returns the MIDI manufacture name
    */
    QString         getManufactureName();
    
    /*!
    	Returns the 2 byte produce ID
    */
    quint16         getProductId();
    
    /*!
    	Return the product family byte by truncating the upper 7 bits
    */
    quint8          getFamilyByte();
    
    /*!
    	Return the product byte code by truncating the upper 7 bits
    */
    quint8          getProductByte();
    
    // The short id is the lower byte of Family and the lower byte of the product id.
    QString         getShortId();


    // Return the two byte family id
    unsigned short  getFamilyId();
    
    QRtMidiData     Manufacture;
    QString         FwVersion;
    unsigned char   SyxCh;
    QRtMidiData     Family;
    QRtMidiData     Product;
    QRtMidiData     SOXHdr;
    int             MfjIdSize;
};

typedef QList<QRtMidiDevIdent> QRtMidiIdentList_t;

#endif // QRtMidiIdent_h__
