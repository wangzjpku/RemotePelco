#include "StdAfx.h"
#include "CameraDSet.h"

CameraDSet::CameraDSet(void)
{
}

CameraDSet::~CameraDSet(void)
{
}

int CameraDSet::PanRun( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x50;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::TiltRun( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x54;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::PresetSave( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x4d;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::PresetRecall( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x52;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::ZoomRun( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x5a;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::FocusRun( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x66;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::IrisMode( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x44;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::IrisRun( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x49;		
		sprintf( (char *)Comdata->d1 ,  "%0.2d" , para );
		Comdata->cr = 0x0d;	 	  
	return 0;
}

int CameraDSet::LimitSet( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x4c;		
		sprintf((char *)Comdata->d1 ,  "%0.1d" , para );
		Comdata->d1[1] = 0x0d;	 	  
		//Comdata->cr = 0x0d;	
	return 0;
}

int CameraDSet::PowerSet( unsigned char * data , unsigned int address , unsigned int para )
{
		Command_Header * Comdata;		
		Comdata = (Command_Header *)data;				
	  Comdata->tag = 0x23;	  
	  sprintf( (char *)Comdata->address ,  "%0.3d" , address );   
		Comdata->cl = 0x4f;		
		sprintf( (char *)Comdata->d1 ,  "%0.1d" , para );
		Comdata->d1[1] = 0x0d;	 	  
		//Comdata->cr = 0x0d;	
	return 0;
}

int CameraDSet::CameraRecod( unsigned char * data , unsigned int button )
{
		Camera_Header_1 * Comdata;		
		Comdata = (Camera_Header_1 *)data;				
	  Comdata->tag = 0xff;	  
		Comdata->cl = 0x00;
		
		if ( button == 1 )		
    	Comdata->d1 = 0x1;
    else if(button == 0)
    	Comdata->d1 = 0x0;
    	
		Comdata->cr = 0x0;
			
	return 0;
}

int CameraDSet::CameraSet( unsigned char * data , unsigned char speed )
{
		Camera_Header_1 * Comdata;		
		Comdata = (Camera_Header_1 *)data;				
	  Comdata->tag = 0xff;	  
		Comdata->cl = 0x01;
    Comdata->d1 = 0x0;
    	
		Comdata->cr = speed;
			
	return 0;
}
