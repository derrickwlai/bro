// This file is automatically generated from zip.pac.

#ifndef zip_pac_h
#define zip_pac_h

#include <vector>

#include "binpac.h"


#include "Event.h"
#include "file_analysis/File.h"
#include "events.bif.h"
#include "types.bif.h"

namespace binpac {

namespace ZIP_File {
class ContextZIP_File;
class ZIP_File_Analyzer;
class Files;
class File;
class LocalFileHeader;
class DataDescriptor;
class ExtraDataHeader;
class CentralDirectoryStructure;
class DigitalSignature;
class EndOfCentralDirectoryStructure;
class Flow;
} // namespace ZIP_File

namespace ZIP_File {

class ContextZIP_File
{
public:
	ContextZIP_File(ZIP_File_Analyzer * analyzer, Flow * flow, FlowBuffer * flow_buffer);
	~ContextZIP_File();
	
	// Member access functions
	ZIP_File_Analyzer * analyzer() const { return analyzer_; }
	Flow * flow() const { return flow_; }
	FlowBuffer * flow_buffer() const { return flow_buffer_; }
	
protected:
	ZIP_File_Analyzer * analyzer_;
	Flow * flow_;
	FlowBuffer * flow_buffer_;
};


class ZIP_File_Analyzer : public binpac::ConnectionAnalyzer
{
public:
	ZIP_File_Analyzer(BroFileAnalyzer * bro_analyzer);
	~ZIP_File_Analyzer();
	
	// Member access functions
	Flow * downflow() const { return downflow_; }
	Flow * upflow() const { return upflow_; }
	BroFileAnalyzer * bro_analyzer() const { return bro_analyzer_; }
	
	void NewData(bool is_orig, const_byteptr begin, const_byteptr end);
	void NewGap(bool is_orig, int gap_length);
	void FlowEOF(bool is_orig);
	
protected:
	Flow * downflow_;
	Flow * upflow_;
	BroFileAnalyzer * bro_analyzer_;
};


class Files
{
public:
	Files();
	~Files();
	bool ParseBuffer(flow_buffer_t t_flow_buffer, ContextZIP_File * t_context);
	
	// Member access functions
	vector<File *> * file() const { return file_; }
	int byteorder() const { return byteorder_; }
	
protected:
	vector<File *> * file_;
	File * file__elem_;
	int file__arraylength_;
	int file__elem__it_;
	int byteorder_;
	int parsing_state_;
};


class File
{
public:
	File();
	~File();
