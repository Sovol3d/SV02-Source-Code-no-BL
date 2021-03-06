#ifndef	RTS_H
#define	RTS_H

#include "string.h"
#include <arduino.h>

/*********************************/
#define FHONE   (0x5A)
#define FHTWO   (0xA5)
#define TEXTBYTELEN     18
#define MaxFileNumber   20

#define	CEIconGrap      12
#define	FileNum	MaxFileNumber
#define	FileNameLen	TEXTBYTELEN
#define	RTS_UPDATE_INTERVAL 2000
#define	RTS_UPDATE_VALUE    (2*RTS_UPDATE_INTERVAL)

#define SizeofDatabuf		26

/*************Register and Variable addr*****************/
#define	RegAddr_W	0x80
#define	RegAddr_R	0x81
#define	VarAddr_W	0x82
#define	VarAddr_R	0x83
#define	ExchangePageBase    ((unsigned long)0x5A010000)     // the first page ID. other page = first page ID + relevant num;
#define	StartSoundSet       ((unsigned long)0x060480A0)     // 06,start-music; 04, 4 musics; 80, the volume value; 04, return value about music number.
#define	FONT_EEPROM      90

/*variable addr*/
#define	ExchangepageAddr	0x0084
#define	SoundAddr			0x00A0
#define	StartIcon			0x1000
#define	FeedrateDisplay		0x1006
#define	Stopprint			0x1008
#define	Pauseprint			0x100A
#define	Resumeprint			0x100C
#define	PrintscheduleIcon	0x100E
#define	Timehour			0x1010
#define	Timemin				0x1012
#define	IconPrintstatus		0x1014
#define	Percentage			0x1016
#define	FanKeyIcon			0x101E

#define	HeatPercentIcon		0x1024

#define	NzBdSet				0x1032
#define	NozzlePreheat		0x1034
#define	NozzleTemp			0x1036
#define	BedPreheat			0x103A
#define	Bedtemp				0x103C

#define	AutoZeroIcon		0x1042
#define	AutoLevelMode		0x1045
#define	AutoZero			0x1046
#define	DisplayXaxis		0x1048
#define	DisplayYaxis		0x104A
#define	DisplayZaxis		0x104C

#define	FilementUnit1		0x1054
#define	Exchfilement		0x1056
#define	FilementUnit2		0x1058

#define	MacVersion			0x1060
#define	SoftVersion			0x106A
#define	PrinterSize			0x1074
#define	CorpWebsite			0x107E
#define	VolumeIcon			0x108A
#define	SoundIcon			0x108C
#define	AutolevelIcon		0x108D
#define	ExchFlmntIcon		0x108E
#define	AutolevelVal		0x1100

#define	FilenameIcon		0x1200
#define	FilenameIcon1		0x1220
#define	Printfilename		0x2000
#define	SDFILE_ADDR			0x200A
#define	FilenamePlay		0x20D2
#define	FilenameChs			0x20D3
#define	Choosefilename		0x20D4
#define	FilenameCount		0x20DE
#define	FilenameNature		0x6003

#define Zaxis               0x3004
#define VmaxX               0x3010
#define VmaxY               0x3012
#define VmaxZ               0x3014
#define VmaxE               0x3016

#define Accel               0x3018
#define ARetract            0x301A
#define ATravel             0x301C
#define AmaxX               0x301E
#define AmaxY               0x3020
#define AmaxZ               0x3022
#define AmaxE               0x3024

#define Xjerk               0x3026
#define Yjerk               0x3028
#define Zjerk               0x302A
#define Ejerk               0x302C

#define Xsteps              0x302E
#define Ysteps              0x3030
#define Zsteps              0x3032
#define Esteps              0x3034

#define PLANozzle           0x3036
#define PLABed              0x3038
#define ABSNozzle           0x303A
#define ABSBed              0x303C




/************struct**************/
typedef struct DataBuf
{
    unsigned char len;  
    unsigned char head[2];
    unsigned char command;
    unsigned long addr;
    unsigned long bytelen;
    unsigned short data[32];
    unsigned char reserv[4];
} DB;

typedef struct CardRecord
{
    char recordcount;
    int Filesum;
    unsigned long addr[FileNum];
    char Cardshowfilename[FileNum][FileNameLen];
    char Cardfilename[FileNum][FileNameLen];
}CRec;

class RTSSHOW {
  public:
    RTSSHOW();
    int RTS_RecData();
    void RTS_SDCardInit(void);
    void RTS_SDCardUpate(void);
    int RTS_CheckFilement(int);
    void RTS_SndData(void);
    void RTS_SndData(const String &, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(const char[], unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(char, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned char*, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(int, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(float, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned int,unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(long,unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned long,unsigned long, unsigned char = VarAddr_W);
    void RTS_SDcard_Stop();
    void RTS_HandleData();
    void RTS_Init();
	void OnPowerLossResume();
    DB recdat;
    DB snddat;
  private:
    unsigned char databuf[SizeofDatabuf];
  };

extern RTSSHOW rtscheck;

#define	Addvalue	3
#define	PrintChoice_Value	(0+Addvalue)
#define	Zoffset_Value		(3+Addvalue)
#define	Setting_Value		(8+Addvalue)
#define	XYZEaxis_Value		(12+Addvalue)
#define	Filement_Value		(15+Addvalue)
#define	Language_Value		(18+Addvalue)
#define	Filename_Value		(22+Addvalue)

enum PROC_COM {Printfile = 0, Ajust, Feedrate, PrintChoice = PrintChoice_Value, Zoffset=Zoffset_Value, TempControl, ManualSetTemp,
               Setting=Setting_Value, ReturnBack, Bedlevel, Autohome, XYZEaxis = XYZEaxis_Value, Filement = Filement_Value,
			   LanguageChoice = Language_Value, No_Filement, PwrOffNoF, Volume, Filename = Filename_Value, Advanced
              };

const unsigned long Addrbuf[] = {0x1002, 0x1004, 0x1006, 0x1008, 0x100A, 0x100C, 0x1026, 0x1030, 0x1032, 0x1034, 0x103A,
                                 0x103E, 0x1040, 0x1044, 0x1046, 0x1048, 0x104A, 0x104C, 0x1054, 0x1056, 0x1058, 0x105C,
                                 0x105E, 0x105F, 0x1088, 0x3010, 0x3012, 0x3014, 0x3016, 0x3018, 0x301A, 0x301C, 0x301E,
								 0x3020, 0x3022, 0x3024, 0x3026, 0x3028, 0x302A, 0x302C, 0x302E, 0x3030, 0x3032, 0x3034,
								 0x3036, 0x3038, 0x303A, 0x303C, 0x303E, 0
                                };

extern void RTSUpdate();
extern void RTSInit();

extern char waitway;
extern char CardCheckStatus[2];
extern bool InforShowStatus;
extern unsigned char LanguageRecbuf;
extern unsigned char AxisPagenum;
extern bool AutohomeKey;
extern bool TPShowStatus;
extern bool AutoLevelStatus;
extern int Update_Time_Value;
extern bool PoweroffContinue;
extern char FilementStatus[2];
extern char commandbuf[30];
extern int PrintModeTime;

#endif// RTS_H
