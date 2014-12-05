//#include "V8Helpers.h"
//
//void Gunship::V8Helpers::ReportException( v8::Isolate* isolate, v8::TryCatch& try_catch )
//{
//	v8::HandleScope handle_scope( isolate );
//	v8::String::Utf8Value exception( try_catch.Exception() );
//	const char* exception_string = *exception;
//	v8::Handle< v8::Message > message = try_catch.Message();
//	if ( message.IsEmpty() )
//	{
//		// V8 didn't provide any extra information about this error; just
//		// print the exception.
//		printf( "%s\n", exception_string );
//	}
//	else
//	{
//		// Print (filename):(line number): (message).
//		v8::String::Utf8Value filename(
//			message->GetScriptOrigin().ResourceName() );
//		const char* filename_string = *filename;
//		int linenum = message->GetLineNumber();
//		printf( "%s:%i: %s\n", filename_string, linenum, exception_string );
//		// Print line of source code.
//		v8::String::Utf8Value sourceline( message->GetSourceLine() );
//		const char* sourceline_string = *sourceline;
//		printf( "%s\n", sourceline_string );
//		// Print wavy underline (GetUnderline is deprecated).
//		int start = message->GetStartColumn();
//		for ( int i = 0; i < start; i++ )
//		{
//			printf( " " );
//		}
//		int end = message->GetEndColumn();
//		for ( int i = start; i < end; i++ )
//		{
//			printf( "^" );
//		}
//		printf( "\n" );
//	}
//}
//
//// Blatantly stolen from the shell.cc example that comes with v8.
//// currently being used as a placeholder until I can be bothered to
//// add some better logging functionality.
//void Gunship::V8Helpers::Print( const v8::FunctionCallbackInfo< v8::Value >& args )
//{
//	bool first = true;
//	for ( int i = 0; i < args.Length(); i++ )
//	{
//		v8::HandleScope handle_scope( args.GetIsolate() );
//		if ( first )
//		{
//			first = false;
//		}
//		else
//		{
//			printf( " " );
//		}
//		v8::String::Utf8Value str( args[i] );
//		const char* cstr = *str;
//		printf( "%s", cstr );
//	}
//	printf( "\n" );
//	fflush( stdout );
//}
//
//void Gunship::V8Helpers::RunStartupScript( v8::Isolate isolate, const char* file )
//{
//	// create scope for v8
//	v8::Isolate::Scope isolateScope( isolate );
//	v8::HandleScope handleScope( isolate );
//	v8::Local< v8::Context > context = v8::Local< v8::Context >::New( isolate, _context );
//	v8::Context::Scope contextScope( context );
//
//	std::string startup = LoadScript( JS_ROOT_DIR + ( "/" + std::string( file ) ) );
//	{
//		v8::TryCatch tryCatch;
//
//		v8::Local< v8::Script > script = v8::Script::Compile( V8_STRING( isolate, startup.c_str() ) );
//		v8::Local< v8::Value > result = script->Run();
//		v8::String::Utf8Value utf8( result );
//
//		if ( tryCatch.HasCaught() )
//		{
//			printf( "startup script %s failed:\n", file );
//			V8Helpers::ReportException( isolate, tryCatch );
//		}
//	}
//}
//
//std::string Gunship::V8Helpers::LoadScript( std::string file )
//{
//	std::string result;
//
//	char buffer[256];
//	SDL_RWops* script = SDL_RWFromFile( file.c_str(), "r" ); // hoo boy this is a leak waiting to happen.
//
//	if ( script == nullptr )
//	{
//		printf( "Script %s not found! SDL Error: %s\n", file.c_str(), SDL_GetError() );
//		SDL_RWclose( script );
//		return std::string();
//	}
//
//	size_t sentinel = 1;
//	do
//	{
//		memset( buffer, 0, sizeof( buffer ) );
//		sentinel = SDL_RWread( script, buffer, sizeof( buffer ) - 1, 1 );
//		result += buffer;
//	}
//	while ( sentinel != 0 );
//
//	SDL_RWclose( script );
//	return result;
//}
