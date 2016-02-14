#include "WebNavigation.h"

WebNavigation::WebNavigation()
{
	_initialPage = "http://www.acm.org/";
	_currentPage = _initialPage;
	_failMsg = "Ignored";

	_backCommand = "BACK";
	_forwardCommand = "FORWARD";
	_visitCommand = "VISIT";
	_quitCommand = "QUIT";
}


std::string WebNavigation::back()
{
	if( _backwardStack.empty() )
	{
		return _failMsg;
	}
	_forwardStack.push( _currentPage );
	_currentPage = _backwardStack.top();
	_backwardStack.pop();

	return _currentPage;
}

std::string WebNavigation::forward()
{
	if( _forwardStack.empty() )
	{
		return _failMsg;
	}

	_backwardStack.push( _currentPage );
	_currentPage = _forwardStack.top();
	_forwardStack.pop();

	return _currentPage;
}

std::string WebNavigation::visit( const std::string webSite )
{
	_backwardStack.push( _currentPage );
	_currentPage = webSite;

	clearForwardStack();

	return _currentPage;
}

bool WebNavigation::quit()
{
	return QUIT;
}

bool WebNavigation::excute( std::string command,
		std::string& currentPage )
{
	if( strcmp( command.c_str(), _quitCommand ) == 0 )
	{
		return quit();
	}

	currentPage = _failMsg;
	if( strcmp( command.c_str(), _backCommand ) == 0 )
	{
		currentPage = back();
	}
	else if( strcmp( command.c_str(), _forwardCommand ) == 0 )
	{
		currentPage = forward();
	}
	else if( strncmp( command.c_str(), _visitCommand, 5 ) == 0 )
	{
		int startPosition = getWebSiteStartPosition( &command[5] );
		if( startPosition != -1 )
		{
			currentPage = visit( &command[ 5 + startPosition ] );
		}
	}

	return SUCCESS;
}

int WebNavigation::getWebSiteStartPosition( char* afterVisitCommand )
{
	if( afterVisitCommand[0] == '\0' || !isspace(afterVisitCommand[0]) )
	{
		return -1;
	}

	for( int i = 1 ; i < strlen(afterVisitCommand) ; ++i )
	{
		if( !isspace(afterVisitCommand[i]) )
		{
			return i;
		}
	}
	return -1;
}

void WebNavigation::clearForwardStack()
{
	while( !_forwardStack.empty() )
	{
		_forwardStack.pop();
	}
}
