#ifndef _Log_
#define _Log_

#define LOG_DEBUG   0
#define LOG_INFO    1
#define LOG_WARNING 2
#define LOG_ERROR   3
#define LOG_SEVERE  4
#define LOG_FATAL   5
#define LOG_NONE    6

#include <string>

///* Minimum level of log messages to display (default: none) */
//int _log_level = LOG_NONE;
//
///* Sets the log level to the value of new_level. */
//void setLogLevel(int new_level)
//{
//	if(new_level >= LOG_DEBUG && new_level < LOG_NONE) _log_level = new_level;
//}
//
///* Gets the log level */
//int getLogLevel(void)
//{
//	return _log_level;
//}



class GeneralLogControl //Base class of any specific log control class,providing basic controls
	{
	protected:
		bool m_bEnabled;
	public:
		GeneralLogControl(const std::string ControlStr):m_bEnabled(true){};//log is enabled by default
		GeneralLogControl():m_bEnabled(true){};
		virtual ~GeneralLogControl(){};
		virtual void Pause(){m_bEnabled=false;}
		virtual void Resume(){m_bEnabled=true;}
		virtual bool CanAdd(std::string& LogStr){return m_bEnabled;}
	};


class FileLogImpl //class that implements file logging ability
{
protected:
	std::string m_LogFileName;
public:
	FileLogImpl(const std::string FileName):m_LogFileName(FileName)
	{
		/*if(m_LogFileName == "")
			m_LogFileName="log.txt";*/
	};
	virtual void AddTimeStamp(std::string& LogStr);
	virtual ~FileLogImpl(){};
	virtual bool AddLog(std::string& LogStr);
	virtual void Clear();
};
template<class ImplT, class ControlT>
class CMjLog
{
protected:
	ControlT m_Control;	  //log control class
	ImplT	 m_Impl;	  //log implementation class
public:
	CMjLog(const std::string ImplStr="",const std::string ControlStr="")
	:m_Control(ControlStr),m_Impl(ImplStr){};
	virtual ~CMjLog(){};
	bool AddLog(const std::string& LogStr) //Add one piece of log message
	{
		return AddLog(LogStr.c_str());
	}
	bool AddLog(const char* pLogStr) //Add one piece of log message
	{
		std::string log=pLogStr;
		if(m_Control.CanAdd(log))
			return m_Impl.AddLog(log);
		else return false;
	}

	void Pause()   //Pause log process
	{
		m_Control.Pause();
	}
	void Resume() //Resume log process
	{
		m_Control.Resume();
	}
	void Clear()  //Clear log content
	{
		m_Impl.Clear();
	}

};
	/*--------------CFileLog definition------------------*/
	typedef CMjLog<FileLogImpl,GeneralLogControl> CFileLog;
	/*------------CFileLog Usage-------------------------
		MjTools::CFileLog log("C:\\test.log"); //Construct a new logfile or open a existing log file
		log.Clear();				//Delete previous logs.
		log.AddLog("This is a test line"); //Add one log message
	---------------------------------------------------*/	
#endif
