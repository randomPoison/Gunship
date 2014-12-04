#include "V8Helpers.h"

void V8Helpers::ReportException( v8::Isolate* isolate, v8::TryCatch& try_catch )
{
	v8::HandleScope handle_scope( isolate );
	v8::String::Utf8Value exception( try_catch.Exception() );
	const char* exception_string = *exception;
	v8::Handle< v8::Message > message = try_catch.Message();
	if ( message.IsEmpty() )
	{
		// V8 didn't provide any extra information about this error; just
		// print the exception.
		printf( "%s\n", exception_string );
	}
	else
	{
		// Print (filename):(line number): (message).
		v8::String::Utf8Value filename(
			message->GetScriptOrigin().ResourceName() );
		const char* filename_string = *filename;
		int linenum = message->GetLineNumber();
		printf( "%s:%i: %s\n", filename_string, linenum, exception_string );
		// Print line of source code.
		v8::String::Utf8Value sourceline( message->GetSourceLine() );
		const char* sourceline_string = *sourceline;
		printf( "%s\n", sourceline_string );
		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn();
		for ( int i = 0; i < start; i++ )
		{
			printf( " " );
		}
		int end = message->GetEndColumn();
		for ( int i = start; i < end; i++ )
		{
			printf( "^" );
		}
		printf( "\n" );
	}
}
