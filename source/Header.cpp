#include <Header.h>

int Header::myrank_ = 0;
int Header::ndomain_ = 1;
std::chrono::system_clock::time_point Header::start_time_;
std::chrono::system_clock::time_point Header::end_time_;
std::string Header::code_name_ = "gridbuilder";

void Header::initialize(void)
{
#ifdef _MPI_USE_
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank_);
	MPI_Comm_size(MPI_COMM_WORLD, &ndomain_);
	SYNCRO;
#else
	myrank_ = 0;
	ndomain_ = 1;
#endif	
}

void Header::Syncro(void)
{
#ifdef _MPI_USE_
	MPI_Barrier(MPI_COMM_WORLD);
#endif
}

void Header::stopStopWatch(void)
{
	end_time_ = std::chrono::system_clock::now();

	std::chrono::microseconds time = std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - start_time_);

	//MASTER_MESSAGE("time:" + StringEditor::toString(time.count()) + "ms");
}


void Header::message(const bool master_only, const std::string& str)
{
	if (master_only)
		std::cout << "(MASTER) : " << str << "\n";
	else
		std::cout << "(MEMBER " << myrank_ << ") : " << str << "\n";
}


void Header::error(const bool master_only, const std::string& message, std::string file_name, const int num_line)
{
	const size_t location = file_name.rfind(code_name_);
	file_name.erase(0, location + code_name_.size() + 1);

	if (master_only)
	{
		std::cout << "\n\n============================ABNORMAL TERMINATION============================\n\n";
		std::cout << "Message : " << message << "\nFile\t: " << file_name << "\nLine\t: " << num_line;
		std::cout << "\n\n============================ABNORMAL TERMINATION============================\n\n";
	}
#ifdef _MPI_USE_
	MPI_Abort(MPI_COMM_WORLD, 99);
#else
	std::exit(99);
#endif 
}
