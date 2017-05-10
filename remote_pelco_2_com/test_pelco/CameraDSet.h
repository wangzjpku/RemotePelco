#pragma once
class CameraDSet
{
public:
	CameraDSet(void);
	~CameraDSet(void);

	int PanRun( unsigned char * data , unsigned int address , unsigned int para );
	int TiltRun( unsigned char * data , unsigned int address , unsigned int para );
	int PresetSave( unsigned char * data , unsigned int address , unsigned int para );
	int PresetRecall( unsigned char * data , unsigned int address , unsigned int para );
	int ZoomRun( unsigned char * data , unsigned int address , unsigned int para );
	int FocusRun( unsigned char * data , unsigned int address , unsigned int para );
	int IrisMode( unsigned char * data , unsigned int address , unsigned int para );
	int IrisRun( unsigned char * data , unsigned int address , unsigned int para );
	int LimitSet( unsigned char * data , unsigned int address , unsigned int para );
	int PowerSet( unsigned char * data , unsigned int address , unsigned int para );
	int CameraRecod( unsigned char * data , unsigned int button );
	int CameraSet( unsigned char * data , unsigned char speed );	

	typedef struct Command_Header
	{
		unsigned char tag;
		unsigned char address[3];
		unsigned char cl;
		unsigned char d1[2];
		//unsigned char d2;
		unsigned char cr;
	}Command_Header;

	typedef struct Camera_Header_1
	{
		unsigned char tag;
		unsigned char cl;
		unsigned char d1;
		unsigned char cr;
		unsigned char t[4];
	}Camera_Header_1;

};


