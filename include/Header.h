#pragma once

#include <vector>
#include <string>
#include <chrono>

#include <iostream>


class Header
{
private:
	Header() {};
	
	~Header() {};

private:
	static int myrank_;

	static int ndomain_;

	static std::chrono::system_clock::time_point start_time_;

	static std::chrono::system_clock::time_point end_time_;

	static std::string code_name_;

public:
	static void initialize(void);

	static int getMyRank(void) { return myrank_; };

	static int getNumDomain(void) { return ndomain_; };

	static void Syncro(void);

	static void startStopWatch(void) { start_time_ = std::chrono::system_clock::now(); };
	
	static void stopStopWatch(void);

	static void message(const bool master_only, const std::string& str);

	static void error(const bool master_only, const std::string& str, std::string file_name, const int num_line );	

};

#define HEADER Header::initialize()

#define MYRANK Header::getMyRank()

#define NDOMAIN Header::getNumDomain()

#define SYNCRO Header::Syncro()

#define TIMESTART Header::startStopWatch()

#define TIMEEND Header::stopStopWatch()

#define MASTER_MESSAGE(text) Header::message(true,text)

#define MASTER_ERROR(text,file_name,num_line) Header::error(true,text,file_name,num_line)





