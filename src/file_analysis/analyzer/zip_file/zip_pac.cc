// This file is automatically generated from zip.pac.


#ifdef __clang__
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif

#include "zip_pac.h"

namespace binpac {

namespace ZIP_File {
ContextZIP_File::ContextZIP_File(ZIP_File_Analyzer * analyzer, Flow * flow, FlowBuffer * flow_buffer)
	{
	analyzer_ = analyzer;
	flow_ = flow;
	flow_buffer_ = flow_buffer;
	}

ContextZIP_File::~ContextZIP_File()
	{
	}

ZIP_File_Analyzer::ZIP_File_Analyzer(BroFileAnalyzer * bro_analyzer)
	{
	downflow_ = new Flow(this);
	upflow_ = new Flow(this);
	bro_analyzer_ = bro_analyzer;
	}

ZIP_File_Analyzer::~ZIP_File_Analyzer()
	{
	delete downflow_;
	downflow_ = 0;
	delete upflow_;
	upflow_ = 0;
	}

void ZIP_File_Analyzer::NewData(bool is_orig, const_byteptr begin, const_byteptr end)
	{
	if ( is_orig )
		upflow_->NewData(begin, end);
	else
		downflow_->NewData(begin, end);
	}

void ZIP_File_Analyzer::NewGap(bool is_orig, int gap_length)
	{
	if ( is_orig )
		upflow_->NewGap(gap_length);
	else
		downflow_->NewGap(gap_length);
	}

void ZIP_File_Analyzer::FlowEOF(bool is_orig)
	{
	if ( is_orig )
		upflow_->FlowEOF();
	else
		downflow_->FlowEOF();
	}

Files::Files()
	{
	file_ = 0;
	file__elem_ = 0;
	file__arraylength_ = 0;
	file__elem__it_ = 0;
	file__elem__it_ = -1;
	byteorder_ = littleendian;
	parsing_state_ = 0;
	parsing_state_ = 0;
	}

Files::~Files()
	{
	delete file__elem_;
	file__elem_ = 0;
	if ( file() )
		{
		for ( int i = 0; i < (int) file()->size(); ++i )
			{
			File * file__elem_ = (*file_)[i];
			delete file__elem_;
			file__elem_ = 0;
			}
		}
	delete file_;
	}

bool Files::ParseBuffer(flow_buffer_t t_flow_buffer, ContextZIP_File * t_context)
	{
	bool t_val_parsing_complete;
	t_val_parsing_complete = false;
	switch ( parsing_state_ ) {
	case 0:
		// Parse "file"
		if ( ! file_ )
			{
			}
		parsing_state_ = 1;
	case 1:
		{
		bool t_file_parsing_complete;
		t_file_parsing_complete = false;
		if ( file__elem__it_ < 0 )
			{
			// Initialize only once
			file__elem__it_ = 0;
			file_ = new vector<File *>;
			}
		for (; /* forever */; ++file__elem__it_)
			{
			if ( ! file__elem_ )
				{
				file__elem_ = new File();
				}
			bool t_file__elem_parsing_complete;
			t_file__elem_parsing_complete = false;
			while ( ! t_file__elem_parsing_complete && t_flow_buffer->ready() )
				{
				const_byteptr t_begin_of_data = t_flow_buffer->begin();
				const_byteptr t_end_of_data = t_flow_buffer->end();
				t_file__elem_parsing_complete = file__elem_->ParseBuffer(t_flow_buffer, t_context);
				if ( t_file__elem_parsing_complete )
					{
					// Evaluate 'let' and 'withinput' fields
					}
				}
			if ( ! t_file__elem_parsing_complete )
				goto need_more_data;
			file_->push_back(file__elem_);
			// Check &until( ( @$element->signature@ == ((int) 0x06054b50) ) )
			if (  ( file__elem_->signature() == 0x06054b50 )  )
				{
				t_file_parsing_complete = true;
				file__elem_ = 0;
				goto end_of_file;
				}
			file__elem_ = 0;
			}
	end_of_file: ;
		if ( t_file_parsing_complete )
			{
			// Evaluate 'let' and 'withinput' fields
			}
		if ( ! (t_file_parsing_complete) )
			goto need_more_data;
		}
		
		
		t_val_parsing_complete = true;
	}
	if ( t_val_parsing_complete )
		{
		// Evaluate 'let' and 'withinput' fields
		}
	BINPAC_ASSERT(t_val_parsing_complete);
	return t_val_parsing_complete;
	
need_more_data:
	BINPAC_ASSERT(!(t_val_parsing_complete));
	return false;
	}

File::File()
	{
	signature_ = 0;
	sig_switch_case_index_ = -1;
	local_file_ = 0;
	extra_data_ = 0;
	central_dir_ = 0;
	digital_sig_ = 0;
	end_of_central_dir_ = 0;
	byteorder_ = littleendian;
	length_ = 0;
	proc_ = 0;
	buffering_state_ = 0;
	buffering_state_ = 0;
	}

File::~File()
	{
	switch ( sig_switch_case_index() )
		{
		case 67324752:
			// Clean up "local_file"
			{
			delete local_file_;
			local_file_ = 0;
			}
			break;
		case 134630224:
			// Clean up "extra_data"
			{
			delete extra_data_;
			extra_data_ = 0;
			}
			break;
		case 33639248:
			// Clean up "central_dir"
			{
			delete central_dir_;
			central_dir_ = 0;
			}
			break;
		case 84233040:
			// Clean up "digital_sig"
			{
			delete digital_sig_;
			digital_sig_ = 0;
			}
			break;
		case 101010256:
			// Clean up "end_of_central_dir"
			{
			delete end_of_central_dir_;
			end_of_central_dir_ = 0;
			}
			break;
		}
	}

