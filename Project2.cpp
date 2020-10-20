#include <iostream>
#include <string>
#include <cstdio>
#include <time.h>
#include <iomanip>																	// cout 여백

#define MAX_SEVERITIES 4															// Severity 개수
#define LOG(severity) LOG_##severity												// LOG 모양 결정
#define LOG_INFO	logprint(INFO		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_WARNING logprint(WARNING	,__FILE__,__FUNCTION__,__LINE__)
#define LOG_ERROR	logprint(ERROR		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_FATAL	logprint(FATAL		,__FILE__,__FUNCTION__,__LINE__)


enum Severity {
	INFO = 0,
	WARNING = 1,
	ERROR = 2,
	FATAL = 3
};

static const char* SeverityNames[MAX_SEVERITIES] = { "INFO","WARNING","ERROR","FATAL" };


class LogMessage {

	// 멤버 변수 //////////////////////////////////////////////////////////
private:
	std::string severity;												// INFO, WARNING, ERROR, FATAL
	std::string fileName;
	std::string funcName;
	int line;

public:

	// 생성 / 소멸자 //////////////////////////////////////////////////////
	LogMessage(const std::string& s_, const char* fileName_,
		const char* funcName_, const int& line_)
		: severity(s_), fileName(fileName_),
		funcName(funcName_), line(line_) {
	}
	~LogMessage() {
	}

	// 멤버 변수 얻기 /////////////////////////////////////////////////////
	std::string getSeverity() const { return severity; }
	std::string getFileName() const { return fileName; }
	std::string getFuncName() const { return funcName; }
	int getLine() const { return line; }


	// 멤버 함수///////////////////////////////////////////////////////////
	// 선택 해서 넣을 수 있도록 구현
	void log_configuration() {

	}
	// Template Method 템플릿의 패턴을 
	void LogMessage_print() {
		time_stamp();
		severity_stamp();
		directory_stamp();
		function_stamp();
		line_stamp();
	}

	// 개별 함수
	void time_stamp() {
		
		time_t timer = time(NULL); // time_t 데이터 타입 변수 timer에 현재 시각 저장
		struct tm t;				// tm 구조체 타입의 날짜
		localtime_s(&t, &timer);
		// 시간 calibration
		t.tm_year += 1900;
		t.tm_mon += 1;

		std::cout << "[" << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << " ";
		std::cout << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
	}

	void severity_stamp() {
		std::cout << "[" << getSeverity() << "] ";
	}

	void directory_stamp() {
		std::cout << "[directory : " << getFileName() << "] ";
	}

	void function_stamp() {
		std::cout << "[function : " << getFuncName() << "] ";
	}

	void line_stamp() {
		std::cout << "[line : " << getLine() << "]  " << std::endl;
	}
	// log_comment 부터는 severity 별로 다르게
	virtual void log_comment() = 0;
	
};

class InfoMessage : public LogMessage{
	// 멤버 변수 //////////////////////////////////////////////////////////

public:
	// 생성 / 소멸자 //////////////////////////////////////////////////////
	InfoMessage(const std::string& s_, const char* fileName_, const char* funcName_, const int& line_)
		: LogMessage(s_, fileName_, funcName_, line_){}
	~InfoMessage() {}
	
	// 멤버 변수 얻기 /////////////////////////////////////////////////////
	
	// 멤버 함수///////////////////////////////////////////////////////////
	void log_comment() override {

	}
};



void logprint(const int& s, const char* fileName_, const char* funcName_, const int& line_){
	LogMessage* m = new InfoMessage(SeverityNames[s], fileName_, funcName_, line_);
	m->LogMessage_print();
}




int main() {

	while(1)
	{
		LOG(INFO);			getchar();
		LOG(WARNING);		getchar();
		LOG(ERROR);			getchar();
		LOG(FATAL);			getchar();
	}	
}